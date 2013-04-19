#include "s3eOSReadString.h"
#include "Wwise_IDs.h"
#include "s3eWwise.h"
#include "IwDebug.h"
#include "IwGx.h"
#include "s3eExt.h"
#include "s3ePointer.h"
#include "s3eFile.h"

static s3eWwiseStreamMgr *streamMgr;
const s3eWwiseGameObjectID gameObjectID = (s3eWwiseGameObjectID)100;

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
    s3eWwiseResult soundEngine = s3eWwiseSoundEngineInit(&settings, &platformSettings);
    if(soundEngine  != s3eWwise_Success )
        s3eDebugTracePrintf("Failed to init Wwise. Error code = %d", soundEngine);
    else
        s3eDebugOutputString("Init Wwise Successfully");

    s3eWwiseMusicSettings musicSettings;
    s3eWwiseMusicEngineGetDefaultInitSettings(&musicSettings);
    s3eWwiseResult musicEngine = s3eWwiseMusicEngineInit(&musicSettings);
    if( musicEngine != s3eWwise_Success )
        s3eDebugTracePrintf("Failed to init music. Error code = %d", musicEngine);
    else
        s3eDebugOutputString("Init Music Successfully");

    s3eWwiseBankID bankId;

    //s3eWwiseResult loadInit = s3eWwiseSoundEngineLoadBankWithID(AK::BANKS::INIT, S3E_WWISE_DEFAULT_POOL_ID);
    s3eWwiseResult loadInit = s3eWwiseSoundEngineLoadBankNamed("iOS/Init.bnk", S3E_WWISE_DEFAULT_POOL_ID, &bankId);
    if(loadInit  != s3eWwise_Success )
    {
        s3eDebugOutputString("Failed to load sound bank");
        s3eDebugTracePrintf("Error code = %d", loadInit);
    }
    else
        s3eDebugOutputString("Loaded sound bank");

    //s3eWwiseResult loadHuman = s3eWwiseSoundEngineLoadBankWithID(AK::BANKS::HUMAN, S3E_WWISE_DEFAULT_POOL_ID);
    s3eWwiseResult loadHuman = s3eWwiseSoundEngineLoadBankNamed("iOS/English(US)/Human.bnk", S3E_WWISE_DEFAULT_POOL_ID, &bankId);
    if( loadHuman != s3eWwise_Success )
    {
        s3eDebugOutputString("Failed to load sound bank");
        s3eDebugTracePrintf("Error code = %d", loadHuman);
    }
    else
        s3eDebugOutputString("Loaded sound bank");

    s3eWwiseSoundEngineRegisterGameObjWithName(gameObjectID, "Human");
}

void shutdownWwise()
{
    s3eWwiseSoundEngineUnregisterAllGameObj();

    s3eWwiseSoundEngineUnloadBankNamed("iOS/Init.bnk");
    s3eWwiseSoundEngineUnloadBankNamed("iOS/English(US)/Human.bnk");

    s3eWwiseMusicEngineTerm();

    s3eWwiseSoundEngineTerm();

    s3eWwiseStreamMgrDestroy(streamMgr);

    s3eWwiseMemoryMgrTerm();
    s3eDebugOutputString("Wwise Shutdown");
}

void touchEvent(s3ePointerTouchEvent *event)
{
    if(event->m_Pressed)
    {
        s3eDebugOutputString("Posting Event \"Play_Hello\"");
        s3eWwiseSoundEnginePostEventWithID(AK::EVENTS::PLAY_HELLO, gameObjectID);
    }
}

// Example showing how to use the s3eWwise extension
int main()
{
    s3eDebugOutputString("Booting s3eWwise example");

    s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)touchEvent, NULL);

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