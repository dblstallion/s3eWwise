#include "s3eOSReadString.h"
#include "s3eWwise.h"
#include "IwDebug.h"
#include "IwGx.h"
#include "s3eExt.h"
#include "s3ePointer.h"

static s3eWwiseStreamMgr *streamMgr;

void initWwise()
{
    if (!s3eWwiseAvailable())
    {
        s3eDebugOutputString("Can't load Wwise");
        s3eDebugOutputString(s3eExtGetErrorString());
        return;
    }

    s3eDebugOutputString("Successfully loaded s3eWwise extension");

    s3eWwiseMemSettings memSettings;
    memSettings.uMaxNumPools = 10;

    s3eWwiseMemoryMgrInit(&memSettings);
    s3eDebugOutputString("Wwise memory manager init");

    s3eWwiseStreamMgrSettings streamSettings;
    s3eWwiseStreamMgrGetDefaultSettings(&streamSettings);
    streamMgr = s3eWwiseStreamMgrCreate(&streamSettings);
    s3eDebugOutputString("Wwise stream manager init");
}

void shutdownWwise()
{
    s3eWwiseStreamMgrDestroy(streamMgr);

    s3eWwiseMemoryMgrTerm();
    s3eDebugOutputString("Wwise Shutdown");
}

// Example showing how to use the s3eWwise extension
int main()
{
    s3eDebugOutputString("Booting s3eWwise example");

    //s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)touchEvent, NULL);

    IwGxInit();

    IwGxSetColClear(0, 0, 0, 0xff);

    initWwise();

    while(!s3eDeviceCheckQuitRequest())
    {
        IwGxClear();

        IwGxPrintString(100, 100, "s3eWwise");

        IwGxPrintString(100, 300, "Touch to fire event");

        IwGxFlush();
        IwGxSwapBuffers();
        s3eDeviceYield(0);
    }

    shutdownWwise();

    IwGxTerminate();

    return 0;
}