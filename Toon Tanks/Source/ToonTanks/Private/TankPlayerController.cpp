// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::ToggleInput(bool bStatus)
{
	const auto MyPawn = GetPawn();
	if (!MyPawn) return;
	if (bStatus)
	{
		MyPawn->EnableInput(this);
	}
	else
	{
		MyPawn->DisableInput(this);
	}
	bShowMouseCursor = bStatus;
}
