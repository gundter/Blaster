// Copyright Serico Games


#include "Character/BlasterAnimInstance.h"

#include "Character/BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (BlasterCharacter == nullptr)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}
}

void UBlasterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (BlasterCharacter == nullptr) return;

	Velocity = BlasterCharacter->GetVelocity();
	GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
	bIsFalling = BlasterCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = GroundSpeed > 3.f && BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration() != FVector::ZeroVector;
}
