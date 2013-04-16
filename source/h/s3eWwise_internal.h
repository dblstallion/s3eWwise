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
s3eBool s3eWwiseMemoryMgrIsInitialized_platform();

void s3eWwiseMemoryMgrTerm_platform();

s3eResult s3eWwiseMemoryMgrInit_platform(s3eWwiseMemSettings* in_pSettings);

s3eWwiseStreamMgr* s3eWwiseStreamMgrCreate_platform(s3eWwiseStreamMgrSettings* in_settings);

void s3eWwiseStreamMgrDestroy_platform(s3eWwiseStreamMgr* streamMgr);

void s3eWwiseStreamMgrGetDefaultSettings_platform(s3eWwiseStreamMgrSettings* out_settings);

s3eBool s3eWwiseSoundEngineIsInitialized_platform();

s3eResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings);

void s3eWwiseSoundEngineGetDefaultInitSettings_platform(s3eWwiseInitSettings* out_settings);

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(s3eWwisePlatformInitSettings* out_settings);

void s3eWwiseSoundEngineTerm_platform();

s3eResult s3eWwiseSoundEngineRenderAudio_platform();

s3eWwisePlayingID PostEvent_platform(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID);

s3eResult s3eWwiseSoundEngineRegisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID);

s3eResult s3eWwiseSoundEngineRegisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName);

s3eResult s3eWwiseSoundEngineUnregisterGameObj_platform(s3eWwiseGameObjectID in_gameObjectID);

s3eResult s3eWwiseSoundEngineUnregisterAllGameObj_platform();

s3eResult s3eWwiseSoundEngineLoadBank_platform(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId);

s3eResult s3eWwiseSoundEngineUnloadBank_platform(const char* in_pszString);

s3eResult s3eWwiseMusicEngineInit_platform(s3eWwiseMusicSettings* in_pSettings);

void s3eWwsieMusicEngineGetDefaultInitSettings_platform(s3eWwiseMusicSettings* out_settings);

void s3eWwiseMusicEngineTerm_platform();


#endif /* !S3EWWISE_INTERNAL_H */