class sumpDetails{
    private:
        short waterLevelInSump = -1;

        bool isWaterLevelAboveLow;
        bool isWaterLevelAboveMid;

        bool lowCheckCompleted;
        bool midCheckCompleted;

    public:
        sumpDetails(){
            lowCheckCompleted = false;
            midCheckCompleted = false;
        }

        void updateSumpDetails( bool updateFromStart = false ){

            int tempWaterLevelInSump = waterLevelInSump;
            if( tempWaterLevelInSump == -1 || tempWaterLevelInSump > 1 ){
                tempWaterLevelInSump = 0;
            }

            switch( tempWaterLevelInSump ){
                case 0 :
                    lowDigitalPin( WL_S_LOW, true, true );
                    if( digitalRead( WL_S_LOW ) == 1 ){

                        lowDigitalPin( WL_S_LOW, true, true );
                        if( digitalRead( WL_S_LOW ) == 1 ){
                            Serial.println("\nWater Level above low in sump");
                            waterLevelInSump = 1;
                        } else {
                            waterLevelInSump = -1;
                        }

                    } else {
                        waterLevelInSump = -1;
                    }

                    break;

                case 1:
                    lowDigitalPin( WL_S_MID, true, true );
                    if( digitalRead( WL_S_MID ) == 1 ){

                        lowDigitalPin( WL_S_MID, true, true );
                        if( digitalRead( WL_S_MID ) == 1 ){
                            Serial.println("\nWater Level above mid in sump");
                            waterLevelInSump = 2;
                        } else {
                            waterLevelInSump = -1;
                        }

                    } else {
                        waterLevelInSump = -1;
                    }

                    break;

                default:
                    highDigitalPin( WL_S_LOW );
                    highDigitalPin( WL_S_MID );
                    break;


            }
            // if( !( midCheckCompleted ) || !( isWaterLevelAboveMid ) || updateFromStart ){
                
            //     lowDigitalPin( WL_S_MID, true, true );
            //     if( digitalRead( WL_S_MID ) == 1 ){

            //         lowDigitalPin( WL_S_MID, true, true );
            //         if( digitalRead( WL_S_MID ) == 1 ){
            //             Serial.println("\nWater Level above mid in sump");
            //             midCheckCompleted = true;
            //             isWaterLevelAboveMid = true;
            //             isWaterLevelAboveLow = true;
            //         } else {
            //             midCheckCompleted = false;
            //             isWaterLevelAboveMid = false;
            //             isWaterLevelAboveLow = false;
            //         }
            //     } else {
            //         midCheckCompleted = false;
            //         isWaterLevelAboveMid = false;
            //         isWaterLevelAboveLow = false;
            //     }
            // }

            // if( !( lowCheckCompleted ) || !( isWaterLevelAboveLow ) || updateFromStart ){

            //     lowDigitalPin( WL_S_LOW, true, true );
            //     if( digitalRead( WL_S_LOW ) == 1 ){

            //         lowDigitalPin( WL_S_LOW, true, true );
            //         if( digitalRead( WL_S_LOW ) == 1 ){
            //             Serial.println("\nWater Level above low in sump");
            //             lowCheckCompleted = true;
            //         } else {
            //             lowCheckCompleted = false;
            //         }

            //     } else {
            //         lowCheckCompleted = false;
            //     }
            // } 

            // highDigitalPin( WL_S_LOW );
            // highDigitalPin( WL_S_MID );
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
