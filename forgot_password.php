<?php
    session_start();

    include "_headers/db_connection.php";
    include "_headers/functions.php";

    $span_check = false;  
    global $connection;

    if ( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) ){
        header("location:information.php");
    } else {
        cookie_check( 'information.php' , $redirect = true );
    }

    if( isset( $_SESSION["hato-forgot_password"] )  ){
        session_destroy();
    }
    

    if(  isset( $_POST["hato-email-id"] ) && isset( $_POST["submit"] )  ){
        $query = "SELECT user_unique_id, user_full_name FROM user_login ";
        $query .= "WHERE user_email_id = '" . mysqli_escape_string( $connection, $_POST["hato-email-id"] ) . "'; ";

        $result = mysqli_query( $connection, $query );
        if( mysqli_num_rows( $result ) > 0 ){
            $verfication_code = rand( 100000, 1000000 );

            $result = mysqli_fetch_assoc( $result );

            $subject = "Forgot Password Reset Code";

            $message = "<h1>Hello <strong>" . $result["user_full_name"] . "</strong>.</h1>";
            $message .= "<br><br>Verfication Code is : <strong>" . $verfication_code . "</strong>";
            $message .= "<br><br>Please enter the above code in our verification site.";
            $message .= "<br><br>Thank You.<br>HOMEATO";

            $_SESSION["hato-forgot_password"] = Array(
                "authentication_code" => $verfication_code,
                "email_id" => $_POST["hato-email-id"],
                "user_unique_id" => $result["user_unique_id"]
            );

            $_SESSION["hato-mail"] = Array(
                "emailid" => $_POST['hato-email-id'],
                "subject" => $subject,
                "body" => $message
            );

            if( mail_to( $_POST["hato-email-id"], $subject, $message ) ){
                echo "<script> if( window.history.replaceState ){
                                    window.history.replaceState( null, null, location.href='forgot_password_authenticate.php' );
                                }
                    </script>";
            } else {
                session_destroy();

                    echo "<script>
                                alert('Couldn\'t send the mail.\\nPlease contact admin.!');
                                window.location.href='login.php';
                    </script>";
            }

        } else {
            $span_check = true;
        }
    }

    
?>
<!DOCTYPE html>
<html lang="en">

    <head>
        <meta charset="utf-8">
        <meta content="width=device-width, initial-scale=1.0" name="viewport">
        <title>FARMATO</title>
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

        <header id="header" class="fixed-top">
            <div class="container d-flex align-items-center justify-content-between">
                <h1 class="logo"><a href="index.php">HOME<span>ATO</span></a></h1>
                <a href="login.php" class="login-btn">Login</a>
            </div>
        </header>

        <div class="log_main">
                <div class="container">
                    <div class="row">
                        <div class="col-sm-9 col-md-7 col-lg-5 mx-auto">
                            <div class="card card-signin my-5">
                                <div class="card-body">
                                    <h5 class='card-title text-center'>Forgot Password?</h5>
                                    <p style='margin-top: -8%;padding-bottom: 5%;text-align: center;'>Enter your email to get the passcode</p>

                                    <?php
                                        if( $span_check  ){
                                    ?>
                                            <h6 class="text-center" style="color: red;"><strong>Incorrect Email-ID</strong></h6>
                                            <br>
                                    <?php
                                        }
                                    ?>

                                    <form class='form-signin' method='post' action='forgot_password.php'>
                                        <div class='form-label-group'>
                                            <input type='email' id='inputEmail' name='hato-email-id' class='form-control' placeholder='Email address' included autofocus>
                                            <label for='inputEmail'>Enter the Email</label>
                                        </div>

                                        <button class='btn btn-lg btn-block text-uppercase' name='submit' style="background-color: #689F38; color: #fff;" type='submit'>Submit</button>
                                        <!-- <p style='padding-top: 3%; text-align: right; margin-right: 2%;'>Didn't receive a mail? <span><a href='signup.php'>Try Again</a></span></p> -->
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

    </body>

</html>


