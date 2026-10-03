# Null-tested (this - a) then returns this - b. Raw pointer arithmetic on a thiscall member; MSVC
# keeps the test on the adjusted pointer and recomputes lea eax,[ecx-b] (static_cast forms add a
# this null check or "add eax, imm").
PATTERN = 'lea eax, [ecx - N] ; test eax, eax ; je +N ; lea eax, [ecx - N] ; ret  ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    a, b = N[0], N[1]
    return ("struct T_%(v)08x { char c; void* f(); };\n"
            "void* T_%(v)08x::f() { char* p = (char*)this; if (p - %(a)d != 0) return p - %(b)d; return 0; }\n"
            % dict(v=va, a=a, b=b),
            "?f@T_%08x@@QAEPAXXZ" % va)
