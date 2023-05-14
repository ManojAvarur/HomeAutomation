void loop(){
    loopMultipleTimes();

    water_pump();

    if( WiFi.status() == WL_CONNECTED ){
        // update_server( 0 );
        // check_requests_from_server();
        control_wifi_ap( false );
    } else {
        if( ( millis() - WIFI_RECONNECTION_INTERVAL_ELAPSED_TIME ) >= WIFI_RECONNECTION_INTERVAL ){
            setup_wifi( 0, 0 );
            WIFI_RECONNECTION_INTERVAL_ELAPSED_TIME = millis();
        }
        control_wifi_ap( true );
    }
    
    delay(1000);
    Serial.println("Looping : " + String( WiFi.status() ) );

    loopMultipleTimes();
}

// else {
    //     // Initiate wifi connection and 
    //     wifi_connection_initiatied = !wifi_connection_initiatied;
    //     if( !setup_wifi( 1, 0 ) && !wifi_connection_initiatied ){
    //         control_wifi_ap( true );
    //     }
    // }
