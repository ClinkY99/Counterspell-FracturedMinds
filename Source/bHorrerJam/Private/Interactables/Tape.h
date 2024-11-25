// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Item.h"
#include "Tape.generated.h"

/**
 * 
 */
UCLASS()
class ATape : public AItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
	USceneComponent* HoldPoint;

public:
	ATape();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = tapeData, meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true", OverrideName = "tapeData"))
	FTapeDataStruct tapeData;

public:
	virtual void interact(AbHorrerJamCharacter* character) override;

};
