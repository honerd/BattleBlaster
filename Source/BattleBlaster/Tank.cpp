// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

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
	Super::Tick(DeltaTime);

	// Creating a line trace to the cursor everyframe
	auto playerController = static_cast<APlayerController*>(GetController());

	if (playerController)
	{
		FHitResult HitResult;
		playerController->GetHitResultUnderCursor(ECC_Visibility, false, OUT HitResult);
		
		// we do an impact point trace
		auto impactPoint = HitResult.ImpactPoint;
		DrawDebugSphere(GetWorld(), impactPoint, 25.0f, 12, FColor::Green);

		if (HitResult.bBlockingHit)
		{
			AActor* HitActor = HitResult.GetActor();
			UPrimitiveComponent* HitComp = HitResult.Component.Get(); // or HitResult.GetComponent() on some engine versions

			UE_LOG(LogTemp, Log, TEXT("Hit actor: %s"), *GetNameSafe(HitActor));
			UE_LOG(LogTemp, Log, TEXT("Hit component: %s"), *GetNameSafe(HitComp));
		}
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
		if (EnhancedInputComponent)
		{
			// This binds a move input to the needed value
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
			EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::RotateInput);
		}
	}
}

void ATank::MoveInput(const FInputActionValue& value)
{
	auto valueGained = value.Get<float>();

	// Gets the local forward actor of the tank
	AddActorLocalOffset(FVector(valueGained * Speed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0.0f, 0.0f), true);
}

void ATank::RotateInput(const FInputActionValue& value)
{
	auto valueGained = value.Get<float>();

	// FRotator has the pitch, yaw and roll values. These values are not X, Y, Z. 
	// Yaw is the rotation around the Z axis
	AddActorLocalRotation(FRotator(0.0f, valueGained * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0.0f), true);
}
