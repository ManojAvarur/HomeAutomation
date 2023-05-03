void water_pump(){

    if( tankObj.waterLevelInTank() != 4 ){

        if ( sumpObj.waterLevelInSump() <= 0) {
            motor_control( MOTOR_OFF );
            debug_log("\nTank level low turning off the pump because low water in sump");
        } else if( sumpObj.waterLevelInSump() == 3 ){
            motor_control( MOTOR_ON );
            debug_log("\nTank level low turning on the pump");
        } else {
            debug_log("\nWater Level low in sump");
        }

    } else {
        motor_control( MOTOR_OFF );
        debug_log("\nTank level high turning off the pump");
    }

}