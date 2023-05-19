void setup(){
    Serial.begin(19200);

    // ----- WIFI Setup -------
    WiFi.mode(WIFI_AP_STA);
    WiFi.setAutoReconnect( false );

    setup_wifi( 6, 1 );
    
    // ----- Motor Setup ------
    pinMode(RELAY_1, OUTPUT);
    motor_control( MOTOR_OFF );

    // Route for root / web page
    server.on("/", [](){
        server.send(200, "text/html", getWebsite() );
    });
    
    server.onNotFound([](){
        server.send(200, "text/html", getWebsite() );
    });

    // ----- Server Configuration ----
  	dnsServer.start( 53, "*", local_ip ); // DNS spoofing (Only for HTTP)


    // Start server
    server.begin();
	
    
	webSocket.begin();
	webSocket.onEvent(webSocketEvent);
}
