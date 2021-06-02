// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "MainCharacter.h"

AHealthPickup::AHealthPickup() 
{
	
}

void AHealthPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	if (OtherActor) 
	{
		AMainCharacter* player = Cast<AMainCharacter>(OtherActor);
		if (player)
		{
			if (player->Health + 10.f < player->MaxHealth) 
			{
				player->Health += 10.f;
			}
			else
			{
				player->Health = player->MaxHealth;
			}
		}
	}

	Destroy();

}

void AHealthPickup::OnPickupEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnPickupEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("Health End Overlap"));
}
