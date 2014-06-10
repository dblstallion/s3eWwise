/*
C++ Shim implementation of the s3eWwise extension's.

Not intended for modifications

These functions are called by C# to access native interface and from C++ to
access managed interface.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "s3eWwise_shim.h"

using namespace s3eWwiseExtension;


IManagedS3Es3eWwiseAPI^ s3eWwiseShim::s_ManagedInterface = nullptr;

s3eWwiseShim::s3eWwiseShim()
{
}

s3eWwiseShim::~s3eWwiseShim()
{
    Terminate();
}

bool s3eWwiseShim::Init(IManagedS3Es3eWwiseAPI^ managedAPI)
{
    // It's an error to do this twice.
    if (s_ManagedInterface)
        return false;

    s_ManagedInterface = managedAPI;
    return true;
}

bool s3eWwiseShim::Terminate()
{
    // It's an error to do this twice.
    if (!s_ManagedInterface)
        return false;

    s_ManagedInterface = nullptr;
    return true;
}

IManagedS3Es3eWwiseAPI^ s3eWwiseShim::GetInterface()
{
    return s_ManagedInterface;
}
