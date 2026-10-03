# Thiscall getter: unsigned char r = f & mask; return r;  -> mov al,[ecx+N]; and al,mask; ret
PATTERN = "mov al, byte ptr [ecx + N] ; and al, N ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, mask = N[0], N[1]
    return ("struct S_%08x { char pad[%d]; unsigned char f; unsigned char get(); };\n"
            "unsigned char S_%08x::get() { unsigned char r = f & %d; return r; }" % (va, off, va, mask)), "?get@S_%08x@@QAEEXZ" % va
