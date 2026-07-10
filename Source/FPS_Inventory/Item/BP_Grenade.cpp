// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BP_Grenade.h"

ABP_Grenade::ABP_Grenade()
{
	Dimensions = FIntPoint(1, 1);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		ItemIcon(TEXT("/Game/_FPS/_Assets/_Materials/_UI/_Icons/MI_Grenade"));

	// /Game/_FPS/_Assets/_Materials/_UI/_Icons/MI_Grenade.MI_Grenade

	if (ItemIcon.Succeeded()) {
		Icon = ItemIcon.Object;
		RotatedIcon = Icon;
	}
}

// part 6 final
