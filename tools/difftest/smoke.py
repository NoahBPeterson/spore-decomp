import sys
sys.path.insert(0, __file__.rsplit("/", 1)[0])
from emu import Emulator, install_crt
e = Emulator(sys.argv[1]); install_crt(e)
s = e.alloc(16, b"Prop\0")
print(hex(e.call(0x68C680, s, 4)))
