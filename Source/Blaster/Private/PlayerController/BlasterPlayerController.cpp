// Copyright Serico Games


#include "PlayerController/BlasterPlayerController.h"

#include "Character/BlasterCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HUD/BlasterHUD.h"
#include "HUD/CharacterOverlay.h"

void ABlasterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	BlasterHUD = Cast<ABlasterHUD>(GetHUD());
}

void ABlasterPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(InPawn))
	{
		SetHUDHealth(BlasterCharacter->GetHealth(), BlasterCharacter->GetMaxHealth());
	}
}

void ABlasterPlayerController::SetHUDHealth(const float Health, const float MaxHealth)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;
	
	if (IsHUDValid())
	{
		const float HealthPercent = Health / MaxHealth;
		BlasterHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		const FString HealthText = FString::Printf(TEXT("%d/%d"), FMath::CeilToInt(Health), FMath::CeilToInt(MaxHealth));
		BlasterHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void ABlasterPlayerController::SetHUDScore(const float Score)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

	if (IsScoreHUDValid())
	{
		BlasterHUD->CharacterOverlay->ScoreAmount->SetText(FText::AsNumber(FMath::FloorToInt(Score)));
	}
}

void ABlasterPlayerController::SetHUDDefeats(const int32 Defeats)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

	if (IsDefeatsHUDValid())
	{
		BlasterHUD->CharacterOverlay->DefeatsAmount->SetText(FText::AsNumber(Defeats));
	}
}



void ABlasterPlayerController::SetHUDWeaponAmmo(const int32 Ammo)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

	if (IsWeaponAmmoHUDValid())
	{
		BlasterHUD->CharacterOverlay->WeaponAmmoAmount->SetText(FText::AsNumber(Ammo));
	}
}

void ABlasterPlayerController::SetHUDCarriedAmmo(const int32 Ammo)
{
	BlasterHUD = BlasterHUD == nullptr ? Cast<ABlasterHUD>(GetHUD()) : BlasterHUD;

	if (IsCarriedAmmoHUDValid())
	{
		BlasterHUD->CharacterOverlay->CarriedAmmoAmount->SetText(FText::AsNumber(Ammo));
	}
}

bool ABlasterPlayerController::IsHUDValid() const
{
	return BlasterHUD &&
		BlasterHUD->CharacterOverlay &&
			BlasterHUD->CharacterOverlay->HealthBar &&
				BlasterHUD->CharacterOverlay->HealthText;
}

bool ABlasterPlayerController::IsScoreHUDValid() const
{
	return BlasterHUD &&
		BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->ScoreAmount;
}

bool ABlasterPlayerController::IsDefeatsHUDValid() const
{
	return BlasterHUD &&
		BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->DefeatsAmount;
}

bool ABlasterPlayerController::IsWeaponAmmoHUDValid() const
{
	return BlasterHUD &&
		BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->WeaponAmmoAmount;
}

bool ABlasterPlayerController::IsCarriedAmmoHUDValid() const
{
	return BlasterHUD &&
		BlasterHUD->CharacterOverlay &&
		BlasterHUD->CharacterOverlay->CarriedAmmoAmount;
}
