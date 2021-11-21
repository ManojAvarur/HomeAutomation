// ------------------ Main Declaration --------------
//String URL = "http://192.168.2.5/website/handel_requests";
String URL = "http://iotproject.coolpage.biz/home_automation";
String USER_ID = "0e7f970107b5e113284bbb706da47ba2";

int INITIAL_PUMP_LOAD_TIME = 5000; // 5 Sec

// ------------------ Wi-Fi Settings ------------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* SSID = "";
const char* PASSWORD = "";
WiFiClient client;

// ------------------ Relay Sensor Settings -----------
#define RELAY_1 D6 // For Water Pump
#define MOTOR_ON HIGH // Turing on the pump / relay
#define MOTOR_OFF LOW // Turing off the pump / relay

// ------------------ Water Level Sensor Settings ------
// For Tank
#define WL_T_LOW D0 // LOW
#define WL_T_MID D3 // MID
#define WL_T_HIGH D5 // HIGH

// For Sump
#define WL_S_LOW D8
#define WL_S_MID D7

// ----------------- Json Libraies Settings ------------
//#include <ArduinoJson.h>
//StaticJsonDocument<48> Json_result_responce;
//StaticJsonDocument<96> User_request_check;
// StaticJsonDocument<192> DB_update;
// StaticJsonDocument<768> TimeStamp;

// ----------------- DEBUG CODE ---------------------
bool DEBUG_CODE = false;
int DEBUG_DELAY_TIME = 5000; // 1 sec

// ---------------- Execution Time Period -------------
unsigned long PERIOD = 5 * 60 * 1000L; // Executes in every 5 mins
unsigned long TARGET_TIME = 0L;

// _________________ Function Declaration -----------
void setup_wifi();
void  highDigitalPin( int pin, bool changeToInput, bool delayRequired );
void lowDigitalPin( int pin, bool changeToInput, bool delayRequired );


class Sump{
    private:
        short waterStatus = -1;

        void updateSumpDetails( bool updateFromStart = false ){

            int tempWaterLevelInSump = waterStatus;
            bool caseBreakCheck = true;

            if( tempWaterLevelInSump == -1 || tempWaterLevelInSump > 1 || updateFromStart ){
                tempWaterLevelInSump = 0;
            }

            switch( tempWaterLevelInSump ){

            case 0 :
                lowDigitalPin( WL_S_LOW, true, true );
                if( digitalRead( WL_S_LOW ) == 1 ){

                    lowDigitalPin( WL_S_LOW, true, true );
                    if( digitalRead( WL_S_LOW ) == 1 ){
                        Serial.println("\nWater Level above low in sump");
                        waterStatus = 1;
                        highDigitalPin( WL_S_LOW );
                        caseBreakCheck = false;
                    } else {
                        waterStatus = -1;
                    }
                } else {
                    waterStatus = -1;
                }
                
                if( caseBreakCheck ){
                        break;
                }

            case 1:
                lowDigitalPin( WL_S_MID, true, true );
                if( digitalRead( WL_S_MID ) == 1 ){

                    lowDigitalPin( WL_S_MID, true, true );
                    if( digitalRead( WL_S_MID ) == 1 ){
                        Serial.println("\nWater Level above mid in sump");
                        waterStatus = 2;
                        highDigitalPin( WL_S_MID );
                    } else {
                        waterStatus = -1;
                    }

                } else {
                    waterStatus = -1;
                }

            break;

            default:
                waterStatus = -1;
                highDigitalPin( WL_S_LOW );
                highDigitalPin( WL_S_MID );
                break;
            }
        } 

    public:
        int waterLevelInSump( bool updateFromStart = false ){
            updateSumpDetails( updateFromStart );
            return waterStatus;
        }
};

// ------------------ Class Instantiation -------------
Sump sumpObj;
