void motor_status( bool status, String from ){
    if( DEBUG_CODE ){
        Serial.print("\nDEBUG CODE ENABLED : \n\tmotor_status called from ' " + from + " '\n\n");
        Serial.print("\tSTATUS = " +  status  );
        delay( DEBUG_DELAY_TIME );
    }

    if( status ){
        digitalWrite( RELAY_1, MOTOR_ON );
    } else {
        digitalWrite( RELAY_1, MOTOR_OFF );
    }
}
