// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mover.h"
#include "Components/BoxComponent.h"
#include "WeightTrigger.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRYPTRAIDER_API UWeightTrigger : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeightTrigger();
	
	UFUNCTION(BlueprintCallable)
	void SetMover(UMover * NewMover);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	TArray<UPrimitiveComponent*> GetAcceptableComponents() const;

private:
	UPROPERTY(EditAnywhere)
	float AcceptableWeight = 10;

	UPROPERTY()
	UMover * Mover;

	//todo - replace with gameplay tags
	FName GrabbedTagName = "Grabbed";
	FName WeightTagName = "Weight";
};
