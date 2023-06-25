#ifndef _USS_BY_
#include "z-ultra_sonic_sensor.h"
#endif

class Sump{
    private:
        UltraSonicSensor *ultraSonicSensor;
        short oldWaterStatus = -1, currentWaterStatus = -1;

        bool isChanged = true;
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

        int waterLevelInSump(){
            if( ( ( millis() - WATER_CHECK_INTERVAL_ELAPSED_TIME ) < WATER_CHECK_INTERVAL ) && ( oldWaterStatus != -1 ) ){
                return oldWaterStatus;
            }
            WATER_CHECK_INTERVAL_ELAPSED_TIME += WATER_CHECK_INTERVAL;

            currentWaterStatus = ultraSonicSensor->getCurrentValue()->inInches();

            if( currentWaterStatus != oldWaterStatus ){
                isChanged = true;
                isChangedForLocal = true;
                oldWaterStatus = currentWaterStatus;
            }

            return currentWaterStatus;
        }

        Sump( int triggerPin, int echoPin, int checkInterval  ){
            ultraSonicSensor = new UltraSonicSensor( triggerPin, echoPin );
            WATER_CHECK_INTERVAL = checkInterval;
        }
};
