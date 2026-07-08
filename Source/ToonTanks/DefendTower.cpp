// Fill out your copyright notice in the Description page of Project Settings.


#include "DefendTower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TimerManager.h"

void ADefendTower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ADefendTower::CheckFireCondition, FireRate, true);
}

void ADefendTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InAttackRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ADefendTower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ADefendTower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}
	if (InAttackRange() && Tank->bAlive)
	{
		Fire();
	}
}

bool ADefendTower::InAttackRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= AttackRange)
		{
			return true;
		}
	}
	return false;
}