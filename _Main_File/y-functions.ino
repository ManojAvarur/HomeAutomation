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

void update_server( int pump_manual_override_data ){
    Serial.println("Inside update server");

    if( tankObj.isChanged || sumpObj.isChanged || motor_status_changed || ( pump_manual_override_data == 1 ) ? true : false ){
        
        json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
        json_sensor_data_update["tank_status"] = tankObj.waterLevelInTank();
        json_sensor_data_update["sump_status"] = sumpObj.waterLevelInTank();
        json_sensor_data_update["motor_status"] = digitalRead( RELAY_1 );
        json_sensor_data_update["debug_log"] = DEBUG_LOG;

        int httpCode;
        int repeatCount = 5, count = 0;
        String jsonData;
        serializeJson( json_sensor_data_update, jsonData );

        do{
            HTTPClient http;
            http.begin(client, URL+"/update_sensor_data.php?data_ready=true&pump_manual_override_data=" + ( pump_manual_override_data >= 1 )? "true" : "false" );
            http.addHeader("Content-Type", "application/json");

            httpCode = http.get( jsonData );

            http.end();

            Serial.println("Inside Send update server. Responce Code : " + String( httpCode ) );  
        
            if( httpCode != 200 ){
                delay( 500 );
                count += 1;
            }

        } while( httpCode != 200 && count <= repeatCount );

        if( httpCode == 200 ){  
            motor_status_changed = false;
            tankObj.isChanged = false;
            sumpObj.isChanged = false;
        }
    }
}

void check_requests_from_server(){
    if( ( millis() - USER_REQUEST_CHECK_INTERVAL_TARGET_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){
        USER_REQUEST_CHECK_INTERVAL_TARGET_TIME += USER_REQUEST_CHECK_INTERVAL;

        if( get_user_requests_from_server() ){


            USER_REQUEST_CHECK_INTERVAL = 10000;
            USER_REQUEST_CHECK_INTERVAL_TARGET_TIME = millis();
            unsigned long counter = 0L;

            while( json_user_request["pump_manual_overide_request"].as<String>().equals("1") && json_user_request["execute_status"] ){

                if( json_user_request["pump_take_over_complete_control"].as<String>().equals("1") ) {
                    motor_control( ( json_user_request["pump_on_off_status"].as<String>().equals("1") )? MOTOR_ON : MOTOR_OFF );
                    update_server( ++counter );
                } else {
                    if( json_user_request["pump_on_off_status"].as<String>().equals("0") && json_user_request["time_in_hours"].as<String>().toInt() >= 7 ){
                        water_pump();
                    } else if(json_user_request["pump_on_off_status"].as<String>().equals("1") ){
                        water_pump();
                    } else {
                        motor_control( MOTOR_OFF );
                    }

                    update_server( ++counter );
                }

                if( ( millis() - USER_REQUEST_CHECK_INTERVAL_TARGET_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){
                    USER_REQUEST_CHECK_INTERVAL_TARGET_TIME += USER_REQUEST_CHECK_INTERVAL;
                    if( ! get_user_requests_from_server() ){
                        break;
                    }
                }
            }
            USER_REQUEST_CHECK_INTERVAL = 30000;
            USER_REQUEST_CHECK_INTERVAL_TARGET_TIME = millis();
        }
    }
}


bool get_user_requests_from_server(){
     
    int httpCode;
    int repeatCount = 5, count = 0;
    String result;

    do{
        HTTPClient http;
        http.begin(client, URL+"/get_user_requests.php?" );
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
        httpCode = http.get("nodemcut_id=" + UNIQUE_ID );

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

    if( httpCode == 200 ){
        deserializeJson( json_user_request, result );
        return true;
    } else {
        return false;
    }
}

void debug_log( String value ){
    Serial.println( value );
    DEBUG_LOG = value;
}

void motor_control( uint8_t value ){
   Serial.println("\n\n\t Inside Motor control : ");
   if( ( value == MOTOR_ON ) && ( digitalRead( RELAY_1 ) != MOTOR_ON ) ){
       Serial.println("\n\t\tMOTOR_ON ");
       digitalWrite( RELAY_1, MOTOR_ON );
       motor_status_changed = true;
    } else if( ( value == MOTOR_OFF ) && ( digitalRead( RELAY_1 ) != MOTOR_OFF ) ) {
        Serial.println("\n\t\tMOTOR_OFF ");
        digitalWrite( RELAY_1, MOTOR_OFF );
        motor_status_changed = true;
    }
    //    digitalWrite( RELAY_1, value );
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
