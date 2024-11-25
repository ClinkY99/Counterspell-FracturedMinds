// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/InteractInterface.h"
#include "../bHorrerJam.h"
#include "Item.generated.h"

UCLASS()
class AItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemData, meta = (ExposeOnSpawn = "true", AllowPrivateAccess = "true", OverrideName = "ItemData"))
	FItemStruct ItemData;

	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void interact(class AbHorrerJamCharacter* character) override;

	virtual void hover(bool isHovered) override;

	void respawn();

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() { return mesh; };


};
