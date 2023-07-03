void setup(){
    Serial.begin(19200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // ----- WIFI Setup -------
    WiFi.mode( WIFI_AP_STA );
    WiFi.setAutoReconnect( false );

    setup_wifi( 6, 1 );
    
    // ----- Motor Setup ------
    motorController.turnOff();

    // Routes for web pages
    server.on( "/", serveIndexPage );

    server.on("/settings", serveSettingsPage );

    server.onNotFound( serveIndexPage );

    // Routes for data accessing / processing   
    server.on("/initial-message", initialMessage );

    server.on("/current-settings", currentSettings );

    server.on("/td", toggleDebug ); // td = Toggle debug

    server.on("/update-wifi-cred", updateWifiCred );

    server.on("/update-tank-sensor", [](){ } );

    server.on("/update-sump-sensor", [](){ } );

    server.on("/commit-data", [](){ } );
    

    // ----- Server Configuration ----
  	dnsServer.start( 53, "*", local_ip ); // DNS spoofing (Only for HTTP)


    // Start server
    server.begin();
	
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}
