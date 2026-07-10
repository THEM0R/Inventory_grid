// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BP_Grenade.h"

ABP_Grenade::ABP_Grenade()
{
	Dimensions = FIntPoint(1, 1);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		ItemInfo(TEXT("/Game/_FPS/_Assets/_Materials/_UI/MI_Grenade"));

	if (ItemInfo.Succeeded()) {
		Icon = ItemInfo.Object;
	}
}

// part 6 final
