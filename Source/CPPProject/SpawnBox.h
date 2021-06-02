// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBox.generated.h"

UCLASS()
class CPPPROJECT_API ASpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnBox();

	UPROPERTY(EditAnywhere, Category = SpawnBox)
	class UBoxComponent* SpawnBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = SpawnObject)
	TSubclassOf<class AFirstPawn> SpawnObject;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = SpawnPoint)
	FVector GetRandomPointInArea();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = SpawnObject)
	void SpawnOurPawn(UClass* PawnToSpawn, const FVector& Location);
};
