// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROJECT_API UEnemyAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animations)
	APawn* EnemyPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	class AEnemyCharacter* EnemyReference;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animations)
	float EnemySpeed;
	
	UFUNCTION(BlueprintCallable, Category = Animations)
	void UpdateEnemyMovementVariables();

};
