// #include <EEPROM.h>

// int currentMemLocPointer = 0;

// void setup() {
//   Serial.begin(19200);

//   EEPROM.begin(512);

//   Serial.println("\n");

//   String dataToWrite = "Madhura~Network_Bridge~10.25~10.55~5.10~5.55~";

//   for( int i = 0; i < dataToWrite.length(); i++ ){

//     if( String( dataToWrite.charAt(i) ) == String("~") ){
//       // EEPROM.write( i, '\0');
//       Serial.println(":\n");
//       i++;
//       if( i >= dataToWrite.length() ){
//         break;
//       }
//     }

//     char charFromString = dataToWrite.charAt(i);

//     // EEPROM.write( i, charFromString );
//     Serial.print(charFromString);
//   }

// Serial.println("\n");
//   // EEPROM.commit();

// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   if( currentMemLocPointer <= 0 ){
//     fetchDataFromMemory();
//   }

// }

// void fetchDataFromMemory(){

    
  
//     for( uint8_t i = 1; i <= 6; i++ ){
    
//         String dataFromMemory = "";
//         int count = 0;

//         while( EEPROM.read( currentMemLocPointer ) != '\0' && count < 200 ){
//             dataFromMemory += char( EEPROM.read( currentMemLocPointer ) ); 
//             currentMemLocPointer++;
//             count++;
//         }

//         if( count >= 200 ){
//             Serial.println("\n\nFailed to fetch");
//             Serial.println("Data : " + String(dataFromMemory) + " || MEMINDEX : " + String(currentMemLocPointer) );
//             break;
//         }

//         Serial.println(" Index : " + String(i) + " || Value : " + dataFromMemory );

//         currentMemLocPointer++;
//     }
// }