// Fill out your copyright notice in the Description page of Project Settings.


#include "VivoxPlayerController.h"
#include "VivoxGameInstance.h"
#include "VivoxTracer.h"

AVivoxPlayerController::AVivoxPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AVivoxPlayerController::PushToTalkAreaChannelPressed()
{
    Tracer::MinorMethodPrologue();
    UVivoxGameInstance* VivoxGameInstance = GetWorld() != NULL ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);
    VivoxGameInstance->MultiChanPushToTalk(PTTKey::PTTAreaChannel, true);
}

void AVivoxPlayerController::PushToTalkAreaChannelReleased()
{
    Tracer::MinorMethodPrologue();
    UVivoxGameInstance* VivoxGameInstance = GetWorld() != NULL ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);
    VivoxGameInstance->MultiChanPushToTalk(PTTKey::PTTAreaChannel, false);
}

void AVivoxPlayerController::PushToTalkTeamChannelPressed()
{
    Tracer::MinorMethodPrologue();
    UVivoxGameInstance* VivoxGameInstance = GetWorld() != NULL ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);
    VivoxGameInstance->MultiChanPushToTalk(PTTKey::PTTTeamChannel, true);
}

void AVivoxPlayerController::PushToTalkTeamChannelReleased()
{
    Tracer::MinorMethodPrologue();
    UVivoxGameInstance* VivoxGameInstance = GetWorld() != NULL ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);
    VivoxGameInstance->MultiChanPushToTalk(PTTKey::PTTTeamChannel, false);
}

void AVivoxPlayerController::PushToToggleAreaChannel()
{
    UVivoxGameInstance* VivoxGameInstance = GetWorld() != NULL ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);
    VivoxGameInstance->MultiChanToggleChat(PTTKey::PTTAreaChannel);
}

void AVivoxPlayerController::PushToToggleTeamChannel()
{
    UVivoxGameInstance* VivoxGameInstance = GetWorld() != NULL ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);
    VivoxGameInstance->MultiChanToggleChat(PTTKey::PTTTeamChannel);
}

void AVivoxPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);

    /*UVivoxGameInstance* VivoxGameInstance = GetWorld() != NULL ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);
    VivoxGameInstance->Update3DPosition(GetPawnOrSpectator()); // Track player in either Warmup or Match.*/
}

void AVivoxPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // unbind native voice and text
    int i = 0;
    while (i < InputComponent->GetNumActionBindings())
    {
        FInputActionBinding action = InputComponent->GetActionBinding(i);
        if (0 == action.GetActionName().ToString().Compare("PushToTalk") || 0 == action.GetActionName().ToString().Compare("ToggleChat"))
        {
            InputComponent->RemoveActionBinding(i);
        }
        else
        {
            ++i;
        }
    }

    // vivox multi-channel push-to-talk
    InputComponent->BindAction("PushToTalkAreaChannel", IE_Pressed, this, &AVivoxPlayerController::PushToTalkAreaChannelPressed);
    InputComponent->BindAction("PushToTalkAreaChannel", IE_Released, this, &AVivoxPlayerController::PushToTalkAreaChannelReleased);
    InputComponent->BindAction("PushToTalkTeamChannel", IE_Pressed, this, &AVivoxPlayerController::PushToTalkTeamChannelPressed);
    InputComponent->BindAction("PushToTalkTeamChannel", IE_Released, this, &AVivoxPlayerController::PushToTalkTeamChannelReleased);

#if (PLATFORM_PS4 || PLATFORM_XBOXONE || PLATFORM_SWITCH)
    // key bindings for for push-to-toggle chat on consoles
    InputComponent->BindAction("PushToToggleAreaChannel", IE_Pressed, this, &AVivoxPlayerController::PushToToggleAreaChannel);
    InputComponent->BindAction("PushToToggleTeamChannel", IE_Pressed, this, &AVivoxPlayerController::PushToToggleTeamChannel);
#endif
}

void AVivoxPlayerController::ClientJoinVoice(const FString& GameMode, const FString& OnlineSessionId, const int32& TeamNum)
{
    Tracer::MajorMethodPrologue("%s %s %d", *GameMode, *OnlineSessionId, TeamNum);

   

    UVivoxGameInstance* VivoxGameInstance = GetWorld() ? CastChecked<UVivoxGameInstance>(GetWorld()->GetGameInstance()) : NULL;
    CHECKRET(VivoxGameInstance);

    VivoxGameInstance->JoinVoiceChannels(GameMode, OnlineSessionId, TeamNum);
}


