// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsTargetInRange())
	{
		const FVector TargetLocation = TargetTank->GetActorLocation();
		RotateTurret(TargetLocation, DeltaTime);
	}
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	TargetTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATurret::ShootProjectile, ShootCooldown, true);

	//!
	ToonTanksGamemode = Cast<AToonTanksGamemode>(UGameplayStatics::GetGameMode(this));
	if (ToonTanksGamemode)
	{
		ToonTanksGamemode->RegisterTurret(this);
	}
}

bool ATurret::IsTargetInRange()
{
	if (!TargetTank) return false;;
	if (TargetTank->IsHidden()) return false;

	const FVector TargetLocation = TargetTank->GetActorLocation();
	const float DistToTarget = FVector::Dist(GetActorLocation(), TargetLocation);
	return DistToTarget <= TargetShootDistance;
}

void ATurret::OnDeath()
{
	Super::OnDeath();
	UE_LOG(LogTemp, Warning, TEXT("Turret Died"));
	ToonTanksGamemode->HandleTurretDeath(this);
	Destroy();
}

void ATurret::ShootProjectile()
{
	if (IsTargetInRange())
	{
		Fire();
	}
}
