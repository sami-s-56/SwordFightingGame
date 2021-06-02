// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr) 
	{
		Pawn = TryGetPawnOwner();
	}

	if(Pawn)
	{
		PlayerCharacter = Cast<AMainCharacter>(Pawn);
	}
}

void UCharacterAnimInstance::UpdateMovementVariables()
{
	/** If some how it isn`t initialized in Initialize, then initialize it here*/
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();

		//We only want speed from Forward and Side movements, not from Up movement
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);

		//Get Magnitude of Vector
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
	}
}