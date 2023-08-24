// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

class ABlasterHUD;
/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdownTime(float CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void SetHUDTime();
private:
	UPROPERTY()
	TObjectPtr<ABlasterHUD> BlasterHUD;

	float MatchTime = 120.f;
	uint32 CountdownInt = 0;

	bool IsHUDValid() const;
	bool IsScoreHUDValid() const;
	bool IsDefeatsHUDValid() const;
	bool IsWeaponAmmoHUDValid() const;
	bool IsCarriedAmmoHUDValid() const;
	bool IsCountdownTimeHUDValid() const;
};
