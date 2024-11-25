// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Door.h"

// Sets default values
ADoor::ADoor()
{
	rotationPoint = CreateDefaultSubobject<USceneComponent>("RotationPoint");
	rotationPoint->SetupAttachment(RootComponent);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(rotationPoint);

	mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECR_Block);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::interact(AbHorrerJamCharacter* character)
{
	if (!bIsOpen) {
		if (!bIsLocked) {
			openDoor();
		}
		else {
			for (auto& key : character->Keys) {
				if (key.DoorID == doorID || key.bIsMaster) {
					openDoor();

					break;
				}
			}
			if (!bIsOpen) {
				playSound(0);
			}
		}
	}
	else {
		closeDoor();
	}
}

void ADoor::hover(bool isHovered)
{
	mesh->SetRenderCustomDepth(isHovered);
}

