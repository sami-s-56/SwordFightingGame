// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerArea;

	TriggerArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);	//Collision Type
	TriggerArea->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic); //Collision Profile
	TriggerArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);	//How it should respond to all collision
	TriggerArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap); //How it should respond to perticular collision type

	TriggerArea->SetGenerateOverlapEvents(true);

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerMesh"));
	TriggerMesh->SetupAttachment(GetRootComponent());

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapBegin);
	TriggerArea->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::OnOverlapEnd);

	InitialDoorLocation = DoorMesh->GetComponentLocation();
	InitialFloorLocation = TriggerMesh->GetComponentLocation();
}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFloorSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Entered"));

	bIsPlayerOnSwitch = true;

	RaiseDoor();
	LowerSwitch();
}

void AFloorSwitch::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Left"));
	bIsPlayerOnSwitch = false;
	GetWorldTimerManager().SetTimer(SwitchTimer, this, &AFloorSwitch::ResetDoor, delayTime);
}

void AFloorSwitch::ResetDoor()
{
	if (!bIsPlayerOnSwitch) 
	{
		LowerDoor();
		RaiseSwitch();
	}
	
}

void AFloorSwitch::UpdateDoorLocation(float z)
{
	FVector NextLocation = InitialDoorLocation;
	NextLocation.Z += z;
	DoorMesh->SetWorldLocation(NextLocation);
}

void AFloorSwitch::UpdateSwitchLocation(float z)
{
	FVector NextLocation = InitialFloorLocation;
	NextLocation.Z += z;
	TriggerMesh->SetWorldLocation(NextLocation);
}

