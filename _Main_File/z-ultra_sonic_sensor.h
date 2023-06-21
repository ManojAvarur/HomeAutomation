class UltraSonicSensor{
    private:
        const int SOUND_VELOCITY = 0.034;
        const int CM_TO_INCH = 0.393701;

        int TRIGGER_PIN;
        int ECHO_PIN;

        long DURATION;

    public:
        UltraSonicSensor* getCurrentValue(){
            // Clears the trigPin
            digitalWrite( this->TRIGGER_PIN, LOW );
            delayMicroseconds(2);

            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite( this->TRIGGER_PIN, HIGH);
            delayMicroseconds(10);
            digitalWrite( this->TRIGGER_PIN, LOW);

            // Reads the echoPin, returns the sound wave travel time in microseconds
            this->DURATION = pulseIn( this->ECHO_PIN, HIGH);

            // Returns current UltraSonicSensor instance
            return this;
        }

        float inCentimeter(){
            return this->DURATION * SOUND_VELOCITY/2;
        }

        float inInches(){
            return ( this->inCentimeter() * CM_TO_INCH );
        }
    
    UltraSonicSensor( int triggerPin, int echoPin ){
        this->TRIGGER_PIN = triggerPin;
        this->ECHO_PIN = echoPin;

        pinMode( this->TRIGGER_PIN, OUTPUT );
        pinMode( this->ECHO_PIN, INPUT );
    }
};