void check_requests_from_server(){

    if( ( millis() - USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME ) < USER_REQUEST_CHECK_INTERVAL ){
        return;
    }

    USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME += USER_REQUEST_CHECK_INTERVAL;

    if( !get_user_requests_from_server() ){
        return;
    }

    bool firstTimeNotify = true;
    USER_REQUEST_CHECK_INTERVAL = 10000;

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

        IS_MOTOR_CONTROLLED_ONLINE = true;

        if( json_user_request["pump_take_over_complete_control"].as<String>().toInt() == 1 ) {

            if( json_user_request["pump_on_off_status"].as<String>().toInt() == 1 ){ 
                Serial.println("Overide On : Complete Control On : Motor On");
                motorController.turnOn();
            } else { 
                Serial.println("Overide On : Complete Control On : Motor Off");
                motorController.turnOff();
            }

        } else {
            
            if(( json_user_request["pump_on_off_status"].as<String>().toInt() == 0 && 
                    json_user_request["time_in_hours"].as<String>().toInt() >= 19 && 
                    json_user_request["time_in_hours"].as<String>().toInt() <= 20  
                ) || (
                    json_user_request["pump_on_off_status"].as<String>().toInt() == 1
                ) 
            ){
                water_pump();
            } else {
                Serial.println("Overide On : Complete Control Off : Motor Off");
                motorController.turnOff();
            }

        }
        
        update_server(firstTimeNotify, true, 1);

        notifyLocalClients(firstTimeNotify);
        toLoopFunctionsMultipleTimes();

        if( ( millis() - USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){
            USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME += USER_REQUEST_CHECK_INTERVAL;

            // If failed to fetch new requests break the loop
            if( !get_user_requests_from_server() ){
                IS_MOTOR_CONTROLLED_ONLINE = false;
                notifyLocalClients(true);
                toLoopFunctionsMultipleTimes();
                break;
            }
        }

        // Checking for any requests from local user
        if( !string_local_user_request.isEmpty() ){
            string_local_user_request = "";
            notifyLocalClients(true);
        }

        firstTimeNotify = false;
    }

    IS_MOTOR_CONTROLLED_ONLINE = false;
    USER_REQUEST_CHECK_INTERVAL = 30000;
}
