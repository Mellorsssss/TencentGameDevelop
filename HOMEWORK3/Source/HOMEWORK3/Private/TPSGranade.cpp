// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGranade.h"
#include "Kismet/GameplayStatics.h"

void ATPSGranade::Fire()
{
	if (!HasAuthority()) {
		ServerShoot();
		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, MuzzleLocation);
		return ;
	}

	AActor* WeaponOwner = GetOwner();
	if (WeaponOwner) {
		FVector EyeLocation;
		FRotator EyeRotation;
		WeaponOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, MuzzleLocation);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation, SpawnParameters);
		Projectile->SetOwner(WeaponOwner);// 设置榴弹的拥有者
	}
}

void ATPSGranade::ServerShoot_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Server shoot the projectile!"));
	Fire();
}

bool ATPSGranade::ServerShoot_Validate()
{
	return true;
}
