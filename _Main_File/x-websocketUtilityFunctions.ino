void notifyClients() {
    String jsonData = "";
    json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
    json_sensor_data_update["tank_status"] = tankObj.waterLevelInTank();
    json_sensor_data_update["sump_status"] = sumpObj.waterLevelInSump();
    json_sensor_data_update["motor_status"] = !digitalRead( RELAY_1 );
    json_sensor_data_update["debug_log"] = DEBUG_LOG;
    json_sersor_data_update["random"] = random()
    serializeJson( json_sensor_data_update, jsonData );
    Serial.println( jsonData );
    ws.textAll( jsonData );
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;

    if( info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT ){
        data[len] = 0;
        if( strcmp( (char*)data, "toggle" ) == 0){
            motor_control( !digitalRead( RELAY_1 ) );
            notifyClients();
        }
    }
}


void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
            break;

        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
            break;

        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
            break;

        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;  
    }
}