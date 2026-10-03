# Pure tail-call thunk: a single "jmp target" (5 bytes, e9 rel32).
# /O2 turns "void f() { g(); }" into a tail jump; the same bytes also come from thunk_FUN_* stubs
# and forwarding wrappers (e.g. UI::CursorAttachment::Initialize -> real Initialize) whose
# arguments/this are passed through untouched (ecx and stack are left as-is). The rel32 target is a
# relocation (masked), so a void() cdecl callee suffices; the callee is named after its real VA.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = "jmp EXT"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    b = _pe.get_data(va - _base, 5)
    tgt = "FUN_%08x" % ((va + 5 + struct.unpack("<i", b[1:5])[0]) & 0xffffffff) if b[0] == 0xE9 else "FUN_%08x_tgt" % va
    src = "void %s();\nvoid FUN_%08x() { %s(); }" % (tgt, va, tgt)
    return src, "?FUN_%08x@@YAXXZ" % va
