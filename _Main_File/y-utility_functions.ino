void debug_log( String value ){
    Serial.println( value );
    DEBUG_LOG = value;
    if( DEBUG_CODE ){
        delay( DEBUG_DELAY_TIME );
    }
}

void control_wifi_ap( bool status ){
    if( status ){
        WiFi.disconnect();
        WiFi.softAPConfig( local_ip, gateway, subnet );
        WiFi.softAP( AP_SSID, AP_PASSWORD );
    } else {
        if( ws.getClients().length() <= 0 ){
            WiFi.softAPdisconnect();
        }
    }
}