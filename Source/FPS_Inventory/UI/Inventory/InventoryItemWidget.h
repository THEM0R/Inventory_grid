// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemWidget.generated.h"


class UCanvasPanel;
class USizeBox;
class UBorder;
class UImage;
class AFPS_InventoryCharacter;
/**
 * 
 */
UCLASS()
class FPS_INVENTORY_API UInventoryItemWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* Canvas;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	USizeBox* BackgroundSizeBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UBorder* BackgroundBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UImage* ItemImage;

	AFPS_InventoryCharacter* CharacterReference;

	FVector2D Size;

	virtual void NativeConstruct() override;

	void Refresh(AActor* ItemToAdd);

	virtual void NativeOnMouseEnter(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	);

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperator
	) override;

	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent
	) override;
};
