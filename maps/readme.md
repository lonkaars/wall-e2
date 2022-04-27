# maps

this directory contains map files. a .map file contains a binary representation
of a maze, and can be sent to the robot over the wireless serial connection.
map files have the following structure: first the width of the map as an
unsigned 16-bit integer, then the height of the map also as an unsigned 16-bit
integer. the rest of the file is the map content in reading order, where each
byte contains two (nibble) map tiles. tiles are stored in the most significant
portion of the byte first, so the last byte of a map file containing an uneven
amount of tiles would look like `0x?0`.

example tile:

```
┌───────┐      ┌───┬───┐
│   b   │      │   │   │
│ a   c │      │   └───┤
│   d   │      │       │
└───────┘      └───────┘
 0bDCBA       0b0110 (0x6)
```

garbage python scripts for generating and viewing these maps are included.
[this](https://www.figma.com/file/GUKV1am9sqWpPoes9h8Ram/robotrun?node-id=0%3A1)
figma file can be used to create a map, and then read out the hexadecimal
notation for the map. google drive ocr works well enough to read out the red
characters if you turn off path visibility in the figma document. figma also
allows pdf export so you can print the maps, but the tiles are 24x24 pixels,
not robot-sized (one tile is supposed to have about the same width and height
as the robot's diameter).

## exporting maps as pdf or svg

```sh
# generate svg file
python3 mappdf.py [file]

# render svg as pdf
inkscape --export-pdf=map.pdf [file].svg

# (optional) convert to tiles for printing at home
# loop up map size using pdfinfo on map.pdf file
pdfposter map.pdf tiles.pdf -m a4 -p [map size]
```

