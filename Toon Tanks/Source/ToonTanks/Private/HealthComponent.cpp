// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealthComponent::SetHealth(const float Health)
{
	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health Depleeted"));
		OnHealthDepleted.Broadcast();
	}
	else
	{
		CurrentHealth = Health;
	}
}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                    AController* Instigator, AActor* DamageCauser)
{
	const auto NewHealth = CurrentHealth - Damage;
	SetHealth(NewHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), NewHealth);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
	// ...
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
