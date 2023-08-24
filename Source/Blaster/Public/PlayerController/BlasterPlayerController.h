// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

class UCharacterOverlay;
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
	virtual void Tick(float DeltaSeconds) override;
	virtual void ReceivedPlayer() override; // Sync with server clock as soon as possible
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float GetServerTime(); // Synced with server world clock
	void OnMatchStateSet(FName State);
protected:
	virtual void BeginPlay() override;
	void CheckTimeSync(float DeltaSeconds);
	void SetHUDTime();
	void PollInit();

	/*
	 * Sync time between client and server
	 */
	// Requests the current server time, passing in the client's time when the request was sent
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfClientRequest);

	// Reports the current server time to the client in response to ServerRequestServerTime
	UFUNCTION(Client, Reliable)
	void ClientReportServerTime(float TimeOfClientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f; // difference between client and server time
	float TimeSyncRunningTime = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Time")
	float TimeSyncFrequency = 5.f;
private:
	UPROPERTY()
	TObjectPtr<ABlasterHUD> BlasterHUD;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;

	UPROPERTY()
	TObjectPtr<UCharacterOverlay> CharacterOverlay;

	UFUNCTION()
	void OnRep_MatchState();

	float MatchTime = 120.f;
	uint32 CountdownInt = 0;
	bool bInitializeCharacterOverlay = false;
	float HUDHealth;
	float HUDMaxHealth;
	float HUDScore;
	int32 HUDDefeats;

	bool IsHUDValid() const;
	bool IsScoreHUDValid() const;
	bool IsDefeatsHUDValid() const;
	bool IsWeaponAmmoHUDValid() const;
	bool IsCarriedAmmoHUDValid() const;
	bool IsCountdownTimeHUDValid() const;
};
