// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractWithCrosshairInterface.h"
#include "BlasterCharacter.generated.h"

enum class ECombatState : uint8;
class ABlasterPlayerState;
class ABlasterPlayerController;
enum class ETurningInPlace : uint8;
class UCombatComponent;
class AWeapon;
class UWidgetComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter, public IInteractWithCrosshairInterface
{
	GENERATED_BODY()

public:
	ABlasterCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	virtual void OnRep_ReplicatedMovement() override;
	virtual void Destroyed() override;
	void PlayFireMontage(bool bAiming) const;
	void PlayReloadMontage() const;
	void PlayElimMontage();
	void ElimPlayer();

	UPROPERTY(Replicated)
	bool bDisableGameplay = false;

	UFUNCTION()
	void OnRep_HandSceneComponent() const;
	
	UFUNCTION(NetMulticast, Reliable)
	void MulticastElim();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowSniperScopeWidget(bool bShowScope);
protected:
	virtual void BeginPlay() override;
	virtual void Jump() override;
	void CalculateAO_Pitch();
	void AimOffset(float DeltaTime);
	void SimProxiesTurn();
	void PlayHitReactMontage() const;
	void RotateInPlace(float DeltaTime);
	// Poll for any relevant classes and initialize our HUD
	void PollInit();

	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser);
	void UpdateHUDHealth();
	/**
	 * Input Callbacks
	 */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Equip();
	void ToggleCrouch();
	void AimButtonPressed();
	void AimButtonReleased();
	void FireButtonPressed();
	void FireButtonReleased();
	void Reload();
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> EquipAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> OverheadWidget;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	TObjectPtr<AWeapon> OverlappingWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCombatComponent> Combat;

	/*
	 * Animation montages
	 */
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> FireWeaponMontage;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> AimFireWeaponMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> ReloadMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> ElimMontage;

	UPROPERTY(ReplicatedUsing = OnRep_HandSceneComponent, BlueprintReadOnly,  Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> HandSceneComponent;

	UPROPERTY(EditAnywhere)
	float CameraThreshold = 200.f;

	UPROPERTY()
	TObjectPtr<ABlasterPlayerState> BlasterPlayerState;
	
	float AO_Yaw;
	float InterpAO_Yaw;
	float AO_Pitch;
	FRotator StartingAimRotation;
	ETurningInPlace TurningInPlace = ETurningInPlace::ETIP_NotTurning;
	bool bRotateRootBone;
	float TurnThreshold = 15.f;
	float ProxyYaw;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float TimeSinceLastMovementReplication;

	UFUNCTION()
	void OnRep_OverlappingWeapon(const AWeapon* LastWeapon) const;

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	void TurnInPlace(float DeltaTime);
	void HideCharacterIfCameraClose() const;
	float CalculateSpeed() const;

	/*
	 * Player Health
	 */
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Health, Category = "Player Stats")
	float Health = 100.f;
	
	UFUNCTION()
	void OnRep_Health();
	
	UPROPERTY()
	TObjectPtr<ABlasterPlayerController> BlasterPlayerController;
	bool bElimmed = false;
	
	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;
	FTimerHandle ElimTimer;
	void ElimTimerFinished();
	
public:
	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }
	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }
	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE bool ShouldRotateRootBone() const { return bRotateRootBone; }
	FORCEINLINE bool IsElimmed() const { return bElimmed; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE USceneComponent* GetHandSceneComponent() const { return HandSceneComponent; }
	FORCEINLINE UCombatComponent* GetCombatComponent() const { return Combat; }
	FORCEINLINE bool GetDisableGameplay() const { return bDisableGameplay; }
	bool IsWeaponEquipped() const;
	bool IsAiming() const;
	AWeapon* GetEquippedWeapon() const;
	ECombatState GetCombatState() const;
	
	void SetOverlappingWeapon(AWeapon* Weapon);
};
