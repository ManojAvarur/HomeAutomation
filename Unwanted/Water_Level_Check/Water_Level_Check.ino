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

// ----------------------------------------------------------------------------------------------------------

// class sumpDetails{
//     private:
//         bool isWaterLevelAboveLow;
//         bool isWaterLevelAboveMid;

//     public:
//         sumpDetails( int lowLevel, int midLevel ){
//             if( lowLevel != NULL ){
//                 this->isWaterLevelAboveLow = ( lowLevel )? true : false;
//             }

//             if( midLevel != NULL ){
//                 this->isWaterLevelAboveMid = ( midLevel )? true : false;
//             }
//         }

//         void updateSumpDetails(){

//         }

//         int waterLevelInSump(){
//             if( this->isWaterLevelAboveMid ){
//                 return 2;
//             } else if ( this->isWaterLevelAboveLow ){
//                 return 1;
//             } else {
//                 return 0;
//             }
//         }
// };

// class tankDetails{
//     private:
//         bool isWaterLevelAboveLow;
//         bool isWaterLevelAboveMid;
//         bool isWaterLevelAboveHigh;

//     public:
//         tankDetails( int lowLevel; int midLevel; int highLevel ){
//             if( lowLevel != NULL ){
//                 this->isWaterLevelAboveLow = ( lowLevel )? true : false;
//             }

//             if( midLevel != NULL ){
//                 this->isWaterLevelAboveMid = ( midLevel )? true : false;
//             }

//             if( highLevel != NULL ){
//                 this->isWaterLevelAboveHigh = ( highLevel )? true : false;
//             }
//         }

//         int waterLevelInTank(){
//             if( this->isWaterLevelAboveHigh ){
//                 return 3;
//             }else if( this->isWaterLevelAboveMid ){
//                 return 2;
//             } else if ( this->isWaterLevelAboveLow ){
//                 return 1;
//             } else {
//                 return 0;
//             }
//         }
// };

// void setup(){
  
// }

// void loop(){
  
// }


// ----------------------------------------------------------------------------------------------------------



// void lowDigitalPin( int pin ){
//     pinMode( pin, OUTPUT );
//     digitalWrite( pin, LOW );
//     pinMode( pin, INPUT );
//     delay(200);
// }



// void setup(){
//     Serial.begin(9600);

//     pinMode(D0, OUTPUT);
//     digitalWrite(D0, LOW);
//     pinMode(D0, INPUT);

//     pinMode(D1, OUTPUT);
//     digitalWrite(D1, LOW);
//     pinMode(D1, INPUT);

//     // pinMode(D2, OUTPUT);
//     // digitalWrite(D2, LOW);
//     // pinMode(D2, INPUT);



//     // pinMode(D5, OUTPUT);
// }

// void loop(){
//     lowDigitalPin( D0 );
//     if( digitalRead( D0 ) == 1 ){
//         Serial.println("\nWater Level above low");
// //        tone( D5, 0 );
//         // tone( D5, 2000, 1000);
// //        tone( D5, 0 );

//         // pinMode(D0, OUTPUT);
//         // digitalWrite(D0, LOW);
//         // pinMode(D0, INPUT);
//     }

// //    delay(2000);
//     lowDigitalPin( D1 );
//     if( digitalRead( D1 ) == 1 ){
//         Serial.println("\nWater Level above mid");
// //        tone( D5, 0 );
//         // tone( D5, 3000, 1000 );
// //        tone( D5, 1000 );
// //        tone( D5, 0 );

//         // pinMode(D1, OUTPUT);
//         // digitalWrite(D1, LOW);
//         // pinMode(D1, INPUT);
//     }


//     lowDigitalPin( D2 );
//     if( digitalRead( D2 ) == 1 ){
//         Serial.println("\nWater Level above High");
// //        tone( D5, 0 );
//         // tone( D5, 3000, 1000 );
// //        tone( D5, 1000 );
// //        tone( D5, 0 );

//         // pinMode(D2, OUTPUT);
//         // digitalWrite(D2, LOW);
//         // pinMode(D2, INPUT);
//     }

//     delay(2000);
// }

