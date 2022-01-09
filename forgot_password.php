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

    if(  isset( $_POST["email-id"] ) && isset( $_POST["submit"]) ){
        $query = "SELECT user_unique_id FROM user_login ";
        $query .= "WHERE user_email_id = '" . mysqli_escape_string( $connection, $_POST["email-id"] ) . "'; ";

        $result = mysqli_query( $connection, $query );
        if( mysqli_num_rows( $result ) > 0 ){
            $verfication_code = rand( 100000, 1000000 );

            $message = "Hello, <br>";
            $message .= "This is your verification code for reseting your password : ";
            $message .= "<strong><u>".$verfication_code."</u></strong>";
            $subject = "Password Reset Code.";

            $_SESSION["authenticate"] = $verfication_code;
            $_SESSION["email-id"] = $_POST["email-id"];
            $_SESSION["mail"]["message"] = $message;
            $_SESSION["mail"]["subject"] = $subject;

            mail_to( $_POST["email-id"], $message, $subject);
            header("location:authenticate.php");
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
        <script src="Assets/js/browser_check.js"></script>
    </head>

<body>

    <header id="header" class="fixed-top">
        <div class="container d-flex align-items-center justify-content-between">
            <h1 class="logo"><a href="index.php">FARM<span>ATO</span></a></h1>
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
                                        <input type='email' id='inputEmail' name='email-id' class='form-control' placeholder='Email address' included autofocus>
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

        <footer id="footer">
            <div class="footer-top">
                <div class="container">
                    <div class="row justify-content-center">
                        <div class="col-lg-3 col-md-6 footer-links">
                            <h4>Services</h4>
                            <ul>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Return Policy</a></li>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Security</a></li>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Term of Use</a></li>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Privacy policy</a></li>
                            </ul>
                        </div>
    
                        <div class="col-lg-3 col-md-6 footer-links">
                            <h4>About</h4>
                            <ul>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Company</a></li>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Team</a></li>
                            </ul>
                        </div>
    
                        <div class="col-lg-3 col-md-12 footer-links">
                            <h4>Contact Us</h4>
                            <ul>
                                <li><i class="bx bx-wifi-1"></i> <a href="mailto:farmato.dontreply@gmail.com">Via Email</a></li>
                                <li><i class="bx bx-wifi-1"></i> <a href="tel:+919123456780">Via Phone Call</a></li>
                            </ul>
                        </div>
    
                    </div>
                </div>
            </div>
        </footer>

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

    <script type = "text/javascript"> 

        var myvar = setInterval(myTimer, 1000);
        var timerSec = 30; 
        var counter = timerSec;
        var Link = document.getElementById("linkRef");
        Link.href = "javascript:void(0)";
        Link.classList.add("disabled-link");

        function myTimer() {
            Link.innerHTML = " Try After : "+counter+"sec";
            
            counter = counter - 1;

            if(counter<0){
                clearInterval(myvar);
                counter = timerSec;
                Link.href = "_headers/resendmail.php";   
                Link.innerHTML = " Try Again";
                Link.classList.remove("disabled-link");
            }
        }

        function checkPassword(form) {
        var password = form.password.value;
        var conf_password = form.conf_password.value;
        if (password != conf_password) {
            alert("PASSWORDS DO NOT MATCH: \nPlease try again...");
            document.getElementById('inputPassword1').value = ""; 
            return false;
        }    
    }

    </script> 
</body>

</html>


