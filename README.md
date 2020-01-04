# FlightGear Simulator Controller

![Logo](https://wallpapercave.com/wp/wp2113392.jpg)

By Rony Utevsky and Yehonatan Sofri.  
A C++ project made for Advanced Programming 1, BIU, Fall 2019.  
[Link to GitHub](https://github.com/yehonatansofri/SonySim/)
## System requirements
* Linux OS  
![Incompatible with Windows OS](https://img.shields.io/badge/Incompatible%20with%20Windows%20OS-red)

**Minimum hardware requirements for FlightGear:**
* Screen with a resolution of at least 1024x768 @32bpp
* 3D video card (with AMD or NVIDIA chipset) with support for OpenGL 2.1 or better and at least 1024-2048MB of dedicated DDR3+ (DDR5 preferred) VRAM
* 2 GB of free RAM 
* Quad core processor with ~ 2 GHz each
* 5 GB of free storage

## Installation

For the program to run as planned, make sure FlightGear simulator is installed in your machine.  
Once installed, copy `generic_small.xml` file to Protocol directory:   `/usr/share/games/flightgear/Protocol`  
  
Open FlightGear, and in settings tab, enter instructions:  
```
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small 
--telnet=socket,in,10,127.0.0.1,5402,tcp
```
this parameters can be codified, please refer to   [FlightGear Documentation](http://wiki.flightgear.org/Main_Page/)

If compilation is required, go to project directory (where main.cpp is) and compile using 

```bash
g++ -std=c++14 */*.cpp  *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```

## Usage
Program get a txt file name as input. add .txt in end of file name, example
```
./a.out file_name.txt
```
## Syntax of .txt file  
The `txt` file contains commands that are sent to the simulator and control the aircraft.  
  
**Supported commands:**  
1. [Run a server](#run-a-server)  
2. [Connect to simulator](#connect-to-simulator)  
3. [Variable Declaration](#variable-declaration)  
4. [Variable assignment](#variable-assignment)  
5. `if` condition
6. `while` loop
7. Print
8. [Sleep](#sleep)
9. Functions

* Comments
---
### Run a Server
`openDataServer(int port)` set and run a server in a new thred.  
IP is set to localhost `127.0.0.1` on given `port`. The server can accept and listen to one client only.  
The server expects to get data as defined in generic_small.xml file. It runs a loop that get data in CSV format, convert it to values of flight data. `value` of variables in symbol table that are defined as modified by simulator will be changed. Thread continues to run as long as `mainIsParsing = true`
e.g.
```
...
openDataServer(1009) //when line is executed - a new thread runs a server on local host in port 1009
```

### Connect to Simulator
`connectControlClient(string ip,int port)` set and run a thread that acts as a client of the flight simulator.  
This function set a new socket in given `ip` and `port`, and connect with the server. Once connected, it runs a loop that dequeue data thats needs to be sent to simulator, and send it as a `set` command to the simulator via Telnet protocol. Thread continues to run as long as `mainIsParsing = true`.  
e.g.  
```
...
connectControlClient("127.0.0.1", 1009) //when line is executed - a new thread runs a client on ip 127.0.0.1 in port 1009
```

### Variable Declaration
`var var_name -> sim("/reference/to/parameter")`  (1)  
`var var_name <- sim("/reference/to/parameter")`  (2)  
`var var_name = double`  (3)  

1. creating a new variable named `var_name`, in current scope, which is binded in a way that when var_name value is changed, the flight parameter in simulator which is located in `"/reference/to/parameter"` is also changed to same value. Once executed, `var_name` is inserted in the program symbol table with key `var_name` and appropriate VarData (with default `value = 0`). When scope ends then `var_name` key no longer exists in symbol table. Calling to `var_name` after the scope ended will cause undefined behaviour.  
e.g.
```
var flaps -> sim("/controls/switchs/flaps") // flaps is now in symbol table with updater = CLIENT
                                            //reference = "/controls/switchs/flaps", value = 0
```

2. creating a new variable named `var_name`, in current scope, which is binded in a way that when the flight parameter in reference `"/reference/to/parameter"` in simulator is changed, then the value of `var_name` in the symbol table will be changed to same value. `var_name` is inserted in the program symbol table with key `var_name` and appropriate VarData (with default `value = 0`). When scope ends then variable no longer exist. Refferring to `var_name` after the scope ended will cause undefined behaviour.  
e.g.
```
var offsetting <- sim("/controls/switchs/offsetting") // offsetting is now in symbol table with updater = SIMULATOR
                                                      //reference = "/controls/switchs/offsetting", value = 0
```

3. creating a new variable named `var_name`, in current scope, with the `double` followed by `=` operator. This variable holds a `VarData` struct with empty reference and updater `NO_ONE`. When scope ends then variable no longer exist. Refferring to `var_name` after the scope ended will cause undefined behaviour.  
e.g.
```
var x = 4.5 // x is now in symbol table with updater = NO_ONE, reference = "", value = 4.5
```

### Variable Assignment
`var_name = double` command set value `double` to variable `nar_name`. The value in the symbol table will be changed accordingly. If `updater = CLIENT` then an updated `VarData` will be enqueued in `updateSimulatorQueue`. Assigning a variable to a variable that it's `updater = SIMULATOR` as well as assigning an unintialized variable will cause undefined behaviour.

### if condition
You can use `if` conditions that take a single boolean expression, without parentheses.  
For example, this is supported:  
```
if  altitude > 1000 {
...
}
```

However, this is not yet supported:
```
if  altitude > 1000 && heading == 0 {
...
}
```

**Please note:** the opening parenthesis must be on the same line with the condition, while the closing one must be on a seperate line.

### While loop
You can use `while` loops that take a single boolean expression, without parentheses.  
For example, this is supported:  
```
while altitude < 1000 {
...
}
```

However, this is not yet supported:  
```
while  altitude < 1000 && heading != 0 {
...
}
```

**Please note:** the opening parenthesis must be on the same line with the `while` keyword's line, while the closing one must be on a seperate line.

### Print
`Print(string)` or `Print(variable name)`  
Using this function, you can print strings and variable, for example:
```
Print("Altitude is:")
Print(alt);
```

### Sleep
`Sleep(int)` will make the main thread to sleep for the number of milliseconds in `int`.  
e.g.
```
Sleep(10000) //now main will sleep for 10 seconds
```

### Functions
You can define and use functions to do various things.
For example:
```
// function definition
takeoff (var x) {
  while (alt < x) {
    rudder = (h0 - heading)/80
    aileron = -roll / 70
    elevator = pitch / 50
    Sleep(250)
  }
}

// function usage
takeoff(1000)
```

**Please note:**  
1. The opening parenthesis must be on the same line with the function's declaration line, while the closing one must be on a seperate line.  
2. The function must be defined before usage.
3. Each variable argument in the function's declaration must be preceded with `var` keyword.
4. If there are multiple variable arguments in the function's declaration, they should be seperated with a comma `,`:  `takeoff (var x, var y) {`

### Comments  
You can comment out a single line by prepending `//` or `#`, for example:  
`# heading = 1`  

---
## Code Architecture:  
![Flow Chart](https://github.com/yehonatansofri/Hello-World/blob/master/flowchart.PNG)
### Threads  
#### Main Thread
 * Interpretation of code in text file - Lexical analysis, parsing and executing  
 * Set new values in the Program Symbol Table and enqueue them in queue
 * Create Client and Server Threads
#### Client Thread  
 * Client of the FlightGear simulator
 * Dequeue and set new values of flight parameters in the simulator
#### Server Thread  
 * Once Connected, listen to the FlightGear Simulator only
 * Get flight parameters in CSV format and update Symbol Table respectively  
 ### Data structures  
 #### Struct VarData  
 Contains data about a specific variable - reference of variable in the flight simulator (e.g. "/dir/to/parameter"), value itself and updater - a flag that marks the updating factor of this variable.
 ```
 struct VarData {
    string reference;
    float  value;
    int    updater; //0 = no one, 1 = client, 2 = simulator
 }
 ```
 #### Symbol Table  
 A global object that stores all scopes data. encapsulate a `list<unordered_map<string, VarData>>`. each map represents a scope.
 the innermost scope will be in the start of list and outermost scope will be in the end.  
 Use mutex due to multi-threading on object.  
 #### Update Simulator Queue  
 A global queue used by main thread and client thread. main thread enqueue VarData structs of variables whose value has been modified, and client thread dequeue these values and send `set` commands to the simulator  

---
## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

---  

## License
Free License (unless you're a BIU student...)
