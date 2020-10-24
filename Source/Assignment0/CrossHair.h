// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossHair.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT0_API ACrossHair : public AHUD
{
	GENERATED_BODY()
protected:
    // ������Ļ������ƴ��
    UPROPERTY(EditDefaultsOnly)
       UTexture2D* CrosshairTexture;
public:
    // HUD�������Ƶ��á�
    virtual void DrawHUD() override;
};
