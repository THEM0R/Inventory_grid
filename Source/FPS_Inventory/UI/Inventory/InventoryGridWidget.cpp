// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryGridWidget.h"
#include "FPS_InventoryCharacter.h"
#include "Component/Inventory/InventoryComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Item/ItemBase.h"
#include "Ui/Inventory/InventoryItemWidget.h"




void UInventoryGridWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
	CharacterReference = Cast<AFPS_InventoryCharacter>(GetOwningPlayerPawn());

	InventoryComponent = CharacterReference->InventoryComponent;

	if (!CharacterReference) return;


	bIsFocusable = true;

	Columns = InventoryComponent->Columns;
	Rows = InventoryComponent->Rows;
	TileSize = InventoryComponent->TileSize;

	float NewWidth = Columns * TileSize;
	float NewHeight = Rows * TileSize;

	LineStructData = new FLines();
	StartX = {};
	StartX = {};
	EndX = {};
	EndY = {};

	UCanvasPanelSlot* BorderAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	BorderAsCanvasSlot->SetSize(FVector2D(NewWidth, NewHeight));

	CreateLineSegments();

	InventoryComponent->SetInventoryGridWidget(this);
}

void UInventoryGridWidget::CreateLineSegments()
{
	for (int32 i = 0; i <= Columns; i++) {
		//float Х{ i * TileSize };
		float X = i * TileSize;

		LineStructData->XLines.Add(FVector2D(X, X));
		LineStructData->YLines.Add(FVector2D(0.0f, Rows * TileSize));

	}

	for (int32 i = 0; i <= Rows; i++) {
		//float Y{ i * TileSize };
		float Y = i * TileSize;

		LineStructData->YLines.Add(FVector2D(Y, Y));
		LineStructData->XLines.Add(FVector2D(0.0f, Columns * TileSize));

	}

	for (const FVector2D Elements : LineStructData->XLines) {
		/*GEngine->AddOnScreenDebugMessage(
			-1, 
			5.0f, 
			FColor::Red, 
			FString::Printf(TEXT("StartX: %.2f, EndX:%.2f"), 
			Elements.X, 
			Elements.Y
		));*/

		StartX.Add(Elements.X);
		EndX.Add(Elements.Y);

	}

	for (const FVector2D Elements : LineStructData->YLines) {
		/*GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Red,
			FString::Printf(TEXT("StartY: %.2f, EndY:%.2f"),
			Elements.X,
			Elements.Y
		));*/

		StartY.Add(Elements.X);
		EndY.Add(Elements.Y);
	}

	// part 2

}

int32 UInventoryGridWidget::NativePaint(
	const FPaintArgs& Args, 
	const FGeometry& AllottedGeometry, 
	const FSlateRect& MyCullingRect, 
	FSlateWindowElementList& OutDrawElements, 
	int32 LayerID, 
	const FWidgetStyle& InWidgetStyle, 
	bool bParentEnabled) const
{

	Super::NativePaint(
		Args, 
		AllottedGeometry, 
		MyCullingRect, 
		OutDrawElements, 
		LayerID, 
		InWidgetStyle, 
		bParentEnabled
	);


	FPaintContext PaintContext(
		AllottedGeometry,
		MyCullingRect,
		OutDrawElements,
		LayerID,
		InWidgetStyle,
		bParentEnabled
	);

	FLinearColor CustomColor(0.5f, 0.5f, 0.5f, 0.5f);


	// fix GridBorder mor
	if (!GridBorder)
	{
		return LayerID;
	}

	if (!LineStructData)
	{
		return LayerID;
	}

	FVector2D TopLeftCorner = GridBorder->GetCachedGeometry()
		.GetLocalPositionAtCoordinates(FVector2D(0.0f, 0.0f));

	int32 k = 0;

	for (int32 i = 0; i < LineStructData->XLines.Num(); i++) 
	{

		for (int32 j = 0; j < LineStructData->YLines.Num(); j++) 
		{
			k = i;
		}
		// функція яка малює лінію
		UWidgetBlueprintLibrary::DrawLine(
			PaintContext,
			FVector2D(StartX[i], StartY[k]) + TopLeftCorner,
			FVector2D(EndX[i], EndY[k]) + TopLeftCorner,
			CustomColor,
			false,
			2.0f
		);
	}

	if (DrawDropLocation) {
		AItemBase* Item = Cast<AItemBase>(DraggedPayLoad);

		if (IsRoomAvailableForPayLoad(Item))
		{
			DrawBackgroundBox(
				Item,
				FLinearColor( 0.0,1.0,0.0,0.25 ),
				AllottedGeometry,
				TopLeftCorner,
				OutDrawElements,
				LayerID
				);
		}
		else {
			DrawBackgroundBox(
				Item,
				FLinearColor(1.0, 0.0, 0.0, 0.25),
				AllottedGeometry,
				TopLeftCorner,
				OutDrawElements,
				LayerID
			);
		}
	}

	return int32();
}



void UInventoryGridWidget::Refresh() {

	TArray<AItemBase*> Keys;
	InventoryComponent->GetAllItems().GetKeys(Keys);

	if (CharacterReference->ItemWidgetClass) {
		CharacterReference->
			ItemWidget = CreateWidget(
				GetWorld(), 
				CharacterReference->ItemWidgetClass
			);

		for (AItemBase* AddedItem : Keys)
		{
			CharacterReference->
				ItemWidget->
				SetOwningPlayer(GetOwningPlayer());

			int32 X = InventoryComponent->
				GetAllItems()[AddedItem].X * InventoryComponent->TileSize;

			int32 Y = InventoryComponent->
				GetAllItems()[AddedItem].Y * InventoryComponent->TileSize;

			PanelSlot = GridCanvasPanel->
				AddChild(CharacterReference->ItemWidget);
			Cast<UCanvasPanelSlot>(PanelSlot)->SetAutoSize(true);
			Cast<UCanvasPanelSlot>(PanelSlot)->SetPosition(FVector2D(X, Y));

		}
	}

}


bool UInventoryGridWidget::NativeOnDrop(
	const FGeometry& InGeometry, 
	const FDragDropEvent& InDragDropEvent, 
	UDragDropOperation* InOperation)
{
	// InOperation->Payload - це і наш предмет який ми перетягуємо

	if(InOperation->Payload) {

		DroppedItem = Cast<AItemBase>(InOperation->Payload);

		if (IsRoomAvailableForPayLoad(DroppedItem)) {

			InventoryComponent->RefreshAllItems();


			InventoryComponent->AddItemAt(
				DroppedItem,
				InventoryComponent->TileToIndex(DraggedItemTopLeftIndex)
			);
		}
		else {

			// тут треба шукати той глюк шо при переміщені інколи пропадають ітеми
			InventoryComponent->RefreshAllItems();

			if (!InventoryComponent->TryAddItem(DroppedItem)) 
			{
				// спавн ітема біля персонажа
				FVector SpawnLocation = CharacterReference->
					GetActorLocation() + CharacterReference->
					GetActorForwardVector() * 200.0f;

				FRotator SpawnRotation = CharacterReference->GetActorRotation();

				FActorSpawnParameters SpawnParams;

				SpawnParams.
					SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

				AItemBase* SpawnedItem = GetWorld()->SpawnActor<AItemBase>(
					InOperation->Payload->GetClass(),
					SpawnLocation * FVector(1, 1, 0), // шоб спавнило на землю
					SpawnRotation,
					SpawnParams
				);
			}
		
		}

		Dropped = true;
		//
		DrawDropLocation = true;
		// тимчасово
		return true;

	}
	return false;
}

bool UInventoryGridWidget::NativeOnDragOver(
	const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (InOperation->Payload) {

		DraggedItem = Cast<AItemBase>(InOperation->Payload);

		FVector2D ScreenPosition = InDragDropEvent.GetLastScreenSpacePosition();
		FVector2D LocalPosition = InGeometry.AbsoluteToLocal(ScreenPosition);

		// Стартові кординати сітки
		FVector2D GridStarterCordinates = GridBorder->
			GetCachedGeometry().GetLocalPositionAtCoordinates(FVector2D(0.0f, 0.0f));

		FVector2D AdjustedPosition = LocalPosition - GridStarterCordinates;

		/*GEngine->AddOnScreenDebugMessage(
			-1, 5.0f,
			FColor::Green, 
			FString::Printf(TEXT("X: %.2f Y: %.2f"), AdjustedPosition.X, AdjustedPosition.Y)
		);*/

		FIntPoint ResultTile;

		bool Down_ = FMousePositionInTileResult(AdjustedPosition).Down;
		bool Right_ = FMousePositionInTileResult(AdjustedPosition).Right;

		if (Right_) {
			ResultTile.X = FMath::Clamp(
				DraggedItem->GetDimensions().X - 1,
				0,
				DraggedItem->GetDimensions().X - 1
			);
		}
		else {
			ResultTile.X = FMath::Clamp(
				DraggedItem->GetDimensions().X,
				0,
				DraggedItem->GetDimensions().X
			);
		}

		if (Down_) {
			ResultTile.Y = FMath::Clamp(
				DraggedItem->GetDimensions().Y - 1,
				0,
				DraggedItem->GetDimensions().Y - 1
			);
		}
		else {
			ResultTile.Y = FMath::Clamp(
				DraggedItem->GetDimensions().Y,
				0,
				DraggedItem->GetDimensions().Y
			);
		}

		DraggedItemTopLeftIndex = FIntPoint(
			FMath::TruncToInt32(AdjustedPosition.X / InventoryComponent->TileSize),
			FMath::TruncToInt32(AdjustedPosition.Y / InventoryComponent->TileSize)
		) - (ResultTile / 2);


		// тимчасово
		return true;
	}
	return false;
}

bool UInventoryGridWidget::IsRoomAvailableForPayLoad(AItemBase* Item) const
{
	if (Item) {
		return InventoryComponent->
			isRoomAvailable(
				Item, 
				InventoryComponent->TileToIndex(DraggedItemTopLeftIndex)
			);
	}
	return false;
}

FMousePositionInTile UInventoryGridWidget::FMousePositionInTileResult(FVector2D(MousePosition))
{
	// Горизонт
	MousePositionInTile
		.Right = fmod(MousePosition.X, InventoryComponent->TileSize)
		> (InventoryComponent->TileSize / 2);

	// Вертикаль
	MousePositionInTile
		.Down = fmod(MousePosition.Y, InventoryComponent->TileSize)
		> (InventoryComponent->TileSize / 2);

	return MousePositionInTile;
}

FReply UInventoryGridWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{

	if (InKeyEvent.GetKey() == EKeys::R) {

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("R clicked"));
		//return FReply::Handled();

		if (DraggedItem) {
			DraggedItem->RotateItem();

			if (StorredDragDropOperation) {
				UInventoryItemWidget* 
					VisualDraggedItem = Cast<UInventoryItemWidget>(
						StorredDragDropOperation->DefaultDragVisual
					);

				if (VisualDraggedItem) {
					VisualDraggedItem->Refresh(DraggedItem);
				}
				return FReply::Handled();

			}
		}
	}

	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UInventoryGridWidget::NativeOnDragEnter(
	const FGeometry& InGeometry,
	const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	DraggedPayLoad = InOperation->Payload;

	DrawDropLocation = true;

	UDragDropOperation* DropOperation = Cast<UDragDropOperation>(InOperation);

	if (DropOperation) {
		StorredDragDropOperation = DropOperation;
	}

}

void UInventoryGridWidget::NativeOnDragLeave(const FDragDropEvent& InMouseEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InMouseEvent, InOperation);

	DraggedPayLoad = nullptr;

	DrawDropLocation = false;

}

void UInventoryGridWidget::DrawBackgroundBox(
	AItemBase* Item,
	FLinearColor MyTintColor,
	const FGeometry& AllottedGeometry,
	FVector2D TopLeftCorner,
	FSlateWindowElementList& OutDrawElements,
	int32 LayedId) const
{
	FSlateBrush BoxBrush;
	BoxBrush.DrawAs = ESlateBrushDrawType::Box;

	FVector2D BoxSize(
		Item->GetDimensions().X * InventoryComponent->TileSize,
		Item->GetDimensions().Y * InventoryComponent->TileSize
	);

	FIntPoint BoxPosition(
		//DraggedItemTopLeftTile.X * InventoryComponent->TileSize,
		DraggedItemTopLeftIndex.X * InventoryComponent->TileSize,
		DraggedItemTopLeftIndex.Y * InventoryComponent->TileSize
	);

	FPaintGeometry PaintGeometry = AllottedGeometry
		.ToPaintGeometry(BoxSize, FSlateLayoutTransform(TopLeftCorner + BoxPosition));

	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayedId,
		PaintGeometry,
		&BoxBrush,
		ESlateDrawEffect::None, 
		MyTintColor
	);

}





