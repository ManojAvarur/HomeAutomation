void water_pump(){

    if( tankObj.waterLevelInTank() != 3 )
}


void setup_wifi(){
    short while_counter = 0;
    short overall_wait_time = 5; //secs
    WiFi.begin(SSID, PASSWORD);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED && ( while_counter != overall_wait_time )) {
        delay(1000);
        Serial.print(".");
        while_counter++;
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}
