#include "s3eOSReadString.h"
#include "data/Audio/Wwise_IDs.h"
#include "s3eWwise.h"
#include "IwDebug.h"
#include "IwGx.h"
#include "s3eExt.h"
#include "s3ePointer.h"
#include "s3eFile.h"
#include "s3eSurface.h"
#include <string>
#include <sstream>

static s3eWwiseStreamMgr *streamMgr;
const s3eWwiseGameObjectID gameObjectID = (s3eWwiseGameObjectID)100;
const s3eWwiseGameObjectID carID = (s3eWwiseGameObjectID)200;

void initWwise()
{
    IW_CALLSTACK("initWwise");

    if (!s3eWwiseAvailable())
    {
        s3eDebugOutputString("Can't load Wwise");
        s3eDebugOutputString(s3eExtGetErrorString());
        return;
    }

    s3eDebugOutputString("Successfully loaded s3eWwise extension");

    s3eWwiseMemSettings memSettings;
    memSettings.uMaxNumPools = 10;

    s3eWwiseResult memoryMgr = s3eWwiseMemoryMgrInit(&memSettings);
    if(memoryMgr  != s3eWwise_Success )
        s3eDebugTracePrintf("Failed to init Wwise memory manager. Error code = %d", memoryMgr);
    else
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

    s3eWwiseCommSettings commSettings;
    s3eWwiseCommGetDefaultInitSettings(&commSettings);
    s3eWwiseResult commEngine = s3eWwiseCommInit(&commSettings);
    if( commEngine != s3eWwise_Success )
    {
        std::stringstream ss;
        ss << "Failed to Init Comm: error code = " << commEngine;
        s3eDebugOutputString(ss.str().c_str());
    }
    else
        s3eDebugOutputString("Init Comm Successfully");

    s3eWwiseBankID bankId;

    // Setup paths
    s3eWwiseStreamMgrSetCurrentLanguage("French(Canada)");
    s3eWwiseLowLevelIOSetBasePath("Audio/iOS/");

    s3eDebugOutputString("Path setup done");

    ///s3eWwiseResult loadInit = s3eWwiseSoundEngineLoadBankWithID(AK::BANKS::INIT, S3E_WWISE_DEFAULT_POOL_ID);
    s3eWwiseResult loadInit = s3eWwiseSoundEngineLoadBankNamed("Init.bnk", S3E_WWISE_DEFAULT_POOL_ID, &bankId);
    if(loadInit  != s3eWwise_Success )
    {
        s3eDebugOutputString("Failed to load sound bank");
        s3eDebugTracePrintf("Error code = %d", loadInit);
    }
    else
        s3eDebugOutputString("Loaded sound bank");

    //s3eWwiseResult loadHuman = s3eWwiseSoundEngineLoadBankWithID(AK::BANKS::HUMAN, S3E_WWISE_DEFAULT_POOL_ID);
    s3eWwiseResult loadHuman = s3eWwiseSoundEngineLoadBankNamed("Human.bnk", S3E_WWISE_DEFAULT_POOL_ID, &bankId);
    if( loadHuman != s3eWwise_Success )
    {
        s3eDebugOutputString("Failed to load sound bank");
        s3eDebugTracePrintf("Error code = %d", loadHuman);
    }
    else
        s3eDebugOutputString("Loaded sound bank");

    s3eWwiseResult loadCar = s3eWwiseSoundEngineLoadBankNamed("Car.bnk", S3E_WWISE_DEFAULT_POOL_ID, &bankId);
    if( loadCar != s3eWwise_Success )
    {
        s3eDebugOutputString("Failed to load sound bank");
        s3eDebugTracePrintf("Error code = %d", loadCar);
    }
    else
        s3eDebugOutputString("Loaded sound bank");

    s3eWwiseSoundEngineRegisterGameObjWithName(gameObjectID, "Human");
    s3eWwiseSoundEngineRegisterGameObj(carID);
}

void shutdownWwise()
{
    IW_CALLSTACK("shutdownWwise");

    s3eWwiseSoundEngineUnregisterAllGameObj();

    s3eWwiseSoundEngineClearBanks();

    s3eWwiseCommTerm();

    s3eWwiseMusicEngineTerm();

    s3eWwiseSoundEngineTerm();

    s3eWwiseStreamMgrDestroy(streamMgr);

    s3eWwiseMemoryMgrTerm();
    s3eDebugOutputString("Wwise Shutdown");
}

void buttonEvent(s3ePointerTouchEvent *event)
{
    IW_CALLSTACK("buttonEvent");

    if(event->m_Pressed)
    {
        s3eDebugOutputString("Posting Event \"Play_Hello\"");
        s3eWwiseSoundEnginePostEventWithID(AK::EVENTS::PLAY_HELLO, gameObjectID);

        s3eWwiseSoundEnginePostEventWithID(AK::EVENTS::PLAY_ENGINE, carID);
    }
    else
    {
        s3eWwiseSoundEnginePostEventWithID(AK::EVENTS::STOP_ENGINE, carID);
    }
}

float rpm = 0.0f;
float touchHeight = 0.0f;
float height = 0.0f;

void motionEvent(s3ePointerMotionEvent *event)
{
    IW_CALLSTACK("motionEvent");

    height = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

    touchHeight = (float)event->m_y;
    rpm = (float)event->m_y / (float)height * (10000.0f - 1000.0f) + 1000.0f;
    s3eWwiseSoundEngineSetRTPCValueWithID(AK::GAME_PARAMETERS::RPM, rpm, carID);
}

// Example showing how to use the s3eWwise extension
int main()
{
    IW_CALLSTACK("main");

    s3eDebugOutputString("Booting s3eWwise example");

    initWwise();

    s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)buttonEvent, NULL);
    s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)motionEvent, NULL);

    IwGxInit();

    IwGxSetColClear(0, 0, 0, 0xff);

    while(!s3eDeviceCheckQuitRequest())
    {
        std::stringstream str;

        s3eWwiseSoundEngineRenderAudio();

        IwGxClear();

        IwGxPrintString(100, 100, "s3eWwise");

        IwGxPrintString(100, 300, "Touch to fire event");

        str << "RPM = " << rpm;
        IwGxPrintString(100, 400, str.str().c_str());
        str.str(std::string());

        str << "TH = " << touchHeight;
        IwGxPrintString(100, 500, str.str().c_str());
        str.str(std::string());

        str << "Height = " << height;
        IwGxPrintString(100, 600, str.str().c_str());
        str.str(std::string());

        IwGxFlush();
        IwGxSwapBuffers();
        s3eDeviceYield(0);
    }

    IwGxTerminate();

    s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)buttonEvent);
    s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)motionEvent);

    shutdownWwise();

    return 0;
}