// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterController.h"
#include "Blueprint/UserWidget.h"

void AMainCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetAsset)
	{
		HUDWidget = CreateWidget<UUserWidget>(this, WidgetAsset);
	}

	HUDWidget->AddToViewport();
	HUDWidget->SetVisibility(ESlateVisibility::Visible);
}
