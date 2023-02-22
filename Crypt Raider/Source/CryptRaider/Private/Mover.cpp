// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Mover ctor "));

}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();
	OriginalRotation = GetOwner()->GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("Mover begin "));

}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Move(DeltaTime);
}

void UMover::SetShouldOpen(bool bShouldOpen)
{
	ShouldOpen = bShouldOpen;
}


void UMover::Move(float DeltaTime) const
{
	FVector TargetLocation = OriginalLocation;
	FRotator TargetRotation = OriginalRotation;
	const FVector ActorLocation = GetOwner()->GetActorLocation();
	const FRotator ActorRotation = GetOwner()->GetActorRotation();

	if (ShouldOpen)
	{
		TargetLocation = OriginalLocation + MoveOffset;
		TargetRotation = OriginalRotation + RotationOffset;
	}

	const FVector NewLocation = FMath::VInterpConstantTo(ActorLocation, TargetLocation, DeltaTime, MoveSpeed);
	GetOwner()->SetActorLocation(NewLocation);

	const FRotator NewRotation = FMath::RInterpConstantTo(ActorRotation, TargetRotation, DeltaTime, RotationSpeed);
	GetOwner()->SetActorRotation(NewRotation);
}
