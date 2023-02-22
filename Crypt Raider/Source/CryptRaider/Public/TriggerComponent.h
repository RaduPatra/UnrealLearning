// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover * NewMover);

private:
	UPrimitiveComponent* GetAcceptableComp() const;
	bool IsPlacedActorBeingGrabbed() const;
	void SnapPlacedActor(float DeltaTime) const;

	UPROPERTY(EditAnywhere)
	FName UnlockTagName;

	UPROPERTY( EditInstanceOnly, meta = ( UseComponentPicker, AllowedClasses="SceneComponent"))
	FComponentReference PlaceLocationRef;

	UPROPERTY(EditAnywhere)
	float PlaceSpeed = 400;
	
	UPROPERTY()
	USceneComponent * PlaceLocation;
	
	UPROPERTY()
	AActor * PlacedActor;

	UPROPERTY()
	UMover * Mover;
	
	//todo - replace with gameplay tags
	FName GrabbedTagName = "Grabbed";
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool
	                    bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);
};
