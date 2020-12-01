// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	DefaultHealthPoints = 100.f;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthPoints = DefaultHealthPoints;

	AActor* MyOwner = GetOwner();
	if (MyOwner) {
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnHealthChangeHandler);
	}
}

void UHealthComponent::OnHealthChangeHandler(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0.f) {
		return;
	}

	HealthPoints = FMath::Clamp(HealthPoints - Damage, 0.f, DefaultHealthPoints);
	UE_LOG(LogTemp, Log, TEXT("Current hp is %f"), HealthPoints);

	OnHealthChanged.Broadcast(this, HealthPoints, Damage,DamageType, InstigatedBy, DamageCauser);// 传递生命值变化事件
}
