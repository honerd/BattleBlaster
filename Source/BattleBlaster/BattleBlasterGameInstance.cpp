// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBattleBlasterGameInstance::ChangeLevel(int32 index)
{
	if (index > 0 && index <= lastLevelIndex)
	{
		CurrentLevelIndex = index;
		FString levelNameString = FString::Printf(TEXT("Level_%d"), (int32)4 - CurrentLevelIndex);
		UGameplayStatics::OpenLevel(GetWorld(), *levelNameString);
	}
}
