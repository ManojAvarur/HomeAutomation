void start_process(){
    if( !high_water_level_in_tank("start_process") ){
        while( !low_water_level_in_sump("start_process") && !high_water_level_in_tank("start_process") && mid_water_level_in_sump("start_process") ){
            motor_status(true, "start_process");
            // if( millis() - TARGET_TIME >= PERIOD ){
            //   TARGET_TIME += PERIOD;
            //   ndemcu_online_update();
            // }
        }
        motor_status(false, "start_process");
    }
}
