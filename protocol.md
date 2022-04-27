# protocol specs

under construction!

## client/robot

the included wixel is used for bidirectional wireless serial data transfer. it
has built-in error correction and other features that make sure data gets to
the robot losslessly, so data loss is not accounted for.

### important constants

|property|value|unit|
|-|-|-|
|baud rate|9600|bit s⁻¹|
|max byte timeout|5|ms|
|byte order|big-endian|-|

### commands

each command consists of an opcode, and then a payload. each opcode defines
logic to handle payload length, so certain commands might expect a fixed-length
payload, a variable-length payload, or none at all.

opcodes are picked sequentially, but bit 0 is reserved to indicate a transfer
from robot to client. this means that the opcode for a sensor data request
would be `0x14`, but the response opcode would be `0x15`. a c header is
provided that contains consts of these opcodes for code readability.

|code|name|implemented|directions|full name|
|--:|---|:-:|:-:|---|
|`0x00`|[BOMD](#bomd)|no|`r <=> c`|<u>b</u>ack<u>o</u>rder <u>m</u>o<u>d</u>ify
|`0x00`|[CORD](#cord)|no|`r <=> c`|<u>co</u>o<u>rd</u>inate
|`0x00`|[EXFL](#exfl)|no|`r <-- c`|<u>ex</u>ecution <u>fl</u>ow
|`0x00`|[SRES](#sres)|no|`r <-- c`|<u>s</u>oft <u>res</u>et
|`0x00`|[EXPT](#expt)|no|`r --> c`|<u>ex</u>ce<u>pt</u>ion
|`0x00`|[SPED](#sped)|no|`r <-- c`|<u>spe</u>e<u>d</u>
|`0x00`|[DIRC](#dirc)|no|`r <-- c`|<u>dir</u>ect <u>c</u>ontrol
|`0x00`|[DISP](#disp)|no|`r <-- c`|<u>disp</u>lay control
|`0x00`|[SENS](#sens)|no|`r <=> c`|<u>sens</u>or data
|`0x00`|[MAPS](#maps)|no|`r <-- c`|<u>map</u> <u>s</u>end
|`0x00`|[PING](#ping)|no|`r <=> c`|<u>ping</u>
|`0x00`|[PLAY](#play)|no|`r <-- c`|<u>play</u> midi
|`0x00`|[CLED](#cled)|no|`r <-- c`|<u>c</u>ontrol <u>led</u>s

#### BOMD

##### backorder append

- length: 2 bytes
- client to robot

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 0`)|
|`uint8_t`|action|

_action_ is a byte containing `0bXXXXXXYY` where X+1 is the amount of times
action Y gets repeated. Y can be:
- 0: move 1 tile forward
- 1: move 1 tile backward
- 2: turn right 90°
- 3: turn left 90°

examples:
- move forward 4 tiles: `0b00001100` (`0x10`)
- turn 180°: `0b00000110` (`0x06`) or `0b00000111` (`0x07`)

##### backorder index

- length: 9 bytes
- robot to client

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 1`)|
|`uint32_t`|backorder buffer length|
|`uint32_t`|backorder buffer index|

#### CORD

##### set position

- length: 6 bytes
- client to robot

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 0`)|
|`uint32_t`|position|
|`uint8_t`|orientation|

_position_ = y * width + x  
_orientation_:
- 0: west
- 1: north
- 2: east
- 3: south

##### get position

- length: 6 bytes
- robot to client

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 1`)|
|`uint32_t`|position|
|`uint8_t`|orientation|

_position_ = y * width + x  
_orientation_:
- 0: west
- 1: north
- 2: east
- 3: south

#### EXFL

##### set execution flow

- length: 2 bytes
- client to robot

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 0`)|
|`uint8_t`|action|

_action_ is:
- 0: suspend all operation
- 1: resume operation

#### SRES

##### soft reset

- length: 1 byte
- client to robot

|type|description|
|-:|-|
|`uint8_t`|opcode (`0x00 + 0`)|

#### EXPT
#### SPED
#### DIRC
#### DISP
DCLR display clear  
DPOS display cursor position  
DWSR display write string  
DWBM display write bitmap
#### SENS
#### MAPS
#### PING
#### PLAY
#### CLED


## client/websocket

TBD

