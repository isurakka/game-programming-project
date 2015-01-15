// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "TopdownGamePawn.h"
#include "GameFramework/PlayerController.h"
#include "TopdownGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNGAME_API ATopdownGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	ATopdownGamePlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float dt) override;
};
