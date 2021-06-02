// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup_Base.generated.h"

UCLASS()
class CPPPROJECT_API APickup_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup_Base();

	UPROPERTY(EditDefaultsOnly, Category = Pickup)
		class USphereComponent* PickupCollider;

	UPROPERTY(EditAnywhere, Category = Pickups)
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, Category = Pickup)
		class UParticleSystemComponent* PickupParticle;

	UPROPERTY(EditAnywhere, Category = Pickup)
		class UParticleSystem* TriggerParticle;

	UPROPERTY(EditAnywhere, Category = Pickup)
		class USoundBase* TriggerSound;

	UPROPERTY(EditAnywhere, Category = Pickup)
		bool bCanRotate;
		
	UPROPERTY(EditAnywhere, Category = Pickup)
		float RotationRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnPickupEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
