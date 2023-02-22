// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGamemode.generated.h"
class ATankPlayerController;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGamemode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void HandleTurretDeath(class ATurret* Turret);
	void RegisterTurret(ATurret* Turret);

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
protected:
	virtual void BeginPlay() override;

	

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	float StartGameDelay = 3;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	FTimerHandle StartGameTimerHandle;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<ATurret*> Turrets;
	

	int TurretsDestroyed;
	int TurretsInGame;
};
