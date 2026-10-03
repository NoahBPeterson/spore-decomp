# bool __thiscall setter: stores arg at [this+off], returns true. /O2.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov dword ptr [ecx + N], eax ; mov al, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[1]
    pad = off // 4
    src = ("struct S%08x { int p[%d]; int v; bool f(int x); };\n"
           "bool S%08x::f(int x) { v = x; return true; }\n") % (va, pad, va)
    return src, "?f@S%08x@@QAE_NH@Z" % va
