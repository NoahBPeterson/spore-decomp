# __thiscall method returning a 2-float struct by value (hidden sret ptr, ret 4)
# whose fields are copied from this+N / this+N+4 (x87 fld/fstp under /O2).
PATTERN = 'mov eax, dword ptr [esp + N] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax] ; fld dword ptr [ecx + N] ; fstp dword ptr [eax + N] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct V2 { float x, y; };\n"
def emit(va, A, N):
    off = N[1]
    src = ("struct C_%08x { unsigned int pad[%d]; float x, y; V2 FUN_%08x(); };\n"
           "V2 C_%08x::FUN_%08x() { V2 r = { x, y }; return r; }\n" % (va, off // 4, va, va, va))
    return src, "?FUN_%08x@C_%08x@@QAE?AUV2@@XZ" % (va, va)
