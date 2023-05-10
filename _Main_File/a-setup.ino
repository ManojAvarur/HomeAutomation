void setup(){
    Serial.begin(115200);

    // ----- WIFI Setup -------
    WiFi.mode(WIFI_AP_STA);
    WiFi.setAutoReconnect( false );

    setup_wifi( 6, 1 );
    
    // ----- Motor Setup ------
    pinMode(RELAY_1, OUTPUT);
    motor_control( MOTOR_OFF );

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", "<h1 style='text-align: center;'>Page is still being developed</h1>" );
    });
    
    server.onNotFound([](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", "<h1 style='text-align: center;'>Page is still being developed</h1>" );
    });

    // ----- Server Configuration ----
    ws.onEvent(onEvent);
    server.addHandler(&ws);

    // Start server
    server.begin();
}
