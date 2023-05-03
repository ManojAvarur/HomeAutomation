



void debug_log( String value ){
    Serial.println( value );
    DEBUG_LOG = value;
    if( DEBUG_CODE ){
        delay( DEBUG_DELAY_TIME );
    }
}