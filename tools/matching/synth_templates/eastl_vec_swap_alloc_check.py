# Member swap(V& o) of a 3-pointer EASTL vector (20-byte object, allocator tag at p[-1]):
# fast pointer swap when both own null/non-fixed storage, else copy temp, assign both ways, free temp.
# No /EHsc: original has no EH frame. Field swaps via helper sw() give the right schedule.
PATTERN = 'sub esp, N ; push esi ; mov esi, ecx ; mov ecx, dword ptr [esi] ; push edi ; mov edi, dword ptr [esp + N] ; test ecx, ecx ; je +N ; cmp dword ptr [ecx - N], N ; je +N ; mov eax, dword ptr [edi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; jne +N ; push esi ; lea ecx, [esp + N] ; call EXT ; push edi ; mov ecx, esi ; call EXT ; lea eax, [esp + N] ; push eax ; mov ecx, edi ; call EXT ; mov eax, dword ptr [esp + N] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; pop edi ; pop esi ; add esp, N ; ret N ; mov dword ptr [esi], eax ; mov dword ptr [edi], ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [edi + N] ; mov dword ptr [esi + N], ecx ; mov dword ptr [edi + N], eax ; mov edx, dword ptr [edi + N] ; mov eax, dword ptr [esi + N] ; mov dword ptr [esi + N], edx ; mov dword ptr [edi + N], eax ; pop edi ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP", "/GR-"]
PRELUDE = """void EASTL_allocator_deallocate(void* p);
static inline void sw(int*& a, int*& b) { int* t = a; a = b; b = t; }
"""
def emit(va, A, N):
    t = "%08x" % va
    src = ("struct C_%s { int* b; int* e; int* c; int x; int y;\n"
           " C_%s(const C_%s&); void assign(const C_%s&);\n"
           " ~C_%s() { if (b && b[-1]) EASTL_allocator_deallocate(b); }\n"
           " void FUN_%s(C_%s& o); };\n"
           "void C_%s::FUN_%s(C_%s& o) {\n"
           " if ((!b || b[-1]) && (!o.b || o.b[-1])) { sw(b, o.b); sw(e, o.e); sw(c, o.c); }\n"
           " else { C_%s tmp(*this); assign(o); o.assign(tmp); } }") % ((t,) * 11)
    return src, "?FUN_%s@C_%s@@QAEXAAU1@@Z" % (t, t)
