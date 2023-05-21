const fs = require('fs');

let data = fs.readFileSync('C:\\xampp\\htdocs\\HomeAutomation\\New\\HomeAutomation\\Unwanted\\LocalServer\\localServer.html')
let newStr = "";

data.toString().split('\n').forEach( elm => {
    let quote = '\"';

    let newElm = elm.replace('"', '\\"');
    newElm = newElm.replace('\r', '');
    newElm = newElm.replace('\t', '' );

    newStr += ' ' + newElm ;
})

fs.writeFileSync('C:\\xampp\\htdocs\\HomeAutomation\\New\\HomeAutomation\\Unwanted\\LocalServer\\localServerCompressed.html', newStr )