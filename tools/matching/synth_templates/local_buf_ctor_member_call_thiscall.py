# Member function with a this-adjust (this-N) that builds a 0xa14-byte local via an external thiscall
# ctor(this-N, name_ptr, 0x1a80d26) and then calls external member m(arg) on it (trivial dtor):
#   sub esp,0xa14 ; push K ; add ecx,-N ; push P ; push ecx ; lea ecx,[esp+0xc] ; call ctor ; mov eax,[esp+0xa18]
#   push eax ; lea ecx,[esp+4] ; call m ; add esp,0xa14 ; ret 4
# Needs /GS- (the char[] local would otherwise get a stack cookie). Call targets are relocations (masked).
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'sub esp, N ; push A ; add ecx, -N ; push A ; push ecx ; lea ecx, [esp + N] ; call EXT ; mov eax, dword ptr [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ""

def _tgt(va, off):
    rel = struct.unpack("<i", _pe.get_data(va + off + 1 - _base, 4))[0]
    return (va + off + 5 + rel) & 0xffffffff

def emit(va, A, N):
    t = "%08x" % va
    code = _pe.get_data(va - _base, 0x13)
    adj = 0x100 - code[13]
    key = struct.unpack("<I", code[7:11])[0]
    ptr = struct.unpack("<I", code[15:19])[0]
    size = struct.unpack("<I", code[2:6])[0]
    c1, c2 = "%08x" % _tgt(va, 0x18), "%08x" % _tgt(va, 0x29)
    src = ("struct B_%s_%s { char d[%d]; B_%s_%s(void*, const void*, int); void m_%s(int); };\n"
           "struct C_%s { void FUN_%s(int a); };\n"
           "void C_%s::FUN_%s(int a) { B_%s_%s b((char*)this - %d, (const void*)0x%x, 0x%x); b.m_%s(a); }\n"
           ) % (t, c2, size, t, c2, c2, t, t, t, t, t, c2, adj, ptr, key, c2)
    return src, "?FUN_%s@C_%s@@QAEXH@Z" % (t, t)
