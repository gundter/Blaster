// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/CombatState.h"
#include "Components/ActorComponent.h"
#include "HUD/BlasterHUD.h"
#include "CombatComponent.generated.h"

class AProjectile;
enum class EWeaponType : uint8;
class ABlasterHUD;
class ABlasterPlayerController;
class AWeapon;
class ABlasterCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend ABlasterCharacter;
	UCombatComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void EquipWeapon(AWeapon* WeaponToEquip);
	void Reload();
	void FireButtonPressed(const bool bPressed);
	void JumpToShotgunEnd() const;
	void PickupAmmo(EWeaponType WeaponType, int32 AmmoAmount);
	
	UFUNCTION(BlueprintCallable)
	void FinishReloading();

	UFUNCTION(BlueprintCallable)
	void GrabMag();

	UFUNCTION(BlueprintCallable)
	void ReleaseMag();

	UFUNCTION(BlueprintCallable)
	void ShotgunShellReload();

	UFUNCTION(BlueprintCallable)
	void ThrowGrenadeFinished();

	UFUNCTION(BlueprintCallable)
	void LaunchGrenade();

	UFUNCTION(Server, Reliable)
	void ServerLaunchGrenade(const FVector_NetQuantize& Target);

protected:
	virtual void BeginPlay() override;
	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(const bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon() const;

	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastFire(const FVector_NetQuantize& TraceHitTarget);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastGrabMag();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastReleaseMag();

	UFUNCTION(Server, Reliable)
	void ServerReload();

	UFUNCTION(Server, Reliable)
	void ServerThrowGrenade();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> GrenadeClass;

	void HandleReload();
	int32 AmountToReload();
	void TraceUnderCrosshair(FHitResult& TraceHitResult);
	void Fire();
	void SetHUDCrosshair(float DeltaTime);
	void ThrowGrenade();
	void DropEquippedWeapon() const;
	void AttachActorToRightHand(AActor* ActorToAttach) const;
	void AttachActorToLeftHand(AActor* ActorToAttach) const;
	void UpdateCarriedAmmo();
	void PlayEquipWeaponSound() const;
	void ReloadEmptyWeapon();
	void ShowAttachedGrenade(bool bShowGrenade) const;
private:
	UPROPERTY()
	TObjectPtr<ABlasterCharacter> Character;

	UPROPERTY()
	TObjectPtr<ABlasterPlayerController> Controller;

	UPROPERTY()
	TObjectPtr<ABlasterHUD> HUD;
	
	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	TObjectPtr<AWeapon> EquippedWeapon;

	UPROPERTY(Replicated)
	bool bAiming;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeed = 480.f;
	
	UPROPERTY(EditAnywhere)
	float AimWalkSpeed = 120.f;

	UPROPERTY(EditAnywhere)
	float BaseWalkSpeedCrouched = 300.f;
	
	UPROPERTY(EditAnywhere)
	float AimWalkSpeedCrouched = 120.f;

	bool bFireButtonPressed;

	UPROPERTY(ReplicatedUsing = OnRep_MagTransform, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FTransform MagTransform;

	FVector_NetQuantize HitTarget;

	UFUNCTION()
	void OnRep_MagTransform();

	/*
	 * HUD and Crosshair
	 */
	float CrosshairVelocityFactor;
	float CrosshairInAirFactor;
	float CrosshairAimFactor;
	float CrosshairShootingFactor;
	FHUDPackage HUDPackage;

	/*
	 * Aiming and FOV
	 */
	// Field of view when not aiming; set to the camera's base FOV in BeginPlay
	float DefaultFOV;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ZoomedFOV = 30.f;

	float CurrentFOV;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ZoomInterpSpeed = 20.f;

	void InterpFOV(float DeltaTime);

	/*
	 * Automatic Fire
	 */
	FTimerHandle FireTimer;
	bool bCanFire = true;
	
	void StartFireTimer();
	void FireTimerFinished();
	bool CanFire() const;

	// Carried ammo for the currently-equipped weapon
	UPROPERTY(ReplicatedUsing = OnRep_CarriedAmmo)
	int32 CarriedAmmo;

	TMap<EWeaponType, int32> CarriedAmmoMap;

	UPROPERTY(EditAnywhere)
	int32 MaxCarriedAmmo = 500;

	UPROPERTY(EditAnywhere)
	int32 StartingARAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingRocketAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingPistolAmmo = 0;
	
	UPROPERTY(EditAnywhere)
	int32 StartingSMGAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingShotgunAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingSniperRifleAmmo = 0;

	UPROPERTY(EditAnywhere)
	int32 StartingGrenadeLauncherAmmo = 0;

	UPROPERTY(ReplicatedUsing = OnRep_Grenades)
	int32 Grenades = 4;

	UFUNCTION()
	void OnRep_Grenades();

	void UpdateHUDGrenades();

	UPROPERTY(EditAnywhere)
	int32 MaxGrenades = 4;
	
	void InitializeCarriedAmmo();
	void UpdateAmmoValues();
	void UpdateShotgunAmmoValues();

	UFUNCTION()
	void OnRep_CarriedAmmo();

	UPROPERTY(ReplicatedUsing = OnRep_CombatState)
	ECombatState CombatState = ECombatState::ECS_Unoccupied;

	UFUNCTION()
	void OnRep_CombatState();
public:
	FORCEINLINE int32 GetGrenades() const { return Grenades; }
};
