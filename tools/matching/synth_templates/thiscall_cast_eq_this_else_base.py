# Object::Cast(uint32_t typeID): if (type == ID) return this; return Base::Cast(type);
# /O2 out-of-line const __thiscall member; base call becomes a tail jmp.
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; jne +N ; mov eax, ecx ; ret N ; mov dword ptr [esp + N], eax ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tid = A[0] if A else N[1]
    c = "C_%08x" % va
    src = ("struct B_%08x { void* Cast(unsigned int type) const; };\n"
           "struct %s : B_%08x { void* Cast(unsigned int type) const; };\n"
           "void* %s::Cast(unsigned int type) const {\n"
           "    if (type == 0x%08xu) return (void*)this;\n"
           "    return B_%08x::Cast(type);\n}") % (va, c, va, c, tid, va)
    return src, "?Cast@%s@@QBEPAXI@Z" % c
