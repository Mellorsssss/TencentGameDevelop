// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSWeaponPickUp.h"
#include "../HOMEWORK3Character.h"


ATPSWeaponPickUp::ATPSWeaponPickUp()
{
	bShouldRotate = true;
}

void ATPSWeaponPickUp::Pickup(APawn* InstigatorPawn)
{
	Super::Pickup(InstigatorPawn);
	UE_LOG(LogTemp, Log, TEXT("Weapon is picked up"));
	AHOMEWORK3Character* MyPawn = Cast<AHOMEWORK3Character>(InstigatorPawn);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ATPSWeapon* NewWeapon = GetWorld()->SpawnActor<ATPSWeapon>(WeaponClass, SpawnInfo);

	MyPawn->AddWeapon(NewWeapon);
}

void ATPSWeaponPickUp::RotateInAir()
{
	if (RotateTimer.IsValid()) {
		GetWorldTimerManager().ClearTimer(RotateTimer);
	}

	if (bShouldRotate) {
		FRotator CurrentRotator = MyMesh->GetComponentRotation();

		float r = FMath::RandRange(0.1f, 0.05f);
		float n = 57.4f;
		CurrentRotator.Yaw += r * n;
		MyMesh->SetWorldRotation(CurrentRotator);
	}

	GetWorldTimerManager().SetTimer(RotateTimer, this, &ATPSWeaponPickUp::RotateInAir, 0.03f, true);
}

void ATPSWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();

	RotateInAir();
}

