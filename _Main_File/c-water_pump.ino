void water_pump(){

    // If failed to load data from EEPROM -> Stop this function execution
    if( !TANK_AND_SUMP_LIMITS.dataLoadedFromMemory ){
        debug_log("\nTank and Sump data not loaded from memory");
        return;
    }

    // If tank level is high -> Turn motor off
    if( tankObj.waterLevelInTank() >= TANK_AND_SUMP_LIMITS.tankHigh ){
        motorController.turnOff();
        debug_log("\nTank level high turning off the pump");
        return;
    }

    // If tank level is less than high
    if ( sumpObj.waterLevelInSump() <= TANK_AND_SUMP_LIMITS.sumpLow ) {
        motorController.turnOff();
        debug_log("\nTank level low turning off the pump because low water in sump");
        return;
    } 
    
    // Turn motor back on only when water level in sump is above the risk buffer zone 
    if( sumpObj.waterLevelInSump() > TANK_AND_SUMP_LIMITS.sumpLow + TANK_AND_SUMP_LIMITS.motorSafeBuffer ){
        motorController.turnOn();
        debug_log("\nTank level low turning on the pump");
        return;
    } 
    
    motorController.turnOff();
    debug_log("\nWater Level low in sump");

}