// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreativeTaskGameMode.h"
#include "CreativeTaskCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACreativeTaskGameMode::ACreativeTaskGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdParty/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
