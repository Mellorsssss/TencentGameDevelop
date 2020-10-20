// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Assignment0GameMode.generated.h"

enum EState {
	EBegin,
	EGame,
	EWin,
	EEnd
};

UCLASS(minimalapi)
class AAssignment0GameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	EState current_state;
public:
	AAssignment0GameMode();
	void SetEState(EState state);
	EState GetEstate()const;

};



