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

