# Swap of a fixed_vector<short>-like EASTL vector (b,e,c + 8-byte allocator at +0xc whose second dword is the fixed buffer):
# allocators compare by address; equal -> swap 3 ptrs; else copy to temp, assign both ways, ~tmp frees if heap-allocated.
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, ecx ; lea eax, [esi + N] ; lea ecx, [edi + N] ; cmp ecx, eax ; jne +N ; mov edx, dword ptr [esi] ; mov eax, dword ptr [edi] ; mov dword ptr [edi], edx ; mov dword ptr [esi], eax ; mov eax, dword ptr [edi + N] ; mov ecx, dword ptr [esi + N] ; mov dword ptr [edi + N], ecx ; mov dword ptr [esi + N], eax ; mov edx, dword ptr [esi + N] ; mov eax, dword ptr [edi + N] ; mov dword ptr [edi + N], edx ; pop edi ; mov dword ptr [esi + N], eax ; pop esi ; add esp, N ; ret N ; push edi ; lea ecx, [esp + N] ; call EXT ; cmp esi, edi ; je +N ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi] ; push eax ; push ecx ; mov ecx, edi ; call EXT ; mov edi, dword ptr [esp + N] ; lea edx, [esp + N] ; cmp edx, esi ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; push edi ; mov ecx, esi ; call EXT ; mov ecx, dword ptr [esp + N] ; sub ecx, edi ; and ecx, A ; cmp ecx, N ; jle +N ; test edi, edi ; je +N ; cmp edi, dword ptr [esp + N] ; je +N ; push edi ; call EXT ; add esp, N ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\nstatic inline void sw(short*& a, short*& b) { short* t = a; a = b; b = t; }\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct Al_@ { int pad; short* buf; };\n"
           "inline bool operator==(const Al_@& a, const Al_@& b) { return &a == &b; }\n"
           "struct V_@ { short* b; short* e; short* c; Al_@ a;\n"
           " void init(const V_@&); void assign(short* f, short* l);\n"
                      " void FUN_@(V_@& o); };\n"
           "void V_@::FUN_@(V_@& o) {\n"
           " if (a == o.a) { sw(b, o.b); sw(e, o.e); sw(c, o.c); }\n"
           " else { V_@ tmp; tmp.init(*this); if (&o != this) assign(o.b, o.e); short* tb = tmp.b; if (&tmp != &o) o.assign(tb, tmp.e); if ((tmp.c - tb) > 1 && tb && tb != tmp.a.buf) EASTL_allocator_deallocate(tb); } }")
    return src.replace("@", t), "?FUN_%s@V_%s@@QAEXAAU1@@Z" % (t, t)
