void loop(){
    water_pump();
    if( WiFi.status() == WL_CONNECTED ){
        update_server();
        check_requests_from_server();
    } 
}
