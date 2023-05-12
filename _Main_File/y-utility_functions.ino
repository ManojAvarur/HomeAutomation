// This function is used to store the debug log in global variable
void debug_log( String value ){
    DEBUG_LOG = value;
    if( DEBUG_CODE ){
        Serial.println("Debug Log : " + value );
        delay( DEBUG_DELAY_TIME );
    }
}

// The following function takes an argument which represents whether the WIFI AP should be turned on or off
void control_wifi_ap( bool status ){
    if( status && !wifi_ap_enabled ){
        // WiFi.disconnect();
        WiFi.softAPConfig( local_ip, gateway, subnet );
        WiFi.softAP( AP_SSID, AP_PASSWORD );
        
        Serial.println("WiFi AP Enabled");
        wifi_ap_enabled = true;
    } else if( !status ) {
        Serial.println("ws.getClients().length() <= " + String( ws.getClients().length() ) + " && " + String( wifi_ap_enabled ) );
        if( ws.getClients().length() <= 0 && wifi_ap_enabled ){
            wifi_ap_enabled = false;
            WiFi.enableAP( false );
            Serial.println("WiFi AP Disabled");
            // WiFi.softAPdisconnect( true );
        }
    }
}