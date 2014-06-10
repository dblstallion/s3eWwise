/*
 * wp8-specific implementation of the s3eWwise extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include <crtdbg.h>

#define _CRT_PERROR_DEFINED
#include <wrl/client.h>
#include <wrl/module.h>
#undef _CRT_PERROR_DEFINED

#include "s3eWwise_internal.h"

#include "s3eWwise_shim.h"
#include "IwDebug.h"

using namespace s3eWwiseExtension;

s3eResult s3eWwiseInit_platform()
{
    if (s3eWwiseShim::GetInterface() == nullptr)
    {
        IwTrace(WWISE, ("No IManagedS3Es3eWwiseAPI interface. Managed part of s3eWwise extension failed to register."));
        return S3E_RESULT_ERROR;
    }

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eWwiseTerminate_platform()
{
    // Add any platform-specific termination code here
}

s3eBool s3eWwiseMemoryMgrIsInitialized_platform()
{
    return (s3eBool)s3eWwiseShim::GetInterface()->s3eWwiseMemoryMgrIsInitialized_managed();
}

void s3eWwiseMemoryMgrTerm_platform()
{
    s3eWwiseShim::GetInterface()->s3eWwiseMemoryMgrTerm_managed();
}

s3eWwiseResult s3eWwiseMemoryMgrInit_platform(s3eWwiseMemSettings* in_pSettings)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseMemoryMgrInit_managed(in_pSettings);
}

s3eWwiseStreamMgr* s3eWwiseStreamMgrCreate_platform(s3eWwiseStreamMgrSettings* in_settings)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseStreamMgrCreate_managed(in_settings);
}

void s3eWwiseStreamMgrDestroy_platform(s3eWwiseStreamMgr* streamMgr)
{
    s3eWwiseShim::GetInterface()->s3eWwiseStreamMgrDestroy_managed(streamMgr);
}

void s3eWwiseStreamMgrGetDefaultSettings_platform(s3eWwiseStreamMgrSettings* out_settings)
{
    s3eWwiseShim::GetInterface()->s3eWwiseStreamMgrGetDefaultSettings_managed(out_settings);
}

s3eWwiseResult s3eWwiseStreamMgrSetCurrentLanguage_platform(const char* in_pszLanguageName)
{
    Platform::String^ in_pszLanguageName_string = UTF8ToString(in_pszLanguageName);
    return s3eWwiseShim::GetInterface()->s3eWwiseStreamMgrSetCurrentLanguage_managed(in_pszLanguageName_string);
}

s3eBool s3eWwiseSoundEngineIsInitialized_platform()
{
    return (s3eBool)s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineIsInitialized_managed();
}

s3eWwiseResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineInit_managed(in_pSettings, in_pPlatformSettings);
}

void s3eWwiseSoundEngineGetDefaultInitSettings_platform(s3eWwiseInitSettings* out_settings)
{
    s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineGetDefaultInitSettings_managed(out_settings);
}

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(s3eWwisePlatformInitSettings* out_settings)
{
    s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineGetDefaultPlatformInitSettings_managed(out_settings);
}

void s3eWwiseSoundEngineTerm_platform()
{
    s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineTerm_managed();
}

s3eWwiseResult s3eWwiseSoundEngineRenderAudio_platform()
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineRenderAudio_managed();
}

s3eWwisePlayingID s3eWwiseSoundEnginePostEventNamed_platform(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID, uint32 flags = 0)
{
    Platform::String^ in_pszEventName_string = UTF8ToString(in_pszEventName);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEnginePostEventNamed_managed(in_pszEventName_string, in_gameObjectID, 0);
}

s3eWwisePlayingID s3eWwiseSoundEnginePostEventWithID_platform(s3eWwiseUniqueID in_eventID, s3eWwiseGameObjectID in_gameObjectID, uint32 flags = 0)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEnginePostEventWithID_managed(in_eventID, in_gameObjectID, 0);
}

void s3eWwiseSoundEngineStopAll_platform(s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT)
{
    s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineStopAll_managed(S3E_WWISE_INVALID_GAME_OBJECT);
}

void s3eWwiseSoundEngineStopPlayingID_platform(s3eWwisePlayingID in_playingID, s3eWwiseTimeMs in_uTransitionDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear)
{
    s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineStopPlayingID_managed(in_playingID, 0, s3eWwiseCurveInterpolation_Linear);
}

s3eWwiseResult s3eWwiseSoundEngineSetActiveListeners_platform(s3eWwiseGameObjectID in_GameObjectID, uint32 in_uListenerMask)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetActiveListeners_managed(in_GameObjectID, in_uListenerMask);
}

s3eWwiseResult s3eWwiseSoundEngineSetListenerPosition_platform(const s3eWwiseListenerPosition* in_Position, uint32 in_uIndex = 0)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetListenerPosition_managed(in_Position, 0);
}

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueWithID_platform(s3eWwiseRtpcID in_rtpcID, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetRTPCValueWithID_managed(in_rtpcID, in_value, S3E_WWISE_INVALID_GAME_OBJECT, 0, s3eWwiseCurveInterpolation_Linear);
}

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueNamed_platform(const char* in_pszRtpcName, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear)
{
    Platform::String^ in_pszRtpcName_string = UTF8ToString(in_pszRtpcName);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetRTPCValueNamed_managed(in_pszRtpcName_string, in_value, S3E_WWISE_INVALID_GAME_OBJECT, 0, s3eWwiseCurveInterpolation_Linear);
}

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueWithID_platform(s3eWwiseRtpcID in_rtpcID, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineResetRTPCValueWithID_managed(in_rtpcID, S3E_WWISE_INVALID_GAME_OBJECT, 0, s3eWwiseCurveInterpolation_Linear);
}

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueNamed_platform(const char* in_pszRtpcName, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear)
{
    Platform::String^ in_pszRtpcName_string = UTF8ToString(in_pszRtpcName);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineResetRTPCValueNamed_managed(in_pszRtpcName_string, S3E_WWISE_INVALID_GAME_OBJECT, 0, s3eWwiseCurveInterpolation_Linear);
}

s3eWwiseResult s3eWwiseSoundEngineSetSwitchWithID_platform(s3eWwiseSwitchGroupID in_switchGroup, s3eWwiseSwitchStateID in_switchState, s3eWwiseGameObjectID in_gameObjectID)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetSwitchWithID_managed(in_switchGroup, in_switchState, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineSetSwitchNamed_platform(const char* in_pszSwitchGroup, const char* in_pszSwitchState, s3eWwiseGameObjectID in_gameObjectID)
{
    Platform::String^ in_pszSwitchGroup_string = UTF8ToString(in_pszSwitchGroup);
    Platform::String^ in_pszSwitchState_string = UTF8ToString(in_pszSwitchState);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetSwitchNamed_managed(in_pszSwitchGroup_string, in_pszSwitchState_string, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEnginePostTriggerWithID_platform(s3eWwiseTriggerID in_triggerID, s3eWwiseGameObjectID in_gameObjectID)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEnginePostTriggerWithID_managed(in_triggerID, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEnginePostTriggerNamed_platform(const char* in_pszTrigger, s3eWwiseGameObjectID in_gameObjectID)
{
    Platform::String^ in_pszTrigger_string = UTF8ToString(in_pszTrigger);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEnginePostTriggerNamed_managed(in_pszTrigger_string, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineSetStateWithID_platform(s3eWwiseStateGroupID in_stateGroup, s3eWwiseStateID in_state)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetStateWithID_managed(in_stateGroup, in_state);
}

s3eWwiseResult s3eWwiseSoundEngineSetStateNamed_platform(const char* in_pszStateGroup, const char* in_pszState)
{
    Platform::String^ in_pszStateGroup_string = UTF8ToString(in_pszStateGroup);
    Platform::String^ in_pszState_string = UTF8ToString(in_pszState);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetStateNamed_managed(in_pszStateGroup_string, in_pszState_string);
}

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineRegisterGameObj_managed(in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObjWithName_platform(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName)
{
    Platform::String^ in_pszObjName_string = UTF8ToString(in_pszObjName);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineRegisterGameObjWithName_managed(in_gameObjectID, in_pszObjName_string);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineUnregisterGameObj_managed(in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterAllGameObj_platform()
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineUnregisterAllGameObj_managed();
}

s3eWwiseResult s3eWwiseSoundEngineSetPosition_platform(s3eWwiseGameObjectID in_gameObjectID, const s3eWwiseSoundPosition* in_Position)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineSetPosition_managed(in_gameObjectID, in_Position);
}

s3eWwiseResult s3eWwiseSoundEngineClearBanks_platform()
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineClearBanks_managed();
}

s3eWwiseResult s3eWwiseSoundEngineLoadBankNamed_platform(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId, s3eWwiseBankID* out_bankID)
{
    Platform::String^ in_pszString_string = UTF8ToString(in_pszString);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineLoadBankNamed_managed(in_pszString_string, in_memPoolId, out_bankID);
}

s3eWwiseResult s3eWwiseSoundEngineLoadBankWithID_platform(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId in_memPoolId)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineLoadBankWithID_managed(in_bankID, in_memPoolId);
}

s3eWwiseResult s3eWwiseSoundEngineUnloadBankNamed_platform(const char* in_pszString, s3eWwiseMemPoolId* out_memPoolId = NULL)
{
    Platform::String^ in_pszString_string = UTF8ToString(in_pszString);
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineUnloadBankNamed_managed(in_pszString_string, NULL);
}

s3eWwiseResult s3eWwiseSoundEngineUnloadBankWithID_platform(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId* out_memPoolId = NULL)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseSoundEngineUnloadBankWithID_managed(in_bankID, NULL);
}

s3eWwiseResult s3eWwiseMusicEngineInit_platform(s3eWwiseMusicSettings* in_pSettings)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseMusicEngineInit_managed(in_pSettings);
}

void s3eWwiseMusicEngineGetDefaultInitSettings_platform(s3eWwiseMusicSettings* out_settings)
{
    s3eWwiseShim::GetInterface()->s3eWwiseMusicEngineGetDefaultInitSettings_managed(out_settings);
}

void s3eWwiseMusicEngineTerm_platform()
{
    s3eWwiseShim::GetInterface()->s3eWwiseMusicEngineTerm_managed();
}

s3eWwiseResult s3eWwiseCommInit_platform(s3eWwiseCommSettings* in_settings)
{
    return s3eWwiseShim::GetInterface()->s3eWwiseCommInit_managed(in_settings);
}

void s3eWwiseCommGetDefaultInitSettings_platform(s3eWwiseCommSettings* out_settings)
{
    s3eWwiseShim::GetInterface()->s3eWwiseCommGetDefaultInitSettings_managed(out_settings);
}

void s3eWwiseCommTerm_platform()
{
    s3eWwiseShim::GetInterface()->s3eWwiseCommTerm_managed();
}

s3eWwiseResult s3eWwiseLowLevelIOSetBasePath_platform(const char* in_pszBasePath)
{
    Platform::String^ in_pszBasePath_string = UTF8ToString(in_pszBasePath);
    return s3eWwiseShim::GetInterface()->s3eWwiseLowLevelIOSetBasePath_managed(in_pszBasePath_string);
}

s3eWwiseResult s3eWwiseLowLevelIOSetBankPath_platform(const char* in_pszBankPath)
{
    Platform::String^ in_pszBankPath_string = UTF8ToString(in_pszBankPath);
    return s3eWwiseShim::GetInterface()->s3eWwiseLowLevelIOSetBankPath_managed(in_pszBankPath_string);
}

s3eWwiseResult s3eWwiseLowLevelIOSetAudioSrcPath_platform(const char* in_pszAudioSrcPath)
{
    Platform::String^ in_pszAudioSrcPath_string = UTF8ToString(in_pszAudioSrcPath);
    return s3eWwiseShim::GetInterface()->s3eWwiseLowLevelIOSetAudioSrcPath_managed(in_pszAudioSrcPath_string);
}
