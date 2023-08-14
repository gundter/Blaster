// Copyright Serico Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class BLASTER_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DisplayText;

	void SetDisplayText(const FString& TextToDisplay) const;

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(const APawn* InPawn) const;
protected:
	virtual void NativeDestruct() override;
};
