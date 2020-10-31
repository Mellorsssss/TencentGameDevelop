// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerFloatingActor.h"


void ATimerFloatingActor::BeginPlay()
{
    Super::BeginPlay();

    UpdateTimerDisplay();
    // ���ö�ʱ���ľ���뵱ǰ��Actor���а�
    GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ATimerFloatingActor::AdvanceTimer, 1.0f, true);
}

ATimerFloatingActor::ATimerFloatingActor():AFloatingActor() {
    //����Actor��Ϊ��֡����Tick()��������˹��ܣ��ɹر���������ܡ�
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
        //������ɣ�ֹͣ���ж�ʱ����
        GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
        CountdownHasFinished();
    }
}

void ATimerFloatingActor::CountdownHasFinished()
{
    //��Ϊ�������
    CountdownText->SetText(TEXT("GO!"));
}


