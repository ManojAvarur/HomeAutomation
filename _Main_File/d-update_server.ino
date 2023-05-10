void update_server( int pump_manual_override_data ){

    if( tankObj.isDataChanged() || sumpObj.isDataChanged() || motor_status_changed || ( pump_manual_override_data == 1 ) ){
        
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
        }
    }
}