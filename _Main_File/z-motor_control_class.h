class MotorControl{
            
    #define MOTOR_ON LOW // Turing on the pump / relay
    #define MOTOR_OFF HIGH // Turing off the pump / relay

    private:
        bool isChanged = false;
        uint8_t previousState = MOTOR_OFF;
        // Should be depricated once NodeJs is completed
        bool isChangedForLocal = false;
        int relayToControl;
        // uint8_t MOTOR_ON, MOTOR_OFF;

        void motor_control( uint8_t value ){
            digitalWrite( RELAY_1, value );
        }

        void setDataChangeNotifier(){
            int currentState = digitalRead( RELAY_1 );
            if( previousState != currentState ){
                isChanged = true;
                isChangedForLocal = true;
                previousState = currentState;
            }
        }


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

        void turnOn(){
            motor_control( MOTOR_ON );
            setDataChangeNotifier();
        }

        void turnOff(){
            motor_control( MOTOR_OFF );
            setDataChangeNotifier();
        }

        MotorControl( int relay ){
            relayToControl = relay;
            pinMode(relayToControl, OUTPUT);
        }
};
