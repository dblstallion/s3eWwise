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
    s3eDebugOutputString(streamMgr ? "Wwise stream manager init" : "FAILED TO INIT STREAM");

    s3eWwiseInitSettings settings;
    s3eWwisePlatformInitSettings platformSettings;
    s3eWwiseSoundEngineGetDefaultInitSettings(&settings);
    s3eWwiseSoundEngineGetDefaultPlatformInitSettings(&platformSettings);
    if( s3eWwiseSoundEngineInit(&settings, &platformSettings) != s3eWwise_Success )
        s3eDebugOutputString("Failed to init Wwise");
    else
        s3eDebugOutputString("Init Wwise Successfully");

    s3eWwiseMusicSettings musicSettings;
    s3eWwiseMusicEngineGetDefaultInitSettings(&musicSettings);
    if( s3eWwiseMusicEngineInit(&musicSettings) != s3eWwise_Success )
        s3eDebugOutputString("Failed to init music");
    else
        s3eDebugOutputString("Init Music Successfully");

    s3eWwiseResult loadInit = s3eWwiseSoundEngineLoadBank("iOS/Init.bnk", S3E_WWISE_DEFAULT_POOL_ID);
    if(loadInit  != s3eWwise_Success )
        s3eDebugTracePrintf("Failed to load sound bank. Error code = %d", loadInit);
    else
        s3eDebugOutputString("Loaded sound bank");

    s3eWwiseResult loadHuman = s3eWwiseSoundEngineLoadBank("iOS/Human.bnk", S3E_WWISE_DEFAULT_POOL_ID);
    if( loadHuman != s3eWwise_Success )
        s3eDebugTracePrintf("Failed to load sound bank. Error code = %d", loadHuman);
    else
        s3eDebugOutputString("Loaded sound bank");
}

void shutdownWwise()
{
    s3eWwiseSoundEngineUnloadBank("iOS/Human.bnk");
    s3eWwiseSoundEngineUnloadBank("iOS/Init.bnk");

    s3eWwiseMusicEngineTerm();

    s3eWwiseSoundEngineTerm();

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
        if(s3eWwiseSoundEngineRenderAudio() != s3eWwise_Success)
            s3eDebugOutputString("Error rendering audio");

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