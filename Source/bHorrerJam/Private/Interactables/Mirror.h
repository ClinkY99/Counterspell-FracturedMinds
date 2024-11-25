// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Item.h"
#include "Mirror.generated.h"

/**
 * 
 */
UCLASS()
class AMirror : public AItem
{
	GENERATED_BODY()
	
public:
	virtual void interact(AbHorrerJamCharacter* character) override;

	UFUNCTION(BlueprintImplementableEvent)
	void Interacted();
	
};
