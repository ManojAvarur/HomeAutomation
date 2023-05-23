void update_server( int pump_manual_override_data ){

    if( tankObj.isDataChanged() || sumpObj.isDataChanged() || motorController.isDataChanged() || ( pump_manual_override_data == 1 ) ){
    
        int httpCode;
        int repeatCount = 5, count = 0;
        String jsonData;
        json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
        json_sensor_data_update["tank_status"] = tankObj.waterLevelInTank();
        json_sensor_data_update["sump_status"] = sumpObj.waterLevelInSump();
        json_sensor_data_update["motor_status"] = !digitalRead( RELAY_1 );
        json_sensor_data_update["debug_log"] = DEBUG_LOG;
        serializeJson( json_sensor_data_update, jsonData );

        String href = URL+"/update_sensor_data.php?data_ready=true&pump_manual_override_data=" + String( ( pump_manual_override_data >= 1 )? "true" : "false" );
        do{
            HTTPClient http;
            http.begin( client, href );
            
            http.addHeader("Content-Type", "application/json");

            httpCode = http.POST( jsonData );

            http.end();
        
            if( httpCode != 200 ){
                delay( 500 );
                count += 1;
            }

        } while( httpCode != 200 && count <= repeatCount );

        if( httpCode != 200 ){  
            motorController.rollBackChangeNotifier();
            tankObj.rollBackChangeNotifier();
            sumpObj.rollBackChangeNotifier();
        }

    }
}