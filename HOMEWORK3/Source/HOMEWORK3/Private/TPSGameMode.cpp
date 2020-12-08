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
	OnActorKilled.AddDynamic(this, &ATPSGameMode::ScoreProcess);
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

void ATPSGameMode::ScoreProcess(AActor* KilledActor, APlayerState* KilledPlayerState, AActor* KillerActor, AController* KillerController)
{
	// 增加凶手玩家的分数
	ATPSPlayerController* KillerPlayerContorller = Cast<ATPSPlayerController>(KillerController);
	if (KillerPlayerContorller) {
		UE_LOG(LogTemp, Log, TEXT("GM: Killer cast success!"));
		ATPSPlayerState* KillerPlayerState = Cast<ATPSPlayerState>(KillerPlayerContorller->PlayerState);
		if (KillerPlayerState) {
			KillerPlayerState->AddScore(100);
			KillerPlayerState->AddPlayerKillNum();
		}
	}

	// 增加被杀玩家的死亡次数
	ATPSPlayerState* VictimPlayerState = Cast<ATPSPlayerState>(KilledPlayerState);
	if (VictimPlayerState) {
		UE_LOG(LogTemp, Log, TEXT("Victim : Add Dead Nun!"));
		VictimPlayerState->AddPlayerDiedNum();
	}
}

void ATPSGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RespawnDeadPlayer();
}


void ATPSGameMode::GameOver()
{
	UE_LOG(LogTemp, Log, TEXT("Time is up, Game is over!!!"));// TODO: 实时显示当前剩余的游戏时间

	bIsGameOver = true;
}

