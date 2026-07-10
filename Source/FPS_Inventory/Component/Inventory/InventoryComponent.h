// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AItemBase;
class UInventoryGridWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UInventoryComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Columns;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 Rows;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float TileSize;

	bool AddedItem = false;

	UInventoryGridWidget* InventoryGridWidgetReference;

	TArray<AItemBase*> Items;

	bool TryAddItem(AItemBase* ItemToAdd);

	bool isRoomAvailable(AItemBase* ItemToAdd, int32 TopLeftIndex);

	FIntPoint IndexToTile(int32 Index);

	bool IsTileValid(FIntPoint Tile);

	int32 TileToIndex(FIntPoint Tile);

	float GetResultAtIndex(int32 Index);

	AItemBase* GetItemAtIndex(int32 Index);

	void AddItemAt(AItemBase* ItemToAdd, int32 TopLeftIndex);

	TMap<AItemBase*, FIntPoint> GetAllItems();

	void SetInventoryGridWidget(UInventoryGridWidget* InventoryGridWidgetReference);


	// функція видалення ітема з масиву
	void RemoveItem(AItemBase* ItemToRemove);

protected:

	// всі ітеми 2 числа одне масив друге ячейка
	TMap<AItemBase*, FIntPoint> AllItems;

	// Called when the game starts
	virtual void BeginPlay() override;

		
};
