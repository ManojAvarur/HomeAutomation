const fs = require('fs');

let location = 'C:\\xampp\\htdocs\\HomeAutomation\\HomeAutomation - IoT\\Unwanted\\LocalServer\\';


let data = fs.readFileSync(`${location}localServer.html`)
let newStr = "";

data.toString().split('\n').forEach( elm => {
    let newElm = elm.replaceAll('"', '\'');
    newElm = newElm.replace('\r', '');
    newElm = newElm.replace('\t', '' );

    newStr += ' ' + newElm ;
})

fs.writeFileSync(`${location}localServerCompressed.html`, newStr )

















// x = {
//     "nodemcu_id": "4bb7abf6d3782611339eb6fe6326b96b6b4fca3d6f7e16f33367268806c5512c",
//     "status": {
//       "tank": true,
//       "sump": true,
//       "motor": {
//         "displayState": true,
//         "isControlled": false,
//         "state": false
//       }
//     },
//     "debug": {
//       "log": "adfnalfjlqwuefnhlqwenfliqwuenfliquwehfhnqlwiuefh qlciwuefliquwefilqwelifql",
//       "display": false
//     },
//     "https://iotdesignpro.com/projects/real-time-data-transfer-between-two-esp32-using-websocket-client-on-arduino-ide": ""
//   }

//   const datad = {
//     "status":{
//         "tank":1,
//         "sump":1,
//         "motor":{
//             "isControlled":false,
//             "state":false,
//             "displayState":1
//         }
//     },
//     "debug":{
//         "display":false,
//         "log":""
//     }
// };