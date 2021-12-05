//#include "z-pin_alter_class.h"

class Tank{
    private:
        short waterStatus = -1;
        bool statusConformation = false;
        int TANK_WL_LOW, TANK_WL_MID, TANK_WL_HIGH;

        void updateTankDetails( bool updateFromStart = false ){

            int tempWaterLevelInTank = waterStatus;
            bool caseBreakCheck = true;

            if( tempWaterLevelInTank == -1 || updateFromStart ){
                tempWaterLevelInTank = 0;
            }

            switch( tempWaterLevelInTank ){

            case 0 :
                pinAlter().lowDigitalPin( TANK_WL_LOW, true, true );
                if( digitalRead( TANK_WL_LOW ) == 1 ){

                    pinAlter().lowDigitalPin( TANK_WL_LOW, true, true );
                    if( digitalRead( TANK_WL_LOW ) == 1 ){
//                        Serial.println("\nWater Level above low in Tank");
                        waterStatus = 1;
                        pinAlter().highDigitalPin( TANK_WL_LOW );
                        caseBreakCheck = false;
                        statusConformation = true;
                    } else {
                        waterStatus = -1;
                        statusConformation = false;
                    }
                } else {
                    waterStatus = 0;
                    statusConformation = false;
                }
                
                if( caseBreakCheck ){
                    caseBreakCheck = true;
                    break;
                }

            case 1:
                pinAlter().lowDigitalPin( TANK_WL_MID, true, true );
                if( digitalRead( TANK_WL_MID ) == 1 ){

                    pinAlter().lowDigitalPin( TANK_WL_MID, true, true );
                    if( digitalRead( TANK_WL_MID ) == 1 ){
                        waterStatus = 2;
                        pinAlter().highDigitalPin( TANK_WL_MID );
                        statusConformation = true;
                    } else {
                        statusConformation = false;
                    }

                } else {
                    waterStatus = 0;
                    statusConformation = false;
                }

                if( caseBreakCheck ){
                    break;
                }

            case 2:
            case 3:
                pinAlter().lowDigitalPin( TANK_WL_HIGH, true, true );
                if( digitalRead( TANK_WL_HIGH ) == 1 ){

                    pinAlter().lowDigitalPin( TANK_WL_HIGH, true, true );
                    if( digitalRead( TANK_WL_HIGH ) == 1 ){
                        waterStatus = 3;
                        pinAlter().highDigitalPin( TANK_WL_HIGH );
                        statusConformation = true;
                    } else {
                        statusConformation = false;
                    }

                } else {
                    waterStatus = 1;
                    statusConformation = false;
                }


                break;
                

            default:
                waterStatus = -1;
                pinAlter().highDigitalPin( TANK_WL_LOW );
                pinAlter().highDigitalPin( TANK_WL_MID );
                pinAlter().highDigitalPin( TANK_WL_HIGH );
                break;
            
            }
        } 

    public:
        int waterLevelInTank( bool updateFromStart = false ){
            do{
                updateTankDetails( updateFromStart );
            } while( waterStatus == -1 || wate );
            return waterStatus;
        }

        Tank( int low, int mid, int high ){
            TANK_WL_LOW = low;
            TANK_WL_MID = mid;
            TANK_WL_HIGH = high;
            Serial.println("------Tank class instantiated------");
        }
};
