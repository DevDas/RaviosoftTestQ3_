// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAVIOSOFTTESTQ3_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FOnDeath OnDeath;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
		float DefaultHealth = 100.f;

	bool bIsDead;

	float GetPercentage()
	{
		return (Health / DefaultHealth);
	};
};
