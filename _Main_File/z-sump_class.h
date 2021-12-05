#include "z-pin_alter_class.h"

class Sump{
    private:
        short waterStatus = -1;
        int SUMP_WL_LOW, SUMP_WL_MID;
        bool DEBUG_CODE = true;
        int DEBUG_DELAY_TIME = 5000;


        void updateSumpDetails( bool updateFromStart = false ){

            int tempWaterLevelInSump = waterStatus;
            bool caseBreakCheck = true;

            if( tempWaterLevelInSump == -1 || updateFromStart ){
                tempWaterLevelInSump = 0;
            }

            switch( tempWaterLevelInSump ){

                case 0 :
                    pinAlter().lowDigitalPin( SUMP_WL_LOW, true, true );
                    if( digitalRead( SUMP_WL_LOW ) == 1 ){

                        pinAlter().lowDigitalPin( SUMP_WL_LOW, true, true );
                        if( digitalRead( SUMP_WL_LOW ) == 1 ){
                            waterStatus = 1;
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

                case 1:
                case 2:
                    pinAlter().lowDigitalPin( SUMP_WL_MID, true, true );
                    if( digitalRead( SUMP_WL_MID ) == 1 ){

                        pinAlter().lowDigitalPin( SUMP_WL_MID, true, true );
                        if( digitalRead( SUMP_WL_MID ) == 1 ){
                            waterStatus = 2;
                            pinAlter().highDigitalPin( SUMP_WL_MID );
                        } else {
                            waterStatus = -1;
                        }

                    } else {
                        waterStatus = 0;
                    }

                break;

                default:
                    waterStatus = -1;
                    pinAlter().highDigitalPin( SUMP_WL_LOW );
                    pinAlter().highDigitalPin( SUMP_WL_MID );
                    break;
            }

            if( DEBUG_CODE ){
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

        Sump( int low, int mid ){
            SUMP_WL_LOW = low;
            SUMP_WL_MID = mid;
            Serial.println("------Sump class instantiated------");
        }
};
