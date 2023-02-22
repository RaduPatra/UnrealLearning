// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool GetGrabbableActorSweep(FHitResult & OutHitResult);

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float SweepLength = 400;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;
	
	UPROPERTY(EditAnywhere)
	float TraceSphereRadius = 50;

	UPROPERTY()
	UPhysicsHandleComponent * PhysicsHandle;

	FName GrabbedTagName = "Grabbed"; //change this to gameplay tag later

private:
	
};
