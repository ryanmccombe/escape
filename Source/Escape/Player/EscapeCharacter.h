#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EscapeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;

UENUM()
enum class ECharacterMovementSpeed : uint8 {
	Walking,
	Crouching,
	Running
};

UCLASS()
class ESCAPE_API AEscapeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEscapeCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/// COMPONENTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UCharacterMovementComponent* MovementComp;

	/// INPUTS
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void StartCrouch();
	void EndCrouch();
	void StartRun();
	void EndRun();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float ForwardInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float RightInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	ECharacterMovementSpeed MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CrouchingMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkingMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunningMovementSpeed;
};
