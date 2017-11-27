// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TheMainGameCharacter.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class THEMAINGAME_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(EditAnywhere)
	USceneComponent* PortalRoot;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PortalMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PortalStairsMesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PortalStandMesh;

	UPROPERTY(EditAnywhere)
		UBoxComponent* PortalCollision;


	UPROPERTY(EditAnywhere)
	FName LevelToLoad;

	TheMainGameCharacter* Character;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
