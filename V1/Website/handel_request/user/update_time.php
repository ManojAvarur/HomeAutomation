<?php
    session_start();

    include "../../_headers/db_connection.php";

    global $connection;

    if( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) 
            && isset( $_SESSION["hato-nodemcu_id"] ) && !empty( $_SESSION["hato-nodemcu_id"] ) 
    ){
        $rawdata = json_decode( file_get_contents('php://input'), true );

        $rawdata["timeStamp"] = mysqli_escape_string( $connection, $rawdata["timeStamp"] );
        
        $query = "UPDATE user_requests SET ";
        $query .= "time_stamp = '".$rawdata["timeStamp"]."' ";
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