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
	bool IsScoreHUDValid() const;
	void SetHUDScore(float Score);
	virtual void OnPossess(APawn* InPawn) override;
protected:
	virtual void BeginPlay() override;
	bool IsHUDValid() const;

private:
	TObjectPtr<ABlasterHUD> BlasterHUD;
};
