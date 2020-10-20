// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment0GameMode.h"
#include "Assignment0Character.h"
#include "UObject/ConstructorHelpers.h"

AAssignment0GameMode::AAssignment0GameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
	DefaultPawnClass = AAssignment0Character::StaticClass();
}

void AAssignment0GameMode::SetEState(EState state) {
	current_state = state;
}
EState AAssignment0GameMode::GetEstate() const {
	return current_state;
}
