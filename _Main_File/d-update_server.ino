void update_server( bool forceUpdate, bool pump_manual_override_data, int repeatCount ){

    if( !tankObj.isDataChanged() && !sumpObj.isDataChanged() && !motorController.isDataChanged() && !forceUpdate ){
        Serial.println("Failed to update");
        return;
    }

    delay(1000);

    int httpCode;
    int count = 1;
    String jsonData;
    json_sensor_data_update.clear();
    json_sensor_data_update["nodemcu_id"] = UNIQUE_ID;
    json_sensor_data_update["tank_status"] = tankObj.waterLevelInTank();
    json_sensor_data_update["sump_status"] = sumpObj.waterLevelInSump();
    json_sensor_data_update["motor_status"] = !digitalRead( RELAY_1 );
    json_sensor_data_update["debug_log"] = DEBUG_LOG;
    serializeJson( json_sensor_data_update, jsonData );

    String href = URL+"/update_sensor_data.php?data_ready=true&motor_controlled_locally="+ String(IS_MOTOR_CONTROLLED_LOCALLY) +"&pump_manual_override_data=" + String(pump_manual_override_data);
    do{
        HTTPClient http;
        http.begin( client, href );
        
        http.addHeader("Content-Type", "application/json");

        httpCode = http.POST( jsonData );

        http.end();
    
        if( httpCode != 200 ){
            delay( 500 );
            count++;
        }

    } while( httpCode != 200 && count <= repeatCount );

    if( httpCode != 200 ){  
        Serial.println("Failed");
        Serial.println( href );
        Serial.println( jsonData );
        delay(30000);
        motorController.rollBackChangeNotifier();
        tankObj.rollBackChangeNotifier();
        sumpObj.rollBackChangeNotifier();
    } else {
      Serial.println( href );
      Serial.println( jsonData );

      delay(20000);
    }

}
