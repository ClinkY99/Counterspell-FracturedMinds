// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/DoorKey.h"
#include "../bHorrerJamCharacter.h"


void ADoorKey::interact(AbHorrerJamCharacter* character)
{
	character->addKey(keyData);
	Super::interact(character);

}
