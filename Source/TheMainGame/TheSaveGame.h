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

	UTheSaveGame();

public:

	UPROPERTY(EditAnywhere, Category = "Save Game")
		FString SaveSlotName;

	UPROPERTY(EditAnywhere, Category = "Save Game")
		uint32 UserIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		int sCurrentPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		int sMaxPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sOffWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sPortalActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		FName sWorldName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		int sTime;
};
