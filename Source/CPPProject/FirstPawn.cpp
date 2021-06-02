// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFirstPawn::AFirstPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PawnDefaultRoot"));

	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PawnMeshComponent"));
	PawnMesh->SetupAttachment(GetRootComponent());

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCameraComponent"));
	PawnCamera->SetupAttachment(GetRootComponent());
	PawnCamera->SetRelativeLocation(FVector(-300, 0, 300)); //Note that in Unreal, Forward is X, Side is Y and Up is Z
	PawnCamera->SetRelativeRotation(FRotator(-45, 0, 0));

	//AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AFirstPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AFirstPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*forwardVal = playerInput->GetAxisValue(TEXT("Forward"));
	sideVal = playerInput->GetAxisValue(TEXT("Side"));*/

	//Moving
	AddActorLocalOffset(FVector(forwardVal * speed * DeltaTime, sideVal * speed * DeltaTime, 0));

}

// Called to bind functionality to input
void AFirstPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	playerInput = PlayerInputComponent;

	PlayerInputComponent->BindAxis(TEXT("Forward"));
	PlayerInputComponent->BindAxis(TEXT("Side"));
	
}

