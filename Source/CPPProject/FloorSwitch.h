// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class CPPPROJECT_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	/**Box defining the overlap region*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TriggerComponent")
		class UBoxComponent* TriggerArea;

	/**Mesh of trigger*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TriggerComponent")
		UStaticMeshComponent* TriggerMesh;

	/** Door which will open on this trigger*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TriggerComponent")
		UStaticMeshComponent* DoorMesh;

	UPROPERTY(BlueprintReadOnly, Category = "FloorMechanics")
		FVector InitialDoorLocation;

	UPROPERTY(BlueprintReadOnly, Category = "FloorMechanics")
		FVector InitialFloorLocation;

	UPROPERTY(EditAnywhere ,BlueprintReadOnly, Category = "FloorMechanics")
		float delayTime = 2.f;

	FTimerHandle SwitchTimer;

	bool bIsPlayerOnSwitch;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**Functions to handle overlap events. It is necessary for those functions to have UFUNCTION macro*/

	//Begin Overlap
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//End OVerlap
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ResetDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = FloorMechanics)
	void RaiseDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = FloorMechanics)
	void LowerDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = FloorMechanics)
	void RaiseSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = FloorMechanics)
	void LowerSwitch();

	UFUNCTION(BlueprintCallable, Category = FloorMechanics)
		void UpdateDoorLocation(float z);

	UFUNCTION(BlueprintCallable, Category = FloorMechanics)
		void UpdateSwitchLocation(float z);

};
