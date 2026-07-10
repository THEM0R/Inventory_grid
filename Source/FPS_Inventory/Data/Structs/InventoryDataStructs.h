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


USTRUCT()
struct FMousePositionInTile {

	GENERATED_USTRUCT_BODY();

	FMousePositionInTile() {

	};

	bool Right;
	bool Down;
};

class FPS_INVENTORY_API InventoryDataStructs
{
public:

};
