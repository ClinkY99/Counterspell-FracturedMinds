// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "bHorrerJam.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemImage;
}; 

USTRUCT(BlueprintType)
struct FKeyDataStruct {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DoorID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsMaster = false;
};


USTRUCT(BlueprintType)
struct FTapeDataStruct {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundCue* TapeSoundAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 tapeID;
};