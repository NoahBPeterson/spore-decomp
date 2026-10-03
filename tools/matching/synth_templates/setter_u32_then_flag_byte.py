# __thiscall member: store u32 arg at [this+a], then set byte flag at [this+b] to a constant; ret 4.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov dword ptr [ecx + N], eax ; mov byte ptr [ecx + N], N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    soff, off, boff, val, ret = N
    c = "C_%08x" % va
    src = ("#pragma pack(push, 1)\nstruct %s { char p0[0x%x]; unsigned v; char p1[0x%x]; bool f; void Set(unsigned a); };\n#pragma pack(pop)\n"
           % (c, off, 0))
    # use raw pointer arithmetic to avoid layout ordering constraints
    src = ("struct %s { void Set(unsigned a); };\n"
           "void %s::Set(unsigned a) { *(unsigned*)((char*)this + 0x%x) = a; *((char*)this + 0x%x) = %d; }"
           % (c, c, off, boff, val))
    return src, "?Set@%s@@QAEXI@Z" % c
