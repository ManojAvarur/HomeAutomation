void loop(){
    water_pump();
    if( WiFi.status() == WL_CONNECTED ){
        update_server( 0 );
        check_requests_from_server();
    } else {
        if( setup_wifi( 1, 0 ) ){
            // Turn on local web server
            server.end();
            ws.cleanupClients();
        }
    }
    
}
