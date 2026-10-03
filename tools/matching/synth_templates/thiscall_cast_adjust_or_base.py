# Object::Cast(type): if (type != ID) return Base::Cast(type); return this ? (char*)this+off : 0;
# /O2 out-of-line non-const __thiscall member; base call becomes tail jmp; ret 4.
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; je +N ; mov dword ptr [esp + N], eax ; jmp EXT ; test ecx, ecx ; je +N ; lea eax, [ecx + N] ; ret N ; xor eax, eax ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    tid = A[0] if A else N[1]
    off = N[-3]
    c = "C_%08x" % va
    src = ("struct B_%08x { void* Cast(unsigned int type); };\n"
           "struct %s : B_%08x { void* Cast(unsigned int type); };\n"
           "void* %s::Cast(unsigned int type) {\n"
           "    if (type != 0x%08xu) return B_%08x::Cast(type);\n"
           "    return this ? (void*)((char*)this + %d) : 0;\n}") % (va, c, va, c, tid, va, off)
    return src, "?Cast@%s@@QAEPAXI@Z" % c
