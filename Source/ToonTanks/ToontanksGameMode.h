// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToontanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToontanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDead(AActor* DeadActor);

protected:
	void virtual BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;

	class AToonTanlsPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int DefendTowerCount = 0;

	int GetDefendTowerCount();
};
