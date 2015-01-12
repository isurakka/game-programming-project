// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TopdownGame.h"
#include "TopdownGameGameMode.h"
#include "TopdownGamePawn.h"

ATopdownGameGameMode::ATopdownGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// set default pawn class to our character class
	DefaultPawnClass = ATopdownGamePawn::StaticClass();
}

