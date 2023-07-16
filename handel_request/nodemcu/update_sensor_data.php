<?php
    ini_set('display_errors', '1');
    session_start();
    date_default_timezone_set("Asia/Kolkata");

    include "../../_headers/db_connection.php";

    global $connection;

    if( isset( $_GET["data_ready"] )  && isset( $_GET["pump_manual_override_data"] ) ){
        $rawdata = json_decode( file_get_contents('php://input'), true );

        $timestamp = mysqli_escape_string( $connection, date("Y-m-d H:i:s") );
        
        $tank_status = mysqli_escape_string( $connection, $rawdata["tank_status"] );
        $tank_low_limit = mysqli_escape_string( $connection, $rawdata["tank_limits"]["low"] );
        $tank_high_limit = mysqli_escape_string( $connection, $rawdata["tank_limits"]["high"] );

        $sump_status = mysqli_escape_string( $connection, $rawdata["sump_status"] );
        $sump_low_limit = mysqli_escape_string( $connection, $rawdata["sump_limits"]["low"] );
        $sump_high_limit = mysqli_escape_string( $connection, $rawdata["sump_limits"]["high"] );

        $motor_status = mysqli_escape_string( $connection, $rawdata["motor_status"] );
        $debug_log = mysqli_escape_string( $connection, $rawdata["debug_log"] );
        $is_controlled_locally = ( $_GET["motor_controlled_locally"] === "1" )? 1 : 0;
        $nodemcu_id = mysqli_escape_string( $connection, $rawdata["nodemcu_id"] );
        $pump_manual_overide_data_flag = mysqli_escape_string( $connection, $_GET["pump_manual_override_data"] );


        $query = "UPDATE node_mcu_data SET ";
        $query .= "time_stamp = '" . $timestamp . "', ";

        $query .= "tank_status = '" . $tank_status . "', ";
        $query .= "tank_low_limit = '" . $tank_low_limit . "', ";
        $query .= "tank_high_limit = '" . $tank_high_limit . "', ";

        $query .= "sump_status = '" . $sump_status . "', ";
        $query .= "sump_low_limit = '" . $sump_low_limit . "', ";
        $query .= "sump_high_limit = '" . $sump_high_limit . "', ";

        $query .= "motor_status = '" . $motor_status . "', ";
        $query .= "debug_log = '" . $debug_log . "', ";
        $query .= "is_controlled_locally = " . $is_controlled_locally . ", ";
        $query .= "pump_manual_overide_data_flag = '" . $pump_manual_overide_data_flag . "' ";
        $query .= "WHERE unc_node_mcu_unique_id = '" . $nodemcu_id . "'; ";

        echo  $query;
        if( mysqli_query( $connection, $query ) ){
            if( mysqli_affected_rows( $connection ) > 0 ){
                // echo json_encode([
                //     "query" => $query,
                //     "success" => true
                // ]);
                http_response_code(200);
            } else {

                
                $query = "INSERT INTO node_mcu_data (
                                        time_stamp, 
                                        unc_node_mcu_unique_id,
                                        sump_status,
                                        sump_low_limit,
                                        sump_high_limit,
                                        tank_status,
                                        tank_low_limit,
                                        tank_high_limit,
                                        motor_status,
                                        debug_log,
                                        is_controlled_locally,
                                        pump_manual_overide_data_flag) VALUES (";
                $query .= "'".$timestamp."', ";
                $query .= "'".$nodemcu_id."', ";
                
                $query .= "'".$sump_status."', ";
                $query .= "'".$sump_low_limit."', ";
                $query .= "'".$sump_high_limit."', ";

                $query .= "'".$tank_status."', ";
                $query .= "'".$tank_low_limit."', ";
                $query .= "'".$tank_high_limit."', ";
                
                $query .= "'".$motor_status."', ";
                $query .= "'".$debug_log."', ";
                $query .= "'".$is_controlled_locally."', ";
                $query .= "'".$pump_manual_overide_data_flag."'); ";
                
                // echo $query;
                
                if( mysqli_query( $connection, $query ) ){
                    if( mysqli_affected_rows( $connection ) > 0 ){
                        // echo json_encode([
                        //     "query" => $query,
                        //     "success" => true
                        // ]);
                        http_response_code(200);
                    } else {
                        // echo json_encode([
                        //     "query" => $query,
                        //     "success" => mysqli_error( $connection )
                        // ]);
                        http_response_code(400);
                    }
                } else {
                    // echo json_encode([
                    //     "query" => $query,
                    //     "success" => mysqli_error( $connection )
                    // ]);
                    http_response_code(400);
                }
            } 
        } else {
            // echo json_encode([
            //     "query" => $query,
            //     "success" => mysqli_error( $connection )
            // ]); 
            http_response_code(400);
        }
    } else {
        http_response_code(400);
    }

    
// INSERT INTO `node_mcu_data` (`time_stamp`, `unc_node_mcu_unique_id`, `sump_status`, `tank_status`, `motor_status`, `debug_log`, `pump_manual_overide_data_flag`) VALUES (current_timestamp(), '6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b', '2', '2', '1', 'Test Log', NULL);

// UPDATE `node_mcu_data` SET `tank_status` = '3' WHERE `node_mcu_data`.`unc_node_mcu_unique_id` = '6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b';