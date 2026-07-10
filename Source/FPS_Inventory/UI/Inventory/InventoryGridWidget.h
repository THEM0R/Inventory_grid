// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// import
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Data/Structs/InventoryDataStructs.h"
// engine import
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryGridWidget.generated.h"

class UCanvasPanel;
class UBorder;
class AFPS_InventoryCharacter;
class UInventoryComponent;
class AItemBase;
/**
 * 
 */
UCLASS()
class FPS_INVENTORY_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* Canvas;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UBorder* GridBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* GridCanvasPanel;

	AFPS_InventoryCharacter* CharacterReference;
	UInventoryComponent* InventoryComponent;

	UPanelSlot* PanelSlot;

	int32 Columns;

	int32 Rows;

	float TileSize;

	TArray<float> StartX;
	TArray<float> StartY;
	TArray<float> EndX;
	TArray<float> EndY;

	FLines* LineStructData;

	virtual void NativeConstruct() override;

	void CreateLineSegments();

	virtual int32 NativePaint(
		const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerID,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override;

	virtual bool NativeOnDrop(
		const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		// const UDragDropOperation* InOperation, 5.8 - UDragDropOperation* InOperation,
		UDragDropOperation* InOperation
	) override;
	// будем діставати верхню ліву плитку
	bool NativeOnDragOver(
		const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		// const UDragDropOperation* InOperation, 5.8 - UDragDropOperation* InOperation,
		UDragDropOperation* InOperation
	) override;

	bool IsRoomAvailableForPayLoad(AItemBase* Item) const;

	FMousePositionInTile MousePositionInTile;
	// функця шоб визначити позицію мошки куди класти ітем
	FMousePositionInTile FMousePositionInTileResult(FVector2D(MousePosition));

	FReply NativeOnPreviewKeyDown(
		const FGeometry& InGeometry,
		const FKeyEvent& InKeyEvent
	) override;

	void NativeOnDragEnter(
		const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation
	) override;

	void NativeOnDragLeave(
		const FDragDropEvent& InMouseEvent,
		UDragDropOperation* InOperation
	) override;

	// Функція для малювання зеленого фону куди підійде ітем
	void DrawBackgroundBox(
		AItemBase* Item,
		FLinearColor MyTintColor,
		const FGeometry& AllottedGeometry,
		FVector2D TopLeftCorner,
		FSlateWindowElementList& OutDrawElements,
		int32 LayedId
	) const;

	UDragDropOperation* StorredDragDropOperation;

	AItemBase* DraggedItem;

	FIntPoint DraggedItemTopLeftIndex;

	bool DrawDropLocation;

public:

	// функція оновлення віджета інвентаря
	void Refresh();

	AItemBase* DroppedItem;

	bool Dropped = false;
};
