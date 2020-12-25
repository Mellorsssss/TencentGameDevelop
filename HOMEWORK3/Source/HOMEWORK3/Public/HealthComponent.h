// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, UHealthComponent*, HealthComponent, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor* ,DamageCauser);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEWORK3_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChangeHandler(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const ;

	FTimerHandle RespawnTimerHandler;

	void DeathHandler();
public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "HealthComponent")
	float HealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	float DefaultHealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	float HealDelta;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "HealthComponent")
	void Heal();


};
