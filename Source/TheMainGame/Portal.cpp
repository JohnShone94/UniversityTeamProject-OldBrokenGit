// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"

// Sets default values
APortal::APortal()
{
	PortalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PortalRoot"));

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->AttachToComponent(PortalRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PortalCollision = CreateDefaultSubobject<UShapeComponent>(TEXT("PortakCollision"));
	PortalCollision->bGenerateOverlapEvents = true;
	PortalCollision->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
    PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	PortalCollision->AttachToComponent(PortalRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//FString entered = FString::Printf(TEXT("You Have Entered The Portal"));

		//GEngine->AddOnScreenDebugMessage(1, 5, FColor::White, entered);
	}
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

