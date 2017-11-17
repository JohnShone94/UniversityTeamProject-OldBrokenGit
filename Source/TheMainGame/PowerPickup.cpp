// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerPickup.h"

// Sets default values
APowerPickup::APowerPickup()
{
	this->PowerPickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PowerPickupRoot"));
	this->RootComponent = this->PowerPickupRoot;

	this->PowerPickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerPickupMesh"));
	this->PowerPickupMesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	this->PowerPickupCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PowerPickupCollision"));
	this->PowerPickupCollision->bGenerateOverlapEvents = true;
	this->PowerPickupCollision->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	this->PowerPickupCollision->OnComponentBeginOverlap.AddDynamic(this, &APowerPickup::OnOverlapBegin);
	this->PowerPickupCollision->AttachToComponent(this->RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APowerPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (OtherActor == Player)
	{
		Destroy();
	}
}
