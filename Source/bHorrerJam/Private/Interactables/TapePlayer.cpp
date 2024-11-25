// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/TapePlayer.h"
#include "../bHorrerJamCharacter.h"

// Sets default values
ATapePlayer::ATapePlayer()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(RootComponent);
	mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECR_Block);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATapePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATapePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATapePlayer::interact(AbHorrerJamCharacter* character)
{
	if (character->heldTape && !bIsPlaying) {
		playTape(character->heldTape->tapeData);
		character->useTape();
	}
}

void ATapePlayer::hover(bool isHovered)
{
	mesh->SetRenderCustomDepth(isHovered);
}

