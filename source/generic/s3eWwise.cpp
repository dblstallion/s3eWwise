/*
Generic implementation of the s3eWwise extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#include "s3eWwise_internal.h"
s3eResult s3eWwiseInit()
{
    //Add any generic initialisation code here
    return s3eWwiseInit_platform();
}

void s3eWwiseTerminate()
{
    //Add any generic termination code here
    s3eWwiseTerminate_platform();
}

s3eBool s3eWwiseMemoryMgrIsInitialized()
{
	return s3eWwiseMemoryMgrIsInitialized_platform();
}

void s3eWwiseMemoryMgrTerm()
{
	s3eWwiseMemoryMgrTerm_platform();
}

s3eWwiseResult s3eWwiseMemoryMgrInit(s3eWwiseMemSettings* in_pSettings)
{
	return s3eWwiseMemoryMgrInit_platform(in_pSettings);
}

s3eWwiseStreamMgr* s3eWwiseStreamMgrCreate(s3eWwiseStreamMgrSettings* in_settings)
{
	return s3eWwiseStreamMgrCreate_platform(in_settings);
}

void s3eWwiseStreamMgrDestroy(s3eWwiseStreamMgr* streamMgr)
{
	s3eWwiseStreamMgrDestroy_platform(streamMgr);
}

void s3eWwiseStreamMgrGetDefaultSettings(s3eWwiseStreamMgrSettings* out_settings)
{
	s3eWwiseStreamMgrGetDefaultSettings_platform(out_settings);
}

s3eBool s3eWwiseSoundEngineIsInitialized()
{
	return s3eWwiseSoundEngineIsInitialized_platform();
}

s3eWwiseResult s3eWwiseSoundEngineInit(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
{
	return s3eWwiseSoundEngineInit_platform(in_pSettings, in_pPlatformSettings);
}

void s3eWwiseSoundEngineGetDefaultInitSettings(s3eWwiseInitSettings* out_settings)
{
	s3eWwiseSoundEngineGetDefaultInitSettings_platform(out_settings);
}

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings(s3eWwisePlatformInitSettings* out_settings)
{
	s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(out_settings);
}

void s3eWwiseSoundEngineTerm()
{
	s3eWwiseSoundEngineTerm_platform();
}

s3eWwiseResult s3eWwiseSoundEngineRenderAudio()
{
	return s3eWwiseSoundEngineRenderAudio_platform();
}

s3eWwisePlayingID s3eWwiseSoundEnginePostEventNamed(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID, uint32 flags)
{
	return s3eWwiseSoundEnginePostEventNamed_platform(in_pszEventName, in_gameObjectID, flags);
}

s3eWwisePlayingID s3eWwiseSoundEnginePostEventWithID(s3eWwiseUniqueID in_eventID, s3eWwiseGameObjectID in_gameObjectID, uint32 flags)
{
	return s3eWwiseSoundEnginePostEventWithID_platform(in_eventID, in_gameObjectID, flags);
}

void s3eWwiseSoundEngineStopAll(s3eWwiseGameObjectID in_gameObjectID)
{
	s3eWwiseSoundEngineStopAll_platform(in_gameObjectID);
}

void s3eWwiseSoundEngineStopPlayingID(s3eWwisePlayingID in_playingID, s3eWwiseTimeMs in_uTransitionDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	s3eWwiseSoundEngineStopPlayingID_platform(in_playingID, in_uTransitionDuration, in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineSetActiveListeners(s3eWwiseGameObjectID in_GameObjectID, uint32 in_uListenerMask)
{
	return s3eWwiseSoundEngineSetActiveListeners_platform(in_GameObjectID, in_uListenerMask);
}

s3eWwiseResult s3eWwiseSoundEngineSetListenerPosition(const s3eWwiseListenerPosition* in_Position, uint32 in_uIndex)
{
	return s3eWwiseSoundEngineSetListenerPosition_platform(in_Position, in_uIndex);
}

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueWithID(s3eWwiseRtpcID in_rtpcID, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return s3eWwiseSoundEngineSetRTPCValueWithID_platform(in_rtpcID, in_value, in_gameObjectID, in_uValueChangeDuration, in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueNamed(const char* in_pszRtpcName, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return s3eWwiseSoundEngineSetRTPCValueNamed_platform(in_pszRtpcName, in_value, in_gameObjectID, in_uValueChangeDuration, in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueWithID(s3eWwiseRtpcID in_rtpcID, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return s3eWwiseSoundEngineResetRTPCValueWithID_platform(in_rtpcID, in_gameObjectID, in_uValueChangeDuration, in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueNamed(const char* in_pszRtpcName, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return s3eWwiseSoundEngineResetRTPCValueNamed_platform(in_pszRtpcName, in_gameObjectID, in_uValueChangeDuration, in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineSetSwitchWithID(s3eWwiseSwitchGroupID in_switchGroup, s3eWwiseSwitchStateID in_switchState, s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEngineSetSwitchWithID_platform(in_switchGroup, in_switchState, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineSetSwitchNamed(const char* in_pszSwitchGroup, const char* in_pszSwitchState, s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEngineSetSwitchNamed_platform(in_pszSwitchGroup, in_pszSwitchState, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEnginePostTriggerWithID(s3eWwiseTriggerID in_triggerID, s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEnginePostTriggerWithID_platform(in_triggerID, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEnginePostTriggerNamed(const char* in_pszTrigger, s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEnginePostTriggerNamed_platform(in_pszTrigger, in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineSetStateWithID(s3eWwiseStateGroupID in_stateGroup, s3eWwiseStateID in_state)
{
	return s3eWwiseSoundEngineSetStateWithID_platform(in_stateGroup, in_state);
}

s3eWwiseResult s3eWwiseSoundEngineSetStateNamed(const char* in_pszStateGroup, const char* in_pszState)
{
	return s3eWwiseSoundEngineSetStateNamed_platform(in_pszStateGroup, in_pszState);
}

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObj(s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEngineRegisterGameObj_platform(in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObjWithName(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName)
{
	return s3eWwiseSoundEngineRegisterGameObjWithName_platform(in_gameObjectID, in_pszObjName);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterGameObj(s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEngineUnregisterGameObj_platform(in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterAllGameObj()
{
	return s3eWwiseSoundEngineUnregisterAllGameObj_platform();
}

s3eWwiseResult s3eWwiseSoundEngineSetPosition(s3eWwiseGameObjectID in_gameObjectID, const s3eWwiseSoundPosition* in_Position, uint32 in_uListenerIndex)
{
	return s3eWwiseSoundEngineSetPosition_platform(in_gameObjectID, in_Position, in_uListenerIndex);
}

s3eWwiseResult s3eWwiseSoundEngineClearBanks()
{
	return s3eWwiseSoundEngineClearBanks_platform();
}

s3eWwiseResult s3eWwiseSoundEngineLoadBankNamed(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId, s3eWwiseBankID* out_bankID)
{
	return s3eWwiseSoundEngineLoadBankNamed_platform(in_pszString, in_memPoolId, out_bankID);
}

s3eWwiseResult s3eWwiseSoundEngineLoadBankWithID(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId in_memPoolId)
{
	return s3eWwiseSoundEngineLoadBankWithID_platform(in_bankID, in_memPoolId);
}

s3eWwiseResult s3eWwiseSoundEngineUnloadBankNamed(const char* in_pszString, s3eWwiseMemPoolId* out_memPoolId)
{
	return s3eWwiseSoundEngineUnloadBankNamed_platform(in_pszString, out_memPoolId);
}

s3eWwiseResult s3eWwiseSoundEngineUnloadBankWithID(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId* out_memPoolId)
{
	return s3eWwiseSoundEngineUnloadBankWithID_platform(in_bankID, out_memPoolId);
}

s3eWwiseResult s3eWwiseMusicEngineInit(s3eWwiseMusicSettings* in_pSettings)
{
	return s3eWwiseMusicEngineInit_platform(in_pSettings);
}

void s3eWwiseMusicEngineGetDefaultInitSettings(s3eWwiseMusicSettings* out_settings)
{
	s3eWwiseMusicEngineGetDefaultInitSettings_platform(out_settings);
}

void s3eWwiseMusicEngineTerm()
{
	s3eWwiseMusicEngineTerm_platform();
}

s3eWwiseResult s3eWwiseCommInit(s3eWwiseCommSettings* in_pSettings)
{
	return s3eWwiseCommInit_platform(in_pSettings);
}

void s3eWwiseCommGetDefaultInitSettings(s3eWwiseCommSettings* out_settings)
{
	s3eWwiseCommGetDefaultInitSettings_platform(out_settings);
}

void s3eWwiseCommTerm()
{
	s3eWwiseCommTerm_platform();
}