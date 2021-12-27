void setup(){
    Serial.begin(9600);
    
    // ----- Motor Setup ------
    pinMode(RELAY_1, OUTPUT);
    motor_control( MOTOR_OFF );
}
