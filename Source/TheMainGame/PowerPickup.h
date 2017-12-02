// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "PowerPickup.generated.h"

UCLASS()
class THEMAINGAME_API APowerPickup : public APickup
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerPickup();
	
	void WasCollected_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		int PowerAmount;
};
