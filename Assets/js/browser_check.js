
// var isOpera = (!!window.opr && !!opr.addons) || !!window.opera || navigator.userAgent.indexOf(' OPR/') >= 0;

// // Firefox 1.0+
// var isFirefox = typeof InstallTrigger !== 'undefined';

// // Safari 3.0+ "[object HTMLElementConstructor]" 
// var isSafari = /constructor/i.test(window.HTMLElement) || (function (p) { return p.toString() === "[object SafariRemoteNotification]"; })(!window['safari'] || (typeof safari !== 'undefined' && window['safari'].pushNotification));

// // Internet Explorer 6-11
// var isIE = /*@cc_on!@*/false || !!document.documentMode;

// Edge 20+
// var isEdge = !isIE && !!window.StyleMedia;

// Chrome 1 - 79
var isChrome = !!window.chrome && (!!window.chrome.webstore || !!window.chrome.runtime);

// Edge (based on chromium) detection
var isEdgeChromium = isChrome && (navigator.userAgent.indexOf("Edg") != -1);

// Blink engine detection
// var isBlink = (isChrome || isOpera) && !!window.CSS;

var isChromium = !!window.chrome;

if(  !( ( isChrome ) ||  ( isEdgeChromium ) ||  ( isChromium ) ) ){
    // window.stop();
    // window.exec("stop");
    document.write("<h1>Browser Not Supported.<br>Supported browsers are Chromium based browsers</h1>");
    // alert( " test " + ! ( isChrome ) ||  ! ( isEdgeChromium ) || ! ( isChromium ) );
    document.execCommand("Stop");
    window.stop();

}
