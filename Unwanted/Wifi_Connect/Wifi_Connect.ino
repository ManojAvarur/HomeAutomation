#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

const char* SSID = "Madhura";
const char* PASSWORD = "Network_Bridge";
WiFiClient client;

bool setup_wifi();

void setup(){
    setup_wifi();
}

void loop(){
    HTTPClient http;

    String data = "http://192.168.2.3/HomeAutomation/test.php";
                        
    http.begin(client, data);
    http.addHeader("Content-Type", "multipart/form-data;");
    
    int httpCode = http.GET();
    
    http.end();

    Serial.println("Responce Code : " + String( httpCode ) );  
    Serial.println( data );

    delay(1000);
}

bool setup_wifi(){
   short while_counter = 0;
   short overall_wait_time = 5; //secs
   WiFi.begin(SSID, PASSWORD);
   Serial.println("Connecting");
   while( ( WiFi.status() != WL_CONNECTED ) && ( while_counter <= overall_wait_time )) {
       Serial.print(".");
       while_counter++;
       delay(1000);
   }
   Serial.println("");
   Serial.print("Connected to WiFi network with IP Address: ");
   Serial.println(WiFi.localIP());
   
   if( WiFi.status() != WL_CONNECTED ){
       return true;
   } else {
       return false;
   }
}
