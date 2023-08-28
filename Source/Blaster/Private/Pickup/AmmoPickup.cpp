// Copyright Serico Games


#include "Pickup/AmmoPickup.h"

#include "BlasterComponents/CombatComponent.h"
#include "Character/BlasterCharacter.h"

AAmmoPickup::AAmmoPickup()
{
	
}

void AAmmoPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bSweep, SweepResult);

	if (const ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor))
	{
		if (UCombatComponent* Combat = BlasterCharacter->GetCombatComponent())
		{
			Combat->PickupAmmo(WeaponType, AmmoAmount);
		}
	}
	Destroy();
}
