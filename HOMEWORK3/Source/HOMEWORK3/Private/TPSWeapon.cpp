// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSWeapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials//PhysicalMaterial.h"
#include "../HOMEWORK3.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ATPSWeapon::ATPSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	ShootRange = 10000.0;
	BaseDamage = 20;

	MuzzleSocketName = "Muzzle";
	TraceSocketName = "Target";

	// ���ÿ��Ը���
	SetReplicates(true);
}

// Called when the game starts or when spawned
void ATPSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATPSWeapon::Fire()
{
	if (!HasAuthority()) {
		ServerFire();
	}

	AActor* WeaponOwner = GetOwner();
	if (WeaponOwner) {
		FVector EyeLocation;
		FRotator EyeRotation;
		WeaponOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector TraceBegin = EyeLocation;
		FVector	TraceEnd = EyeLocation + (EyeRotation.Vector() * ShootRange);

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(WeaponOwner);
		CollisionQueryParams.AddIgnoredActor(this);
		CollisionQueryParams.bTraceComplex = true; // ��ײ��׼��Triangle Mesh
		CollisionQueryParams.bReturnPhysicalMaterial = true; // �˴���Ҫ����Ϊ�棬����Ĭ�ϲ���ȡ�������

		FHitResult HitResult;// �洢��ײ�Ľ��
		EPhysicalSurface HitSurfaceType = SURFACETYPE_DEFAULT;

		float ActualDamge = BaseDamage;
		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceBegin, TraceEnd, ECC_GameTraceChannel1, CollisionQueryParams)) {
			HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());
			
			if (HitSurfaceType == SURFACETYPE_FLESHHEAD) {
				UE_LOG(LogTemp, Log, TEXT("Hit the head!!!"));
				ActualDamge *= 2.0;
			}

			ApplyDamage(HitResult.GetActor(),ActualDamge, EyeRotation.Vector(), HitResult, WeaponOwner->GetInstigatorController());

			TraceEnd = HitResult.ImpactPoint;

			PlayImpactEffect(HitSurfaceType, TraceEnd);
		}

		PlayFireEffect(TraceEnd);

		if (HasAuthority()) {
			FireTraceResult.TraceEnd = TraceEnd;
			FireTraceResult.SurfaceType = HitSurfaceType;
			if (FireTraceResult.SurfaceType != SURFACETYPE_DEFAULT) {
				UE_LOG(LogTemp, Log, TEXT("Server Transfer Surface Type!"));
			}
		}
	}
}

void ATPSWeapon::ApplyDamage(AActor* HitedActor,float damage, FVector HitFromDirection, FHitResult HitInfo, AController* EventInsitigator)
{
	if (HitedActor) {
		UGameplayStatics::ApplyPointDamage(HitedActor, damage, HitFromDirection, HitInfo, EventInsitigator, this, DamageType);
	}
}

void ATPSWeapon::PlayFireEffect(FVector TraceEnd)
{

	FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, MuzzleLocation);

	if (MuzzleEffect) {// ���ÿ�����Ч
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}

	// ���õ����켣
	if (TracerEffect) {
		UParticleSystemComponent* TraceComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
		if (TraceComp) {
			TraceComp->SetVectorParameter(TraceSocketName, TraceEnd);// ����Ŀ�ĵ�Ϊ���е�λ��
		}
	}
}

void ATPSWeapon::PlayImpactEffect(EPhysicalSurface SurfaceType, FVector TraceEnd)
{
	UE_LOG (LogTemp, Log, TEXT("Play the effect"));
	// �������е�������ʲ�ͬ��ѡ��ͬ������ϵͳ
	UParticleSystem* SelectedEffect = nullptr;
	USoundBase* SelectSound = nullptr;
	switch (SurfaceType) {
	case SURFACETYPE_DEFAULT:
		SelectedEffect = DefaultImpactEffect;
		SelectSound = DefaultSound;
		break;
	case SURFACETYPE_FLESHDEFAULT:
		SelectedEffect = FleshDefaultImpactEffect;
		SelectSound = HitBodySound;
		break;
	case SURFACETYPE_FLESHHEAD:
		SelectedEffect = FleshHeadImpactEffect;
		SelectSound = HeadBoostSound;
		break;
	default:
		SelectedEffect = DefaultImpactEffect;
		SelectSound = DefaultSound;
		break;
	}
	
	if (SelectedEffect) {
		// �����������
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		FVector ShootDirection = TraceEnd - MuzzleLocation;
		ShootDirection.Normalize();

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, TraceEnd,ShootDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SelectSound, TraceEnd);
	}
}

void ATPSWeapon::ServerFire_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Fire on the server."));
	Fire();
}

bool ATPSWeapon::ServerFire_Validate()
{
	return true;
}

void ATPSWeapon::OnRep_FireTrace()
{
	PlayFireEffect(FireTraceResult.TraceEnd);
	PlayImpactEffect(FireTraceResult.SurfaceType, FireTraceResult.TraceEnd);
}

void ATPSWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ATPSWeapon, FireTraceResult, COND_SkipOwner);
}

