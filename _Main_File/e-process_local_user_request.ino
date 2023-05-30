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

        update_server(false, false, 0);
        Serial.println("Inside local loop");
    }

    notifyLocalClients( processEndNotify );
    toLoopFunctionsMultipleTimes();

    IS_MOTOR_CONTROLLED_LOCALLY = isBeingControlledLocally;
    // motorController.turnOff();

}