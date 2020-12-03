// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../HOMEWORK3Character.h"
#include "TPSPlayerController.h"
#include "TPSPlayerState.h"
#include "TPSGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnActorKilled, AActor*, KilledActor, APlayerState*,KilledPlayerState, AActor*, KillerActor, AController*, KillerController);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);

class ATPSPlayerState;
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

	UFUNCTION()
	void RespawnDeadPlayer();

	UFUNCTION()
	void ScoreProcess(AActor* KilledActor, APlayerState* KilledPlayerState,AActor* KillerActor, AController* KillerController);
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
