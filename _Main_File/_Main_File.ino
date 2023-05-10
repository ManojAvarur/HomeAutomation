// ------------------ Main Declaration --------------
String URL = "http://iotproject.coolpage.biz/home_automation/handel_request/nodemcu";
//String URL = "http://192.168.2.2/HomeAutomation-website/handel_request/nodemcu";
String UNIQUE_ID = "4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c";

// ------------------ Wi-Fi Settings ------------------
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char* SSID = "POCO";
const char* PASSWORD = "123456789";
const char* AP_SSID = "HOMEATO Water Controller";
const char* AP_PASSWORD = "36066585767";


IPAddress local_ip( 192, 168, 0, 1 );
IPAddress gateway( 192, 168, 0, 1 );
IPAddress subnet( 255, 255, 255, 0 );

WiFiClient client;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

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
StaticJsonDocument<512> json_sensor_data_update;
StaticJsonDocument<384> json_user_request;

// ----------------- DEBUG CODE ---------------------
bool DEBUG_CODE = false;
int DEBUG_DELAY_TIME = 0; // 1 sec

bool DEBUG_CLASS_CODE = false;
int DEBUG_CLASS_DELAY_TIME = 0; // 1 sec


// ---------------- Execution Time Period -------------
// unsigned long PERIOD = 5 * 60 * 1000L; // Executes in every 5 mins
// int INITIAL_PUMP_LOAD_TIME = 5000; // 5 Sec

int USER_REQUEST_CHECK_INTERVAL = 30000;
unsigned long USER_REQUEST_CHECK_INTERVAL_ELAPSED_TIME = 0L;

int WIFI_RECONNECTION_INTERVAL = 10000;
unsigned long WIFI_RECONNECTION_INTERVAL_ELAPSED_TIME = 0L;

int TANK_SUMP_WATER_LEVEL_UPDATE_INTERVAL = 20000; 

// ------------------ Class Instantiation -------------

#include "z-sump_class.h"
#include "z-tank_class.h"

Sump sumpObj = Sump( WL_S_LOW, WL_S_MID, TANK_SUMP_WATER_LEVEL_UPDATE_INTERVAL, DEBUG_CLASS_CODE, DEBUG_CLASS_DELAY_TIME );
Tank tankObj = Tank( WL_T_LOW, WL_T_MID, WL_T_HIGH, TANK_SUMP_WATER_LEVEL_UPDATE_INTERVAL, DEBUG_CLASS_CODE, DEBUG_CLASS_DELAY_TIME );

// ------------------ Extras --------------------------
String DEBUG_LOG = "";
bool motor_status_changed = false;
bool wifi_ap_enabled = false;

// ---------------- Function Declaration -----------
void water_pump();
void motor_control( uint8_t value );
void update_server( int pump_manual_override_data );
void check_requests_from_server();
bool get_user_requests_from_server();
bool setup_wifi( short overall_wait_time, short delay_timer );
void control_wifi_ap( bool status );
void notifyClients();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
