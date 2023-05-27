// This function is used to store the debug log in global variable
void debug_log( String value ){
    DEBUG_LOG = value;
    if( DEBUG_CODE ){
        Serial.println("Debug Log : " + value );
        delay( DEBUG_DELAY_TIME );
    }
}

// contains functions that are to be executed quite often
void toLoopFunctionsMultipleTimes(){   
    webSocket.loop();
    dnsServer.processNextRequest(); 
    server.handleClient();
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
    json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
    json_sensor_data_update["status"]["tank"] = tankObj.waterLevelInTank();
    json_sensor_data_update["status"]["sump"] = sumpObj.waterLevelInSump();
    json_sensor_data_update["status"]["motor"]["displayState"] = ( digitalRead(RELAY_1) )? 0 : 1;

    json_sensor_data_update["debug"]["display"] = SEND_DEBUG_LOG;
    if( SEND_DEBUG_LOG ){
        json_sensor_data_update["debug"]["log"] = DEBUG_LOG;
    }

    json_sensor_data_update["status"]["motor"]["isControlled"] = false;
    json_sensor_data_update["status"]["motor"]["state"] = false;
    json_sensor_data_update["status"]["motor"]["isOnlineControlled"] = IS_MOTOR_CONTROLLED_ONLINE;

    if( !json_local_user_request.isNull() ) {
        json_sensor_data_update["status"]["motor"]["isControlled"] = json_local_user_request["isBeingControlled"];
        json_sensor_data_update["status"]["motor"]["state"] = json_local_user_request["state"];
    }

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