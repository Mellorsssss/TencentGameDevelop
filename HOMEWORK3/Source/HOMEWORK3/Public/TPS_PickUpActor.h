// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "TPS_PickUpActor.generated.h"

class ACharacter;

UCLASS()
class HOMEWORK3_API ATPS_PickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPS_PickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MyMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* HoldingComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	USoundBase* PickUpSound;

	UFUNCTION()
	void RotateActor();

	UFUNCTION(BlueprintCallable, Category = "PickUp")
	virtual void Pickup(APawn* InstigatorPawn);

	UFUNCTION()
	virtual void OnFocus();
	
	bool bHolding;

	bool bGravity;

	FRotator ControlRotation;

	ACharacter* MyCharacter;

	UCameraComponent* PlayerCamera;

	FVector ForwardVector;
};
