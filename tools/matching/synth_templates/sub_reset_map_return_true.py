# bool Reset(): sub.Helper(sub.p, sub.n); sub.count = 0; return true;  (sub-object at offset N[1])
PATTERN = 'mov eax, dword ptr [ecx + N] ; push esi ; lea esi, [ecx + N] ; mov ecx, dword ptr [esi + N] ; push eax ; push ecx ; mov ecx, esi ; call EXT ; mov dword ptr [esi + N], N ; mov al, N ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    t = "%08x" % va
    off = N[1]
    src = ("struct S_%(t)s { unsigned pad; void* p; unsigned n; unsigned c; void H(void* p, unsigned n); void Clear() { H(p, n); c = 0; } };\n"
           "struct C_%(t)s { char pad[%(off)d]; S_%(t)s s; bool FUN_%(t)s(); };\n"
           "bool C_%(t)s::FUN_%(t)s() { s.Clear(); return true; }") % dict(t=t, off=off)
    src = src.replace("char pad[%d]" % off, "unsigned pad[%d]" % (off // 4))
    return src, "?FUN_%s@C_%s@@QAE_NXZ" % (t, t)
