# client code

this is the subdirectory for all client code (runs on pc/laptop)

this page is WIP

## features

|feature|status|author|description|
|-|-|-|-|
|view warnings / errors|unimplemented||see a log of parsed warnings/errors
|direct control|done|Loek|directly control the robot with tank-style controls
|configure map|unimplemented||set map width/height and define entry/exitpoints
|input orders|unimplemented||type orders with lists of coordinates to visit
|enable/disable emergency mode|unimplemented||self-explanatory
|enable/disable sensor calibration mode|unimplemented||self-explanatory
|enable/disable wet floor mode|unimplemented||self-explanatory
|read sensor values|unimplemented||dashboard that displays all i/o as bar graphs
|set display contents|unimplemented||send text to display on lcd
|play music|unimplemented||play tunes
|control leds|unimplemented||turn on/off underside leds

## interface

the client is a user-facing application that allows control and monitoring of
the robot in various ways. it primarily works in a bios-like way, with the user
having access to multiple tabs containing options or custom interface elements.

to start the interface, the user should run `./main <com-port>`. the interface
could look something like this (with colored text for element seperation, [see
on figma](https://www.figma.com/file/vZ6rQp2G1HBAmbdrkxIZJ3/terminal-app)):

```
verbonden, 2ms ping           (0.0.2-11-g92c394b)                  batterij 100%
[huidige logica-modus]                         0 waarschuwingen, 0 foutmeldingen
 [info]  logs   direct aansturen   kaart   orders   modus instellen   sensor...
--------------------------------------------------------------------------------

welkom in de wall-e2 console applicatie! deze client is versie
0.0.2-11-g92c394b

deze applicatie functioneert op een soortgelijke manier als een BIOS. hier is
een lijst met besturingscommando's:

<links>/<rechts>, <h>/<l>     tabblad wisselen
<omlaag>/<omhoog>, <j>/<k>    optie selecteren
<enter>, <i>                  optie aanpassen
<home>, <g>                   terug naar boven scrollen
<end>, <G>                    naar einde van pagina scrollen
<escape>                      terug
<q>                           console applicatie sluiten

sneltoetsen:
<N>  info                   <o>  orders
<S>  logs                   <M>  modus instellen
<d>  direct aansturen       <m>  kaart              

```

the top status bar is always supposed to be visible, and is sort of inspired by
[ncmpcpp](https://github.com/ncmpcpp/ncmpcpp). we're using
[ncurses](https://invisible-mirror.net/ncurses/ncurses.html) to assist in
creating a cross-platform terminal ui.

going from top-left in reading order the status bar contains: connection
status, ping time, robot version number, robot battery info, current logic
mode, warnings and critical exceptions, and lastly a tab bar. the version
number is aligned to the terminal center, and the battery and warning counters
are aligned right. when a connection hasn't been established between the robot
and client, the fields containing robot info should dissapear. the tab bar
scrolls horizontally, and tab names should in addition to a single space
seperator, keep spaces before and after to fit square brackets indicating tab
selection status.

## code structure

because multithreading is hard, another cyclic system is used. the following
modules are executed after each other:

- serial read
- stdin read (user input)
- status bar paint
- current tab paint

