// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BlasterPlayerState.generated.h"

class ABlasterPlayerController;
class ABlasterCharacter;
/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Score() override;
	UFUNCTION()
	virtual void OnRep_Defeats();
	void AddToScore(float ScoreAmount);
	void AddToDefeats(int32 DefeatsAmount);
private:
	UPROPERTY()
	TObjectPtr<ABlasterCharacter> Character;
	UPROPERTY()
	TObjectPtr<ABlasterPlayerController> Controller;

	UPROPERTY(ReplicatedUsing = OnRep_Defeats)
	int32 Defeats;
};
