// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	// Set the capsule component as the root component
	SetRootComponent(CapsuleComp);

	// Set base mesh and attach to root component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	// Set turret mesh and attach to base mesh
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// Take the vector diff to find the loction of the debug sphere relative to the turret
	// Then rotate only on the yaw axis to face the target
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	// Smoothens the rotator
	auto interpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 10.0f);
	TurretMesh->SetWorldRotation(interpolatedRotation);
}

void ABasePawn::Fire()
{
	auto spawnLocation = ProjectileSpawnPoint->GetComponentLocation();
	auto spawnRotation = ProjectileSpawnPoint->GetComponentRotation();

	auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, spawnLocation, spawnRotation);
	if (projectile)
	{
		projectile->SetOwner(this);
	}
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation(), GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	}
}

