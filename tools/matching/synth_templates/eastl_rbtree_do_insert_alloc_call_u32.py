# eastl rbtree DoInsertValueImpl variant where node creation is a this-call helper (DoCreateNode(value)):
# side = (!force && parent != &anchor && value >= parent->key); node = this->Create(value);
# RBTreeInsert(node,parent,&anchor,side); ++size; *out = node.
PATTERN = 'cmp byte ptr [esp + N], N ; mov eax, dword ptr [esp + N] ; push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, ecx ; jne +N ; lea ecx, [esi + N] ; cmp ebp, ecx ; je +N ; mov edx, dword ptr [eax] ; cmp edx, dword ptr [ebp + N] ; jb +N ; mov ebx, N ; jmp +N ; xor ebx, ebx ; push eax ; mov ecx, esi ; call EXT ; mov edi, eax ; push ebx ; lea eax, [esi + N] ; push eax ; push ebp ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; add esp, N ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "struct It { void* p; It(void* q) : p(q) {} It(const It& o) : p(o.p) {} };\n"
def emit(va, A, N):
    src = ("struct T_%08x { int cmp; void* a[4]; unsigned sz;\n"
           "  char* Create(const unsigned* v);\n"
           "  static void Ins(char*, char*, char*, int);\n"
           "  It Impl(char* parent, const unsigned* value, bool force);\n"
           "};\n"
           "It T_%08x::Impl(char* parent, const unsigned* value, bool force) {\n"
           "    int side = (!force && parent != (char*)this + 4 && *value >= *(unsigned*)(parent + 0x10)) ? 1 : 0;\n"
           "    char* node = Create(value);\n"
           "    Ins(node, parent, (char*)this + 4, side);\n"
           "    ++sz; return It(node); }\n" % (va, va))
    return src, "?Impl@T_%08x@@QAE?AUIt@@PADPBI_N@Z" % va
