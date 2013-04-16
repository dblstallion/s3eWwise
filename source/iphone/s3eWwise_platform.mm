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

s3eResult s3eWwiseInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void s3eWwiseTerminate_platform()
{
    // Add any platform-specific termination code here
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

s3eResult s3eWwiseStreamMgrCreate_platform(s3eWwiseStreamMgrSettings* in_settings)
{
    return S3E_RESULT_ERROR;
}

void s3eWwiseStreamMgrDestroy_platform()
{
}

void s3eWwiseStreamMgrGetDefaultSettings_platform(s3eWwiseStreamMgrSettings* out_settings)
{
}

s3eBool s3eWwiseSoundEngineIsInitialized_platform()
{
    return S3E_FALSE;
}

s3eResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
{
    return S3E_RESULT_ERROR;
}

void s3eWwiseSoundEngineGetDefaultInitSettings_platform(s3eWwiseInitSettings* out_settings)
{
}

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(s3eWwisePlatformInitSettings* out_settings)
{
}

void s3eWwiseSoundEngineTerm_platform()
{
}

s3eResult s3eWwiseSoundEngineRenderAudio_platform()
{
    return S3E_RESULT_ERROR;
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
    return S3E_RESULT_ERROR;
}

void s3eWwsieMusicEngineGetDefaultInitSettings_platform(s3eWwiseMusicSettings* out_settings)
{
}

void s3eWwiseMusicEngineTerm_platform()
{
}
