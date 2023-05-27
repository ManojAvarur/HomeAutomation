void processLocalUserRequest(){
    StaticJsonDocument<96> userRequest = deserializeStringifiedJsonDataFromLocalUser();

    bool isBeingControlledLocally = userRequest["isBeingControlled"];
    bool motorStateRequest = userRequest["state"];
    bool processEndNotify = false, processStartNotify = true;
    IS_MOTOR_CONTROLLED_LOCALLY = isBeingControlledLocally;

    while( isBeingControlledLocally ){

        notifyLocalClients( processStartNotify );
        processStartNotify = false;

        processEndNotify = true;
       
        notifyLocalClients( false );
        toLoopFunctionsMultipleTimes();

        if( motorStateRequest ){
            motorController.turnOn();
        } else {
            motorController.turnOff();
        }

        userRequest = deserializeStringifiedJsonDataFromLocalUser();

        isBeingControlledLocally = userRequest["isBeingControlled"];
        motorStateRequest = userRequest["state"];

        update_server(0);
    }

    notifyLocalClients( processEndNotify );
    toLoopFunctionsMultipleTimes();

    IS_MOTOR_CONTROLLED_LOCALLY = isBeingControlledLocally;
    motorController.turnOff();

}