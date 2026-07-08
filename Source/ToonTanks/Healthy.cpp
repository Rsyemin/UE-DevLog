// Fill out your copyright notice in the Description page of Project Settings.


#include "Healthy.h"
#include "ToontanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthy::UHealthy()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealthy = 1000;
	CurrentHealthy = MaxHealthy;
}


// Called when the game starts
void UHealthy::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthy::TakeDamage);

	ToontanksGameMode = Cast<AToontanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthy::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage >= 0)
	{
		CurrentHealthy -= Damage;
	}
	
	if (CurrentHealthy == 0 && ToontanksGameMode)
	{
		ToontanksGameMode->ActorDead(DamagedActor);
	}
}