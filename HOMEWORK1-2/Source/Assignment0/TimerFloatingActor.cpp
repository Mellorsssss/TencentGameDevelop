// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerFloatingActor.h"


void ATimerFloatingActor::BeginPlay()
{
    Super::BeginPlay();

    UpdateTimerDisplay();
    // 设置定时器的句柄与当前的Actor进行绑定
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATimerFloatingActor::AdvanceTimer, 1.0f, true);
}

ATimerFloatingActor::ATimerFloatingActor():AFloatingActor() {
    //将此Actor设为逐帧调用Tick()。如无需此功能，可关闭以提高性能。
    PrimaryActorTick.bCanEverTick = false;
    CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber"));
    CountdownText->SetHorizontalAlignment(EHTA_Center);
    CountdownText->SetWorldSize(150.0f);
    RootComponent = CountdownText;
    CountdownTime = 10;
}


void ATimerFloatingActor::UpdateTimerDisplay()
{
    CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ATimerFloatingActor::AdvanceTimer()
{
    --CountdownTime;
    UpdateTimerDisplay();
    if (CountdownTime < 1)
    {
        //倒数完成，停止运行定时器。
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownHasFinished();
    }
}

void ATimerFloatingActor::CountdownHasFinished()
{
    //改为特殊读出
    CountdownText->SetText(TEXT("GO!"));
}


