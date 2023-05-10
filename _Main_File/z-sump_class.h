#include "z-pin_alter_class.h"

class Sump{
    private:
        short oldWaterStatus = -1, currentWaterStatus = -1;
        int SUMP_WL_LOW, SUMP_WL_MID;
        bool CODE_DEBUG, firstTimeLoad = false;
        int DEBUG_DELAY_TIME;
        bool isChanged = true;
        int WATER_CHECK_INTERVAL;
        unsigned long WATER_CHECK_INTERVAL_ELAPSED_TIME = 0L;


        void updateSumpDetails( bool updateFromStart = false ){

            int tempWaterLevelInSump = currentWaterStatus;
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
                            currentWaterStatus = 2;
                            pinAlter().highDigitalPin( SUMP_WL_LOW );
                            caseBreakCheck = false;
                        } else {
                            currentWaterStatus = -1;
                        }
                    } else {
                        currentWaterStatus = 0;
                    }
                    
                    if( caseBreakCheck ){
                            break;
                    } else {
                        caseBreakCheck = true;
                    }

                case 2 :
                case 3 : 
                    pinAlter().lowDigitalPin( SUMP_WL_MID, true, true );
                    if( digitalRead( SUMP_WL_MID ) == 1 ){

                        pinAlter().lowDigitalPin( SUMP_WL_MID, true, true );
                        if( digitalRead( SUMP_WL_MID ) == 1 ){
                            currentWaterStatus = 3;
                            pinAlter().highDigitalPin( SUMP_WL_MID );
                        } else {
                            currentWaterStatus = -1;
                        }

                    } else {
                        currentWaterStatus = 1;
                    }

                break;

                default:
                    currentWaterStatus = -1;
                    pinAlter().highDigitalPin( new int[ SUMP_WL_LOW, SUMP_WL_MID ] );
                break;
            }

            if( CODE_DEBUG ){
                 Serial.println("\n\t\tDebug from sump class : ");
                 Serial.println("\n\t\t\t Water low sensor value : " + pinAlter().checkValueInPin( SUMP_WL_LOW ) );
                 Serial.println("\n\t\t\t Water mid sensor value : " + pinAlter().checkValueInPin( SUMP_WL_MID ) );
                 Serial.println("\n\n\t\t\t Value in currentWaterStatus : " + String( currentWaterStatus ) );
                 delay( DEBUG_DELAY_TIME );
            }


        } 


    public:
        bool isDataChanged(){
            return isChanged;
        }

        void setIsChangedToFalse(){
            isChanged = false;
        }

        int waterLevelInSump( bool updateFromStart = false ){

            if( ( ( millis() - WATER_CHECK_INTERVAL_ELAPSED_TIME ) >= WATER_CHECK_INTERVAL ) || firstTimeLoad ){

                if( firstTimeLoad ){
                    WATER_CHECK_INTERVAL_ELAPSED_TIME += WATER_CHECK_INTERVAL;
                }
            
                do{
                    updateSumpDetails( updateFromStart );
                }while( currentWaterStatus == -1 );

                if( currentWaterStatus != oldWaterStatus ){
                    isChanged = true;
                    oldWaterStatus = currentWaterStatus;
                }

                firstTimeLoad = false;

            }

            return currentWaterStatus;

        }

        Sump( int low, int mid, int checkInterval, bool debug, int delay_time  ){
            SUMP_WL_LOW = low;
            SUMP_WL_MID = mid;
            WATER_CHECK_INTERVAL = checkInterval;
            CODE_DEBUG = debug;
            DEBUG_DELAY_TIME = delay_time;
            firstTimeLoad = true;
        }
};
