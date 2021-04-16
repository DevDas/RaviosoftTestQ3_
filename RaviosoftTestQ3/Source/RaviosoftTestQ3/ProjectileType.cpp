// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileType.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileType::AProjectileType()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachTo(CollisionComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
}

// Called when the game starts or when spawned
void AProjectileType::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileType::OnHit);
}

// Called every frame
void AProjectileType::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileType::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if (OtherActor && (OtherActor != this) && OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	}
	
	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		150.f, 
		UDamageType::StaticClass(),
		TArray<AActor*>() // damage all actor thats why its empty
	);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactBlast, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundCueClass, GetActorLocation());
	
	Destroy();
}