// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanlsPlayerController.h"
#include "GameFramework/Pawn.h"


void AToonTanlsPlayerController::SetPlayerEnableState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}