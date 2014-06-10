/*
C# implementation of the s3eWwise extension.

Add win8-specific functionality here.

These functions are called via Shim class from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
using System.Windows.Controls;
using Microsoft.Phone.Controls;
using System.Windows.Media;
        

using s3e_native;
using s3eWwiseExtension;

namespace s3eWwiseManaged
{
    public  class s3eWwiseManaged: IManagedS3Es3eWwiseAPI, IManagedS3EEDKAPI
    {
        

        public bool ExtRegister(IS3EAPIManager apiManager, object mainPage)
        {
            try
            {
                // Keep a reference to the API Manager in order to call other
                // APIs.
                m_APIManager = apiManager;
                m_MainPage = mainPage as PhoneApplicationPage;
                m_MainPanel = VisualTreeHelper.GetChild(m_MainPage, 0) as Panel;

                // Add the managed API to the API Manager
                if (!m_APIManager.RegisterManagedAPI("s3eWwise", this))
                    throw new System.Exception("Can't register Managed API");

                // Add the native API to the API manager.  Note that we don't own the native
                // interface, the API Manager does.  We want the two notions of managed and
                // native interface to be separate as there may be cases where we only want
                // one not the other.  It's only a matter of convenience that we create both
                // APIs in this ctr
                m_Native = new s3eWwiseNativeInterface();
                if (!m_APIManager.RegisterNativeAPI("s3eWwise", m_Native))
                    throw new System.Exception("Can't register Native API");

                // Create a Shim so we can pass the Managed interface down to native
                m_Shim = new s3eWwiseShim();

                // Pass the managed interface down
                m_Shim.Init(this);
            }
            catch (System.Exception e)
            {
                m_APIManager = null;
                m_Shim = null;
                m_Native = null;
                System.Windows.MessageBox.Show("Failed to register s3eWwise : " + e.Message);
                
                return false;
            }
            
            return true;
        }
        IS3EAPIManager m_APIManager = null;
        PhoneApplicationPage m_MainPage = null;
        // hint: add UI Elements as children of m_MainPanel
        Panel m_MainPanel = null;
        s3eWwiseShim m_Shim = null;
        s3eWwiseNativeInterface m_Native = null;

        // managed platform functionality


        public bool s3eWwiseMemoryMgrIsInitialized_managed()
        {
            return false;
        }

        public void s3eWwiseMemoryMgrTerm_managed()
        {
            
        }

        public FIXME s3eWwiseMemoryMgrInit_managed(FIXME in_pSettings)
        {
            return 0;
        }

        public FIXME s3eWwiseStreamMgrCreate_managed(FIXME in_settings)
        {
            return 0;
        }

        public void s3eWwiseStreamMgrDestroy_managed(FIXME streamMgr)
        {
            
        }

        public void s3eWwiseStreamMgrGetDefaultSettings_managed(FIXME out_settings)
        {
            
        }

        public FIXME s3eWwiseStreamMgrSetCurrentLanguage_managed(string in_pszLanguageName)
        {
            return 0;
        }

        public bool s3eWwiseSoundEngineIsInitialized_managed()
        {
            return false;
        }

        public FIXME s3eWwiseSoundEngineInit_managed(FIXME in_pSettings, FIXME in_pPlatformSettings)
        {
            return 0;
        }

        public void s3eWwiseSoundEngineGetDefaultInitSettings_managed(FIXME out_settings)
        {
            
        }

        public void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_managed(FIXME out_settings)
        {
            
        }

        public void s3eWwiseSoundEngineTerm_managed()
        {
            
        }

        public FIXME s3eWwiseSoundEngineRenderAudio_managed()
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEnginePostEventNamed_managed(string in_pszEventName, FIXME in_gameObjectID, FIXME 0)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEnginePostEventWithID_managed(FIXME in_eventID, FIXME in_gameObjectID, FIXME 0)
        {
            return 0;
        }

        public void s3eWwiseSoundEngineStopAll_managed(FIXME S3E_WWISE_INVALID_GAME_OBJECT)
        {
            
        }

        public void s3eWwiseSoundEngineStopPlayingID_managed(FIXME in_playingID, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear)
        {
            
        }

        public FIXME s3eWwiseSoundEngineSetActiveListeners_managed(FIXME in_GameObjectID, uint in_uListenerMask)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetListenerPosition_managed(FIXME in_Position, FIXME 0)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetRTPCValueWithID_managed(FIXME in_rtpcID, FIXME in_value, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetRTPCValueNamed_managed(string in_pszRtpcName, FIXME in_value, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineResetRTPCValueWithID_managed(FIXME in_rtpcID, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineResetRTPCValueNamed_managed(string in_pszRtpcName, FIXME S3E_WWISE_INVALID_GAME_OBJECT, FIXME 0, FIXME s3eWwiseCurveInterpolation_Linear)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetSwitchWithID_managed(FIXME in_switchGroup, FIXME in_switchState, FIXME in_gameObjectID)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetSwitchNamed_managed(string in_pszSwitchGroup, string in_pszSwitchState, FIXME in_gameObjectID)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEnginePostTriggerWithID_managed(FIXME in_triggerID, FIXME in_gameObjectID)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEnginePostTriggerNamed_managed(string in_pszTrigger, FIXME in_gameObjectID)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetStateWithID_managed(FIXME in_stateGroup, FIXME in_state)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetStateNamed_managed(string in_pszStateGroup, string in_pszState)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineRegisterGameObj_managed(FIXME in_gameObjectID)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineRegisterGameObjWithName_managed(FIXME in_gameObjectID, string in_pszObjName)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineUnregisterGameObj_managed(FIXME in_gameObjectID)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineUnregisterAllGameObj_managed()
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineSetPosition_managed(FIXME in_gameObjectID, FIXME in_Position)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineClearBanks_managed()
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineLoadBankNamed_managed(string in_pszString, FIXME in_memPoolId, FIXME out_bankID)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineLoadBankWithID_managed(FIXME in_bankID, FIXME in_memPoolId)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineUnloadBankNamed_managed(string in_pszString, FIXME NULL)
        {
            return 0;
        }

        public FIXME s3eWwiseSoundEngineUnloadBankWithID_managed(FIXME in_bankID, FIXME NULL)
        {
            return 0;
        }

        public FIXME s3eWwiseMusicEngineInit_managed(FIXME in_pSettings)
        {
            return 0;
        }

        public void s3eWwiseMusicEngineGetDefaultInitSettings_managed(FIXME out_settings)
        {
            
        }

        public void s3eWwiseMusicEngineTerm_managed()
        {
            
        }

        public FIXME s3eWwiseCommInit_managed(FIXME in_settings)
        {
            return 0;
        }

        public void s3eWwiseCommGetDefaultInitSettings_managed(FIXME out_settings)
        {
            
        }

        public void s3eWwiseCommTerm_managed()
        {
            
        }

        public FIXME s3eWwiseLowLevelIOSetBasePath_managed(string in_pszBasePath)
        {
            return 0;
        }

        public FIXME s3eWwiseLowLevelIOSetBankPath_managed(string in_pszBankPath)
        {
            return 0;
        }

        public FIXME s3eWwiseLowLevelIOSetAudioSrcPath_managed(string in_pszAudioSrcPath)
        {
            return 0;
        }
    }
}
