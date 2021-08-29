// ------------------ Main Declaration --------------
//String URL = "http://192.168.2.5/website/handel_requests";
String URL = "http://iotproject.coolpage.biz/home_automation";
String USER_ID = "0e7f970107b5e113284bbb706da47ba2";

// ------------------ Wi-Fi Settings ------------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* SSID = "";
const char* PASSWORD = "";
WiFiClient client;

// ------------------ Relay Sensor Settings -----------
#define RELAY_1 D7 // For Water Pump

// ------------------ Water Level Sensor Settings ------
// For Tank
#define WL_T_LOW D0 // LOW
#define WL_T_MID D3 // LOW
#define WL_T_HIGH D5 // HIGH

// For Sump
#define WL_S_LOW D8

// ----------------- Json Libraies Settings ------------
#include <ArduinoJson.h>
StaticJsonDocument<48> Json_result_responce;
StaticJsonDocument<96> User_request_check;
// StaticJsonDocument<192> DB_update;
// StaticJsonDocument<768> TimeStamp;

// ----------------- DEBUG CODE ---------------------
int DEBUG_CODE = 0;
int DEBUG_DELAY_TIME = 1000; // 1 sec

// _________________ Function Declaration -----------
void setup_wifi();