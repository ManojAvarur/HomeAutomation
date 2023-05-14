void notifyClients() {
    String jsonData = "";
    json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
    json_sensor_data_update["tank_status"] = tankObj.waterLevelInTank();
    json_sensor_data_update["sump_status"] = sumpObj.waterLevelInSump();
    json_sensor_data_update["motor_status"] = !digitalRead( RELAY_1 );
    json_sensor_data_update["debug_log"] = DEBUG_LOG;
    serializeJson( json_sensor_data_update, jsonData );
    webSocket.broadcastTXT( jsonData );

}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
	char *textToBroadcast;
   	if (type == WStype_TEXT){
		payload[length] = '\0';
		textToBroadcast = (char*)payload;
	}
}