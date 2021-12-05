void setup_wifi(){
    int while_counter = 0;
    int delay_counter = 0;
    WiFi.begin(SSID, PASSWORD);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
}
