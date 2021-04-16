// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RaviosoftTestQ3/RaviosoftTestQ3.h"
#include "DrawDebugHelpers.h"
#include "SPawn.h"
#include "ProjectileType.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	RootComponent = GunMesh;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->AttachToComponent(GunMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGun::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AGun::OnOverlapEnd);
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
		TraceEndProjectile = TraceEnd;

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

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactBlast, TraceEnd);
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), SoundCueClass, GetActorLocation());
		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 10.f, 0, 1.0f);
	}
}

void AGun::ShootWithProjectile()
{
	FRotator Rotation = (GunMesh->GetSocketLocation(FName("Projectile")) - TraceEndProjectile).Rotation();
	AProjectileType* Projectile = GetWorld()->SpawnActor<AProjectileType>(
		ProjectileBlueprint,										
		GunMesh->GetSocketLocation(FName("Projectile")), Rotation
		/*GunMesh->GetSocketRotation(FName("Projectile"))*/
		);

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), GSoundCueClass, GetActorLocation());
}

void AGun::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASPawn* MyPawn{ Cast<ASPawn>(OtherActor) };
	if (MyPawn)
	{
		MyPawn->CurrentNearbyGun = this;
	}
}

void AGun::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Pawn = Cast<ASPawn>(OtherActor);
	if (Pawn)
	{
		FTimerHandle Handle_ResetNearbyGun;
		GetWorld()->GetTimerManager().SetTimer(Handle_ResetNearbyGun, this, &AGun::ResetNearbyGun, 0.5f, false);
	}
}

void AGun::ResetNearbyGun()
{
	if (Pawn)
	{
		Pawn->CurrentNearbyGun = nullptr;
	}
}