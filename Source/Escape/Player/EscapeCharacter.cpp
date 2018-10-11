#include "EscapeCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEscapeCharacter::AEscapeCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	/// COMPONENTS
	MovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	MovementComp->MaxWalkSpeed = WalkingMovementSpeed;

	// Third Person Camera setup for now - TODO: remove this eventually
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// Enable Crouch
	MovementComp->GetNavAgentPropertiesRef().bCanCrouch = true;

	MovementSpeed = ECharacterMovementSpeed::Walking;
}

void AEscapeCharacter::BeginPlay() {
	Super::BeginPlay();
}

void AEscapeCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Direction = FVector(ForwardInput, RightInput, 0.f).Rotation().Yaw;
}

void AEscapeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEscapeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEscapeCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AEscapeCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AEscapeCharacter::Turn);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AEscapeCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AEscapeCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AEscapeCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AEscapeCharacter::EndRun);
}

void AEscapeCharacter::MoveForward(float Value) {
	ForwardInput = Value;
	AddMovementInput(GetActorForwardVector() * Value);
}

void AEscapeCharacter::MoveRight(float Value) {
	RightInput = Value;
	AddMovementInput(GetActorRightVector() * Value);
}

void AEscapeCharacter::LookUp(float Value) {
	AddControllerPitchInput(Value);
}

void AEscapeCharacter::Turn(float Value) {
	AddControllerYawInput(Value);
}

void AEscapeCharacter::StartCrouch() {
	MovementSpeed = ECharacterMovementSpeed::Crouching;
	MovementComp->MaxWalkSpeed = CrouchingMovementSpeed;
	Crouch();
}

void AEscapeCharacter::EndCrouch() {
	MovementSpeed = ECharacterMovementSpeed::Walking;
	MovementComp->MaxWalkSpeed = WalkingMovementSpeed;
	UnCrouch();
}

void AEscapeCharacter::StartRun() {
	MovementSpeed = ECharacterMovementSpeed::Running;
	MovementComp->MaxWalkSpeed = RunningMovementSpeed;
}

void AEscapeCharacter::EndRun() {
	MovementSpeed = ECharacterMovementSpeed::Walking;
	MovementComp->MaxWalkSpeed = WalkingMovementSpeed;
}
