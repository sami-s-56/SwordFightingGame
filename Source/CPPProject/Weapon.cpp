// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "EnemyCharacter.h"
#include "MainCharacter.h"

AWeapon::AWeapon()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());

	WeaponDamageArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollider"));
	WeaponDamageArea->SetupAttachment(GetRootComponent());

	SetWeaponState(EWeaponState::EWS_Pickup);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponDamageArea->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponOverlap);
	WeaponDamageArea->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnWeaponEndOverlap);
}

void AWeapon::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((GetWeaponState() == EWeaponState::EWS_Pickup) && OtherActor)
	{
		AMainCharacter* player = Cast<AMainCharacter>(OtherActor);
		if (player)
		{
			player -> SetOverlappingPickup(this);
		}
	}
}

void AWeapon::OnPickupEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((GetWeaponState() == EWeaponState::EWS_Pickup) && OtherActor)
	{
		AMainCharacter* player = Cast<AMainCharacter>(OtherActor);
		if (player)
		{
			player->SetOverlappingPickup(nullptr);
		}
	}
}

void AWeapon::Equip(AMainCharacter* character)
{
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	WeaponMesh->SetSimulatePhysics(false);

	if (character) 
	{
		const USkeletalMeshSocket* weaponSocket = character->GetMesh()->GetSocketByName(TEXT("WeaponSocket"));
		if (weaponSocket)
		{
			weaponSocket->AttachActor(this, character->GetMesh());
			SetWeaponState(EWeaponState::EWS_Equiped);
		}
	}
}

void AWeapon::OnWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AActor* OwningActor = this->GetAttachParentActor();
		
		AMainCharacter* PlayerCharacter;
		
		

		AEnemyCharacter* HitCharacter = Cast<AEnemyCharacter>(OtherActor);
		if (HitCharacter)
		{
			if (OwningActor)
			{
				PlayerCharacter = Cast<AMainCharacter>(OwningActor);
				{
					if (PlayerCharacter->bIsAttacking)
					{
						UE_LOG(LogTemp, Warning, TEXT("Other actor is enemy"));
					}
				}

			}
			
			
		}
	}
}

void AWeapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
