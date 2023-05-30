<?php

    session_start();

    include "_headers/db_connection.php";
    include "_headers/functions.php";

    $spanCheck = false;  
    global $connection;

    if ( isset( $_SESSION["hato-token-id"] ) && !empty( $_SESSION["hato-token-id"] ) ){
        header("location:information.php");
    } else {
        cookie_check( 'information.php' , $redirect = true );
    }



    if( isset( $_SESSION["hato-forgot_password"] ) && !isset( $_SESSION["hato-forgot_password"]["authenticated"]  )
            && !empty( $_SESSION["hato-forgot_password"]["authentication_code"] )
            && !empty( $_SESSION["hato-forgot_password"]["email_id"] ) 
            && !empty( $_SESSION["hato-forgot_password"]["user_unique_id"] )  
    ){
        //------------------------------------------------ Values initialisation ----------------------------------------------------------- 

        if( isset( $_POST['submit'] )) {
            
            if( $_POST['passcode'] == $_SESSION["hato-forgot_password"]["authentication_code"] ){
                // $_SESSION["hato-forgot_password"]["authentication_code"] = null;
                $_SESSION["hato-forgot_password"]["authenticated"] = true;
                // die("completed");
                header('location:forgot_password_new_password.php');
            } else {
                $spanCheck = true;            
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
                                <h5 class="card-title text-center">Email Verification!</h5>
                                <p style="margin-top: -8%;padding-bottom: 5%;text-align: center;">Check your mail <br>'&nbsp;<strong><?php echo $_SESSION["hato-forgot_password"]["email_id"] ?></strong>&nbsp;'<br> for activation passcode</p>

                        <?php

                                if($spanCheck)
                                    echo "<h6 class='text-center' style='color: red;'><strong>Incorrect passcode! Please try it again </strong> </h6>";
                        
                        ?>
                                
                                <form class="form-signin" action="forgot_password_authenticate.php" method="post">
                                    <div class="form-label-group">
                                        <input type="text" name="passcode" id="inputEmail" class="form-control" placeholder="Email address" required autofocus>
                                        <label for="inputEmail">Enter the Passcode</label>
                                    </div>

                                    <button class="btn btn-lg btn-block text-uppercase" style="background-color: #000; color: #fff;" name="submit" type="submit">Submit</button>
                                    <p style="padding-top: 3%; text-align: right; margin-right: 2%;" >Didn't receive a mail? 
                                        <span>
                                            <a href="javascript:void(0);" id="linkRef" onclick="resend_mail()">Try Again</a>
                                        </span>
                                    </p>
                                    <p style='padding-top: 3%; text-align: right; margin-right: 2%;'>Incorrect Mail?
                                        <span>
                                            <a href=''  onclick="window.history.go(-1); return false;" id='mailReset'>Click Here</a>
                                        </span>
                                    </p>
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
        <script type = "text/javascript"> 

            let tryAgainCounter = setInterval(resend_mail_counter, 1000);
            var counter = 30;
            var resend_mail_element = document.getElementById("linkRef");
            resend_mail_element.classList.add("disabled-link");

            function resend_mail_counter() {
                resend_mail_element.innerText = " Try After : "+counter+"s";
                --counter;

                if( counter < 0 ){
                    clearInterval( tryAgainCounter );
                    counter = 30; 
                    resend_mail_element.innerText = " Try Again";
                    resend_mail_element.classList.remove( resend_mail_element.classList[0] );
                    resend_mail_element.disabled = false;
                }

            }

            function resend_mail(){
                resend_mail_element.disabled = true;
                resend_mail_element.classList.add("disabled-link");
                tryAgainCounter = setInterval(resend_mail_counter, 1000);
                fetch("_headers/resend_mail.php");
            }

        </script> 

    </body>
</html>

<?php

    } else if( isset( $_SESSION["hato-forgot_password"]["authenticated"] ) && $_SESSION["hato-forgot_password"]["authenticated"] == true ) {
        header('location:forgot_password_new_password.php');
    } else {
        header('location:login.php');
    }

?>