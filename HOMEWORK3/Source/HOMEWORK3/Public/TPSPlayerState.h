// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK3_API ATPSPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	FText PlayerName;

public:
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void AddScore(float ScoreDelta);


	/*UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void SetPlayerName(FText Name);
	*/
	/*UFUNCTION(BlueprintCallable, Category = "PlayerState")
	void GetPlayerName()const;*/
};
