void motor_control( uint8_t value ){
    Serial.println("\n\n\t Inside Motor control : ");
    if( ( value == MOTOR_ON ) && ( digitalRead( RELAY_1 ) != MOTOR_ON ) ){
        Serial.println("\n\t\tMOTOR_ON ");
        digitalWrite( RELAY_1, MOTOR_ON );
        motor_status_changed = true;
    } else if( ( value == MOTOR_OFF ) && ( digitalRead( RELAY_1 ) != MOTOR_OFF ) ) {
        Serial.println("\n\t\tMOTOR_OFF ");
        digitalWrite( RELAY_1, MOTOR_OFF );
        motor_status_changed = true;
    }
}