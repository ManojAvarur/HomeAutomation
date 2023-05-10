class pinAlter{

    public: 
        static void lowDigitalPin( int pin, bool changeToInput = false, bool delayRequired = false ){
            pinMode( pin, OUTPUT );
            digitalWrite( pin, LOW );

            if( changeToInput ){
                pinMode( pin, INPUT );
            }

            if( delayRequired ){
                delay(200);
            }
        }

        static void highDigitalPin( int pin, bool changeToInput = false, bool delayRequired = false ){
            pinMode( pin, OUTPUT );
            digitalWrite( pin, HIGH );

            if( changeToInput ){ 
                pinMode( pin, INPUT );
            }

            if( delayRequired ){
                delay(200);
            }
        }

        static void lowDigitalPins( int pin[], bool changeToInput = false, bool delayRequired = false ){
            for( int i=0; i < sizeof( pin ); i++ ){
                pinMode( pin[i], OUTPUT );
                digitalWrite( pin[i], LOW );

                if( changeToInput ){
                    pinMode( pin[i], INPUT );
                }
            }

            if( delayRequired ){
                delay(200);
            }
        }

        static void highDigitalPin( int pin[], bool changeToInput = false, bool delayRequired = false ){
            for( int i=0; i < sizeof( pin ) ; i++ ){
                pinMode( pin[i], OUTPUT );
                digitalWrite( pin[i], HIGH );

                if( changeToInput ){
                    pinMode( pin[i], INPUT );
                }
            }

            if( delayRequired ){
                delay(200);
            }
        }

        static String checkValueInPin( int pin ){
             lowDigitalPin( pin, true, true );
             return String( digitalRead( pin ) );
        }
};
