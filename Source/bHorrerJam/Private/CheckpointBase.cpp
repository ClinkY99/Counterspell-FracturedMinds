// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointBase.h"
#include "bHorrerJam/bHorrerJamCharacter.h"

// Sets default values
ACheckpointBase::ACheckpointBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	checkpointBounds = CreateDefaultSubobject<UBoxComponent>(FName("checkpointBounds"));
	checkpointBounds->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACheckpointBase::BeginPlay()
{
	Super::BeginPlay();

	checkpointBounds->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointBase::playerOverlap);
	
}

// Called every frame
void ACheckpointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointBase::playerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AbHorrerJamCharacter* characterRef = Cast<AbHorrerJamCharacter>(OtherActor)) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("CheckpointTouched"));
		characterRef->ovelappedCheckpoint();
	}
}

