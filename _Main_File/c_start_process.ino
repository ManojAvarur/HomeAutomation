void start_process(){
    if( !high_water_level_in_tank("start_process") ){
        while( !low_water_level_in_sump("start_process") && !high_water_level_in_tank("start_process") && mid_water_level_in_sump("start_process") ){
            motor_status(true, "start_process");
            Serial.println( water_level_in_tank() );
            Serial.println( water_level_in_sump() );
        }
        motor_status(false, "start_process");
    }
}
