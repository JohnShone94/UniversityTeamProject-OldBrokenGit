// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"

// Sets default values
APortal::APortal()
{
	
	this->PortalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PortalRoot"));
	this->RootComponent = this->PortalRoot;

	this->PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	this->PortalMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	this->PortalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollision"));
	this->PortalCollision->bGenerateOverlapEvents = true;
	this->PortalCollision->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	this->PortalCollision->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	this->LevelToLoad = "Level_World1";
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if(OtherActor == Player && LevelToLoad != "")
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);

		FString Output = FString::Printf(TEXT("Whooooooooooosh!!!!!!!"));
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::White, Output);

	}
}

