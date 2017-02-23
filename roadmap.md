# 1. PCB Making

| Module            | Routing     | Photomask   | Layer Image | Layer Etch | Solder Mask | Milling | Plates | Pcb    |  Make Status  |
|-------------------|-------------|-------------|-------------|------------|-------------|---------|--------|--------|---------------|
|ADD+C              | Done        |    ***2/2***      |    ***1***/2      |    0/2     |      0/2    |   0/2   |  2     |  16    |  Layer Image  |
|2AND/2OR           | Done        |    4/4      |    3/4      |    3/4     |      0/4    |   0/4   |  4(?)  |  32(?) | ***Layer Etch***  |
|5AND               | Done        |    ***4***/4      |    ***4***/4      |    0/4     |      0/4    |   0/4   |  4     |  32    | ***Layer Image***  |
|D-TRIGGER          | Done       |    ***2/2***      |    2/8      |    0/8     |      0/8    |   0/8   |  8     |  64    |  Layer Image  |
|Base board         | Done        |    2/2      |    5/5      |    2/5     |      0/5    |   0/5   |  5     |   5    |  ***Layer Etch***  |
|Base/Switch board  | Done        |    0/0      |    0/1      |    0/1     |      0/1    |   0/1   |  1     |   1    | Photomask  |
|Memory board       | In work     |     N/A     |    N/A      |    N/A     |      N/A    |   N/A   |  1     |   1    |  Routing      |
| Summary   | N/A |   16/20  |    17/24(?) |    5/24    |   0/24   |   0/24  |   24   |   151(?)  | |
## Equipment
1. Roaster temperature regulator - Done
2. ***Solder mask frame table   - Making plywood parts***
3. ***Etching bath - First successfull test***
4. CNC milling machine tuning - Not started

# 2. Soldering
| Module            | Components  | Soldered    | Checked  |    Status    |
|-------------------|-------------|-------------|----------|--------------|
|ADD+C              |  Not check  |   0/16      |    0     |  Not started |
|2AND/2OR           |  Not check  |   0/16      |    0     |  Not started |
|5AND               |  Not check  |   0/32      |    0     |  Not started |
|D-TRIGGER          |  Not check  |   0/64      |    0     |  Not started |
|Base board         |  Not check  |   0/5       |    0     |  Not started |
|Base/Switch board  |  Not check  |   0/1       |    0     |  Not started |
|Memory board       |  Not check  |   0/1       |    0     |  Routing     |
## Equipment
1. ***Relay tester - I'm looking through suitable relay connectors for this tester***
2. Modules tester - Not started

# 3. Wire Wrapping
|Block               |     Status    |     
|--------------------|---------------|
|ADD                 |  Not started  |
|CARRY               |  Not started  |
|IP/AP REG           |  Not started  |
|TMP/CMD REG         |  Not started  |
|LOGIC BLOCK         |  Not started  |
|LOGIC/SWITCH BLOCK  |  Not started  |

# 4. Memory Board 
| Operation           |  Status       |
|---------------------|---------------|
| Schematic           |  In work      |
| PCB Routing         |  In work      |
| MCU firmware        |  Not started  |


# 5. Housing
|  Component          |   Status     |
|---------------------|--------------|
| Base Plate          | Drawing      |
| Main Frame          | Not started  |

# 6. Progress updates:

## Update 23/02/2017:
* Suddenly found that I have D-trigger unrouted yet. Fix this issue and got one-side pcb with one jumper. Printed Photomasks and Imaged two plates;
* Modified ADD+C routing into one-side pcb with one jumper. Reprinted photomasks and made one of two Images;
* Bought thermal laminator for doing photoresist operations better - when I start etching I found that they are a lot of issues with images quality. First test gaves me stable good image quality after I just found proper temperature;
* Currently I have 5 etched plates and 7 - waiting for etch (will do it in 2-3 days).
