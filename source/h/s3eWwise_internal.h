/*
 * Internal header for the s3eWwise extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#ifndef S3EWWISE_INTERNAL_H
#define S3EWWISE_INTERNAL_H

#include "s3eTypes.h"
#include "s3eWwise.h"
#include "s3eWwise_autodefs.h"

/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eWwiseInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eWwiseInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eWwiseTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eWwiseTerminate_platform();
void s3eWwiseMemoryMgrTerm_platform();

s3eBool s3eWwiseMemoryMgrIsInitialized_platform();

s3eWwiseResult s3eWwiseMemoryMgrInit_platform(s3eWwiseMemSettings* in_pSettings);

s3eWwiseStreamMgr* s3eWwiseStreamMgrCreate_platform(s3eWwiseStreamMgrSettings* in_settings);

void s3eWwiseStreamMgrDestroy_platform(s3eWwiseStreamMgr* streamMgr);

void s3eWwiseStreamMgrGetDefaultSettings_platform(s3eWwiseStreamMgrSettings* out_settings);

s3eBool s3eWwiseSoundEngineIsInitialized_platform();

s3eWwiseResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings);

void s3eWwiseSoundEngineGetDefaultInitSettings_platform(s3eWwiseInitSettings* out_settings);

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(s3eWwisePlatformInitSettings* out_settings);

void s3eWwiseSoundEngineTerm_platform();

s3eWwiseResult s3eWwiseSoundEngineRenderAudio_platform();

s3eWwisePlayingID s3eWwiseSoundEnginePostEventNamed_platform(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID, uint32 flags = 0);

s3eWwisePlayingID s3eWwiseSoundEnginePostEventWithID_platform(s3eWwiseUniqueID in_eventID, s3eWwiseGameObjectID in_gameObjectID, uint32 flags = 0);

void s3eWwiseSoundEngineStopAll_platform(s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT);

void s3eWwiseSoundEngineStopPlayingID_platform(s3eWwisePlayingID in_playingID, s3eWwiseTimeMs in_uTransitionDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear);

s3eWwiseResult s3eWwiseSoundEngineSetActiveListeners_platform(s3eWwiseGameObjectID in_GameObjectID, uint32 in_uListenerMask);

s3eWwiseResult s3eWwiseSoundEngineSetListenerPosition_platform(const s3eWwiseListenerPosition *in_Position, uint32 in_uIndex = 0);

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueWithID_platform(s3eWwiseRtpcID in_rtpcID, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear);

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueNamed_platform(const char* in_pszRtpcName, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear);

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueWithID_platform(s3eWwiseRtpcID in_rtpcID, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear);

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueNamed_platform(const char* in_pszRtpcName, s3eWwiseGameObjectID in_gameObjectID = S3E_WWISE_INVALID_GAME_OBJECT, s3eWwiseTimeMs in_uValueChangeDuration = 0, s3eWwiseCurveInterpolation in_eFadeCurve = s3eWwiseCurveInterpolation_Linear);

s3eWwiseResult s3eWwiseSoundEngineSetSwitchWithID_platform(s3eWwiseSwitchGroupID in_switchGroup, s3eWwiseSwitchStateID in_switchState, s3eWwiseGameObjectID in_gameObjectID);

s3eWwiseResult s3eWwiseSoundEngineSetSwitchNamed_platform(const char* in_pszSwitchGroup, const char* in_pszSwitchState, s3eWwiseGameObjectID in_gameObjectID);

s3eWwiseResult s3eWwiseSoundEnginePostTriggerWithID_platform(s3eWwiseTriggerID in_triggerID, s3eWwiseGameObjectID in_gameObjectID);

s3eWwiseResult s3eWwiseSoundEnginePostTriggerNamed_platform(const char* in_pszTrigger, s3eWwiseGameObjectID in_gameObjectID);

s3eWwiseResult s3eWwiseSoundEngineSetStateWithID_platform(s3eWwiseStateGroupID in_stateGroup, s3eWwiseStateID in_state);

s3eWwiseResult s3eWwiseSoundEngineSetStateNamed_platform(const char *in_pszStateGroup, const char *in_pszState);

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID);

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObjWithName_platform(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName);

s3eWwiseResult s3eWwiseSoundEngineUnregisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID);

s3eWwiseResult s3eWwiseSoundEngineUnregisterAllGameObj_platform();

s3eWwiseResult s3eWwiseSoundEngineSetPosition_platform(s3eWwiseGameObjectID in_gameObjectID, const s3eWwiseSoundPosition* in_Position, uint32 in_uListenerIndex = S3E_WWISE_INVALID_LISTENER_INDEX);

s3eWwiseResult s3eWwiseSoundEngineClearBanks_platform();

s3eWwiseResult s3eWwiseSoundEngineLoadBankNamed_platform(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId, s3eWwiseBankID* out_bankID);

s3eWwiseResult s3eWwiseSoundEngineLoadBankWithID_platform(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId in_memPoolId);

s3eWwiseResult s3eWwiseSoundEngineUnloadBankNamed_platform(const char* in_pszString, s3eWwiseMemPoolId* out_memPoolId = NULL);

s3eWwiseResult s3eWwiseSoundEngineUnloadBankWithID_platform(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId* out_memPoolId = NULL);

s3eWwiseResult s3eWwiseMusicEngineInit_platform(s3eWwiseMusicSettings* in_pSettings);

void s3eWwiseMusicEngineGetDefaultInitSettings_platform(s3eWwiseMusicSettings* out_settings);

void s3eWwiseMusicEngineTerm_platform();

s3eWwiseResult s3eWwiseCommInit_platform(s3eWwiseCommSettings* in_pSettings);

void s3eWwiseCommGetDefaultInitSettings_platform(s3eWwiseCommSettings* out_settings);

void s3eWwiseCommTerm_platform();

#endif /* !S3EWWISE_INTERNAL_H */