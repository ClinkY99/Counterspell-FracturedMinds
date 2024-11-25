// Fill out your copyright notice in the Description page of Project Settings.


#include "Eyes.h"

// Sets default values
AEyes::AEyes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("mesh"));
	mesh->SetupAttachment(RootComponent);

	mesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel2, ECR_Block);
}

// Called when the game starts or when spawned
void AEyes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEyes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

