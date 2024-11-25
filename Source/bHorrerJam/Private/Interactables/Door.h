// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractInterface.h"
#include "../bHorrerJamCharacter.h"
#include "Door.generated.h"

UCLASS()
class ADoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* rotationPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = keys, meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true", OverrideName = "isLocked"))
	bool bIsLocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = keys, meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true", OverrideName = "doorID"))
	int32 doorID;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOpen;

public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void openDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void playSound(int ID);
public:
	UFUNCTION(BlueprintImplementableEvent)
	void closeDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void interact(AbHorrerJamCharacter* character) override;

	virtual void hover(bool isHovered) override;

};
