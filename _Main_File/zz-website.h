const char INDEX_PAGE[] PROGMEM = R"=====(
    <!DOCTYPE html> <html lang='en'> <head> <meta charset='UTF-8'> <meta http-equiv='X-UA-Compatible' content='IE=edge'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>HOMEATO</title> <style> /* * Green: #97cb6a * Dark Green: #698b49 * Black: #040404 */ *{ margin: 0; padding: 0; box-sizing: border-box; font-family:'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; } a{ text-decoration: none; color: black; } h1, h2, h3, h4, h5, h6{ text-transform: capitalize; margin-bottom: 0.75rem; } .container{ max-width: 80vw; margin: auto; } .mx-1{ margin: 0 1rem } .mx-2{ margin: 0 2rem } .mx-3{ margin: 0 3rem } .mx-4{ margin: 0 4rem } .mx-5{ margin: 0 5rem } .my-1{ margin: 1rem 0} .my-2{ margin: 2rem 0} .my-3{ margin: 3rem 0} .my-4{ margin: 4rem 0} .my-5{ margin: 5rem 0} .mxy-1{ margin: 1rem } .mxy-2{ margin: 2rem } .mxy-3{ margin: 3rem } .mxy-4{ margin: 4rem } .mxy-5{ margin: 5rem } .btn { border: 2.5px solid #698b49; border-radius: 5px; padding: 0.5rem 1rem; margin: 0.75rem; display: inline-block; text-align: center; color: #fff; } .btn:hover, .btn:focus-visible{ background: #698b49; color: #040404 ; border: 2.5px solid #698b49 ; } .logo{ text-transform: uppercase; display: inline-block; font-size: 1.75rem; padding: 0.8rem 0; text-align: center; color: #fff; margin: 0.3rem ; font-weight: 600; letter-spacing: 2px; } nav .btn{ float: right; margin: 1rem; } nav{ background: rgba( 0, 0, 0, 0.8); overflow: hidden; } nav div > :first-child span { color: #698b49; } .title h1{ font-size: 1.75rem; text-transform: uppercase; } .title h4{ text-transform: uppercase; } h4::after{ content: ''; width: 7rem; height: 0.12rem; display: inline-block; background-color: #698b49; margin: 0.25rem; } #Sensor-Data .grid-items{ display: grid; grid-template-columns: 1fr 1fr 1fr; place-items: center; margin: 1.5rem; padding: 0.5rem; } #Sensor-Data .grid-items .grid{ border: 1px solid rgba(0, 0, 0, 0.2); border-radius: 10px; margin: 0.5rem; padding: 0.75rem; width: 24vw; text-align: center; } #Sensor-Data .Debug-log, #Manual-Pump .Pump-override{ border: 1px solid rgba(0, 0, 0, 0.2); border-radius: 10px; margin: 2.5rem; padding: 1rem 0; text-align: center; display: block; } #Sensor-Data .container .grid-items .grid h2::after, .Debug-log h2:after, #Manual-Pump .Pump-override h2::after{ content: ''; width: 80px; height: 10px; display: block; margin: auto; margin-bottom: 20px; border-bottom: 1.5px solid #698b49; } .toggle { position: relative; display: block; width: 95px; height: 32px; padding: 3px; margin: 0.75rem auto; border-radius: 50px; cursor: pointer; } .toggle-input { position: absolute; top: 0; left: 0; opacity: 0; } .toggle-label { position: relative; display: block; height: inherit; font-size: .9rem; background: #882525; border-radius: inherit; box-shadow: inset 0 1px 2px rgba(0, 0, 0, 0.12), inset 0 0 3px rgba(0, 0, 0, 0.15); } .toggle-label:before, .toggle-label:after { position: absolute; top: 50%; left: 38%; color: black; margin-top: -.5em; line-height: .855; } .toggle-label:before { content: attr(data-off); /* right: 11px; */ color: #fff; text-shadow: 0 1px rgba(0, 0, 0, 0.2); } .toggle-label:after { content: attr(data-on); /* left: 11px; */ color: #fff; text-shadow: 0 1px rgba(0, 0, 0, 0.2); opacity: 0; } .toggle-input:checked~.toggle-label { background: #698b49; } .toggle-input:checked~.toggle-label:before { opacity: 0; } .toggle-input:checked~.toggle-label:after { opacity: 1; } .toggle-handle { position: absolute; top: 6.5px; left: 6.5px; width: 25px; height: 25px; background: linear-gradient(to bottom, #FFFFFF 40%, #f0f0f0); border-radius: 50%; } .toggle-handle:before { position: absolute; top: 50%; left: 50%; margin: -6px 0 0 -6px; width: 16px; height: 16px; } .toggle-input:checked~.toggle-handle { left: 64px; box-shadow: -1px 1px 5px rgba(0, 0, 0, 0.2); } /* Transition*/ .toggle-label, .toggle-handle { transition: All 0.3s ease; -webkit-transition: All 0.3s ease; -moz-transition: All 0.3s ease; -o-transition: All 0.3s ease; } .isDisabled { color: rgb(152, 143, 129); cursor: not-allowed; opacity: 0.5; text-decoration: none; } @media ( max-width: 900px ) { #Sensor-Data .grid-items{ display: grid; grid-template-columns: 1fr ; } #Sensor-Data .grid-items .grid{ width: 50vw; } #Sensor-Data .Debug-log, #Manual-Pump .Pump-override{ margin: auto; } } @media ( max-width: 435px ) { .container{ max-width: 100vw; margin: 0; } .logo{ margin-left: 0.5rem; } #Sensor-Data .grid-items{ margin: 0.5rem; padding: 0.5rem; } #Sensor-Data .grid-items .grid{ width: 60vw; margin: 0.75rem; padding: 0.5rem; } #Sensor-Data .Debug-log{ margin: 0; } } @media ( max-width: 350px ) { .logo{ font-size: 1.5rem; } nav .btn{ font-size: 0.9rem; } } @keyframes rotate-s-loader { from { transform: rotate(0); } to { transform: rotate(360deg); } } .gradient_circle, .red_circle, .yellow_circle, .orange_circle, .green_circle{ height: 25px; width: 25px; display: inline-block; border-radius: 100vw; margin: 0.75rem; padding: 0.75rem; display: inline-block; transition: ease-in; animation-name: rotate-s-loader; animation-iteration-count: infinite; animation-duration: 1s; animation-timing-function: linear; } .gradient_circle{ background: linear-gradient( 217deg, rgba(255, 0, 0), rgba(0, 128, 0, .8) 70.71% ),linear-gradient( 127deg, rgba(255, 255, 0), rgba(255, 166, 0, .8) 70.71% ), linear-gradient( 336deg, rgba(255, 166, 0), rgba(255, 0, 0, .8) 70.71% ); } .red_circle{ background-color: rgb(255, 0, 0); } .yellow_circle{ background-color: rgb(255, 255, 0); } .orange_circle{ background-color: rgb(255, 166, 0); } .green_circle{ background-color: rgb(0, 128, 0); } </style> <script> const connectionUrl = `ws://${window.location.host}:81/`; let ws = new WebSocket(connectionUrl); let tankStatus, sumpStatus, motorStatus, debugLog, manualOverideCheckbox, manualOverideController; function calculatePercentage({ min, max, value }){ return ( ( value - min ) * 100 ) / ( max - min ); } function onChangeOverideCheckbox( event ){ if( manualOverideCheckbox.checked ){ manualOverideController.disabled = false; manualOverideController.parentElement.className = `toggle`; } else { manualOverideController.checked = false; manualOverideController.disabled = true; manualOverideController.parentElement.className = `toggle isDisabled`; } } function loadElements(){ tankStatus = document.getElementById(`tank-status`); sumpStatus = document.getElementById(`sump-status`); motorStatus = document.getElementById(`motor-status`); debugLog = document.getElementById(`debug-log`); manualOverideCheckbox = document.getElementById(`manual-overide-checkbox`); manualOverideController = document.getElementById(`manual-overide-controller`); manualOverideCheckbox.addEventListener('change', onChangeOverideCheckbox); } ws.onopen = function(){ fetch(`/initial-message`) .then( res => res.text() ) .then( textRes => { ws.onmessage({ data: textRes }); manualOverideCheckbox.disabled = false; document.getElementById('Manual-Pump').style.display = 'block'; }) .catch( error => { console.error(`Error occurred while initiaing the first message`); console.log( error ); }); console.log(`Connection establised`); }; ws.onmessage = function( event ){ const levelIndicators = { '-1': 'gradient_circle', '0': 'red_circle', '1': 'yellow_circle', '2': 'orange_circle', '3': 'green_circle', '4': 'green_circle', 'motor': { '-1': 'gradient_circle', '0': 'red_circle', '1': 'green_circle' } }; event = JSON.parse( event.data ); sumpStatus.className = ``; tankStatus.className = ``; motorStatus.className = levelIndicators[ event.status.motor.displayState ] || levelIndicators.motor['-1']; sumpStatus.innerText = `${calculatePercentage({ min: event.status.sump.maximumLevel, max: event.status.sump.minimumLevel, value: event.status.sump.currentLevel })} %`; tankStatus.innerText = `${calculatePercentage({ min: event.status.tank.maximumLevel, max: event.status.tank.minimumLevel, value: event.status.tank.currentLevel })} %`; if( event.debug.display ){ debugLog.style.display = `block`; debugLog.children[1].innerText = event.debug.log; } else { debugLog.style.display = `none`; debugLog.children[1].innerText = `NO DEBUG LOG TO DISPLAY`; } if( manualOverideCheckbox.checked && event.status.motor.isOnlineControlled ){ manualOverideCheckbox.checked = false; alert('Motor is controlled by one of your family member!'); } if( event.status.motor.isControlled ){ manualOverideCheckbox.checked = true; manualOverideController.checked = event.status.motor.state; } else { manualOverideCheckbox.checked = false; } onChangeOverideCheckbox(); }; ws.onerror = function( event ){ console.error(`Error occurred in sending/fetching data through sockets`); }; ws.onclose = function(){ console.log(`Connection closed`); setTimeout( () => window.location.reload(), 3000 ); }; function motorController(){ onChangeOverideCheckbox(); ws.send(JSON.stringify({ isBeingControlled: manualOverideCheckbox.checked, state: manualOverideController.checked })); }; </script> </head> <body onload='loadElements()'> <header> <nav> <div class='container'> <a class='logo' href='/'>HOME<span>ATO</span></a> <a class='btn' href='/settings'>Settings</a> </div> </nav> </header> <section id='Sensor-Data' class='mxy-2'> <div class='container'> <div class='title'> <h4>Sensor</h4> <h1>Sensor Data</h3> </div> <div class='grid-items'> <div class='grid'> <h2>Tank Status</h2> <span class='gradient_circle' id='tank-status'></span> </div> <div class='grid'> <h2>Sump Status</h2> <span class='gradient_circle' id='sump-status'></span> </div> <div class='grid'> <h2>Motor Status</h2> <span class='gradient_circle' id='motor-status'></span> </div> </div> <div class='Debug-log' id='debug-log' style='display: none;'> <h2>Debug Log</h2> <p>NO DEBUG LOG TO DISPLAY</p> </div> </div> </section> <section id='Manual-Pump' class='mxy-2' style="display: none;"> <div class='container'> <div class='title'> <h4>Pump</h4> <h1>Pump Control</h3> </div> <div class='Pump-override'> <h2>Manual Pump Override</h2> <h3> <label for='manual-overide-checkbox'><strong>Pump Manual Overide&nbsp;:&nbsp;</strong></label> <input type='checkbox' class='check-input' id='manual-overide-checkbox' data-type='checkbox' onclick='motorController(event)' disabled> </h3> <div class='mxy1'> <label class='toggle isDisabled'> <input class='toggle-input' type='checkbox' id='manual-overide-controller' data-type='contoller' onclick='motorController(event)' disabled/> <span class='toggle-label' data-off='OFF' data-on='ON'></span> <span class='toggle-handle'></span> </label> </div> </div> </section> </body> </html> 
)=====";


const char SETTINGS_PAGE[] PROGMEM = R"=====(
    <!DOCTYPE html><html lang='en'><head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Settings</title> <style> /* * Green: #97cb6a * Dark Green: #698b49 * Black: #040404 */ *{ margin: 0; padding: 0; box-sizing: border-box; font-family:'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; } a{ text-decoration: none; color: black; } h1, h2, h3, h4, h5, h6{ text-transform: capitalize; margin-bottom: 0.75rem; } .container{ max-width: 80vw; margin: auto; position: relative; } .mx-1{ margin: 0 1rem } .mx-2{ margin: 0 2rem } .mx-3{ margin: 0 3rem } .mx-4{ margin: 0 4rem } .mx-5{ margin: 0 5rem } .my-1{ margin: 1rem 0} .my-2{ margin: 2rem 0} .my-3{ margin: 3rem 0} .my-4{ margin: 4rem 0} .my-5{ margin: 5rem 0} .mxy-1{ margin: 1rem } .mxy-2{ margin: 2rem } .mxy-3{ margin: 3rem } .mxy-4{ margin: 4rem } .mxy-5{ margin: 5rem } .btn { border: 2.5px solid #698b49; border-radius: 5px; padding: 0.5rem 1rem; margin: 0.75rem; display: inline-block; text-align: center; color: #fff; } .btn:hover, .btn:focus-visible{ background: #698b49; color: #040404 ; border: 2.5px solid #698b49 ; } .logo{ text-transform: uppercase; display: inline-block; font-size: 1.75rem; padding: 0.8rem 0; text-align: center; color: #fff; margin: 0.3rem ; font-weight: 600; letter-spacing: 2px; } nav .btn{ float: right; margin: 1rem; } nav{ background: rgba( 0, 0, 0, 0.8); overflow: hidden; } nav div > :first-child span { color: #698b49; } .title h1{ font-size: 1.75rem; text-transform: uppercase; } .title h4{ text-transform: uppercase; } h4::after{ content: ''; width: 7rem; height: 0.12rem; display: inline-block; background-color: #698b49; margin: 0.25rem; } .isDisabled { color: rgb(152, 143, 129); cursor: not-allowed; opacity: 0.5; text-decoration: none; } .title h1{ font-size: 1.75rem; text-transform: uppercase; } .title h4{ text-transform: uppercase; } form{ max-width: 1110px; margin: auto; } label{ margin-bottom: 10px; font-weight: 700; letter-spacing: 5px; margin-left: 20px; font-size: 1.2rem; } label::after{ content: ''; width: 2px; height: 1rem; display: inline-block; background-color: #698b49; /* margin: 0.25rem; */ } #wifi-data form{ display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: 1fr; grid-template-areas: 'ssid password' 'submit submit'; align-items: center; column-gap: 10px; } #wifi-data form div.form-group-1{ grid-area: ssid; } #wifi-data form div.form-group-2{ grid-area: password; } #wifi-data form div.form-group-3{ grid-area: submit; margin: auto; } #sump-sensor-data form, #tank-sensor-data form{ display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: 1fr 1fr 1fr; align-items: center; column-gap: 10px; grid-template-areas: 'low high' 'new new' 'submit submit' ; } #sump-sensor-data form div.form-group-1, #tank-sensor-data form div.form-group-1{ grid-area: low; } #sump-sensor-data form div.form-group-2, #tank-sensor-data form div.form-group-2{ grid-area: high; } #sump-sensor-data form div.form-group-3, #tank-sensor-data form div.form-group-3{ grid-area: submit; margin: auto; } #sump-sensor-data form div.form-group-4, #tank-sensor-data form div.form-group-4{ grid-area: new; margin: auto; } #sump-sensor-data form input, #tank-sensor-data form input, #wifi-data form input[type=text], #wifi-data form input[type=password]{ font-size: 1.2em; border-radius: 5rem; letter-spacing: .2rem; font-weight: bold; padding: 1rem; transition: all 0.2s; } #wifi-data form input[type=text]:focus, #wifi-data form input[type=password]:focus{ border-color: #698b49; } #sump-sensor-data form input[type=submit], #tank-sensor-data form input[type=submit], #tank-sensor-data form input[type=button], #sump-sensor-data form input[type=button], #wifi-data form input[type=submit], #captureData, #commit-data{ font-size: 1em; border-radius: 5rem; letter-spacing: .2rem; font-weight: bold; padding: 1rem; transition: all 0.2s; color: #698b49; cursor: pointer; } #sump-sensor-data form input[type=submit]:hover, #sump-sensor-data form input[type=submit]:focus, #sump-sensor-data form input[type=button]:hover, #sump-sensor-data form input[type=button]:focus, #tank-sensor-data form input[type=submit]:hover, #tank-sensor-data form input[type=submit]:focus, #tank-sensor-data form input[type=button]:hover, #tank-sensor-data form input[type=button]:focus, #wifi-data form input[type=submit]:hover, #wifi-data form input[type=submit]:focus, #captureData:hover, #captureData:focus, #commit-data:hover, #commit-data:focus{ color: #040404; } #sump-sensor-data form div, #tank-sensor-data form div, #wifi-data form div{ display: inherit; } /* Model Style */ .modal { display: none; /* Hidden by default */ position: fixed; /* Stay in place */ z-index: 0; /* Sit on top */ padding-top: 100px; /* Location of the box */ left: 0; top: 0; width: 100%; /* Full width */ height: 100%; /* Full height */ overflow: auto; /* Enable scroll if needed */ background-color: rgb(0,0,0); /* Fallback color */ background-color: rgba(0,0,0,0.8); /* Black w/ opacity */ } /* Modal Content */ .modal-content { background-color: #fefefe; margin: auto; padding: 20px; border: 1px solid #888; width: 80%; margin-top: 25vh; } /* The Close Button */ .close { color: #aaaaaa; float: right; font-size: 28px; font-weight: bold; } .close:hover, .close:focus { color: #698b49; text-decoration: none; cursor: pointer; } .modal .wrapper{ display: inline-flex; background: #fff; height: 100px; width: 400px; align-items: center; justify-content: space-evenly; border-radius: 5px; padding: 20px 15px; box-shadow: 5px 5px 30px rgba(0,0,0,0.2); } .modal .wrapper{ display: flex; margin: auto; margin-bottom: 20px; } .modal .wrapper .option{ background: #fff; height: 100%; width: 100%; display: flex; align-items: center; justify-content: space-evenly; margin: 0 10px; border-radius: 5px; cursor: pointer; padding: 0 10px; border: 2px solid lightgrey; transition: all 0.3s ease; } .modal .wrapper .option .dot{ height: 20px; width: 20px; background: #d9d9d9; border-radius: 50%; position: relative; } .modal .wrapper .option .dot::before{ position: absolute; content: ''; top: 4px; left: 4px; width: 12px; height: 12px; background: #698b49; border-radius: 50%; opacity: 0; transform: scale(1.5); transition: all 0.3s ease; } .modal .modal-content .wrapper input[type='radio']{ display: none; } .modal .modal-content .wrapper #low:checked:checked ~ .low, .modal .modal-content .wrapper #high:checked:checked ~ .high{ border-color: #698b49; background: #698b49; } .modal .modal-content .wrapper #low:checked:checked ~ .low .dot, .modal .modal-content .wrapper #high:checked:checked ~ .high .dot{ background: #fff; } .modal .modal-content .wrapper #low:checked:checked ~ .low .dot::before, .modal .modal-content .wrapper #high:checked:checked ~ .high .dot::before{ opacity: 1; transform: scale(1); } .modal .wrapper .option span{ font-size: 20px; color: #808080; } .modal .modal-content .wrapper #low:checked:checked ~ .low span, .modal .modal-content .wrapper #high:checked:checked ~ .high span{ color: #fff; } #captureData{ margin-top: 50px; display: block; margin: auto; } /* Spinner */ @keyframes spinner { to {transform: rotate(360deg);} } #spinner:before { content: ''; box-sizing: border-box; position: absolute; top: 50%; left: 50%; width: 100px; height: 100px; margin-top: -10px; margin-left: -30px; border-radius: 50%; border: 3px solid #ccc; border-top-color: #698b49; animation: spinner .6s linear infinite; z-index: 5; } #spinner{ position: fixed; width: 100vw; top: -10%; height: 110vh; background-color: rgba(0, 0, 0, 0.9); z-index: 1; } @media ( max-width: 435px ) { .container{ max-width: 100vw; margin: 0; } .logo{ margin-left: 0.5rem; } } @media ( max-width: 350px ) { .logo{ font-size: 1.5rem; } nav .btn{ font-size: 0.9rem; } } @media ( max-width: 1223px ){ #wifi-data form{ grid-template-columns: 1fr 1fr; grid-template-rows: 1fr 1fr ; grid-template-areas: 'ssid password' 'submit submit' ; } #sump-sensor-data form div.form-group-3, #tank-sensor-data form div.form-group-3, #wifi-data form div.form-group-3{ margin: auto; min-width: 30%; } } @media ( max-width: 780px ) { #wifi-data form{ grid-template-columns: 1fr; grid-template-rows: 1fr 1fr 1fr ; grid-template-areas: 'ssid' 'password' 'submit' ; } label{ margin-top: 15px; } #sump-sensor-data form, #tank-sensor-data form{ grid-template-columns: 1fr; grid-template-rows: 1fr 1fr 1fr 1fr; grid-template-areas: 'low' 'high' 'new' 'submit' ; } } @media ( max-width: 550px ) { .modal .wrapper{ flex-direction: column; height: 175px; width: 150px; } .btn[data-capturefrom=Tank], .btn[data-capturefrom=Sump]{ font-size: 15px !important; letter-spacing: 1px !important; } } </style> <script> class SpinnerHandler{ _spinnerElement; constructor(){ this._spinnerElement = document.getElementById('spinner'); }; showSpinner(){ this._spinnerElement.removeAttribute('hidden'); }; hideSpinner(){ this._spinnerElement.setAttribute('hidden', ""); }; } </script> </head><body onload="fetchCurrentData()"> <div id="spinner" hidden></div> <header> <nav> <div class='container'> <a class='logo' href='/'>HOME<span>ATO</span></a> <a class='btn' href='/'>Home</a> </div> </nav> </header> <main> <div class='container'> <section id='wifi-data' class='mxy-2'> <div class='title'> <h4>Wi-Fi</h4> <h1>Wi-Fi Credentials</h3> </div> <form action='/update-wifi-cred' method='post'> <div class='form-group-1'> <label for='ssid'>SSID</label> <input type='text' id='ssid' name='ssid' placeholder='WiFi Name' required> </div> <div class='form-group-2'> <label for='password'>Password</label> <input type='password' id='password' name='password' placeholder='Password' required> </div> <div class='form-group-3'> <input class='btn' type='submit' value='Submit Locally'> </div> </form> </section> <section id='tank-sensor-data' class='mxy-2'> <div class='title'> <h4>Sensor Calibration</h4> <h1>Tank Sensor</h3> </div> <form action='/update-tank-sensor' method='post'> <div class='form-group-1'> <label for='tlow'>Low</label> <input type='number' id='tlow' name='tlow' placeholder='Tank Low' required> </div> <div class='form-group-2'> <label for='ssid'>High</label> <input type='number' id='thigh' name='thigh' placeholder='Tank High' required> </div> <div class='form-group-3'> <input class='btn' type='submit' value='Submit Locally'> </div> <div class='form-group-4'> <input class='btn' data-capturefrom='Tank' onclick='displayModel(event)' name='captureCurrentTank' type='button' value='Capture Current Sensor Data'> </div> </form> </section> <section id='sump-sensor-data' class='mxy-2'> <div class='title'> <h1>Sump Sensor</h3> </div> <form action='/update-sump-sensor' method='post'> <div class='form-group-1'> <label for='slow'>Low</label> <input type='number' id='slow' name='slow' placeholder='Sump Low' required> </div> <div class='form-group-2'> <label for='shigh'>High</label> <input type='number' id='shigh' name='shigh' placeholder='Sump High' required> </div> <div class='form-group-3'> <input class='btn' type='submit' value='Submit Locally'> </div> <div class='form-group-4'> <input class='btn' data-capturefrom='Sump' onclick='displayModel(event)' name='captureCurrentSump' type='button' value='Capture Current Sensor Data'> </div> </form> </section> <section id='' class='mxy-2'> <div class='title'> <h4>Commit Data</h4> <h1>Store Data Permanently</h3> </div> <form action='/commit-data' method='post' onsubmit='javascript:return confirm(`Do you want to permanently store the data?`)'> <input class='btn' id='commit-data' type='submit' value='Store Data Permanently' style='margin: auto; display: block;'> </form> </section> </div> <div class='water-wave'> <svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 1440 320'> <path fill='#698b49' fill-opacity='0.5' d='M0,128L24,112C48,96,96,64,144,80C192,96,240,160,288,160C336,160,384,96,432,85.3C480,75,528,117,576,128C624,139,672,117,720,106.7C768,96,816,96,864,117.3C912,139,960,181,1008,208C1056,235,1104,245,1152,250.7C1200,256,1248,256,1296,224C1344,192,1392,128,1416,96L1440,64L1440,320L1416,320C1392,320,1344,320,1296,320C1248,320,1200,320,1152,320C1104,320,1056,320,1008,320C960,320,912,320,864,320C816,320,768,320,720,320C672,320,624,320,576,320C528,320,480,320,432,320C384,320,336,320,288,320C240,320,192,320,144,320C96,320,48,320,24,320L0,320Z' style='--darkreader-inline-fill: #007acc #698b49;' > </path> </svg> </div> </main> <!-- The Modal --> <div id='myModal' class='modal'> <div class='modal-content'> <span class='close' onclick='javascript:this.parentElement.parentElement.style.display = `none`;'>&times;</span> <h2 style='text-align: center;'><span id='captureFrom'></span> Sensor Data Capture</h2> <div class='wrapper'> <input type='radio' name='sensorLevelSelector' id='low' onclick='handelRadioButtonChange(event)'> <input type='radio' name='sensorLevelSelector' id='high' onclick='handelRadioButtonChange(event)'> <label for='low' class='option low'> <div class='dot'></div> <span>Low</span> </label> <label for='high' class='option high'> <div class='dot'></div> <span>High</span> </label> </div> <input class='btn' type='button' id='captureData' onclick='handelCaptureRequest(event)' value='Capture Data'> </div> </div> <script> const dataCapturePreferences = { Sump: { selected: null }, Tank: { selected: null } }; let wifiSSID, wifiPassword, tankHigh, tankLow, sumpHigh, sumpLow; const spinnerHandler = new SpinnerHandler(); /* * Fetch current data stored in nodemcu */ function fetchCurrentData(){ init(); fetch(`/current-settings`) .then( settings => settings.json() ) .then( userSetting => { dataToDisplay( userSetting ); spinnerHandler.hideSpinner(); }).catch( error => { console.log( error ); alert(`failed to fetch current settings`); /* window.location.href = `/`; */ }); }; /* * Used to display model and also pre populates model with Capture from data and Selected Radio button data */ function displayModel(event){ const captureFrom = event.target.dataset.capturefrom; document.getElementById(`captureFrom`).innerText = captureFrom; document.getElementById(`captureData`).dataset[`capturefrom`] = captureFrom; document.querySelectorAll(`[name=sensorLevelSelector]`).forEach( elem => { elem.dataset[`capturefrom`] = captureFrom; elem.checked = dataCapturePreferences[captureFrom].selected === elem.id; }); document.getElementById(`myModal`).style.display = `block`; }; /* * Updates the global variable with current selected radio button with respect to ( Sump \ Tank ) */ function handelRadioButtonChange(event){ const captureFrom = event.target.dataset.capturefrom; dataCapturePreferences[captureFrom].selected = event.target.id; }; async function handelCaptureRequest(event){ const captureFrom = event.target.dataset.capturefrom; const requestPayload = { captureFrom, sensorLevelSelector: `` }; document.querySelectorAll(`[name=sensorLevelSelector]`).forEach( el => { if( requestPayload.sensorLevelSelector ){ return null; } requestPayload.sensorLevelSelector = ( el.checked )? el.id : null; }); if( !requestPayload.sensorLevelSelector ){ alert(`Please select level for which the data will be assigned to`); return; } spinnerHandler.showSpinner(); try{ const sensorResult = await fetch(`/get-sensor-value`, { method: `POST`, body: JSON.stringify( requestPayload ) } ); if( !sensorResult.ok ){ throw new Error(`An error has occured: ${sensorResult.status}`); } const sensorValue = await sensorResult.json(); switch( captureFrom ) { case `Tank`: if( requestPayload.sensorLevelSelector === `low` && sensorValue.hasOwnProperty(`requestedData`) ){ tankLow.value = sensorValue.requestedData; }; if( requestPayload.sensorLevelSelector === `high` && sensorValue.hasOwnProperty(`requestedData`) ){ tankHigh.value = sensorValue.requestedData; }; break; case `Sump`: if( requestPayload.sensorLevelSelector === `low` && sensorValue.hasOwnProperty(`requestedData`) ){ sumpLow.value = sensorValue.requestedData; }; if( requestPayload.sensorLevelSelector === `high` && sensorValue.hasOwnProperty(`requestedData`) ){ sumpHigh.value = sensorValue.requestedData; }; break; } document.getElementById(`myModal`).style.display = `none`; } catch( error ) { alert(`Failed to fetch selected sensor value`); console.log( error ); } spinnerHandler.hideSpinner(); }; /* * Overrides the sensor value if present in userSettings else holds back value present in HTML element */ function dataToDisplay( userSetting ){ wifiSSID.value = userSetting.wifi.ssid || wifiSSID.value; wifiPassword.value = userSetting.wifi.password || wifiPassword.value; tankLow.value = userSetting.tank.low || tankLow.value; tankHigh.value = userSetting.tank.high || tankHigh.value; sumpLow.value = userSetting.sump.low || sumpLow.value; sumpHigh.value = userSetting.sump.high || sumpHigh.value; }; /* * Initilizes global variables with its coresponding HTML element */ function init(){ wifiSSID = document.getElementById('ssid'); wifiPassword = document.getElementById('password'); tankHigh = document.getElementById('thigh'); tankLow = document.getElementById('tlow'); sumpLow = document.getElementById('slow'); sumpHigh = document.getElementById('shigh'); }; </script></body></html>
)=====";