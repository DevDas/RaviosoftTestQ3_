// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGun.h"
#include "HealthComponent.h"

AAIGun::AAIGun()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

void AAIGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}