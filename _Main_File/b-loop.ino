void loop(){
    toLoopFunctionsMultipleTimes();
    processLocalUserRequest();

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
    
    // Serial.println("Looping : " + String( WiFi.status() ) );

}