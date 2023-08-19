#ifndef _USS_BY_
#include "z-ultra_sonic_sensor.h"
#endif

class Tank{
    private:
        UltraSonicSensor *ultraSonicSensor;
        float oldWaterStatus = -1, currentWaterStatus = -1;
        
        bool isChanged = true, firstTimeLoad = true;
        // Should be depricated once NodeJs is completed
        bool isChangedForLocal = false;

        int WATER_CHECK_INTERVAL;
        unsigned long WATER_CHECK_INTERVAL_ELAPSED_TIME = 0L;

    public:
        bool isDataChanged(){
            bool changeStatus = isChanged;
            isChanged = false;
            return changeStatus;
        }

        void rollBackChangeNotifier(){
            isChanged = !isChanged;
        }

        bool isDataChanged_Local(){
            bool changeStatus = isChangedForLocal;
            isChangedForLocal = false;
            return changeStatus;
        }

        void rollBackChangeNotifier_Local(){
            isChangedForLocal = !isChangedForLocal;
        }

        float waterLevelInTank( bool byPassTimeCheck = false ){
            if( ( ( millis() - WATER_CHECK_INTERVAL_ELAPSED_TIME ) < WATER_CHECK_INTERVAL ) && ( oldWaterStatus != -1 ) && !byPassTimeCheck ){
                return oldWaterStatus;
            }
            WATER_CHECK_INTERVAL_ELAPSED_TIME = millis();

            currentWaterStatus = ultraSonicSensor->getCurrentValue()->inInches();
            Serial.print("In Current Tank data : ");
            Serial.println(currentWaterStatus);

            if( currentWaterStatus != oldWaterStatus ){
                isChanged = true;
                isChangedForLocal = true;
                oldWaterStatus = currentWaterStatus;
            }
            
            return currentWaterStatus;
        }

        Tank( int triggerPin, int echoPin, int checkInterval ){
            ultraSonicSensor = new UltraSonicSensor( triggerPin, echoPin );
            WATER_CHECK_INTERVAL = checkInterval;
        }
};
