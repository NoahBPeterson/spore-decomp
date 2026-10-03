# 8-byte key copy variant. eastl rbtree DoInsertValueImpl with DoCreateNode inlined: EASTL_allocator_allocate(size,name,0,0,file,line);
# node->key = value.key; out-of-line sub-object ctor on (&value+4) into node+0x14; RBTreeInsert; ++size; *out=node.
PATTERN = 'cmp byte ptr [esp + N], N ; push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, ecx ; jne +N ; lea eax, [esi + N] ; cmp ebp, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; cmp edx, dword ptr [ebp + N] ; jb +N ; mov ebx, N ; jmp +N ; xor ebx, ebx ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov edi, eax ; lea eax, [edi + N] ; add esp, N ; test eax, eax ; je +N ; mov ecx, dword ptr [esp + N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax], edx ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [eax + N], ecx ; push ebx ; lea edx, [esi + N] ; push edx ; push ebp ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; add esp, N ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
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
    src = ("struct T_%08x { int cmp; char anchor[16]; unsigned sz;\n"
           "  It Impl(char* parent, const unsigned* value, bool force);\n};\n"
           "void* __cdecl al_%08x(unsigned, const char*, int, int, const char*, int);\n"
           ""
           "void __cdecl ins_%08x(char*, char*, char*, int);\n"
           "It T_%08x::Impl(char* parent, const unsigned* value, bool force) {\n"
           "    int side = (!force && parent != anchor && *value >= *(unsigned*)(parent + 0x10)) ? 1 : 0;\n"
           "    char* node = (char*)al_%08x(%d, \"%s\", 0, 0, \"%s\", %d);\n"
           "    unsigned* nv = (unsigned*)(node + 0x10);\n    if (nv) { nv[0] = value[0]; nv[1] = value[1]; }\n"
           "    ins_%08x(node, parent, anchor, side);\n"
           "    ++sz; return It(node); }\n"
           % (va, va, va, va, va, size, _cstr(pe, name), _cstr(pe, file_), line, va))
    return src, "?Impl@T_%08x@@QAE?AUIt@@PADPBI_N@Z" % va
