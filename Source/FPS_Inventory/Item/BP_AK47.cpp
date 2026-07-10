// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BP_AK47.h"

ABP_AK47::ABP_AK47()
{
	Dimensions = FIntPoint(5, 2);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> 
		ItemInfo(TEXT("/Game/_FPS/_Assets/_Materials/_UI/MI_AK47"));

	if (ItemInfo.Succeeded()) {
		Icon = ItemInfo.Object;
	}

}
