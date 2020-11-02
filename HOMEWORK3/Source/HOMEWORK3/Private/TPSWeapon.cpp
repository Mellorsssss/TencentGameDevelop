// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSWeapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATPSWeapon::ATPSWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	ShootRange = 10000.0;
}

// Called when the game starts or when spawned
void ATPSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATPSWeapon::Fire()
{
	AActor* WeaponOwner = GetOwner();
	if (WeaponOwner) {
		FVector EyeLocation;
		FRotator EyeRotation;
		WeaponOwner->GetActorEyesViewPoint(EyeLocation,EyeRotation);

		FVector TraceBegin = EyeLocation,
			TraceEnd = EyeLocation + (EyeRotation.Vector() * ShootRange);

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(WeaponOwner);
		CollisionQueryParams.AddIgnoredActor(this);
		CollisionQueryParams.bTraceComplex = true; // 碰撞精准到Triangle Mesh

		FHitResult HitResult;// 存储碰撞的结果

		if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceBegin, TraceEnd, ECC_Visibility, CollisionQueryParams)) {
			AActor* HitedActor = HitResult.GetActor();
			if (HitedActor) {
				//DrawDebugLine(GetWorld(), TraceBegin, TraceEnd, FColor::White, false, 1.0, 0, 1.0);
				UGameplayStatics::ApplyPointDamage(HitedActor, 40.0, EyeRotation.Vector(), HitResult, WeaponOwner->GetInstigatorController(), this, DamageType);
			}
		}

		
	}
}

// Called every frame
void ATPSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

