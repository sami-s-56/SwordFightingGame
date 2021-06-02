// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemyStates : uint8 {
	ES_Idle UMETA(DisplayName = "Idle"),
	ES_Moving UMETA(DisplayName = "MovingToTarget"),
	ES_Attaking UMETA(DisplayName = "Attacking"),

	ES_MAX UMETA(DisplayName = "Default")
};

UCLASS()
class CPPPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animations")
	EEnemyStates EnemyState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		class USphereComponent* LookRangeSphere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
		class USphereComponent* AttackRangeSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
		class AAIController* EnemyController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons")
		class UStaticMeshComponent* EnemyWeapon;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetEnemyState(EEnemyStates state) { EnemyState = state; }

	UFUNCTION()
	virtual void OnLookRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnLookRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnAttackRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void MoveToTarget(class AMainCharacter* Player);


};
