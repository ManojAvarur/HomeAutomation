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
#define WL_T_MID D1 // MID
#define WL_T_HIGH D2 // HIGH

// For Sump
#define WL_S_LOW D5 // LOW
#define WL_S_MID D6 // MID

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
void water_pump();

// ------------------ Class Instantiation -------------

#include "z-sump_class.h"
#include "z-tank_class.h"

Sump sumpObj = Sump( WL_S_LOW, WL_S_MID );
Tank tankObj = Tank( WL_T_LOW, WL_T_MID, WL_T_HIGH );
