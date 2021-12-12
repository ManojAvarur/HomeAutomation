#include "z-pin_alter_class.h"

class Sump{
    private:
        short waterStatus = -1;
        int SUMP_WL_LOW, SUMP_WL_MID;
        bool CODE_DEBUG;
        int DEBUG_DELAY_TIME;


        void updateSumpDetails( bool updateFromStart = false ){

            int tempWaterLevelInSump = waterStatus;
            bool caseBreakCheck = true;

            if( tempWaterLevelInSump <= 0 || updateFromStart ){
                tempWaterLevelInSump = 1;
            }

            switch( tempWaterLevelInSump ){

                case 1 :
                    pinAlter().lowDigitalPin( SUMP_WL_LOW, true, true );
                    if( digitalRead( SUMP_WL_LOW ) == 1 ){

                        pinAlter().lowDigitalPin( SUMP_WL_LOW, true, true );
                        if( digitalRead( SUMP_WL_LOW ) == 1 ){
                            waterStatus = 2;
                            pinAlter().highDigitalPin( SUMP_WL_LOW );
                            caseBreakCheck = false;
                        } else {
                            waterStatus = -1;
                        }
                    } else {
                        waterStatus = 0;
                    }
                    
                    if( caseBreakCheck ){
                            break;
                    }

                case 2 :
                case 3 : 
                    pinAlter().lowDigitalPin( SUMP_WL_MID, true, true );
                    if( digitalRead( SUMP_WL_MID ) == 1 ){

                        pinAlter().lowDigitalPin( SUMP_WL_MID, true, true );
                        if( digitalRead( SUMP_WL_MID ) == 1 ){
                            waterStatus = 3;
                            pinAlter().highDigitalPin( SUMP_WL_MID );
                        } else {
                            waterStatus = -1;
                        }

                    } else {
                        waterStatus = 1;
                    }

                break;

                default:
                    waterStatus = -1;
                    pinAlter().highDigitalPin( SUMP_WL_LOW );
                    pinAlter().highDigitalPin( SUMP_WL_MID );
                break;
            }

            if( CODE_DEBUG ){
                 Serial.println("\n\t\tDebug from sump class : ");
                 Serial.println("\n\t\t\t Water low sensor value : " + pinAlter().checkValueInPin( SUMP_WL_LOW ) );
                 Serial.println("\n\t\t\t Water mid sensor value : " + pinAlter().checkValueInPin( SUMP_WL_MID ) );
                 Serial.println("\n\n\t\t\t Value in waterStatus : " + String( waterStatus ) );
                 delay( DEBUG_DELAY_TIME );
            }


        } 

    public:
        int waterLevelInSump( bool updateFromStart = false ){
            do{
                updateSumpDetails( updateFromStart );
            }while( waterStatus == -1 );
            return waterStatus;
        }

        Sump( int low, int mid, bool debug, int delay_time  ){
            SUMP_WL_LOW = low;
            SUMP_WL_MID = mid;
            CODE_DEBUG = debug;
            DEBUG_DELAY_TIME = delay_time;
        }
};
