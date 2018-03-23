// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheMainGameCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class ATheMainGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* L_MotionController;

public:
	ATheMainGameCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ATheMainGameProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

protected:
	
	/** Fires a projectile. */
	void OnFire();
	void StopFire();
	void StartFire();
	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	//void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }


	//----------------------------------------------------------------------------------------------------------------//
	//-----------------------------------------NEW FUNCTIONS AND VARIABLES--------------------------------------------//
	//----------------------------------------------------------------------------------------------------------------//
public:
	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetCurrentPower(int power);
	UFUNCTION(BlueprintPure, Category = Basic)
		int GetCurrentPower();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetMaxPower(int power);
	UFUNCTION(BlueprintPure, Category = Basic)
		int GetMaxPower();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetCurrentHealth(int health);
	UFUNCTION(BlueprintPure, Category = Basic)
		int GetCurrentHealth ();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetMaxHealth(int health);
	UFUNCTION(BlueprintPure, Category = Basic)
		int GetMaxHealth ();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetIsOverlappingComp(bool overlap);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetIsOverlappingComp();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetIsOverlappingPower(bool overlap);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetIsOverlappingPower();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetPortalActive(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetPortalActive();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetLabratory(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetLabratory();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetFactory(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetFactory();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetSpacestation(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetSpacestation();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetFlashlight(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetFlashlight();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetTutorial1(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetTutorial1();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetTutorial2(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetTutorial2();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetTutorial3(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetTutorial3();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetTutorial4(bool active);
	UFUNCTION(BlueprintPure, Category = Basic)
		bool GetTutorial4();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetWorldName(FName name);
	UFUNCTION(BlueprintPure, Category = Basic)
		FName GetWorldName();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetCurrentWorld(FString name);
	UFUNCTION(BlueprintPure, Category = Basic)
		FString GetCurrentWorld();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetCheckpointLoc(FVector checkpointLoc);
	UFUNCTION(BlueprintPure, Category = Basic)
		FVector GetCheckPointLoc();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetCheckpointRot(FRotator checkpointRot);
	UFUNCTION(BlueprintPure, Category = Basic)
		FRotator GetCheckPointRot();

	UFUNCTION(BlueprintPure, Category = Basic)
		int GetTime();
	UFUNCTION(BlueprintCallable, Category = Basic)
		void UpdateTime(int time);
	UFUNCTION(BlueprintCallable, Category = Basic)
		void ResetTime();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void SetGunType();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void RunSaveGame();
	UFUNCTION(BlueprintCallable, Category = Basic)
		void RunLoadGame();
	UFUNCTION(BlueprintCallable, Category = Basic)
		void RunReloadGame();

	UFUNCTION(BlueprintCallable, Category = Basic)
		void BeginOverheat();
	UFUNCTION(BlueprintCallable, Category = Basic)
		void EndOverheat();

private:
	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool PortalActive;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool OverlappingComp;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool OverlappingPower;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Overheated;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int CurrentPower;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int MaxPower;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int CurrentTime;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int pHealth;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int pMaxHealth;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int gunType;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int Ammo;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int MaxAmmo;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FName WorldName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FName SpawnPoint;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FRotator CheckpointRot;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FVector CheckpointLoc;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Factory;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Spacestation;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Labratory;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Flashlight;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool shooting;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString CurrentWorld;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Tutorial1;
	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Tutorial2;
	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Tutorial3;
	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Tutorial4;
};

