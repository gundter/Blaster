// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Projectile.h"
#include "ProjectileGrenade.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AProjectileGrenade : public AProjectile
{
	GENERATED_BODY()
public:
	AProjectileGrenade();
	virtual void Destroyed() override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> BounceSound;
};
