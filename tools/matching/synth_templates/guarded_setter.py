# if (this->guard == 0) this->field = v;  thiscall setter
PATTERN = 'cmp dword ptr [ecx + N], N ; jne +N ; mov eax, dword ptr [esp + N] ; mov dword ptr [ecx + N], eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    g, s = N[0], N[3]
    src = ("struct S_%08x { char p0[%d]; int f; char p1[%d]; int guard;\n"
           "  void set(int v) { if (guard == 0) f = v; } };\n"
           "void FUN_%08x(S_%08x* s, int v) { s->set(v); }") % (va, s, g - s - 8, va, va)
    # need a real member symbol
    src = ("struct S_%08x { char p0[%d]; int f; char p1[%d]; int guard;\n"
           "  void set(int v); };\n"
           "void S_%08x::set(int v) { if (guard == 0) f = v; }") % (va, s, g - s - 4, va)
    return src, "?set@S_%08x@@QAEXH@Z" % va
