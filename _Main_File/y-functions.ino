void water_pump(){
    if( tankObj.waterLevelInTank() != 4 ){
        if ( sumpObj.waterLevelInSump() <= 0) {
            motor_control( MOTOR_OFF );
            debug_log("\nTank level low turning off the pump because low water in summp");
        } else if( sumpObj.waterLevelInSump() == 3 ){
            motor_control( MOTOR_ON );
            debug_log("\nTank level low turning on the pump");
        } else {
            debug_log("\nWater Level low in sump");
        }
    } else {
        motor_control( MOTOR_OFF );
        debug_log("\nTank level high turning off the pump");
    }

}


void motor_control( uint8_t value ){
   Serial.println("\n\n\t Inside Motor control : ");
   if( ( value == MOTOR_ON ) && ( digitalRead( RELAY_1 ) != MOTOR_ON ) ){
       Serial.println("\n\t\tMOTOR_ON ");
       digitalWrite( RELAY_1, MOTOR_ON );
    } else if( ( value == MOTOR_OFF ) && ( digitalRead( RELAY_1 ) != MOTOR_OFF ) ) {
        Serial.println("\n\t\tMOTOR_OFF ");
        digitalWrite( RELAY_1, MOTOR_OFF );
    }
    //    digitalWrite( RELAY_1, value );
}

void update_server( pump_manual_override_data = false ){
    Serial.println("Inside update server");
    if( tankObj.isChanged || sumpObj.isChanged ){
        
        json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
        json_sensor_data_update["tank_status"] = tankObj.waterLevelInTank();
        json_sensor_data_update["sump_status"] = sumpObj.waterLevelInTank();
        json_sensor_data_update["motor_status"] = digitalRead( RELAY_1 );
        json_sensor_data_update["debug_log"] = DEBUG_LOG;

        int httpCode;
        int repeatCount = 5; count = 0;
        String jsonData;
        serializeJson( json_sensor_data_update, jsonData );

        do{
            HTTPClient http;
            http.begin(client, URL+"/update_sensor_data.php?data_ready=true&pump_manual_override_data=" + String( pump_manual_override_data ) );
            http.addHeader("Content-Type", "application/json");

            httpCode = http.GET( jsonData );

            http.end();

            Serial.println("Inside Send update server. Responce Code : " + String( httpCode ) );  
        
            if( httpCode != 200 ){
                delay( 500 );
                count += 1;
            }

        } while( httpCode != 200 && count <= repeatCount );
    }
}

bool check_requests_from_server(){
    if( ( millis() - USER_REQUEST_CHECK_INTERVAL_TARGET_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){

        USER_REQUEST_CHECK_INTERVAL_TARGET_TIME += USER_REQUEST_CHECK_INTERVAL;
        
        int httpCode;
        int repeatCount = 5; count = 0;
        String result;
        serializeJson( json_sensor_data_update, jsonData );

        do{
            HTTPClient http;
            http.begin(client, URL+"/get_user_requests.php?" );
            // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            httpCode = http.GET("nodemcut_id=" + UNIQUE_ID );

            http.end();

            Serial.println("Inside Send update server. Responce Code : " + String( httpCode ) );  
        
            if( httpCode == 404 ){
                return false;
            } else if( httpCode != 200 ){
                delay( 500 );
                count += 1;
            } else {
                result = http.getString();
            }

        } while( httpCode != 200 && count <= repeatCount );

        if( count <= repeatCount ){
            deserializeJson( json_user_request, result );
            if( json_user_request["pump_manual_overide_request"].equals("1") ){
                
            }
        }


    }
}

void debug_log( String value ){
    Serial.prinln( value );
    DEBUG_LOG = value;
}

void setup_wifi(){
   short while_counter = 0;
   short overall_wait_time = 5; //secs
   WiFi.begin(SSID, PASSWORD);
   Serial.println("Connecting");
   while( ( WiFi.status() != WL_CONNECTED ) && ( while_counter <= overall_wait_time )) {
       Serial.print(".");
       while_counter++;
       delay(1000);
   }
   Serial.println("");
   Serial.print("Connected to WiFi network with IP Address: ");
   Serial.println(WiFi.localIP());
}
