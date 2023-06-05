<?php
    // ini_set('display_errors', '1');
    session_start();
    date_default_timezone_set("Asia/Kolkata");
    include "../../_headers/db_connection.php";

    global $connection;

    function updateData( $rawdata ){

        global $connection;
        
        $query = "UPDATE user_requests SET ";
        $query .= "time_stamp = '".$rawdata["time_stamp"]."', ";
        $query .= "pump_manual_overide_request = '" . $rawdata["pump_manual_overide_request"] . "', "; 
        $query .= "pump_on_off_status = '" . $rawdata["pump_on_off_status"] . "', ";
        $query .= "pump_take_over_complete_control = '" . $rawdata["pump_take_over_complete_control"] . "' ";
        $query .= "WHERE node_mcu_is_controled_by_user_id = '" . $_SESSION["hato-token-id"] . "' AND ";
        $query .= "phpsessid = '" . $rawdata["phpsessid"] . "'; ";

        if( mysqli_query( $connection, $query ) ){

            return [
                "success" => true, 
                "affected_rows" => mysqli_affected_rows( $connection ),
                // "query" => $query,
                // "mysqli_error" => mysqli_error( $connection ) 
            ];

        } else {

            return [ 
                "success" => false, 
                "affected_rows" => mysqli_affected_rows( $connection ),
                // "query" => $query,
                // "mysqli_error" => mysqli_error( $connection ) 
            ];

        }
    }

    function insertDate( $rawdata ){

        global $connection;

        $query = "
            UPDATE node_mcu_data SET 
            is_controlled_locally = false
            WHERE unc_node_mcu_unique_id = '".$_SESSION["hato-nodemcu_id"]."'
        ";

        if( !mysqli_query( $connection, $query ) ){
            return [
                "success" => false,
                "from" => "UPDATE"
            ];
        }

        $query = "INSERT INTO user_requests (time_stamp, 
                                            unc_node_mcu_unique_id, 
                                            pump_manual_overide_request, 
                                            pump_on_off_status, 
                                            pump_take_over_complete_control, 
                                            node_mcu_is_controled_by_user_id,
                                            phpsessid) VALUES ( ";
        $query .= "'".$rawdata["time_stamp"]."',";
        $query .= "'".$_SESSION["hato-nodemcu_id"]."',";
        $query .= "'".$rawdata["pump_manual_overide_request"]."',";
        $query .= "'".$rawdata["pump_on_off_status"]."',";
        $query .= "'".$rawdata["pump_take_over_complete_control"]."',";
        $query .= "'".$_SESSION["hato-token-id"]."', ";
        $query .= "'" . $rawdata["phpsessid"] . "'); ";

        return [
            "success" => mysqli_query( $connection, $query ), 
            "affected_rows" => mysqli_affected_rows( $connection )
        ];

    }

    function deleteData( $rawdata ){

        global $connection;

        $query = "DELETE FROM user_requests ";
        $query .= "WHERE node_mcu_is_controled_by_user_id = '" . $_SESSION["hato-token-id"] . "' AND ";
        $query .= "phpsessid = '" . $rawdata["phpsessid"] . "'; ";

        if( mysqli_query( $connection, $query ) ){

            return [
                "success" => true, 
                "affected_rows" => mysqli_affected_rows( $connection ),
                // "query" => $query,
                // "mysqli_error" => mysqli_error( $connection ) 
            ];

        } else {

            return [
                "success" => false, 
                "affected_rows" => mysqli_affected_rows( $connection ),
                // "query" => $query,
                // "mysqli_error" => mysqli_error( $connection ) 
            ];

        }

    }

    function getUserUnderNodeMCU_Control( $user_requests_data ){

        global $connection;

        $query = "SELECT user_full_name, user_unique_id FROM user_login ";
        $query .= "WHERE user_unique_id = '" . $user_requests_data["node_mcu_is_controled_by_user_id"] . "'; ";

        $result = mysqli_query( $connection, $query );

        if( $result && mysqli_num_rows( $result ) > 0 ){

            $result = mysqli_fetch_assoc( $result );

            return [ 
                "execution_error" => false,
                "success" => false, 
                "usedby" => $result["user_full_name"],
                // "query" => $query,
                // "mysqli_error" => mysqli_error( $connection ) 
            ];

        } else {

            return [ 
                "execution_error" => true,
                "success" => false, 
                "usedby" => "Unknown User",
                // "query" => $query,
                // "mysqli_error" => mysqli_error( $connection ) 
            ];

        }

    }


    if( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) 
            && isset( $_SESSION["hato-nodemcu_id"] ) && !empty( $_SESSION["hato-nodemcu_id"] ) 
    ){
        $rawdata = json_decode( file_get_contents('php://input'), true );

        $rawdata["time_stamp"] = mysqli_escape_string( $connection, date("Y-m-d H:i:s") );
        $rawdata["pump_manual_overide_request"] = mysqli_escape_string( $connection, $rawdata["pump_manual_overide_request"] );
        $rawdata["pump_on_off_status"] = mysqli_escape_string( $connection, $rawdata["pump_on_off_status"] );
        $rawdata["pump_take_over_complete_control"] = mysqli_escape_string( $connection, $rawdata["pump_take_over_complete_control"] );
        $rawdata["phpsessid"] = mysqli_escape_string( $connection, $_COOKIE["PHPSESSID"] );

        if( $rawdata["operation_count"] == -1 ){
            
            echo json_encode( deleteData( $rawdata ) );

        } else if( $rawdata["operation_count"] == 0 ){

            $result = insertDate( $rawdata );
            
            if( $result["success"]  ){

                echo json_encode( $result );
                
            } else if( $result["from"] === "UPDATE" ) {
                
                // unset( $result["from"] );
                echo json_encode( $result );

            } else {
                
                $query = "SELECT node_mcu_is_controled_by_user_id, time_stamp, phpsessid FROM user_requests ";
                $query .= "WHERE unc_node_mcu_unique_id = '".$_SESSION["hato-nodemcu_id"] ."'; ";

                $result = mysqli_query( $connection, $query );

                if( $result && mysqli_num_rows( $result ) > 0 ){
                    
                    $user_requests_data = mysqli_fetch_assoc( $result );
                    
                    if( ( strtotime( $rawdata["time_stamp"] ) - strtotime( $user_requests_data["time_stamp"] ) ) > 10   && 
                    //     $user_requests_data["node_mcu_is_controled_by_user_id"] != $_SESSION["hato-token-id"] && 
                        $rawdata["phpsessid"] != $user_requests_data["phpsessid"]
                    ){

                        $query = "DELETE FROM user_requests WHERE unc_node_mcu_unique_id = '".$_SESSION["hato-nodemcu_id"] ."'; ";

                        $result = mysqli_query( $connection, $query );

                        if( $result and mysqli_affected_rows( $connection ) > 0 ){

                            $result = insertDate( $rawdata );

                            if( $result["success"]  ){

                                // $result["time_stamp_from_user"] = $rawdata["time_stamp"];
                                // $result["time_stamp_from_db"] = $user_requests_data["time_stamp"];
                                echo json_encode( $result );

                            } else {
                                echo json_encode( getUserUnderNodeMCU_Control( $user_requests_data ) );
                            }

                        } else {

                            echo json_encode( [ 
                                "success" => false, 
                                "affected_rows" => 0,
                                // "query" => $query,
                                // "mysqli_error" => mysqli_error( $connection )
                            ]);

                        }

                    } else if( $user_requests_data["node_mcu_is_controled_by_user_id"] == $_SESSION["hato-token-id"] && 
                                $rawdata["phpsessid"] == $user_requests_data["phpsessid"]
                    ){

                        echo json_encode( updateData( $rawdata ) );

                    } else {

                        echo json_encode( getUserUnderNodeMCU_Control( $user_requests_data ) );
                        // $result = [];
                        // $result["time_stamp_from_user"] = $rawdata["time_stamp"];
                        // $result["time_stamp_from_db"] = $user_requests_data["time_stamp"];
                        // $result["calculated_time"] = ( strtotime( $rawdata["time_stamp"] ) - strtotime( $user_requests_data["time_stamp"] ) );
                        // echo json_encode( $result );

                    }
                    
                } else{

                    echo json_encode( [ 
                        "success" => false, 
                        "affected_rows" => 0,
                        // "query" => $query,
                        // "mysqli_error" => mysqli_error( $connection )
                    ]);

                }

            }
        
        } else if( $rawdata["operation_count"] == 1 ){

            echo json_encode( updateData( $rawdata ) );

        }

    } else {
        echo json_encode( [ 
            "success" => false, 
            "affected_rows" => 0,
            "query" => "No query executed"
        ] );
    }

?>