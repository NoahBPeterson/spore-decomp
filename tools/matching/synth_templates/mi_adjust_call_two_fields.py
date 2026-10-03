# Method in secondary base (at +adj) calling primary-base method h(out, a->fa, b->fb); returns out.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov edx, dword ptr [eax + N] ; mov eax, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; push edx ; mov edx, dword ptr [eax + N] ; push edx ; push esi ; add ecx, -N ; call EXT ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    fb, fa, adj = N[1], N[4], N[5]
    s = """struct R%(v)08x { int p; };
struct X%(v)08x { int d[%(m)d]; };
struct P%(v)08x { virtual void y(); R%(v)08x* h(R%(v)08x*, int, int); int pad[%(pp)d]; };
struct S%(v)08x { virtual void z(); R%(v)08x* f(R%(v)08x*, X%(v)08x*, X%(v)08x*); };
struct D%(v)08x : P%(v)08x, S%(v)08x {};
R%(v)08x* S%(v)08x::f(R%(v)08x* o, X%(v)08x* a, X%(v)08x* b) { ((P%(v)08x*)((char*)this - %(adj)d))->h(o, a->d[%(fa)d], b->d[%(fb)d]); return o; }
""" % dict(adj=adj, v=va, m=16, pp=(adj - 4) // 4, fa=fa // 4, fb=fb // 4)
    return s, "?f@S%08x@@QAEPAUR%08x@@PAU2@PAUX%08x@@1@Z" % (va, va, va)
