void processLocalUserRequest(){
    StaticJsonDocument<96> userRequest = deserializeStringifiedJsonDataFromLocalUser();

    bool isBeingControlledLocally = userRequest["isBeingControlled"];
    bool motorStateRequest = userRequest["state"];
    bool processEndNotify = false, processStartNotify = true;
    IS_MOTOR_CONTROLLED_LOCALLY = isBeingControlledLocally;

    while( isBeingControlledLocally && webSocket.connectedClients() > 0 ){

        tankObj.waterLevelInTank();
        sumpObj.waterLevelInSump();

        if( processStartNotify ){
            processStartNotify = false;
            processEndNotify = true;
            notifyLocalClients(true);
            update_server(true, false, 0);
        }

       
        notifyLocalClients(false);
        toLoopFunctionsMultipleTimes();

        if( motorStateRequest ){
            motorController.turnOn();
            Serial.println("Motor On");
        } else {
            motorController.turnOff();
        }

        userRequest = deserializeStringifiedJsonDataFromLocalUser();

        isBeingControlledLocally = userRequest["isBeingControlled"];
        motorStateRequest = userRequest["state"];

        update_server(false , false, 0);
        Serial.println("Inside local loop");

        if( ( millis() - TANK_SUMP_WATER_LEVEL_UPDATE_INTERVAL_ELAPSED_TIME ) >= TANK_SUMP_WATER_LEVEL_UPDATE_INTERVAL ){
            update_server(true, false, 0);
            TANK_SUMP_WATER_LEVEL_UPDATE_INTERVAL_ELAPSED_TIME = millis();
        }
    }

    IS_MOTOR_CONTROLLED_LOCALLY = isBeingControlledLocally;
    
    water_pump();
    notifyLocalClients( processEndNotify );
    toLoopFunctionsMultipleTimes();
    update_server(processEndNotify, false, 0);

    // motorController.turnOff();

}