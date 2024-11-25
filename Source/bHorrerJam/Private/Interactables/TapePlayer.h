// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractInterface.h"
#include "../bHorrerJam.h"
#include "Tape.h"
#include "TapePlayer.generated.h"

UCLASS()
class ATapePlayer : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPlaying;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTapeDataStruct tapeBeingPlayed;
	
public:	
	// Sets default values for this actor's properties
	ATapePlayer();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void playTape(FTapeDataStruct tapeToPlay);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void interact(class AbHorrerJamCharacter* character) override;

	virtual void hover(bool isHovered) override;

};
