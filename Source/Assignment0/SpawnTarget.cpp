// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnTarget.h"
#include "FloatingActor.h"

// Sets default values
ASpawnTarget::ASpawnTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	CountDownTime = rand()%20+3;
}

// Called when the game starts or when spawned
void ASpawnTarget::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &ASpawnTarget::AdvanceTimer, 1.0f, true);
	Generate();
}

// Called every frame
void ASpawnTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Generate();
}

void ASpawnTarget::Generate() {
	UWorld* const world = GetWorld();
	if (world) {
		// 获取Spawn Actor的位置与方向
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotator = GetActorRotation();

		// 设置spawn时的参数，此处设置为如果发生碰撞则不生成
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		world->SpawnActor<AFloatingActor>(spawnedActor, SpawnLocation, SpawnRotator, spawnParams);
	}
}

void ASpawnTarget::AdvanceTimer()
{
	--CountDownTime;
	/*
	if (spawnedActor != NULL) {
		UpdateTimerDisplay();
	}*/
	if (CountDownTime < 1)
	{
		//倒数完成，停止运行定时器。
		CountDownTime = rand() % 10;
		//GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		/*if (GEngine) {

		}*/
		Generate();
	}
}


void ASpawnTarget::UpdateTimerDisplay()
{
	CountdownText->SetText(FString::FromInt(FMath::Max(CountDownTime, 0)));
}

void ASpawnTarget::TimeUp() {
	return;
}

