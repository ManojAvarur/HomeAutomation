#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "z-ArduinoJson-v6.18.5.h"

StaticJsonDocument<256> json_user_request;

unsigned long USER_REQUEST_CHECK_INTERVAL_TARGET_TIME= 0L;
int USER_REQUEST_CHECK_INTERVAL = 10000;


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
    check_requests_from_server();
    get_user_requests_from_server();
}


void check_requests_from_server(){

    if( ( millis() - USER_REQUEST_CHECK_INTERVAL_TARGET_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){
        USER_REQUEST_CHECK_INTERVAL_TARGET_TIME += USER_REQUEST_CHECK_INTERVAL;

        if( get_user_requests_from_server() ){

            USER_REQUEST_CHECK_INTERVAL = 5000;
            USER_REQUEST_CHECK_INTERVAL_TARGET_TIME = USER_REQUEST_CHECK_INTERVAL + millis();
            
            unsigned long counter = 0L;

            if( DEBUG_CODE ){
                Serial.println("\n\tInside user related operations umanual overide is set to true." );  
                Serial.println("\n\t\t pump_manual_overide_request : " + String( json_user_request["pump_manual_overide_request"].as<String>().toInt() ) );  
                Serial.println("\n\t\t pump_take_over_complete_control : " + String( json_user_request["pump_take_over_complete_control"].as<String>().toInt() ) );  
                Serial.println("\n\t\t pump_on_off_status : " + String( json_user_request["pump_on_off_status"].as<String>().toInt() ) );  
                Serial.println("\n\t\t time_in_hours : " + String( json_user_request["time_in_hours"].as<String>().toInt() ) );  
                Serial.println("\n\t\t execute_status : " + String( json_user_request["execute_status"].as<String>().toInt() ));  
//                Serial.print( json_user_request["execute_status"] );
                delay( DEBUG_DELAY_TIME );
            }


            while( json_user_request["pump_manual_overide_request"].as<String>().toInt() == 1  && json_user_request["execute_status"].as<String>().toInt() == 1 ){

                if( json_user_request["pump_take_over_complete_control"].as<String>().toInt() == 1 ) {
                    
                    Serial.println("\n\nInside Manual Overide Complete Control");
                    motor_control( ( json_user_request["pump_on_off_status"].as<String>().toInt() == 1 )? MOTOR_ON : MOTOR_OFF );
                    // update_server( ++counter );

                } else {

                    if( json_user_request["pump_on_off_status"].as<String>().toInt() == 0 && json_user_request["time_in_hours"].as<String>().toInt() >= 7 ){

                        water_pump();

                        if( DEBUG_CODE ){
                            Serial.println("\n\tInside manual overide and under water_pump() as it is grater than 7");  
                            delay( DEBUG_DELAY_TIME );
                        }

                    } else if( json_user_request["pump_on_off_status"].as<String>().toInt() == 1 ){

                        water_pump();

                        if( DEBUG_CODE ){
                            Serial.println("\n\tInside manual overide and under water_pump() as pump_on_off_status = 1");  
                            delay( DEBUG_DELAY_TIME );
                        }

                    } else {
                        motor_control( MOTOR_OFF );

                        if( DEBUG_CODE ){
                            Serial.println("\n\tInside manual overide and under water_pump() as pump_on_off_status =  0");  
                            delay( DEBUG_DELAY_TIME );
                        }
                    }

                }

                update_server( ++counter );

                if( ( millis() - USER_REQUEST_CHECK_INTERVAL_TARGET_TIME ) >= USER_REQUEST_CHECK_INTERVAL ){
                    USER_REQUEST_CHECK_INTERVAL_TARGET_TIME += USER_REQUEST_CHECK_INTERVAL;
                    if( ! get_user_requests_from_server() ){
                        break;
                    }
                }

            }

            USER_REQUEST_CHECK_INTERVAL = 30000;
            USER_REQUEST_CHECK_INTERVAL_TARGET_TIME = USER_REQUEST_CHECK_INTERVAL + millis();
            
        }
    }
}


bool get_user_requests_from_server(){
     
    int httpCode;
    int repeatCount = 5, count = 0;
    String result;
    String href = URL+"/get_user_requests.php?nodemcu_id=" + UNIQUE_ID;

    do{
        HTTPClient http;
        http.begin( client, href  );
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
        httpCode = http.GET();

        if( DEBUG_CODE ){
            Serial.println("\n\tInside user related operations. Checked after " + String( millis() - USER_REQUEST_CHECK_INTERVAL_TARGET_TIME ) );  
            Serial.println("\n\tInside get user request from server : "+href+". Responce Code : " + String( httpCode ) );  
            delay( DEBUG_DELAY_TIME );
        }
        
        if( httpCode == 404 ){
            http.end();
            return false;
        } else if( httpCode != 200 ){
            delay( 500 );
            count += 1;
        } else {
            result = http.getString();
        }

        http.end();

    } while( httpCode != 200 && count <= repeatCount );

    if( httpCode == 200 ){
        deserializeJson( json_user_request, result );
        return true;
    } else {
        return false;
    }
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
