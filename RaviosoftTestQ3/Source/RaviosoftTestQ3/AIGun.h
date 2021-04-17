// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIGun.generated.h"

UCLASS()
class RAVIOSOFTTESTQ3_API AAIGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIGun();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* TurretPipe;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

	UPROPERTY(EditAnywhere)
		float AIRange = 1000.f;

	bool bCanFire = true;

	UPROPERTY(EditAnywhere)
		UClass* ProjectileBlueprint;

	FTimerHandle Handle_Fire;

	void ClearTimer();

	UPROPERTY(BlueprintReadOnly)
	bool bGameOver = false;
		
	UFUNCTION(BlueprintCallable)
		float GetPercentage();
};
