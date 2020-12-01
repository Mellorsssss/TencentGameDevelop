// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TPSWeapon.h"
#include "TPSGranade.generated.h"
UCLASS()
class HOMEWORK3_API ATPSGranade : public ATPSWeapon
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AActor> ProjectileClass;
protected:
	virtual void Fire() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerShoot();
};
