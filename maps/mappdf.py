import sys
from struct import unpack
import svgutils.transform as sg
import svgutils.compose as sc

SVG_TILE_SIZE = 24
DPI = 96
INCH = 2.54
ROBOT_SIZE = 9.5
ROBOT_SIZE_UNIT = "cm"

RESIZE_FACTOR = ROBOT_SIZE / (SVG_TILE_SIZE / DPI * INCH)

def read_tiles():
  tiles = []
  for x in range(16):
    tile = open(f"./tiles/{x:x}.svg", "r")
    tiles.append(tile.read())
    tile.close()
  return tiles

def mappdf(filename):
  file = open(filename, 'rb')
  contents = file.read()
  file.close()
  tiles = read_tiles()

  width, height = unpack('>HH', contents[0:4])

  target = sg.SVGFigure()
  target.set_size((f"{width * SVG_TILE_SIZE}px", f"{height * SVG_TILE_SIZE}px"))

  for y in range(height):
    for x in range(width):
      nibble = x + y * width
      byte = int(nibble / 2)
      shift = byte * 2 - nibble + 1
      num = (contents[4 + byte] & (0xf << 4 * shift)) >> 4 * shift

      tile = sg.fromstring(tiles[num]).getroot()
      tile.moveto(x * SVG_TILE_SIZE, y * SVG_TILE_SIZE)
      target.append(tile)

  target.save(f"{filename}.svg")
  target_scaled = sc.SVG(f"{filename}.svg")
  target_scaled.scale(RESIZE_FACTOR)
  target = sc.Figure(width * SVG_TILE_SIZE * RESIZE_FACTOR, height * SVG_TILE_SIZE * RESIZE_FACTOR, target_scaled)
  target.save(f"{filename}.svg")
  print(f"inkscape --export-pdf={filename}.pdf {filename}.svg")


if __name__ == "__main__":
  if len(sys.argv) > 1:
    mappdf(sys.argv[1])
  else:
    exit(1)
