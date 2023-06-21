void water_pump(){
    if( tankObj.waterLevelInTank() != 4 ){
        if ( sumpObj.waterLevelInSump() <= 0) {
            motor_control( MOTOR_OFF );
            Serial.println("\nTank level low turning off the pump because low water in summp");
        } else if( sumpObj.waterLevelInSump() == 3 ){
            motor_control( MOTOR_ON );
            Serial.println("\nTank level low turning on the pump");
        } else {
            Serial.println("\nWater Level low in sump");
        }
    } else {
        motor_control( MOTOR_OFF );
        Serial.println("\nTank level high turning off the pump");
    }

}


void motor_control( uint8_t value ){
   Serial.println("\n\n\t Inside Motor control : ");
   if( ( value == MOTOR_ON ) && ( digitalRead( RELAY_1 ) != MOTOR_ON ) ){
       Serial.println("\n\t\tMOTOR_ON ");
       digitalWrite( RELAY_1, MOTOR_ON );
    } else if( ( value == MOTOR_OFF ) && ( digitalRead( RELAY_1 ) != MOTOR_OFF ) ) {
        Serial.println("\n\t\tMOTOR_OFF ");
        digitalWrite( RELAY_1, MOTOR_OFF );
    }
    //    digitalWrite( RELAY_1, value );
}