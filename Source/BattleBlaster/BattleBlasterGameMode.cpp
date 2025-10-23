// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	// GetAllTowers in the level and store their count
	TArray <AActor*> towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), towers);
	TowerCount = towers.Num();

	Tank = static_cast<ATank*>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (Tank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank not found by GameMode"));
	}

	for (const auto& iter : towers)
	{
		auto tower = static_cast<ATower*>(iter);
		if (tower && Tank)
		{
			tower->Tank = Tank;
		}
	}
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
	}
	else
	{
		auto deadTower = static_cast<ATower*>(DeadActor);
		if (deadTower)
		{
			deadTower->HandleDestruction();
			TowerCount--;
			if (TowerCount <= 0)
			{
				// Win the game
				UE_LOG(LogTemp, Warning, TEXT("You win!"));
			}
		}
	}
}
