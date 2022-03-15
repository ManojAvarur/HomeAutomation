<?php

    session_start();

    include "_headers/db_connection.php";
    include "_headers/functions.php";

    global $connection;
    $span_check = false;

    if ( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) ){
        header("location:information.php");
    } else {
        cookie_check( 'information.php' , $redirect = true );
    }



    if( isset( $_SESSION["hato-forgot_password"] ) && isset( $_SESSION["hato-forgot_password"]["authenticated"]  )
            && $_SESSION["hato-forgot_password"]["authenticated"] == true
            && !empty( $_SESSION["hato-forgot_password"]["authentication_code"] )
            && !empty( $_SESSION["hato-forgot_password"]["email_id"] ) 
            && !empty( $_SESSION["hato-forgot_password"]["user_unique_id"] )  
    ){
        //------------------------------------------------ Values initialisation ----------------------------------------------------------- 

        if( isset( $_POST['reinsert_password'] ) && isset( $_POST["password"] ) && !empty( $_POST["password"] ) ) {
            
            $query = "UPDATE user_login ";
            $query .= "SET user_password = '". hash('sha256', $_POST["password"] ) ."' ";
            $query .= "WHERE user_unique_id = '".$_SESSION["hato-forgot_password"]["user_unique_id"]."';";

            if( mysqli_query( $connection, $query ) ){

                if( mysqli_affected_rows( $connection ) > 0 ){
                    session_destroy();
                    echo "<script>
                                    alert('Password has been successfully changed!');
                                    window.location.href='login.php';
                        </script>";
                } else {
                    // session_destroy();
                    // echo "<script>
                    //                 alert('New password cannot be same as old password.');
                    //     </script>";
                    $span_check = true;
                }

            } else {
                session_destroy();
                echo "<script>
                                alert('Error occured while changing the password!\\nPlease contact admin!');
                                window.location.href='login.php';
                    </script>";
            }
            
        }

?>


<!DOCTYPE html>
<html lang="en">
<head>
        <meta charset="utf-8">
        <meta content="width=device-width, initial-scale=1.0" name="viewport">
        <title>HOMEATO</title>
        <meta content="Farmato, Farming Automation sales, Farming Automation india" name="description">
        <meta content="Farmato, Farming Automation sales, Farming Automation india" name="keywords">
        <link href="Assets/Images/logo2.png" rel="icon">
        <link href="Assets/Images/apple-touch-icon.png" rel="apple-touch-icon">
        <link href="Assets/vendor/remixicon/remixicon.css" rel="stylesheet">
        <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,600,600i,700,700i|Raleway:300,300i,400,400i,500,500i,600,600i,700,700i|Poppins:300,300i,400,400i,500,500i,600,600i,700,700i" rel="stylesheet">
        <link href="Assets/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
        <link href="Assets/vendor/icofont/icofont.min.css" rel="stylesheet">
        <link href="Assets/vendor/owl.carousel/assets/owl.carousel.min.css" rel="stylesheet">
        <link href="Assets/vendor/venobox/venobox.css" rel="stylesheet">
        <link href="Assets/vendor/boxicons/css/boxicons.min.css" rel="stylesheet">
        <link href="Assets/vendor/aos/aos.css" rel="stylesheet">
        <link href="Assets/css/style.css" rel="stylesheet">
        <script src="Assets/js/browser_and_protocol_check.js"></script>
    </head>

<body>
    <noscript>
        <meta http-equiv = "refresh" content = "0; url = noscript.html" />
    </noscript>
    <header id="header" class="fixed-top ">
        <div class="container d-flex align-items-center justify-content-between">
            <h1 class="logo"><a href="index.php">Amart<span>.</span></a></h1>
            <a href="login.php" class="login-btn">Log In</a>
        </div>
    </header>

    <div class="log_main">
        <div class="container">
            <div class="row">
                <div class="col-sm-9 col-md-7 col-lg-5 mx-auto">
                    <div class="card card-signin my-5">
                        <div class="card-body">
                        
                            <h5 class='card-title text-center'>Enter New Password</h5>
                            <?php
                                if( $span_check  ){
                                    echo '
                                        <h6 class="text-center" style="color: red;"><strong>New password cannot be same as old password</strong></h6>
                                        <br>
                                    ';
                                }
                            ?>
                            <form class='form-signin' action='forgot_password_new_password.php' method='POST' onSubmit='return checkPassword(this)'>

                                <h6 class="text-center" id="error" style="color: red; display: none;"><strong>Password doesn't match! Try Again.</strong></h6>

                                <div class='form-label-group'>
                                    <input type='password' id='inputPassword' class='form-control' placeholder='Password' name='password' required >
                                    <label for='inputPassword'>New Password</label>
                                </div>

                                <div class='form-label-group'>
                                    <input type='password' id='inputPassword1' class='form-control' placeholder='Password' name='conf_password' required >
                                    <label for='inputPassword1'>Confirm Password</label>
                                </div>

                                <button class='btn btn-lg btn-block text-uppercase' name='reinsert_password' style='background-color: #000; color: #fff;' type='submit'>Submit</button>
                                <hr class='my-4'>
                            </form>

                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>



    <a href="#" class="back-to-top"><i class="ri-arrow-up-line"></i></a>
    <div id="preloader"></div>
    <script src="Assets/vendor/jquery/jquery.min.js"></script>
    <script src="Assets/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
    <script src="Assets/vendor/jquery.easing/jquery.easing.min.js"></script>
    <!-- <script src="Assets/vendor/php-email-form/validate.js"></script> -->
    <script src="Assets/vendor/owl.carousel/owl.carousel.min.js"></script>
    <script src="Assets/vendor/isotope-layout/isotope.pkgd.min.js"></script>
    <script src="Assets/vendor/venobox/venobox.min.js"></script>
    <script src="Assets/vendor/waypoints/jquery.waypoints.min.js"></script>
    <script src="Assets/vendor/counterup/counterup.min.js"></script>
    <script src="Assets/vendor/aos/aos.js"></script>
    <script src="Assets/js/main.js"></script>
    <script>
        function checkPassword(form) {
            var password = form.password.value;
            var conf_password = form.conf_password.value;
            if (password != conf_password) {
                document.getElementById("error").style.display = "block";
                document.getElementById('inputPassword1').value = ""; 
                return false;
            }    
        }
    </script>
</body>



</html>

<?php

} else {
    header('location:login.php');
}

?>