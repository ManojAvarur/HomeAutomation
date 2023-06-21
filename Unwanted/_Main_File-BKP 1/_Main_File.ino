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
#include <ArduinoJson.h>
StaticJsonDocument<48> Json_result_responce;
StaticJsonDocument<96> User_request_check;
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
void motor_status( bool status, String from );
void start_process();
bool low_water_level_in_tank( String from );
bool mid_water_level_in_tank( String from );
bool high_water_level_in_tank( String from );
bool low_water_level_in_sump( String from );
bool mid_water_level_in_sump( String from );
