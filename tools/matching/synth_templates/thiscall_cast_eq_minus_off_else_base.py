# Object::Cast(type): if (type == ID) return (char*)this - off; return Base::Cast(type);
# /O2 out-of-line non-const __thiscall member; jne to the tail-jmp, match path laid out first.
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; jne +N ; lea eax, [ecx - N] ; ret N ; mov dword ptr [esp + N], eax ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tid = A[0] if A else N[1]
    off = N[1] if A else N[2]
    c = "C_%08x" % va
    src = ("struct B_%08x { void* Cast(unsigned int type); };\n"
           "struct %s : B_%08x { void* Cast(unsigned int type); };\n"
           "void* %s::Cast(unsigned int type) {\n"
           "    if (type == 0x%08xu) return (void*)((char*)this - %d);\n"
           "    return B_%08x::Cast(type);\n}") % (va, c, va, c, tid, off, va)
    return src, "?Cast@%s@@QAEPAXI@Z" % c
