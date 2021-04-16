// Fill out your copyright notice in the Description page of Project Settings.

#include "SPawn.h"
#include "HealthComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Gun.h"

// Sets default values
ASPawn::ASPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->bUsePawnControlRotation = true;

	GunAttachPoint = CreateDefaultSubobject<UCameraComponent>(TEXT("GunAttachPoint"));
	GunAttachPoint->SetupAttachment(GetCapsuleComponent());

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
}

void ASPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region PlayerInput

static void BindPawnInputs()
{
	static bool bindingsAdded = false;

	if (bindingsAdded == false)
	{
		bindingsAdded = true;

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("Turn", EKeys::MouseX, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("LookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveForward", EKeys::S, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("MoveRight", EKeys::D, 1.f));


		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Jump", EKeys::SpaceBar));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Shoot", EKeys::LeftMouseButton));

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("Use", EKeys::F));
	}
}

void ASPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent != nullptr);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	BindPawnInputs();

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPawn::MoveRight);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASPawn::Jump);
	PlayerInputComponent->BindAction("Use", EInputEvent::IE_Pressed, this, &ASPawn::Use);
	PlayerInputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &ASPawn::Shoot);
}

#pragma endregion PlayerInput

void ASPawn::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector() * Val);
}

void ASPawn::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector() * Val);
}

FVector ASPawn::GetPawnViewLocation() const
{
	if (CameraComponent)
	{
		return CameraComponent->GetComponentLocation();
	}
	else
	{
		return Super::GetPawnViewLocation(); // If SomeHow Fails Then Return The Original State
	}
}

void ASPawn::Use()
{

}

void ASPawn::Shoot()
{
	if (CurrentGun)
	{
		CurrentGun->Shoot();
	}
}