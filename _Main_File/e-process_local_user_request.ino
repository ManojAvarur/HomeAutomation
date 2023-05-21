void processLocalUserRequest(){
    StaticJsonDocument<96> userRequest = deserializeStringifiedJsonDataFromLocalUser();

    bool isBeingControlledLocally = userRequest["isBeingControlled"];
    bool motorStateRequest = userRequest["state"];
    bool doNotifyLocalClients = false;

    while( isBeingControlledLocally ){

        doNotifyLocalClients = true;

        if( motorStateRequest ){
            motor_control( MOTOR_ON );
        } else {
            motor_control( MOTOR_OFF );
        }

        notifyLocalClients( false );
        toLoopFunctionsMultipleTimes();

        userRequest = deserializeStringifiedJsonDataFromLocalUser();

        isBeingControlledLocally = userRequest["isBeingControlled"];
        motorStateRequest = userRequest["state"];

        MOTOR_STATUS_CHANGED = false;
        tankObj.setIsChangedToFalse();
        sumpObj.setIsChangedToFalse();
    }

    // notifyLocalClients( doNotifyLocalClients );
    toLoopFunctionsMultipleTimes();

    motor_control( MOTOR_OFF );

}