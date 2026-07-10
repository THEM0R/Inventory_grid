// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"


class UCanvasPanel;
class UBorder;
class UBackgroundBlur;
class AFPS_InventoryCharacter;
class AItemBase;

/**
 * 
 */

UCLASS()
class FPS_INVENTORY_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UCanvasPanel* Canvas;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UBorder* BackgroundBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "UI")
	UBackgroundBlur* Blur;

	AItemBase* SpawnedItem;
	
protected:

	AFPS_InventoryCharacter* CharacterReference;

	// ця функція стартує разом з створення віджета
	virtual void NativeConstruct() override;


	// Блокує мишку
	virtual FReply NativeOnMouseButtonDown(
		const FGeometry& InGeometry, 
		const FPointerEvent& InMouseEvent
	);

	virtual bool NativeOnDrop(
		const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		// const UDragDropOperation* InOperation, 5.8 - UDragDropOperation* InOperation,
		UDragDropOperation* InOperation
	) override;

};
