// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerState.h"

void ATPSPlayerState::AddScore(float ScoreDelta) {
	Score += ScoreDelta;
}

void ATPSPlayerState::SetName(FString Name)
{
	SetPlayerName(Name);
}

FString ATPSPlayerState::GetName() const
{
	return GetPlayerName();
}

int ATPSPlayerState::GetPlayerKillNum() const
{
	return PlayerKillNum;
}

int ATPSPlayerState::GetPlayerDiedNum() const
{
	return PlayerDiedNum;
}

void ATPSPlayerState::AddPlayerKillNum()
{
	UE_LOG(LogTemp, Log, TEXT("Kill a person!!"));
	PlayerKillNum += 1;
}

void ATPSPlayerState::AddPlayerDiedNum()
{
	UE_LOG(LogTemp, Log, TEXT("Died!"));
	PlayerDiedNum += 1;
}

