# EASTL vector<POD>::DoAssign(first,last, tag) for trivially-copyable elements (memcpy path), /O2.
# Element size from the sar shift (N[3]); DoAllocateAndCopy is an out-of-line thiscall.
PATTERN = 'mov eax, dword ptr [esp + N] ; push ebx ; push ebp ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; mov esi, ecx ; mov ecx, dword ptr [esi] ; mov edx, dword ptr [esi + N] ; mov ebp, edi ; sub ebp, eax ; sub edx, ecx ; mov ebx, ebp ; sar ebx, N ; sar edx, N ; cmp ebx, edx ; jbe +N ; push edi ; push eax ; push ebx ; mov ecx, esi ; call EXT ; mov edi, eax ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp eax, dword ptr [esi + N] ; je +N ; push eax ; call EXT ; add esp, N ; lea eax, [edi + ebx*N] ; mov dword ptr [esi], edi ; pop edi ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; pop esi ; pop ebp ; pop ebx ; ret N ; mov edx, dword ptr [esi + N] ; sub edx, ecx ; sar edx, N ; cmp ebx, edx ; ja +N ; push ebp ; push eax ; push ecx ; call EXT ; add esp, N ; lea eax, [eax + ebx*N] ; pop edi ; mov dword ptr [esi + N], eax ; pop esi ; pop ebp ; pop ebx ; ret N ; lea ebx, [eax + edx*N] ; mov edx, ebx ; sub edx, eax ; push edx ; push eax ; push ecx ; call EXT ; mov eax, dword ptr [esi + N] ; sub edi, ebx ; push edi ; push ebx ; push eax ; call EXT ; add esp, N ; sar edi, N ; lea eax, [eax + edi*N] ; pop edi ; mov dword ptr [esi + N], eax ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''typedef unsigned int size_t;
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
void __cdecl EASTL_allocator_deallocate(void* p);
'''
def emit(va, A, N):
    sz = 1 << N[3]
    h = "vec_%08x" % va
    src = ("struct %(h)s_T { char b[%(sz)d]; };\n"
           "struct %(h)s {\n"
           "    %(h)s_T *mpBegin, *mpEnd, *mpCapacity; void* mAlloc; void* mAlloc2;\n"
           "    static %(h)s_T* cp(const %(h)s_T* f, const %(h)s_T* l, %(h)s_T* r) { return (%(h)s_T*)memcpy(r, f, (size_t)((char*)l - (char*)f)) + (l - f); }\n"
           "    %(h)s_T* DoAllocateAndCopy(size_t n, const %(h)s_T* f, const %(h)s_T* l);\n"
           "    void DoAssign(const %(h)s_T* first, const %(h)s_T* last, int tag);\n"
           "};\n"
           "void %(h)s::DoAssign(const %(h)s_T* first, const %(h)s_T* last, int) {\n"
           "    const size_t n = (size_t)(last - first);\n"
           "    if (n > (size_t)(mpCapacity - mpBegin)) {\n"
           "        %(h)s_T* p = DoAllocateAndCopy(n, first, last);\n"
           "        if (mpBegin && mpBegin != (%(h)s_T*)mAlloc2) EASTL_allocator_deallocate(mpBegin);\n"
           "        mpBegin = p; mpEnd = mpCapacity = p + n;\n"
           "    } else if (n <= (size_t)(mpEnd - mpBegin)) {\n"
           "        mpEnd = cp(first, last, mpBegin);\n"
           "    } else {\n"
           "        const %(h)s_T* mid = first + (mpEnd - mpBegin);\n"
           "        cp(first, mid, mpBegin);\n"
           "        mpEnd = cp(mid, last, mpEnd);\n"
           "    }\n"
           "}") % dict(h=h, sz=sz)
    return src, "?DoAssign@%s@@QAEXPBU%s_T@@0H@Z" % (h, h)
