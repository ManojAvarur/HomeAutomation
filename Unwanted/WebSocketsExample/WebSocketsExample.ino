#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <DNSServer.h> 
#include <Hash.h>

const char* ssid = "Madhura";
const char* password = "Network_Bridge";

String WebPage = "\
	<!DOCTYPE html>\
	<html>\
	<style>\
		input[type='text'] {\
			width: 90%;\
			height: 3vh;\
		}\
		input[type='button'] {\
			width: 9%;\
			height: 3.6vh;\
		}\
		.rxd {\
			height: 90vh;\
		}\
		textarea {\
			width: 99%;\
			height: 100%;\
			resize: none;\
		}\
	</style>\
	<script>\
		var Socket; \
		function start() { \
			Socket = new WebSocket('ws://' + window.location.hostname + ':81/'); \
			Socket.onmessage = function (evt) { \
				document.getElementById('rxConsole').value += evt.data; \
			} \
		} \
		\
		function enterpressed(){ \
			Socket.send(document.getElementById('txbuff').value); \
			document.getElementById('txbuff').value = ''; \
		}\
	</script>\
	<body onload='javascript:start();'>\
		<div>\
			<input class='txd' type='text' id='txbuff' onkeydown='if(event.keyCode==13) enterpressed();'>\
			<input class='txd' type='button' onclick='enterpressed();' value='Send'> </div><br>\
		<div class='rxd'> \
			<textarea id='rxConsole' readonly></textarea> \
		</div>\
	</body>\
</html>\
";

WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);
DNSServer dnsServer; 
IPAddress APIP(192, 168, 0, 1);

void setup() {
	Serial.begin(19200);

	WiFi.mode(WIFI_AP_STA);
	WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  	dnsServer.start( 53, "*", APIP); // DNS spoofing (Only for HTTP)

	WiFi.softAP("Test");
	WiFi.begin(ssid, password);
	Serial.println("");

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
		
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	
	server.on("/", [](){
		server.send(200, "text/html", WebPage);
	});

	server.onNotFound( [](){ 
        server.send(200, "text/html", WebPage ); 
    });
	
	server.begin();
	
	webSocket.begin();
	webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
    dnsServer.processNextRequest(); 
    server.handleClient();
    if (Serial.available() > 0){
      char c[] = {(char)Serial.read()};
      webSocket.broadcastTXT(c, sizeof(c));
    }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
	char *textToBroadcast;
   	if (type == WStype_TEXT){
		payload[length] = '\0';
		textToBroadcast = (char*)payload;
		webSocket.broadcastTXT( textToBroadcast, strlen( textToBroadcast ) );
	}
}
