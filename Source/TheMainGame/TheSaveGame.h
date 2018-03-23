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
		int sHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		int sMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		FName sSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sPortalActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		FName sWorldName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		FString sCurrentWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		int sTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		FRotator sCheckpointRot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		FVector sCheckpointLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sLabratory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sFactory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sSpaceStation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sFlashlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sTutorial1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sTutorial2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sTutorial3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
		bool sTutorial4;
};
