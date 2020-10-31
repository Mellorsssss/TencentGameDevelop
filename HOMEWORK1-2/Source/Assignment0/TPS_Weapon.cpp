// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_Weapon.h"

// Sets default values
ATPS_Weapon::ATPS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ATPS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

