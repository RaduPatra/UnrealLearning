// Fill out your copyright notice in the Description page of Project Settings.


#include "TestModuleActor.h"

// Sets default values
ATestModuleActor::ATestModuleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestModuleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestModuleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

