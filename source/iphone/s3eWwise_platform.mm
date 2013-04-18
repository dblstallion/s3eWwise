/*
 * iphone-specific implementation of the s3eWwise extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eWwise_internal.h"

#include <AK/SoundEngine/Common/AkMemoryMgr.h>
#include <AK/SoundEngine/Common/AkModule.h>

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>

#include "s3eIOHook.h"
#include "AkFilePackageLowLevelIO.h"

#include <AK/SoundEngine/Common/AkSoundEngine.h>

#include <AK/MusicEngine/Common/AkMusicEngine.h>

#include <stdlib.h>

// We're using the default Low-Level I/O implementation that's part
// of the SDK's sample code, with the file package extension
CAkFilePackageLowLevelIO<s3eIOHook> g_lowLevelIO;

s3eResult s3eWwiseInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eWwiseTerminate_platform()
{
    // Add any platform-specific termination code here
}

// Necessary memory hooks
namespace AK
{
	void * AllocHook( size_t in_size )
	{
		return malloc( in_size );
	}
	void FreeHook( void * in_ptr )
	{
		free( in_ptr );
	}
}

s3eBool s3eWwiseMemoryMgrIsInitialized_platform()
{
    return AK::MemoryMgr::IsInitialized();
}

void s3eWwiseMemoryMgrTerm_platform()
{
	AK::MemoryMgr::Term();
}

s3eWwiseResult s3eWwiseMemoryMgrInit_platform(s3eWwiseMemSettings* in_pSettings)
{
	AkMemSettings memSettings;
	memSettings.uMaxNumPools = in_pSettings->uMaxNumPools;
	
    return (s3eWwiseResult)AK::MemoryMgr::Init(&memSettings);
}

s3eWwiseStreamMgr* s3eWwiseStreamMgrCreate_platform(s3eWwiseStreamMgrSettings* in_settings)
{
	AkStreamMgrSettings streamSettings;
	streamSettings.uMemorySize = in_settings->uMemorySize;

	s3eWwiseStreamMgr *ret = (s3eWwiseStreamMgr *)AK::StreamMgr::Create(streamSettings);

	AkDeviceSettings deviceSettings;
	AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
	g_lowLevelIO.Init(deviceSettings);
	
    return ret;
}

void s3eWwiseStreamMgrDestroy_platform(s3eWwiseStreamMgr* streamMgr)
{
	g_lowLevelIO.Term();

	AK::IAkStreamMgr *mgr = (AK::IAkStreamMgr *)streamMgr;
	
	mgr->Destroy();
}

void s3eWwiseStreamMgrGetDefaultSettings_platform(s3eWwiseStreamMgrSettings* out_settings)
{
	AkStreamMgrSettings streamSettings;
	
	AK::StreamMgr::GetDefaultSettings(streamSettings);
	
	out_settings->uMemorySize = streamSettings.uMemorySize;
}

s3eBool s3eWwiseSoundEngineIsInitialized_platform()
{
    return AK::SoundEngine::IsInitialized();
}

s3eWwiseResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
{
	AkInitSettings initSettings;
	initSettings.pfnAssertHook					= in_pSettings->pfnAssertHook;
	initSettings.uMaxNumPaths					= in_pSettings->uMaxNumPaths;
	initSettings.uMaxNumTransitions				= in_pSettings->uMaxNumTransitions;
	initSettings.uDefaultPoolSize				= in_pSettings->uDefaultPoolSize;
	initSettings.fDefaultPoolRatioThreshold		= in_pSettings->fDefaultPoolRatioThreshold;
	initSettings.uCommandQueueSize				= in_pSettings->uCommandQueueSize;
	initSettings.uPrepareEventMemoryPoolID		= in_pSettings->uPrepareEventMemoryPoolID;
	initSettings.bEnableGameSyncPreparation		= in_pSettings->bEnableGameSyncPreparation;
	initSettings.uContinuousPlaybackLookAhead	= in_pSettings->uContinuousPlaybackLookAhead;
	initSettings.uMonitorPoolSize				= in_pSettings->uMonitorPoolSize;
	initSettings.uMonitorQueuePoolSize			= in_pSettings->uMonitorQueuePoolSize;
	
	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
	platformInitSettings.fLEngineDefaultPoolRatioThreshold	= in_pPlatformSettings->fLEngineDefaultPoolRatioThreshold;
	platformInitSettings.uLEngineDefaultPoolSize			= in_pPlatformSettings->uLEngineDefaultPoolSize;
	platformInitSettings.uSampleRate						= in_pPlatformSettings->uSampleRate;
	platformInitSettings.uNumRefillsInVoice					= in_pPlatformSettings->uNumRefillsInVoice;
	platformInitSettings.bMuteOtherApps						= in_pPlatformSettings->bMuteOtherApps;
	
    return (s3eWwiseResult)AK::SoundEngine::Init(&initSettings, &platformInitSettings);
}

void s3eWwiseSoundEngineGetDefaultInitSettings_platform(s3eWwiseInitSettings* out_settings)
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

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(s3eWwisePlatformInitSettings* out_settings)
{
	AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	out_settings->fLEngineDefaultPoolRatioThreshold	= platformInitSettings.fLEngineDefaultPoolRatioThreshold;
	out_settings->uLEngineDefaultPoolSize			= platformInitSettings.uLEngineDefaultPoolSize;
	out_settings->uSampleRate						= platformInitSettings.uSampleRate;
	out_settings->uNumRefillsInVoice				= platformInitSettings.uNumRefillsInVoice;
	out_settings->bMuteOtherApps					= platformInitSettings.bMuteOtherApps;
}

void s3eWwiseSoundEngineTerm_platform()
{
	AK::SoundEngine::Term();
}

s3eWwiseResult s3eWwiseSoundEngineRenderAudio_platform()
{
    return (s3eWwiseResult)AK::SoundEngine::RenderAudio();
}

s3eWwisePlayingID s3eWwiseSoundEnginePostEvent_platform(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID)
{
    return (s3eWwisePlayingID)AK::SoundEngine::PostEvent(in_pszEventName, (AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineRegisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName)
{
    return (s3eWwiseResult)AK::SoundEngine::RegisterGameObj((AkGameObjectID)in_gameObjectID, in_pszObjName);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID)
{
    return (s3eWwiseResult)AK::SoundEngine::UnregisterGameObj((AkGameObjectID)in_gameObjectID);
}

s3eWwiseResult s3eWwiseSoundEngineUnregisterAllGameObj_platform()
{
    return (s3eWwiseResult)AK::SoundEngine::UnregisterAllGameObj();
}

s3eWwiseResult s3eWwiseSoundEngineLoadBank_platform(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId)
{
	AkBankID bankId;
    return (s3eWwiseResult)AK::SoundEngine::LoadBank(in_pszString, (AkMemPoolId)in_memPoolId, bankId);
}

s3eWwiseResult s3eWwiseSoundEngineUnloadBank_platform(const char* in_pszString)
{
    return (s3eWwiseResult)AK::SoundEngine::UnloadBank(in_pszString);
}

s3eWwiseResult s3eWwiseMusicEngineInit_platform(s3eWwiseMusicSettings* in_pSettings)
{
	AkMusicSettings settings;
	settings.fStreamingLookAheadRatio = in_pSettings->fStreamingLookAheadRatio;

	return (s3eWwiseResult)AK::MusicEngine::Init(&settings);
}

void s3eWwiseMusicEngineGetDefaultInitSettings_platform(s3eWwiseMusicSettings* out_settings)
{
	AkMusicSettings settings;
	AK::MusicEngine::GetDefaultInitSettings(settings);

	out_settings->fStreamingLookAheadRatio = settings.fStreamingLookAheadRatio;
}

void s3eWwiseMusicEngineTerm_platform()
{
	AK::MusicEngine::Term();
}
