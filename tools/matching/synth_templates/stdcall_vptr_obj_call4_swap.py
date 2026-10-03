# stdcall(a,b,c,d) { Obj o; o.vptr=&vt; o.f=<float imm>; o.x=d; ext(b,a,c,&o); }
# Stack temp of a 12-byte polymorphic object built inline, passed by pointer to a stdcall callee.
PATTERN = 'sub esp, N ; mov eax, dword ptr [esp + N] ; mov dword ptr [esp + N], eax ; mov eax, dword ptr [esp + N] ; lea edx, [esp] ; push edx ; mov edx, dword ptr [esp + N] ; push eax ; mov eax, dword ptr [esp + N] ; push edx ; push eax ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], A ; call EXT ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct LocalObj { const void* vp; unsigned f; unsigned x; };
"""
def emit(va, A, N):
    return ("""extern const int g_%08x[];\nvoid __stdcall ext_%08x(unsigned, unsigned, unsigned, LocalObj*);
void __stdcall FUN_%08x(unsigned a, unsigned b, unsigned c, unsigned d) { LocalObj o; o.x = d; o.f = 0x%x; o.vp = g_%08x; ext_%08x(b, a, c, &o); }""" % (A[1], va, va, A[0], A[1], va),
            "?FUN_%08x@@YGXIIII@Z" % va)
