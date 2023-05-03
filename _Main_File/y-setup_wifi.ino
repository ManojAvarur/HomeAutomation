bool setup_wifi( short overall_wait_time, short delay_timer ){
	Serial.println("Connecting");

	short while_counter = 0;
	WiFi.begin(SSID, PASSWORD);

	while( ( WiFi.status() != WL_CONNECTED ) && ( while_counter <= overall_wait_time )) {
		Serial.print(".");
    	while_counter++;
		delay( delay_timer * 1000 );
	}

	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());
	
	return ( WiFi.status() == WL_CONNECTED );
}