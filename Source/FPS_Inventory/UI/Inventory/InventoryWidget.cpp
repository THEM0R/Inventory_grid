// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/InventoryWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Kismet/GameplayStatics.h"
#include "FPS_InventoryCharacter.h"
#include "Item/ItemBase.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CharacterReference = Cast<AFPS_InventoryCharacter>
		(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

FReply UInventoryWidget::NativeOnMouseButtonDown(
	const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent
) {
	return FReply::Handled();
}

bool UInventoryWidget::NativeOnDrop(
	const FGeometry& InGeometry, 
	const FDragDropEvent& InDragDropEvent, 
	UDragDropOperation* InOperation)
{
	if (InOperation->Payload) {

		// спавн ітема біля персонажа
		FVector SpawnLocation = CharacterReference->
			GetActorLocation() + CharacterReference->
			GetActorForwardVector() * 200.0f;

		FRotator SpawnRotation = CharacterReference->GetActorRotation();

		FActorSpawnParameters SpawnParams;

		SpawnParams.
			SpawnCollisionHandlingOverride = 
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		SpawnedItem = GetWorld()->SpawnActor<AItemBase>(
			InOperation->Payload->GetClass(),
			SpawnLocation * FVector(1,1,0), // шоб спавнило на землю
			SpawnRotation,
			SpawnParams
		);

		return true;
	}
	else {
		return false;
	}
}
