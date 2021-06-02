// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "EnemyCharacter.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	EnemyPawn = TryGetPawnOwner();
	if (EnemyPawn)
	{
		EnemyReference = Cast<AEnemyCharacter>(EnemyPawn);
	}
}

void UEnemyAnimInstance::UpdateEnemyMovementVariables()
{
	/** If some how it isn`t initialized in Initialize, then initialize it here*/
	if (EnemyPawn == nullptr)
	{
		EnemyPawn = TryGetPawnOwner();
	}

	if (EnemyPawn)
	{
		FVector Speed = EnemyPawn->GetVelocity();

		//We only want speed from Forward and Side movements, not from Up movement
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);

		//Get Magnitude of Vector
		EnemySpeed = LateralSpeed.Size();
	}
}
