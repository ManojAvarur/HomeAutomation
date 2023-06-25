void loop(){
    toLoopFunctionsMultipleTimes();
    processLocalUserRequest();

    water_pump();
    if( WiFi.status() == WL_CONNECTED ){
        update_server(false, false, 0);

        toLoopFunctionsMultipleTimes();
        processLocalUserRequest();

        check_requests_from_server();

        toLoopFunctionsMultipleTimes();
        processLocalUserRequest();

        control_wifi_ap( false );
    } else {
        if( ( millis() - WIFI_RECONNECTION_INTERVAL_ELAPSED_TIME ) >= WIFI_RECONNECTION_INTERVAL ){
            setup_wifi( 0, 0 );
            // WIFI_RECONNECTION_INTERVAL_ELAPSED_TIME = millis();
            WIFI_RECONNECTION_INTERVAL_ELAPSED_TIME += WIFI_RECONNECTION_INTERVAL;
        }
        control_wifi_ap( true );
    }
}