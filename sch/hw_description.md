#Parts

Computer consists of many different unified basic modules 60x44mm with 16x2.54mm male socket. 
Each module contains 4 reed relays, status LED's and diode binding for each relay.

## Modules types:

* 1bit ADD+C module for adder - 16 modules;
* 5AND module for parallel carry - 32 modules;
* Universal 2AND/2OR module for adder and control logic - 16 modules(for Adder);
* 1bit D-trigger with inversion for temp register - 16 modules;
* 1bit D-trigger with Output switch, for IP and AP register, Bias register and command register - 48 modules;
* Some other modules, which I din't implemented yet (list is updated)

## Base Plates:

Modules are mounted on base plates, 32 modules on each 150x200m base plate. Current implementation requers 7 base plates:

* Base plate with 32 16pin connectiors - 5 base plates;
* Switching plate with only 8 16-pin connectors, but with 4 16 bit switches - 1 plate;
* Memory plate with static RAM IC, input and output buffers and MCU with LED drivers for LED 16x32dot disdplay;

I will made all connection with wire-wrapping method.
