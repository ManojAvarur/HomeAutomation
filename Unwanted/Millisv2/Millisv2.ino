#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "z-ArduinoJson-v6.18.5.h"

StaticJsonDocument<512> json_sensor_data_update;
StaticJsonDocument<256> json_user_request;


String URL = "http://192.168.2.3/HomeAutomation-website/handel_request/nodemcu";
String UNIQUE_ID = "4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c";

const char* SSID = "Manoj";
const char* PASSWORD = "Hazelnut+-";
WiFiClient client;


void setup(){
    Serial.begin( 9600 );
    setup_wifi();    
}

void loop(){
    int httpCode;
    int repeatCount = 5, count = 0;
    String result;

    do{
        HTTPClient http;
        http.begin(client, URL+"/get_user_requests.php?nodemcu_id=" + UNIQUE_ID );
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
        httpCode = http.GET();

        

        Serial.println("Inside Send update server. Responce Code : " + String( httpCode ) );  
    
        if( httpCode == 404 ){
            Serial.println("\n\n404");
        } else if( httpCode != 200 ){
            delay( 500 );
            count += 1;
        } else {
            result = http.getString();
        }

        http.end();

    } while( httpCode != 200 && count <= repeatCount );
    

    deserializeJson( json_user_request, result );

    Serial.println("\n\n Result : " + result  );
    delay(5000);
}

void setup_wifi(){
   short while_counter = 0;
   short overall_wait_time = 10; //secs
   WiFi.begin(SSID, PASSWORD);
   Serial.println("Connecting");
   
   while( ( WiFi.status() != WL_CONNECTED ) && ( while_counter <= overall_wait_time )) {
       Serial.print(".");
       while_counter++;
       delay(1000);
   }

   if( WiFi.status() == WL_CONNECTED ){
        Serial.println("");
        Serial.print("Connected to WiFi network with IP Address: ");
        Serial.println(WiFi.localIP());
   }
   
}
