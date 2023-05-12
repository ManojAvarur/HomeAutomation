// #include <ESP8266WiFi.h>
// #include <ESPAsyncTCP.h>
// #include <DNSServer.h> 
// #include <ESP8266WebServer.h>

// ESP8266WebServer webServer(80);
// DNSServer dnsServer; 
// IPAddress APIP(192, 168, 0, 1);


// void setup(){    
//     Serial.begin(115200);

//     // WiFi.begin("Madhura", "Network_Bridge");

//     //  while( WiFi.status() != WL_CONNECTED ){
//     //     Serial.print(".");
//     //     delay(1000);
//     // }

//     WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));

//     WiFi.softAP("Test");

//     dnsServer.start( 53, "*", APIP); // DNS spoofing (Only for HTTP)


//     Serial.println(WiFi.localIP());
//     webServer.on( "/post", [](){ 
//         webServer.send( 200, "text/html", "Hello World"); 
//     });

//     webServer.onNotFound( [](){ 
//         webServer.send(200, "text/html", "Hello Worldsssssssssss" ); 
//     });

//     webServer.begin();
// }

// void loop(){
//     dnsServer.processNextRequest(); 

//     webServer.handleClient(); 
// }