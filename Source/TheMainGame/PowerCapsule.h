// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerCapsule.generated.h"

UCLASS()
class THEMAINGAME_API APowerCapsule : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerCapsule();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		int PowerAmount;

	UFUNCTION(BlueprintPure, Category = Basic)
		int GetPower();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* PowerCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
		USceneComponent* PickupRoot;
};
