// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetGameModeBase.h"
#include "TPSPlayerState.h"

ATargetGameModeBase::ATargetGameModeBase() {
	PlayerControllerClass = ATPSPlayerState::StaticClass();
}