# Cast(type) matching two ids then tail-jmp to base: derived checks id1, inlined intermediate base checks id2
# (written as "!=" with early base call) so both je go to a shared "mov eax,ecx; ret 4".
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; je +N ; cmp eax, A ; je +N ; mov dword ptr [esp + N], eax ; jmp EXT ; mov eax, ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    s = "%08x" % va
    src = ("struct B0_%s { void* Cast(unsigned int type) const; };\n"
           "struct D1_%s : B0_%s { void* Cast(unsigned int type) const {\n"
           "    if (type != 0x%08xu) return B0_%s::Cast(type);\n    return (void*)this; } };\n"
           "struct C_%s : D1_%s { void* Cast(unsigned int type) const; };\n"
           "void* C_%s::Cast(unsigned int type) const {\n"
           "    if (type == 0x%08xu) return (void*)this;\n"
           "    return D1_%s::Cast(type);\n}") % (s, s, s, A[1], s, s, s, s, A[0], s)
    return src, "?Cast@C_%s@@QBEPAXI@Z" % s
