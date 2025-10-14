// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

void ATank::BeginPlay()
{
	Super::BeginPlay();

	// Every pawn has a player controller we try to acces it here.
	// PlayerControllers are used by human players to control Pawns.
	auto playerController = Cast<APlayerController>(Controller);


	if (playerController)
	{

		// We get the local player subsystem from the player controller.
		// Each player that is active has a local player subsystem.
		// it can be 0 for dedicated servers hence we are having a check here
		auto localPlayer = playerController->GetLocalPlayer();
		if (localPlayer)
		{
			// A subsystem in UE5 is a special, automatically managed class that handles specific tasks, similar to a singleton
			auto subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);

			// if UEnhancedInputLocalPlayerSubsystem subsystem exists, we can create custom input mapping contexts
			if (subSystem)
			{
				// this takes in which mapping content we want to add and the priority of that mapping context
				subSystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);
}

void ATank::Tick(float DeltaTime)
{
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
