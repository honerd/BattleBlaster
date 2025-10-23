// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BattleBlasterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UBattleBlasterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 lastLevelIndex = 3;
	
	UPROPERTY(VisibleAnywhere)
	int32 CurrentLevelIndex = 1;

	void LoadNextLevel()
	{
		if (CurrentLevelIndex < lastLevelIndex)
		{
			ChangeLevel(CurrentLevelIndex + 1);
		}
		else
		{
			RestartGame();
		}
	}

	void RestartCurrentLevel()
	{
		ChangeLevel(CurrentLevelIndex);
	}

	void RestartGame()
	{
		ChangeLevel(1);
	}
private:
	void ChangeLevel(int32 index);

};
