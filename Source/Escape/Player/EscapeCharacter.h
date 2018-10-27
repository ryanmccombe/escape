#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/CharacterMovementSpeed.h"
#include "EscapeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCharacterMovementComponent;

UCLASS()
class ESCAPE_API AEscapeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEscapeCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/// GETTERS
	float GetDirection() const;
	float GetForwardInput() const;
	float GetRightInput() const;
	ECharacterMovementSpeed GetMovementSpeed() const;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	bool bIsCarryingObjective;

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


	/// VALUES CALCULATED FROM INPUTS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float ForwardInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float RightInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	float Direction;


	/// MOVEMENT MODES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	ECharacterMovementSpeed MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float CrouchingMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkingMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunningMovementSpeed;
};
