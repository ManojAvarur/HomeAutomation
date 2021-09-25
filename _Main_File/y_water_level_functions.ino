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

bool low_water_level_in_sump( String from ){
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

bool mid_water_level_in_sump( String from ){
    if( DEBUG_CODE ){
        Serial.print("\nDEBUG CODE ENABLED : \n\tlow_water_level_in_tank called from ' " + from + " '\n\n");
        Serial.print("\tLOW = " + String( digitalRead( WL_S_MID ) ) );
        delay( DEBUG_DELAY_TIME );
    }

    if( digitalRead( WL_S_MID ) == 0 ){
        return false;
    }

    if( digitalRead( WL_S_MID ) == 1 ){
        pinMode( WL_S_MID, OUTPUT);
        digitalWrite( WL_S_MID, LOW);
        pinMode( WL_S_MID, INPUT);
        if( digitalRead( WL_S_MID ) == 1 ){
            return true;
        }
    }
}
