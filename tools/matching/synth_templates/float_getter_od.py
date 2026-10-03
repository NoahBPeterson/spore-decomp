# Member float getter at /Od: stores this in a local, fld dword [eax+off].
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; fld dword ptr [eax + N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[-1]
    c = "C_%08x" % va
    src = ("struct %s { char pad[%d]; float f; float FUN_%08x(); };\n"
           "float %s::FUN_%08x() { return f; }\n") % (c, off, va, c, va)
    return src, "?FUN_%08x@%s@@QAEMXZ" % (va, c)
