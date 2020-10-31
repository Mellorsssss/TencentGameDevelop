// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime\Engine\Classes\Components\TextRenderComponent.h>
#include "SpawnTarget.generated.h"

class AFloatingActor;

UCLASS()
class ASSIGNMENT0_API ASpawnTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category= "Projectile")
	TSubclassOf<AFloatingActor>spawnedActor;

	UPROPERTY(EditAnyWhere)
	int32 CountDownTime;

	FTimerHandle CountDownTimerHandle;

	void AdvanceTimer();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void TimeUp();

	void Generate();

	UTextRenderComponent* CountdownText;
	void UpdateTimerDisplay();


};
