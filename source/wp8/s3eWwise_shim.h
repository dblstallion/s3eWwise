/*
C++ Shim implementation of the s3eWwise extension's.

Not intended for modifications

These functions are called by C# to access native interface and from C++ to
access managed interface.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

namespace s3eWwiseExtension
{
// This is the interface which native code can use to talk to managed code.
[Windows::Foundation::Metadata::WebHostHidden]
public interface class IManagedS3Es3eWwiseAPI : public s3e_native::IManagedS3EAPI
{
    // We shouldn't populate these defacto.  We should only add functions here as and when
    // necessary.
    bool s3eWwiseMemoryMgrIsInitialized_managed();
    void s3eWwiseMemoryMgrTerm_managed();
    FIXME s3eWwiseMemoryMgrInit_managed(FIXME in_pSettings);
    FIXME s3eWwiseStreamMgrCreate_managed(FIXME in_settings);
    void s3eWwiseStreamMgrDestroy_managed(FIXME streamMgr);
    void s3eWwiseStreamMgrGetDefaultSettings_managed(FIXME out_settings);
    FIXME s3eWwiseStreamMgrSetCurrentLanguage_managed(Platform::String^ in_pszLanguageName);
    bool s3eWwiseSoundEngineIsInitialized_managed();
    FIXME s3eWwiseSoundEngineInit_managed(FIXME in_pSettings, FIXME in_pPlatformSettings);
    void s3eWwiseSoundEngineGetDefaultInitSettings_managed(FIXME out_settings);
    void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_managed(FIXME out_settings);
    void s3eWwiseSoundEngineTerm_managed();
    FIXME s3eWwiseSoundEngineRenderAudio_managed();
    FIXME s3eWwiseSoundEnginePostEventNamed_managed(Platform::String^ in_pszEventName, FIXME in_gameObjectID, FIXME 0);
    FIXME s3eWwiseSoundEnginePostEventWithID_managed(FIXME in_eventID, FIXME in_gameObjectID, FIXME 0);
    void s3eWwiseSoundEngineStopAll_managed(FIXME S3E_WWISE_INVALID_GAME_OBJECT);
    void s3eWwiseSoundEngineStopPlayingID_managed(FIXME in_playingID, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear);
    FIXME s3eWwiseSoundEngineSetActiveListeners_managed(FIXME in_GameObjectID, uint32 in_uListenerMask);
    FIXME s3eWwiseSoundEngineSetListenerPosition_managed(FIXME in_Position, FIXME 0);
    FIXME s3eWwiseSoundEngineSetRTPCValueWithID_managed(FIXME in_rtpcID, FIXME in_value, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear);
    FIXME s3eWwiseSoundEngineSetRTPCValueNamed_managed(Platform::String^ in_pszRtpcName, FIXME in_value, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear);
    FIXME s3eWwiseSoundEngineResetRTPCValueWithID_managed(FIXME in_rtpcID, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear);
    FIXME s3eWwiseSoundEngineResetRTPCValueNamed_managed(Platform::String^ in_pszRtpcName, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear);
    FIXME s3eWwiseSoundEngineSetSwitchWithID_managed(FIXME in_switchGroup, FIXME in_switchState, FIXME in_gameObjectID);
    FIXME s3eWwiseSoundEngineSetSwitchNamed_managed(Platform::String^ in_pszSwitchGroup, Platform::String^ in_pszSwitchState, FIXME in_gameObjectID);
    FIXME s3eWwiseSoundEnginePostTriggerWithID_managed(FIXME in_triggerID, FIXME in_gameObjectID);
    FIXME s3eWwiseSoundEnginePostTriggerNamed_managed(Platform::String^ in_pszTrigger, FIXME in_gameObjectID);
    FIXME s3eWwiseSoundEngineSetStateWithID_managed(FIXME in_stateGroup, FIXME in_state);
    FIXME s3eWwiseSoundEngineSetStateNamed_managed(Platform::String^ in_pszStateGroup, Platform::String^ in_pszState);
    FIXME s3eWwiseSoundEngineRegisterGameObj_managed(FIXME in_gameObjectID);
    FIXME s3eWwiseSoundEngineRegisterGameObjWithName_managed(FIXME in_gameObjectID, Platform::String^ in_pszObjName);
    FIXME s3eWwiseSoundEngineUnregisterGameObj_managed(FIXME in_gameObjectID);
    FIXME s3eWwiseSoundEngineUnregisterAllGameObj_managed();
    FIXME s3eWwiseSoundEngineSetPosition_managed(FIXME in_gameObjectID, FIXME in_Position);
    FIXME s3eWwiseSoundEngineClearBanks_managed();
    FIXME s3eWwiseSoundEngineLoadBankNamed_managed(Platform::String^ in_pszString, FIXME in_memPoolId, FIXME out_bankID);
    FIXME s3eWwiseSoundEngineLoadBankWithID_managed(FIXME in_bankID, FIXME in_memPoolId);
    FIXME s3eWwiseSoundEngineUnloadBankNamed_managed(Platform::String^ in_pszString, FIXME NULL);
    FIXME s3eWwiseSoundEngineUnloadBankWithID_managed(FIXME in_bankID, FIXME NULL);
    FIXME s3eWwiseMusicEngineInit_managed(FIXME in_pSettings);
    void s3eWwiseMusicEngineGetDefaultInitSettings_managed(FIXME out_settings);
    void s3eWwiseMusicEngineTerm_managed();
    FIXME s3eWwiseCommInit_managed(FIXME in_settings);
    void s3eWwiseCommGetDefaultInitSettings_managed(FIXME out_settings);
    void s3eWwiseCommTerm_managed();
    FIXME s3eWwiseLowLevelIOSetBasePath_managed(Platform::String^ in_pszBasePath);
    FIXME s3eWwiseLowLevelIOSetBankPath_managed(Platform::String^ in_pszBankPath);
    FIXME s3eWwiseLowLevelIOSetAudioSrcPath_managed(Platform::String^ in_pszAudioSrcPath);
};// This is the class which managed code can use to talk to native code.
[Windows::Foundation::Metadata::WebHostHidden]
public ref class s3eWwiseNativeInterface sealed : public s3e_native::INativeS3EAPI
{
    // We shouldn't populate these defacto.  We should only add functions here as and when
    // necessary.
public:
    s3eWwiseNativeInterface() {}
};


[Windows::Foundation::Metadata::WebHostHidden]
public ref class s3eWwiseShim sealed 
{
public:

    s3eWwiseShim();

    // We use two stage construction to avoid the use of exceptions.  We
    // don't want to ever register an API more than once (as it's a static
    // below).  If we did this initialization in the ctr then we'd either
    // have to fail silently or throw an exception.
     bool Init(IManagedS3Es3eWwiseAPI^ managedAPI);

    // Unregisters the static interface.
     bool Terminate();

    // Need static getters as we can't have public members in the class.
    static IManagedS3Es3eWwiseAPI^ GetInterface();
private:

    ~s3eWwiseShim();

    // This is the unavoidable point where we need a static.  There's
    // no choice as we're converting to a C-API.
    static IManagedS3Es3eWwiseAPI^ s_ManagedInterface;
};

// char* <-> Platform::String^ wrappers
static inline Platform::String^ UTF8ToString(const char* utf8str)
{
    return s3e_native::s3eAPIDataTypeWrapper::CStringToPlatformString(const_cast<char*>(utf8str));
}

static inline void StringToUTF8(char* utf8str, size_t size, Platform::String^ str)
{
    s3e_native::s3eAPIDataTypeWrapper::PlatformStringToCString(const_cast<char*>(utf8str), size, str);
}

}
