// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBox.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "FirstPawn.h"

// Sets default values
ASpawnBox::ASpawnBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));

}

// Called when the game starts or when spawned
void ASpawnBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnBox::GetRandomPointInArea()
{
	FVector BoxExtent = SpawnBox->GetScaledBoxExtent();
	FVector Origin = SpawnBox->GetComponentLocation();

	FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
	return FVector();
}

void ASpawnBox::SpawnOurPawn_Implementation(UClass* PawnToSpawn, const FVector& Location)
{
	if (PawnToSpawn) 
	{
		UWorld* world = GetWorld();
		FActorSpawnParameters SpawnParams;

		if (world) 
		{
			world->SpawnActor<AFirstPawn>(PawnToSpawn, Location, FRotator(0, 0, 0), SpawnParams);
		}

	}
}

