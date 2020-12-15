// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS_PickUpActor.h"
#include "HOMEWORK3Character.generated.h"

class ATPSWeapon;
class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBulletNumChange, int, BulletNum, int, BulletNumDelta);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActorDied, )

UCLASS(config=Game)
class AHOMEWORK3Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AHOMEWORK3Character();


	virtual FVector GetPawnViewLocation() const override;

	UFUNCTION(BlueprintCallable, Category = "Player")
	FRotator GetAimOffsets() const;

	// 用于给武器类调用
	UFUNCTION(BlueprintCallable, Category = "Player")
	void AddWeapon(ATPSWeapon* NewWeapon);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Player")
	bool bCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	bool bEnableZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float CustomFOV;

	float DefaultFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100.0))
	float ZoomSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100.0))
	float ViewRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Player")
	bool bFiring;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	bool bPunching;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	bool bTargeting;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "Player")
	int BulletNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	int TotalBulletNum;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	bool bFocusing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	USceneComponent* HoldingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ATPSWeapon> WeaponClasss;

	UPROPERTY(Replicated,EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	ATPSWeapon* CurrentWeapon;
	
	// 当前注视的物品
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Player")
	ATPS_PickUpActor* CurrentFocusItem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundBase* PickUpSound;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player")
	bool bDied;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	float DiedSpanTime;
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	void BeginCrouch();

	void EndCrouch();

	void TouchCrouch();

	void UseControllerRotationYaw();

	void UnUseControllerRotationYaw();

	
	void BeginZoom();

	void EndZoom();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void BeginFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void EndFire();

	void BeginPunch();

	void EndPunch();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StartAim();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void EndAim();

	ATPS_PickUpActor* GetFocusItem();

	void PickUp();

	void Reload();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAddWeapon(ATPSWeapon* NewWeapon);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPickUp();
	// void RemoveWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnHealthChangeHandler(UHealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(BlueprintAssignable)
	FBulletNumChange OnBulletNumChanged;

	UFUNCTION(BlueprintImplementableEvent, Category = "EventTest")
	void OnBulletNumChange(int CurrentBulletNum, int BulletNumDelta);

	UFUNCTION(BlueprintCallable, Category = "Player")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category =  "Player")
	float GetMaxHealth() const;
};

