// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryItemWidget.h"
#include "FPS_InventoryCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Item/ItemBase.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/CanvasPanelSlot.h"
#include "Component/Inventory/InventoryComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"



void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterReference = Cast<AFPS_InventoryCharacter>
		(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (CharacterReference) {
		Refresh(CharacterReference->ItemToAdd);
	}

}

void UInventoryItemWidget::Refresh(AActor* ItemToAdd)
{
	AItemBase* Item = Cast<AItemBase>(ItemToAdd);

	ItemImage->SetBrushFromMaterial(Item->GetIcon());

	Size = FVector2D(
		Item->GetDimensions().X * CharacterReference->InventoryComponent->TileSize,
		Item->GetDimensions().Y * CharacterReference->InventoryComponent->TileSize
	);

	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);


	UCanvasPanelSlot* ImageAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ItemImage);

	ImageAsCanvasSlot->SetSize(Size);
}
