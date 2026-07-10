// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BP_Knife.h"

ABP_Knife::ABP_Knife()
{
	Dimensions = FIntPoint(1, 2);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		ItemInfo(TEXT("/Game/_FPS/_Assets/_Materials/_UI/MI_Knife"));

	if (ItemInfo.Succeeded()) {
		Icon = ItemInfo.Object;
	}
}
