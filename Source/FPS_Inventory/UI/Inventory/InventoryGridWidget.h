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


};
