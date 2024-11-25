// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Tape.h"
#include "../bHorrerJamCharacter.h"

ATape::ATape()
{
	HoldPoint = CreateDefaultSubobject<USceneComponent>("RotationPoint");
	HoldPoint->SetupAttachment(RootComponent);

	GetMesh()->SetupAttachment(HoldPoint);
}

void ATape::interact(AbHorrerJamCharacter* character)
{
	if (character->pickUpTape(this)) {
		Super::interact(character);
	}
}
