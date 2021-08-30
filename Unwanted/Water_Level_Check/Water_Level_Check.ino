// For Tank
#define WL_T_LOW D0 // LOW
#define WL_T_MID D2  // MID
#define WL_T_HIGH D5 // HIGH

// For Sump
#define WL_S_LOW D8

bool low_water_level_in_tank( String from );
bool mid_water_level_in_tank( String from );
bool high_water_level_in_tank( String from );

void setup(){
     Serial.begin(9600);

    // For Tank
    // Setting Initial Value ( 0 ) to WL_T_LOW
    pinMode(WL_T_LOW, OUTPUT);
    digitalWrite(WL_T_LOW, LOW);
    pinMode(WL_T_LOW, INPUT);

    // Setting Initial Value ( 0 ) to WL_T_MID
    pinMode(WL_T_MID, OUTPUT);
    digitalWrite(WL_T_MID, LOW);
    pinMode(WL_T_MID, INPUT);

    // Setting Initial Value ( 0 ) to WL_T_HIGH
    pinMode(WL_T_HIGH, OUTPUT);
    digitalWrite(WL_T_HIGH, LOW);
    pinMode(WL_T_HIGH, INPUT);

    // For Sump
    // Setting Initial Value ( 0 ) to WL_S_LOW
    pinMode(WL_S_LOW, OUTPUT);
    digitalWrite(WL_S_LOW, LOW);
    pinMode(WL_S_LOW, INPUT);
}

void loop(){
    if( DEBUG_CODE ){
      Serial.print("\n------------------------------------------------------\n");
    }
  
    if( low_water_level_in_tank("loop") ){
        Serial.println("\nWater Level Low!");
    } 
    if( mid_water_level_in_tank("loop") ){
        Serial.println("\nWater Level Mid!");
    }
    if( high_water_level_in_tank("loop") ){
        Serial.println("\nWater Level High!");
    }

    delay(3000);
}

bool low_water_level_in_tank( String from ){
    if( DEBUG_CODE ){
        Serial.print("\nDEBUG CODE ENABLED : \n\tlow_water_level_in_tank called from ' " + from + " '\n\n");
        Serial.print("\tLOW = " + String( digitalRead( WL_T_LOW ) ) );
        delay( DEBUG_DELAY_TIME );
    }

    if( digitalRead( WL_T_LOW ) == 0 ){
        return true;
    }

    if( digitalRead( WL_T_LOW ) == 1 ){
        pinMode(WL_T_LOW, OUTPUT);
        digitalWrite(WL_T_LOW, LOW);
        pinMode(WL_T_LOW, INPUT);
        if( digitalRead( WL_T_LOW ) == 1 ){
            return false;
        }
    }
}

bool mid_water_level_in_tank( String from ){
    if( DEBUG_CODE ){
        Serial.print("\nDEBUG CODE ENABLED : \n\tmid_water_level_in_tank called from ' " + from + " '\n\n");
        Serial.print("\tMID = " + String( digitalRead( WL_T_MID ) ) );
        delay( DEBUG_DELAY_TIME );
    }

    if( digitalRead( WL_T_MID ) == 0 ){
        return false;
    }

    if( digitalRead( WL_T_MID ) == 1 ){
        pinMode(WL_T_MID, OUTPUT);
        digitalWrite(WL_T_MID, LOW);
        pinMode(WL_T_MID, INPUT);
        if( digitalRead( WL_T_MID ) == 1 ){
            return true;
        }
    }
}

bool high_water_level_in_tank( String from ){
    if( DEBUG_CODE ){
        Serial.print("\nDEBUG CODE ENABLED : \n\thigh_water_level_in_tank called from ' " + from + " '\n\n");
        Serial.print("\tHIGH = " + String( digitalRead( WL_T_HIGH ) ) );
        delay( DEBUG_DELAY_TIME );
    }

    if( digitalRead( WL_T_HIGH ) == 0 ){
        return false;
    }

    if( digitalRead( WL_T_HIGH ) == 1 ){
        pinMode(WL_T_HIGH, OUTPUT);
        digitalWrite(WL_T_HIGH, LOW);
        pinMode(WL_T_HIGH, INPUT);
        if( digitalRead( WL_T_HIGH ) == 1 ){
            return true ;
        }
    }
}
