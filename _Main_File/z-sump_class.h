#include "z-pin_alter_class.h"
pinAlter pin_alter = pinAlter();

class Sump{
    private:
        short waterStatus = -1;
        int SUMP_WL_LOW, SUMP_WL_MID;

        void updateSumpDetails( bool updateFromStart = false ){

            int tempWaterLevelInSump = waterStatus;
            bool caseBreakCheck = true;

            if( tempWaterLevelInSump == -1 || tempWaterLevelInSump > 1 || updateFromStart ){
                tempWaterLevelInSump = 0;
            }

            switch( tempWaterLevelInSump ){

            case 0 :
                pin_alter.lowDigitalPin( SUMP_WL_LOW, true, true );
                if( digitalRead( SUMP_WL_LOW ) == 1 ){

                    pin_alter.lowDigitalPin( SUMP_WL_LOW, true, true );
                    if( digitalRead( SUMP_WL_LOW ) == 1 ){
                        Serial.println("\nWater Level above low in sump");
                        waterStatus = 1;
                        pin_alter.highDigitalPin( SUMP_WL_LOW );
                        caseBreakCheck = false;
                    } else {
                        waterStatus = -1;
                    }
                } else {
                    waterStatus = -1;
                }
                
                if( caseBreakCheck ){
                        break;
                }

            case 1:
                pin_alter.lowDigitalPin( SUMP_WL_MID, true, true );
                if( digitalRead( SUMP_WL_MID ) == 1 ){

                    pin_alter.lowDigitalPin( SUMP_WL_MID, true, true );
                    if( digitalRead( SUMP_WL_MID ) == 1 ){
                        Serial.println("\nWater Level above mid in sump");
                        waterStatus = 2;
                        pin_alter.highDigitalPin( SUMP_WL_MID );
                    } else {
                        waterStatus = -1;
                    }

                } else {
                    waterStatus = -1;
                }

            break;

            default:
                waterStatus = -1;
                pin_alter.highDigitalPin( SUMP_WL_LOW );
                pin_alter.highDigitalPin( SUMP_WL_MID );
                break;
            }
        } 

    public:
        int waterLevelInSump( bool updateFromStart = false ){
            updateSumpDetails( updateFromStart );
            return waterStatus;
        }

        Sump( int low, int mid ){
            SUMP_WL_LOW = low;
            SUMP_WL_MID = mid;
            Serial.println("------Sump class instantiated------");
        }
};
