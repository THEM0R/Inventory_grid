// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Inventory/InventoryComponent.h"
#include "Item/ItemBase.h"
#include "Ui/Inventory/InventoryGridWidget.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Success"));
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (AddedItem) {
		InventoryGridWidgetReference->Refresh();
		AddedItem = false;
	}
}

bool UInventoryComponent::TryAddItem(AItemBase* ItemToAdd)
{
	if (ItemToAdd) {
		for (int32 i = 0; i < Items.Num(); i++) {

			if (isRoomAvailable(ItemToAdd, i)) {

				AddItemAt(ItemToAdd, i);
				return true;
			}
		}
		return false;
	}
	return false;

}

bool UInventoryComponent::isRoomAvailable(AItemBase* ItemToAdd, int32 TopLeftIndex)
{
	FIntPoint Dimensions = ItemToAdd->GetDimensions();
	FIntPoint Tile = IndexToTile(TopLeftIndex);

	// по горизонталі
	for (int32 i = Tile.X; i <= Tile.X + Dimensions.X - 1; i++) {
		// по вертикалі
		for (int32 j = Tile.Y; j <= Tile.Y + Dimensions.Y - 1; j++) {
			if (IsTileValid(FIntPoint(i, j))) {
				int32 Index = TileToIndex(FIntPoint(i, j));
				if (GetResultAtIndex(Index)) {
					if(GetItemAtIndex(Index)){
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}
	return true;
}

FIntPoint UInventoryComponent::IndexToTile(int32 Index)
{
	return FIntPoint(Index % Columns, Index / Columns);
}

bool UInventoryComponent::IsTileValid(FIntPoint Tile)
{
	if (Tile.X >= 0 && Tile.Y >= 0 && Tile.X < Columns && Tile.Y < Rows) {
		return true;
	}
	return false;
}

int32 UInventoryComponent::TileToIndex(FIntPoint Tile)
{
	int32 Index = Tile.X + Tile.Y * Columns;

	return Index;
}

float UInventoryComponent::GetResultAtIndex(int32 Index)
{
	if (Items.IsValidIndex(Index)) {
		return true;
	}
	return false;
}

AItemBase* UInventoryComponent::GetItemAtIndex(int32 Index)
{
	if (Items.IsValidIndex(Index)) {
		return Items[Index];
	}
	return nullptr;
}

void UInventoryComponent::AddItemAt(AItemBase* ItemToAdd, int32 TopLeftIndex)
{
	FIntPoint Dimensions = ItemToAdd->GetDimensions();
	FIntPoint Tile = IndexToTile(TopLeftIndex);

	// по горизонталі
	for (int32 i = Tile.X; i <= Tile.X + Dimensions.X - 1; i++) {
		// по вертикалі
		for (int32 j = Tile.Y; j <= Tile.Y + Dimensions.Y - 1; j++) {

			Items[TileToIndex(FIntPoint(i, j))] = ItemToAdd;
		}
	}

	AddedItem = true;
}
// 35.59

TMap<AItemBase*, FIntPoint> UInventoryComponent::GetAllItems() 
{
	for (int32 i = 0; i < Items.Num(); i++) 
	{
		if (Items[i]) {

			if (!AllItems.Contains(Items[i])) {
				AllItems.Add(Items[i],IndexToTile(i));
			}
		}
	}
	return AllItems;
}

void UInventoryComponent::SetInventoryGridWidget(UInventoryGridWidget* GridWidgetReference)
{
	InventoryGridWidgetReference = GridWidgetReference;
}

void UInventoryComponent::RemoveItem(AItemBase* ItemToRemove)
{
	if (ItemToRemove) {
		for (int32 i = 0; i < Items.Num(); i++)
		{
			if (Items[i] == ItemToRemove) {
				Items[i] == nullptr;
			}
		}
	}
}

