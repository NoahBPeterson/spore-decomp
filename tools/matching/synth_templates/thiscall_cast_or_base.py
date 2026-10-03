# Object::Cast(uint32_t typeID) that accepts one type-id hash and otherwise defers to the base class:
#   if (type != ID) return Base::Cast(type); return this;
# /O2 out-of-line const __thiscall member; the base call becomes a tail jmp (arg re-stored to [esp+4]).
# Writing it as `if (type == ID) return this; return Base::Cast(type);` flips the branch layout.
PATTERN = 'mov eax, dword ptr [esp + N] ; cmp eax, A ; je +N ; mov dword ptr [esp + N], eax ; jmp EXT ; mov eax, ecx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    # A small type id (< 0x400000) is classified as an immediate by synth.py and lands in N.
    if A and N == [4, 4, 4]:
        tid = A[0]
    elif not A and len(N) == 4 and N[0] == N[2] == N[3] == 4:
        tid = N[1]
    else:
        return "// unsupported variant", "?unsupported_%08x@@YAXXZ" % va
    c = "C_%08x" % va
    src = ("struct B_%08x { void* Cast(unsigned int type) const; };\n"
           "struct %s : B_%08x { void* Cast(unsigned int type) const; };\n"
           "void* %s::Cast(unsigned int type) const {\n"
           "    if (type != 0x%08xu) return B_%08x::Cast(type);\n"
           "    return (void*)this;\n}") % (va, c, va, c, tid, va)
    return src, "?Cast@%s@@QBEPAXI@Z" % c
