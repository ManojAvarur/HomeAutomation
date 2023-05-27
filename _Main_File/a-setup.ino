void setup(){
    Serial.begin(9600);

    // ----- WIFI Setup -------
    WiFi.mode(WIFI_AP_STA);
    WiFi.setAutoReconnect( false );

    setup_wifi( 6, 1 );
    
    // ----- Motor Setup ------
    pinMode(RELAY_1, OUTPUT);
    motorController.turnOff();

    // Route for root / web page
    server.on("/", [](){
        server.send(200, "text/html", getWebsite() );
    });

    server.on("/initial-message", [](){
      String jsonData = generateStringifiedJsonDataForLocalUser();
      Serial.println( jsonData );
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
        server.send(200, "text/html", getWebsite() );
    });

    // ----- Server Configuration ----
  	dnsServer.start( 53, "*", local_ip ); // DNS spoofing (Only for HTTP)


    // Start server
    server.begin();
	
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}
