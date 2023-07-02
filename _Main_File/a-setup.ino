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

    // Route for root / web page
    server.on( "/", serveIndexPage );

    server.on("/initial-message", initialMessage );

    // server.on("/settings", serveSettingsPage );

    server.on("/current-settings", currentSettings );

    server.on("/td", toggleDebug ); // td = Toggle debug
    
    server.onNotFound( serveIndexPage );

    // ----- Server Configuration ----
  	dnsServer.start( 53, "*", local_ip ); // DNS spoofing (Only for HTTP)


    // Start server
    server.begin();
	
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}
