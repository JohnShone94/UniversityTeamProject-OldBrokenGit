// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerCapsule.h"
#include "TheSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "TheMainGameCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
APowerCapsule::APowerCapsule()
{
	this->PickupRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickupRoot"));
	this->RootComponent = this->PickupRoot;

	this->PowerCapsule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerCapsule"));
	this->PowerCapsule->SetupAttachment(this->RootComponent);

	this->PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	this->PickupMesh->SetupAttachment(this->RootComponent);
}

int APowerCapsule::GetPower()
{
	return PowerAmount;
}