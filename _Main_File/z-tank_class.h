//#include "z-pin_alter_class.h"

class Tank{
    private:
        short oldWaterStatus = -1, currentWaterStatus = -1;
        int TANK_WL_LOW, TANK_WL_MID, TANK_WL_HIGH;
        bool CODE_DEBUG;
        int DEBUG_DELAY_TIME;
        bool isChanged = true;

        void updateTankDetails( bool updateFromStart = false ){

            short tempWaterLevelInTank = currentWaterStatus;
            bool caseBreakCheck = true;

            if( tempWaterLevelInTank <= 0 || updateFromStart ){
                tempWaterLevelInTank = 1;
            }

            switch( tempWaterLevelInTank ){

                case 1 :
                    pinAlter().lowDigitalPin( TANK_WL_LOW, true, true );
                    if( digitalRead( TANK_WL_LOW ) == 1 ){

                        pinAlter().lowDigitalPin( TANK_WL_LOW, true, true );
                        if( digitalRead( TANK_WL_LOW ) == 1 ){
                            currentWaterStatus = 2;
                            pinAlter().highDigitalPin( TANK_WL_LOW );
                            caseBreakCheck = false;

                            if( CODE_DEBUG ){
                                Serial.println("\n\n\tInside |-| Tank LOW and tempWaterLevel in tank is : " + String( tempWaterLevelInTank ) );
                                delay( DEBUG_DELAY_TIME );
                            }

                        } else {
                            currentWaterStatus = -1;
                        }
                    } else {
                        currentWaterStatus = 0;
                    }
                    
                    if( caseBreakCheck ){
                        break;
                    }

                case 2 :
                    pinAlter().lowDigitalPin( TANK_WL_MID, true, true );
                    if( digitalRead( TANK_WL_MID ) == 1 ){

                        pinAlter().lowDigitalPin( TANK_WL_MID, true, true );
                        if( digitalRead( TANK_WL_MID ) == 1 ){
                            currentWaterStatus = 3;
                            pinAlter().highDigitalPin( TANK_WL_MID );
                            caseBreakCheck = false;
                            if( CODE_DEBUG ){
                                Serial.println("\n\n\tInside |-| Tank MID and tempWaterLevel in tank is : " + String( tempWaterLevelInTank ) );
                                delay( DEBUG_DELAY_TIME );
                            }
                        } else {
                            currentWaterStatus = -1;
                        }

                    } else {
                        currentWaterStatus = 1;
                    }

                    if( caseBreakCheck ){
                        break;
                    }

                case 3:
                case 4:
                    pinAlter().lowDigitalPin( TANK_WL_HIGH, true, true );
                    if( digitalRead( TANK_WL_HIGH ) == 1 ){

                        pinAlter().lowDigitalPin( TANK_WL_HIGH, true, true );
                        if( digitalRead( TANK_WL_HIGH ) == 1 ){
                            currentWaterStatus = 4;
                            pinAlter().highDigitalPin( TANK_WL_HIGH );
                            if( CODE_DEBUG ){
                                Serial.println("\n\n\tInside |-| Tank HIGH and tempWaterLevel in tank is : " + String( tempWaterLevelInTank ) );
                                delay( DEBUG_DELAY_TIME );
                            }
                        } else {
                            currentWaterStatus = -1;
                        }

                    } else {
                        currentWaterStatus = 2;
                    }


                    break;
                    

                default:
                    currentWaterStatus = -1;
                    pinAlter().highDigitalPin( TANK_WL_LOW );
                    pinAlter().highDigitalPin( TANK_WL_MID );
                    pinAlter().highDigitalPin( TANK_WL_HIGH );
                    break;
            
            }

            if( CODE_DEBUG ){
                Serial.println("\n\t\tDebug from tank class : ");
                Serial.println("\n\t\t\t Water low sensor value : " + pinAlter().checkValueInPin( TANK_WL_LOW ) );
                Serial.println("\n\t\t\t Water mid sensor value : " + pinAlter().checkValueInPin( TANK_WL_MID ) );
                Serial.println("\n\t\t\t Water mid sensor value : " + pinAlter().checkValueInPin( TANK_WL_HIGH ) );
                Serial.println("\n\n\t\t\t Value in currentWaterStatus : " + String( currentWaterStatus ) );
                delay( DEBUG_DELAY_TIME );
            }
        } 

    public:

        int waterLevelInTank( bool updateFromStart = false ){
            
            do{
                updateTankDetails( updateFromStart );
            }while( currentWaterStatus == -1 );

            if( currentWaterStatus != oldWaterStatus ){
                isChanged = true;

                if( CODE_DEBUG ){
                    Serial.println("\n\t\tDebug from tank class oldWaterStatus : " + String( oldWaterStatus ));
                    Serial.println("\n\t\tDebug from tank class currentWaterStatus : " + String( currentWaterStatus ));
                    delay( DEBUG_DELAY_TIME );
                }

                oldWaterStatus = currentWaterStatus;
            }

            return currentWaterStatus;
        }

        bool isDataChanged(){
            return isChanged;
        }

        void setIsChangedToFalse(){
            isChanged = false;
        }

        Tank( int low, int mid, int high, bool debug, int delay_time ){
            TANK_WL_LOW = low;
            TANK_WL_MID = mid;
            TANK_WL_HIGH = high;
            CODE_DEBUG = debug;
            DEBUG_DELAY_TIME = delay_time;
        }
};
