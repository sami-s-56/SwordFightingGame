// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROJECT_API AMainCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
		/** Variable to hold it`s reference after widget creation */
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = HUD)
	class UUserWidget* HUDWidget;

	/** Variable to select the widget*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = HUD)
	TSubclassOf<UUserWidget> WidgetAsset;

protected:
	virtual void BeginPlay() override;
};
