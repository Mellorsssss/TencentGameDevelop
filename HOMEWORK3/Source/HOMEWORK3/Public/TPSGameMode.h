// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../HOMEWORK3Character.h"
#include "TPSGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, KilledActor, AActor*, KillerActor, AController*, KillerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);
/**
 * 
 */
UCLASS()
class HOMEWORK3_API ATPSGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category ="Settings")
	float MatchPeriod;

	FTimerHandle MatchTimerHandler;

	void RespawnDeadPlayer();

public:
	ATPSGameMode();

	virtual void StartPlay() override;

	virtual  void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnActorKilled OnActorKilled;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDied OnPlayerDied;

	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;

	// ”Œœ∑Ω· ¯
	UFUNCTION(BlueprintCallable)
	void GameOver();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameMode")
	bool bIsGameOver;
};
