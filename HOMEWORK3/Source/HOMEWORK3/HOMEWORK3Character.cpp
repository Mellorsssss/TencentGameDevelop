// Copyright Epic Games, Inc. All Rights Reserved.

#include "HOMEWORK3Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AHOMEWORK3Character

AHOMEWORK3Character::AHOMEWORK3Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	bCrouching = false;
}

FVector AHOMEWORK3Character::GetPawnViewLocation() const
{
	if (FollowCamera) {
		return FollowCamera->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHOMEWORK3Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHOMEWORK3Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHOMEWORK3Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AHOMEWORK3Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHOMEWORK3Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AHOMEWORK3Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHOMEWORK3Character::LookUpAtRate);

	// handle touch devices
	/*PlayerInputComponent->BindTouch(IE_Pressed, this, &AHOMEWORK3Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHOMEWORK3Character::TouchStopped);*/

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AHOMEWORK3Character::OnResetVR);

	// crouch handle
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AHOMEWORK3Character::TouchCrouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AHOMEWORK3Character::EndCrouch);
}


void AHOMEWORK3Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHOMEWORK3Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AHOMEWORK3Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AHOMEWORK3Character::BeginCrouch()
{
	Crouch();
}

void AHOMEWORK3Character::EndCrouch()
{
	UnCrouch();
}

void AHOMEWORK3Character::TouchCrouch()
{
	if (bCrouching) {
		bCrouching = false;
		UnCrouch();
	}
	else {
		bCrouching = true;
		Crouch();
	}
}

void AHOMEWORK3Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHOMEWORK3Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHOMEWORK3Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHOMEWORK3Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
