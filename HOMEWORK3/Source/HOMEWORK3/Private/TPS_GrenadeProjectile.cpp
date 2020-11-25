 // Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_GrenadeProjectile.h"
#include "Components\SphereComponent.h"
#include "GameFrameWork\ProjectileMovementComponent.h"
#include "PhysicsEngine\RadialForceComponent.h"
#include "Particles\ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATPS_GrenadeProjectile::ATPS_GrenadeProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	InitImpulse = 1000.f;
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->ImpulseStrength = 2000.f;
	RadialForceComp->AttachTo(RootComponent);

	SpeedThreshold = 1000.f;
}

// Called when the game starts or when spawned
void ATPS_GrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentHit.AddDynamic(this, &ATPS_GrenadeProjectile::OnHit);
	Shoot();
}

// Called every frame
void ATPS_GrenadeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsToExplode()) {
		Explode(MeshComp->GetComponentLocation());
	}
}

void ATPS_GrenadeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode(Hit.ImpactPoint);
}

void ATPS_GrenadeProjectile::Shoot()
{
	FRotator ProjectileRotator = GetActorRotation();
	MeshComp->AddImpulse(ProjectileRotator.Vector()*InitImpulse, NAME_None, true);
}

void ATPS_GrenadeProjectile::Explode(FVector ExplodeLocation)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, ExplodeLocation);
	RadialForceComp->FireImpulse();
	Destroy();
}

bool ATPS_GrenadeProjectile::IsToExplode() const
{
	float CurrentVelocity = GetVelocity().Size();
	if (CurrentVelocity <= 0.1f) // 冲量还没有作用
		return false;
	return CurrentVelocity <= SpeedThreshold;
}
