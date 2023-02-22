// Fill out your copyright notice in the Description page of Project Settings.


#include "UMyStaticLibrary.h"

bool UUMyStaticLibrary::GetHitResultUnderCursor(const APlayerController* Controller,
                                                ECollisionChannel TraceChannel,
                                                bool bTraceComplex,
                                                FHitResult& HitResult,
                                                const AActor* ActorToIgnore)
{
	float LocationX;
	float LocationY;
	if (Controller->GetMousePosition(LocationX, LocationY))
	{
		FVector2d ScreenPos(LocationX, LocationY);
		FCollisionQueryParams CollisionQueryParams(SCENE_QUERY_STAT(ClickableTrace), bTraceComplex, ActorToIgnore);
		return Controller->GetHitResultAtScreenPosition(ScreenPos, TraceChannel, CollisionQueryParams,
		                                                HitResult);
	}
	return false;
}
