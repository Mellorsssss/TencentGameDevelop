// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FloatingActor.h"
#include "Components/TextRenderComponent.h"
#include "TimerFloatingActor.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT0_API ATimerFloatingActor : public AFloatingActor
{
	GENERATED_BODY()
	ATimerFloatingActor();

protected:
	virtual void BeginPlay()override;
public:
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;
	UTextRenderComponent* CountdownText;

	void UpdateTimerDisplay();

	void AdvanceTimer();

	void CountdownHasFinished();

	FTimerHandle CountdownTimerHandle;
};
