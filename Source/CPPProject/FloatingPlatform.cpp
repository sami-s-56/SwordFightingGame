 // Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = PlatformMesh;

}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	EndLocation += StartLocation; //This will convert end point from Local Space to World Space
	interpSpeed = 1.f;

	bCanInterp = false;
	StartDelay = 1.f;

	Distance = (EndLocation - StartLocation).Size();

	GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterp, StartDelay);

}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanInterp)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector LerpVector = FMath::VInterpTo(CurrentLocation, EndLocation, DeltaTime, interpSpeed);

		SetActorLocation(LerpVector);

		float currentDistance = (EndLocation - CurrentLocation).Size();

		if (currentDistance <= 1.f) 
		{
			ToggleInterp();
			SwapVectors(StartLocation, EndLocation);
			GetWorldTimerManager().SetTimer(InterpTimer, this, &AFloatingPlatform::ToggleInterp, StartDelay);
		}
	}
}

void AFloatingPlatform::ToggleInterp()
{
	bCanInterp = !bCanInterp;
}

void AFloatingPlatform::SwapVectors(FVector& VecA, FVector& VecB) 
{
	FVector VecTemp = VecA;
	VecA = VecB;
	VecB = VecTemp;
}

