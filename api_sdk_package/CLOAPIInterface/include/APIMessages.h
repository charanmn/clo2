#pragma once
#include <string>

using namespace std;

// Javascript console message to CLO 
const string _CLO_MESSAGE_START				= "CLO_MESSAGE_START";			// header: notify CLO that commands and/or messages start
const string _CLO_MESSAGE_END				= "CLO_MESSAGE_END";			// footer: notify CLO that commands and/or messages end

/* example in JS to send message[0] ~ message[n] to CLO via console.log(..) function.
   this example code would parse 'console.log(..)' into 
   'n' for args, 
   messaages[0]~[n] for char**  
   inside callbackfunc(int args, char** argv) in plug-in dll; 

<!DOCTYPE html>
<html>
<head>
<script>
function myFunction()
{
console.log('CLO_MESSAGE_START \n message[0] \n message[1] \n .. message[n] \n CLO_MESSAGE_END');
}
</script>
</head>

<body>

<button onclick="myFunction()">Try it</button>

<p>By clicking the button above, a function will be called. The function will alert a message.</p>

</body>
</html>

*/