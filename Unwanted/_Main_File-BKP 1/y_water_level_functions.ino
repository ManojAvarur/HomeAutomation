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

bool mid_water_level_in_sump( String from ){

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

int water_level_in_tank( String from ){
    if( DEBUG_CODE ){
        Serial.print("\nDEBUG CODE ENABLED : \n\twater_level_in_tank called from ' " + from + " '\n\n");
        // Serial.print("\tLOW = " + String( digitalRead( WL_S_MID ) ) );
        delay( DEBUG_DELAY_TIME );
    }

    if( high_water_level_in_tank("water_level_tank_in_tank") ){
        return 2;
    } else if( mid_water_level_in_tank("water_level_tank_in_tank") ){
        return 1;
    } else {
        return 0;
    }
}

int water_level_in_sump( String from ){
    if( DEBUG_CODE ){
        Serial.print("\nDEBUG CODE ENABLED : \n\twater_level_in_sump called from ' " + from + " '\n\n");
        // Serial.print("\tLOW = " + String( digitalRead( WL_S_MID ) ) );
        delay( DEBUG_DELAY_TIME );
    }

    if( mid_water_level_in_sump("water_level_in_sump") ){
        return 1;
    } else {
        return 0;
    }
}