void processLocalUserRequest(){
    StaticJsonDocument<96> userRequest = deserializeStringifiedJsonDataFromLocalUser();

    bool isBeingControlledLocally = userRequest["isBeingControlled"];
    bool motorStateRequest = userRequest["state"];
    bool doNotifyLocalClients = false;

    while( isBeingControlledLocally ){

        doNotifyLocalClients = true;

        if( motorStateRequest ){
            motorController.turnOn();
        } else {
            motorController.turnOff();
        }

        notifyLocalClients( false );
        toLoopFunctionsMultipleTimes();

        userRequest = deserializeStringifiedJsonDataFromLocalUser();

        isBeingControlledLocally = userRequest["isBeingControlled"];
        motorStateRequest = userRequest["state"];
    }

    notifyLocalClients( doNotifyLocalClients );
    toLoopFunctionsMultipleTimes();

    motorController.turnOff();

}