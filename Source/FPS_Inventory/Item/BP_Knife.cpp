// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BP_Knife.h"

ABP_Knife::ABP_Knife()
{
	Dimensions = FIntPoint(1, 2);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		ItemIcon(TEXT("/Game/_FPS/_Assets/_Materials/_UI/_Icons/MI_Knife"));

	if (ItemIcon.Succeeded()) {
		Icon = ItemIcon.Object;
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		IconRotated(TEXT("/Game/_FPS/_Assets/_Materials/_UI/_Icons/_Rotated/MI_Knife_Rotated"));

	if (IconRotated.Succeeded()) {
		RotatedIcon = IconRotated.Object;
	}
}
