<?php

    include "functions.php";

    if( !empty( $_SESSION["mail"]["subject"] ) 
            && !empty( $_SESSION["mail"]["body"] ) 
            && !empty( $_SESSION["mail"]["emailid"] ) ){

        if( mail_to( $_SESSION["mail"]["emailid"], $_SESSION["mail"]["subject"], $_SESSION["mail"]["body"] ) ){
            http_response_code(200);
        } else {
            http_response_code(401);
        }
        
    } else {
        // echo json_encode( $_SESSION["mail"] );
        http_response_code(417);
    }

    print_r( $_SESSION["hato-postdata"] );

?>