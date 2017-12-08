// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"
#include "TheSaveGame.h"
#include "TheMainGameCharacter.h"

// Sets default values
APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;
	
	this->PortalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PortalRoot"));
	this->RootComponent = this->PortalRoot;

	this->PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	this->PortalMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	this->PortalStandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalStandMesh"));
	this->PortalStandMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	this->PortalStairsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalStairsMesh"));
	this->PortalStairsMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	this->PortalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollision"));
	this->PortalCollision->bGenerateOverlapEvents = true;
	this->PortalCollision->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	this->PortalCollision->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATheMainGameCharacter* Character;
	Character = (ATheMainGameCharacter*)GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn();
	LevelToLoad = Character->GetWorldName();
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	ATheMainGameCharacter* Character;
	Character = (ATheMainGameCharacter*)GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn();
	if(OtherActor == Player && LevelToLoad != "" && Character->GetPortalActive())
	{
		//Changing the character variables.
		Character->SetOffWorld(!Character->GetOffWorld());

		if (LevelToLoad == "Factory")
		{
			Character->SetWorldName("Base");
		}
		else
		{
			Character->SetPortalActive(false);
		}


		//Saving the variables.
		UTheSaveGame* SaveGameInstance = Cast<UTheSaveGame>(UGameplayStatics::CreateSaveGameObject(UTheSaveGame::StaticClass()));
		SaveGameInstance->sCurrentPower = Character->GetCurrentPower();
		SaveGameInstance->sMaxPower = Character->GetMaxPower();
		SaveGameInstance->sOffWorld = Character->GetOffWorld();
		SaveGameInstance->sPortalActive = Character->GetPortalActive();
		SaveGameInstance->sWorldName = Character->GetWorldName();
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

		UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
	}
}

