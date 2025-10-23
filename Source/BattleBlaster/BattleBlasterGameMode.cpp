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

	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (playerController)
	{
		screenMessageWidget = CreateWidget<UScreenMessage>(playerController, ScreenMessageClass);
		if (screenMessageWidget)
		{
			screenMessageWidget->AddToPlayerScreen();
		}

	}
	countdownSeconds = gameplayTimer;

	GetWorldTimerManager().SetTimer(
		CountdownTimerHandle,
		this,
		&ABattleBlasterGameMode::OnCountdownTimeout,
		1.0f,
		true
	);
}

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	auto gameOver = false;
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		gameOver = true;
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
				gameOver = true;
				victory = true;
			}
		}
	}

	if (gameOver)
	{
		FString message = victory ? "You win" : "You Died";
		if (screenMessageWidget)
		{
			screenMessageWidget->SetVisibility(ESlateVisibility::Visible);
			screenMessageWidget->SetMessageText(message);
		}
		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(
			GameOverTimerHandle,
			this,
			&ABattleBlasterGameMode::OnGameOvertimeout,
			GameOverDelay,
			false
		);
	}
}

void ABattleBlasterGameMode::OnGameOvertimeout()
{
	auto gameInstance = GetGameInstance();
	if (gameInstance)
	{
		auto bbGameInstance = static_cast<UBattleBlasterGameInstance*>(gameInstance);
		if (bbGameInstance)
		{
			if (victory)
			{
				bbGameInstance->LoadNextLevel();
			}
			else
			{
				bbGameInstance->RestartCurrentLevel();
			}
		}
	}
	
}

void ABattleBlasterGameMode::OnCountdownTimeout()
{
	if (screenMessageWidget)
	{
		screenMessageWidget->SetMessageText(FString::Printf(TEXT("Game starts in %d"), countdownSeconds));
	}

	countdownSeconds--;

	if (countdownSeconds < 0)
	{
		if (screenMessageWidget)
		{
			screenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		Tank->SetPlayerEnabled(true);
	}
}