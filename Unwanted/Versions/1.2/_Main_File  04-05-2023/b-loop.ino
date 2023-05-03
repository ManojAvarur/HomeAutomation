void loop(){
    water_pump();
    if( WiFi.status() == WL_CONNECTED ){
        update_server( 0 );
        check_requests_from_server();
    } 
}
