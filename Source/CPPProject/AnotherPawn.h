// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AnotherPawn.generated.h"

UCLASS()
class CPPPROJECT_API AAnotherPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAnotherPawn();

	void MoveForward(float val);
	void MoveSideward(float val);

	void LookUp(float val);
	void LookSideways(float val);

	UPROPERTY(VisibleAnywhere, Category = "Pawn Movement")
	float ForwVal;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Movement")
	float SideVal;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Movement")
		FVector2D LookRotations;

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

	UPROPERTY(VisibleAnywhere, Category = "Pawn Components")
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Components")
	class USphereComponent* PawnSphere;	//Forward Declaration

	UPROPERTY(VisibleAnywhere, Category = "Pawn Components")
	class UCameraComponent* PawnCamera;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Components")
	class USpringArmComponent* PawnSpringArm;

	//Mesh Setter Getter
	FORCEINLINE UStaticMeshComponent* GetPawnMesh() { return PawnMesh; }
	FORCEINLINE void SetPawnMesh(UStaticMeshComponent* Mesh) { PawnMesh = Mesh; }

	//Sphere Setter Getter
	FORCEINLINE USphereComponent* GetPawnSphere() { return PawnSphere; }
	FORCEINLINE void SetPawnSphere(USphereComponent* Sphere) { PawnSphere = Sphere; }

	FORCEINLINE UCameraComponent* GetPawnCamera() { return PawnCamera; }
	FORCEINLINE void SetPawnMesh(UCameraComponent* Cam) { PawnCamera = Cam; }

	FORCEINLINE USpringArmComponent* GetPawnSpringArm() { return PawnSpringArm; }
	FORCEINLINE void SetPawnMesh(USpringArmComponent* Arm) { PawnSpringArm = Arm; }
};
