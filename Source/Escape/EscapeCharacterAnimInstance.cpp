#include "EscapeCharacterAnimInstance.h"
#include "Player/EscapeCharacter.h"

void UEscapeCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds) {
	Super::NativeUpdateAnimation(DeltaSeconds);
	UpdateAnimationProperties();
}

void UEscapeCharacterAnimInstance::UpdateAnimationProperties() {
	auto Character = Cast<AEscapeCharacter>(TryGetPawnOwner());

	if (Character) {
		MovementSpeed = Character->GetMovementSpeed();
		Speed = Character->GetVelocity().Size();
		ForwardInput = Character->GetForwardInput();
		RightInput = Character->GetRightInput();
		Direction = Character->GetDirection();
		bHasReceivedInput = FMath::Abs<float>(ForwardInput) > 0 || FMath::Abs<float>(RightInput) > 0;
		if (bHasReceivedInput) {
			LastInputDirection = Direction;
		}
	}
}
