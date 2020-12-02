// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGameMode.h"

ATPSGameMode::ATPSGameMode()
{
	MatchPeriod = 60.f;
	bIsGameOver = false;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

}

void ATPSGameMode::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(MatchTimerHandler, this, &ATPSGameMode::GameOver, MatchPeriod, false);
	OnPlayerDied.AddDynamic(this, &ATPSGameMode::RespawnDeadPlayer);
}

void ATPSGameMode::RespawnDeadPlayer()
{
	UE_LOG(LogTemp, Log, TEXT("GameMode: Respawn DeadPlayer!"));
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (PC && PC->GetPawn() == nullptr)
		{
			RestartPlayer(PC);
		}
	}
}

void ATPSGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATPSGameMode::GameOver()
{
	UE_LOG(LogTemp, Log, TEXT("Time is up, Game is over!!!"));// TODO: 实时显示当前剩余的游戏时间

	bIsGameOver = true;
}

