// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "DefendTower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ADefendTower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

	UPROPERTY(EditDefaultsOnly)
	float AttackRange = 700.f;
	UPROPERTY(VisibleInstanceOnly)
	class ATank* Tank;
	bool InAttackRange();

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();
};
