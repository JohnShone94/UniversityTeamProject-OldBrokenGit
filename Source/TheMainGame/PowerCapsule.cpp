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
	this->PowerCapsule = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerCapsule"));
	this->PowerCapsule->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APowerCapsule::WasCollected_Implementation()
{
	Super::WasCollected_Implementation();
}

int APowerCapsule::GetPower()
{
	return PowerAmount;
}