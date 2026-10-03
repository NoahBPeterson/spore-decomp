# Lazy getter: if (!m_x) Init(); return m_x;  (thiscall helper on same object)
PATTERN = 'push esi ; mov esi, ecx ; cmp dword ptr [esi + N], N ; jne +N ; call EXT ; mov eax, dword ptr [esi + N] ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[0]
    pad = "char pad[%d]; " % off if off else ""
    src = ("struct S_%08x { %sint v; void Init(); int Get(); };\n"
           "int S_%08x::Get() { if (v == 0) Init(); return v; }" % (va, pad, va))
    return src, "?Get@S_%08x@@QAEHXZ" % va
