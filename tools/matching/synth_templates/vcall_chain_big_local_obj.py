# bool __thiscall T::f(R* r): r->v8()->v6() gets a service, F1(svc,&key,1,0) cdecl, then a ~2.5KB local object
# constructed thiscall as obj(this, &global, 0x1a80d26) and queried with obj.m(r); returns result != 0.
# Status: NOT byte-exact. Only diff: key store lands right after the first call instead of just before the get() call.
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax + N] ; push edi ; mov edi, ecx ; mov ecx, esi ; call edx ; mov edx, dword ptr [eax] ; mov ecx, eax ; mov eax, dword ptr [edx + N] ; mov dword ptr [esp + N], A ; call eax ; push N ; push N ; lea ecx, [esp + N] ; push ecx ; push eax ; call EXT ; add esp, N ; push A ; push A ; push edi ; lea ecx, [esp + N] ; call EXT ; push esi ; lea ecx, [esp + N] ; call EXT ; test al, al ; pop edi ; setne al ; pop esi ; add esp, N ; ret N'
import os
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """typedef unsigned int u32;
struct Svc { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void* get(); };
struct Res { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual Svc* svc(); };
struct Key { u32 v; Key(u32 a) : v(a) {} };
struct Big { u32 d[645]; Big(void* t, const void* g, u32 k); char m(Res* r); };
void Reg(void* s, const u32* key, int a, int b);
"""
def emit(va, A, N):
    key, k2, g = A[0], A[1], A[2]
    src = ("struct T_%08x { bool f(Res* r); };\n"
           "extern char g_%08x[];\n"
           "bool T_%08x::f(Res* r) {\n"
           "  Svc* s = r->svc();\n  u32 key;\n  void* x = (key = 0x%x, s->get());\n  Reg(x, &key, 1, 0);\n"
           "  Big b(this, g_%08x, 0x%x);\n"
           "  return b.m(r) ? true : false;\n}" % (va, g, va, key, g, k2))
    return src, "?f@T_%08x@@QAE_NPAURes@@@Z" % va
