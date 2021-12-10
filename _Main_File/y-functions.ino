void water_pump(){

    if( tankObj.waterLevelInTank() != 3 ){
        if( sumpObj.waterLevelInSump() > 1 ){
            motor_control( MOTOR_ON );
            Serial.println("\nTank level low turning on the pump");
        } else {
            motor_control( MOTOR_OFF );
            Serial.println("\nTank level low turning off the pump because low water in summp");
        }
    } else {
        motor_control( MOTOR_OFF );
        Serial.println("\nTank level high turning off the pump");
    }

}


void motor_control( uint8_t value ){
    if( ( value == MOTOR_ON ) && ( isMotorOn == false ) ){
        digitalWrite( RELAY_1, MOTOR_ON );
     } else if( ( value == MOTOR_OFF ) && ( isMotorOn == true ) ) {
         digitalWrite( RELAY_1, MOTOR_OFF );
     }
}


void setup_wifi(){
    short while_counter = 0;
    short overall_wait_time = 5; //secs
    WiFi.begin(SSID, PASSWORD);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED && ( while_counter != overall_wait_time )) {
        delay(1000);
        Serial.print(".");
        while_counter++;
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}
