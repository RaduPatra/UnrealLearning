// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "HealthComponent.h"
#include "Tank.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(TurretMesh);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	HealthComp->OnHealthDepleted.AddUObject(this, &ABasePawn::OnDeath);
}

void ABasePawn::Fire()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	const auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	                                                                   SpawnPoint->GetComponentLocation(),
	                                                                   SpawnPoint->GetComponentRotation(), SpawnParams);
	if (SpawnedProjectile)
	{
		SpawnedProjectile->SetLifeSpan(10.f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawned null"));
	}
}

void ABasePawn::OnDeath()
{
	if (DeathParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(),
	                                                             GetActorRotation());
	if (DeathSound)
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());

	if (DeathCameraShakeClass)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePawn::RotateTurret(const FVector Direction, const float DeltaTime) const
{
	const FRotator TurretToHitRot = (Direction - TurretMesh->GetComponentLocation()).Rotation();
	const FRotator TargetRot = FRotator(0, TurretToHitRot.Yaw, 0);
	const FRotator NewRot = FMath::RInterpConstantTo(TurretMesh->GetComponentRotation(), TargetRot, DeltaTime,
	                                                 TurretRotationSpeed);
	TurretMesh->SetWorldRotation(NewRot);
}
