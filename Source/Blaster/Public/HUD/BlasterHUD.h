// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlasterHUD.generated.h"

USTRUCT(BlueprintType)
struct FHUDPackage
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UTexture2D> CrosshairCenter;
	
	UPROPERTY()
	TObjectPtr<UTexture2D> CrosshairRight;
	
	UPROPERTY()
	TObjectPtr<UTexture2D> CrosshairLeft;

	UPROPERTY()
	TObjectPtr<UTexture2D> CrosshairTop;

	UPROPERTY()
	TObjectPtr<UTexture2D> CrosshairBottom;
};

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void DrawHUD() override;
private:
	FHUDPackage HUDPackage;
public:
	FORCEINLINE void SetHUDPackage(const FHUDPackage& Package) { HUDPackage = Package; }
};
