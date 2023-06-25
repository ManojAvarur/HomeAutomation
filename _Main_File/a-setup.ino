void setup(){
    Serial.begin(19200);

    // ----- WIFI Setup -------
    WiFi.mode(WIFI_AP_STA);
    WiFi.setAutoReconnect( false );

    setup_wifi( 6, 1 );
    
    // ----- Motor Setup ------
    motorController.turnOff();

    // Route for root / web page
    server.on("/", [](){
		server.sendContent( serveIndexSite() );
    });

    server.on("/initial-message", [](){
		String jsonData = generateStringifiedJsonDataForLocalUser();
		server.sendHeader("Access-Control-Allow-Origin", "*", true);
		server.send(200, "application/json", jsonData );
    });

    // td > Toggle debug
    server.on("/td", [](){
        SEND_DEBUG_LOG = !SEND_DEBUG_LOG;
        server.sendHeader("Location", String("/"), true);
        server.send(302, "text/plain", "");
    });
    
    server.onNotFound([](){
        server.sendContent( serveIndexSite() );
    });

    // ----- Server Configuration ----
  	dnsServer.start( 53, "*", local_ip ); // DNS spoofing (Only for HTTP)


    // Start server
    server.begin();
	
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}
