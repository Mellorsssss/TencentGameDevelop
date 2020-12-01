// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../HOMEWORK3.h"
#include "GameFramework/Actor.h"
#include "TPS_GrenadeProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class URadialForceComponent;
class UParticleSystem;
class UDamageType;

UCLASS()
class HOMEWORK3_API ATPS_GrenadeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPS_GrenadeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 给抛射体一个初速度
	void Shoot();

	void Explode(FVector ExplodeLocation);
	
	bool IsToExplode() const;

	void SlowDown(EPhysicalSurface HitSurfaceType);

	FORCEINLINE bool IsHitTarget(EPhysicalSurface HitSurfaceType)const {
		return HitSurfaceType == SURFACETYPE_FLESHDEFAULT || HitSurfaceType == SURFACETYPE_FLESHHEAD;
	};

	virtual void Destroyed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	URadialForceComponent* RadialForceComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	USoundBase* ExplodeSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	float InitImpulse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	float DamageRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	// 碰撞事件
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float SpeedThreshold;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float ImpulseStrength;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
