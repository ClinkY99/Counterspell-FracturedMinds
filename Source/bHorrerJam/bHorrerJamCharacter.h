// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "bHorrerJam.h"
#include "Interfaces/InteractInterface.h"
#include "bHorrerJamCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ATape;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AbHorrerJamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Flashlight Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* toggleFlashlightAction;

	//Sprint Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = sprint, meta = (AllowPrivateAccess = "true"))
	int32 maxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = sprint, meta = (AllowPrivateAccess = "true"))
	float walkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = sprint, meta = (AllowPrivateAccess = "true"))
	float runSpeed;
	
	//Interact Variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = interact, meta = (AllowPrivateAccess = "true"))
	int32 interactRange;

public:
	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

private:
	bool isSprinting;

	int32 currentStamina;

	FTimerHandle StaminaTimer;

	IInteractInterface* hoveredActor;

	FTransform checkpointRespawnData;

	TArray<FKeyDataStruct> KeysSaved;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = respawn)
	bool bIsDying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = respawn)
	int dayNum;

	TArray<FKeyDataStruct> Keys;

	ATape* heldTape;

public:
	AbHorrerJamCharacter();

protected:
	virtual void BeginPlay();

public:
	virtual void Tick(float delta) override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for looking input */
	void interact(const FInputActionValue& Value);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void toggleFlashlight();

	UFUNCTION(BlueprintImplementableEvent)
	void tickBP();

	UFUNCTION(BlueprintImplementableEvent)
	void showDeathUI();

	UFUNCTION(BlueprintImplementableEvent)
	void showBadEnding();

	UFUNCTION(BlueprintImplementableEvent)
	void playSound(int soundID);

private:
	void staminaAdjust();
	void startSprinting();
	void stopSprinting();

public:
	void pickUpItem(FItemStruct itemData);
	void addKey(FKeyDataStruct key);
	bool pickUpTape(ATape* tape);
	void useTape();

	void ovelappedCheckpoint();


	UFUNCTION(BlueprintCallable)
	void death();
	

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void pickUpUI(FItemStruct itemData);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

