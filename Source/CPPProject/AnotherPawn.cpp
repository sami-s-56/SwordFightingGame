// Fill out your copyright notice in the Description page of Project Settings.


#include "AnotherPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"


// Sets default values
AAnotherPawn::AAnotherPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//Pawn Sphere setup
	PawnSphere = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	PawnSphere->InitSphereRadius(50.f);	//Setting Radius of sphere
	PawnSphere->SetCollisionProfileName(TEXT("Pawn"));	//Setting its collision profile
	PawnSphere->SetupAttachment(GetRootComponent());

	//PawnMesh Setup
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	PawnMesh->SetupAttachment(GetRootComponent());
	//Adding Mesh from code
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshComponentAsset.Succeeded()) 
	{
		PawnMesh->SetStaticMesh(MeshComponentAsset.Object);
	}
	PawnMesh->SetRelativeLocation(FVector(0, 0, -50));

	//Pawn SpringArm Setup
	PawnSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PawnSpringArm->SetupAttachment(GetRootComponent());
	PawnSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	PawnSpringArm->TargetArmLength = 300.f;
	PawnSpringArm->CameraLagSpeed = 5.f;

	//Pawn Camera Setup
	PawnCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	PawnCamera->SetupAttachment(PawnSpringArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AAnotherPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAnotherPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += LookRotations.X;
	SetActorRotation(NewRotation);

	FRotator NewSpringArmRotation = PawnSpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += LookRotations.Y, -80.f, 20.f);
	PawnSpringArm->SetWorldRotation(NewSpringArmRotation);

	AddActorLocalOffset(FVector(ForwVal * DeltaTime * speed, SideVal * DeltaTime * speed, 0));
}

// Called to bind functionality to input
void AAnotherPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AAnotherPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Side"), this, &AAnotherPawn::MoveSideward);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AAnotherPawn::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookSide"), this, &AAnotherPawn::LookSideways);

}

void AAnotherPawn::MoveForward(float val) 
{
	ForwVal = val;
}

void AAnotherPawn::MoveSideward(float val) 
{
	SideVal = val;
}

void AAnotherPawn::LookUp(float val)
{
	LookRotations.Y = val;
}

void AAnotherPawn::LookSideways(float val)
{
	LookRotations.X = val;
}
