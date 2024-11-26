// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Item.h"
#include "Components/BoxComponent.h"
#include "DoorKey.generated.h"

/**
 * 
 */
UCLASS()
class ADoorKey : public AItem
{
	GENERATED_BODY()



public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Hit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemData, meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true", OverrideName = "KeyData"))
	FKeyDataStruct keyData;

public:
	ADoorKey();

public:
	virtual void interact(AbHorrerJamCharacter* character) override;
	
};
