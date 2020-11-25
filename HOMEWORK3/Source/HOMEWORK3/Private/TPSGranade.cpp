// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGranade.h"

void ATPSGranade::Fire()
{
	AActor* WeaponOwner = GetOwner();
	if (WeaponOwner) {
		FVector EyeLocation;
		FRotator EyeRotation;
		WeaponOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		//GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation.Vector());
		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, EyeRotation, SpawnParameters);
	}
}
