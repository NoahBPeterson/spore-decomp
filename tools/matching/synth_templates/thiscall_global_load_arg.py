# Calls a one-arg __thiscall member on a file-scope global, passing a 32-bit value loaded from
# another global (typically the field 12 bytes past the object, i.e. "g.Method(g.field)"):
#   mov eax,[v]; push eax; mov ecx, offset g; call Obj::method; ret
PATTERN = "mov eax, dword ptr [A] ; push eax ; mov ecx, A ; call EXT ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct GlobalObj { void Method(unsigned); };\n"

def emit(va, A, N):
    v, g = "g_%08x" % A[0], "g_%08x" % A[1]
    src = ("extern unsigned %s;\nextern GlobalObj %s;\n"
           "void FUN_%08x() { %s.Method(%s); }" % (v, g, va, g, v))
    return src, "?FUN_%08x@@YAXXZ" % va
