Flight Simulator Interpreter
---
The porpuse of the project in the attacheted link is to interpret a special programming languege that has been written in order of controlling and flying the flight simulator (https://www.flightgear.org). In the project, we used sockets and multi-threding for attchiving communication with the simulator server and back.

Activating the simulator & running the project
---
In order to activate the program you should do the following:

- [ ] First, implement two arguments in the flightGear's setting:
1. --generic=socket,out,10,REQUESTED-IP,5400,tcp,generic_small.
2. --telnet=socket,in,10,REQUESTED-IP,5402,tcp.
- [ ] Second, locate the included "generic_small.xml" file inside the FlightGear installation folder "data/Protocol".
After following the steps above, you are ready to fly!
You should first run the program (compile the files by Running The following Command: "g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread") and the flight gear next.

So What Now?
---
Congragulations! you've overcame the hard work. Now let the plane do the rest of the work...
We'll guide you through the different prints in the console during the flight:
* Before even activating the flight simulator, you'll see the message: " accepting clients". That means that the "OPenDataServerCommand" has executed successfuly and now waiting for connection.
* After the flight simulaor has been activated, if the connection proccess was made the "OPenDataServerCommand" will let you know that "client connected, listen for messages". The server you've created is now waiting for data from the simulator.
* Next, "connected" will apear - you are now the connected as a client (you're actually both :wink: ). That is the multi-threading in action! 

Write commands for the simulator yourself!
---
The programm reads from a filt which you can edit however you want - write the commands for the simulator and create your own journy...


:small_blue_diamond: *Open Data Server Comand[port]* -  open server using sockets used for reciving data.


:small_blue_diamond: *Connect Control Client Command[ip, port]* - open client using sockets used for sending data.


:small_blue_diamond: *Var Command[name]* - assign value to a variable.


:small_blue_diamond: *Print Command[expression]* - Prints the given expression to consol.


:small_blue_diamond: *Sleep Command[expression]* - stop the main thread for the specified amount of time.


:small_blue_diamond: *while Command[condition]* - while the condition is true, execute the commands.


:small_blue_diamond: *If Command[condition]* - if the condition is true, execute the commands.

# Authors
:star2: Chen Baadani


:star2: Dana Kreimer


* Did you really thought we would end without a little teaser?

[FlightGear](http://home.flightgear.org/)
