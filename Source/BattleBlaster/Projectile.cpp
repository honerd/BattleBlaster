// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	SetRootComponent(ProjectileMesh);

	// Any movement component, or actor component for that matter, doesn't have to be attached to anything
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	TrailParticles = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto strongThis = this;
	AActor* owner = GetOwner();
	if (OtherActor && OtherActor!= strongThis && OtherActor != owner, owner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, owner->GetInstigatorController(), this, UDamageType::StaticClass());

		if (HitParticles)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
		}
	}
	// Destroy on Hit
	Destroy();
}

