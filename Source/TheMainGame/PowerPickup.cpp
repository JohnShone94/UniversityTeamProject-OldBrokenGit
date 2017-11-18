// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPickup.h"

// Sets default values
APowerPickup::APowerPickup()
{
	PowerAmount = 10;
}

void APowerPickup::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();
	Destroy();
}
// Returns the amount of power this pickup gives.
int APowerPickup::GetPower()
{

	return PowerAmount;
}