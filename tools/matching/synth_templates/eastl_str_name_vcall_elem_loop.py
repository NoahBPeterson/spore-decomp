# Pattern 615 (5 instances, ~330 bytes): bool F(Obj* o, const wchar16* name, Vec* v): if vec non-empty, builds a
# string from name (name ? Mk(name,-1) : String(0)), calls o->v0(c_str), loops 32-byte elements
# ok = ok && Elem(o, 0, &e->f4), calls o->v1(c_str); returns ok.
PATTERN = 'sub esp, N ; push esi ; mov esi, dword ptr [esp + N] ; mov ecx, dword ptr [esi] ; push edi ; xor edi, edi ; mov al, N ; mov dword ptr [esp + N], edi ; mov byte ptr [esp + N], al ; cmp ecx, dword ptr [esi + N] ; je +N ; mov eax, dword ptr [esp + N] ; push ebx ; push ebp ; cmp eax, edi ; je +N ; push -N ; push eax ; lea edx, [esp + N] ; push edx ; lea ebx, [edi + N] ; call EXT ; add esp, N ; jmp +N ; push edi ; lea ecx, [esp + N] ; mov ebx, N ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; mov dword ptr [esp + N], edi ; call EXT ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; call EXT ; test bl, N ; je +N ; mov ecx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub ecx, eax ; and ecx, A ; and ebx, A ; cmp ecx, N ; jle +N ; cmp eax, edi ; je +N ; push eax ; call EXT ; add esp, N ; test bl, N ; je +N ; mov edx, dword ptr [esp + N] ; mov eax, dword ptr [esp + N] ; sub edx, eax ; and edx, A ; cmp edx, N ; jle +N ; cmp eax, edi ; je +N ; push eax ; call EXT ; add esp, N ; mov edi, dword ptr [esp + N] ; mov ebp, dword ptr [esp + N] ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax] ; mov ecx, edi ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebp ; jmp +N ; push A ; call edx ; mov eax, dword ptr [esp + N] ; mov esi, dword ptr [esi] ; mov ebx, dword ptr [eax + N] ; cmp esi, ebx ; je +N ; mov edi, edi ; cmp byte ptr [esp + N], N ; je +N ; lea ecx, [esi + N] ; push ecx ; push N ; push edi ; call EXT ; add esp, N ; mov byte ptr [esp + N], N ; test al, al ; jne +N ; mov byte ptr [esp + N], N ; add esi, N ; cmp esi, ebx ; jne +N ; mov edx, dword ptr [edi] ; mov eax, dword ptr [edx + N] ; mov ecx, edi ; cmp ebp, dword ptr [esp + N] ; je +N ; push ebp ; jmp +N ; push A ; call eax ; mov ecx, dword ptr [esp + N] ; sub ecx, ebp ; and ecx, A ; cmp ecx, N ; jle +N ; test ebp, ebp ; je +N ; push ebp ; call EXT ; add esp, N ; mov al, byte ptr [esp + N] ; pop ebp ; pop ebx ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = """typedef unsigned short wchar16;
void EASTL_allocator_deallocate(void* p);
extern const wchar16 kEmpty[];
struct Alloc2 { const char* mpName; };
struct WString {
    wchar16* mpBegin; wchar16* mpEnd; wchar16* mpCap; Alloc2 a;
    WString(int n) : mpEnd(0), mpCap(0) { a.mpName = 0; Init(n); }
    void Init(int);
    const wchar16* c_str() const { return mpBegin != mpEnd ? mpBegin : kEmpty; }
    WString(const WString&);
    ~WString() { if ((mpCap - mpBegin) > 1 && mpBegin) EASTL_allocator_deallocate(mpBegin); }
};
struct Obj { virtual void v0(const wchar16*); virtual void v1(const wchar16*); };
struct Elem { int f0; int f4; int pad[6]; };
struct Vec { Elem* b; Elem* e; };
WString Mk(const wchar16*, int);
bool ElemFn(Obj*, int, void*);
extern const wchar16 kEmpty[];
"""
def emit(va, A, N):
    src = ("bool FUN_%08x(Obj* o, const wchar16* name, Vec* v) {\n"
           "    bool ok = true; const wchar16* b;\n"
           "    if (v->b != v->e) {\n"
           "        WString s(name ? Mk(name, -1) : WString(0));\n"
           "        const wchar16* b = s.mpBegin; o->v0(b != s.mpEnd ? b : kEmpty);\n"
           "        for (Elem* p = v->b, *e = v->e; p != e; ++p) ok = ok && ElemFn(o, 0, &p->f4);\n"
           "        o->v1(b != s.mpEnd ? b : kEmpty);\n"
           "    }\n    return ok;\n}\n") % va
    return src, "?FUN_%08x@@YA_NPAUObj@@PBGPAUVec@@@Z" % va
