// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGun.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SPawn.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileType.h"

AAIGun::AAIGun()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	TurretPipe = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretPipe"));
	TurretPipe->AttachToComponent(TurretMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

void AAIGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO Check If In Range , Then Shoot

	if (bGameOver) return;

	if (HealthComp && GetPercentage() > 0.f)
	{
		ASPawn* PlayerPawn = Cast<ASPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

		if (PlayerPawn)
		{
			if (PlayerPawn->GetPercentage() <= 0.f) // Don't Fire If Player Already Died
			{
				bGameOver = true;
				ClearTimer();
				bCanFire = false;
				return;
			}

			if ((PlayerPawn->GetActorLocation() - GetActorLocation()).Size() <= AIRange)
			{
				FRotator Rotation = (PlayerPawn->GetActorLocation() - GetActorLocation()).Rotation();
				if (TurretMesh)
				{
					TurretMesh->SetWorldRotation(Rotation);
				}
				
				if (bCanFire)
				{
					bCanFire = false;
					GetWorld()->GetTimerManager().SetTimer(Handle_Fire, this, &AAIGun::Fire, 2.f, true);
				}
			}
			else
			{
				ClearTimer();
			}
		}
	}
	else
	{
		ClearTimer();
	}
}

void AAIGun::Fire()
{
	AProjectileType* ProjectileType = GetWorld()->SpawnActor<AProjectileType>(ProjectileBlueprint, TurretPipe->GetSocketLocation(FName("Projectile")), TurretPipe->GetSocketRotation(FName("Projectile")));
	if (ProjectileType)
	{
		ProjectileType->SetOwner(this);
	}
}

void AAIGun::ClearTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(Handle_Fire))
	{
		GetWorld()->GetTimerManager().ClearTimer(Handle_Fire);
		bCanFire = true;
	}
}

float AAIGun::GetPercentage()
{
	return HealthComp->GetPercentage();
};