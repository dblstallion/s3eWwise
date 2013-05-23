/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Audiokinetic Wwise generated include file. Do not edit.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __WWISE_IDS_H__
#define __WWISE_IDS_H__

#include <AK/SoundEngine/Common/AkTypes.h>

namespace AK
{
    namespace EVENTS
    {
        static const AkUniqueID DISABLE_MICROPHONE_DELAY = 6251382U;
        static const AkUniqueID DOORSLIDING = 679837841U;
        static const AkUniqueID ENABLE_MICROPHONE_DELAY = 3533161767U;
        static const AkUniqueID GUNFIRE = 2975448509U;
        static const AkUniqueID IM_1_ONE_ENEMY_WANTS_TO_FIGHT = 2221704914U;
        static const AkUniqueID IM_2_TWO_ENEMIES_WANT_TO_FIGHT = 3753105098U;
        static const AkUniqueID IM_3_SURRONDED_BY_ENEMIES = 1350929071U;
        static const AkUniqueID IM_4_DEATH_IS_COMING = 3175089270U;
        static const AkUniqueID IM_COMMUNICATION_BEGIN = 2160840676U;
        static const AkUniqueID IM_EXPLORE = 3280047539U;
        static const AkUniqueID IM_GAMEOVER = 3455955770U;
        static const AkUniqueID IM_START = 3952084898U;
        static const AkUniqueID IM_THEYAREHOSTILE = 2841817544U;
        static const AkUniqueID IM_WINTHEFIGHT = 1133905385U;
        static const AkUniqueID PAUSE_ALL = 3864097025U;
        static const AkUniqueID PLAY_ENGINE = 639345804U;
        static const AkUniqueID PLAY_FOOTSTEPS = 3854155799U;
        static const AkUniqueID PLAY_HELLO = 2952797154U;
        static const AkUniqueID PLAY_HELLO_RSX = 330151568U;
        static const AkUniqueID PLAY_MARKERS_TEST = 3368417626U;
        static const AkUniqueID PLAY_MICROPHONE = 1324678662U;
        static const AkUniqueID PLAY_POSITIONING_DEMO = 1237313597U;
        static const AkUniqueID PLAY_THREE_NUMBERS_IN_A_ROW = 4142087708U;
        static const AkUniqueID PLAYMUSICDEMO1 = 519773714U;
        static const AkUniqueID RESUME_ALL = 3679762312U;
        static const AkUniqueID STOP_ALL = 452547817U;
        static const AkUniqueID STOP_ENGINE = 37214798U;
        static const AkUniqueID STOP_MICROPHONE = 3629954576U;
    } // namespace EVENTS

    namespace DIALOGUE_EVENTS
    {
        static const AkUniqueID OBJECTIVE_STATUS = 3970659059U;
        static const AkUniqueID UNIT_UNDER_ATTACK = 3585983975U;
        static const AkUniqueID WALKIETALKIE = 4110439188U;
    } // namespace DIALOGUE_EVENTS

    namespace STATES
    {
        namespace MUSIC
        {
            static const AkUniqueID GROUP = 3991942870U;

            namespace STATE
            {
                static const AkUniqueID EXPLORING = 1823678183U;
                static const AkUniqueID FIGHT = 514064485U;
                static const AkUniqueID FIGHT_DAMAGED = 886139701U;
                static const AkUniqueID FIGHT_DYING = 4222988787U;
                static const AkUniqueID FIGHT_LOWHEALTH = 1420167880U;
                static const AkUniqueID GAMEOVER = 4158285989U;
                static const AkUniqueID PLAYING = 1852808225U;
                static const AkUniqueID WINNING_THEFIGHT = 1323211483U;
            } // namespace STATE
        } // namespace MUSIC

        namespace PLAYERHEALTH
        {
            static const AkUniqueID GROUP = 151362964U;

            namespace STATE
            {
                static const AkUniqueID BLASTED = 868398962U;
                static const AkUniqueID NORMAL = 1160234136U;
            } // namespace STATE
        } // namespace PLAYERHEALTH

    } // namespace STATES

    namespace SWITCHES
    {
        namespace FOOTSTEP_GAIT
        {
            static const AkUniqueID GROUP = 4202554577U;

            namespace SWITCH
            {
                static const AkUniqueID RUN = 712161704U;
                static const AkUniqueID WALK = 2108779966U;
            } // namespace SWITCH
        } // namespace FOOTSTEP_GAIT

        namespace FOOTSTEP_WEIGHT
        {
            static const AkUniqueID GROUP = 246300162U;

            namespace SWITCH
            {
                static const AkUniqueID HEAVY = 2732489590U;
                static const AkUniqueID LIGHT = 1935470627U;
            } // namespace SWITCH
        } // namespace FOOTSTEP_WEIGHT

        namespace SURFACE
        {
            static const AkUniqueID GROUP = 1834394558U;

            namespace SWITCH
            {
                static const AkUniqueID DIRT = 2195636714U;
                static const AkUniqueID GRAVEL = 2185786256U;
                static const AkUniqueID METAL = 2473969246U;
                static const AkUniqueID WOOD = 2058049674U;
            } // namespace SWITCH
        } // namespace SURFACE

    } // namespace SWITCHES

    namespace GAME_PARAMETERS
    {
        static const AkUniqueID ENABLE_EFFECT = 2451442924U;
        static const AkUniqueID FOOTSTEP_SPEED = 3182548923U;
        static const AkUniqueID FOOTSTEP_WEIGHT = 246300162U;
        static const AkUniqueID RPM = 796049864U;
        static const AkUniqueID SS_AIR_FEAR = 1351367891U;
        static const AkUniqueID SS_AIR_FREEFALL = 3002758120U;
        static const AkUniqueID SS_AIR_FURY = 1029930033U;
        static const AkUniqueID SS_AIR_MONTH = 2648548617U;
        static const AkUniqueID SS_AIR_PRESENCE = 3847924954U;
        static const AkUniqueID SS_AIR_RPM = 822163944U;
        static const AkUniqueID SS_AIR_SIZE = 3074696722U;
        static const AkUniqueID SS_AIR_STORM = 3715662592U;
        static const AkUniqueID SS_AIR_TIMEOFDAY = 3203397129U;
        static const AkUniqueID SS_AIR_TURBULENCE = 4160247818U;
    } // namespace GAME_PARAMETERS

    namespace ARGUMENTS
    {
        namespace HOSTILE
        {
            static const AkUniqueID ARGUMENT = 3712907969U;

            namespace ARGUMENT_VALUE
            {
                static const AkUniqueID BUM = 714721627U;
                static const AkUniqueID GANG = 685704824U;
            } // namespace ARGUMENT_VALUE
        } // namespace HOSTILE

        namespace LOCATION
        {
            static const AkUniqueID ARGUMENT = 1176052424U;

            namespace ARGUMENT_VALUE
            {
                static const AkUniqueID ALLEY = 672587556U;
                static const AkUniqueID HANGAR = 2192450996U;
                static const AkUniqueID STREET = 4142189312U;
            } // namespace ARGUMENT_VALUE
        } // namespace LOCATION

        namespace OBJECTIVE
        {
            static const AkUniqueID ARGUMENT = 6899006U;

            namespace ARGUMENT_VALUE
            {
                static const AkUniqueID DEFUSEBOMB = 3261872615U;
                static const AkUniqueID NEUTRALIZEHOSTILE = 141419130U;
                static const AkUniqueID RESCUEHOSTAGE = 3841112373U;
            } // namespace ARGUMENT_VALUE
        } // namespace OBJECTIVE

        namespace OBJECTIVESTATUS
        {
            static const AkUniqueID ARGUMENT = 3299963692U;

            namespace ARGUMENT_VALUE
            {
                static const AkUniqueID COMPLETED = 94054856U;
                static const AkUniqueID FAILED = 1655200910U;
            } // namespace ARGUMENT_VALUE
        } // namespace OBJECTIVESTATUS

        namespace UNIT
        {
            static const AkUniqueID ARGUMENT = 1304109583U;

            namespace ARGUMENT_VALUE
            {
                static const AkUniqueID UNIT_A = 3004848135U;
                static const AkUniqueID UNIT_B = 3004848132U;
            } // namespace ARGUMENT_VALUE
        } // namespace UNIT

        namespace WALKIETALKIE
        {
            static const AkUniqueID ARGUMENT = 4110439188U;

            namespace ARGUMENT_VALUE
            {
                static const AkUniqueID COMM_IN = 1856010785U;
                static const AkUniqueID COMM_OUT = 1553720736U;
            } // namespace ARGUMENT_VALUE
        } // namespace WALKIETALKIE

    } // namespace ARGUMENTS

    namespace BANKS
    {
        static const AkUniqueID INIT = 1355168291U;
        static const AkUniqueID CAR = 983016381U;
        static const AkUniqueID DIRT = 2195636714U;
        static const AkUniqueID DYNAMICDIALOGUE = 1028808198U;
        static const AkUniqueID EXTERNALSOURCES = 480966290U;
        static const AkUniqueID GRAVEL = 2185786256U;
        static const AkUniqueID HUMAN = 3887404748U;
        static const AkUniqueID IMPULSE_RESPONSES = 1064729931U;
        static const AkUniqueID INTERACTIVEMUSIC = 2279279248U;
        static const AkUniqueID MARKERTEST = 2309453583U;
        static const AkUniqueID METAL = 2473969246U;
        static const AkUniqueID MICROPHONE = 2872041301U;
        static const AkUniqueID MOTION = 2012559111U;
        static const AkUniqueID MUSICCALLBACKS = 4146461094U;
        static const AkUniqueID POSITIONING_DEMO = 418215934U;
        static const AkUniqueID TESTRSX = 1868882208U;
        static const AkUniqueID WOOD = 2058049674U;
    } // namespace BANKS

    namespace BUSSES
    {
        static const AkUniqueID CONVOLUTION_REVERB = 1800874279U;
        static const AkUniqueID ENVIRONMENTAL_BUS = 3600197733U;
        static const AkUniqueID MASTER_CONTROL_BUS = 3444197610U;
        static const AkUniqueID MUSIC = 3991942870U;
        static const AkUniqueID VOICES = 3313685232U;
        static const AkUniqueID VOICES_RADIO = 197057172U;
    } // namespace BUSSES

    namespace AUX_BUSSES
    {
        static const AkUniqueID HANGAR_ENV = 2112490296U;
    } // namespace AUX_BUSSES

    namespace EXTERNAL_SOURCES
    {
        static const AkUniqueID EXTERN_2ND_NUMBER = 293435250U;
        static const AkUniqueID EXTERN_3RD_NUMBER = 978954801U;
        static const AkUniqueID EXTERN_1ST_NUMBER = 4004957102U;
    } // namespace EXTERNAL_SOURCES

}// namespace AK

#endif // __WWISE_IDS_H__
