bool get_user_requests_from_server(){
    int httpCode;
    int repeatCount = 5, count = 0;
    String result;
    String href = URL+"/get_user_requests.php?nodemcu_id=" + UNIQUE_ID;

    do{
        HTTPClient http;
        http.begin( client, href  );
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
        httpCode = http.GET();

        if( DEBUG_CODE ){  
            Serial.println("\n\tInside get user request from server . Responce Code : " + String( httpCode ) );  
            delay( DEBUG_DELAY_TIME );
        }
        
        if( httpCode == 204 || httpCode == 500 ){
            http.end();
            return false;
        } else if( httpCode != 200 ){
            delay( 500 );
            count += 1;
        } else {
            result = http.getString();
        }

        http.end();

    } while( httpCode != 200 && count <= repeatCount );

    if( httpCode == 200 ){
        deserializeJson( json_user_request, result );
        return true;
    } else {
        return false;
    }
}