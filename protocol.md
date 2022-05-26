# protocol specs

under construction!

the included wixel is used for bidirectional wireless serial data transfer. it
has built-in error correction and other features that make sure data gets to
the robot losslessly, so data loss is not accounted for.

## important constants

|property|value|unit|
|-|-|-|
|baud rate|9600|bit s⁻¹|
|max byte timeout|5|ms|
|byte order|big-endian|-|

## commands

each command consists of a start byte, opcode, and a payload. each opcode
defines logic to handle payload length, so certain commands might expect a
fixed-length payload, a variable-length payload, or none at all. the start byte
is `0xff`, and because most data sent is in binary format, if the data contains
an `0xff` byte, it will be escaped by replacing it with two `0xff` bytes. this
is converted to a single `0xff` on the receiving end, so these duplicated bytes
and the starting byte don't count towards message length.

opcodes are picked sequentially, but the direction bit (LSB) is reserved to
indicate a transfer from robot to client (`tx`). this means that the opcode for
a sensor data request would be `0x12`, but the response opcode would be `0x13`.
these opcodes are stored as enum constants inside shared/protocol.h for code
readability.

|code|name|implemented|directions|full name|
|--:|---|:-:|:-:|---|
|`0x00`|[PING](#ping)|yes|`r <=> c`|<u>ping</u>
|`0x02`|[EXPT](#expt)|no|`r --> c`|<u>ex</u>ce<u>pt</u>ion
|`0x04`|[MODE](#mode)|no|`r <=> c`|<u>mode</u>
|`0x06`|[SPED](#sped)|no|`r <-- c`|<u>spe</u>e<u>d</u>
|`0x08`|[DIRC](#dirc)|no|`r <-- c`|<u>dir</u>ect <u>c</u>ontrol
|`0x0a`|[CORD](#cord)|no|`r <=> c`|<u>co</u>o<u>rd</u>inate
|`0x0c`|[BOMD](#bomd)|no|`r <=> c`|<u>b</u>ack<u>o</u>rder <u>m</u>o<u>d</u>ify
|`0x0e`|[SRES](#sres)|no|`r <-- c`|<u>s</u>oft <u>res</u>et
|`0x10`|[MCFG](#mcfg)|no|`r <-- c`|<u>m</u>ap <u>c</u>on<u>f</u>i<u>g</u>
|`0x12`|[SENS](#sens)|no|`r <-> c`|<u>sens</u>or data
|`0x14`|[INFO](#info)|yes|`r <-> c`|<u>info</u>
|`0x16`|[DISP](#disp)|no|`r <-- c`|<u>disp</u>lay control
|`0x18`|[PLAY](#play)|no|`r <-- c`|<u>play</u> midi
|`0x1a`|[CLED](#cled)|no|`r <-- c`|<u>c</u>ontrol <u>led</u>s

the DISP, PLAY, and CLED commands have low implementation priority, and should
be considered extra features

a double stroke arrow means that the command can be initiated from either the
robot or the client, while a single arrow indicates a request-response
structure.

in *both* the robot and client code `r <-- c` is referred to as `rx` and  `r
--> c` as `tx` (from the *robots* view).

### PING

#### ping (`r <=> c`) (2 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 0` or `0x00 + 1`)|
|`uint8_t`|ping id|

**ping** sends back an identical message either way with the direction bit
toggled. _ping id_ is a random 8-bit value that makes sure the same ping
doesn't keep bouncing back and forth indefinitely.

### EXPT

#### exception (`r --> c`) (3+ bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x02 + 1`)|
|`uint8_t`|error code|
|`uint8_t`|length|
|`uint8_t[length]`|message contents|

the **exception** instruction is used by the robot to send errors, warnings,
and other messages back to the client. an error can also optionally contain a
message between 0 and 255 characters long. message length is sent before the
message, and can be 0 in case of no message.

### MODE

#### set mode (`r <-- c`) (2 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x04 + 0`)|
|`uint8_t`|mode code|

when initiated from the client, the **mode** command forces the robot to change
execution mode. the mode codes are undetermined as of now.

#### get mode (`r --> c`) (2 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x04 + 1`)|
|`uint8_t`|mode code|

the **mode** command is send by the robot when it switches into another mode.
the mode codes are undetermined as of now.

<!-- TODO: mode codes in client and robot -->

### SPED

#### set speed modifier (`r <-- c`) (2 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x06 + 0`)|
|`uint8_t`|speed modifier|

scales motor output power from 0% (0x00) to 100% (0xff).

### DIRC

#### set motor speed (`r <-- c`) (5 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x08 + 0`)|
|`int16_t`|left motor speed|
|`int16_t`|right motor speed|

directly set left and right motor speed values. only works in direct control
mode (unimplemented!). motor values range from -255 to 255. speed is sent as a
signed 16-bit integer (`short`).

### CORD

#### set position (`r <-- c`) (6 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x0a + 0`)|
|`uint32_t`|position|
|`uint8_t`|orientation|

manually correct robot position and orientation in grid portion of the map.

_position_ = y * width + x
_orientation_:
- 0: west
- 1: north
- 2: east
- 3: south

#### get position (`r --> c`) (6 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x0a + 1`)|
|`uint32_t`|position|
|`uint8_t`|orientation|

sent by the robot in the grid portion of the map when a transition to a new
_position_ is finished.

_position_ = y * width + x
_orientation_:
- 0: west
- 1: north
- 2: east
- 3: south

### BOMD

#### append order (`r <-- c`) (9 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x0c + 0`)|
|`uint32_t`|order identifier|
|`uint32_t`|position|

add a new order to the backorder list (queue).

_position_ = y * width + x

#### order status (`r --> c`) (6 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x0c + 1`)|
|`uint32_t`|order identifier|
|`uint8_t`|status|

sent by the robot in the grid portion of the map when the status of an order
changes. also used to confirm orders are received successfully.

_status_ is one of:
- 0: received
- 1: processing (begin)
- 2: reached
- 3: finished

### SRES

#### soft reset (`r <-- c`) (2 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x0e + 0`)|
|`uint8_t`|type|

_type_ is one of:
- 0: reinitialize all global state
- 1: reset emergency mode

### MCFG

#### configure map (`r <-- c`) (4+ bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x10 + 0`)|
|`uint8_t`|width|
|`uint8_t`|height|
|`uint8_t`|length|
|`feature[length]`|features|

> _feature_ is a struct containing:
> 
> |type|description|
> |-:|-|
> |`uint16_t`|position|
> |`uint8_t`|kind|
> 
> where _position_ = y * width + x  
> and _kind_ = 0bXXYYYYYY where X = _orientation_ and Y = _type_
> 
> _orientation_:
> - 0: west
> - 1: north
> - 2: east
> - 3: south
> 
> _type_:
> - 0: entrance / exit
>

sends the map layout to the robot. the map is an automatically generated grid
of the specified size, starting at coordinates (1, 1) to keep a margin around
the grid for the maze-grid transition.

example hexdump of 5x5 map with a north-facing entrance/exit at (3, 0) for
later reference:
```
10 05 05 01 00 03 40
```

### SENS

#### request sensor data (`r <-- c`) (1 byte)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x12 + 0`)|

requests sensor data

#### sensor data response (`r --> c`) (??? bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x12 + 1`)|
|`???`|???|

sensor data response. contains all sensor data (distance, ir, buttons) in one
packet. format yet to be determined.

### INFO

#### request robot info (`r <-- c`) (1 byte)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x14 + 0`)|

requests robot info

#### robot info response (`r --> c`) (41 bytes)

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x14 + 1`)|
|`uint8_t[32]`|build string|
|`uint8_t`|errcatch module cycle time (ms)|
|`uint8_t`|io module cycle time (ms)|
|`uint8_t`|sercomm module cycle time (ms)|
|`uint8_t`|modes module cycle time (ms)|
|`uint32_t`|total robot uptime (s)|

robot info response

<!--
### DISP
- DCLR display clear
- DPOS display cursor position
- DWSR display write string
- DWBM display write bitmap
-->


