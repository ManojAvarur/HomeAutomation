void notifyLocalClients( bool forceNotify = false ) {
    if( tankObj.isDataChanged() || sumpObj.isDataChanged() || motorController.isDataChanged_Local() || forceNotify ){
        Serial.println("Inside notify local clients");
        String jsonData = generateStringifiedJsonDataForLocalUser();
        webSocket.broadcastTXT( jsonData );
    }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
    char *broadCastedText;
    if (type == WStype_TEXT){
        payload[length] = '\0';
        broadCastedText = (char*)payload;
        string_local_user_request = broadCastedText;
    }
}