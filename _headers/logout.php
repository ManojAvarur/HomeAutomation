<?php

    session_start();

    if ( isset( $_COOKIE['hato-token_id_1'] ) && isset( $_COOKIE['hato-token_id_2'] ) ){
 
        setcookie("hato-token_id_1", "", time() - 3600, "/");   
        setcookie("hato-token_id_2", "", time() - 3600, "/");   

    }

    session_destroy();

    header('location:../login.php');

?>