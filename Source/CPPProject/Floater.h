// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class CPPPROJECT_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* FloaterStaticMesh;

	//Location of actor when beginplay is called
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Vectors")
	FVector InitialPosition = FVector(0);

	//Location of actor where we need to place
	UPROPERTY(VisibleInstanceOnly ,BlueprintReadWrite, Category = "Floater Vectors")
	FVector PlacingPosition = FVector(0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	bool bIsInitialized = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	bool bCanFloat = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
	FVector InitialDirection;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Floater Forces")
	FVector InitialForce;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Floater Forces")
	FVector InitialTorque;

private:
	float RunningTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
