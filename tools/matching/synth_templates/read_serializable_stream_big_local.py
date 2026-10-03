# ISimulatorSerializable::Read-like: vcall chain on stream, cdecl helper with small local,
# two member calls on this, ctor of a ~2.5KB local (no dtor), method call on that local.
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push esi ; mov ecx, edi ; call EXT ; push esi ; lea ecx, [edi + N] ; call EXT ; push A ; push A ; push edi ; lea ecx, [esp + N] ; call EXT ; push esi ; lea ecx, [esp + N] ; call EXT ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """
struct Id2 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual int id(); };
struct Strm { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual Id2* get(); };
struct Small { int a; };
struct Big { unsigned pad[0x285]; Big(void* o, const char* name, int n); void go(Strm* s); };
struct Sub { int x; void put(Strm* s); };
void __cdecl helper(int id, Small* out, int a, int b);
"""
def emit(va, A, N):
    n = "S_%08x" % va
    src = """struct %s { char pad[0x34]; Sub sub; void f(Strm* s); void g1(Strm* s); };
void %s::f(Strm* s) {
    Small sm;
    int id = s->get()->id();
    helper(id, &sm, 1, 0);
    g1(s);
    sub.put(s);
    Big b((void*)this, (const char*)0x%x, 0x%x);
    b.go(s);
}
""" % (n, n, A[1], A[0])
    return src, "?f@%s@@QAEXPAUStrm@@@Z" % n
