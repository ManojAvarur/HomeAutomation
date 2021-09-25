#define RELAY_1 D6 // For Water Pump
#define MOTOR_ON HIGH // Turing on the pump / relay
#define MOTOR_OFF LOW // Turing off the pump / relay

void setup(){
    // delay( INITIAL_PUMP_LOAD_TIME );
    pinMode(RELAY_1, OUTPUT);
    digitalWrite(RELAY_1, MOTOR_OFF);
}

void loop(){
    digitalWrite(RELAY_1, MOTOR_ON);
    delay(5000);
    digitalWrite(RELAY_1, MOTOR_OFF);
    delay(5000);
}
