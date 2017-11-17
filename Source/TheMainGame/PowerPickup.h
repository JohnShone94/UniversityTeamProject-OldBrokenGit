// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerPickup.generated.h"

UCLASS()
class THEMAINGAME_API APowerPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerPickup();

	UPROPERTY(EditAnywhere)
		USceneComponent* PowerPickupRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PowerPickupMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* PowerPickupCollision;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	void OnOverlapBegin();
	
};
