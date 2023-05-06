#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DNSServer.h> 
#include <ESP8266WebServer.h>


DNSServer dnsServer; 
IPAddress APIP(192, 168, 0, 1);

ESP8266WebServer webServer(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

void setup() {
  // Serial begin
  Serial.begin(115200);
  
  
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));

  WiFi.softAP("Test");  

  // Start webserver
  dnsServer.start( 53, "*", APIP); // DNS spoofing (Only for HTTP)
  webServer.on( "/post", [](){ 
    webServer.send( 200, "text/html", "Hello World"); 
  });
  webServer.onNotFound( []() { webServer.send(200, "text/html", "Hello Worldsssssssssss" ); } );
  webServer.begin();

  // Enable the built-in LED
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
}

void loop() {
  dnsServer.processNextRequest(); 
  webServer.handleClient(); 
  webServer.close()
}