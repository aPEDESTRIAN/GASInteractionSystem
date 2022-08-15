// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASInteractionSystemGameMode.h"
#include "GASInteractionSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGASInteractionSystemGameMode::AGASInteractionSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
