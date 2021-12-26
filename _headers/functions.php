<?php
    ini_set('display_errors', '1');
    include 'PHPMailer/PHPMailerAutoload.php';
    include "db_connection.php";
    // $file = fopen( "_headers/credentials.txt", "r" );

    function generate_cookie_token( $email, $uid ){
        $cookie_id = hash('sha256', $email.$uid );
        $token_1 = substr( $cookie_id, 0, strlen($cookie_id)/2 );
        $token_2 = substr( $cookie_id, strlen($cookie_id)/2 );
        return array( $token_1, $token_2 );
    }

    function cookie_check($location='index.php', $redirect = true){

        if( isset( $_COOKIE["hato-token_id_1"] ) &&  isset( $_COOKIE["hato-token_id_2"] )  && !empty( $_COOKIE["hato-token_id_1"] ) && !empty( $_COOKIE["hato-token_id_2"] ) ){
    
            global $connection;

            //SELECT cookie_user_unique_id FROM cookie_data WHERE token_id_1 = 'f48a18ff4d1b6bfea59e832981ebc0d3' AND token_id_2 = '9764028e1b3a4592ff3f8dca1dd8f296');"
    
            $query = "SELECT user_full_name, user_unique_id, user_is_admin, user_node_mcu_reference FROM user_login ";
            $query .= "WHERE user_unique_id in ( ";
            $query .= "SELECT cookie_user_unique_id FROM cookie_data ";
            $query .= "WHERE token_id_1  = '".mysqli_escape_string( $connection, $_COOKIE["hato-token_id_1"] )."' ";
            $query .= "AND token_id_2 = '".mysqli_escape_string( $connection, $_COOKIE["hato-token_id_2"] )."' ); ";

            $result = mysqli_query( $connection, $query );
    
            if( mysqli_num_rows( $result ) > 0 ){
                $result = mysqli_fetch_assoc($result);
                $_SESSION['hato-token-id'] = $result['user_unique_id'];
                $_SESSION["hato-user_name"] = $result["user_full_name"];
                $_SESSION["hato-is_admin"] = $result["user_is_admin"];
                $_SESSION["hato-nodemcu_id"] = $result["user_node_mcu_reference"];
                if( $redirect ){
                    header('location:'.$location);
                }

                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    
    }

    function mail_to( $email_id, $subject, $message ){
        global $file;

        $mail = new PHPMailer;
        // $mail->SMTPDebug = SMTP::DEBUG_SERVER;  
        $mail->isSMTP();                                       
        $mail->Host       = 'smtp.gmail.com';                    
        $mail->SMTPAuth   = true;                              
        $mail->Username   = "";                     
        $mail->Password   = ""; 
        $mail->SMTPSecure = 'tls';           //Enable implicit TLS encryption
        $mail->Port       = 587;   
        //Sender
        $mail->setFrom('homeato.dontreplay@gmail.com', 'HOMEATO');
        //Recipient
        $mail->addAddress($email_id);    
        $mail->isHTML(true);                                  //Set email format to HTML
        $mail->Subject = $subject;
        $mail->Body    = $message;
        $mail->AltBody = strip_tags($message) ; 
        if( $mail->send() ){ 
            return true;
        } else {
            return false;
            // echo "Message not sent " . $mail->ErrorInfo;
        }
    }
?>