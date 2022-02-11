<?php
    // ini_set('display_errors', '1');
    session_start();

    include "../../_headers/db_connection.php";

    global $connection;

    function retryWithUpdate( $rawdata ){
        global $connection;
        
        $query = "UPDATE user_requests SET ";
        $query .= "time_stamp = '".$rawdata["time_stamp"]."', ";
        $query .= "pump_manual_overide_request = '" . $rawdata["pump_manual_overide_request"] . "', "; 
        $query .= "pump_on_off_status = '" . $rawdata["pump_on_off_status"] . "', ";
        $query .= "pump_take_over_complete_control = '" . $rawdata["pump_take_over_complete_control"] . "' ";
        $query .= "WHERE node_mcu_is_controled_by_user_id = '" . $_SESSION["hato-token-id"] . "';";

        if( mysqli_query( $connection, $query ) ){
            echo json_encode( [
                    "success" => true, 
                    "affected_rows" => mysqli_affected_rows( $connection ),
                    // "query" => $query 
                ]);
        } else {
            echo json_encode( [ 
                "success" => false, 
                "affected_rows" => mysqli_affected_rows( $connection ),
                // "query" => $query 
            ]);
        }
    }


    if( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) 
            && isset( $_SESSION["hato-nodemcu_id"] ) && !empty( $_SESSION["hato-nodemcu_id"] ) 
    ){
        $rawdata = json_decode( file_get_contents('php://input'), true );

        $rawdata["time_stamp"] = mysqli_escape_string( $connection, $rawdata["time_stamp"] );
        $rawdata["pump_manual_overide_request"] = mysqli_escape_string( $connection, $rawdata["pump_manual_overide_request"] );
        $rawdata["pump_on_off_status"] = mysqli_escape_string( $connection, $rawdata["pump_on_off_status"] );
        $rawdata["pump_take_over_complete_control"] = mysqli_escape_string( $connection, $rawdata["pump_take_over_complete_control"] );

        $query;

        if( $rawdata["operation_count"] == -1 ){
            
            $query = "DELETE FROM user_requests WHERE node_mcu_is_controled_by_user_id = '" . $_SESSION["hato-token-id"] . "'";

        } else if( $rawdata["operation_count"] == 0 ){

            $query = "INSERT INTO user_requests (time_stamp, unc_node_mcu_unique_id, pump_manual_overide_request, pump_on_off_status, pump_take_over_complete_control, node_mcu_is_controled_by_user_id) VALUES ( ";
            $query .= "'".$rawdata["time_stamp"]."',";
            $query .= "'".$_SESSION["hato-nodemcu_id"]."',";
            $query .= "'".$rawdata["pump_manual_overide_request"]."',";
            $query .= "'".$rawdata["pump_on_off_status"]."',";
            $query .= "'".$rawdata["pump_take_over_complete_control"]."',";
            $query .= "'".$_SESSION["hato-token-id"]."');";

        } else if( $rawdata["operation_count"] == 1 ){

            $query = "UPDATE user_requests SET ";
            $query .= "pump_manual_overide_request = '" . $rawdata["pump_manual_overide_request"] . "', "; 
            $query .= "pump_on_off_status = '" . $rawdata["pump_on_off_status"] . "', ";
            $query .= "pump_take_over_complete_control = '" . $rawdata["pump_take_over_complete_control"] . "' ";
            $query .= "WHERE node_mcu_is_controled_by_user_id = '" . $_SESSION["hato-token-id"] . "';";

        }

        if( mysqli_query( $connection, $query ) ){
            echo json_encode( [
                    "success" => true, 
                    "affected_rows" => mysqli_affected_rows( $connection ),
                    // "query" => $query 
                ]);
        } else {
            if( $rawdata["operation_count"] == 0 ){

                $query = "SELECT user_full_name, user_unique_id FROM user_login WHERE user_unique_id = ";
                $query .= "( SELECT node_mcu_is_controled_by_user_id FROM user_requests ";
                $query .= "WHERE unc_node_mcu_unique_id = '".$_SESSION["hato-nodemcu_id"] ."')";

                $result = mysqli_query( $connection, $query );

                if( mysqli_num_rows( $result ) > 0 ){
                    $result = mysqli_fetch_assoc( $result );
                    if( $result["user_unique_id"] == $_SESSION["hato-token-id"] ){
                        retryWithUpdate( $rawdata );
                    } else {
                        echo json_encode( [ "success" => false, "usedby" => $result["user_full_name"] ] );
                    }
                } else {
                    echo json_encode( [ 
                        "success" => false, 
                        "affected_rows" => mysqli_affected_rows( $connection ),
                        // "query" => $query 
                    ]);
                }
            } else {
                echo json_encode( [ 
                    "success" => false, 
                    "affected_rows" => mysqli_affected_rows( $connection ),
                    // "query" => $query 
                ]);
            }
        }
    } else {
        echo json_encode( [ 
            "success" => false, 
            "affected_rows" => mysqli_affected_rows( $connection ),
            // "query" => $query 
        ]);
    }
