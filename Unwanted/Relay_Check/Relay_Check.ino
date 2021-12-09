#define RELAY_1 D7 // For Water Pump
#define MOTOR_ON LOW // Turing on the pump / relay
#define MOTOR_OFF HIGH // Turing off the pump / relay

void motor_control( uint8_t value ){
    digitalWrite( RELAY_1, value );
}

void setup(){
    // delay( INITIAL_PUMP_LOAD_TIME );
    pinMode(RELAY_1, OUTPUT);
    motor_control( MOTOR_OFF );
}

void loop(){
    motor_control( MOTOR_ON );
    delay(5000);
    motor_control( MOTOR_OFF );
    delay(5000);
}
