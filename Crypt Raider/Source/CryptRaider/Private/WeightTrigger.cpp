// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightTrigger.h"


// Sets default values for this component's properties
UWeightTrigger::UWeightTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWeightTrigger::SetMover(UMover* NewMover)
{
	Mover = NewMover;
}


// Called when the game starts
void UWeightTrigger::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UWeightTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TArray<UPrimitiveComponent*> AcceptableComp = GetAcceptableComponents();
	bool bShouldOpen = false;
	if (AcceptableComp.Num())
	{
		float Weight = 0;
		for (const auto Comp : AcceptableComp)
		{
			Weight += Comp->GetMass();
			UE_LOG(LogTemp, Warning, TEXT("GetMass %f"), Weight);

			if (Weight == AcceptableWeight)
			{
				bShouldOpen = true;
			}
			// Comp->SetSimulatePhysics(false);
		}
	}
	Mover->SetShouldOpen(bShouldOpen);
}


TArray<UPrimitiveComponent*> UWeightTrigger::GetAcceptableComponents() const
{
	TArray<UPrimitiveComponent*> OverlapComponents;
	TArray<UPrimitiveComponent*> AcceptableComponents;
	GetOverlappingComponents(OverlapComponents);

	for (const auto Comp : OverlapComponents)
	{
		const AActor* Actor = Comp->GetOwner();
		if (!Actor->ActorHasTag(GrabbedTagName) && Actor->ActorHasTag(WeightTagName))
		{
			AcceptableComponents.Add(Comp);
		}
	}
	return AcceptableComponents;
}
