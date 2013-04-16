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

s3eResult s3eWwiseMemoryMgrInit(s3eWwiseMemSettings* in_pSettings)
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

s3eResult s3eWwiseSoundEngineInit(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings)
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

s3eResult s3eWwiseSoundEngineRenderAudio()
{
	return s3eWwiseSoundEngineRenderAudio_platform();
}

s3eWwisePlayingID PostEvent(const char* in_pszEventName, s3eWwiseGameObjectID in_gameObjectID)
{
	return PostEvent_platform(in_pszEventName, in_gameObjectID);
}

s3eResult s3eWwiseSoundEngineRegisterGameObj(s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEngineRegisterGameObj_platform(in_gameObjectID);
}

s3eResult s3eWwiseSoundEngineRegisterGameObj(s3eWwiseGameObjectID in_gameObjectID, const char* in_pszObjName)
{
	return s3eWwiseSoundEngineRegisterGameObj_platform(in_gameObjectID, in_pszObjName);
}

s3eResult s3eWwiseSoundEngineUnregisterGameObj(s3eWwiseGameObjectID in_gameObjectID)
{
	return s3eWwiseSoundEngineUnregisterGameObj_platform(in_gameObjectID);
}

s3eResult s3eWwiseSoundEngineUnregisterAllGameObj()
{
	return s3eWwiseSoundEngineUnregisterAllGameObj_platform();
}

s3eResult s3eWwiseSoundEngineLoadBank(const char* in_pszString, s3eWwiseMemPoolId in_memPoolId)
{
	return s3eWwiseSoundEngineLoadBank_platform(in_pszString, in_memPoolId);
}

s3eResult s3eWwiseSoundEngineUnloadBank(const char* in_pszString)
{
	return s3eWwiseSoundEngineUnloadBank_platform(in_pszString);
}

s3eResult s3eWwiseMusicEngineInit(s3eWwiseMusicSettings* in_pSettings)
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