// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPawn.generated.h"

UCLASS()
class RAVIOSOFTTESTQ3_API ASPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* GunAttachPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UCameraComponent* CameraComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

	class AGun* CurrentGun = nullptr;
	class AGun* CurrentNearbyGun = nullptr;

	void DisableCollision(AGun* GunRef);
	void EnableCollision(AGun* GunRef);


private:

	void MoveForward(float Val);
	void MoveRight(float Value);

	void Use();
	void Shoot();
};
