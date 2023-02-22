// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "ToonTanksGamemode.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual bool IsTargetInRange();
	// virtual void OnDeath() override;
	virtual void OnDeath() override;

private:
	void ShootProjectile();

	class ATank* TargetTank;

	UPROPERTY(EditAnywhere)
	float TargetShootDistance = 600;

	UPROPERTY(EditAnywhere)
	float ShootCooldown = 6.f;

	FTimerHandle TimerHandle;

	UPROPERTY()
	AToonTanksGamemode * ToonTanksGamemode;
};
