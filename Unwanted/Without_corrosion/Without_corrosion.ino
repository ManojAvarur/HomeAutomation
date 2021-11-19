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





// void setup(){
//     Serial.begin(9600);

//     pinMode(D0, OUTPUT);
//     digitalWrite(D0, LOW);
//     pinMode(D0, INPUT);

//     pinMode(D1, OUTPUT);
//     digitalWrite(D1, LOW);
//     pinMode(D1, INPUT);

//     pinMode(D2, OUTPUT);
//     digitalWrite(D2, LOW);
//     pinMode(D2, INPUT);



//     // pinMode(D5, OUTPUT);
// }

// void loop(){
//     if( digitalRead( D0 ) == 1 ){
//         Serial.println("\nWater Level above low");
// //        tone( D5, 0 );
//         // tone( D5, 2000, 1000);
// //        tone( D5, 0 );

//         pinMode(D0, OUTPUT);
//         digitalWrite(D0, LOW);
//         pinMode(D0, INPUT);
//     }

// //    delay(2000);

//     if( digitalRead( D1 ) == 1 ){
//         Serial.println("\nWater Level above mid");
// //        tone( D5, 0 );
//         // tone( D5, 3000, 1000 );
// //        tone( D5, 1000 );
// //        tone( D5, 0 );

//         pinMode(D1, OUTPUT);
//         digitalWrite(D1, LOW);
//         pinMode(D1, INPUT);
//     }


//     if( digitalRead( D2 ) == 1 ){
//         Serial.println("\nWater Level above High");
// //        tone( D5, 0 );
//         // tone( D5, 3000, 1000 );
// //        tone( D5, 1000 );
// //        tone( D5, 0 );

//         pinMode(D2, OUTPUT);
//         digitalWrite(D2, LOW);
//         pinMode(D2, INPUT);
//     }

//     delay(2000);
// }
















void setup(){
    Serial.begin(9600);

    pinMode(D0, OUTPUT);
    // digitalWrite(D0, LOW);
    // pinMode(D0, INPUT);

    pinMode(D1, OUTPUT);
    // digitalWrite(D1, LOW);
    // pinMode(D1, INPUT);

    pinMode(D2, OUTPUT);

    pinMode( D3, OUTPUT );
    digitalWrite( D3, LOW );
    pinMode( D3, INPUT );
    Serial.println( "D3 value after low in low : " + String( digitalRead( D3 ) ) );
}

void loop(){

    digitalWrite(D0, HIGH);

    if( digitalRead( D3 ) == 1 ){
        Serial.println("\nWater Level above low");

        digitalWrite(D0, LOW);

        pinMode( D3, OUTPUT );
        digitalWrite( D3, LOW );
        pinMode( D3, INPUT );
        Serial.println( "D3 value after low in low : " + String( digitalRead( D3 ) ) );
        // pinMode(D0, INPUT);
    }


    digitalWrite(D1, HIGH);

    if( digitalRead( D3 ) == 1 ){
        Serial.println("\nWater Level above mid");

        digitalWrite(D1, LOW);

        pinMode( D3, OUTPUT );
        digitalWrite( D3, LOW );
        pinMode( D3, INPUT );
        Serial.println( "D3 value after low in mid : " + String( digitalRead( D3 ) ) );
    }


    digitalWrite(D2, HIGH);

    if( digitalRead( D3 ) == 1 ){
        Serial.println("\nWater Level above High");

        digitalWrite(D2, LOW);

        pinMode( D3, OUTPUT );
        digitalWrite( D3, LOW );
        pinMode( D3, INPUT );
        Serial.println( "D3 value after low in high : " + String( digitalRead( D3 ) ) );
    }

    delay(2000);
}
