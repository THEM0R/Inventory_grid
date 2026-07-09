// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InventoryDataStructs.generated.h"

/**
 * 
 */

USTRUCT()
struct FLines {

	GENERATED_USTRUCT_BODY();

	FLines() {

	};

	TArray<FVector2D> XLines;
	TArray<FVector2D> YLines;
};

class FPS_INVENTORY_API InventoryDataStructs
{
public:

};
