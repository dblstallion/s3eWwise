/*
 * windows-specific implementation of the s3eWwise extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eWwise_internal.h"

#include "s3eEdk.h"

#include <AK/SoundEngine/Common/AkSoundEngine.h>

// Necessary memory hooks
namespace AK
{
    // Note: VirtualAllocHook() may be used by I/O pools of the default implementation
    // of the Stream Manager, to allow "true" unbuffered I/O (using FILE_FLAG_NO_BUFFERING
    // - refer to the Windows SDK documentation for more details). This is NOT mandatory;
    // you may implement it with a simple malloc().
    void * VirtualAllocHook(
        void * in_pMemAddress,
        size_t in_size,
        DWORD in_dwAllocationType,
        DWORD in_dwProtect
        )
    {
        return s3eEdkMallocOS(in_size);
    }
    void VirtualFreeHook(
        void * in_pMemAddress,
        size_t in_size,
        DWORD in_dwFreeType
        )
    {
        s3eEdkFreeOS(in_pMemAddress);
    }
}

s3eResult s3eWwiseInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eWwiseTerminate_platform()
{
    // Add any platform-specific termination code here
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
	//platformInitSettings.uSampleRate						= in_pPlatformSettings->uSampleRate;
	platformInitSettings.uNumRefillsInVoice					= in_pPlatformSettings->uNumRefillsInVoice;
	//platformInitSettings.bMuteOtherApps						= in_pPlatformSettings->bMuteOtherApps;

    return (s3eWwiseResult)AK::SoundEngine::Init(&initSettings, &platformInitSettings);
}

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(s3eWwisePlatformInitSettings* out_settings)
{
    AkPlatformInitSettings platformInitSettings;
	AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

	out_settings->fLEngineDefaultPoolRatioThreshold	= platformInitSettings.fLEngineDefaultPoolRatioThreshold;
	out_settings->uLEngineDefaultPoolSize			= platformInitSettings.uLEngineDefaultPoolSize;
	//out_settings->uSampleRate						= platformInitSettings.uSampleRate;
	out_settings->uNumRefillsInVoice				= platformInitSettings.uNumRefillsInVoice;
	//out_settings->bMuteOtherApps					= platformInitSettings.bMuteOtherApps;
}