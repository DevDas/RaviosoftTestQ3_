// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UENUM(BlueprintType)
enum EShootType
{
	LineTrace,

	Projectile
};

UCLASS()
class RAVIOSOFTTESTQ3_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void Shoot();

	void ShootWithLineTrace();
	void ShootWithProjectile();
	void ResetNearbyGun();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* CollisionComp;

	// Because I Have Only This Skeletal Asset
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
		TEnumAsByte<EShootType> ShootType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
		float ActualDamage = 20.f;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<class UDamageType> DamageType;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	class ASPawn* Pawn = nullptr;

	UPROPERTY(EditAnywhere)
		UClass* ProjectileBlueprint;

	FVector TraceEndProjectile;

	UPROPERTY(EditAnywhere, Category = "FX")
		class UParticleSystem* ImpactBlast = nullptr;

	UPROPERTY(EditAnywhere, Category = "FX")
		class USoundBase* SoundCueClass;

	UPROPERTY(EditAnywhere, Category = "FX")
		class USoundBase* GSoundCueClass;
};
