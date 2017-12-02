// Fill out your copyright notice in the Description page of Project Settings.

#include "TheSaveGame.h"
#include "TheMainGame.h"


UTheSaveGame::UTheSaveGame()
{
	SaveSlotName = TEXT("SaveSlotOne");
	UserIndex = 0;
}

int UTheSaveGame::GetCurrentPower()
{
	return CurrentPower;
}

void UTheSaveGame::SetCurrentPower(int power)
{
	if (CurrentPower > MaxPower)
	{
		CurrentPower = MaxPower;
	}
	else
	{
		CurrentPower = CurrentPower + power;
		UE_LOG(LogTemp, Warning, TEXT("Current Power"), CurrentPower);
	}
}


int UTheSaveGame::GetMaxPower()
{
	return MaxPower;
}

void UTheSaveGame::SetMaxPower(int power)
{
	if (MaxPower < 200)
	{
		MaxPower = 200;
	}
	else
	{
		MaxPower += power;
	}
}
