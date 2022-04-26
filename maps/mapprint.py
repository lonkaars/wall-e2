import sys
from struct import unpack

def mapprint(filename):
  file = open(filename, 'rb')
  contents = file.read()
  file.close()

  width, height = unpack('>HH', contents[0:4])

  for y in range(height):
    for x in range(width):
      nibble = x + y * width
      byte = int(nibble / 2)
      shift = byte * 2 - nibble + 1
      num = (contents[4 + byte] & (0xf << 4 * shift)) >> 4 * shift
      print(" ─│┘──└┴│┐│┤┌┬├┼"[num], end='')
    print("\n", end='')

if __name__ == "__main__":
  if len(sys.argv) > 1:
    mapprint(sys.argv[1])
  else:
    exit(1)
