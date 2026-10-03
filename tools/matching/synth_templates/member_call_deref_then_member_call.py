# S2::f(P* p) { q->g(p, *p->h(1), K, 0); }  (p thiscall'd first)
PATTERN = 'push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; push N ; mov ecx, edi ; call EXT ; mov eax, dword ptr [eax] ; mov ecx, dword ptr [esi + N] ; push N ; push N ; push eax ; push edi ; call EXT ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """
struct P;
struct Q { void g(P* a, int b, int c, int d); };
struct P { int* h(int a); };
struct S { int pad[3]; Q* q; };
"""
def emit(va, A, N):
    return ("struct S2_%08x : S { void f(P* p); };\nvoid S2_%08x::f(P* p) { q->g(p, *p->h(1), %d, 0); }" % (va, va, N[4]),
            "?f@S2_%08x@@QAEXPAUP@@@Z" % va)
