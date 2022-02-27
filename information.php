<?php 
    // ini_set('display_errors', '1');

    session_start();

    include "_headers/db_connection.php";
    include "_headers/functions.php";
    global $connection;
    $span_check = false;

    if ( !isset( $_SESSION["hato-token-id"] ) && empty( $_SESSION["hato-token-id"] ) && !isset( $_SESSION["hato-user_name"] ) && empty( $_SESSION["hato-user_name"] ) && !isset( $_SESSION["hato-is_admin"] ) && empty( $_SESSION["hato-is_admin" ] ) ){
        if( ! cookie_check() ){
            header("location:login.php");
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
        <link href="Assets/vendor/toggle-switch/css/manual-toggle.css" rel="stylesheet">
        <!-- <link href="Assets/vendor/toggle-switch/css/bootstrap4-toggle.min.css" rel="stylesheet"> -->
        <link href="Assets/css/style.css" rel="stylesheet">
        <script src="Assets/js/browser_check.js"></script>
    </head>
    <body>
        <noscript>
            <meta http-equiv = "refresh" content = "0; url = noscript.html" />
        </noscript>
        <header id="header" class="fixed-top">
            <div class="container d-flex align-items-center justify-content-between">
                <h1 class="logo"><a href="index.php">HOME<span>ATO</span></a></h1>

                <?php
                    if( $_SESSION["hato-is_admin"] ){
                ?>

                    <nav class="nav-bar d-none d-lg-block">
                        <ul>
                            <li><a href="javascript:void(0);" onclick="loadSensorData()" class="login-btn">Refresh Data</a></li>
                        </ul>
                    </nav>
                    <nav class="nav-bar d-lg-none d-sm-block">
                        <ul>
                            <li class="drop-down">
                                <a></a>
                                <ul>
                                    <!-- <li class="active"><a href="index.php">Home</a></li> -->
                                    <li><a href="javascript:void(0);" onclick="loadSensorData()" class="login-btn active">Refresh Data</a></li> 
                                </ul>
                            </li>
                        </ul>
                    </nav>

                <?php
                    }
                ?>
                
                <a href="javascript:void(0);" onclick="logout()" class="login-btn">Log Out</a>
            </div>
        </header>

        <section id="information_main_home" class="d-flex align-items-center justify-content-center">
            <div class="container">
                <div class="row justify-content-center" data-aos="fade-down" data-aos-delay="150">
                    <div class="col-xl-6 col-lg-8">
                        <script type="text/javascript">
                            document.write("<h1>");
                            var username = "<?= $_SESSION["hato-user_name"] ?>"
                            var day = new Date();
                            var hr = day.getHours();
                            if (hr >= 0 && hr < 12) {
                                document.write("Good Morning <br>"+username+"<span>!</span>");
                            } else if (hr >= 12 && hr <= 17) {
                                document.write("Good Afternoon <br>"+username+"<span>!</span>");
                            } else {
                                document.write("Good Evening <br>"+username+"<span>!</span>");
                            }
                            document.write("</h1>");
                        </script>
                    </div>
                </div>
            </div>
        </section>

        <section class="sensor-datas" id="sensorData" >
            <div class="container" data-aos="fade-down">
                <div class="section-title">
                    <h2>Sensor</h2>
                    <p>Sensor Data</p>
                    <h6>Last Updated : <span id="last-updated">Loading Data</span></h6>
                </div>

                <?php
                    if( $span_check ){
                        echo "<div class='error'>
                                <span class='closebtn' onclick='this.parentElement.style.display='none';'>&times;</span> 
                                <strong>Error! : </strong><span>Couldn't load the data.<br>Please wait for 5 seconds</span>
                            </div>"; 
                    }
                ?>
                <div class="warning" id="warning-container">
                    <span class="closebtn"  onclick="this.parentElement.style.display='none';">&times;</span> 
                    <strong id="warning-type"></strong><strong> @ <span id="warning-time"></span> : </strong><span id="warning-msg"></span>
                </div> 

                <div class="error" id="error-container">
                    <span class="closebtn" onclick="this.parentElement.style.display='none';">&times;</span> 
                    <strong>Error! @ <span id="error-time"></span>  : </strong><span id="error-msg"></span>
                </div> 

                <div class="data-container">
                    <p>
                        <h4><strong>Tank Status</strong></h4><span class="gradient_circle" id="tank-status"></span>
                    </p>
                </div> 

                <div class="data-container">
                    <p>
                        <h4><strong>Sump Status</strong></h4><span class="gradient_circle" id="sump-status"></span>
                    </p>
                </div> 

                <div class="data-container">
                    <p>
                        <h4><strong>Motor Status</strong></h4><span class="gradient_circle"  id="motor-status"></span>
                    </p>
                </div> 

                

                <?php
                    if( $_SESSION["hato-is_admin"] ){
                        echo " 
                            <div class='data-container debug-log'>
                                <p>
                                    <h4><strong>Debug Log</strong></h4><span id='debug-log'>No Log To Display</span>
                                </p>
                            </div> 
                        ";
                    }
                ?>

            </div>
        </section>

        <section class="sensor-datas">
            <div class="container" data-aos="fade-down">
                <div class="section-title">
                    <h2>Pump</h2>
                    <p>Pump Control</p>
                </div>
                <div class="data-container" id="pump" >
                        <h4>
                            <label for="manual-overide" ><strong>Pump Manual Overide&nbsp;:&nbsp;</strong></label>
                            <input type="checkbox" class="check-input" id="manual-overide" onchange="handelPumpManualOveride()">
                        </h4>
                    

                    <label class="switch" onclick="elementDisabledError()">
                        <input type="checkbox" id="togBtn" onchange="handelToggleButton()">
                        <div class="slider round" id="togBtn-slider">
                            <span class="on">ON</span>
                            <span class="off">OFF</span>
                        </div>
                    </label>

                    <p>
                        <label for="complete-control" onclick="elementDisabledError()">Take Over Complete Control&nbsp;:&nbsp;</label>
                        <input type="checkbox" id="complete-control" onchange="handelCompleteControl()">
                    </p>

                </div>
            </div>
        </section>

        <footer id="footer">
            <div class="footer-top">
                <div class="container">
                    <div class="row justify-content-center">
                        <div class="col-lg-3 col-md-6 footer-links">
                            <h4>Tank & Sump Information</h4>
                            <ul>
                                <li><i class="gradient_circle"></i> <a href="#sensorData"> Loding Data </a> </li>
                                <li><i class="red_circle"></i> <a href="#sensorData"> Water level is <strong> Low </strong> </a> </li>
                                <li><i class="yellow_circle"></i> <a href="#sensorData"> Water level is <strong> Above Low Level </strong> </a> </li>
                                <li><i class="orange_circle"></i> <a href="#sensorData"> Water level is <strong> Above Mid Level </strong> </a> </li>
                                <li><i class="green_circle"></i> <a href="#sensorData"> Water level is <strong> Above High Level </strong> </a> </li>
                            </ul>
                        </div>
    
                        <div class="col-lg-3 col-md-6 footer-links">
                            <h4>Motor Information</h4>
                            <ul>
                                <li><i class="gradient_circle"></i> <a href="#sensorData"> Loding Data </a> </li>
                                <li><i class="red_circle"></i> <a href="#sensorData"> Motor is <strong> OFF </strong> </a> </li>
                                <li><i class="green_circle"></i> <a href="#sensorData"> Motor is <strong> ON </strong> </a> </li>
                            </ul>
                        </div>
    
                        <div class="col-lg-3 col-md-12 footer-links">
                            <h4>Data Load Information</h4>
                            <ul>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Data is refreshed every 40 seconds</a></li>
                                <li><i class="bx bx-wifi-1"></i> <a href="#">Under complete control you should not switch the tab/window. In case of switch the ' Pump Manual Overide ' will turned off.</a></li>
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
        <script src="Assets/vendor/owl.carousel/owl.carousel.min.js"></script>
        <script src="Assets/vendor/isotope-layout/isotope.pkgd.min.js"></script>
        <script src="Assets/vendor/venobox/venobox.min.js"></script>
        <script src="Assets/vendor/waypoints/jquery.waypoints.min.js"></script>
        <script src="Assets/vendor/counterup/counterup.min.js"></script>
        <script src="Assets/vendor/aos/aos.js"></script>
        <script src="Assets/js/main.js"></script>
        <script src="Assets/js/homeautomation_information.js"></script>

    </body>
</html>
