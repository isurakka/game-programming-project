// Fill out your copyright notice in the Description page of Project Settings.

#include "TopdownGame.h"
#include "TopdownGameViewportClient.h"


bool UTopdownGameViewportClient::InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	//bool ret = UGameViewportClient::InputKey(InViewport, ControllerId, Key, EventType, AmountDepressed, bGamepad);

	//UE_LOG(LogTemp, Warning, TEXT("ASD 1"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ASD 1");
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%d %s %s"), ControllerId, *Key.ToString(), bGamepad ? TEXT("Gamepad") : TEXT("Keyboard")));

	//return ret;

	if (IgnoreInput())
	{
		return false;
	}

	if (bGamepad)
	{
		ControllerId = int32(1);
	}

	if (InViewport->IsPlayInEditorViewport() && Key.IsGamepadKey())
	{
		GEngine->RemapGamepadControllerIdForPIE(this, ControllerId);
	}

	// route to subsystems that care
	bool bResult = (ViewportConsole ? ViewportConsole->InputKey(ControllerId, Key, EventType, AmountDepressed, bGamepad) : false);
	if (!bResult)
	{
		ULocalPlayer* const TargetPlayer = GEngine->GetLocalPlayerFromControllerId(this, ControllerId);
		if (TargetPlayer && TargetPlayer->PlayerController)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("ControllerId %d"), TargetPlayer->GetControllerId()));
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("FullName %s"), *TargetPlayer->PlayerController->GetFullName()));
			bResult = TargetPlayer->PlayerController->InputKey(Key, EventType, AmountDepressed, bGamepad);
		}

		// A gameviewport is always considered to have responded to a mouse buttons to avoid throttling
		if (!bResult && Key.IsMouseButton())
		{
			bResult = true;
		}
	}

	// For PIE, let the next PIE window handle the input if we didn't
	// (this allows people to use multiple controllers to control each window)
	if (!bResult && ControllerId > 0 && InViewport->IsPlayInEditorViewport())
	{
		UGameViewportClient *NextViewport = GEngine->GetNextPIEViewport(this);
		if (NextViewport)
		{
			bResult = NextViewport->InputKey(InViewport, ControllerId - 1, Key, EventType, AmountDepressed, bGamepad);
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%d %s %s"), ControllerId, *Key.ToString(), bGamepad ? TEXT("Gamepad") : TEXT("Keyboard")));

	return bResult;
}

bool UTopdownGameViewportClient::InputAxis(FViewport* InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	//bool ret = UGameViewportClient::InputAxis(InViewport, ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);

	//UE_LOG(LogTemp, Warning, TEXT("ASD 2"));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ASD 2");
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%d %s %s"), ControllerId, *Key.ToString(), bGamepad ? TEXT("Gamepad") : TEXT("Keyboard")));

	//return ret;

	if (IgnoreInput())
	{
		return false;
	}

	if (bGamepad)
	{
		ControllerId = int32(1);
	}

	bool bResult = false;

	if (InViewport->IsPlayInEditorViewport() && Key.IsGamepadKey())
	{
		GEngine->RemapGamepadControllerIdForPIE(this, ControllerId);
	}

	// Don't allow mouse/joystick input axes while in PIE and the console has forced the cursor to be visible.  It's
	// just distracting when moving the mouse causes mouse look while you are trying to move the cursor over a button
	// in the editor!
	if (!(InViewport->IsSlateViewport() && InViewport->IsPlayInEditorViewport()) || ViewportConsole == NULL || !ViewportConsole->ConsoleActive())
	{
		// route to subsystems that care
		if (ViewportConsole != NULL)
		{
			bResult = ViewportConsole->InputAxis(ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
		}
		if (!bResult)
		{
			ULocalPlayer* const TargetPlayer = GEngine->GetLocalPlayerFromControllerId(this, ControllerId);
			if (TargetPlayer && TargetPlayer->PlayerController)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("ControllerId %d"), TargetPlayer->GetControllerId()));
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("FullName %s"), *TargetPlayer->PlayerController->GetFullName()));
				bResult = TargetPlayer->PlayerController->InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
			}
		}

		// For PIE, let the next PIE window handle the input if we didn't
		// (this allows people to use multiple controllers to control each window)
		if (!bResult && ControllerId > 0 && InViewport->IsPlayInEditorViewport())
		{
			UGameViewportClient *NextViewport = GEngine->GetNextPIEViewport(this);
			if (NextViewport)
			{
				bResult = NextViewport->InputAxis(InViewport, ControllerId - 1, Key, Delta, DeltaTime, NumSamples, bGamepad);
			}
		}

		if (InViewport->IsSlateViewport() && InViewport->IsPlayInEditorViewport())
		{
			// Absorb all keys so game input events are not routed to the Slate editor frame
			bResult = true;
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("%d %s %s"), ControllerId, *Key.ToString(), bGamepad ? TEXT("Gamepad") : TEXT("Keyboard")));

	return bResult;
}
