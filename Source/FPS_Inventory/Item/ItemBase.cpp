// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Components/SphereComponent.h"
#include "ItemBase.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	// прикріпляєм меш до рута
	Mesh->SetupAttachment(RootComponent);
	Sphere->SetupAttachment(Mesh);

	// відключаєм колізію
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}



// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FIntPoint AItemBase::GetDimensions() const
{
	return Dimensions;
}

UMaterialInterface* AItemBase::GetIcon()
{
	return Icon;
}

UMaterialInterface* AItemBase::GetRotationIcon()
{
	return RotationIcon;
}

bool AItemBase::GetIsRotated()
{
	return isRotated;
}

void AItemBase::RotateItem()
{
	if (isRotated) {
		isRotated = false;
	}
	else {
		isRotated = true;
	}
}

