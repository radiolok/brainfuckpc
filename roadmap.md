# 1. PCB Making[DEPRACATED]

I have no time to finish self-maid boards so ordered full set of pcb's:
10 pcb - base boards
10 plates with 24 different modules on each - 240 modules
2AND/2XOR
2AND/2OR
D-trigger
2&(3C+1A)
Diode(8)

## Equipment
1. Roaster temperature regulator - Done
2. Solder mask frame table   - Done
3. Etching bath - Ok
4. CNC milling machine tuning - Not finished yet
5. 3D printer - In use

# 2. Soldering
| Module            | Components  | Soldered    | Checked  |    Status    |
|-------------------|-------------|-------------|----------|--------------|
|2AND/2OR           |  Check  |   0/?      |    0     |  Not started |
|2AND/2XOR          |  Check  |   35/32+?      |    0     |  Done |
|D-TRIGGER          |  Check |   29/64+?      |    0     |  Active |
|2&          | Check  |   0/64      |    0     |  Not started |
|Diode module         |  Check  |   6/?      |    0     |  Done |
|Base board         |  Check |   1/6       |    0     |  Active |
|Memory board       |  Check |   1/1       |    0     |  Done   |

## Equipment
1. Relay tester - N/A
2. Modules tester - Done

# 3. Wire Wrapping
|Block               |     Status    |     
|--------------------|---------------|
|ADD                 |  Active  |
|LATCH BLOCK         |  Not started  |
|IP/AP REG           |  Not started  |
|TMP/CMD REG         |  Not started  |
|LOGIC BLOCK         |  Not started  |
|LOGIC/SWITCH BLOCK  |  Not started  |

# 4. Memory Board 
| Operation           |  Status       |
|---------------------|---------------|
| Schematic           |  Done         |
| PCB Routing         |  Done         |
| MCU firmware        |  Started  |


# 5. Housing
|  Component          |   Status     |
|---------------------|--------------|
| Base Plate          | Drawing      |
| Main Frame          | Not started  |

# 6. Progress updates:

## Update 14/12/2017:
* Soldering D-trigger modules. Need 64+, got half of them
* Designed indicator board
* Start wire-wrap of adder block

## Update 12/11/2017:
* Ordered pcbs from easyeda and got it.
* Soldered all 2AND/2XOR modules for carry-chain adder. Start soldering base plate for it.
* Done with modules tester - didn't check any relay but will check all modules.


## Update 05/06/2017:
* Only in third attempt I painted some boards with solder mask. It's a diode module, 2ANDx4 module and 2& module - two plates of each type. Currently can start drill and mill them and start assemble the modules.

## Update 17/04/2017:
* Rework and optimized ADDer logic. previous version needed 64 modules with 3 different types: ADD+C, 5AND, 2AND/2OR. New version need 32 modules with 2AND/2XOR type; One basic block would be used for latches.
* Done with memory Board module routing - Already got ready pcb from manufacturer and currently soldering it.
* Done with prepearing for solder mask operations - will start with this one as soon possible;
* Thinking about memory module firmware. Start developing it's arch.

## Update 08/03/2017:
* I'm done with all known modules etching 30 pcbs! All adder modules, all register modules are ecthed;
* Created and etched some modules for logic block - I have 64 modules capacity on it and have only preliminarty schematic for microcode;
* Next step - apply solder mask on them and send to drilling and milling. After this steps I will start soldering modules.

## Update 04/03/2017:
* Put image on another 6 plates and want to etch them in near future - 3x5AND, 1x2AND/2OR, 2xD-trigger.
* Almost finished with Memory Board routing. Need to fix power lines and check all connections.
* Prepare plywood table for photomask - it's ready for use and I want to start when finished with all known boards.

## Update 25/02/2017:
* Etched additional 12 pcb's - 6 pcb of D-trigger, 2 ADD+C, 1 5AND, 3 base boards.

## Update 23/02/2017:
* Suddenly found that I have D-trigger unrouted yet. Fix this issue and got one-side pcb with one jumper. Printed Photomasks and Imaged two plates;
* Modified ADD+C routing into one-side pcb with one jumper. Reprinted photomasks and made one of two Images;
* Bought thermal laminator for doing photoresist operations better - when I start etching I found that they are a lot of issues with images quality. First test gaves me stable good image quality after I just found proper temperature;
* Currently I have 5 etched plates and 7 - waiting for etch (will do it in 2-3 days).
