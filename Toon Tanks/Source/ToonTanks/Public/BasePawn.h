// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void Tick(float DeltaTime) override;
	void RotateTurret(FVector Direction, float DeltaTime) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Fire();
	virtual void OnDeath();
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere)
	float TurretRotationSpeed = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent* CapsuleComp;

private:
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	USceneComponent* SpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	class UHealthComponent* HealthComp;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	UParticleSystem * DeathParticles;

	UPROPERTY(EditAnywhere)
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;
};
