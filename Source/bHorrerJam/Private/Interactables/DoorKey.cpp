// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/DoorKey.h"
#include "../bHorrerJamCharacter.h"


ADoorKey::ADoorKey()
{
	Hit = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	Hit->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECR_Block);
	Hit->SetupAttachment(GetMesh());
}

void ADoorKey::interact(AbHorrerJamCharacter* character)
{
	character->addKey(keyData);
	Super::interact(character);

}
