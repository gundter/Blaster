// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

class ABlasterGameMode;
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
	void SetHUDAnnouncementCountdown(float CountdownTime);
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void ReceivedPlayer() override; // Sync with server clock as soon as possible
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float GetServerTime(); // Synced with server world clock
	void OnMatchStateSet(FName State);
	void HandleMatchHasStarted();
	void HandleCooldown();
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

	UFUNCTION(Server, Reliable)
	void ServerCheckMatchState();

	UFUNCTION(Client, Reliable)
	void ClientJoinMidGame(FName StateOfMatch, float Warmup, float Match, float StartingTime, float Cooldown);
private:
	UPROPERTY()
	TObjectPtr<ABlasterHUD> BlasterHUD;

	UPROPERTY()
	TObjectPtr<ABlasterGameMode> BlasterGameMode;

	UPROPERTY(ReplicatedUsing = OnRep_MatchState)
	FName MatchState;

	UPROPERTY()
	TObjectPtr<UCharacterOverlay> CharacterOverlay;

	UFUNCTION()
	void OnRep_MatchState();

	float MatchTime = 0.f;
	float WarmupTime = 0.f;
	float CooldownTime = 0.f;
	float LevelStartingTime = 0.f;
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
	bool IsWarmupHUDValid() const;
	bool IsAnnouncementHUDValid() const;
};
