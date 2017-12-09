// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPickup.h"
#include "TheSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TheMainGameCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APowerPickup::APowerPickup()
{
	PowerAmount = 10;

	this->PowerCapsule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerCapsule"));
	this->PowerCapsule->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APowerPickup::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();
}

int APowerPickup::GetPower()
{
	return PowerAmount;
}