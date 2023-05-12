void setup(){
    Serial.begin(115200);

    // ----- WIFI Setup -------
    WiFi.mode(WIFI_AP_STA);
    WiFi.setAutoReconnect( false );

    setup_wifi( 6, 1 );
    
    // ----- Motor Setup ------
    pinMode(RELAY_1, OUTPUT);
    motor_control( MOTOR_OFF );

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", "<h1 style='text-align: center;'>Page is still being developed</h1><script>var gateway = `ws://${window.location.hostname}/ws`;var websocket;window.addEventListener('load', onLoad);function initWebSocket() {  console.log('Trying to open a WebSocket connection...');  websocket = new WebSocket(gateway);  websocket.onopen    = onOpen;  websocket.onclose   = onClose;  websocket.onmessage = onMessage; }function onOpen(event) {  console.log('Connection opened');}function onClose(event) {  console.log('Connection closed');  setTimeout(initWebSocket, 2000);}function onMessage(event) {  document.getElementsByTagName('h1').innerHTML = event.data;}function onLoad(event) {  initWebSocket();}</script>" );
    });
    
    server.onNotFound([](AsyncWebServerRequest *request){
        request->send_P(200, "text/html", "<h1 style='text-align: center;'>Page is still being developed</h1> <script>var gateway = `ws://${window.location.hostname}/ws`;var websocket;window.addEventListener('load', onLoad);function initWebSocket() {  console.log('Trying to open a WebSocket connection...');  websocket = new WebSocket(gateway);  websocket.onopen    = onOpen;  websocket.onclose   = onClose;  websocket.onmessage = onMessage; }function onOpen(event) {  console.log('Connection opened');}function onClose(event) {  console.log('Connection closed');  setTimeout(initWebSocket, 2000);}function onMessage(event) {  document.getElementsByTagName('h1').innerHTML = event.data;}function onLoad(event) {  initWebSocket();}</script>" );
    });

    // ----- Server Configuration ----
    ws.onEvent(onEvent);
    server.addHandler(&ws);

    // Start server
    server.begin();
}
