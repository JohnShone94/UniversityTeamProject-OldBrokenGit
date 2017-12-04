// Fill out your copyright notice in the Description page of Project Settings.

#include "TheSaveGame.h"
#include "TheMainGame.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>


UTheSaveGame::UTheSaveGame()
{
	SaveSlotName = TEXT("SaveSlotOne");
	UserIndex = 0;
}