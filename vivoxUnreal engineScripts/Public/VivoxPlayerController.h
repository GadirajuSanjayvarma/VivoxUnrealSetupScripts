// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Online.h"
#include "VivoxPlayerController.generated.h"

/**
 * 
 */
#define CHECKRET(cond) if (!(cond)) { UE_LOG(LogTemp, Error, TEXT("CHECKRET(%s) Failed"), TEXT(#cond)); return; }

UCLASS(config = Game)
class ORACLEEARTHIUM_API AVivoxPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "vivox")
    void PushToTalkAreaChannelPressed();
    UFUNCTION(BlueprintCallable, Category = "vivox")
    void PushToTalkAreaChannelReleased();
    void PushToTalkTeamChannelPressed();
    void PushToTalkTeamChannelReleased();

    void PushToToggleAreaChannel();
    void PushToToggleTeamChannel();

    virtual void PlayerTick(float DeltaTime) override;
    virtual void SetupInputComponent() override;
    

    UFUNCTION(BlueprintCallable, Category = "vivox")
     void ClientJoinVoice(const FString& GameMode, const FString& OnlineSessionId, const int32& TeamNum = -1);
	
};
