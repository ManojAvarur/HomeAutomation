void fetchDataFromMemory(){

    int currentMemLocPointer = EEPROM_DATA_START_LOC;
  
    for( uint8_t i = 1; i <= 6; i++ ){
    
        String dataFromMemory = "";
        int count = 0;

        while( EEPROM.read( currentMemLocPointer ) != '\0' && count < 200 ){
            dataFromMemory += char( EEPROM.read( currentMemLocPointer ) ); 
            currentMemLocPointer++;
            count++;
        }

        Serial.println(" Index : " + String(i) + " || Value : " + dataFromMemory );

        if( count >= 200 ){
            break;
        }

        switch(i){
            case 1: {
                SSID = dataFromMemory;
                break;
            }

            case 2: {
                PASSWORD = dataFromMemory;
                break;    
            }

            case 3: {
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.tankLow = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.tankLow = limitValue;
                break;
            }

            case 4: {
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.tankHigh = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.tankHigh = limitValue;
                break;
            }

            case 5: {
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.sumpLow = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.sumpLow = limitValue;
                break;
            }

            case 6: {
                float limitValue = dataFromMemory.toFloat();
                TANK_AND_SUMP_LIMITS.sumpHigh = limitValue;
                TANK_AND_SUMP_LIMITS_OLD.sumpHigh = limitValue;
                break;
            }
        }

        currentMemLocPointer++;
    }
}