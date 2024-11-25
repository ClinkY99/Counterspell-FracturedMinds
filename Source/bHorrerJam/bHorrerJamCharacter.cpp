// Copyright Epic Games, Inc. All Rights Reserved.

#include "bHorrerJamCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Interactables/Tape.h"
#include "Kismet/GameplayStatics.h"
#include "Interactables/DoorKey.h"
#include "Interactables/Tape.h"
#include "bHorrerJam.h"
#include "Eyes.h"
#include "Interactables/Door.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AbHorrerJamCharacter

AbHorrerJamCharacter::AbHorrerJamCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetMesh(), "head");
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	PrimaryActorTick.bCanEverTick = true;

}

void AbHorrerJamCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

	isSprinting = false;

	currentStamina = maxStamina;

	checkpointRespawnData = GetActorTransform();

	dayNum = 0;
}

void AbHorrerJamCharacter::Tick(float delta)
{
	FHitResult Hit;

	FVector startLoc;

	FVector endLoc;

	startLoc = FirstPersonCameraComponent->GetComponentLocation();

	endLoc = startLoc + (FirstPersonCameraComponent->GetForwardVector() * interactRange);

	GetWorld()->LineTraceSingleByChannel(Hit, startLoc, endLoc, ECC_EngineTraceChannel1);

	if (Hit.GetActor()) {
		if (IInteractInterface* interactable = Cast<IInteractInterface>(Hit.GetActor())) {
			if (interactable != hoveredActor && hoveredActor) {
				hoveredActor->hover(false);
			}
			interactable->hover(true);
			hoveredActor = interactable;
		}
		else {
			hoveredActor->hover(false);

			hoveredActor = nullptr;
		}
	}
	else {
		if (hoveredActor) {
			hoveredActor->hover(false);
			hoveredActor = nullptr;
		}
	}

	tickBP();
}


//////////////////////////////////////////////////////////////////////////// Input

void AbHorrerJamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AbHorrerJamCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AbHorrerJamCharacter::Look);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AbHorrerJamCharacter::startSprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AbHorrerJamCharacter::stopSprinting);

		//Interaction
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AbHorrerJamCharacter::interact);

		//Flashlight
		EnhancedInputComponent->BindAction(toggleFlashlightAction, ETriggerEvent::Triggered, this, &AbHorrerJamCharacter::toggleFlashlight);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AbHorrerJamCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AbHorrerJamCharacter::staminaAdjust()
{
	if (isSprinting) {
		currentStamina--;
		if (currentStamina <= 0) {
			stopSprinting();
		}
	}
	else {
		if (currentStamina < maxStamina) {
			currentStamina++;
		}
	}
}

void AbHorrerJamCharacter::startSprinting()
{
	if (currentStamina > 0) {
		isSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
		GetWorldTimerManager().SetTimer(StaminaTimer, this, &AbHorrerJamCharacter::staminaAdjust, 0.5f, true);
	}
}

void AbHorrerJamCharacter::stopSprinting()
{
	isSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	GetWorldTimerManager().SetTimer(StaminaTimer, this, &AbHorrerJamCharacter::staminaAdjust, 1.0f, true);
}



void AbHorrerJamCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AbHorrerJamCharacter::interact(const FInputActionValue& Value)
{
	if (hoveredActor) {
		hoveredActor->interact(this);
	}
}

void AbHorrerJamCharacter::pickUpItem(FItemStruct itemData)
{
	pickUpUI(itemData);
}

void AbHorrerJamCharacter::addKey(FKeyDataStruct key)
{
	playSound(0);
	Keys.Add(key);;
}

bool AbHorrerJamCharacter::pickUpTape(ATape* tape)
{
	if (!heldTape) {
		heldTape = tape;
		playSound(1);
		return true;
	}
	else {
		return false;
	}
}

void AbHorrerJamCharacter::useTape()
{
	heldTape->Destroy();
	heldTape = nullptr;
}

void AbHorrerJamCharacter::ovelappedCheckpoint()
{
	checkpointRespawnData = GetActorTransform();
	
	KeysSaved = Keys;
}

void AbHorrerJamCharacter::death()
{
	if (dayNum < 4) {
		bIsDying = true;
		//ShowDeathScreen
		dayNum++;
		showDeathUI();
	}
	else {
		bIsDying = true;
		showBadEnding();
	}
	

	//SetActorTransform(checkpointRespawnData, false, nullptr, ETeleportType::ResetPhysics);

	//TArray<AActor*> actors;

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorKey::StaticClass(), actors);

	//TArray<int32> keyInts;

	//for (auto& key : KeysSaved) {
	//	keyInts.Add(key.DoorID);
	//}

	//for (auto& key : actors) {
	//	ADoorKey* keyRef = Cast<ADoorKey>(key);
	//	if (!keyInts.Contains(keyRef->keyData.DoorID)) {
	//		keyRef->respawn();
	//	}
	//}

	//Keys = KeysSaved;

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATape::StaticClass(), actors);

	//for (auto& tape : actors) {
	//	ATape* tapeRef = Cast<ATape>(tape);
	//	tapeRef->respawn();
	//}

	//heldTape = nullptr;

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoor::StaticClass(), actors);

	//for (auto& door : actors) {
	//	ADoor* doorRef = Cast<ADoor>(door);

	//	doorRef->closeDoor();
	//}


}



