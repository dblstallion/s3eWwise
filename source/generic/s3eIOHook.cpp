#include "s3eIOHook.h"
#include "s3eTypes.h"
#include "s3eFile.h"
#include "string.h"

#define DEVICE_NAME AKTEXT("S3E Device")

s3eIOHook::s3eIOHook() : m_deviceID( AK_INVALID_DEVICE_ID )
{
}

s3eIOHook::~s3eIOHook()
{
}

AKRESULT s3eIOHook::Init(const AkDeviceSettings &in_deviceSettings)
{
	if ( in_deviceSettings.uSchedulerTypeFlags != AK_SCHEDULER_BLOCKING )
	{
		AKASSERT( !"s3eIOHook I/O hook only works with AK_SCHEDULER_BLOCKING devices" );
		return AK_Fail;
	}

	// If the Stream Manager's File Location Resolver was not set yet, set this object as the
	// File Location Resolver (this I/O hook is also able to resolve file location).
	if ( !AK::StreamMgr::GetFileLocationResolver() )
		AK::StreamMgr::SetFileLocationResolver( this );

	// Create a device in the Stream Manager, specifying this as the hook.
	m_deviceID = AK::StreamMgr::CreateDevice( in_deviceSettings, this );
	if ( m_deviceID != AK_INVALID_DEVICE_ID )
		return AK_Success;

	return AK_Fail;
}

void s3eIOHook::Term()
{
	if ( AK::StreamMgr::GetFileLocationResolver() == this )
		AK::StreamMgr::SetFileLocationResolver( NULL );

	AK::StreamMgr::DestroyDevice( m_deviceID );
}

// Returns a file descriptor for a given file name.
AKRESULT s3eIOHook::Open(const AkOSChar* in_pszFileName, AkOpenMode in_eOpenMode, AkFileSystemFlags *in_pFlags, bool &io_bSyncOpen, AkFileDesc &out_fileDesc)
{
    AkOSChar szFullFilePath[AK_MAX_PATH];
    if ( GetFullFilePath( in_pszFileName, in_pFlags, in_eOpenMode, szFullFilePath ) == AK_Success )
    {
        return OpenInternal(szFullFilePath, in_eOpenMode, in_pFlags, io_bSyncOpen, out_fileDesc);
    }

    return AK_Fail;
}

// Returns a file descriptor for a given file ID.
AKRESULT s3eIOHook::Open(AkFileID in_fileID, AkOpenMode in_eOpenMode, AkFileSystemFlags *in_pFlags, bool &io_bSyncOpen, AkFileDesc &out_fileDesc)
{
    AkOSChar szFullFilePath[AK_MAX_PATH];
    if ( GetFullFilePath( in_fileID, in_pFlags, in_eOpenMode, szFullFilePath ) == AK_Success )
    {
        return OpenInternal(szFullFilePath, in_eOpenMode, in_pFlags, io_bSyncOpen, out_fileDesc);
    }

    return AK_Fail;
}

AKRESULT s3eIOHook::OpenInternal(const AkOSChar* in_pszFileName, AkOpenMode in_eOpenMode, AkFileSystemFlags *in_pFlags, bool &io_bSyncOpen, AkFileDesc &out_fileDesc)
{
	io_bSyncOpen = true;

    const char *mode;
    switch ( in_eOpenMode )
	{
		case AK_OpenModeRead:
			mode = "rb";
			break;
		case AK_OpenModeWrite:
			mode = "wb";
			break;
		case AK_OpenModeWriteOvrwr:
			mode = "w+b";
			break;
		case AK_OpenModeReadWrite:
			mode = "ab";
			break;
		default:
			AKASSERT( !"Invalid open mode" );
			return AK_InvalidParameter;
			break;
	}

    char *filename;
    CONVERT_OSCHAR_TO_CHAR(in_pszFileName, filename);
    s3eFile *file = s3eFileOpen(filename, mode);

	if ( file != NULL )
	{
		out_fileDesc.iFileSize			= s3eFileGetSize(file);
		out_fileDesc.uSector			= 0;
		out_fileDesc.deviceID			= m_deviceID;
		out_fileDesc.pCustomParam		= NULL;
		out_fileDesc.uCustomParamSize	= 0;
        out_fileDesc.hFile              = (AkFileHandle)file;

        return AK_Success;
	}

	return AK_Fail;
}

AKRESULT s3eIOHook::Read(AkFileDesc &in_fileDesc, const AkIoHeuristics &, void *out_pBuffer, AkIOTransferInfo &io_transferInfo)
{
    int32 position = (int32)io_transferInfo.uFilePosition;

	if( s3eFileSeek((s3eFile *)in_fileDesc.hFile, position, S3E_FILESEEK_SET) == S3E_RESULT_SUCCESS )
	{
        uint32 itemsRead = s3eFileRead(out_pBuffer, 1, io_transferInfo.uRequestedSize, (s3eFile *)in_fileDesc.hFile);
		if( itemsRead > 0 )
		   return AK_Success;
	}
	return AK_Fail;
}

AKRESULT s3eIOHook::Write(AkFileDesc &in_fileDesc, const AkIoHeuristics &, void *in_pData, AkIOTransferInfo &io_transferInfo)
{
	int32 position = (int32)io_transferInfo.uFilePosition;

	if( s3eFileSeek((s3eFile *)in_fileDesc.hFile, position, S3E_FILESEEK_SET) == S3E_RESULT_SUCCESS )
	{
		uint32 itemsWritten = s3eFileWrite( in_pData, 1, io_transferInfo.uRequestedSize, (s3eFile *)in_fileDesc.hFile );
		if( itemsWritten > 0 )
		{
			s3eFileFlush( (s3eFile *)in_fileDesc.hFile );
			return AK_Success;
		}
	}
	return AK_Fail;
}

AKRESULT s3eIOHook::Close(AkFileDesc & in_fileDesc)
{
	return s3eFileClose( (s3eFile *)in_fileDesc.hFile ) == S3E_RESULT_SUCCESS ? AK_Success : AK_Fail;
}

AkUInt32 s3eIOHook::GetBlockSize(AkFileDesc &)
{
	// No constraint on block size (file seeking).
    return 1;
}

void s3eIOHook::GetDeviceDesc(AkDeviceDesc &out_deviceDesc)
{
#ifndef AK_OPTIMIZED
	out_deviceDesc.deviceID       = m_deviceID;
	out_deviceDesc.bCanRead       = true;
	out_deviceDesc.bCanWrite      = true;

	AK_OSCHAR_TO_UTF16( out_deviceDesc.szDeviceName, DEVICE_NAME, AK_MONITOR_DEVICENAME_MAXLENGTH );
	out_deviceDesc.uStringSize   = (AkUInt32)AKPLATFORM::AkUtf16StrLen( out_deviceDesc.szDeviceName ) + 1;
#endif
}

// Returns custom profiling data: 1 if file opens are asynchronous, 0 otherwise.
AkUInt32 s3eIOHook::GetDeviceData()
{
	return 0;
}