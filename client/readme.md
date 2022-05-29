# client code

this is the subdirectory for all client code (runs on pc/laptop)

this page is WIP

## features

|feature|due|status|author|description|
|-|-|-|-|-|
|view warnings / errors|may 31|unimplemented||see a log of parsed warnings/errors
|direct control|may 31|unimplemented||directly control the robot with tank-style controls
|configure map|june 04|unimplemented||set map width/height and define entry/exitpoints
|input orders|june 04|unimplemented||type orders with lists of coordinates to visit
|enable/disable emergency mode|may 31|unimplemented||self-explanatory
|enable/disable sensor calibration mode|may 31|unimplemented||self-explanatory
|enable/disable wet floor mode|may 31|unimplemented||self-explanatory
|read sensor values|june 04|unimplemented||dashboard that displays all i/o as bar graphs
|set display contents|optional|unimplemented||send text to display on lcd
|play music|optional|unimplemented||play tunes
|control leds|optional|unimplemented||turn on/off underside leds

## interface

the client is a user-facing application that allows control and monitoring of
the robot in various ways. it primarily works in a command-line way, with the
user typing commands that get translated to protocol messages, and sent to the
robot. to start the interface, the user should run `./main <com-port> [command]
[args]`. by not specifying a command, the interactive shell is launched which
looks like this (and it's supposed to be in dutch):

```
verbonden, 2ms ping           (0.0.2-11-g92c394b)                  batterij 100%
[huidige logica-modus]                         0 waarschuwingen, 0 foutmeldingen
--------------------------------------------------------------------------------














welkom in de wall-e2 console applicatie! deze client is versie
0.0.2-11-g92c394b

typ 'help' om alle commando's te zien in een lijst, of 'doei' om deze
applicatie weer te sluiten.

w2>
```

the top status bar is always supposed to be visible, and is sort of inspired by
[ncmpcpp](https://github.com/ncmpcpp/ncmpcpp). because the client software
should use no libraries if possible, a custom renderer needs to be implemented,
though it doesn't matter if it's very primitive.

going from top-left in reading order the status bar contains: connection
status, ping time, robot version number, robot battery info, current logic
mode, warnings and critical exceptions. the version number is aligned to the
terminal center, and the battery and warning counters are aligned right. when a
connection hasn't been established between the robot and client, the fields
containing robot info should dissapear.

## code structure

because multithreading is hard, another cyclic system is used. the following
modules are executed after each other:

- serial read
- stdin read (user input)
- optional control mode handling

## notes on ascii escape codes

- color codes
- terminal echo codes
- how to read terminal (re)size
- cursor movement

