// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VivoxGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ORACLEEARTHIUM_API AVivoxGameMode : public AGameMode
{
	
        GENERATED_UCLASS_BODY()

        void PostLogin(APlayerController* NewPlayer) override;

};
