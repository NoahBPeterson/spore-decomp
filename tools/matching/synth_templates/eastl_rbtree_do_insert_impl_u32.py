# eastl rbtree DoInsertValueImpl(pParent, value, bForceToLeft) for a u32-keyed node, returning iterator via out ptr:
# side = (!force && parent != &anchor && value >= parent->key); node = EASTL alloc(size,name,0,0,file,line);
# placement-construct value at node+0x10 (null-checked); RBTreeInsert(node,parent,&anchor,side); ++size.
PATTERN = 'cmp byte ptr [esp + N], N ; push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, ecx ; jne +N ; lea eax, [esi + N] ; cmp ebp, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; cmp edx, dword ptr [ebp + N] ; jb +N ; mov ebx, N ; jmp +N ; xor ebx, ebx ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov edi, eax ; lea ecx, [edi + N] ; add esp, N ; test ecx, ecx ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; call EXT ; push ebx ; lea ecx, [esi + N] ; push ecx ; push ebp ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; add esp, N ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ("typedef unsigned int size_t;\n"
           "void* EAlloc(size_t sz, const char* name, int f, unsigned df, const char* file, int line);\n"
           "struct It { void* p; It(void* q) : p(q) {} It(const It& o) : p(o.p) {} };\n"
           "inline void* operator new(size_t, void* p) { return p; }\n")
def emit(va, A, N):
    import sys
    if va == 0x5a9690: print("DBG", A, N, file=sys.stderr)
    # A[0]=file, A[1]=name (push order)
    line, size = N[7], N[10]
    for i, n in enumerate(N):
        pass
    t = "T_%08x" % va
    src = ("struct V_%08x { V_%08x(const unsigned&); };\n"
           "struct T_%08x { int cmp; void* a[4]; unsigned sz;\n"
           "  It Impl( char* parent, const unsigned* value, bool force);\n"
           "  static void Ins(char*, char*, char*, int);\n"
           "};\n"
           "It T_%08x::Impl( char* parent, const unsigned* value, bool force) {\n"
           "    int side = (!force && parent != (char*)this + 4 && *value >= *(unsigned*)(parent + 0x10)) ? 1 : 0;\n"
           "    char* node = (char*)EAlloc(%d, (const char*)%d, 0, 0, (const char*)%d, %d);\n"
           "    new (node + 0x10) V_%08x(*value);\n"
           "    Ins(node, parent, (char*)this + 4, side);\n"
           "    ++sz; return It(node); }\n"
           % (va, va, va, va, size, A[1], A[0], line, va))
    return src, "?Impl@T_%08x@@QAE?AUIt@@PADPBI_N@Z" % va
