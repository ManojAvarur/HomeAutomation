void processLocalUserRequest(){
    StaticJsonDocument<96> userRequest = deserializeStringifiedJsonDataFromLocalUser();

    bool isBeingControlledLocally = userRequest["isBeingControlled"];
    bool motorStateRequest = userRequest["state"];
    bool processEndNotify = false, processStartNotify = true;

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
    }

    notifyLocalClients( processEndNotify );
    toLoopFunctionsMultipleTimes();

    motorController.turnOff();

}