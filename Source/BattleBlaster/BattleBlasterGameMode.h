// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "ScreenMessage.h"
#include "BattleBlasterGameInstance.h"
#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.0f;

	UPROPERTY(EditAnywhere)
	int32 gameplayTimer = 3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;

	UScreenMessage* screenMessageWidget;

	int32 countdownSeconds;

	FTimerHandle CountdownTimerHandle;

	void ActorDied(AActor* DeadActor);
	ATank* Tank;
	int32 TowerCount;
	bool victory = false; 

	void OnGameOvertimeout();

	void OnCountdownTimeout();

};
