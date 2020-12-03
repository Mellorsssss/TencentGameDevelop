// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TPSGameMode.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	DefaultHealthPoints = 100.f;

	SetIsReplicatedByDefault(true);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthPoints = DefaultHealthPoints;

	// 只在服务器上处理生命值变动的逻辑
	if (GetOwnerRole() == ROLE_Authority){
		AActor* MyOwner = GetOwner();
		if (MyOwner) {
			MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnHealthChangeHandler);
		}
	}
}

void UHealthComponent::OnHealthChangeHandler(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0.f) {
		return;
	}

	HealthPoints = FMath::Clamp(HealthPoints - Damage, 0.f, DefaultHealthPoints);
	UE_LOG(LogTemp, Log, TEXT("Current hp is %f"), HealthPoints);

	if (HealthPoints <= 0.f) {
		ATPSGameMode* GM = Cast<ATPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GM) {
			UE_LOG(LogTemp, Log, TEXT("HealthComp: killed!"));
			GM->OnActorKilled.Broadcast(DamagedActor, Cast<ACharacter>(GetOwner())->GetPlayerState(), DamageCauser, InstigatedBy);
		}
	}

	OnHealthChanged.Broadcast(this, HealthPoints, Damage,DamageType, InstigatedBy, DamageCauser);// 传递生命值变化事件，考虑到时序，此处最后调用
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, HealthPoints);
}
