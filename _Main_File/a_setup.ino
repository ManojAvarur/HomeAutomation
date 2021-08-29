void setup(){
    Serial.begin(9600);

    // Setting Up Wifi
    setup_wifi();

    // Settings for Water Level Sensor
    pinMode(RELAY_1, OUTPUT);
    digitalWrite(RELAY_1, HIGH);

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