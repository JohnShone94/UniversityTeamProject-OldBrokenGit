// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
		USceneComponent* PortalRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
		UStaticMeshComponent* PortalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
		UStaticMeshComponent* PortalStandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
		UStaticMeshComponent* PortalStairsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
		UBoxComponent* PortalCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Portal)
		FName LevelToLoad;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
