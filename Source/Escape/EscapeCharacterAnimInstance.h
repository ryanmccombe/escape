#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player/CharacterMovementSpeed.h"
#include "EscapeCharacterAnimInstance.generated.h"

UCLASS()
class ESCAPE_API UEscapeCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ForwardInput;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RightInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHasReceivedInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LastInputDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECharacterMovementSpeed MovementSpeed;
};
