// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TheSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class THEMAINGAME_API UTheSaveGame : public USaveGame
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UTheSaveGame();

public:
	UFUNCTION(BlueprintCallable, Category = Basic)
	void SetCurrentPower(int power);
	UFUNCTION(BlueprintPure, Category = Basic)
	int GetCurrentPower();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetMaxPower(int power);
	UFUNCTION(BlueprintPure, Category = Basic)
		int GetMaxPower();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int CurrentPower;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int MaxPower;
};
