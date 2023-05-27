#define trigPin D5
#define echoPin D6
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <DNSServer.h> 
#include <Hash.h>

const char* ssid = "Madhura";
const char* password = "Network_Bridge";

WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);


String WebPage(){
  return R"(
    <!DOCTYPE html>
    <html>
      <script>
      var Socket; 
      function start() { 
        Socket = new WebSocket('ws://' + window.location.hostname + ':81/'); 
        Socket.onmessage = function (evt) { 
          console.log( evt.data );
        document.querySelector('p').innerHTML = evt.data; 
        } 
      } 
      </script>
      <body onload='javascript:start();'>
      <p></p>
      </body>
    </html>
  )";
}

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  	// Serial.begin(19200); // Starts the serial communication


	WiFi.begin(ssid, password);

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
		server.send(200, "text/html", WebPage() );
	});

	server.onNotFound( [](){ 
        server.send(200, "text/html", WebPage() ); 
    });

	server.begin();
	
	webSocket.begin();
	webSocket.onEvent(webSocketEvent);


	pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
	// Clears the trigPin
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(echoPin, HIGH);
	
	// Calculate the distance
	distanceCm = duration * SOUND_VELOCITY/2;
	
	// Convert to inches
	distanceInch = distanceCm * CM_TO_INCH;
	
	// Prints the distance on the Serial Monitor
	String data = "Distance (cm): ";
	data += String( distanceCm );
	data += "&nbsp;&nbsp;Distance (inch): ";
	data += String(distanceInch);
  
  Serial.println( data );
	webSocket.broadcastTXT( data );

  server.handleClient();
  webSocket.loop();


  	delay(500);
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
	char *textToBroadcast;
   	if (type == WStype_TEXT){
		payload[length] = '\0';
		textToBroadcast = (char*)payload;
    	Serial.println( textToBroadcast );
	}
}