//#include "z-pin_alter_class.h"

class Tank{
    private:
        short waterStatus = -1;
        int TANK_WL_LOW, TANK_WL_MID, TANK_WL_HIGH;
        bool DEBUG_CODE = true;
        int DEBUG_DELAY_TIME = 5000;

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
                            waterStatus = 1;
                            pinAlter().highDigitalPin( TANK_WL_LOW );
                            caseBreakCheck = false;
                        } else {
                            waterStatus = -1;
                        }
                    } else {
                        waterStatus = 0;
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
                        } else {
                            waterStatus = -1;
                        }

                    } else {
                        waterStatus = 0;
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
                        } else {
                            waterStatus = -1;
                        }

                    } else {
                        waterStatus = 1;
                    }


                    break;
                    

                default:
                    waterStatus = -1;
                    pinAlter().highDigitalPin( TANK_WL_LOW );
                    pinAlter().highDigitalPin( TANK_WL_MID );
                    pinAlter().highDigitalPin( TANK_WL_HIGH );
                    break;
            
            }

            if( DEBUG_CODE ){
                 Serial.println("\n\t\tDebug from tank class : ");
                 Serial.println("\n\t\t\t Water low sensor value : " + pinAlter().checkValueInPin( TANK_WL_LOW ) );
                 Serial.println("\n\t\t\t Water mid sensor value : " + pinAlter().checkValueInPin( TANK_WL_MID ) );
                 Serial.println("\n\t\t\t Water mid sensor value : " + pinAlter().checkValueInPin( TANK_WL_HIGH ) );
                 Serial.println("\n\n\t\t\t Value in waterStatus : " + String( waterStatus ) );
                 delay( DEBUG_DELAY_TIME );
            }
        } 

    public:
        int waterLevelInTank( bool updateFromStart = false ){
            do{
                updateTankDetails( updateFromStart );
            }while( waterStatus == -1 );
            return waterStatus;
        }

        Tank( int low, int mid, int high ){
            TANK_WL_LOW = low;
            TANK_WL_MID = mid;
            TANK_WL_HIGH = high;
            Serial.println("------Tank class instantiated------");
        }
};
