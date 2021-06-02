 // Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup_Base.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
APickup_Base::APickup_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/** Collider Setup */
	PickupCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PickupArea"));
	RootComponent = PickupCollider;

	PickupCollider->OnComponentBeginOverlap.AddDynamic(this, &APickup_Base::OnPickupOverlap);
	PickupCollider->OnComponentEndOverlap.AddDynamic(this, &APickup_Base::OnPickupEndOverlap);

	PickupCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	PickupCollider->SetGenerateOverlapEvents(true);

	/**Mesh Setup*/
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(GetRootComponent());

	/**ParticleSystem Setup*/
	PickupParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PickupParticle"));
	PickupParticle->SetupAttachment(GetRootComponent());

	bCanRotate = false;
	RotationRate = 45.f;

}

// Called when the game starts or when spawned
void APickup_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanRotate) 
	{
		PickupMesh->AddLocalRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
	}
}

void APickup_Base::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Base pickup Overlap"));

	if (TriggerParticle) 
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TriggerParticle, GetActorLocation(), FRotator(0.f), true);
	}

	if (TriggerSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), TriggerSound);
	}

	
}

void APickup_Base::OnPickupEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Base pickup End Overlap"));
}

