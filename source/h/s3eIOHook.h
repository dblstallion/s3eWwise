#ifndef S3E_IO_HOOK_H
#define S3E_IO_HOOK_H

#ifdef S3E_ANDROID
#define USE_AK_FILE_HELPERS 1
#endif

#if USE_AK_FILE_HELPERS
#include "AkFileHelpers.h"
#endif

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include "AkFileLocationBase.h"
#include "AkFilePackageLowLevelIO.h"
#include <stdio.h>

class s3eIOHook : public CAkFileLocationBase, public AK::StreamMgr::IAkFileLocationResolver, public AK::StreamMgr::IAkIOHookBlocking
{
public:
    
	s3eIOHook();
	virtual ~s3eIOHook();
    
	AKRESULT Init(const AkDeviceSettings &in_deviceSettings);
	void Term();
    
    virtual AKRESULT Open(const AkOSChar *in_pszFileName, AkOpenMode in_eOpenMode, AkFileSystemFlags *in_pFlags, bool &io_bSyncOpen, AkFileDesc &out_fileDesc);
    virtual AKRESULT Open(AkFileID in_fileID, AkOpenMode in_eOpenMode, AkFileSystemFlags *in_pFlags, bool &io_bSyncOpen, AkFileDesc &out_fileDesc);
    
	virtual AKRESULT Read(AkFileDesc &in_fileDesc, const AkIoHeuristics &in_heuristics, void *out_pBuffer, AkIOTransferInfo &io_transferInfo);
    
	virtual AKRESULT Write(AkFileDesc &in_fileDesc, const AkIoHeuristics &in_heuristics, void *in_pData, AkIOTransferInfo &io_transferInfo);
    
    virtual AKRESULT Close(AkFileDesc &in_fileDesc);
    
	virtual AkUInt32 GetBlockSize(AkFileDesc &in_fileDesc);
    
    virtual void GetDeviceDesc(AkDeviceDesc &out_deviceDesc);
    
	virtual AkUInt32 GetDeviceData();
    
protected:
    AKRESULT OpenInternal(const AkOSChar *in_pszFileName, AkOpenMode in_eOpenMode, AkFileSystemFlags *in_pFlags, bool &io_bSyncOpen, AkFileDesc &out_fileDesc);
    
	AkDeviceID	m_deviceID;
#if USE_AK_FILE_HELPERS
    CAkFileHelpers m_helper;
#endif
};

class s3eFilePackageLowLevelIO : public CAkFilePackageLowLevelIO<s3eIOHook>
{
public:
	s3eFilePackageLowLevelIO() {}
	virtual ~s3eFilePackageLowLevelIO() {}
	
	virtual void InitFileDesc( CAkDiskPackage * in_pPackage, AkFileDesc & io_fileDesc)
	{
		//On android, pCustomParam must point to the location object.
		io_fileDesc.pCustomParam = in_pPackage->GetFileDesc()->pCustomParam;
	}
};

#endif