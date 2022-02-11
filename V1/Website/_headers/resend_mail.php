<?php
    session_start();
    include "functions.php";

    if( isset( $_SESSION["hato-mail"] )
            && !empty( $_SESSION["hato-mail"]["subject"] ) 
            && !empty( $_SESSION["hato-mail"]["body"] ) 
            && !empty( $_SESSION["hato-mail"]["emailid"] ) ){

        if( mail_to( $_SESSION["hato-mail"]["emailid"], $_SESSION["hato-mail"]["subject"], $_SESSION["hato-mail"]["body"] ) ){
            http_response_code(200);
        } else {
            http_response_code(401);
        }
        
    } else {
        http_response_code(417);
    }
    // echo empty( $_SESSION["hato-mail"]["body"] ) ;
    // print_r($_SESSION["hato-mail"] );

?>