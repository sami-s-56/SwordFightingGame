// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Required to create sub objects of Actor
	FloaterStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloaterMesh"));
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();
	/*PlacingPosition = GetActorLocation();
	if (bIsInitialized)
	{
		SetActorLocation(InitialPosition);
	}*/

	//FloaterStaticMesh->AddForce(InitialForce);
	//FloaterStaticMesh->AddTorque(InitialTorque);
	
	RunningTime = 0;
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanFloat)
	{
		//AddActorLocalOffset(InitialDirection, false, nullptr);	//Local Direction
		//AddActorWorldOffset(InitialDirection, false, nullptr);	//World Direction
		
		
		//float roatatingVal = FMath::Sin(RunningTime);
		float movingVal = FMath::Cos(RunningTime);

		RunningTime += DeltaTime;

		/*FRotator rotation = GetActorRotation();

		rotation.Pitch += roatatingVal;

		SetActorRotation(rotation);*/

		FVector pos = GetActorLocation();
		pos.X += movingVal;

		SetActorLocation(pos);
	}

}

