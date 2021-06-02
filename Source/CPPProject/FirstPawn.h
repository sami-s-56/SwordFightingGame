// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FirstPawn.generated.h"

UCLASS()
class CPPPROJECT_API AFirstPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFirstPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	

	UPROPERTY(EditAnywhere, Category = "Pawn Movement")
		float speed = 100.f;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Variables
	UPROPERTY(EditAnywhere, Category = "Pawn Components")
	USkeletalMeshComponent* PawnMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Pawn Components")
	class UCameraComponent* PawnCamera;	//Forward declaration, means it`s header file can be included at time of initialization

private:

	UPROPERTY(VisibleAnywhere, Category = "Pawn Movement")
	float forwardVal; 

	UPROPERTY(VisibleAnywhere, Category = "Pawn Movement")
	float sideVal;

	UInputComponent* playerInput;
};
