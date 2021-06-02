// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TheObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CPPPROJECT_API UTheObject : public UObject
{
	GENERATED_BODY()

		UTheObject();

private:

	UPROPERTY()
	float MyFloat;

public:
	UFUNCTION(BlueprintCallable)
	void MyFunction();
};
