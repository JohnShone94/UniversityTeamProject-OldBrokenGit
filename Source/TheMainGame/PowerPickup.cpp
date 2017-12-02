// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPickup.h"
#include "TheSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APowerPickup::APowerPickup()
{
	PowerAmount = 10;
}

void APowerPickup::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();

	UTheSaveGame* SaveGameInstance = Cast<UTheSaveGame>(UGameplayStatics::CreateSaveGameObject(UTheSaveGame::StaticClass()));
	SaveGameInstance->SetCurrentPower(15);
	Destroy();
}