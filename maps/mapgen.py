import sys
from struct import pack

def mapgen(filename):
  file = open(filename, 'r')
  target = open(filename + '.map', 'wb')
  contents = file.read()

  lines = contents.strip().split("\n")
  target.write(pack('>H', len(lines[0])))
  target.write(pack('>H', len(lines)))

  first_nibble = False
  temp_byte = 0
  for char in contents.replace('\n', '').strip():
    first_nibble = not first_nibble
    num = int(char, 16)
    temp_byte |= num << (4 * first_nibble)
    if not first_nibble:
      target.write(pack('B', temp_byte))
      temp_byte = 0
  if first_nibble: target.write(pack('B', temp_byte))

  file.close()
  target.close()

if __name__ == "__main__":
  if len(sys.argv) > 1:
    mapgen(sys.argv[1])
  else:
    exit(1)
