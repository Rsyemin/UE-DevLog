// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanlsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanlsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetPlayerEnableState(bool bPlayerEnabled);
};
