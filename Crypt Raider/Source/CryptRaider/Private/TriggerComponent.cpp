// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlaceLocation = Cast<USceneComponent>(PlaceLocationRef.GetComponent(GetOwner()));
	if (!PlaceLocation)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlaceLocation is NULL!!"));
	}
}


UPrimitiveComponent* UTriggerComponent::GetAcceptableComp() const
{
	TArray<UPrimitiveComponent*> OverlapComponents;
	GetOverlappingComponents(OverlapComponents);

	for (const auto Comp : OverlapComponents)
	{
		AActor* Actor = Comp->GetOwner();
		if (Actor->ActorHasTag(UnlockTagName) && !Actor->ActorHasTag(GrabbedTagName))
		{
			UE_LOG(LogTemp, Warning, TEXT("Has Right Tag"));
			return Comp;
		}
	}
	return nullptr;
}


bool UTriggerComponent::IsPlacedActorBeingGrabbed() const
{
	return PlacedActor && PlacedActor->ActorHasTag(GrabbedTagName);
}

void UTriggerComponent::SnapPlacedActor(float DeltaTime) const
{
	if (PlacedActor && PlaceLocation)
	{
		FVector InterpLocResult = FMath::VInterpConstantTo(PlacedActor->GetActorLocation(),
		                                                   PlaceLocation->GetComponentLocation(), DeltaTime,
		                                                   PlaceSpeed);

		FRotator InterpRotResult = FMath::RInterpConstantTo(PlacedActor->GetActorRotation(),
		                                                    PlaceLocation->GetComponentRotation(), DeltaTime,
		                                                    PlaceSpeed);

		PlacedActor->SetActorLocation(InterpLocResult);
		PlacedActor->SetActorRotation(InterpRotResult);
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SnapPlacedActor(DeltaTime);

	if (IsPlacedActorBeingGrabbed()) PlacedActor = nullptr;

	//don't search if an actor is already placed
	if (PlacedActor) return;

	if (UPrimitiveComponent* AcceptableComp = GetAcceptableComp())
	{
		AcceptableComp->SetSimulatePhysics(false);
		PlacedActor = AcceptableComp->GetOwner();
		Mover->SetShouldOpen(true);
	}
	else
	{
		Mover->SetShouldOpen(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}
#pragma region
void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
#pragma endregion
