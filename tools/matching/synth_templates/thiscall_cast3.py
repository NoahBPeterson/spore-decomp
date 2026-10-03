# Object::Cast(uint32_t typeID) with three accepted type-id hashes, returning this or nullptr:
#   if (type == A) return this; else if (type == B) return this; else if (type == C) return this;
#   else return 0;
# /O2 out-of-line const __thiscall member; MSVC turns the last compare into setne/dec/and.
PATTERN = "mov eax, ecx ; mov ecx, dword ptr [esp + N] ; cmp ecx, A ; je +N ; cmp ecx, A ; je +N ; xor edx, edx ; cmp ecx, A ; setne dl ; dec edx ; and eax, edx ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct %s { void* Cast(unsigned int type) const; };\n"
           "void* %s::Cast(unsigned int type) const {\n"
           "    if (type == 0x%08xu) return (void*)this;\n"
           "    else if (type == 0x%08xu) return (void*)this;\n"
           "    else if (type == 0x%08xu) return (void*)this;\n"
           "    else return 0;\n}") % (c, c, A[0], A[1], A[2])
    return src, "?Cast@%s@@QBEPAXI@Z" % c
