void fetchDataFromMemory(){

    int currentMemLocPointer = USER_SETTINGS_MEM_LOC.searchStartLocation;
  
    for( uint8_t i = 1; i <= 6; i++ ){
    
        String dataFromMemmory = "";
        int count = 0;

        while( EEPROM.read( currentMemLocPointer ) != '\0' && count < 200 ){
            dataFromMemory += char( EEPROM.read( currentMemLocPointer ) ); 
            currentMemLocPointer++;
            count++;
        }

        if( count >= 200 ){
            break;
        }

        switch(i){
            case 1:
                SSID = dataFromMemory;
                USER_SETTINGS_MEM_LOC.ssidStart = USER_SETTINGS_MEM_LOC.searchStartLocation;
            break;

            case 2:
                PASSWORD = dataFromMemory;
                USER_SETTINGS_MEM_LOC.passwordStart = currentMemLocPointer;
            break;

            case 3:
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.tankLow = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.tankLow = limitValue;
                USER_SETTINGS_MEM_LOC.tankLowStart = currentMemLocPointer;
            break;

            case 4:
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.tankHigh = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.tankHigh = limitValue;
                USER_SETTINGS_MEM_LOC.tankHighStart = currentMemLocPointer;
            break;

            case 5:
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.sumpLow = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.sumpLow = limitValue;
                USER_SETTINGS_MEM_LOC.sumpLowStart = currentMemLocPointer;
            break;

            case 5:
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.sumpHigh = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.sumpHigh = limitValue;
                USER_SETTINGS_MEM_LOC.sumpHighStart = currentMemLocPointer;
            break;
        }

        currentMemLocPointer++;
    }
}

// This function is used to store the debug log in global variable
void debug_log( String value ){
    DEBUG_LOG = value;
    if( DEBUG_CODE ){
        delay( DEBUG_DELAY_TIME );
    }
}

// contains functions that are to be executed quite often
void toLoopFunctionsMultipleTimes(){   
    server.handleClient();
    webSocket.loop();
    dnsServer.processNextRequest(); 
}

// The following function takes an argument which represents whether the WIFI AP should be turned on or off
void control_wifi_ap( bool status ){
    if( status && !WIFI_AP_ENABLED ){
        WiFi.softAPConfig( local_ip, gateway, subnet );
        WiFi.softAP( AP_SSID, AP_PASSWORD );
        
        Serial.println("WiFi AP Enabled");
        WIFI_AP_ENABLED = true;
    } else if( !status ) {
        if( webSocket.connectedClients() <= 0 && WIFI_AP_ENABLED ){
            WIFI_AP_ENABLED = false;
            WiFi.enableAP( false );
            Serial.println("WiFi AP Disabled");
            // WiFi.softAPdisconnect( true );
        }
    }
}

// generates json data with all sensor information
String generateStringifiedJsonDataForLocalUser(){
    String jsonData = "";
    json_sensor_data_update.clear();
    json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;

    json_sensor_data_update["status"]["tank"]["currentLevel"] = tankObj.waterLevelInTank();
    json_sensor_data_update["status"]["tank"]["maximumLevel"] = TANK_AND_SUMP_LIMITS.tankHigh;
    json_sensor_data_update["status"]["tank"]["minimumLevel"] = TANK_AND_SUMP_LIMITS.tankLow;
    
    json_sensor_data_update["status"]["sump"]["currentLevel"] = sumpObj.waterLevelInSump();
    json_sensor_data_update["status"]["sump"]["maximumLevel"] = TANK_AND_SUMP_LIMITS.sumpHigh;
    json_sensor_data_update["status"]["sump"]["minimumLevel"] = TANK_AND_SUMP_LIMITS.sumpLow;
    
    json_sensor_data_update["status"]["motor"]["displayState"] = ( digitalRead(RELAY_1) )? 0 : 1;

    json_sensor_data_update["debug"]["display"] = SEND_DEBUG_LOG;
    json_sensor_data_update["debug"]["log"] = ( SEND_DEBUG_LOG )? DEBUG_LOG : "";
    

    if( !json_local_user_request.isNull() ) {
        json_sensor_data_update["status"]["motor"]["isControlled"] = json_local_user_request["isBeingControlled"];
        json_sensor_data_update["status"]["motor"]["state"] = json_local_user_request["state"];
    } else {
        json_sensor_data_update["status"]["motor"]["isControlled"] = false;
        json_sensor_data_update["status"]["motor"]["state"] = false;
    }
    json_sensor_data_update["status"]["motor"]["isOnlineControlled"] = IS_MOTOR_CONTROLLED_ONLINE;

    serializeJson( json_sensor_data_update, jsonData );
    return jsonData;
}

StaticJsonDocument<96> deserializeStringifiedJsonDataFromLocalUser(){
    if( string_local_user_request != "" ){
        deserializeJson( json_local_user_request, string_local_user_request );
        string_local_user_request = "";
    }
    return json_local_user_request;
}