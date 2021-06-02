// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CharacterSpringArm->SetupAttachment(GetRootComponent());
	CharacterSpringArm->TargetArmLength = 600.f;
	CharacterSpringArm->bUsePawnControlRotation = true;

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CharacterCamera->SetupAttachment(CharacterSpringArm, CharacterSpringArm->SocketName);
	CharacterCamera->bUsePawnControlRotation = false;

	BaseTurnRate = 50.f;
	BaseLookupRate = 50.f;

	bUseControllerRotationYaw = false; //To ensure that only camera rotates... other rotations are disabled by default (For root of Character)

	GetCharacterMovement()->bOrientRotationToMovement = true;	//Inbuilt function to rotate character to correct direction...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);	// ... at this rate

	Health = 15.f;
	MaxHealth = 100.f;

	Stamina = 90.f;
	MaxStamina = 100.f;
	StaminaChangeRate = 10.f; //10 per second
	MinStamina = 15.f;

	NormalSpeed = 650.f;
	SprintSpeed = 950.f;

	PlayerMovementState = EMovementState::EMS_Idle;
	PlayerStaminaState = EStaminaStates::ESS_Normal;

	bCanSprint = true;
	bIsSprinting = false;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckForIdle();

	//Converting rte from seconds to frames
	float StaminaChangePerFrame = StaminaChangeRate * DeltaTime;
	
	//Handles stamina states based on Stamina value and controls stamina
	HandleStaminaStates(StaminaChangePerFrame);

	//Chekcing for sprinting every frame as Sprint functionality will only be called on button press and release
	ControlSprinting();
}

void AMainCharacter::ControlSprinting()
{
	if (bIsSprinting)
	{
		if (!bCanSprint)
		{
			StopSprint();
		}
	}
}

void AMainCharacter::HandleStaminaStates(float StaminaChangePerFrame)
{
	switch (PlayerStaminaState)
	{
	case EStaminaStates::ESS_Normal:
		if (bIsSprinting && Stamina >= MinStamina)
		{
			Stamina -= StaminaChangePerFrame;
			if (Stamina <= MinStamina)
			{
				PlayerStaminaState = EStaminaStates::ESS_BelowNormal;
				UE_LOG(LogTemp, Warning, TEXT("Switched to BelowNormal"));
			}
		}
		else if (PlayerMovementState == EMovementState::EMS_Idle && Stamina < MaxStamina)
		{
			PlayerStaminaState = EStaminaStates::ESS_Regenerating;
			UE_LOG(LogTemp, Warning, TEXT("Switched to Regenerating"));
		}
		break;
	case EStaminaStates::ESS_BelowNormal:
		if (bIsSprinting && Stamina >= 0.f)
		{
			Stamina -= StaminaChangePerFrame;
			if (Stamina <= 0)
			{
				Stamina = 0;
				PlayerStaminaState = EStaminaStates::ESS_Exhausted;
				UE_LOG(LogTemp, Warning, TEXT("Switched to Exhausted"));
			}
		}
		else if (PlayerMovementState == EMovementState::EMS_Idle)
		{
			PlayerStaminaState = EStaminaStates::ESS_Regenerating;
			UE_LOG(LogTemp, Warning, TEXT("Switched to Regenerating"));
		}
		break;
	case EStaminaStates::ESS_Exhausted:
		bCanSprint = false;
		PlayerStaminaState = EStaminaStates::ESS_Regenerating;
		break;
	case EStaminaStates::ESS_Regenerating:
		if (PlayerMovementState == EMovementState::EMS_Idle && Stamina < MaxStamina)
		{
			if (Stamina < MaxStamina) 
			{
				Stamina += StaminaChangePerFrame;
			}
			if (Stamina >= MinStamina)
				bCanSprint = true;
			if (Stamina > MaxStamina)
				Stamina = MaxStamina;
		}
		else
		{
			if (Stamina >= MinStamina)
			{
				PlayerStaminaState = EStaminaStates::ESS_Normal;
				UE_LOG(LogTemp, Warning, TEXT("Switched to Normal"));
			}
			else if (Stamina > 0)
			{
				PlayerStaminaState = EStaminaStates::ESS_BelowNormal;
				UE_LOG(LogTemp, Warning, TEXT("Switched to BelowNormal"));
			}
			else
			{
				PlayerStaminaState = EStaminaStates::ESS_Exhausted;
				UE_LOG(LogTemp, Warning, TEXT("Switched to Exhausted"));
			}
		}
		break;
	default:
		break;
	}
}

//Check for idleness of player
void AMainCharacter::CheckForIdle()
{
	float forVal = playerInput->GetAxisValue(TEXT("Forward"));
	float sideVal = playerInput->GetAxisValue(TEXT("Side"));

	if (forVal == 0 && sideVal == 0 && !bIsSprinting)
	{
		PlayerMovementState = EMovementState::EMS_Idle;
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	playerInput = PlayerInputComponent;

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Side"), this, &AMainCharacter::MoveSideward);

	PlayerInputComponent->BindAxis(TEXT("LookUpButton"), this, &AMainCharacter::LooupAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookSideButton"), this, &AMainCharacter::TurnAtRate);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSide"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMainCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMainCharacter::StopSprint);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &AMainCharacter::InteractWithObject);

	PlayerInputComponent->BindAction(TEXT("Lmb"), IE_Pressed, this, &AMainCharacter::OnLmbDown);
	PlayerInputComponent->BindAction(TEXT("Lmb"), IE_Released, this, &AMainCharacter::OnLmbUp);
}

//These movement code will only move the character in forward direction with respect to camera rotaion...
//... but it will not rotate the character
void AMainCharacter::MoveForward(float val)
{
	if (Controller != nullptr && val != 0 && !bIsAttacking) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	//Get forward direction from rotation vector
		AddMovementInput(Direction, val);

		if (!bIsSprinting)
		{
			SetMovementState(EMovementState::EMS_Normal);
		}
	}
}

void AMainCharacter::MoveSideward(float val)
{
	if (Controller != nullptr && val != 0 && !bIsAttacking)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);	//Get forward direction from rotation vector
		AddMovementInput(Direction, val);

		if (!bIsSprinting)
		{
			SetMovementState(EMovementState::EMS_Normal);
		}
	}
}

void AMainCharacter::TurnAtRate(float turnRate)
{
	AddControllerYawInput(turnRate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LooupAtRate(float lookUpRate)
{
	AddControllerPitchInput(lookUpRate * BaseLookupRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::SetMovementState(EMovementState state)
{
	PlayerMovementState = state;
	switch (state)
	{
	case EMovementState::EMS_Normal:
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;	//Setting the value of character class variable
		//UE_LOG(LogTemp, Warning, TEXT("Actually Moving"));
		break;
	case EMovementState::EMS_Sprinting:
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		//UE_LOG(LogTemp, Warning, TEXT("Actually Sprinting"));
		break;
	default:
		break;
	}
}

void AMainCharacter::Sprint()
{
	if (bCanSprint && PlayerMovementState != EMovementState::EMS_Idle)
	{
		SetMovementState(EMovementState::EMS_Sprinting);
		bIsSprinting = true;
	}
	else
	{
		//SetMovementState(EMovementState::EMS_Normal);
		bIsSprinting = false;
	}
}

void AMainCharacter::StopSprint()
{
	bIsSprinting = false;
	SetMovementState(EMovementState::EMS_Normal);
}

void AMainCharacter::InteractWithObject() 
{
	if (OverlappingPickup)
	{
		if (EquippedWeapon) 
		{
			EquippedWeapon->Destroy();
		}
		AWeapon* weapon = Cast<AWeapon>(OverlappingPickup);
		if (weapon)
		{
			weapon->Equip(this);
			EquippedWeapon = weapon;
			OverlappingPickup = nullptr;
		}
	}
}

void AMainCharacter::OnLmbDown()
{
	if (EquippedWeapon)
	{
		Attack();
	}
}

void AMainCharacter::OnLmbUp()
{
	
}

void AMainCharacter::Attack()
{
	if (!bIsAttacking)
	{
		bIsAttacking = true;
		UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
		if (AnimInst && CombatMontage)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attacking"));
			AnimInst->Montage_Play(CombatMontage, 2.0);
			AnimInst->Montage_JumpToSection(FName("Attack_1"), CombatMontage);
		}
	}
	else
	{
		if (!bIsComboActive)
		{
			bIsComboActive = true;
			UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
			if (AnimInst && CombatMontage)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Attacking"));
				AnimInst->Montage_Play(CombatMontage, 1.5);
				AnimInst->Montage_JumpToSection(FName("Attack_2"), CombatMontage);
			}
		}
	}
	
}

void AMainCharacter::EndAttack()
{
	bIsAttacking = false;
	bIsComboActive = false;
}

