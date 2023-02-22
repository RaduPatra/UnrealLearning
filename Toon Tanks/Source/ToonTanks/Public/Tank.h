// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Tank.generated.h"

class ATankPlayerController;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	void Move(float Value);
	void Turn(float Value);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnDeath() override;


private:
	void GetNonVisibleHit(FHitResult& OutHitResult) const;
	bool GetPlaneHit(FHitResult& HitResult) const;
	void GetSkyHit(FHitResult& OutHitResult) const;
	void FireProjectile();
	bool IsInCooldown() const;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	AStaticMeshActor* PlayerFollowSkyAimBox;


	ATankPlayerController* TankPlayerController;

	UPROPERTY(EditAnywhere)
	float Speed = 400.f;

	UPROPERTY(EditAnywhere)
	float TurnSpeed = 100.f;

	UPROPERTY()
	float FireCooldown = 0;

	UPROPERTY(EditAnywhere)
	float FireTime = 2;
};
