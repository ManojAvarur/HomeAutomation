<?php
        ini_set('display_errors', '1');
        session_start();

        include "../../_headers/db_connection.php";
        global $connection;

    if( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) 
             && isset( $_SESSION["hato-nodemcu_id"] ) && !empty( $_SESSION["hato-nodemcu_id"] ) && isset( $_SESSION["hato-is_admin"] ) )
    {            
        $query = "";
        if( $_SESSION["hato-is_admin" ] ){
            $query = "SELECT time_stamp, sump_status, tank_status, motor_status, debug_log ";
            $query .= "FROM node_mcu_data WHERE unc_node_mcu_unique_id = '".$_SESSION["hato-nodemcu_id"]."';";
        } else {
            $query = "SELECT time_stamp, sump_status, tank_status, motor_status ";
            $query .= "FROM node_mcu_data WHERE unc_node_mcu_unique_id = '".$_SESSION["hato-nodemcu_id"]."';";
        }
                
        $result = mysqli_query( $connection, $query );
        if( mysqli_num_rows( $result ) < 0 ){
            echo json_encode( mysqli_fetch_assoc( $result ) );
        } else {
            http_response_code(400);
        }

    } else {
        http_response_code(400);
    }

    ?>