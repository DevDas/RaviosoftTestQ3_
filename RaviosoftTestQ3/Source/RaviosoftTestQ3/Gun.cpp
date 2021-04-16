// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RaviosoftTestQ3/RaviosoftTestQ3.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->AttachTo(CollisionComp);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Shoot()
{
	switch (ShootType)
	{
	case LineTrace : ShootWithLineTrace();
		break;
	case Projectile : ShootWithProjectile();
		break;
	}
}

void AGun::ShootWithLineTrace()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation); // Changed Character

		FVector ShotDirection = EyeRotation.Vector();

		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true; // Trace Against Each Indivisual Triangle Of The Mesh, We're Hitting

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_GUN, QueryParams)) // From Pawn_BP->Camera->EyeHeight/ Changed It
		{
			// Blocking Hit Process Damage
			AActor* HitActor = Hit.GetActor();

			// Applying Damage
			UGameplayStatics::ApplyPointDamage(
				HitActor,
				ActualDamage,
				ShotDirection,
				Hit,
				MyOwner->GetInstigatorController(),
				MyOwner,
				DamageType);
		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.f, 0, 1.0f);
	}
}

void AGun::ShootWithProjectile()
{

}