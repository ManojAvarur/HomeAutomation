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
        float value = server.arg(i).toFloat();
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
        float value = server.arg(i).toFloat();
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

    deserializeJson( general_purpose_json_holder, payloadString );

    if( general_purpose_json_holder["captureFrom"] == "Tank" ){
        general_purpose_json_holder["requestedData"] = tankObj.waterLevelInTank( true );
    }

    if( general_purpose_json_holder["captureFrom"] == "Sump" ){
        general_purpose_json_holder["requestedData"] = sumpObj.waterLevelInSump( true );
    }

    payloadString = "";
    serializeJson( general_purpose_json_holder, payloadString );

    server.send( 200, "application/json", payloadString );
}

void commitTempSettingsDataToMemory(){
    bool isChanged = false;

    if( !isChanged &&  )

}