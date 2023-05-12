// #include <ESP8266WiFi.h>
// #include <ESPAsyncTCP.h>
// #include <ESPAsyncWebServer.h>

// // Replace with your network credentials
// const char* ssid = "Madhura";
// const char* password = "Network_Bridge";

// // Create AsyncWebServer object on port 80
// AsyncWebServer server(80);
// AsyncWebSocket ws("/ws");

// const char index_html[] PROGMEM = R"rawliteral(
//     <!DOCTYPE HTML><html>
//     <head>
//       <title>ESP Web Server</title>
//     </head>
//     <body>
//       <h1>Current trending number : <span id='state'></span></h1>
//       //<input type='text'  onkeydown='toggle(event)' />
//     <script>
//       var gateway = `ws://${window.location.hostname}/ws`;
//       var websocket;
//       window.addEventListener('load', onLoad);
//       function initWebSocket() {
//         console.log('Trying to open a WebSocket connection...');
//         websocket = new WebSocket(gateway);
//         websocket.onopen    = onOpen;
//         websocket.onclose   = onClose;
//         websocket.onmessage = onMessage; // <-- add this line
//       }
//       function onOpen(event) {
//         console.log('Connection opened');
//       }
//       function onClose(event) {
//         console.log('Connection closed');
//         setTimeout(initWebSocket, 2000);
//       }
//       function onMessage(event) {
//         document.getElementById('state').innerHTML = event.data;
//       }
//       function onLoad(event) {
//         initWebSocket();
//       }
//       function initButton() {
//         document.getElementById('button').addEventListener('click', toggle);
//       }
//       function toggle( event ){
//         console.log( event.target.value );
//         if( event.target.value.length > 0 ){
//           websocket.send( event.target.value);
//         }
//       }
//     </script>
//     </body>
//     </html>
// ";)rawliteral";

// void notifyClients( char* data ) {
//   Serial.println("In notify all : " + String( data ) );
//   ws.textAll( data, strlen( data ) );
//   Serial.println("Notified all : " + String( data ) );
// }

// void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
//   AwsFrameInfo *info = (AwsFrameInfo*)arg;
//   if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
//     data[len] = 0;
//     char* dataConverted = (char*) data;
//     if( strlen( dataConverted ) > 1 ){
//       notifyClients( (char*)data );
//     }
//     Serial.println( strlen( dataConverted ) );
//   }
// }

// void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
//              void *arg, uint8_t *data, size_t len) {
//     switch (type) {
//       case WS_EVT_CONNECT:
//         Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
//         break;
//       case WS_EVT_DISCONNECT:
//         Serial.printf("WebSocket client #%u disconnected\n", client->id());
//         break;
//       case WS_EVT_DATA:
//         handleWebSocketMessage(arg, data, len);
//         break;
//       case WS_EVT_PONG:
//       case WS_EVT_ERROR:
//         break;
//   }
// }

// void initWebSocket() {
//   ws.onEvent(onEvent);
//   server.addHandler(&ws);
// }

// void setup(){
//   // Serial port for debugging purposes
//   Serial.begin(115200);
  
//   // Connect to Wi-Fi
//   WiFi.mode(WIFI_AP_STA);
//   WiFi.setAutoReconnect( false );

//   WiFi.begin( ssid, password );

//   while( WiFi.status() != WL_CONNECTED ){
//     Serial.print(".");
//     delay(1000);
//   }
//   // Soft AP
//   // WiFi.softAPConfig( IPAddress(192, 168, 0, 1), IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));
//   // WiFi.softAP("Test");  
//   // Serial.println( WiFi.softAPIP() );

//   // Print ESP Local IP Address
//   Serial.println(WiFi.localIP());

//   initWebSocket();

//   // Route for root / web page
//   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//     request->send_P(200, "text/html", index_html );
//   });

//   // Start server
//   server.begin();

//   ws.getClients();
// }

// void loop() {
//   ws.cleanupClients();
// }




