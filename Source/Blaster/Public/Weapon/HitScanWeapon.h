// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "HitScanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AHitScanWeapon : public AWeapon
{
	GENERATED_BODY()
public:
	AHitScanWeapon();
	virtual void Fire(const FVector& HitTarget) override;
protected:
	virtual FVector TraceEndWithScatter(const FVector& TraceStart, const FVector& HitTarget);
private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UParticleSystem> ImpactParticles;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UParticleSystem> BeamParticles;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UParticleSystem> MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USoundBase> FireSound;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<USoundBase> HitSound;

	/*
	 * Trace end with scatter
	 */
	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float DistanceToSphere = 800.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	float SphereRadius = 75.f;

	UPROPERTY(EditAnywhere, Category = "Weapon Scatter")
	bool bUseScatter = false;
	
};
