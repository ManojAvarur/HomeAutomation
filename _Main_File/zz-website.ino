String getWebsite(){
    return " <!DOCTYPE html>  <html lang='en'>     <head>       <meta charset='UTF-8'>       <meta http-equiv='X-UA-Compatible' content='IE=edge'>        <meta name='viewport' content='width=device-width, initial-scale=1.0'>       <title>HOMEATO</title>            <style>          /*           * Green: #97cb6a             * Dark Green: #698b49            * Black: #040404             */           *{              margin: 0;               padding: 0;              box-sizing: border-box;              font-family:'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;          }                     a{               text-decoration: none;               color: black;            }                     h1, h2, h3, h4, h5, h6{              text-transform: capitalize;              margin-bottom: 0.75rem;          }                     .container{              max-width: 80vw;                 margin: auto;            }                     .mx-1{ margin: 0 1rem }          .mx-2{ margin: 0 2rem }          .mx-3{ margin: 0 3rem }          .mx-4{ margin: 0 4rem }          .mx-5{ margin: 0 5rem }                   .my-1{ margin: 1rem 0}           .my-2{ margin: 2rem 0}           .my-3{ margin: 3rem 0}           .my-4{ margin: 4rem 0}           .my-5{ margin: 5rem 0}                    .mxy-1{ margin: 1rem }           .mxy-2{ margin: 2rem }           .mxy-3{ margin: 3rem }           .mxy-4{ margin: 4rem }           .mxy-5{ margin: 5rem }                    .btn {               border: 2.5px solid #698b49;                 border-radius: 5px;              padding: 0.5rem 1rem;                margin: 0.75rem;                 display: inline-block;               text-align: center;              color: #fff;             }                     .btn:hover,                  .btn:focus-visible{              background: #698b49;                 color: #040404 ;                 border: 2.5px solid #698b49 ;            }                     .logo{               text-transform: uppercase;               display: inline-block;               font-size: 1.75rem;              padding: 0.8rem 0;               text-align: center;              color: #fff;                 margin: 0.3rem ;                 font-weight: 600;                letter-spacing: 2px;             }                     nav .btn{                float: right;                margin: 1rem;            }                     nav{                 background: rgba( 0, 0, 0, 0.8);                 overflow: hidden;            }                     nav div > :first-child span {                color: #698b49;          }                     .title h1{               font-size: 1.75rem;              text-transform: uppercase;           }                     .title h4{               text-transform: uppercase;           }                     h4::after{               content: '';                 width: 7rem;                 height: 0.12rem;                 display: inline-block;               background-color: #698b49;               margin: 0.25rem;             }                     #Sensor-Data .grid-items{                display: grid;               grid-template-columns: 1fr 1fr 1fr;              place-items: center;                 margin: 1.5rem;              padding: 0.5rem;             }                     #Sensor-Data .grid-items .grid{              border: 1px solid rgba(0, 0, 0, 0.2);                border-radius: 10px;                 margin: 0.5rem;              padding: 0.75rem;                width: 24vw;                 text-align: center;          }                     #Sensor-Data .Debug-log,             #Manual-Pump .Pump-override{                 border: 1px solid rgba(0, 0, 0, 0.2);                border-radius: 10px;                 margin: 2.5rem;              padding: 1rem 0;                 text-align: center;              display: block;          }                     #Sensor-Data .container .grid-items .grid h2::after,             .Debug-log h2:after,             #Manual-Pump .Pump-override h2::after{               content: '';                 width: 80px;                 height: 10px;                display: block;              margin: auto;                margin-bottom: 20px;                 border-bottom: 1.5px solid #698b49;          }                     .toggle {                position: relative;              display: block;              width: 95px;                 height: 32px;                padding: 3px;                margin: 0.75rem auto;                border-radius: 50px;                 cursor: pointer;             }                     .toggle-input {              position: absolute;              top: 0;              left: 0;                 opacity: 0;          }                     .toggle-label {              position: relative;              display: block;              height: inherit;                 font-size: .9rem;                background: #882525;                 border-radius: inherit;              box-shadow: inset 0 1px 2px rgba(0, 0, 0, 0.12), inset 0 0 3px               rgba(0, 0, 0, 0.15);             }                     .toggle-label:before,            .toggle-label:after {                position: absolute;              top: 50%;                left: 38%;               color: black;                margin-top: -.5em;               line-height: .855;           }                     .toggle-label:before {               content: attr(data-off);                 /* right: 11px; */               color: #fff;                 text-shadow: 0 1px rgba(0, 0, 0, 0.2);           }                     .toggle-label:after {                content: attr(data-on);              /* left: 11px; */                color: #fff;                 text-shadow: 0 1px rgba(0, 0, 0, 0.2);               opacity: 0;          }                     .toggle-input:checked~.toggle-label {                background: #698b49;             }                     .toggle-input:checked~.toggle-label:before {                 opacity: 0;          }                     .toggle-input:checked~.toggle-label:after {              opacity: 1;          }                     .toggle-handle {                 position: absolute;              top: 6.5px;              left: 6.5px;                 width: 25px;                 height: 25px;                background: linear-gradient(to bottom, #FFFFFF 40%, #f0f0f0);                border-radius: 50%;          }                     .toggle-handle:before {              position: absolute;              top: 50%;                left: 50%;               margin: -6px 0 0 -6px;               width: 16px;                 height: 16px;            }            .toggle-input:checked~.toggle-handle {               left: 64px;              box-shadow: -1px 1px 5px rgba(0, 0, 0, 0.2);             }                     /* Transition*/          .toggle-label,           .toggle-handle {                 transition: All 0.3s ease;               -webkit-transition: All 0.3s ease;               -moz-transition: All 0.3s ease;              -o-transition: All 0.3s ease;            }                     .isDisabled {                color: rgb(152, 143, 129);               cursor: not-allowed;                 opacity: 0.5;                text-decoration: none;           }                                       @media ( max-width: 900px ) {                             #Sensor-Data .grid-items{                    display: grid;                   grid-template-columns: 1fr ;                 }                             #Sensor-Data .grid-items .grid{                  width: 50vw;                 }                 #Sensor-Data .Debug-log,                 #Manual-Pump .Pump-override{                  margin: auto;             }         }                              @media ( max-width: 435px ) {                .container{                  max-width: 100vw;                    margin: 0;               }                             .logo{                   margin-left: 0.5rem;                 }                             #Sensor-Data .grid-items{                    margin: 0.5rem;                  padding: 0.5rem;                 }                             #Sensor-Data .grid-items .grid{                  width: 60vw;                     margin: 0.75rem;                     padding: 0.5rem;                 }                             #Sensor-Data .Debug-log{                     margin: 0;               }            }                  @media ( max-width: 350px ) {             .logo{                 font-size: 1.5rem;             }              nav .btn{                 font-size: 0.9rem;             }         }                  @keyframes rotate-s-loader {                 from {                 transform: rotate(0);              }                to {                   transform: rotate(360deg);                 }            }                     .gradient_circle,            .red_circle,             .yellow_circle,          .orange_circle,          .green_circle{               height: 25px;                width: 25px;                 display: inline-block;               border-radius: 100vw;                margin: 0.75rem;                 padding: 0.75rem;                display: inline-block;               transition: ease-in;                              animation-name: rotate-s-loader;                 animation-iteration-count: infinite;                 animation-duration: 1s;              animation-timing-function: linear;           }                     .gradient_circle{                background:  linear-gradient( 217deg, rgba(255, 0, 0), rgba(0, 128, 0, .8) 70.71% ),linear-gradient( 127deg, rgba(255, 255, 0), rgba(255, 166, 0, .8) 70.71% ), linear-gradient( 336deg, rgba(255, 166, 0), rgba(255, 0, 0, .8) 70.71% );            }                     .red_circle{                 background-color: rgb(255, 0, 0);            }                     .yellow_circle{              background-color: rgb(255, 255, 0);          }                     .orange_circle{              background-color: rgb(255, 166, 0);          }                     .green_circle{               background-color: rgb(0, 128, 0);            }        </style>              <script>             const connectionUrl = `ws://${window.location.host}:81/`;         let ws = new WebSocket(connectionUrl);                   let tankStatus, sumpStatus, motorStatus, debugLog, manualOverideCheckbox, manualOverideController;            function onChangeOverideCheckbox( event ){             if( manualOverideCheckbox.checked ){                 manualOverideController.disabled = false;                 manualOverideController.parentElement.className =  `toggle`;                 } else {                 manualOverideController.checked = false;                 manualOverideController.disabled = true;                 manualOverideController.parentElement.className =  `toggle isDisabled`;                 }         }                  function loadElements(){                 tankStatus = document.getElementById(`tank-status`);                 sumpStatus = document.getElementById(`sump-status`);                 motorStatus = document.getElementById(`motor-status`);               debugLog = document.getElementById(`debug-log`);                 manualOverideCheckbox = document.getElementById(`manual-overide-checkbox`);              manualOverideController = document.getElementById(`manual-overide-controller`);               manualOverideCheckbox.addEventListener('change', onChangeOverideCheckbox);         }                  ws.onopen = function(){              fetch(`/initial-message`)                .then( res => res.text() )             .then( textRes => {                  ws.onmessage({ data: textRes });                 manualOverideCheckbox.disabled = false;                  document.getElementById('Manual-Pump').style.display = 'block';             })               .catch( error => {                   console.error(`Error occurred while initiaing the first message`);                   console.log( error );             });                console.log(`Connection establised`);            };                   ws.onmessage = function( event ){                const levelIndicators = {                    '-1': 'gradient_circle',                     '0': 'red_circle',                   '1': 'yellow_circle',                    '2': 'orange_circle',                     '3': 'green_circle',                     '4': 'green_circle',                     'motor': {                       '-1': 'gradient_circle',                         '0': 'red_circle',                       '1': 'green_circle'                      }                };                            event = JSON.parse( event.data );                             tankStatus.className = levelIndicators[ event.status.tank ] || levelIndicators['-1'];                sumpStatus.className = levelIndicators[ event.status.sump ] || levelIndicators['-1'];                motorStatus.className = levelIndicators.motor[ event.status.motor.displayState ] || levelIndicators['-1'] ;                               if( event.debug.display ){                   debugLog.style.display = `block`;                    debugLog.children[1].innerText = event.debug.log;                } else {                     debugLog.style.display = `none`;                     debugLog.children[1].innerText = `NO DEBUG LOG TO DISPLAY`;              }                             if( manualOverideCheckbox.checked && event.status.motor.isOnlineControlled ){                 manualOverideCheckbox.checked = false;                 alert('Motor is controlled by one of your family member!');             }              if( event.status.motor.isControlled ){                 manualOverideCheckbox.checked = true;                 manualOverideController.checked = event.status.motor.state;             } else {                 manualOverideCheckbox.checked = false;             }              onChangeOverideCheckbox();         };                    ws.onerror = function( event ){              console.error(`Error occurred in sending/fetching data through sockets`);            };                     ws.onclose = function(){                 console.log(`Connection closed`);                setTimeout( () => window.location.reload(), 3000 );         };                       function motorController(){               onChangeOverideCheckbox();             ws.send(JSON.stringify({ isBeingControlled: manualOverideCheckbox.checked, state: manualOverideController.checked }));             };                 </script>    </head>       <body onload='loadElements()'>       <header>             <nav>                <div class='container'>                  <a class='logo' href='#'>HOME<span>ATO</span></a>                    <a class='btn' href='/alter-wifi-credentials'>Wi-Fi Credentials</a>                </div>           </nav>       </header>             <section id='Sensor-Data' class='mxy-2'>             <div class='container'>              <div class='title'>                  <h4>Sensor</h4>                  <h1>Sensor Data</h3>                 </div>                            <div class='grid-items'>                     <div class='grid'>                       <h2>Tank Status</h2>                         <span class='gradient_circle' id='tank-status'></span>                   </div>                   <div class='grid'>                       <h2>Sump Status</h2>                         <span class='gradient_circle' id='sump-status'></span>                   </div>                   <div class='grid'>                       <h2>Motor Status</h2>                        <span class='gradient_circle' id='motor-status'></span>                  </div>               </div>                            <div class='Debug-log' id='debug-log' style='display: none;'>                    <h2>Debug Log</h2>                   <p>NO DEBUG LOG TO DISPLAY</p>               </div>                        </div>       </section>            <section id='Manual-Pump' class='mxy-2' style='display: none;'>             <div class='container'>              <div class='title'>                  <h4>Pump</h4>                    <h1>Pump Control</h3>                </div>                        <div class='Pump-override'>                  <h2>Manual Pump Override</h2>                    <h3>                         <label for='manual-overide-checkbox'><strong>Pump Manual Overide&nbsp;:&nbsp;</strong></label>                       <input type='checkbox' class='check-input' id='manual-overide-checkbox' data-type='checkbox' onclick='motorController(event)' disabled>                   </h3>                                 <div class='mxy1'>                   <label class='toggle isDisabled'>                        <input class='toggle-input' type='checkbox' id='manual-overide-controller' data-type='contoller' onclick='motorController(event)' disabled/>                         <span class='toggle-label' data-off='OFF' data-on='ON'></span>                       <span class='toggle-handle'></span>                  </label>                 </div>           </div>                         </section>            </body>  </html> ";
}