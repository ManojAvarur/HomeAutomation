void motor_control( uint8_t value ){
    if( ( value == MOTOR_ON ) && ( digitalRead( RELAY_1 ) != MOTOR_ON ) ){
        digitalWrite( RELAY_1, MOTOR_ON );
        MOTOR_STATUS_CHANGED = true;
    } else if( ( value == MOTOR_OFF ) && ( digitalRead( RELAY_1 ) != MOTOR_OFF ) ) {
        digitalWrite( RELAY_1, MOTOR_OFF );
        MOTOR_STATUS_CHANGED = true;
    }
}