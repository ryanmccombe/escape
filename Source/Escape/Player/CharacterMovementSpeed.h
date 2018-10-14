#pragma once

#include "CharacterMovementSpeed.generated.h"

UENUM(BlueprintType)
enum class ECharacterMovementSpeed : uint8 {
	Crouching,
	Walking,
	Running
};