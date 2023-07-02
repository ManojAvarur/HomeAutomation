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
        String value = (String) server.arg(i);

        switch( server.argName(i) ){
            case "ssid": SSID = value; break;
            case "password": PASSWORD = value; break;
        } 
    }

    server.sendHeader("Location", "/settings", true);
    server.send(302, "text/plain", "");
}