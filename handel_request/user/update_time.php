<?php
    session_start();
    date_default_timezone_set("Asia/Kolkata");
    include "../../_headers/db_connection.php";

    global $connection;

    if( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) 
            && isset( $_SESSION["hato-nodemcu_id"] ) && !empty( $_SESSION["hato-nodemcu_id"] ) 
    ){
        
        $query = "UPDATE user_requests SET ";
        $query .= "time_stamp = '". mysqli_escape_string( $connection, date("Y-m-d H:i:s") ) ."' ";
        $query .= "WHERE node_mcu_is_controled_by_user_id = '".$_SESSION["hato-token-id"]."';";
        
        if( mysqli_query( $connection, $query ) ){
            echo json_encode( [
                "success" => true, 
                "affected_rows" => mysqli_affected_rows( $connection ),
                "query" => $query 
            ]);
        } else {
            echo json_encode( [
                "success" => fasle, 
                "affected_rows" => mysqli_affected_rows( $connection ),
                "query" => $query 
            ]);
        }

        
    }
?>