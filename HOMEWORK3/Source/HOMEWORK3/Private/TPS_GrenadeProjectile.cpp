 // Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_GrenadeProjectile.h"
#include "Components\SphereComponent.h"
#include "GameFrameWork\ProjectileMovementComponent.h"
#include "PhysicsEngine\RadialForceComponent.h"
#include "Particles\ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials//PhysicalMaterial.h"

// Sets default values
ATPS_GrenadeProjectile::ATPS_GrenadeProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	InitImpulse = 1000.f;
	ImpulseStrength = 2000.f;
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetAutoActivate(false);
	RadialForceComp->ImpulseStrength = ImpulseStrength;
	RadialForceComp->AttachTo(RootComponent);

	SpeedThreshold = 1000.f;
	DamageType = UDamageType::StaticClass();
	Damage = 100.f;
	DamageRadius = 100.f;
	

	SetReplicates(true);
}

// Called when the game starts or when spawned
void ATPS_GrenadeProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority()) {// 只有服务器可以处理榴弹击中事件
		MeshComp->OnComponentHit.AddDynamic(this, &ATPS_GrenadeProjectile::OnHit);
	}
	Shoot();
}

// Called every frame
void ATPS_GrenadeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) {// 只有服务器出需要执行该逻辑
		FVector CurrentV = GetVelocity();
		if (IsToExplode()) {
			Explode(MeshComp->GetComponentLocation());
		}
	}
}

void ATPS_GrenadeProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//TODO :首先获取材质
	EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
	if (IsHitTarget(HitSurfaceType)) {
		Explode(Hit.ImpactPoint);
	}
	else {
		SlowDown(HitSurfaceType);
	}
	
}

void ATPS_GrenadeProjectile::Shoot()
{
	FRotator ProjectileRotator = GetActorRotation();
	MeshComp->AddImpulse(ProjectileRotator.Vector()*InitImpulse, NAME_None, true);
}

bool ATPS_GrenadeProjectile::IsToExplode() const
{
	float CurrentVelocity = GetVelocity().Size();
	if (CurrentVelocity <= 0.1f) // 冲量还没有作用
		return false;
	return CurrentVelocity <= SpeedThreshold;
}

void ATPS_GrenadeProjectile::Explode(FVector ExplodeLocation)
{
	TArray<AActor*> IgnoreActors;
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, ExplodeLocation, DamageRadius, DamageType,IgnoreActors);
	Destroy();
}

void ATPS_GrenadeProjectile::SlowDown(EPhysicalSurface HitSurfaceType)
{
	float DecayFactor = 1.0f;
	switch (HitSurfaceType)
	{
	case SURFACETYPE_DEFAULT:
	case SURFACETYPE_FLESHDEFAULT:
	case SURFACETYPE_FLESHHEAD:
		break;
	case SURFACETYPE_GRASS:
		DecayFactor = 0.3f;
		break;
	case SURFACETYPE_IRON:
		DecayFactor = 1.0f;
		break;
	case SURFACETYPE_SOIL:
		DecayFactor = 0.5f;
	default:
		break;
	}
	FVector CurrentVelocity = GetVelocity();
	CurrentVelocity *= DecayFactor;
	UE_LOG(LogTemp, Log, TEXT("The factor is %f"), DecayFactor);
	MeshComp->SetAllPhysicsLinearVelocity(CurrentVelocity);
}

void ATPS_GrenadeProjectile::Destroyed()
{
	FVector ExplodeLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, ExplodeLocation);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplodeSound, ExplodeLocation);
	RadialForceComp->FireImpulse();
}
