<?php
    ini_set('display_errors', '1');
    session_start();
    date_default_timezone_set("Asia/Kolkata");

    include "../../_headers/db_connection.php";

    global $connection;
    
    if( isset( $_GET["nodemcut_id"] ) && !empty( $_GET["nodemcut_id"] ) ){

        $query = "SELECT time_stamp, pump_manual_overide_request, pump_on_off_status, pump_take_over_complete_control ";
        $query .= "FROM user_requests WHERE ";
        $query .= "unc_node_mcu_unique_id = '".mysqli_escape_string( $connection, $_GET["nodemcut_id"] )."'; ";

        $result = mysqli_query( $connection, $query );
        if( $result ){
            if( mysqli_num_rows( $result ) > 0 ){
                $result = mysqli_fetch_assoc( $result );
                $result["execute_status"] = ( ( strtotime( date("Y-m-d H:i:s") ) - strtotime( "2022-01-01 00:34:30" ) ) <= 10 )? true : false;       
                $result["time_in_hours"] = date("H"); 
                echo json_encode( $result );
            } else {
                http_response_code( 404 );
            }
        } else {
            http_response_code( 400 );
        }
        
    }
?>