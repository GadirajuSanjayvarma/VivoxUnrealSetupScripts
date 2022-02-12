// Fill out your copyright notice in the Description page of Project Settings.


#include "VivoxGameMode.h"
#include "VivoxPlayerController.h"

AVivoxGameMode::AVivoxGameMode(const FObjectInitializer& ObjectInitializer)
{
  
    PlayerControllerClass = AVivoxPlayerController::StaticClass();
}




void AVivoxGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    /*FString GameMode;
    FString OnlineSessionId;

    AVivoxPlayerController* VivoxPlayerController = CastChecked<AVivoxPlayerController>(NewPlayer);
    CHECKRET(VivoxPlayerController);

    IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
    CHECKRET(OnlineSubsystem);
    IOnlineSessionPtr SessionSubsystem = OnlineSubsystem->GetSessionInterface();
    CHECKRET(SessionSubsystem.IsValid());
    FNamedOnlineSession* Session = SessionSubsystem->GetNamedSession(NAME_GameSession);
    CHECKRET(Session);
    Session->SessionSettings.Get(SETTING_GAMEMODE, GameMode);
    OnlineSessionId = Session->SessionInfo->GetSessionId().ToString();

    // Needs to be called after the parent constructor is called, otherwise the player's team will not have been set yet.
    VivoxPlayerController->ClientJoinVoice("FFA", "123456789561");*/
}

