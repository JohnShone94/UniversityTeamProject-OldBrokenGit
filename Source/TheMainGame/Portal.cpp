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
	this->PortalMesh->SetupAttachment(this->RootComponent);

	this->PortalStandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalStandMesh"));
	this->PortalStandMesh->SetupAttachment(this->RootComponent);

	this->PortalStairsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalStairsMesh"));
	this->PortalStairsMesh->SetupAttachment(this->RootComponent);

	this->PortalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollision"));
	this->PortalCollision->bGenerateOverlapEvents = true;
	this->PortalCollision->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	this->PortalCollision->SetupAttachment(this->RootComponent);

}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	ATheMainGameCharacter* Character;
	Character = (ATheMainGameCharacter*)GEngine->GetFirstLocalPlayerController(GetWorld())->GetPawn();
	if(OtherActor == Player && LevelToLoad != "" && Character->GetPortalActive())
	{
		LevelToLoad = Character->GetWorldName();

		Character->SetCheckpointLoc(FVector(0.0f, 0.0f, 0.0f));
		Character->SetCheckpointRot(FRotator(0.0f, 0.0f, 0.0f));

		if (Character->GetWorldName() == "The_Factory" || Character->GetWorldName() == "The_SpaceStation")
		{
			Character->SetWorldName("The_Labratory");
		}
		else
		{
			Character->SetPortalActive(false);
		}
		Character->RunSaveGame();

		UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
	}
}

