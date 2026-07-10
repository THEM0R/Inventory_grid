// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BP_AK47.h"

ABP_AK47::ABP_AK47()
{
	Dimensions = FIntPoint(5, 2);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> 
		ItemIcon(TEXT("/Game/_FPS/_Assets/_Materials/_UI/_Icons/MI_AK47"));

	if (ItemIcon.Succeeded()) {
		Icon = ItemIcon.Object;
	}

	// /Game/_FPS/_Assets/_Materials/_UI/_Icons/_Rotated/MI_AK47_Rotated.MI_AK47_Rotated


	static ConstructorHelpers::FObjectFinder<UMaterialInterface>
		IconRotated(TEXT("/Game/_FPS/_Assets/_Materials/_UI/_Icons/_Rotated/MI_AK47_Rotated"));

	if (IconRotated.Succeeded()) {
		RotatedIcon = IconRotated.Object;
	}


}
