# Ctor: local descriptor {0,?,begin,end,elem} initialised via external thiscall on the local, then this->helper(&desc).
PATTERN = 'sub esp, N ; push esi ; push edi ; push N ; push N ; mov esi, ecx ; push N ; push N ; lea edi, [esi + N] ; push edi ; lea ecx, [esp + N] ; mov dword ptr [esp + N], N ; call EXT ; mov dword ptr [esp + N], edi ; lea eax, [esp + N] ; add edi, N ; push eax ; mov ecx, esi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], N ; call EXT ; pop edi ; mov eax, esi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """
struct Desc {
    unsigned a, b; char* begin; char* end; unsigned n;
    Desc() : a(0) {}
    void init(void* p, unsigned bytes, unsigned esz, unsigned al, unsigned z);
};
"""
def emit(va, A, N):
    off, tot, esz, al = 0x2c, N[4], N[3], N[2]
    # N order: 0x14,0,8,0x50,0x1400,0x2c,0x1c,0,... ; locate robustly
    tot = N[4]; esz = N[3]; al = N[2]
    src = """
struct C_%08x { char pad[0x2c]; char data[%d]; };
struct T_%08x { void m(Desc*); };
struct K_%08x : T_%08x { unsigned pad[11]; char data[%d]; K_%08x* ctor(); };
K_%08x* K_%08x::ctor() {
    Desc d;
    d.init(data, %d, %d, %d, 0);
    char* q = data;
    d.begin = q; q += %d; d.end = q; d.n = %d;
    m(&d);
    return this;
}
""" % (va, tot, va, va, va, tot, va, va, va, tot, esz, al, tot, esz)
    return src, "?ctor@K_%08x@@QAEPAU1@XZ" % va
