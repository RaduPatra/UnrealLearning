// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void SetShouldOpen(bool bShouldOpen);

private:
	void Move(float DeltaTime) const;

	UPROPERTY(EditAnywhere)
	FVector MoveOffset = FVector(100, 0, 0);

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 40;

	UPROPERTY(EditAnywhere)
	bool ShouldOpen = false;

	UPROPERTY(EditAnywhere)
	FRotator RotationOffset = FRotator(0, 0, 90);

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 40;

	
	FVector OriginalLocation;
	
	FRotator OriginalRotation;
	
	float ElapsedTime = 0;
	
	

};
