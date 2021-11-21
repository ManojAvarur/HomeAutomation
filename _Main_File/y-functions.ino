void lowDigitalPin( int pin, bool changeToInput = false, bool delayRequired = false ){
    pinMode( pin, OUTPUT );
    digitalWrite( pin, LOW );

    if( changeToInput ){
        pinMode( pin, INPUT );
    }
    if( delayRequired ){
        delay(200);
    }
}

void highDigitalPin( int pin, bool changeToInput = false, bool delayRequired = false ){
    pinMode( pin, OUTPUT );
    digitalWrite( pin, HIGH );

    if( changeToInput ){
        pinMode( pin, INPUT );
    }
    if( delayRequired ){
        delay(200);
    }
}

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
