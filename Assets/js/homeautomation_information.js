let switchOnColor = "#689F38";
let switchOffColor = "#aa2e2e";
let disabledColor = "#808080";
let sensorDataLoadIntervalTime = 40000;
let updateTimeToServerIntervalTime = 10000;  
let lastUpdatedTime;
let operationCount = 0;

let timeStampDisplay = document.getElementById("last-updated");

let tankStatusDisplay = document.getElementById("tank-status");
let sumpStatusDisplay = document.getElementById("sump-status");
let motorStatusDisplay = document.getElementById("motor-status");
let debugLogDisplay = document.getElementById("debug-log");

let displayWarningContainer = document.getElementById("warning-container");
let displayWarningType = document.getElementById("warning-type");
let displayWarningMessage = document.getElementById("warning-msg");

let displayErrorContainer = document.getElementById("error-container");
let displayErrorMessage = document.getElementById("error-msg");

let manualOverideCheckBox = document.getElementById("manual-overide");

let toggleButtonContainer = document.getElementById("togBtn-slider");
let toggleButton = document.getElementById("togBtn");

let completeControl = document.getElementById("complete-control");

let scrollToSensorDataViewPoint = document.getElementById("sensorData");

let loadSensorDataInterval = setInterval( () => {
    loadSensorData();
}, sensorDataLoadIntervalTime );

let updateTimeToServerInterval;

function loadSensorData(){
    fetch("handel_request/user/retrive_sensor_data.php")
    .then( result => result.json() )
    .then( sensorData => {

        if( manualOverideCheckBox.checked ){
            if( parseInt( sensorData.pump_manual_overide_data_flag ) != 1 ){
                return true;
            }
        }

        switch( parseInt( sensorData.tank_status ) ){
            case -1 :
            default : 
                tankStatusDisplay.classList.remove( tankStatusDisplay.classList[0] );
                tankStatusDisplay.classList.add( "gradient_circle") ;
            break;

            case 0 :
                tankStatusDisplay.classList.remove( tankStatusDisplay.classList[0] );
                tankStatusDisplay.classList.add( "red_circle") ;
            break;

            case 1 :
                tankStatusDisplay.classList.remove( tankStatusDisplay.classList[0] );
                tankStatusDisplay.classList.add( "yellow_circle") ;
            break;  

            case 2 :
                tankStatusDisplay.classList.remove( tankStatusDisplay.classList[0] );
                tankStatusDisplay.classList.add( "orange_circle") ;
            break;

            case 3 :
            case 4 :
                tankStatusDisplay.classList.remove( tankStatusDisplay.classList[0] );
                tankStatusDisplay.classList.add( "green_circle") ;
            break;
            
        }

        switch( parseInt( sensorData.sump_status ) ){
            case -1 :
            default : 
                sumpStatusDisplay.classList.remove( sumpStatusDisplay.classList[0] );
                sumpStatusDisplay.classList.add( "gradient_circle") ;
            break;

            case 0 :
                sumpStatusDisplay.classList.remove( sumpStatusDisplay.classList[0] );
                sumpStatusDisplay.classList.add( "red_circle") ;
            break;

            case 1 :
                sumpStatusDisplay.classList.remove( sumpStatusDisplay.classList[0] );
                sumpStatusDisplay.classList.add( "yellow_circle") ;
            break;  

            case 2 :
            case 3 :
                sumpStatusDisplay.classList.remove( sumpStatusDisplay.classList[0] );
                sumpStatusDisplay.classList.add( "orange_circle") ;
            break;
        }

        switch( parseInt( sensorData.motor_status ) ){
            case -1 :
            default : 
                motorStatusDisplay.classList.remove( motorStatusDisplay.classList[0] );
                motorStatusDisplay.classList.add( "gradient_circle") ;
            break;

            case 0 :
                motorStatusDisplay.classList.remove( motorStatusDisplay.classList[0] );
                motorStatusDisplay.classList.add( "red_circle") ;
            break;

            case 1 :
                motorStatusDisplay.classList.remove( motorStatusDisplay.classList[0] );
                motorStatusDisplay.classList.add( "green_circle") ;
            break;  
        }

        let retrivedTimeStamp = new Date( sensorData.time_stamp );
        let currentTimeStamp = new Date();
        if( retrivedTimeStamp.getDate() == currentTimeStamp.getDate() && retrivedTimeStamp.getMonth() == currentTimeStamp.getMonth() && retrivedTimeStamp.getFullYear() == currentTimeStamp.getFullYear() ){
            let hours = parseInt( ( ( currentTimeStamp.getTime() - retrivedTimeStamp.getTime() ) / ( 1000 * 60 * 60 ) ) % 24 );
            if( hours > 0 ){
                timeStampDisplay.innerText = `${hours} hour ago.`
            } else {
                let mins = parseInt( ( ( currentTimeStamp.getTime() - retrivedTimeStamp.getTime() ) / ( 1000 ) ) / 60 );
                if( mins > 0 ){
                    timeStampDisplay.innerText = `${mins} min ago.`
                } else {
                    let secs = parseInt( ( ( currentTimeStamp.getTime() - retrivedTimeStamp.getTime() ) / 1000 ) % 60 );
                    timeStampDisplay.innerText = `${secs} sec ago.`
                }
            }
        } else {
            timeStampDisplay.innerText = `${( currentTimeStamp.getDate() - retrivedTimeStamp.getDate() )} days ago.`;
        }

        if( sensorData.debug_log !== undefined ){
            debugLogDisplay.innerText = sensorData.debug_log;
        }

        if( displayWarningMessage.innerText === "Couldn't load the data.\nPlease wait for 5 seconds, we will try to retrive your data" ){
            closeShowWarning();
        }
    }) 
    .catch( error => {
        if( displayWarningContainer.style.display !== "block" ){
            showWarning({ type:"Note!", message:"Couldn't load the data.\nPlease wait for 5 seconds, we will try to retrive your data" });
        }
    })
}

// Check for succesfull delete query
async function pumpRelatedOperations( overRideOperationCount = operationCount ){

    let timeStamp = new Date();
    timeStamp = timeStamp.toISOString().split('T')[0] + ' ' + timeStamp.toTimeString().split(' ')[0];

    let data = {
        pump_manual_overide_request : ( manualOverideCheckBox.checked )? 1 : 0,
        pump_on_off_status : ( toggleButton.checked )? 1 : 0,
        pump_take_over_complete_control : ( completeControl.checked )? 1 : 0,
        time_stamp : timeStamp,
        operation_count : overRideOperationCount
    };
    
    let response = await fetch("handel_request/user/moto_control.php", { 
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(data),
    });

    let result = await response.json();

    // console.log( result );

    if( result["success"] && result["affected_rows"] > 0 ){
        operationCount = ( overRideOperationCount == -1 ) ? 0 : 1;
        return true;
    } else {
        if( result["usedby"] ){
            showError(`Pump controled by ' ${result["usedby"]} '.\nPlease try again after some time!` );
        }
        return false;
    }

}

async function updateTimeToServer(){
    let timeStamp = new Date();
    
    timeStamp = timeStamp.toISOString().split('T')[0] + ' ' + timeStamp.toTimeString().split(' ')[0];

    let response = await fetch( "handel_request/user/update_time.php", {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ timeStamp : timeStamp }),
    });

    if( response.status === 200 ){
        lastUpdatedTime = timeStamp;
    }

    // console.log( await response.json() );
}

async function handelCompleteControl(){
    if( completeControl.checked ){
        if( confirm("Are you sure want to take over the automatic execution?") ){
            if( ! await pumpRelatedOperations() ){
                manualOverideCheckBox.checked = false;
                operationCount = 0;
                showWarning({ message : "' Pump Manual Overide ' is turned off because of an internal server error.\nPlease try again."});
                performToggleSwitchAndControlOP();
            }
        } else {
            completeControl.checked = false;
        }
    } else {
        if( ! await pumpRelatedOperations() ){
            manualOverideCheckBox.checked = false;
            operationCount = 0;
            clearInterval( updateTimeToServerInterval ); 
            showWarning({ message : "' Pump Manual Overide ' is turned off because of an internal server error.\nPlease try again."});
            performToggleSwitchAndControlOP();
        }
    }
}

async function handelToggleButton(){
    if( ! await pumpRelatedOperations() ){
        manualOverideCheckBox.checked = false;
        operationCount = 0;
        clearInterval( updateTimeToServerInterval );
        showWarning({ message : "' Pump Manual Overide ' is turned off because of an internal server error.\nPlease try again."});  
    }
    performToggleSwitchAndControlOP();
}


async function handelPumpManualOveride(){
    if( manualOverideCheckBox.checked ){
        if( confirm("Are you sure want to control the pump?") ){
            
            if( await pumpRelatedOperations() ){

                tankStatusDisplay.classList.remove( tankStatusDisplay.classList[0] );
                tankStatusDisplay.classList.add( "gradient_circle") ;

                sumpStatusDisplay.classList.remove( sumpStatusDisplay.classList[0] );
                sumpStatusDisplay.classList.add( "gradient_circle") ;

                motorStatusDisplay.classList.remove( motorStatusDisplay.classList[0] ) ;
                motorStatusDisplay.classList.add( "gradient_circle") ;

                timeStampDisplay.innerText = "Loading New Data";
                if( debugLogDisplay !== undefined ){
                    debugLogDisplay.innerText = "Loading New Data"
                }

                toggleButton.disabled = false;
                completeControl.disabled = false;
                completeControl.classList.remove("isDisabled");

                updateTimeToServerInterval = setInterval(() => {
                    updateTimeToServer();
                }, updateTimeToServerIntervalTime );

            } else {
                manualOverideCheckBox.checked = false;
                toggleButton.disabled = true;
                completeControl.disabled = true;
                completeControl.classList.add("isDisabled");
            }

        } else {
            manualOverideCheckBox.checked = false;
        }
    } else {
        operationCount = -1;
        if(  await pumpRelatedOperations() ){
            toggleButton.checked = false;
            toggleButton.disabled = true;
            completeControl.disabled = true;
            completeControl.checked = false;
            completeControl.classList.add("isDisabled"); 

            clearInterval( updateTimeToServerInterval );
        } else {
            manualOverideCheckBox.checked = false;
            operationCount = 0;
            clearInterval( updateTimeToServerInterval );
            showWarning({ message : "' Pump Manual Overide ' is turned off because of an internal server error.\nPlease try again."});
        }
    }
    performToggleSwitchAndControlOP();
}

function showWarning({ type="Warning!", message }){
    // closeShowWarning();
    displayWarningType.innerText = type;
    displayWarningMessage.innerText = message;
    displayWarningContainer.style.display = "block";
    scrollToSensorDataViewPoint.scrollIntoView();
}

function closeShowWarning(){
    displayWarningContainer.style.display = "none";
    displayWarningType.innerText = "";
    displayErrorMessage.innerText = "";
}

function showError( errorMsg ){
    displayErrorMessage.innerText = errorMsg;
    displayErrorContainer.style.display = "block";
    scrollToSensorDataViewPoint.scrollIntoView();
}

function performToggleSwitchAndControlOP(){

    if( manualOverideCheckBox.checked ){
        if( toggleButton.checked ){
            toggleButtonContainer.style.backgroundColor = switchOnColor;
        } else{
            toggleButtonContainer.style.backgroundColor = switchOffColor;
        }
        completeControl.disabled = false;
        completeControl.classList.remove("isDisabled");
        toggleButtonContainer.classList.remove("isDisabled");

        if( sensorDataLoadIntervalTime !== 10000 ){
            clearInterval( loadSensorDataInterval );
            sensorDataLoadIntervalTime = 10000;
            loadSensorDataInterval = setInterval( () => {
                loadSensorData();
            }, sensorDataLoadIntervalTime );
        }
    } else {
        toggleButton.checked = false;
        completeControl.checked = false;
        toggleButton.disabled = true;
        completeControl.disabled = true;
        toggleButtonContainer.style.backgroundColor = disabledColor;
        toggleButtonContainer.classList.add("isDisabled");
        toggleButton.classList.add("isDisabled");

        if( sensorDataLoadIntervalTime !== 40000 ){
            clearInterval( loadSensorDataInterval );
            sensorDataLoadIntervalTime = 40000;
            loadSensorDataInterval = setInterval( () => {
                loadSensorData();
            }, sensorDataLoadIntervalTime );
        }
    }
}

function elementDisabledError(){
    if( completeControl.disabled || toggleButton.disabled ){
        showError("Selected option is disabled because ' Pump Manual Overide ' is not checked.");
    }
}

function logout(){
    if( manualOverideCheckBox.checked ){
        if( confirm("On logout ' Pump Manual Overide ' will be turned off.") ){
            location.href = "_headers/logout.php";
        } 
    } else {
        location.href = "_headers/logout.php";
    }
}


window.onload = () => {
    performToggleSwitchAndControlOP();
    loadSensorData();
}

window.onbeforeunload = function(){
    if( manualOverideCheckBox.checked ){
        manualOverideCheckBox.checked = false;
        performToggleSwitchAndControlOP();
        showWarning({
            type : "Note!",
            message : "' Pump Manual Overide ' turned off."
        });
        pumpRelatedOperations( -1 );
        return 'Are you sure you want to leave?';
    }  
};

window.onoffline = () => {
    showWarning({ 
        message: "Connection to our servers has been lost.\nDon't worry you're ' Pump Manual Overide ' will be disabled."
    });
    manualOverideCheckBox.checked = false;
    manualOverideCheckBox.disabled = true;
    manualOverideCheckBox.classList.add("isDisabled");
}

window.ononline = () => {
    showWarning({ 
        message: "You're back online!\nWebpage will be refreshed in 5 seconds"
    });
    setTimeout(() => {
        location.reload();
    }, 5000);
}

document.addEventListener("visibilitychange", ( event )=> {
    if ( document.visibilityState == "visible") {
        loadSensorDataInterval = setInterval( () => {
            loadSensorData();
        }, sensorDataLoadIntervalTime );

    } else {
        clearInterval( loadSensorDataInterval );
        if( ( completeControl.checked ) || ( new Date() - lastUpdatedTime ) > updateTimeToServerIntervalTime ){
            pumpRelatedOperations( -1 );
            manualOverideCheckBox.checked = false;
            performToggleSwitchAndControlOP();
            showWarning({ message : "Pump overide turned off because of inactive tab."});
            clearInterval( updateTimeToServerInterval );
        }
    }
});



// USER : Sensor Data request every 10 secs
// NODE MCU : Sesnsor data update only when changes
// USER : Manual over ride request only when changed
// NODE MCU : user request check and Manual pump overside status check with full control  every 2 secs
// USER : online update only under manual pump overide is set for every 5 secs

// USER : as soon as user check manual over ride wait 5 secs before updating server
