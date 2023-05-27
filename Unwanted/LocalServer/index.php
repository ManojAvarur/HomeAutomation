<?php
    $defaultIp = "192,168,1,1";
    $maxSearch = 100;
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Searching for local device</title>
    <style>
        h1{
            display:inline-block;
            display: flex;
            justify-content: center;
        }

        svg{
            display: block;
            margin: auto;
            width: 70px;
        }

        h3 span + span{
            color: rgb(0, 128, 0);
        }
    </style>
</head>
<body>
    <h1>Scanning</h1>
    <svg version="1.1" id="L2" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" x="0px" y="0px"
        viewBox="0 0 100 100" enable-background="new 0 0 100 100" xml:space="preserve">
        <circle fill="none" stroke="#000" stroke-width="4" stroke-miterlimit="10" cx="50" cy="50" r="48"/>
        <line fill="none" stroke-linecap="round" stroke="rgb(0, 128, 0)" stroke-width="4" stroke-miterlimit="10" x1="50" y1="50" x2="85" y2="50.5">
        <animateTransform 
            attributeName="transform" 
            dur="2s"
            type="rotate"
            from="0 50 50"
            to="360 50 50"
            repeatCount="indefinite" />
        </line>
        <line fill="none" stroke-linecap="round" stroke="rgb(0, 128, 0)" stroke-width="4" stroke-miterlimit="10" x1="50" y1="50" x2="49.5" y2="74">
        <animateTransform 
            attributeName="transform" 
            dur="15s"
            type="rotate"
            from="0 50 50"
            to="360 50 50"
            repeatCount="indefinite" />
        </line>
    </svg>
    <h3 style="text-align: center;">Location : <span></span><span></span></h3>
</body>
<script>

    async function fetchWithTimeout(resource, options = {}) {
        const { timeout = 2000 } = options;

        const controller = new AbortController();
        const id = setTimeout(() => controller.abort(), timeout);

        const response = await fetch(resource, {
            ...options,
            signal: controller.signal  
        });
        clearTimeout(id);

        return response;
    }

    async function checkEndpoints(){

        for( let i = defaultIp[defaultIpLength - 1]; i <= maxSearch; ++i ){
            defaultIp[defaultIpLength - 1] = i;
            const currentIpSearch = `http://${defaultIp.join('.')}/initial-message`;

            document.querySelector('h3 span').innerText = `${defaultIp.map( ( ips, index ) => ( index < defaultIpLength - 1 )? ips : '' ).join('.')}`;
            document.querySelector('h3 span + span').innerText = `${defaultIp[defaultIpLength - 1]}`;
            try{
                const result = await fetchWithTimeout( currentIpSearch, { timeout: 2000 } );
                const jsonRes = await result.json();
                
                if( 'nodemcu_id' in jsonRes && jsonRes.nodemcu_id ){
                    window.location.href = `http://${defaultIp.join('.')}/`;
                }

            } catch( error ) {
                console.log( error );
            }
            
        }

        document.querySelector('h1').innerText = '';
        document.querySelector('svg').style.display = 'none';
        document.querySelector('h3 span + span').innerText = '';
        document.querySelector('h3 span').innerText = '';
        document.querySelector('h3').style.color = 'red';
        document.querySelector('h3').innerText = 'Motor Controller and your device are not connected to the same WiFi network! Try refreshing the page once connected to the same network';

    }

    let defaultIp = "<?= $defaultIp ?>".split(',').map( elem => parseInt( elem ) );
    const defaultIpLength = defaultIp.length;
    const maxSearch = <?= $maxSearch ?>;

    checkEndpoints();
    
    
</script>
</html>