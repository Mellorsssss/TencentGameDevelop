// Fill out your copyright notice in the Description page of Project Settings.


#include "TPS_PickUpActor.h"
#include "KisMet/GameplayStatics.h"

// Sets default values
ATPS_PickUpActor::ATPS_PickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	MyMesh->SetSimulatePhysics(true);
	RootComponent = MyMesh;

	bHolding = false;
	bGravity = true;
}


void ATPS_PickUpActor::Pickup(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Picking Up by the Actor"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickUpSound, MyMesh->GetComponentLocation());

	/*bHolding = !bHolding;
	bGravity = !bGravity;
	MyMesh->SetEnableGravity(bGravity);
	MyMesh->SetSimulatePhysics(bHolding ? false : true);
	MyMesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);*/
}

void ATPS_PickUpActor::OnFocus()
{
	MyMesh->SetRenderCustomDepth(true);
}
