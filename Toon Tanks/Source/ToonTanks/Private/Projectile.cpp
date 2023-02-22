// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComponent->MaxSpeed = 1300;
	MovementComponent->InitialSpeed = 1000;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	ParticleSystemComponent->SetupAttachment(RootComponent);


	DamageType = UDamageType::StaticClass();
}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));

	const AActor* MyOwner = GetOwner();
	const APawn* MyInstigator = GetInstigator();
	if (!IsValid(MyOwner) || !IsValid(MyInstigator))
	{
		UE_LOG(LogTemp, Warning, TEXT("MyOwner Not Valid"));
		Destroy();
		return;
	}

	const auto InstigatorController = MyInstigator->GetController();

	if (OtherActor && OtherActor != MyOwner && InstigatorController)
	{
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, InstigatorController, this, DamageType);
	}

	if (HitParticles)
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());

	if (HitSound)
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	
	if (HitCameraShakeClass)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);

	Destroy();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), 1, 0.5);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
