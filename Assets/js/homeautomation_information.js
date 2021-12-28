function loadSensorData(){
    fetch("handel_request/user/retrive_sensor_data.php")
    .then( result => result.json() )
    .then( sensorData => {

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

        switch( sensorData.sump_status ){
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

        switch( sensorData.motor_status ){
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
async function pumpRelatedOperations(){

    let timeStamp = new Date();
    timeStamp = timeStamp.toISOString().split('T')[0] + ' ' + timeStamp.toTimeString().split(' ')[0];

    let data = {
        pump_manual_overide_request : ( manualOverideCheckBox.checked )? 1 : 0,
        pump_on_off_status : ( toggleButton.checked )? 1 : 0,
        pump_take_over_complete_control : ( completeControl.checked )? 1 : 0,
        time_stamp : timeStamp,
        operation_count : operationCount
    };
    
    let response = await fetch("handel_request/user/moto_control.php", { 
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(data),
    });

    let result = await response.json();

    console.log( result );

    if( result["success"] ){
        if( operationCount == -1 ){
            operationCount = 0;
        } else {
            operationCount = 1;
        }
        return true;
    } else {
        if( result["usedby"] ){
            showError(`Pump controled by ' ${result["usedby"]} '.\nPlease try again after some time!` );
        }
        return false;
    }

}

async function handelCompleteControl(){
    if( completeControl.checked ){
        if( confirm("Are you sure want to take over the automatic execution?") ){
            if( ! await pumpRelatedOperations() ){
                completeControl.checked = !completeControl.checked;
            }
        } else {
            completeControl.checked = false;
        }
    } else {
        if( ! await pumpRelatedOperations() ){
            completeControl.checked = !completeControl.checked;
        }
    }
}

async function handelToggleButton(){
    if( ! await pumpRelatedOperations() ){
        toggleButton.checked = !toggleButton.checked;
    }
    performToggleSwitchAndControlOP();
}


async function handelPumpManualOveride(){
    if( manualOverideCheckBox.checked ){
        if( confirm("Are you sure want to control the pump?") ){
            
            if( await pumpRelatedOperations() ){
                toggleButton.disabled = false;
                completeControl.disabled = false;
                completeControl.classList.remove("isDisabled");
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
    } else {
        toggleButton.checked = false;
        completeControl.checked = false;
        toggleButton.disabled = true;
        completeControl.disabled = true;
        toggleButtonContainer.style.backgroundColor = disabledColor;
        toggleButtonContainer.classList.add("isDisabled");
        toggleButton.classList.add("isDisabled");
    }
}

function elementDisabledError(){
    if( completeControl.disabled || toggleButton.disabled ){
        showError("Selected option is disabled because ' Pump Manual Overide ' is not checked.");
    }
}
