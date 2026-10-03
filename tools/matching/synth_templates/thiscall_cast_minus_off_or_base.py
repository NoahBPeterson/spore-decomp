# Object::Cast(type): if (type != ID) return Base::Cast(type); return (char*)this - off;
# /O2 out-of-line non-const __thiscall member; base call becomes a tail jmp; no null check.
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; je +N ; mov dword ptr [esp + N], eax ; jmp EXT ; lea eax, [ecx - N] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tid = A[0] if A else N[1]
    off = N[-2]
    c = "C_%08x" % va
    src = ("struct B_%08x { void* Cast(unsigned int type); };\n"
           "struct %s : B_%08x { void* Cast(unsigned int type); };\n"
           "void* %s::Cast(unsigned int type) {\n"
           "    if (type != 0x%08xu) return B_%08x::Cast(type);\n"
           "    return (void*)((char*)this - %d);\n}") % (va, c, va, c, tid, va, off)
    return src, "?Cast@%s@@QAEPAXI@Z" % c
