# Vector-like dtor in a /GS- module: erase(begin,end) then member Buf dtor frees begin if begin && begin[-1].
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push esi ; mov esi, ecx ; mov dword ptr [esp + N], esi ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi] ; push eax ; push ecx ; mov ecx, esi ; mov dword ptr [esp + N], N ; call EXT ; mov esi, dword ptr [esi] ; test esi, esi ; je +N ; cmp dword ptr [esi - N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov ecx, dword ptr [esp + N] ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = ("void EASTL_allocator_deallocate(void* p) throw();\n"
           "struct Buf { int* p; ~Buf() { if (p && p[-1]) EASTL_allocator_deallocate(p); } };\n")

def emit(va, A, N):
    t = "V_%08x" % va
    src = ("struct %s { Buf b; int* e; void erase(int*, int*); ~%s(); };\n"
           "%s::~%s() { erase(b.p, e); }\n" % (t, t, t, t))
    return src, "??1%s@@QAE@XZ" % t
