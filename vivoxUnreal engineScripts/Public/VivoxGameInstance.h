// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VivoxCore.h"
#include "VivoxGameInstance.generated.h"

template<class T>
class CachedProperty
{
public:
    explicit CachedProperty(T value) {
        m_dirty = false;
        m_value = value;
    }

    const T& GetValue() const {
        return m_value;
    }

    void SetValue(const T& value) {
        if (m_value != value) {
            m_value = value;
            m_dirty = true;
        }
    }

    void SetDirty(bool value) {
        m_dirty = value;
    }

    bool IsDirty() const {
        return m_dirty;
    }
protected:
    bool m_dirty;
    T m_value;
};

UENUM(BlueprintType)
enum class PTTKey : uint8
{
    PTTNoChannel,
    PTTAreaChannel,
    PTTTeamChannel
};

UCLASS(config = Game)
class ORACLEEARTHIUM_API UVivoxGameInstance : public UGameInstance
{
public:
    GENERATED_UCLASS_BODY()

public:
    ~UVivoxGameInstance();

    virtual void Init() override;
    virtual void Shutdown() override;
    virtual void StartGameInstance() override;

    UFUNCTION(BlueprintCallable, Category = "vivox")
    void LoadModule();

    
   

    /// Runtime console commands.
    virtual bool Exec(UWorld* Inworld, const TCHAR* Cmd, FOutputDevice& Ar) override;

    void BindLoginSessionHandlers(bool DoBind, ILoginSession& LoginSession);
    void BindChannelSessionHandlers(bool DoBind, IChannelSession& ChannelSession);

    VivoxCoreError Initialize(int logLevel);
    void Uninitialize();

    UFUNCTION(BlueprintCallable, Category = "vivox")
    void Login(const FString& PlayerName);
    
    void Logout();
    
    VivoxCoreError JoinVoiceChannels(FString GameMode, FString OnlineSessionId, int32 TeamNum = -1);
    VivoxCoreError Join(ChannelType ChannelType, bool ShouldTransmitOnJoin, const FString& ChannelName, PTTKey AssignChanneltoPTTKey = PTTKey::PTTNoChannel);
    void LeaveVoiceChannels();


    UFUNCTION(BlueprintCallable, Category = "vivox")
    void Update3DPosition(APawn* Pawn);

    void OnLoginSessionStateChanged(LoginState State);
    void OnChannelParticipantAdded(const IParticipant& Participant);
    void OnChannelParticipantRemoved(const IParticipant& Participant);
    void OnChannelParticipantUpdated(const IParticipant& Participant);
    void OnChannelAudioStateChanged(const IChannelConnectionState& State);
    void OnChannelTextStateChanged(const IChannelConnectionState& State);
    void OnChannelStateChanged(const IChannelConnectionState& State);
    void OnChannelTextMessageReceived(const IChannelTextMessage& Message);

    virtual bool IsInitialized();
    virtual bool IsLoggedIn();

    VivoxCoreError MultiChanPushToTalk(PTTKey Key, bool PTTKeyPressed);
    VivoxCoreError MultiChanToggleChat(PTTKey Key);

    ILoginSession* GetLoginSessionForRoster();
    TSharedPtr<IChannelSession> GetChannelSessionForRoster();
    ChannelId GetLastKnownTransmittingChannel() { return LastKnownTransmittingChannel; }
    static FString GetVivoxSafePlayerName(FString BaseName);

private:
    bool bInitialized;

    bool bLoggedIn;
    bool bLoggingIn;

    IClient* VivoxVoiceClient;
    AccountId LoggedInAccountID;
    FString LoggedInPlayerName;

    TPair<ChannelId, bool> PTTAreaChannel;
    TPair<ChannelId, bool> PTTTeamChannel;
    ChannelId ConnectedPositionalChannel; // You can only be in one Positional channel at a time.
    ChannelId LastKnownTransmittingChannel;

    /// Cached 3D position and orientation
    CachedProperty<FVector> CachedPosition = CachedProperty<FVector>(FVector());
    CachedProperty<FVector> CachedForwardVector = CachedProperty<FVector>(FVector());
    CachedProperty<FVector> CachedUpVector = CachedProperty<FVector>(FVector());

    /// Privates methods to check and clear dirtiness of cached 3D position
    bool Get3DValuesAreDirty() const;
    void Clear3DValuesAreDirty();
	
};
