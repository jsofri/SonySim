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
2. Connect to simulator
3. Variable assignment
4. `if` condition
5. `while` loop
6. Print
7. Sleep
8. Functions

* Comments
---
### Run a Server
`openDataServer(int port)` command set a new server in a new thred.  
IP is set to localhost `127.0.0.1` on given port. the server can listen to one client only, where client should send data as described in generic_small.xml

### Connect to Simulator
`openDataServer(int port)` command set a new server 

### Variable Assignment
`openDataServer(int port)` command set a new server 

### if condition
`openDataServer(int port)` command set a new server 

### While loop
`openDataServer(int port)` command set a new server 

### Print
`openDataServer(int port)` command set a new server 

### Sleep
`openDataServer(int port)` command set a new server 

### Functions
`openDataServer(int port)` command set a new server 

### Comments
`openDataServer(int port)` command set a new server 

## Code Architecture:  
![Flow Chart](https://github.com/yehonatansofri/SonySim/blob/master/flowchart.PNG)
### Threads  
1. Main Thread
 * Interpretation of code in text file - Lexical analysis, parsing and executing  
 * Set new values in the Program Symbol Table
 * Enqueue new values in the queue
2. Client Thread  
 * Client of the FlightGear simulator
 * Dequeue and set new values of flight parameters in the simulator
3. Server Thread  
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

1. a flowchart of: client, server, simulator
2. multithreading
3. how the data is stored (global vars) - link to flowchart


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
Free License (unless you're a BIU student...)
