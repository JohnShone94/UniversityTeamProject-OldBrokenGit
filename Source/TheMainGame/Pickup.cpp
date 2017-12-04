// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TheMainGameCharacter.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsActive = true;

	this->PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	this->RootComponent = this->PickupRoot;

	this->PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	this->PickupMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickup::IsActive()
{
	return bIsActive;
}

void APickup::SetActive(bool active)
{
	bIsActive = active;
}

void APickup::WasCollected_Implementation()
{
}