// Copyright Epic Games, Inc. All Rights Reserved.

#include "HOMEWORK3Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "TPSWeapon.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "HealthComponent.h"
#include "TPSGameMode.h"
#include "Kismet/GameplayStatics.h"

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
	bUseControllerRotationYaw = true;
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


	// 初始化生命值组件 
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	bCrouching = false;

	bEnableZoom = false;
	CustomFOV = 65.0f;
	ZoomSpeed = 20.0;
	ViewRange = 1000.f;

	bFiring = false;
	bPunching = false;
	bDied = false;

	WeaponSocketName = "WeaponSocket";

	TotalBulletNum = 50;
	DiedSpanTime = 3.0f;
}

void AHOMEWORK3Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float TargetFOV = bEnableZoom ? CustomFOV : DefaultFOV;
	float CurrentFOV = FMath::FInterpTo(FollowCamera->FieldOfView, TargetFOV, DeltaTime, ZoomSpeed);
	FollowCamera->SetFieldOfView(CurrentFOV);

	CurrentFocusItem = GetFocusItem();// 获取当前注视的物体
}

float AHOMEWORK3Character::GetHealth() const
{
	if (HealthComponent) {
		return HealthComponent->HealthPoints;
	}
	return 0.f;
}

float AHOMEWORK3Character::GetMaxHealth() const
{
	if (HealthComponent) {
		return HealthComponent->DefaultHealthPoints;
	}
	return 100.f;
}

void AHOMEWORK3Character::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV = FollowCamera->FieldOfView;// store the default to recover 
	BulletNum = TotalBulletNum;
	HealthComponent->OnHealthChanged.AddDynamic(this, &AHOMEWORK3Character::OnHealthChangeHandler);

	if (HasAuthority()) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		CurrentWeapon = GetWorld()->SpawnActor<ATPSWeapon>(WeaponClasss, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

		if (CurrentWeapon) {
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		}
	}
}

FVector AHOMEWORK3Character::GetPawnViewLocation() const
{
	if (FollowCamera) {
		return FollowCamera->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

FRotator AHOMEWORK3Character::GetAimOffsets() const
{
	const FVector AimWorldSpace = GetBaseAimRotation().Vector();
	const FVector AimLocalSpace = ActorToWorld().InverseTransformVectorNoScale(AimWorldSpace);
	const FRotator AimRotationLocalSpace = AimLocalSpace.Rotation();
	return AimRotationLocalSpace;
}

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
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHOMEWORK3Character::TouchStarted);
	//PlayerInputComponent->BindTouch(IE_Released, this, &AHOMEWORK3Character::TouchStopped);*/

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AHOMEWORK3Character::OnResetVR);

	// crouch handle
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AHOMEWORK3Character::TouchCrouch);
	//PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AHOMEWORK3Character::EndCrouch);

	// 当按下Alt键时，可以自由观察角色当前的状态
	PlayerInputComponent->BindAction("UseControllerYaw", IE_Pressed, this, &AHOMEWORK3Character::UnUseControllerRotationYaw);
	PlayerInputComponent->BindAction("UseControllerYaw", IE_Released, this, &AHOMEWORK3Character::UseControllerRotationYaw);
	
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AHOMEWORK3Character::BeginZoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AHOMEWORK3Character::EndZoom);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AHOMEWORK3Character::BeginFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AHOMEWORK3Character::EndFire);

	PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &AHOMEWORK3Character::BeginPunch);
	PlayerInputComponent->BindAction("Punch", IE_Released, this, &AHOMEWORK3Character::EndPunch);

	PlayerInputComponent->BindAction("Target", IE_Pressed, this, &AHOMEWORK3Character::StartAim);
	PlayerInputComponent->BindAction("Target", IE_Released, this, &AHOMEWORK3Character::EndAim);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AHOMEWORK3Character::PickUp);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AHOMEWORK3Character::Reload);
}

void AHOMEWORK3Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHOMEWORK3Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	PickUp();
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

void AHOMEWORK3Character::UseControllerRotationYaw()
{
	bUseControllerRotationYaw = true;
}

void AHOMEWORK3Character::UnUseControllerRotationYaw()
{
	bUseControllerRotationYaw = false;
}

void AHOMEWORK3Character::BeginZoom()
{
	bEnableZoom = true;
}

void AHOMEWORK3Character::EndZoom()
{
	bEnableZoom = false;
}

void AHOMEWORK3Character::BeginFire()
{
	if (BulletNum > 0) {
		--BulletNum;
		bFiring = true;
		OnBulletNumChange(BulletNum, -1);
	}
}

void AHOMEWORK3Character::EndFire() {
	bFiring = false;
}

void AHOMEWORK3Character::BeginPunch()
{
	if (!bPunching) {
		bPunching = true;
	}
}

void AHOMEWORK3Character::EndPunch()
{
	if (bPunching) {
		bPunching = false;
	}
}

void AHOMEWORK3Character::StartAim()
{
	if (!bTargeting) {
		bTargeting = true;
	}
}

void AHOMEWORK3Character::EndAim()
{
	if (bTargeting) {
		bTargeting = false;
	}
}

ATPS_PickUpActor* AHOMEWORK3Character::GetFocusItem()
{
	// 从当前的视角使用射线检测判断是否注视Item
	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector TraceBegin = EyeLocation;
	FVector	TraceEnd = EyeLocation + (EyeRotation.Vector() * ViewRange);

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.bTraceComplex = true; // 碰撞精准到Triangle Mesh

	FHitResult HitResult;// 存储碰撞的结果
	
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceBegin, TraceEnd, ECC_Visibility, CollisionQueryParams);

	ATPS_PickUpActor* PickUpItem = Cast<ATPS_PickUpActor>(HitResult.GetActor());
	if (PickUpItem) {
		BeginZoom();
		bFocusing = true;
	}
	else if (bFocusing) {
		bFocusing = false;
		EndZoom();
	}
	return PickUpItem;
}

void AHOMEWORK3Character::PickUp()
{
	if (HasAuthority()) {
		if (CurrentFocusItem) {
			CurrentFocusItem->Pickup(this);
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Server pick the item up!"));
		ServerPickUp();
	}
}

void AHOMEWORK3Character::Reload()
{
	int BulletNumDelta = TotalBulletNum - BulletNum;
	BulletNum = TotalBulletNum;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),PickUpSound, GetActorLocation());
	OnBulletNumChange(BulletNum, BulletNumDelta);
}


void AHOMEWORK3Character::ServerAddWeapon_Implementation(ATPSWeapon* NewWeapon)
{
	AddWeapon(NewWeapon);
}

bool AHOMEWORK3Character::ServerAddWeapon_Validate(ATPSWeapon* NewWeapon)
{
	return true;
}

void AHOMEWORK3Character::ServerPickUp_Implementation()
{
	PickUp();
}	

bool AHOMEWORK3Character::ServerPickUp_Validate()
{
	return true;
}

void AHOMEWORK3Character::AddWeapon(ATPSWeapon* NewWeapon)
{
	if (NewWeapon && HasAuthority()) {// 客户端不执行该代码，在服务器上执行
		UE_LOG(LogTemp, Log, TEXT("charcter : add the weapon!"));
		if (NewWeapon == CurrentWeapon) {
			return;
		}

		if (NewWeapon) {
			if (CurrentWeapon) {
				CurrentWeapon->Destroy();
			}

			CurrentWeapon = NewWeapon;
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocketName);
		}

	}
	else {
		UE_LOG(LogTemp, Log, TEXT("charcter : run on the server!"));
		ServerAddWeapon(NewWeapon);
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

void AHOMEWORK3Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHOMEWORK3Character, CurrentWeapon);
	DOREPLIFETIME(AHOMEWORK3Character, bDied);
	DOREPLIFETIME(AHOMEWORK3Character, CurrentFocusItem);
}

void AHOMEWORK3Character::OnHealthChangeHandler(UHealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (!bDied && Health <= 0.f) {
		bDied = true;
		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DetachFromControllerPendingDestroy();
		SetLifeSpan(DiedSpanTime);

		ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GM) {
			UE_LOG(LogTemp, Log, TEXT("Charcter: The player is dead!"));
			GM->OnPlayerDied.Broadcast();
		}
	}
}
