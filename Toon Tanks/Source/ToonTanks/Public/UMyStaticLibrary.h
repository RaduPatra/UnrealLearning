// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UMyStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UUMyStaticLibrary final : public UObject
{
	GENERATED_BODY()
public:
	/*
	 * Like APlayerController::GetHitResultUnderCursor but we can also add ignored actors to collision params
	 */
	static bool GetHitResultUnderCursor(const APlayerController* Controller,
	                                    ECollisionChannel TraceChannel, bool bTraceComplex,
	                                    FHitResult& HitResult, const AActor* ActorToIgnore);
};
