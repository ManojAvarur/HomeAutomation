function showWarning({ type="Warning!", message }){
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