// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	EMS_Idle UMETA(DisplayName = "Idle"),
	EMS_Normal UMETA(DisplayName = "Normal"), 
	EMS_Sprinting UMETA(DisplayName = "Sprint"),
	EMS_MAX UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class EStaminaStates : uint8
{
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowNormal UMETA(DisplayName = "BelowNormal"),	//when below 15%
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_Regenerating UMETA(DisplayName = "Regenerating"),
	ESS_MAX UMETA(DisplayName = "MAX")
};

UCLASS()
class CPPPROJECT_API AMainCharacter : public ACharacter	//Classes derived from Actor have A as prefix
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	/** Declaring all variables */

	UPROPERTY(BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CharacterCamera;

	UPROPERTY(BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CharacterSpringArm;

	UPROPERTY(VisibleAnywhere ,BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;	//for side rotation

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookupRate;	//for up down rotation

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerStats)
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerStats)
	float MaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerStats)
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerStats)
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerMovement)
	float NormalSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerMovement)
	float SprintSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PlayerMovement)
	float StaminaChangeRate;

	float MinStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerMovement)
	EMovementState PlayerMovementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerMovement)
	EStaminaStates PlayerStaminaState;

	UInputComponent* playerInput;	//To get forward and side values

	bool bIsSprinting, bCanSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, CAtegory = "Player Weapon")
	class AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Pickup")
	class APickup_Base* OverlappingPickup;	//This way it can be used for other weapon like pickups as well

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	bool bIsAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	class UAnimMontage* CombatMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Animations")
	bool bIsComboActive;	//To use if combo attack is active and accordingly end attack
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ControlSprinting();

	void HandleStaminaStates(float StaminaChangePerFrame);

	void CheckForIdle();

	//Getter for Camera and Spring Arm component
	FORCEINLINE class UCameraComponent* GetCharacterCamera() { return CharacterCamera; }
	FORCEINLINE class USpringArmComponent* GetCharacterSpringArm() { return CharacterSpringArm; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float val);

	void MoveSideward(float val);

	/** Methods for Key Rotations */
	void TurnAtRate(float turnRate);

	void LooupAtRate(float lookUpRate);

	void SetMovementState(EMovementState state);

	FORCEINLINE void SetStaminaState(EStaminaStates state) { PlayerStaminaState = state; }

	void Sprint();

	void StopSprint();

	void InteractWithObject();

	FORCEINLINE void SetWeapon(AWeapon* weapon) { EquippedWeapon = weapon; }

	FORCEINLINE void SetOverlappingPickup(APickup_Base* pickup) { OverlappingPickup = pickup; }

	/**Methods for left mouse button presses*/
	void OnLmbDown();
	void OnLmbUp();
	
	void Attack();

	UFUNCTION(BlueprintCallable)
	void EndAttack();
};
