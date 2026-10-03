# Indirect tail jump "jmp dword ptr [A]" (6 bytes, ff 25 abs32).
# Most instances are linker-generated import thunks (jmp [__imp_X]) for DLL functions called without
# __declspec(dllimport) (steam_api, msvcr90, imm32, ...); a few are non-import stubs jumping through a
# function-pointer global. The real import thunks come from the import library at link time, not from
# cl; this template reproduces the identical bytes with /O2 tail-calling an extern function pointer
# named from the IAT slot address. The abs32 operand is a relocation (masked), and the stub leaves
# ecx/stack untouched, so arguments pass through exactly like the original thunk.
# synth.py skips jmp operands, so the slot address is read from the image bytes.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "jmp dword ptr [A]"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    b = _pe.get_data(va - _base, 6)
    p = "g_%08x" % struct.unpack("<I", b[2:6])[0]
    src = "extern void (*%s)();\nvoid FUN_%08x() { %s(); }" % (p, va, p)
    return src, "?FUN_%08x@@YAXXZ" % va
