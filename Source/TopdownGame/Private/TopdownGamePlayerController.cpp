// Fill out your copyright notice in the Description page of Project Settings.

#include "TopdownGame.h"
#include "TopdownGamePlayerController.h"


ATopdownGamePlayerController::ATopdownGamePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	SetReplicates(true);
}

void ATopdownGamePlayerController::Tick(float dt)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Tick");

	auto pawn = GetPawn();
	if (pawn == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Pawn is null!");
		return;
	}

	FVector mouseLocation, mouseDirection;
	DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FRotator currentCharacterRotation = pawn->GetActorRotation();
	FRotator targetRotation = mouseDirection.Rotation();

	FRotator newRotation = FRotator(currentCharacterRotation.Pitch, targetRotation.Yaw, currentCharacterRotation.Roll);
	pawn->SetActorRotation(newRotation);

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, mouseDirection.ToString());
	
	auto castedPawn = Cast<ATopdownGamePawn, APawn>(pawn);
	castedPawn->FireShot(FVector(mouseDirection.X, mouseDirection.Y, 0.0f));
}