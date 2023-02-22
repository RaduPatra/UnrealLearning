// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "CollisionDebugDrawingPublic.h"
#include "ToolBuilderUtil.h"
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhysicsHandle is NULL!!"));
	}
}


bool UGrabber::GetGrabbableActorSweep(FHitResult& OutHitResult)
{
	const FVector StartLocation = GetComponentLocation();
	const FVector EndLocation = StartLocation + GetForwardVector() * SweepLength;
	const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(TraceSphereRadius);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red);
	DrawDebugSphere(GetWorld(), EndLocation, 10, 10, FColor::Blue, false, 5);

	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		CollisionShape
	);
}

void UGrabber::Grab()
{
	if (!PhysicsHandle) return;
	FHitResult HitResult;
	bool bActorHit = GetGrabbableActorSweep(HitResult);
	if (bActorHit)
	{
		FString ActorName = HitResult.GetActor()->GetName();
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Yellow, false, 5);
		UE_LOG(LogTemp, Warning, TEXT("Found Grabbable: %s"), *ActorName);


		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitResult.GetActor()->Tags.Add(GrabbedTagName);
		HitComponent->SetSimulatePhysics(true);

		HitComponent->WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			HitComponent->GetComponentRotation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Actor"));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Released"));
	UPrimitiveComponent* GrabbedComp = PhysicsHandle->GetGrabbedComponent();
	if (!PhysicsHandle || !GrabbedComp) return;
	AActor* GrabbedActor = GrabbedComp->GetOwner();
	GrabbedActor->Tags.Remove(GrabbedTagName);
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle || !PhysicsHandle->GetGrabbedComponent()) return;

	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
}
