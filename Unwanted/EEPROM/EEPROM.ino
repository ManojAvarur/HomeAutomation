// #include <EEPROM.h>


// void setup(){

//     Serial.begin(19200); // Starts the serial communication

//     String word = "Hello World!";

//     EEPROM.begin(512);


//     // EEPROM.get( 0, data ); 

   


//     // Serial.println( EEPROM.read(0) );

//     for( int i = 0; i < word.length(); i++ ){
//         EEPROM.write(i, word[i]);
//     }

//     EEPROM.write( word.length(), '\0');

//     EEPROM.commit();
// }

// void loop(){

//     String data = "";
//     for( int i = 0; EEPROM.read(i) != '\0'; i++ ){
//         data += char(EEPROM.read(i)); 
//     }

//     Serial.println( data );

//     delay(5000);

// //   Serial.println( "@ " + String( i ) + " : " + String( EEPROM.read( i ) ) );
// //   i++;
//   // delay(1000);
// }