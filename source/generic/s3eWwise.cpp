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

#include "s3eEdk.h"
#include "s3eDevice.h"

#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/MusicEngine/Common/AkMusicEngine.h>
#include <AK/Comm/AkCommunication.h>

// IO System
#ifdef USE_AK_DEFAULT_IO

#include "AkDefaultIOHookBlocking.h"
CAkDefaultIOHookBlocking g_lowLevelIO;

#else

#include "s3eIOHook.h"
#include "AkFilePackageLowLevelIO.h"
s3eFilePackageLowLevelIO g_lowLevelIO;

#endif

// Plugins
#ifdef WWISE_AK_AAC_PLUGIN
#include <AK/Plugin/AkAACFactory.h>
#endif
#ifdef WWISE_AK_ROOM_VERB_PLUGIN
#include <AK/Plugin/AkRoomVerbFXFactory.h>
#endif
#ifdef WWISE_AK_VORBIS_PLUGIN
#include <AK/Plugin/AkVorbisFactory.h>
#endif
#ifdef WWISE_AK_COMPRESSOR_PLUGIN
#include <AK/Plugin/AkCompressorFXFactory.h>
#endif
#ifdef WWISE_AK_PEAK_LIMITER_PLUGIN
#include <AK/Plugin/AkPeakLimiterFXFactory.h>
#endif
#ifdef WWISE_AK_METER_PLUGIN
#include <AK/Plugin/AkMeterFXFactory.h>
#endif
#ifdef WWISE_AK_SILENCE_PLUGIN
#include <AK/Plugin/AkSilenceSourceFactory.h>
#endif

// Necessary memory hooks
namespace AK
{
	void * AllocHook( size_t in_size )
	{
        return malloc(in_size);
	}
	void FreeHook( void * in_ptr )
	{
		free(in_ptr);
	}
}

static int32 applicationUnpaused(void* systemData, void* userData)
{
	AK::SoundEngine::WakeupFromSuspend();

	return 0;
}

static int32 applicationPaused(void* systemData, void* userData)
{
	AK::SoundEngine::Suspend();

	return 0;
}

s3eResult s3eWwiseInit()
{
    if(s3eDeviceRegister(S3E_DEVICE_UNPAUSE, (s3eCallback)applicationUnpaused, NULL) != S3E_RESULT_SUCCESS)
		return S3E_RESULT_ERROR;
		
	if(s3eDeviceRegister(S3E_DEVICE_PAUSE, (s3eCallback)applicationPaused, NULL) != S3E_RESULT_SUCCESS)
		return S3E_RESULT_ERROR;

    //Add any generic initialisation code here
    return s3eWwiseInit_platform();
}

void s3eWwiseTerminate()
{
    s3eDeviceUnRegister(S3E_DEVICE_UNPAUSE, (s3eCallback)applicationUnpaused);
	s3eDeviceUnRegister(S3E_DEVICE_UNPAUSE, (s3eCallback)applicationPaused);

    //Add any generic termination code here
    s3eWwiseTerminate_platform();
}

s3eBool s3eWwiseMemoryMgrIsInitialized()
{
	return AK::MemoryMgr::IsInitialized();
}

void s3eWwiseMemoryMgrTerm()
{
	AK::MemoryMgr::Term();
}

s3eWwiseResult s3eWwiseMemoryMgrInit(s3eWwiseMemSettings* in_pSettings)
{
	AkMemSettings memSettings;
	memSettings.uMaxNumPools = in_pSettings->uMaxNumPools;

    return (s3eWwiseResult)AK::MemoryMgr::Init(&memSettings);
}

s3eWwiseStreamMgr* s3eWwiseStreamMgrCreate(s3eWwiseStreamMgrSettings* in_settings)
{
	AkStreamMgrSettings streamSettings;
	streamSettings.uMemorySize = in_settings->uMemorySize;

	s3eWwiseStreamMgr *ret = (s3eWwiseStreamMgr *)AK::StreamMgr::Create(streamSettings);

	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
	if ( g_lowLevelIO.Init( deviceSettings ) != AK_Success )
	{
		return NULL;
	}

    return ret;
}

void s3eWwiseStreamMgrDestroy(s3eWwiseStreamMgr* streamMgr)
{
	g_lowLevelIO.Term();

	AK::IAkStreamMgr *mgr = (AK::IAkStreamMgr *)streamMgr;

	mgr->Destroy();
}

void s3eWwiseStreamMgrGetDefaultSettings(s3eWwiseStreamMgrSettings* out_settings)
{
	AkStreamMgrSettings streamSettings;

	AK::StreamMgr::GetDefaultSettings(streamSettings);

	out_settings->uMemorySize = streamSettings.uMemorySize;
}

s3eWwiseResult s3eWwiseStreamMgrSetCurrentLanguage(const char *in_pszLanguageName)
{
    AkOSChar *languageName;
    CONVERT_CHAR_TO_OSCHAR(in_pszLanguageName, languageName);
    return (s3eWwiseResult)AK::StreamMgr::SetCurrentLanguage(languageName);
}

s3eBool s3eWwiseSoundEngineIsInitialized()
{
	return AK::SoundEngine::IsInitialized();
}

s3eWwiseResult s3eWwiseSoundEngineInit(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
{
	s3eWwiseResult result = s3eWwiseSoundEngineInit_platform(in_pSettings, in_pPlatformSettings);

    if(result != s3eWwise_Success)
        return result;

    // Plugins
#ifdef WWISE_AK_ROOM_VERB_PLUGIN
    AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_ROOMVERB, CreateRoomVerbFX, CreateRoomVerbFXParams);
#endif
#ifdef WWISE_AK_COMPRESSOR_PLUGIN
    AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_COMPRESSOR, CreateCompressorFX, CreateCompressorFXParams);
#endif
#ifdef WWISE_AK_PEAK_LIMITER_PLUGIN
    AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_PEAKLIMITER, CreatePeakLimiterFX, CreatePeakLimiterFXParams);
#endif
#ifdef WWISE_AK_METER_PLUGIN
    AK::SoundEngine::RegisterPlugin(AkPluginTypeEffect, AKCOMPANYID_AUDIOKINETIC, AKEFFECTID_METER, CreateMeterFX, CreateMeterFXParams);
#endif
#ifdef WWISE_AK_SILENCE_PLUGIN
    AK::SoundEngine::RegisterPlugin(AkPluginTypeSource, AKCOMPANYID_AUDIOKINETIC, AKSOURCEID_SILENCE, CreateSilenceSource, CreateSilenceSourceParams);
#endif

    // Codecs
#ifdef WWISE_AK_AAC_PLUGIN
    AK::SoundEngine::RegisterCodec(AKCOMPANYID_AUDIOKINETIC, AKCODECID_AAC, CreateAACFilePlugin, CreateAACBankPlugin);
#endif
#ifdef WWISE_AK_VORBIS_PLUGIN
    AK::SoundEngine::RegisterCodec(AKCOMPANYID_AUDIOKINETIC, AKCODECID_VORBIS, CreateVorbisFilePlugin, CreateVorbisBankPlugin);
#endif

    return result;
}

void s3eWwiseSoundEngineGetDefaultInitSettings(s3eWwiseInitSettings* out_settings)
{
	AkInitSettings initSettings;
	AK::SoundEngine::GetDefaultInitSettings(initSettings);

	out_settings->pfnAssertHook					= initSettings.pfnAssertHook;
	out_settings->uMaxNumPaths					= initSettings.uMaxNumPaths;
	out_settings->uMaxNumTransitions			= initSettings.uMaxNumTransitions;
	out_settings->uDefaultPoolSize				= initSettings.uDefaultPoolSize;
	out_settings->fDefaultPoolRatioThreshold	= initSettings.fDefaultPoolRatioThreshold;
	out_settings->uCommandQueueSize				= initSettings.uCommandQueueSize;
	out_settings->uPrepareEventMemoryPoolID		= initSettings.uPrepareEventMemoryPoolID;
	out_settings->bEnableGameSyncPreparation	= initSettings.bEnableGameSyncPreparation;
	out_settings->uContinuousPlaybackLookAhead	= initSettings.uContinuousPlaybackLookAhead;
	out_settings->uMonitorPoolSize				= initSettings.uMonitorPoolSize;
	out_settings->uMonitorQueuePoolSize			= initSettings.uMonitorQueuePoolSize;
}

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings(s3eWwisePlatformInitSettings* out_settings)
{
	s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(out_settings);
}

void s3eWwiseSoundEngineTerm()
{
	AK::SoundEngine::Term();
}

s3eWwiseResult s3eWwiseSoundEngineRenderAudio()
{
	return (s3eWwiseResult)AK::SoundEngine::RenderAudio();
}

s3eWwisePlayingID s3eWwiseSoundEnginePostEventNamed(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID, uint32 flags)
{
	return (s3eWwisePlayingID)AK::SoundEngine::PostEvent(in_pszEventName, (AkGameObjectID)in_gameObjectID, flags);
}

s3eWwisePlayingID s3eWwiseSoundEnginePostEventWithID(s3eWwiseUniqueID in_eventID, s3eWwiseGameObjectID in_gameObjectID, uint32 flags)
{
	return (s3eWwisePlayingID)AK::SoundEngine::PostEvent(in_eventID, (AkGameObjectID)in_gameObjectID, flags);
}

void s3eWwiseSoundEngineStopAll(s3eWwiseGameObjectID in_gameObjectID)
{
	AK::SoundEngine::StopAll((AkGameObjectID)in_gameObjectID);
}

void s3eWwiseSoundEngineStopPlayingID(s3eWwisePlayingID in_playingID, s3eWwiseTimeMs in_uTransitionDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	AK::SoundEngine::StopPlayingID((AkPlayingID)in_playingID, (AkTimeMs)in_uTransitionDuration, (AkCurveInterpolation)in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineSetActiveListeners(s3eWwiseGameObjectID in_GameObjectID, uint32 in_uListenerMask)
{
	return (s3eWwiseResult)AK::SoundEngine::SetActiveListeners((AkGameObjectID)in_GameObjectID, in_uListenerMask);
}

s3eWwiseResult s3eWwiseSoundEngineSetListenerPosition(const s3eWwiseListenerPosition* in_Position, uint32 in_uIndex)
{
	// Memory layouts of both structures must be the same
	return (s3eWwiseResult)AK::SoundEngine::SetListenerPosition((const AkListenerPosition &)*in_Position, in_uIndex);
}

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueWithID(s3eWwiseRtpcID in_rtpcID, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return (s3eWwiseResult)AK::SoundEngine::SetRTPCValue((AkRtpcID)in_rtpcID, (AkRtpcValue)in_value, (AkGameObjectID)in_gameObjectID, (AkTimeMs)in_uValueChangeDuration, (AkCurveInterpolation)in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineSetRTPCValueNamed(const char* in_pszRtpcName, s3eWwiseRtpcValue in_value, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return (s3eWwiseResult)AK::SoundEngine::SetRTPCValue(in_pszRtpcName, (AkRtpcValue)in_value, (AkGameObjectID)in_gameObjectID, (AkTimeMs)in_uValueChangeDuration, (AkCurveInterpolation)in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueWithID(s3eWwiseRtpcID in_rtpcID, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return (s3eWwiseResult)AK::SoundEngine::ResetRTPCValue((AkRtpcID)in_rtpcID, (AkGameObjectID)in_gameObjectID, (AkTimeMs)in_uValueChangeDuration, (AkCurveInterpolation)in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineResetRTPCValueNamed(const char* in_pszRtpcName, s3eWwiseGameObjectID in_gameObjectID, s3eWwiseTimeMs in_uValueChangeDuration, s3eWwiseCurveInterpolation in_eFadeCurve)
{
	return (s3eWwiseResult)AK::SoundEngine::ResetRTPCValue(in_pszRtpcName, (AkGameObjectID)in_gameObjectID, (AkTimeMs)in_uValueChangeDuration, (AkCurveInterpolation)in_eFadeCurve);
}

s3eWwiseResult s3eWwiseSoundEngineSetSwitchWithID(s3eWwiseSwitchGroupID in_switchGroup, s3eWwiseSwitchStateID in_switchState, s3eWwiseGameObjectID in_gameObjectID)
{
	return (s3eWwiseResult)AK::SoundEngine::SetSwitch((AkSwitchGroupID)in_switchGroup, (AkSwitchStateID)in_switchState, (AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineSetSwitchNamed(const char* in_pszSwitchGroup, const char* in_pszSwitchState, s3eWwiseGameObjectID in_gameObjectID)
{
	return (s3eWwiseResult)AK::SoundEngine::SetSwitch(in_pszSwitchGroup, in_pszSwitchState, (AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEnginePostTriggerWithID(s3eWwiseTriggerID in_triggerID, s3eWwiseGameObjectID in_gameObjectID)
{
	return (s3eWwiseResult)AK::SoundEngine::PostTrigger((AkTriggerID)in_triggerID, (AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEnginePostTriggerNamed(const char* in_pszTrigger, s3eWwiseGameObjectID in_gameObjectID)
{
	return (s3eWwiseResult)AK::SoundEngine::PostTrigger(in_pszTrigger, (AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineSetStateWithID(s3eWwiseStateGroupID in_stateGroup, s3eWwiseStateID in_state)
{
	return (s3eWwiseResult)AK::SoundEngine::SetState((AkStateGroupID)in_stateGroup, (AkStateID)in_state);
}

s3eWwiseResult s3eWwiseSoundEngineSetStateNamed(const char* in_pszStateGroup, const char* in_pszState)
{
	return (s3eWwiseResult)AK::SoundEngine::SetState(in_pszStateGroup, in_pszState);
}

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObj(s3eWwiseGameObjectID in_gameObjectID)
{
	return (s3eWwiseResult)AK::SoundEngine::RegisterGameObj((AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObjWithName(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName)
{
	return (s3eWwiseResult)AK::SoundEngine::RegisterGameObj((AkGameObjectID)in_gameObjectID, in_pszObjName);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterGameObj(s3eWwiseGameObjectID in_gameObjectID)
{
	return (s3eWwiseResult)AK::SoundEngine::UnregisterGameObj((AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterAllGameObj()
{
	return (s3eWwiseResult)AK::SoundEngine::UnregisterAllGameObj();
}

s3eWwiseResult s3eWwiseSoundEngineSetPosition(s3eWwiseGameObjectID in_gameObjectID, const s3eWwiseSoundPosition* in_Position)
{
	// Memory layouts of both structures must be the same
	return (s3eWwiseResult)AK::SoundEngine::SetPosition((AkGameObjectID)in_gameObjectID, (const AkSoundPosition &)*in_Position);
}

s3eWwiseResult s3eWwiseSoundEngineClearBanks()
{
	return (s3eWwiseResult)AK::SoundEngine::ClearBanks();
}

s3eWwiseResult s3eWwiseSoundEngineLoadBankNamed(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId, s3eWwiseBankID* out_bankID)
{
	 return (s3eWwiseResult)AK::SoundEngine::LoadBank(in_pszString, (AkMemPoolId)in_memPoolId, (AkBankID &)*out_bankID);
}

s3eWwiseResult s3eWwiseSoundEngineLoadBankWithID(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId in_memPoolId)
{
	return (s3eWwiseResult)AK::SoundEngine::LoadBank((AkBankID)in_bankID, (AkMemPoolId)in_memPoolId);
}

s3eWwiseResult s3eWwiseSoundEngineUnloadBankNamed(const char* in_pszString, s3eWwiseMemPoolId* out_memPoolId)
{
	return (s3eWwiseResult)AK::SoundEngine::UnloadBank(in_pszString, (AkMemPoolId*)out_memPoolId);
}

s3eWwiseResult s3eWwiseSoundEngineUnloadBankWithID(s3eWwiseBankID in_bankID, s3eWwiseMemPoolId* out_memPoolId)
{
	return (s3eWwiseResult)AK::SoundEngine::UnloadBank((AkBankID)in_bankID, (AkMemPoolId*)out_memPoolId);
}

s3eWwiseResult s3eWwiseMusicEngineInit(s3eWwiseMusicSettings* in_pSettings)
{
	AkMusicSettings settings;
	settings.fStreamingLookAheadRatio = in_pSettings->fStreamingLookAheadRatio;

	return (s3eWwiseResult)AK::MusicEngine::Init(&settings);
}

void s3eWwiseMusicEngineGetDefaultInitSettings(s3eWwiseMusicSettings* out_settings)
{
	AkMusicSettings settings;
	AK::MusicEngine::GetDefaultInitSettings(settings);

	out_settings->fStreamingLookAheadRatio = settings.fStreamingLookAheadRatio;
}

void s3eWwiseMusicEngineTerm()
{
	AK::MusicEngine::Term();
}

s3eWwiseResult s3eWwiseCommInit(s3eWwiseCommSettings* in_pSettings)
{
#ifndef AK_OPTIMIZED
	AkCommSettings settings;
	AK::Comm::GetDefaultInitSettings(settings);
	settings.uPoolSize					= in_pSettings->uPoolSize;
	settings.ports.uDiscoveryBroadcast	= in_pSettings->ports.uDiscoveryBroadcast;
	settings.ports.uCommand				= in_pSettings->ports.uCommand;
	settings.ports.uNotification		= in_pSettings->ports.uNotification;
	settings.bInitSystemLib				= in_pSettings->bInitSystemLib;

	return (s3eWwiseResult)AK::Comm::Init(settings);
#else
    return s3eWwise_NotImplemented;
#endif
}

void s3eWwiseCommGetDefaultInitSettings(s3eWwiseCommSettings* out_settings)
{
#ifndef AK_OPTIMIZED
	AkCommSettings settings;
	AK::Comm::GetDefaultInitSettings(settings);

	out_settings->uPoolSize					= settings.uPoolSize;
	out_settings->ports.uDiscoveryBroadcast = settings.ports.uDiscoveryBroadcast;
	out_settings->ports.uCommand			= settings.ports.uCommand;
	out_settings->ports.uNotification		= settings.ports.uNotification;
	out_settings->bInitSystemLib			= settings.bInitSystemLib;
#endif
}

void s3eWwiseCommTerm()
{
#ifndef AK_OPTIMIZED
	AK::Comm::Term();
#endif
}

s3eWwiseResult s3eWwiseLowLevelIOSetBasePath(const char* in_pszBasePath)
{
    AkOSChar *basePath;
    CONVERT_CHAR_TO_OSCHAR(in_pszBasePath, basePath);
	return (s3eWwiseResult)g_lowLevelIO.SetBasePath(basePath);
}

s3eWwiseResult s3eWwiseLowLevelIOSetBankPath(const char* in_pszBankPath)
{
    AkOSChar *bankPath;
    CONVERT_CHAR_TO_OSCHAR(in_pszBankPath, bankPath);
	return (s3eWwiseResult)g_lowLevelIO.SetBankPath(bankPath);
}

s3eWwiseResult s3eWwiseLowLevelIOSetAudioSrcPath(const char* in_pszAudioSrcPath)
{
    AkOSChar *audioSrcPath;
    CONVERT_CHAR_TO_OSCHAR(in_pszAudioSrcPath, audioSrcPath);
	return (s3eWwiseResult)g_lowLevelIO.SetAudioSrcPath(audioSrcPath);
}