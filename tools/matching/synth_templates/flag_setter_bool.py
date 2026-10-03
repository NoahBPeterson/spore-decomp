# thiscall bool flag setter: if (b) flags |= bit; else flags &= ~bit;
PATTERN = 'cmp byte ptr [esp + N], N ; je +N ; or dword ptr [ecx + N], N ; ret N ; and dword ptr [ecx + N], A ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, bit = N[2], N[3]
    pad = off // 4
    s = ("struct C_%08x { unsigned pad[%d]; unsigned flags; void f(bool b); };\n"
         "void C_%08x::f(bool b) { if (b) flags |= 0x%x; else flags &= ~0x%xu; }") % (va, pad, va, bit, bit)
    return s, "?f@C_%08x@@QAEX_N@Z" % va
