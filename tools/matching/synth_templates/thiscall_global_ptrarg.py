# Calls a one-arg __thiscall member on a file-scope global, passing the address of another global:
#   push offset data; mov ecx, offset g; call Obj::method; ret
# /O2 cannot turn this into a tail jump (callee pops its stack arg with ret 4). Most instances are
# probably dynamic initializers "Obj g(&data);" (the callee 0x695450 is shared by many) or
# registration thunks; the shape is identical either way, so a plain function is emitted.
PATTERN = "push A ; mov ecx, A ; call EXT ; ret "
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct GlobalObj { void Method(void*); };\n"

def emit(va, A, N):
    d, g = "g_%08x" % A[0], "g_%08x" % A[1]
    src = ("extern char %s;\nextern GlobalObj %s;\n"
           "void FUN_%08x() { %s.Method(&%s); }" % (d, g, va, g, d))
    return src, "?FUN_%08x@@YAXXZ" % va
