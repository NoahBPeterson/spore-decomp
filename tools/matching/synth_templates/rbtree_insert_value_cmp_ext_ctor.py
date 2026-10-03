# eastl rbtree DoInsertValueImpl (8-byte key compared via external cmp), DoCreateNode inlined:
# EASTL_allocator_allocate(size,name,0,0,file,line); ctor(node+0x10, value); RBTreeInsert; ++size; *out=node.
PATTERN = 'cmp byte ptr [esp + N], N ; push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, ecx ; jne +N ; lea eax, [esi + N] ; cmp ebp, eax ; je +N ; mov ecx, dword ptr [ebp + N] ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [ebp + N] ; push ecx ; mov ecx, dword ptr [eax + N] ; push edx ; mov edx, dword ptr [eax] ; push ecx ; push edx ; call EXT ; add esp, N ; test eax, eax ; jl +N ; mov ebx, N ; jmp +N ; xor ebx, ebx ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov edi, eax ; lea ecx, [edi + N] ; add esp, N ; test ecx, ecx ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; call EXT ; push ebx ; lea ecx, [esi + N] ; push ecx ; push ebp ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; add esp, N ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "struct It { void* p; It(void* q) : p(q) {} It(const It& o) : p(o.p) {} };\n"
def _cstr(pe, va):
    d = pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, 300)
    t = d.split(b"\0")[0].decode("latin1")
    return t.replace("\\", "\\\\").replace('"', '\\"')
def emit(va, A, N):
    from synth import pe, bounds, load_funcs
    import capstone
    starts, _ = load_funcs()
    code = bounds(va, starts)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    ins = list(md.disasm(code, va))
    pushes = [i for i in ins if i.mnemonic == "push" and i.op_str.startswith("0x")]
    line = int(pushes[0].op_str, 16)
    file_ = int(pushes[1].op_str, 16)
    name = int(pushes[2].op_str, 16)
    size = int(pushes[3].op_str, 16)
    src = ("struct K_%08x { unsigned a, b; };\n"
           "struct T_%08x { int cmp; char anchor[16]; unsigned sz;\n"
           "  It Impl(char* parent, const K_%08x* value, bool force);\n};\n"
           "int __cdecl cmp_%08x(unsigned __int64, unsigned __int64);\n"
           "void* __cdecl al_%08x(unsigned, const char*, int, int, const char*, int);\n"
           "struct Sub_%08x { void Init(const K_%08x*); };\n"
           "void __cdecl ins_%08x(char*, char*, char*, int);\n"
           "It T_%08x::Impl(char* parent, const K_%08x* value, bool force) {\n"
           "    int side = (!force && parent != anchor && cmp_%08x(*(unsigned __int64*)value, *(unsigned __int64*)(parent + 0x10)) >= 0) ? 1 : 0;\n"
           "    char* node = (char*)al_%08x(%d, \"%s\", 0, 0, \"%s\", %d);\n"
           "    char* nv = node + 0x10;\n    if (nv) ((Sub_%08x*)nv)->Init(value);\n"
           "    ins_%08x(node, parent, anchor, side);\n"
           "    ++sz; return It(node); }\n"
           % ((va,)*12 + (size, _cstr(pe, name), _cstr(pe, file_), line, va, va)))
    return src, "?Impl@T_%08x@@QAE?AUIt@@PADPBUK_%08x@@_N@Z" % (va, va)
