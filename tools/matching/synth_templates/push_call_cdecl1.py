# One-arg cdecl call with an absolute address argument: push imm32; call; pop ecx; ret
# Mostly atexit(<??__F dtor>) registrations emitted by file-scope globals with destructors,
# plus thunks calling a cdecl helper on the address of a global (e.g. FUN_011e5860(&g)).
# Plain /O2: the call target and pushed address are relocations, so only the shape matters.
import os, struct
import pefile

ATEXIT = 0x11e07ef
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def _callee(va):
    rel = struct.unpack("<i", _pe.get_data(va + 6 - _base, 4))[0]
    return va + 10 + rel

PATTERN = "push A ; call EXT ; pop ecx ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "#include <stdlib.h>\n"

def emit(va, A, N):
    a, tgt = A[0], _callee(va)
    if tgt == ATEXIT:
        src = ("void __cdecl FUN_%08x();\n"
               "void FUN_%08x() { atexit(FUN_%08x); }" % (a, va, a))
    else:
        src = ("extern char g_%08x;\nvoid __cdecl FUN_%08x(void*);\n"
               "void FUN_%08x() { FUN_%08x(&g_%08x); }" % (a, tgt, va, tgt, a))
    return src, "?FUN_%08x@@YAXXZ" % va
