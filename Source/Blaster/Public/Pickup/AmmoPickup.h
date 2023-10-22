// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "Pickup/Pickup.h"
#include "Weapon/WeaponTypes.h"
#include "AmmoPickup.generated.h"

enum class EWeaponType : uint8;
/**
 * 
 */
UCLASS()
class BLASTER_API AAmmoPickup : public APickup
{
	GENERATED_BODY()
public:
	AAmmoPickup();
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& SweepResult) override;
private:
	UPROPERTY(EditAnywhere)
	int32 AmmoAmount = 30;

	UPROPERTY(EditAnywhere)
	EWeaponType WeaponType = EWeaponType::EWT_MAX;
};
