unsigned long PERIOD = 5 * 1000L; // Every 5 Seconds
unsigned long TARGET_TIME = 0L;

void setup(){
    Serial.begin(9600);
}

void loop(){
    if( millis() - TARGET_TIME >= PERIOD ){
        TARGET_TIME += PERIOD;
        Serial.println("Current Millis is : { " + String( millis() ) + " }\n Taget time is : { "+ String( TARGET_TIME ) + " }" );
    }
}