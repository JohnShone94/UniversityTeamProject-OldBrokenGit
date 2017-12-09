// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheMainGameGameMode.generated.h"

UCLASS(minimalapi)
class ATheMainGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheMainGameGameMode();

	//virtual void StartNewPlayer(APlayerController* NewPlayer)    override;
};