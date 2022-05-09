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

## module hierarchy

the software is divided into seperate 'modules' for maintenance, testing and
debugging purposes. the sizes of the blocks in the following diagram are a bit
misleading, as some of these blocks are mostly organizational and form more of
a software 'skeleton', while the 'maze' and 'warehouse' modules provide the
majority of the control logic.

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
called. most of these modules can talk to each other (e.g. the maze module
sending an error code to the error handling module, which then forwards it to
pc communication). here's a quick run-down of all modules and what they're
supposed to do:

|module          |internal name|purpose|
|----------------|-------------|-|
|hypervisor      |`hypervisor `|backbone of all other modules; stores global variables; controls when other modules run|
|pc communication|`sercomm    `|reads and parses incoming serial data; sends all data in the message buffer|
|error handling  |`errcatch   `|receives error codes; controls how errors are handled|
|i/o read & write|`io         `|reads all inputs to global state; writes all outputs|
|mode logic      |`modes      `|executes the appropriate module for current mode|
|maze            |`mode_maze  `|controls robot during maze portion of map; hands off control to warehouse module|
|warehouse       |`mode_grid  `|controls robot during warehouse portion of map; hands off control to maze module|
|emergency stop  |`mode_halt  `|stops all execution until emergency mode is reset by software or user|
|calibration     |`mode_calb  `|find line by turning on own axis if lost|

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
- run `make format` as a seperate commit in case of breaking changes

