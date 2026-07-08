// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ToontanksGameMode.h"
#include "Tank.h"
#include "DefendTower.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanlsPlayerController.h"

void AToontanksGameMode::BeginPlay()
{
	HandleGameStart();

	DefendTowerCount = GetDefendTowerCount();
}

void AToontanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	ToonTanksPlayerController = Cast<AToonTanlsPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);

		FTimerHandle PlayerEnableTimerHandle;
		//定时器回调有参数的函数，必须将回调函数装进委托里面
		FTimerDelegate PlayerTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanlsPlayerController::SetPlayerEnableState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerTimerDelegate, StartDelay, false);
	}
}

void AToontanksGameMode::ActorDead(AActor* DeadActor)
{
	if (DeadActor == nullptr) return;

	Cast<ABasePawn>(DeadActor) -> HandleDestruction();

	if (DeadActor == Tank)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);

		GameOver(false);
	}
	else
	{
		DefendTowerCount--;
		if (DefendTowerCount == 0)
		{
			GameOver(true);
		}
	}
}

int AToontanksGameMode::GetDefendTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ADefendTower::StaticClass(), Towers);
	return Towers.Num();
}