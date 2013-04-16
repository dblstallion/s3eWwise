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
#include <AK/Tools/Common/AkPlatformFuncs.h>

#include <AK/SoundEngine/Common/AkSoundEngine.h>

#include <AK/MusicEngine/Common/AkMusicEngine.h>

#include <stdlib.h>

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

s3eResult s3eWwiseMemoryMgrInit_platform(s3eWwiseMemSettings* in_pSettings)
{
	AkMemSettings memSettings;
	memSettings.uMaxNumPools = in_pSettings->uMaxNumPools;
	
    return AK::MemoryMgr::Init(&memSettings) == AK_Success ? S3E_RESULT_SUCCESS : S3E_RESULT_ERROR;
}

s3eWwiseStreamMgr* s3eWwiseStreamMgrCreate_platform(s3eWwiseStreamMgrSettings* in_settings)
{
	AkStreamMgrSettings streamSettings;
	streamSettings.uMemorySize = in_settings->uMemorySize;
	
    return (s3eWwiseStreamMgr *)AK::StreamMgr::Create(streamSettings);
}

void s3eWwiseStreamMgrDestroy_platform(s3eWwiseStreamMgr* streamMgr)
{
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

s3eResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
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
	
    return AK::SoundEngine::Init(&initSettings, &platformInitSettings) == AK_Success ? S3E_RESULT_SUCCESS : S3E_RESULT_ERROR;
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

s3eResult s3eWwiseSoundEngineRenderAudio_platform()
{
    return AK::SoundEngine::RenderAudio() == AK_Success ? S3E_RESULT_SUCCESS : S3E_RESULT_ERROR;
}

s3eWwisePlayingID PostEvent_platform(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID)
{
    return S3E_WWISE_INVALID_PLAYING_ID;
}

s3eResult s3eWwiseSoundEngineRegisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eWwiseSoundEngineRegisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eWwiseSoundEngineUnregisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eWwiseSoundEngineUnregisterAllGameObj_platform()
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eWwiseSoundEngineLoadBank_platform(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eWwiseSoundEngineUnloadBank_platform(const char* in_pszString)
{
    return S3E_RESULT_ERROR;
}

s3eResult s3eWwiseMusicEngineInit_platform(s3eWwiseMusicSettings* in_pSettings)
{
	AkMusicSettings settings;
	settings.fStreamingLookAheadRatio = in_pSettings->fStreamingLookAheadRatio;

    return AK::MusicEngine::Init(&settings) == AK_Success ? S3E_RESULT_SUCCESS : S3E_RESULT_ERROR;
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
