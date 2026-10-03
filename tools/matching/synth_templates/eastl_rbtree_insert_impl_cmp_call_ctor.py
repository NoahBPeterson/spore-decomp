# eastl rbtree DoInsertValueImpl, key compared through an out-of-line cdecl comparator, node created inline via
# EASTL_allocator_allocate(size,name,0,0,file,line) with an out-of-line thiscall value ctor on node+0x10.
# side = !force && parent != &anchor && !cmp(value, parent+0x10); RBTreeInsert; ++size; *out = node.
PATTERN = 'cmp byte ptr [esp + N], N ; push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; push edi ; mov esi, ecx ; jne +N ; lea eax, [esi + N] ; cmp ebp, eax ; je +N ; mov edx, dword ptr [esp + N] ; lea ecx, [ebp + N] ; push ecx ; push edx ; call EXT ; add esp, N ; test al, al ; jne +N ; mov ebx, N ; jmp +N ; xor ebx, ebx ; push N ; push A ; push N ; push N ; push A ; push N ; call EXT ; mov edi, eax ; lea ecx, [edi + N] ; add esp, N ; test ecx, ecx ; je +N ; mov eax, dword ptr [esp + N] ; push eax ; call EXT ; push ebx ; lea ecx, [esi + N] ; push ecx ; push ebp ; push edi ; call EXT ; mov eax, dword ptr [esp + N] ; inc dword ptr [esi + N] ; add esp, N ; mov dword ptr [eax], edi ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "inline void* operator new(unsigned, void* p) { return p; }\n"
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
    h = "%08x" % va
    src = ("struct It_@ { void* p; It_@(void* q) : p(q) {} It_@(const It_@& o) : p(o.p) {} };\n"
           "struct V_@ { V_@(const void* v); int x; };\n"
           "bool __cdecl cmp_@(const void*, const void*);\n"
           "void* __cdecl al_@(unsigned, const char*, int, int, const char*, int);\n"
           "void __cdecl ins_@(char*, char*, char*, int);\n"
           "struct T_@ { int cmp; char anchor[16]; unsigned sz;\n"
           "  It_@ Impl(char* parent, const void* value, bool force);\n};\n"
           "It_@ T_@::Impl(char* parent, const void* value, bool force) {\n"
           "    int side = (!force && parent != anchor && !cmp_@(value, parent + 0x10)) ? 1 : 0;\n"
           "    char* node = (char*)al_@(SIZE, \"NAME\", 0, 0, \"FILE\", LINE);\n"
           "    V_@* nv = (V_@*)(node + 0x10);\n"
           "    if (nv) new (nv) V_@(value);\n"
           "    ins_@(node, parent, anchor, side);\n"
           "    ++sz; return It_@(node); }\n").replace("@", h)
    src = src.replace("SIZE", str(size)).replace("NAME", _cstr(pe, name)).replace("FILE", _cstr(pe, file_)).replace("LINE", str(line))
    return src, "?Impl@T_%s@@QAE?AUIt_%s@@PADPBX_N@Z" % (h, h)
