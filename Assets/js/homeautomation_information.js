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

        if( sensorData.debug_log !== undefined ){
            debugLogDisplay.innerText = sensorData.debug_log;
        }

        if( displayWarningContainer.style.display === "block" && displayWarningMessage.innerText === "Couldn't load the data.\nPlease wait for 5 seconds, we will try to retrive your data" ){
            closeShowWarning();
        }
    }) 
    .catch( error => {
  
        showWarning({ type:"Note!", message:"Couldn't load the data.\nPlease wait for 5 seconds, we will try to retrive your data" });
        
    })
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
    if( ! toggleButton.disabled ){
        if( toggleButton.checked ){
            toggleButtonContainer.style.backgroundColor = switchOnColor;
        } else{
            toggleButtonContainer.style.backgroundColor = switchOffColor;
        }
        toggleButtonContainer.classList.remove("isDisabled");
    } else {
        toggleButtonContainer.style.backgroundColor = disabledColor;
        toggleButtonContainer.classList.add("isDisabled");
    }
}

function handelToggleButton(){
    performToggleSwitchAndControlOP();
}


function handelPumpManualOveride(){
    if( manualOverideCheckBox.checked ){
        toggleButton.disabled = false;
        completeControl.disabled = false;
        completeControl.classList.remove("isDisabled");
    } else {
        toggleButton.checked = false;
        toggleButton.disabled = true;
        completeControl.disabled = true;
        completeControl.checked = false;
        completeControl.classList.add("isDisabled");
    }
    performToggleSwitchAndControlOP();
}

function elementDisabledError(){
    if( completeControl.disabled || toggleButton.disabled ){
        showError("Selected option is disabled because ' Pump Manual Overide ' is not checked.");
    }
}