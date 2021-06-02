// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AIController.h"
#include "MainCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LookRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Look Range"));
	LookRangeSphere->SetupAttachment(GetRootComponent());
	LookRangeSphere->SetSphereRadius(750.f);

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Range"));
	AttackRangeSphere->SetupAttachment(GetRootComponent());
	AttackRangeSphere->SetSphereRadius(100.f);

	EnemyWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	

	USkeletalMeshComponent* EnemyMesh = this->GetMesh();
	const USkeletalMeshSocket* EnemySocket = this->GetMesh()->GetSocketByName("RightHandSocket");

	if (EnemyMesh && EnemySocket) 
	{
		EnemyWeapon->SetupAttachment(EnemyMesh, EnemySocket->GetFName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid EnemyMesh or Socket"));
	}
	
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyController = Cast<AAIController>(GetController());

	LookRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnLookRangeOverlap);
	LookRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnLookRangeEndOverlap);

	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnAttackRangeOverlap);
	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnAttackRangeEndOverlap);


	//EnemyWeapon->Attach
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnLookRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			MoveToTarget(PlayerCharacter);
		}
	}
}

void AEnemyCharacter::OnLookRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			EnemyController->StopMovement();
		}
	}
}

void AEnemyCharacter::OnAttackRangeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			SetEnemyState(EEnemyStates::ES_Attaking);
		}
	}
}

void AEnemyCharacter::OnAttackRangeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(OtherActor);
		if (PlayerCharacter)
		{
			SetEnemyState(EEnemyStates::ES_Moving);
			MoveToTarget(PlayerCharacter);
		}
	}
}

void AEnemyCharacter::MoveToTarget(AMainCharacter* Player) 
{

	SetEnemyState(EEnemyStates::ES_Moving);

	if (Player)
	{
		/*FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Player);
		MoveRequest.SetAcceptanceRadius(AttackRangeSphere->GetScaledSphereRadius());

		FNavPathSharedPtr NavPointer;

		if (EnemyController)
		{
			EnemyController->MoveTo(MoveRequest, &NavPointer);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Problem with enemy controller"));
		}*/

		//UE_LOG(LogTemp, Warning, TEXT("Should move now"));
		
		EnemyController->MoveToActor(Player, 10.f);
	}
}

