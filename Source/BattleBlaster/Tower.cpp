// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireRateTimerHandle;
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::FireBullet,
		FireRate,
		true
	);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto TankLocation = Tank->GetActorLocation();

	if (FVector::Dist(GetActorLocation(), TankLocation) <= FireRange)
	{
		RotateTurret(TankLocation);
	}
}

void ATower::FireBullet()
{
	auto TankLocation = Tank->GetActorLocation();
	if (FVector::Dist(GetActorLocation(), TankLocation) <= FireRange && Tank->GetIsAlive())
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	this->Destroy();
}
