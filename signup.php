<?php 
    // ini_set('display_errors', '1');

    session_start();

    include "_headers/db_connection.php";
    include "_headers/functions.php";

    $span_email_check = false;  
    $span_nodemcu_check = false;
    global $connection;

    if ( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) ){
        header("location:information.php");
    } else {
        cookie_check( 'information.php' , $redirect = true );
    }

    if( isset( $_POST['submit'] ) && isset( $_POST['email'] ) && isset( $_POST['password'] ) && !empty( $_POST['email'] ) && !empty( $_POST['password'] ) ) {

        $node_mcu = mysqli_escape_string( $connection, $_POST['nodeMCUCode']);
        $query = "SELECT * FROM registered_node_mcu WHERE node_mcu_unique_id = '".$node_mcu."'";

        if( mysqli_num_rows( mysqli_query( $connection, $query ) ) > 0 ){

            $email = mysqli_escape_string( $connection, $_POST['email']);

            $emailCheck = "SELECT * FROM user_login WHERE user_email_id = '$email'; ";

            $qemailCheck = mysqli_query( $connection, $emailCheck);

            if( mysqli_num_rows($qemailCheck) > 0 ) {

                $span_email_check = true;

                echo "<script> if( window.history.replaceState ){
                                    window.history.replaceState( null, null, location.href='#' );
                                }
                    </script>";     

                

            } else {

                $_SESSION['hato-postdata'] = $_POST;   

                $verification = rand(1000000,9999999);
                
                $_SESSION['hato-postdata']['verification'] = $verification;

                $subject = "Verification Code For HOMEATO";

                $message = "<h1>Hello <strong>" . $_POST["fname"] . "</strong>.</h1>";
                $message .= "<br>Welcome to HOMEATO.";
                $message .= "<br><br>Verfication Code is : <strong>" . $verification . "</strong>";
                $message .= "<br><br>Please enter the above code in our verification site.";
                $message .= "<br><br>Thank You.<br>HOMEATO";

                $_SESSION["hato-mail"] = Array(
                    "emailid" => $_POST['email'],
                    "subject" => $subject,
                    "body" => $message
                );

                if( mail_to($email, $subject, $message) ){
                    echo "<script> if( window.history.replaceState ){
                                        window.history.replaceState( null, null, location.href='registration_confirmation.php' );
                                    }
                        </script>";
                } else {
                    session_destroy();

                        echo "<script>
                                    alert('Couldn\'t send the mail.\\nPlease contact admin.!');
                                    window.location.href='login.php';
                        </script>";
                }

                

            }
        } else {
            $span_nodemcu_check = true;
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

        <header id="header" class="fixed-top header-pannel">
            <div class="container d-flex align-items-center justify-content-between">
                <h1 class="logo"><a href="index.php">HOME<span>ATO</span></a></h1>
                <a href="login.php" class="login-btn">Login</a>
            </div>
        </header>
    

        <div class="sign_main">
            <div class="container">
                <div class="row">
                    <div class="col-sm-9 col-md-7 col-lg-5 mx-auto">
                        <div class="card card-signin my-5">
                            <div class="card-body">
                                <h5 class="card-title text-center">Sign Up</h5>
                                <form class="form-signin" name="signupform" method="POST" action="signup.php" onSubmit="return checkPassword(this)">
                                    
                                    <?php
                                        if( $span_email_check ){
                                            echo "<h6 class='text-center' style='color: red;'><strong>' " . $email ." ' already exists!</strong></h6>
                                                <br>";
                                        }
                                    ?>

                                    <?php
                                        if( $span_nodemcu_check ){
                                            echo "<h6 class='text-center' style='color: red;'><strong>Previously entered ' Node MCU Code ' was incorrect!</strong></h6>
                                                <br>";
                                        }
                                    ?>

                                    <h6 class="text-center" id="error" style="color: red; display: none;"><strong>Password doesn't match! Try Again.</strong></h6>
                                    

                                    <div class="form-label-group">
                                        <input type="text" name="fname" id="inputName" class="form-control" placeholder="Full Name" required autofocus onKeyup="checkform()">
                                        <label for="inputName">Full Name</label>
                                    </div>

                                    <div class="form-label-group">
                                        <input type="email" name="email" id="inputEmail" class="form-control" placeholder="Email address" required autofocus onKeyup="checkform()">
                                        <label for="inputEmail">Email address</label>
                                    </div>

                                    <?php

                                        if( isset( $_GET["nodemcuid"] ) && !empty( $_GET["nodemcuid"] ) ){

                                            echo "
                                                <div class='form-label-group'>
                                                    <input type='text' value='".$_GET["nodemcuid"]."' disabled class='form-control' placeholder='Node MCU Code' required autofocus onKeyup='checkform()'>
                                                    <label for='inputNodeMcuCode'>Node MCU Code</label>
                                                </div>

                                                <input type='hidden' id='inputNodeMcuCode' name='nodeMCUCode' value='".$_GET["nodemcuid"]."'>
                                            ";

                                        } else {

                                            echo "
                                                <div class='form-label-group'>
                                                    <input type='text' id='inputNodeMcuCode' name='nodeMCUCode' class='form-control' placeholder='Node MCU Code' required autofocus onKeyup='checkform()'>
                                                    <label for='inputNodeMcuCode'>Node MCU Code</label>
                                                </div>
                                            ";

                                        }

                                    ?>

                                    

                                    <div class="form-label-group">
                                        <input type="password" name="password" id="inputPassword" class="form-control" placeholder="Password" name="password" required onKeyup="checkform()" minlength = "8">
                                        <label for="inputPassword">Password</label>
                                    </div>

                                    <div class="form-label-group">
                                        <input type="password" id="inputPassword1" class="form-control" placeholder="Password" name="conf_password" required onKeyup="checkform()">
                                        <label for="inputPassword1">Confirm Password</label>
                                    </div>
                                    <input id="submitbutton" class="btn btn-lg btn-block text-uppercase" name="submit"  type="submit" style="background-color: #000; color: #fff;" disabled="disabled" value="Submit" />
                                    <p style="padding-top: 3%; text-align: right; margin-right: 2%;">Existing User? <span><a href="login.php">Log In</a></span></p>
                                    <hr class="my-4">
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
        <script type="text/javascript" language="javascript">
            function checkform() {
                var f = document.forms["signupform"].elements;
                var c = true;
                for (var i = 0; i < f.length; i++) {
                    if (f[i].value.length == 0)
                        c = false;
                }
                if (c) {
                    document.getElementById('submitbutton').disabled = !c;
                }
            }

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