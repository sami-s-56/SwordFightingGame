// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class CPPPROJECT_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = Mesh)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PositionVectors)
		FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PositionVectors, meta = (MakeEditWidget = "true"))	//Created a widget in editor
		FVector EndLocation;

	UPROPERTY(EditAnywhere, Category = Interpolation)
		float interpSpeed;

	UPROPERTY(EditAnywhere, Category = Interpolation)
		float StartDelay; //Time after which the movement should begin

	UPROPERTY(VisibleAnywhere, Category = Interpolation)
		bool bCanInterp; 

	FTimerHandle InterpTimer;
	float Distance;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleInterp();

	void SwapVectors(FVector& VecA, FVector& VecB);

};
