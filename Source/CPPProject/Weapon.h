// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup_Base.h"
#include "Weapon.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum  class EWeaponState : uint8
{
	EWS_Pickup UMETA(DisplayName = "Pickup"),
	EWS_Equiped UMETA(DisplayName = "Equiped"),

	EWS_MAX UMETA(DisplayName = "Default")
};

UCLASS()
class CPPPROJECT_API AWeapon : public APickup_Base
{
	GENERATED_BODY()

public:

	AWeapon();

	/** Variables */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Pickups")
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Pickups | Weapons")
	EWeaponState WeaponState;

	//Different weapons may have different damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Pickups | Weapons")
	float Damage;

	//Collider which will check and apply damage on overlap
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Pickups")
	class UBoxComponent* WeaponDamageArea;

protected:
	virtual void BeginPlay() override;

public:
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnPickupEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void Equip(class AMainCharacter* character);

	FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }
	FORCEINLINE void SetWeaponState(EWeaponState state) { WeaponState = state; }

	UFUNCTION()
	void OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

