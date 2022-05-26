# robot code

this is the subdirectory for all code that runs on the 3pi robot

## make

the makefile in this directory works the same as a regular makefile, with the
exception of the `make flash` command.

to upload the compiled robot executable, you need to change the com port
specified in the makefile in this directory (line that says `PORT ?=
/dev/ttyACMx`). for windows this should be changed to `PORT ?= COMx`, where x
is the number of the 'programming' com port on the programmer. this will
probably change every time you re-plug the programmer, so you should try every
com port until it uploads successfully. you can find available com ports in
device manager on windows, or by running `ls /dev/ttyACM*` on linux. once the
com port is configured, run `make flash` to upload the executable and
automatically reboot the robot.

another fun option in the makefile is the SIM mode. by uncommenting the line `#
SIM = true`, the robot code can be compiled for desktop debugging instead. all
used pololu functions must be manually implemented in sim.c for this to work,
but it allows easier debugging. *it's important that the `orangutan_shim.h`
header is used instead of including `<pololu/orangutan.h>` directly for this to
keep working!*

## module hierarchy

the software is divided into seperate 'modules' for organizational,
maintenance, testing and debugging purposes. the sizes of the blocks in the
following diagram are a bit misleading, as some of these blocks are mostly
organizational and form more of a software 'skeleton', while the 'maze' and
'warehouse' modules provide the majority of the actual control logic.

```
┌──────────────────────────────────────────────────────────────────────┐
│                              "Hypervisor"                            │
└────────┬──────────────────┬──────────────────┬────────────────┬──────┘
┌────────┴───────┐┌─────────┴────────┐┌────────┴─────────┐┌─────┴──────┐
│ Error handling ││ I/O Read & Write ││ PC communication ││ Mode logic │
└────────────────┘└──────────────────┘└──────────────────┘└─────┬──────┘
                      ┌──────────┬──────────────┬───────────────┤
                  ┌───┴──┐┌──────┴────┐┌────────┴───────┐┌──────┴──────┐
      *modes* ->  │ Maze ││ Warehouse ││ Emergency stop ││ Calibration │
                  └──────┘└───────────┘└────────────────┘└─────────────┘
```

this diagram roughly describes how different parts of the robot software are
called. most of these modules can talk to each other using functions exposed by
the modules themselves (e.g. the maze module sending an error code to the error
handling module, which then both handles the error and forwards it to pc
communication for logging purposes). here's a quick run-down of all modules and
what they're supposed to do:

|module            |internal name|due|author|purpose|
|------------------|-------------|-|-|-|
|hypervisor        |`hypervisor `|done|N/a| backbone of all other modules; stores global variables; controls when other modules run|
|pc communication  |`sercomm    `|may 27|Loek| reads and parses incoming serial data; sends all data in the message buffer|
|error handling    |`errcatch   `|done|Loek| receives error codes; controls how errors are handled|
|i/o read & write  |`io         `|may 27|Jorn & Abdullaahi| reads all inputs to global state; writes all outputs|
|mode logic        |`modes      `|done|N/a| executes the appropriate module for current mode|
|maze              |`mode_maze  `|may 31|Jorn & Abdullaahi| controls robot during maze portion of map; hands off control to warehouse module|
|warehouse         |`mode_grid  `|may 31|Loek| controls robot during warehouse portion of map; hands off control to maze module|
|emergency stop    |`mode_halt  `|may 31|Fiona| stops all execution until emergency mode is reset by software or user|
|line finding      |`mode_lcal  `|may 31|Fiona| find line by turning on own axis if lost|
|charge station    |`mode_chrg  `|may 31|Fiona| go to the charging station transition in the grid, and continue until a black circle is found|
|direct control    |`mode_dirc  `|may 31|Loek| respond to [DIRC](../protocol.md#DIRC) commands|
|wet floor         |`mode_spin  `|may 31|Fiona| spin uncontrollably (simulating wet floor??)|
|sensor calibration|`mode_scal  `|may 31|Jorn & Abdullaahi| calibrate underside uv sensors|

## some standards

this list will probably get updated from time to time:

- modules shouldn't create any global state variables, they should use `static`
  variables instead.
- modules are run cyclically, so they shouldn't take more than
  `W2_MAX_MODULE_CYCLE_MS` to execute (this is an arbitrary number, and may be
  changed).
- documentation comments should follow the [javadoc-style doxygen
  format](https://wiki.scilab.org/Doxygen%20documentation%20Examples) and be
  placed in header (.h) files if possible. this only applies to public members
  (e.g. no local variables or module-internal code).
- code style is mostly handled by `clang-format` and `clang-tidy`, but you
  should still follow these naming conventions (`<angle brackets>` indicate
  placeholders):
  |symbol type|name|example|
  |-|-|-|
  |function|`w2_<module>_<name>`|`w2_errcatch_pushcode`; `w2_sercomm_sendraw`|
  |variable|`g_w2_<name>`|`g_w2_inputs`; `g_w2_current_mode`|
  |constant|`W2_<NAME>`|`W2_MAX_MODULE_CYCLE_MS`; `W2_SERIAL_BAUD`|
  |struct|`w2_s_<name>`|`w2_s_input_data`; `w2_s_output_data`|
  |enum|`w2_e_<name>`|`w2_e_errorcodes`; `w2_e_serial_commands`|
  
  this again only applies to public members. local variables should still have
  short descriptive names, but shouldn't be prefixed with `w2_*`.
- arbitrary numbers should be aliased to `#define` statements or `enum`s if
  part of a series.
- general constants should be placed in `consts.h`
- don't import `<pololu/orangutan.h>` directly, instead use
  `"orangutan_shim.h"` to keep code compatible with the simulator

## todo

global todo:

- [ ] start robot in calibration mode
- [ ] assume robot starts in maze
- [ ] 'crosswalk' transition detection in seperate file (used by grid and maze
  mode)
- [ ] client software architecture
- [x] mode 'return' buffer
- [x] clear global timer at start of cycle instead of just for mode selection
  module (for last ping time measurement)
- [ ] calibrate (line-detecting) light sensors in setup.c, or manually by
  placing the robot and pressing a button (maybe make this a seperate mode)
- [ ] create labeled timer functions like nodejs `console.time()` and
  `console.timeEnd()` (use for serial read timeout constraint)

### hypervisor

the hypervisor executes all other modules, and measures execution time. it also
provides all other modules with a central place for defining global variables.

### pc communication

the pc communication module sends messages in a binary format over the serial
connection provided by the wixel modules. this module should also send a 'ping'
command each cycle to check if the connection is still intact. the pc will also
periodically send ping, and various other commands which this module will have
to act on accordingly.

### error handling

the error handling module (a) provides functions for other modules to report
errors, and (b) handles errors accordingly.

- [x] create an error `struct` that holds:
  - [x] error code
  - [x] message length
  - [x] message contents
- [x] create a global error ring buffer with an appropriate size that holds
  error messages
- [ ] handle errors in the error buffer, referencing the functional
  specification for details on what the robot should do to resolve each kind of
  error
- [ ] forward error codes to the pc-communication module

~empty function declarations are in place for providing other modules an error
reporting function.~

this module is as good as finished but full functionality is currently
dependent on:

- [ ] pc communication
- [ ] other mode implementations

### i/o read & write

the i/o module reads all inputs once and writes all outputs once. this keeps
cycle time constant, and makes sure no time is wasted re-reading inputs, or
writing outputs more than once.

- [ ] create `struct`s for each type of input:  
  - [ ] button
  - [ ] infrared light sensor
  - [ ] time-of-flight distance sensor
- [ ] create a single `struct` that holds all input data
- [ ] create a single `struct` that holds output data values for:
  - [ ] left motor speed
  - [ ] right motor speed
  - [ ] red led
  - [ ] green led

extra (requires external interrupt setup):
- [ ] add a `pressed` property to the button struct that turns on if the button
  was pressed outside the i/o module execution span
- [ ] add a `press_duration` property to the button struct that measures button
  press duration, and that works when the button is pressed outside the i/o
  module execution span

technically the wixel serial channel, programmer debug serial channel, lcd
contents and speaker tones are also considered outputs, but these all take
significant time or memory to update, so these will not be updated using the
cyclic i/o module.

### modes

modes is a shim module that forwards execution to the currently selected mode.
the global variable `g_w2_current_mode` holds a pointer to the current mode.
this makes sure only a single mode handler gets ran on every execution cycle.

### maze

the maze mode controls the robot when it's in the maze, and sets execution to
grid mode when it detects the maze-grid transition. the solving algorithm will
constantly keep either left or right until (a) the maze-grid transition is
detected, (b) the charging pad is detected, or (c) the starting point is
detected. depending on which location is desired, the robot may continue to
venture through the maze when it finds any of these. exact implementation
details for this mode are yet to be determined.

### warehouse

the warehouse mode controls the robot when it's in the warehouse, and sets
execution to maze mode when it detects the maze-grid transition. exact
implementation details for this mode are yet to be determined.

### emergency stop

the emergency stop mode stops the robot from doing anything until the user
determines it is safe to resume execution.

- [ ] create a global variable that holds the previous mode
- [ ] create a global variable that holds a 'safe' state (startup/default
  value = false)
- [ ] add a condition in the supervisor that switches to the emergency mode if
  the 'safe' state variable is false
- [ ] add a condition in the emergency mode handler that switches to the
  previous mode if the 'safe' state returns to false

### calibration

the calibration sequence is used during the maze mode for re-finding the line
when the robot gets lost. the robot will first try to find the line by itself
when it gets lost. when it does this it will send a warning to the error
buffer. in case it can't find the line anymore, it will go into emergency mode
and send a critical warning.

- [ ] implement line-finding sequence  
  - turn 360 degrees (about robot's own axis)
  - if a line is found at any point during this rotation, stop turning
  - if a full rotation is completed without a found line, enter emergency
    mode
- [ ] add a warning for line lost

