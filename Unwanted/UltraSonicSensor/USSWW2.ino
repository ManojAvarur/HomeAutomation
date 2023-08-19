// #define trigPin D1
// #define echoPin D3
// #define trigPin2 D5
// #define echoPin2 D7

// //define sound velocity in cm/uS
// #define SOUND_VELOCITY 0.034
// #define CM_TO_INCH 0.393701

// long duration;
// float distanceCm;
// float distanceInch;

// void setup() {
//     Serial.begin(19200); // Starts the serial communication
//     pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//     pinMode(echoPin, INPUT); // Sets the echoPin as an Input

//     pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
//     pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
// }

// void loop() {
//     getSensorData(trigPin, echoPin);
//     getSensorData(trigPin2, echoPin2);
//     delay(1000);
// }

// void getSensorData( int tp, int ep ){
//      // Clears the trigPin
//     digitalWrite(tp, LOW);
//     delayMicroseconds(2);
//     // Sets the tp on HIGH state for 10 micro seconds
//     digitalWrite(tp, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(tp, LOW);
    
//     // Reads the echoPin, returns the sound wave travel time in microseconds
//     duration = pulseIn(ep, HIGH);
    
//     // Calculate the distance
//     distanceCm = duration * SOUND_VELOCITY/2;
    
//     // Convert to inches
//     distanceInch = distanceCm * CM_TO_INCH;
    
//     // Prints the distance on the Serial Monitor
//     Serial.print("Distance (cm): ");
//     Serial.print(distanceCm);
//     Serial.print(" Distance (inch): ");
//     Serial.println(distanceInch);
// }