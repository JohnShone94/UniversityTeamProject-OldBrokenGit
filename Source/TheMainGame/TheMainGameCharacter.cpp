// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TheMainGameCharacter.h"
#include "Engine.h"
#include "TheMainGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "TheSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Portal.h"
#include "MotionControllerComponent.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATheMainGameCharacter

ATheMainGameCharacter::ATheMainGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->Hand = EControllerHand::Right;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;


	CurrentPower = 50;
	MaxPower = 200;
	WorldName = "The_Labratory";
	CurrentWorld = "The_Labratory";
	PortalActive = false;
	CurrentTime = 120;
	pHealth = 200;
	pMaxHealth = 200;
	MaxAmmo = 50;
	Ammo = MaxAmmo;
	gunType = 0;
	Labratory = true;
	Flashlight = false;
	Tutorial1 = false;
	Tutorial2 = false;
	Tutorial3 = false;
	Tutorial4 = false;
}

void ATheMainGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
//------------------------------------------------ Setting up and loading the save game --------------------------------------------------------------------//

	UTheSaveGame* LoadGameInstance = Cast<UTheSaveGame>(UGameplayStatics::CreateSaveGameObject(UTheSaveGame::StaticClass()));
	if (!Cast<UTheSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex)))
	{
		RunSaveGame();
	}
	else
	{
		RunLoadGame();
	}

/*	UWorld* const World = GetWorld();
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(World, 0);
	myCharacter->SetActorLocation(Checkpoint)*/


//----------------------------------------------------------------------------------------------------------------------------------------------------------//
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheMainGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);



	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATheMainGameCharacter::TouchStarted);
	if (EnableTouchscreenMovement(PlayerInputComponent) == false)
	{
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATheMainGameCharacter::StartFire);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATheMainGameCharacter::StopFire);
		PlayerInputComponent->BindAction("SwitchGun", IE_Pressed, this, &ATheMainGameCharacter::SetGunType);
	}

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATheMainGameCharacter::OnResetVR);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATheMainGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATheMainGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATheMainGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATheMainGameCharacter::LookUpAtRate);


	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATheMainGameCharacter::OnResetVR);
}

void ATheMainGameCharacter::OnFire()
{
	if (gunType == 1 && shooting == true && !Overheated && !OverlappingComp)
	{
		FTimerHandle FuzeTimerHandle;

		// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				if (bUsingMotionControllers)
				{
					const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
					const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
					World->SpawnActor<ATheMainGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
				}
				else
				{
					const FRotator SpawnRotation = GetControlRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

					//Set Spawn Collision Handling Override
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					// spawn the projectile at the muzzle
					World->SpawnActor<ATheMainGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					Ammo--;
					GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ATheMainGameCharacter::OnFire, 0.3f, false);
				}
			}
		}

		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}

		if (Ammo <= 0)
		{
			BeginOverheat();
		}

	}
	else if(gunType == 0 && !Overheated && !OverlappingComp)
	{
		// try and fire a projectile
		if (ProjectileClass != NULL)
		{
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				if (bUsingMotionControllers)
				{
					const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
					const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
					World->SpawnActor<ATheMainGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
				}
				else
				{
					const FRotator SpawnRotation = GetControlRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

					//Set Spawn Collision Handling Override
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					// spawn the projectile at the muzzle
					World->SpawnActor<ATheMainGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					Ammo--;
				}
			}
		}
		// try and play the sound if specified
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}

		if (Ammo <= 0)
		{
			BeginOverheat();
		}

	}
}
void ATheMainGameCharacter::StartFire()
{
	shooting = true;
	OnFire();
}

void ATheMainGameCharacter::StopFire()
{
	shooting = false;
}
void ATheMainGameCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATheMainGameCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ATheMainGameCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = false;
}

void ATheMainGameCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATheMainGameCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATheMainGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATheMainGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ATheMainGameCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	bool bResult = false;
	if (FPlatformMisc::GetUseVirtualJoysticks() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		bResult = true;
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATheMainGameCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ATheMainGameCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATheMainGameCharacter::TouchUpdate);
	}
	return bResult;
}



//----------------------------------------------------------------------------------------------------------------//
//-----------------------------------------NEW FUNCTIONS AND VARIABLES--------------------------------------------//
//----------------------------------------------------------------------------------------------------------------//
int ATheMainGameCharacter::GetCurrentPower()
{
	return CurrentPower;
}

void ATheMainGameCharacter::SetCurrentPower(int power)
{
		CurrentPower = CurrentPower + power;
		if (CurrentPower < 0)
		{
			CurrentPower = 0;
		}
		if (CurrentPower >= MaxPower + 1)
		{
			CurrentPower = MaxPower;
		}
}

int ATheMainGameCharacter::GetTime()
{
	return CurrentTime;
}

void ATheMainGameCharacter::UpdateTime(int time)
{
	if (CurrentTime <= 0)
	{
		PortalActive = false;
	}
	else
	{
		CurrentTime += time;
	}
}

void ATheMainGameCharacter::ResetTime()
{
	CurrentTime = 120;
}

int ATheMainGameCharacter::GetMaxPower()
{
	return MaxPower;
}

void ATheMainGameCharacter::SetMaxPower(int power)
{
	if (MaxPower < 200)
	{
		MaxPower = 200;
	}
	else
	{
		MaxPower += power;
	}
}

int ATheMainGameCharacter::GetMaxHealth()
{
	return pMaxHealth;
}

void ATheMainGameCharacter::SetMaxHealth(int maxHealth)
{
	if (pMaxHealth < 200)
	{
		pMaxHealth = 200;
	}
	else
	{
		pMaxHealth += maxHealth;
	}
}
void ATheMainGameCharacter::SetGunType()
{
	switch (gunType)
	{
	case 0:
		gunType = 1;
		MaxAmmo = 100;
		Ammo = MaxAmmo;
		break;
	case 1:
		gunType = 0;
		MaxAmmo = 50;
		Ammo = MaxAmmo;
		break;
	default:
		gunType = 0;
		MaxAmmo = 50;
		Ammo = MaxAmmo;
		break;
	}
}
int ATheMainGameCharacter::GetCurrentHealth()
{
	return pHealth;
}

void ATheMainGameCharacter::SetCurrentHealth(int health)
{
	if (pHealth > pMaxHealth)
	{
		pHealth = pMaxHealth;
	}
	else
	{
		pHealth = pHealth + health;
		if (pHealth < 0)
		{
		//	RunReloadGame();
		}
	}
}

void ATheMainGameCharacter::SetIsOverlappingComp(bool overlap)
{
	OverlappingComp = overlap;
}
bool ATheMainGameCharacter::GetIsOverlappingComp()
{
	return OverlappingComp;
}

void ATheMainGameCharacter::SetIsOverlappingPower(bool overlap)
{
	OverlappingPower = overlap;
}
bool ATheMainGameCharacter::GetIsOverlappingPower()
{
	return OverlappingPower;
}



void ATheMainGameCharacter::SetPortalActive(bool active)
{
	PortalActive = active;
	CurrentTime = 120;
}
bool ATheMainGameCharacter::GetPortalActive()
{
	return PortalActive;
}


void ATheMainGameCharacter::SetLabratory(bool active)
{
	Labratory = active;
	Spacestation = false;
	Factory = false;
}
bool ATheMainGameCharacter::GetLabratory()
{
	return Labratory;
}

void ATheMainGameCharacter::SetFactory(bool active)
{
	Factory = active;
	Labratory = false;
	Spacestation = false;
}
bool ATheMainGameCharacter::GetFactory()
{
	return Factory;
}

void ATheMainGameCharacter::SetSpacestation(bool active)
{
	Spacestation = active;
	Factory = false;
	Labratory = false;
}
bool ATheMainGameCharacter::GetSpacestation()
{
	return Spacestation;
}

void ATheMainGameCharacter::SetFlashlight(bool active)
{
	Flashlight = active;
}
bool ATheMainGameCharacter::GetFlashlight()
{
	return Flashlight;
}

void ATheMainGameCharacter::SetWorldName(FName name)
{
	WorldName = name;

	UTheSaveGame* SaveGameInstance = Cast<UTheSaveGame>(UGameplayStatics::CreateSaveGameObject(UTheSaveGame::StaticClass()));
	SaveGameInstance->sWorldName = WorldName;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
FName ATheMainGameCharacter::GetWorldName()
{
	return WorldName;
}

void ATheMainGameCharacter::SetCurrentWorld(FString name)
{
	CurrentWorld = name;
	RunSaveGame();
}

FString ATheMainGameCharacter::GetCurrentWorld()
{
	return CurrentWorld;
}

void ATheMainGameCharacter::SetCheckpointRot(FRotator checkpointRot)
{
	CheckpointRot = checkpointRot;
}

FRotator ATheMainGameCharacter::GetCheckPointRot()
{
	return CheckpointRot;
}

void ATheMainGameCharacter::SetCheckpointLoc(FVector checkpointLoc)
{
	CheckpointLoc = checkpointLoc;
}

FVector ATheMainGameCharacter::GetCheckPointLoc()
{
	return CheckpointLoc;
}


void ATheMainGameCharacter::SetTutorial1(bool active)
{
	Tutorial1 = active;
}
bool ATheMainGameCharacter::GetTutorial1()
{
	return Tutorial1;
}

void ATheMainGameCharacter::SetTutorial2(bool active)
{
	Tutorial2 = active;
}
bool ATheMainGameCharacter::GetTutorial2()
{
	return Tutorial2;
}

void ATheMainGameCharacter::SetTutorial3(bool active)
{
	Tutorial3 = active;
}
bool ATheMainGameCharacter::GetTutorial3()
{
	return Tutorial3;
}

void ATheMainGameCharacter::SetTutorial4(bool active)
{
	Tutorial4 = active;
}
bool ATheMainGameCharacter::GetTutorial4()
{
	return Tutorial4;
}

void ATheMainGameCharacter::RunSaveGame()
{
	UTheSaveGame* SaveGameInstance = Cast<UTheSaveGame>(UGameplayStatics::CreateSaveGameObject(UTheSaveGame::StaticClass()));
	SaveGameInstance->sCurrentPower = CurrentPower;
	SaveGameInstance->sMaxPower = MaxPower;
	SaveGameInstance->sTime = CurrentTime;
	SaveGameInstance->sWorldName = WorldName;
	SaveGameInstance->sPortalActive = PortalActive;
	SaveGameInstance->sHealth = pHealth;
	SaveGameInstance->sMaxHealth = pMaxHealth;
	SaveGameInstance->sLabratory = Labratory;
	SaveGameInstance->sFactory = Factory;
	SaveGameInstance->sSpaceStation = Spacestation;
	SaveGameInstance->sFlashlight = Flashlight;
	SaveGameInstance->sCurrentWorld = GetWorld()->GetName();

	SaveGameInstance->sCheckpointLoc = CheckpointLoc;
	SaveGameInstance->sCheckpointRot = CheckpointRot;

	SaveGameInstance->sTutorial1 = Tutorial1;
	SaveGameInstance->sTutorial2 = Tutorial2;
	SaveGameInstance->sTutorial3 = Tutorial3;
	SaveGameInstance->sTutorial4 = Tutorial4;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void ATheMainGameCharacter::RunLoadGame()
{
	UTheSaveGame* LoadGameInstance = Cast<UTheSaveGame>(UGameplayStatics::CreateSaveGameObject(UTheSaveGame::StaticClass()));
	LoadGameInstance = Cast<UTheSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	CurrentPower = LoadGameInstance->sCurrentPower;
	MaxPower = LoadGameInstance->sMaxPower;
	WorldName = LoadGameInstance->sWorldName;
	PortalActive = LoadGameInstance->sPortalActive;
	CurrentTime = LoadGameInstance->sTime;
	pHealth = LoadGameInstance->sHealth;
	pMaxHealth = LoadGameInstance->sMaxHealth;
	Labratory = LoadGameInstance->sLabratory;
	Factory = LoadGameInstance->sFactory;
	Spacestation = LoadGameInstance->sSpaceStation;
	Flashlight = LoadGameInstance->sFlashlight;
	CurrentWorld = LoadGameInstance->sCurrentWorld;

	CheckpointLoc = LoadGameInstance->sCheckpointLoc;
	CheckpointRot = LoadGameInstance->sCheckpointRot;

	Tutorial1 = LoadGameInstance->sTutorial1;
	Tutorial2 = LoadGameInstance->sTutorial2;
	Tutorial3 = LoadGameInstance->sTutorial3;
	Tutorial4 = LoadGameInstance->sTutorial4;
}

void ATheMainGameCharacter::RunReloadGame()
{
	RunLoadGame();
}

void ATheMainGameCharacter::BeginOverheat()
{
	Overheated = true;
	FTimerHandle FuzeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ATheMainGameCharacter::EndOverheat, 3.0f, false);
}

void ATheMainGameCharacter::EndOverheat()
{
	Overheated = false;
	Ammo = MaxAmmo;
}
