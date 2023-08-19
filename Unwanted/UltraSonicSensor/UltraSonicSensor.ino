// #define trigPin D1 // yellow
// #define echoPin D3 // green
// #define trigPin2 D5 // yellow
// #define echoPin2 D7 // green
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>
// #include <ESP8266WebServer.h>
// #include <WebSocketsServer.h>
// #include <DNSServer.h> 
// #include <Hash.h>
// #include "z-ultra_sonic_sensor.h"

// const char* ssid = "Madhura";
// const char* password = "Network_Bridge";

// WebSocketsServer webSocket = WebSocketsServer(81);
// ESP8266WebServer server(80);


// String WebPage(){
//   return R"(
//     <!DOCTYPE html>
//     <html>
//       <script>
//       var Socket; 
//       function start() { 
//         Socket = new WebSocket('ws://' + window.location.hostname + ':81/'); 
//         Socket.onmessage = function (evt) { 
//           console.log( evt.data );
//         document.querySelector('p').innerHTML = evt.data; 
//         } 
//       } 
//       </script>
//       <body onload='javascript:start();'>
//       <p></p>
//       </body>
//     </html>
//   )";
// }

// long duration;
// float distanceCm;
// float distanceInch;

// UltraSonicSensor *uss;// = new UltraSonicSensor( trigPin, echoPin );
// UltraSonicSensor *uss2;// = new UltraSonicSensor( trigPin, echoPin );

// void setup() {
//   	Serial.begin(19200); // Starts the serial communication

//   WiFi.mode( WIFI_AP_STA );
// 	WiFi.begin(ssid, password);

// 	uss = new UltraSonicSensor( trigPin, echoPin );
// 	uss2 = new UltraSonicSensor( trigPin2, echoPin2 );

// 	while (WiFi.status() != WL_CONNECTED) {
// 		delay(500);
// 		Serial.print(".");
// 	}

// 	Serial.println("");
// 	Serial.print("Connected to ");
// 	Serial.println(ssid);
// 	Serial.print("IP address: ");
// 	Serial.println(WiFi.localIP());
	

// 	server.on("/", [](){
// 		server.send(200, "text/html", WebPage() );
// 	});

// 	server.onNotFound( [](){ 
//         server.send(200, "text/html", WebPage() ); 
//     });

// 	server.begin();
	
// 	webSocket.begin();
// 	webSocket.onEvent(webSocketEvent);
// }

// void loop() {
// 	UltraSonicSensor *newData = uss->getCurrentValue();
// 	distanceCm = newData->inCentimeter();
// 	distanceInch = newData->inInches();


// 	String data = "Distance (cm): ";
// 	data += String( distanceCm );
// 	data += " &nbsp;&nbsp; Distance (inch): ";
// 	data += String(distanceInch);
  
//   Serial.println( "\n\n" +data );

//   newData = uss2->getCurrentValue();
// 	distanceCm = newData->inCentimeter();
// 	distanceInch = newData->inInches();

//   String data2 = "Distance (cm): ";
// 	data2 += String( distanceCm );
// 	data2 += " &nbsp;&nbsp; Distance (inch): ";
// 	data2 += String(distanceInch);

//   Serial.println( data2 );

//   data += "<br><br>" + data2;


// 	webSocket.broadcastTXT( data );

//   server.handleClient();
//   webSocket.loop();
// }


// void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
// 	char *textToBroadcast;
//    	if (type == WStype_TEXT){
// 		payload[length] = '\0';
// 		textToBroadcast = (char*)payload;
//     	Serial.println( textToBroadcast );
// 	}
// }