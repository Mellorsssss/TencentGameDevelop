// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPS_PickUpActor.h"
#include "TPSWeapon.h"
#include "TPSWeaponPickUp.generated.h"


UCLASS()
class HOMEWORK3_API ATPSWeaponPickUp : public ATPS_PickUpActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,Category = "Pickup")
	FTimerHandle RotateTimer;

	void RotateInAir();

	virtual void BeginPlay() override;
public:
	ATPSWeaponPickUp();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
	TSubclassOf<ATPSWeapon> WeaponClass;
	

	virtual void Pickup(APawn* InstigatorPawn) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
	bool bShouldRotate;
};
