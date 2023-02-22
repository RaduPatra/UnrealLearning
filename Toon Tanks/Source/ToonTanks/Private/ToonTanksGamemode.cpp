// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGamemode.h"

#include "TankPlayerController.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGamemode::HandleTurretDeath(ATurret* Turret)
{
	check(Turret != nullptr);

	Turrets.Remove(Turret);
	
	if (Turrets.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroyed All Turrets"));
		GameOver(true);
	}
}

void AToonTanksGamemode::RegisterTurret(ATurret* Turret)
{
	Turrets.Add(Turret);
}

void AToonTanksGamemode::BeginPlay()
{
	Super::BeginPlay();
	ATankPlayerController* TankController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!TankController) return;

	TankController->ToggleInput(false);
	const FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(TankController,
	                                                                   &ATankPlayerController::ToggleInput, true);
	if (StartGameDelay > 0)
	{
		GetWorldTimerManager().SetTimer(StartGameTimerHandle, TimerDelegate, StartGameDelay, false);
	}
	else
	{
		TankController->ToggleInput(true);
	}
}
