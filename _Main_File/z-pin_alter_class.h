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
};