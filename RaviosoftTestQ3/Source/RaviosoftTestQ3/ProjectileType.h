// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileType.generated.h"

UCLASS()
class RAVIOSOFTTESTQ3_API AProjectileType : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UProjectileMovementComponent* ProjectileMovementComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ProjectileDamage = 20.f;

	UPROPERTY(EditAnywhere, Category = "FX")
		class UParticleSystem* ImpactBlast = nullptr;

	UPROPERTY(EditAnywhere, Category = "FX")
	class USoundBase* SoundCueClass;

};
