/*
 * iphone-specific implementation of the s3eWwise extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eWwise_internal.h"

#include "s3eDevice.h"

#include <AK/SoundEngine/Common/AkSoundEngine.h>

static int32 applicationUnpaused(void* systemData, void* userData)
{
	AK::SoundEngine::iOS::ListenToAudioSessionInterruption(false);

	return 0;
}

static int32 applicationPaused(void* systemData, void* userData)
{
	AK::SoundEngine::iOS::ListenToAudioSessionInterruption(true);

	return 0;
}

s3eResult s3eWwiseInit_platform()
{
    if(s3eDeviceRegister(S3E_DEVICE_UNPAUSE, (s3eCallback)applicationUnpaused, NULL) != S3E_RESULT_SUCCESS)
		return S3E_RESULT_ERROR;
		
	if(s3eDeviceRegister(S3E_DEVICE_PAUSE, (s3eCallback)applicationPaused, NULL) != S3E_RESULT_SUCCESS)
		return S3E_RESULT_ERROR;
	
    return S3E_RESULT_SUCCESS;
}

void s3eWwiseTerminate_platform()
{
    s3eDeviceUnRegister(S3E_DEVICE_UNPAUSE, (s3eCallback)applicationUnpaused);
	s3eDeviceUnRegister(S3E_DEVICE_UNPAUSE, (s3eCallback)applicationPaused);
}

s3eWwiseResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
{
	AkInitSettings initSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
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