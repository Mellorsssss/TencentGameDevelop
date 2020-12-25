// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"
#include "TPSGameMode.h"

ATPSPlayerController::ATPSPlayerController()
{
	RespawnWaitTime = 5.0f;
}


void ATPSPlayerController::DeathHandler()
{
	ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM) {
	UE_LOG(LogTemp, Log, TEXT("Now is time to handle death!"));
		GM->OnPlayerDied.Broadcast();
	}
}


void ATPSPlayerController::OnPlayerDiedHandle()
{
	ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
	GM->GetWorldTimerManager().SetTimer(DeathTimer, this, &ATPSPlayerController::DeathHandler, RespawnWaitTime, false);
}
