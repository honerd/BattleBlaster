// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:

		ATank();
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		void MoveInput(const FInputActionValue& value);

		void RotateInput(const FInputActionValue& value);

		void FireInput(const FInputActionValue& value);

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputMappingContext* DefaultMappingContext; // Forward declaration improves the performance of the build

		UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComp;

		UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComp;

		UPROPERTY(EditAnywhere, Category = "Input")
		UInputAction* MoveAction;

		UPROPERTY(EditAnywhere, Category = "Input")
		UInputAction* RotateAction;

		UPROPERTY(EditAnywhere, Category = "Input")
		UInputAction* FireAction;

		UPROPERTY(EditAnywhere)
		float Speed = 300.f;

		UPROPERTY(EditAnywhere)	
		float TurnRate = 45.f;

};
