void loop(){
    Serial.println("\n\n\t---------------------------------------------");
    Serial.println("\n\tSump : ");
    switch( sumpObj.waterLevelInSump() ){
        case 0:
            Serial.println("\tWater Level Low");
            break;
        case 1:
            Serial.println("\tWater Level Above Low");
            break;
        case 2:
            Serial.println("\tWater level above mid");
            break;
    }

    Serial.println("\n\n\tTank : ");
    switch( tankObj.waterLevelInTank() ){
        case 0:
            Serial.println("\tWater Level Low : " + String( digitalRead( WL_T_LOW ) ) );
            break;
        case 1:
            Serial.println("\tWater Level Above Low : " + String( digitalRead( WL_T_LOW ) ));
            break;
        case 2:
            Serial.println("\tWater level above mid : " + String( digitalRead( WL_T_MID ) ));
            break;
        case 3:
            Serial.println("\tWater level above High : " + String( digitalRead( WL_T_HIGH ) ));
            break;
    }

    delay(2000);
}
