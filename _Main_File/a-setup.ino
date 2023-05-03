void setup(){
    Serial.begin(9600);

    // ----- WIFI Setup -------
    setup_wifi( 5, 1 );
    
    // ----- Motor Setup ------
    pinMode(RELAY_1, OUTPUT);
    motor_control( MOTOR_OFF );
}
