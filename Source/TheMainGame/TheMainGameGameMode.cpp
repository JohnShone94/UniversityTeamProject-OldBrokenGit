// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TheMainGameGameMode.h"
#include "TheMainGameHUD.h"
#include "TheMainGameCharacter.h"
#include "TheSaveGame.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ATheMainGameGameMode::ATheMainGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Character/bp_TheMainGameCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATheMainGameHUD::StaticClass();

}
