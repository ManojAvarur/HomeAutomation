// ------------------ Main Declaration --------------
String URL = "http://iotproject.coolpage.biz/home_automation";
String UNIQUE_ID = "4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c";

// ------------------ Wi-Fi Settings ------------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* SSID = "";
const char* PASSWORD = "";
WiFiClient client;

// ------------------ Relay Sensor Settings -----------
#define RELAY_1 D7 // For Water Pump
#define MOTOR_ON LOW // Turing on the pump / relay
#define MOTOR_OFF HIGH // Turing off the pump / relay

// ------------------ Water Level Sensor Settings ------
// For Tank
#define WL_T_LOW D0 // LOW
#define WL_T_MID D1 // MID
#define WL_T_HIGH D2 // HIGH

// For Sump
#define WL_S_LOW D5 // LOW
#define WL_S_MID D6 // MID

// ----------------- Json Libraies Settings ------------
#include "z-ArduinoJson-v6.18.5.h"
StaticJsonDocument<48> Json_result_responce;
StaticJsonDocument<96> User_request_check;
// StaticJsonDocument<192> DB_update;
// StaticJsonDocument<768> TimeStamp;

// ----------------- DEBUG CODE ---------------------
bool DEBUG_CODE = true;
int DEBUG_DELAY_TIME = 0; // 1 sec

// ---------------- Execution Time Period -------------
unsigned long PERIOD = 5 * 60 * 1000L; // Executes in every 5 mins
int INITIAL_PUMP_LOAD_TIME = 5000; // 5 Sec
unsigned long UPDATE_INTERVAL_TIME = 5 * 1000L;
unsigned long TARGET_TIME = 0L; 

// ------------------ Class Instantiation -------------

#include "z-sump_class.h"
#include "z-tank_class.h"

Sump sumpObj = Sump( WL_S_LOW, WL_S_MID, DEBUG_CODE, DEBUG_DELAY_TIME );
Tank tankObj = Tank( WL_T_LOW, WL_T_MID, WL_T_HIGH, DEBUG_CODE, DEBUG_DELAY_TIME );

// ------------------ Extras --------------------------

// ---------------- Function Declaration -----------
void water_pump();
void motor_control( uint8_t value );
void update_server();
void setup_wifi();