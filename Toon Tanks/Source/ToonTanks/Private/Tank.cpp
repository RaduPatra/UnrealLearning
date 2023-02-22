// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "TankPlayerController.h"
#include "ToonTanksGamemode.h"
#include "UMyStaticLibrary.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<ATankPlayerController>(GetController());
	UE_LOG(LogTemp, Warning, TEXT("Begin"));
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::FireProjectile);
}

void ATank::Move(float Value)
{
	const FVector DeltaLocation = FVector(Value, 0, 0);
	AddActorLocalOffset(DeltaLocation * Speed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator(0, Value, 0);
	AddActorLocalRotation(DeltaRotation * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void ATank::OnDeath()
{
	Super::OnDeath();
	UE_LOG(LogTemp, Warning, TEXT("Tank Died"));

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	TankPlayerController->ToggleInput(false);
	// CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorEnableCollision(false);
	if (AToonTanksGamemode* Gamemode = Cast<AToonTanksGamemode>(UGameplayStatics::GetGameMode(this)))
	{
		Gamemode->GameOver(false);
	}
}

void ATank::FireProjectile()
{
	if (!IsInCooldown())
	{
		FireCooldown = FireTime;
		Fire();
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireCooldown -= DeltaTime;

	if (!TankPlayerController) return;
	FHitResult HitResult;
	const bool bHitObject = UUMyStaticLibrary::GetHitResultUnderCursor(TankPlayerController, ECC_Visibility, false,
	                                                                   HitResult, this);
	if (!bHitObject)
	{
		//if not hitting objects, get impact point from a plane at player position
		if (!GetPlaneHit(HitResult))
		{
			//if not hitting plane either, get impact point from far away point in the sky towards mouse direction
			GetSkyHit(HitResult);
		}
	}

	RotateTurret(HitResult.ImpactPoint, DeltaTime);
}

bool ATank::IsInCooldown() const
{
	return FireCooldown > 0;
}

bool ATank::GetPlaneHit(FHitResult& HitResult) const
{
	FVector WorldLocation;
	FVector WorldDirection;
	TankPlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	const FPlane Plane = FPlane(GetActorLocation(), FVector::UpVector);
	float T;
	const FVector EndPoint = WorldLocation + WorldDirection * BIG_NUMBER;
	return UKismetMathLibrary::LinePlaneIntersection(WorldLocation, EndPoint, Plane, T, HitResult.ImpactPoint);
}

void ATank::GetSkyHit(FHitResult& OutHitResult) const
{
	FVector WorldLocation;
	FVector WorldDirection;
	TankPlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
	const FVector EndPos = WorldLocation + WorldDirection * 999999;
	OutHitResult.ImpactPoint = EndPos;
}
