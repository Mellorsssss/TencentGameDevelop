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

	MyCharacter = nullptr;
	bHolding = false;
	bGravity = true;
}

// Called when the game starts or when spawned
void ATPS_PickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
	MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerCamera = MyCharacter->FindComponentByClass<UCameraComponent>();

	TArray<USceneComponent*> Components;

	MyCharacter->GetComponents(Components);

	if (Components.Num() > 0)
	{
		for (auto& Comp : Components)
		{
			if (Comp->GetName() == "CurrentWeapon")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	}
}

// Called every frame
void ATPS_PickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATPS_PickUpActor::RotateActor()
{
	ControlRotation = GetWorld()->GetFirstPlayerController()->GetControlRotation();
	SetActorRotation(FQuat(ControlRotation));
}

void ATPS_PickUpActor::Pickup(APawn* InstigatorPawn)
{
	UE_LOG(LogTemp, Log, TEXT("Picking Up by the Actor"));
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickUpSound, MyMesh->GetComponentLocation());

	bHolding = !bHolding;
	bGravity = !bGravity;
	MyMesh->SetEnableGravity(bGravity);
	MyMesh->SetSimulatePhysics(bHolding ? false : true);
	MyMesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);

	if (!bHolding)
	{
		ForwardVector = PlayerCamera->GetForwardVector();
		MyMesh->AddForce(ForwardVector * 100000 * MyMesh->GetMass());
	}
}

void ATPS_PickUpActor::OnFocus()
{
	MyMesh->SetRenderCustomDepth(true);
}
