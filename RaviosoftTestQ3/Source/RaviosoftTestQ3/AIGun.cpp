// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGun.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SPawn.h"

AAIGun::AAIGun()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

void AAIGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO Rotate Turret
	// TODO Check If In Range , Then Shoot

	//GetWorld()->GetAllActorsOfClass<ASPawn>()
}

void AAIGun::Fire()
{

}