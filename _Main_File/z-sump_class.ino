class sumpDetails{
    private:
        bool isWaterLevelAboveLow;
        bool isWaterLevelAboveMid;

    public:
        sumpDetails( int lowLevel, int midLevel ){
            if( lowLevel != NULL ){
                this->isWaterLevelAboveLow = ( lowLevel )? true : false;
            }

            if( midLevel != NULL ){
                this->isWaterLevelAboveMid = ( midLevel )? true : false;
            }
        }

        void updateSumpDetails( bool updateFromLow = false ){

            if( digitalRead( WL_S_MID ) == 1 ){
                pinMode( WL_S_MID, OUTPUT);
                digitalWrite( WL_S_MID, LOW);
                pinMode( WL_S_MID, INPUT);
                if( digitalRead( WL_S_MID ) == 1 ){
                    return true;
                }
            }

            if( DEBUG_CODE ){
                Serial.print("\nDEBUG CODE ENABLED : \n\tlow_water_level_in_tank called from ' " + from + " '\n\n");
                Serial.print("\tLOW = " + String( digitalRead( WL_S_MID ) ) );
                delay( DEBUG_DELAY_TIME );
            }
        }

        int waterLevelInSump(){
            if( this->isWaterLevelAboveMid ){
                return 2;
            } else if ( this->isWaterLevelAboveLow ){
                return 1;
            } else {
                return 0;
            }
        }
};