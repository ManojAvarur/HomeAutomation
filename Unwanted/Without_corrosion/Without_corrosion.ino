void lowDigitalPin( int pin ){
    pinMode( pin, OUTPUT );
    digitalWrite( pin, LOW );
    pinMode( pin, INPUT );
    delay(200);
}



void setup(){
    Serial.begin(9600);

    pinMode(D0, OUTPUT);
    digitalWrite(D0, LOW);
    pinMode(D0, INPUT);

    pinMode(D1, OUTPUT);
    digitalWrite(D1, LOW);
    pinMode(D1, INPUT);

    pinMode(D2, OUTPUT);
    digitalWrite(D2, LOW);
    pinMode(D2, INPUT);

    pinMode(D6, OUTPUT);
}

void loop(){
    lowDigitalPin( D0 );
    if( digitalRead( D0 ) == 1 ){
        Serial.println("\nWater Level above low in tank");
    }

//    delay(2000);
    lowDigitalPin( D1 );
    if( digitalRead( D1 ) == 1 ){
        Serial.println("\nWater Level above mid in tank");
    }


    lowDigitalPin( D2 );
    if( digitalRead( D2 ) == 1 ){
        Serial.println("\nWater Level above High in tank");
        tone( D6, 2000, 1000 );
    }

//    lowDigitalPin( D3 );
//    if( digitalRead( D3 ) == 1 ){
//        Serial.println("\nWater Level above low in sump");
//    }
//
//    lowDigitalPin( D4 );
//    if( digitalRead( D4 ) == 1 ){
//        Serial.println("\nWater Level above mid in sump");
//    }

    delay(2000);
}
