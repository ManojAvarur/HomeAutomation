void water_pump(){

    if( tankObj.waterLevelInTank() != 4 ){

        if ( sumpObj.waterLevelInSump() <= 0) {
            motor_control( MOTOR_OFF );
            debug_log("\nTank level low turning off the pump because low water in sump");
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

    if( tankObj.isDataChanged() || sumpObj.isDataChanged() || motor_status_changed || ( pump_manual_override_data == 1 ) ? true : false ){
        
        json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
        json_sensor_data_update["tank_status"] = tankObj.waterLevelInTank();
        json_sensor_data_update["sump_status"] = sumpObj.waterLevelInSump();
        json_sensor_data_update["motor_status"] = ! digitalRead( RELAY_1 );
        json_sensor_data_update["debug_log"] = DEBUG_LOG;

        int httpCode;
        int repeatCount = 5, count = 0;
        String jsonData;
        serializeJson( json_sensor_data_update, jsonData );
        String href = URL+"/update_sensor_data.php?data_ready=true&pump_manual_override_data=" + String( ( pump_manual_override_data >= 1 )? "true" : "false" );
        do{
            HTTPClient http;
            http.begin( client, href );
            
            http.addHeader("Content-Type", "application/json");

            httpCode = http.POST( jsonData );

            http.end();

            if( DEBUG_CODE ){
                Serial.println("\n\t\t Inside Send update server .\n\t Responce Code : " + String( httpCode ) ); 
                Serial.println("\n\t\t\t tankObj.isDataChanged() : " + String( tankObj.isDataChanged() ) );
                Serial.println("\n\t\t\t sumpObj.isDataChanged() : " + String( sumpObj.isDataChanged() ) );
                Serial.println("\n\t\t\t motor_status_changed : " + String( motor_status_changed ) );
                Serial.println("\n\t\t\t ( pump_manual_override_data == 1 ) ? true : false : " + String( ( pump_manual_override_data == 1 ) ? true : false ) );
                
                delay( DEBUG_DELAY_TIME );

            }

        
            if( httpCode != 200 ){
                delay( 500 );
                count += 1;
            }

        } while( httpCode != 200 && count <= repeatCount );

        if( httpCode == 200 ){  
            motor_status_changed = false;
            tankObj.setIsChangedToFalse();
            sumpObj.setIsChangedToFalse();
            Serial.println("\n\t\t\t tankObj.isDataChanged() : " + String( tankObj.isDataChanged() ) );
        }
    }
}

void check_requests_from_server(){
    if( ( millis() - USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){
        USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME += USER_REQUEST_CHECK_INTERVAL;

        if( get_user_requests_from_server() ){

            USER_REQUEST_CHECK_INTERVAL = 10000;
            unsigned long counter = 0L;

            if( DEBUG_CODE ){
                Serial.println("\n\tInside user related operations umanual overide is set to true." );  
                Serial.println("\n\t\t pump_manual_overide_request : " + String( json_user_request["pump_manual_overide_request"].as<String>().toInt() ) );  
                Serial.println("\n\t\t pump_take_over_complete_control : " + String( json_user_request["pump_take_over_complete_control"].as<String>().toInt() ) );  
                Serial.println("\n\t\t pump_on_off_status : " + String( json_user_request["pump_on_off_status"].as<String>().toInt() ) );  
                Serial.println("\n\t\t time_in_hours : " + String( json_user_request["time_in_hours"].as<String>().toInt() ) );  
                Serial.println("\n\t\t execute_status : " + String( json_user_request["execute_status"].as<String>().toInt() ));  
                delay( DEBUG_DELAY_TIME );
            }

            while( json_user_request["pump_manual_overide_request"].as<String>().toInt() == 1  && json_user_request["execute_status"].as<String>().toInt() == 1 ){

                Serial.println("\n\nMillis : " + String( millis() ) + "\n USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME =" + String( USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME ) );

                if( json_user_request["pump_take_over_complete_control"].as<String>().toInt() == 1 ) {
                    
                    motor_control( ( json_user_request["pump_on_off_status"].as<String>().toInt() == 1 )? MOTOR_ON : MOTOR_OFF );
                    tankObj.waterLevelInTank();
                    sumpObj.waterLevelInSump();
                    update_server( ++counter );

                    if( DEBUG_CODE ){
                        Serial.println("\n\nInside Manual Overide Complete Control");
                        Serial.println("\n\t\t pump_on_off_status : " + String( json_user_request["pump_on_off_status"].as<String>().toInt() ));  
                        delay( DEBUG_DELAY_TIME );
                    }

                } else {
                    if( json_user_request["pump_on_off_status"].as<String>().toInt() == 0 && json_user_request["time_in_hours"].as<String>().toInt() >= 19 && json_user_request["time_in_hours"].as<String>().toInt() <= 20  ){
                        water_pump();

                        if( DEBUG_CODE ){
                            Serial.println("\n\tInside manual overide and under water_pump() as it is grater than 7");  
                            delay( DEBUG_DELAY_TIME );
                        }

                    } else if(json_user_request["pump_on_off_status"].as<String>().toInt() == 1 ){

                        water_pump();

                        if( DEBUG_CODE ){
                            Serial.println("\n\tInside manual overide and under water_pump() as pump_on_off_status = 1");  
                            delay( DEBUG_DELAY_TIME );
                        }

                    } else {

                        motor_control( MOTOR_OFF );
                        tankObj.waterLevelInTank();
                        sumpObj.waterLevelInSump();
                        
                        if( DEBUG_CODE ){
                            Serial.println("\n\tInside manual overide and under water_pump() as pump_on_off_status =  0");  
                            delay( DEBUG_DELAY_TIME );
                        }
                    }

                    update_server( ++counter );
                }

                if( ( millis() - USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){
                    USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME += USER_REQUEST_CHECK_INTERVAL;
                    if( ! get_user_requests_from_server() ){
                        break;
                    }

                }

            }

            USER_REQUEST_CHECK_INTERVAL = 30000;
        }
    }
}


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

void debug_log( String value ){
    Serial.println( value );
    DEBUG_LOG = value;
    if( DEBUG_CODE ){
        delay( DEBUG_DELAY_TIME );
    }
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
