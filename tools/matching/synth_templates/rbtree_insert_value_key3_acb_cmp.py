# rbtree DoInsertValueImpl: key of 3 u32 compared a, then c, then b (inline); node created via out-of-line member; RBTreeInsert; ++size.
PATTERN = 'cmp byte ptr [esp + N], N ; mov edx, dword ptr [esp + N] ; push ebx ; mov ebx, dword ptr [esp + N] ; push ebp ; push esi ; push edi ; mov esi, ecx ; jne +N ; lea eax, [esi + N] ; cmp ebx, eax ; je +N ; mov eax, dword ptr [edx] ; mov ecx, dword ptr [ebx + N] ; cmp eax, ecx ; jne +N ; mov eax, dword ptr [edx + N] ; mov ecx, dword ptr [ebx + N] ; cmp eax, ecx ; jne +N ; mov ecx, dword ptr [edx + N] ; cmp ecx, dword ptr [ebx + N] ; setb al ; test al, al ; jne +N ; mov ebp, N ; jmp +N ; xor ebp, ebp ; push edx ; mov ecx, esi ; call EXT ; push ebp ; lea edx, [esi + N] ; push edx ; mov edi, eax ; push ebx ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; add esp, N ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "struct It { void* p; It(void* q) : p(q) {} It(const It& o) : p(o.p) {} };\nstruct K3 { unsigned a, b, c; };\ninline bool K3Less(const K3& x, const K3& y) { if (x.a != y.a) return x.a < y.a; if (x.c != y.c) return x.c < y.c; return x.b < y.b; }\n"
def emit(va, A, N):
    src = ("void __cdecl ins_%08x(char*, char*, char*, int);\n"
           "struct T_%08x { int cmp; char anchor[16]; unsigned sz;\n"
           "  char* Create(const K3*);\n"
           "  It Impl(char* parent, const K3* value, bool force);\n};\n"
           "It T_%08x::Impl(char* parent, const K3* value, bool force) {\n"
           "    int side = (!force && parent != anchor && !K3Less(*value, *(K3*)(parent + 0x10))) ? 1 : 0;\n"
           "    char* node = Create(value);\n"
           "    ins_%08x(node, parent, anchor, side);\n"
           "    ++sz; return It(node); }\n" % (va, va, va, va))
    return src, "?Impl@T_%08x@@QAE?AUIt@@PADPBUK3@@_N@Z" % va
