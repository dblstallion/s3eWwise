#ifndef S3E_IO_HOOK_H
#define S3E_IO_HOOK_H

#include <AK/SoundEngine/Common/AkStreamMgrModule.h>

class s3eIOHook : public AK::StreamMgr::IAkFileLocationResolver, public AK::StreamMgr::IAkIOHookBlocking
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
	AkDeviceID	m_deviceID;
};

#endif
