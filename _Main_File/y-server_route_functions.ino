void serveIndexPage(){
    server.send( 200, "text/html", INDEX_PAGE );
}

void serveSettingsPage(){
    server.send( 200, "text/html", SETTINGS_PAGE );
}

void initialMessage(){
    String jsonData = generateStringifiedJsonDataForLocalUser();
    server.sendHeader("Access-Control-Allow-Origin", "*", true);
    server.send(200, "application/json", jsonData );
}

void currentSettings(){
    String jsonData;
    general_purpose_json_holder.clear();

    general_purpose_json_holder["wifi"]["ssid"] = SSID;
    general_purpose_json_holder["wifi"]["password"] = PASSWORD;

    general_purpose_json_holder["tank"]["low"] = TANK_AND_SUMP_LIMITS.tankLow;
    general_purpose_json_holder["tank"]["high"] = TANK_AND_SUMP_LIMITS.tankHigh;

    general_purpose_json_holder["sump"]["low"] = TANK_AND_SUMP_LIMITS.sumpLow;
    general_purpose_json_holder["sump"]["high"] = TANK_AND_SUMP_LIMITS.sumpHigh;

    serializeJson( general_purpose_json_holder, jsonData );
    server.send(200, "application/json", jsonData );
}

void toggleDebug(){
    SEND_DEBUG_LOG = !SEND_DEBUG_LOG;
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
}

void updateWifiCred(){
    for(uint8_t i = 0; i < server.args(); i++){ 
        String value = server.arg(i);
        String nameAttribute = server.argName(i);
    
        if( String("ssid") == nameAttribute ){ 
            SSID = value; 
        }

        if( String("password") == nameAttribute ){ 
            PASSWORD = value; 
        } 
    }

    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "");
}

void updateTankSensorLimits(){
    for(uint8_t i = 0; i < server.args(); i++){ 
        float value = String( server.arg(i).toFloat(), ROUND_FLOAT_VALUES_TO ).toFloat();
        String nameAttribute = server.argName(i);
    
        if( String("tlow") == nameAttribute ){ 
            TANK_AND_SUMP_LIMITS.tankLow = value; 
        }

        if( String("thigh") == nameAttribute ){ 
            TANK_AND_SUMP_LIMITS.tankHigh = value; 
        } 
    }

    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "");
}

void updateSumpSensorLimits(){
    for(uint8_t i = 0; i < server.args(); i++){ 
        float value = String( server.arg(i).toFloat(), ROUND_FLOAT_VALUES_TO ).toFloat();
        String nameAttribute = server.argName(i);
    
        if( String("slow") == nameAttribute ){
            TANK_AND_SUMP_LIMITS.sumpLow = value; 
        }

        if( String("shigh") == nameAttribute ){
            TANK_AND_SUMP_LIMITS.sumpHigh = value; 
        } 
    }

    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "");
}

void getSensorValue(){
    general_purpose_json_holder.clear();

    if( server.hasArg("plain") == false ){
        server.send(400, "text/plain", "Body not received");
        return;
    }

    String payloadString = server.arg("plain");
    float sensorData = 0;
    
    deserializeJson( general_purpose_json_holder, payloadString );


    if( general_purpose_json_holder["captureFrom"] == "Tank" ){
        sensorData = tankObj.waterLevelInTank( true );
    }

    if( general_purpose_json_holder["captureFrom"] == "Sump" ){
        sensorData = sumpObj.waterLevelInSump( true );
    }

    // Rounding of float to 2 decimals
    general_purpose_json_holder["requestedData"] = String( sensorData, ROUND_FLOAT_VALUES_TO ).toFloat();

    payloadString = "";
    serializeJson( general_purpose_json_holder, payloadString );

    server.send( 200, "application/json", payloadString );
}

void commitTempSettingsDataToMemory(){
    
    int currentMemLocPointer = EEPROM_DATA_START_LOC;

    String settingsToBeCommited = 
        SSID + '\0' +
        PASSWORD + '\0' +
        String( TANK_AND_SUMP_LIMITS.tankLow ) + '\0' + 
        String( TANK_AND_SUMP_LIMITS.tankHigh ) + '\0' + 
        String( TANK_AND_SUMP_LIMITS.sumpLow ) + '\0' + 
        String( TANK_AND_SUMP_LIMITS.sumpHigh ) + '\0' 
    ;

    for( int i = 0; i < settingsToBeCommited.length(); i++, currentMemLocPointer++ ){

        char dataFetchedFromMem = char( EEPROM.read( currentMemLocPointer ) );

        if( dataFetchedFromMem != settingsToBeCommited.charAt(i) ){
            Serial.println( "@ " + String(currentMemLocPointer) + " : " + dataFetchedFromMem + " != " + settingsToBeCommited.charAt(i) );
            EEPROM.write( currentMemLocPointer, settingsToBeCommited.charAt(i) );
        }
    }

    EEPROM.commit();

    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "");
}