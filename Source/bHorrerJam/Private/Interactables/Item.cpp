// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Item.h"
#include "../bHorrerJamCharacter.h"

// Sets default values
AItem::AItem()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(RootComponent);
	mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECR_Block);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::interact(AbHorrerJamCharacter* character)
{
	character->pickUpItem(ItemData);
	mesh->SetVisibility(false);
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECR_Ignore);
}

void AItem::hover(bool isHovered)
{
	mesh->SetRenderCustomDepth(isHovered);
}

void AItem::respawn()
{
	mesh->SetVisibility(true);
	mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECR_Block);
}

