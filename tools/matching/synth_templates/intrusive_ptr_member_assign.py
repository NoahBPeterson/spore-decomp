# __thiscall setter assigning a raw pointer to an intrusive_ptr member (EA "IntrusivePtr = p"):
#   T* old = field; if (p != old) { if (p) p->AddRef(); field = p; if (old) old->Release(); }
# /O2 out-of-line member; AddRef is vtable slot 0, Release slot N[3]/4 (normally 1).
PATTERN = "push ebx ; push esi ; mov esi, dword ptr [esp + N] ; mov ebx, ecx ; push edi ; mov edi, dword ptr [ebx + N] ; cmp esi, edi ; je +N ; test esi, esi ; je +N ; mov eax, dword ptr [esi] ; mov edx, dword ptr [eax] ; mov ecx, esi ; call edx ; mov dword ptr [ebx + N], esi ; test edi, edi ; je +N ; mov eax, dword ptr [edi] ; mov edx, dword ptr [eax + N] ; mov ecx, edi ; call edx ; pop edi ; pop esi ; pop ebx ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct RefObj {\n" +
           "".join("    virtual int v%d() = 0;\n" % i for i in range(16)) +
           "};\n")

def emit(va, A, N):
    _, off, _, rel, ret = N
    c = "C_%08x" % va
    pad = "char pad[0x%x]; " % off if off else ""
    src = ("#pragma pack(push, 1)\nstruct %s { %sRefObj* field; void Set(RefObj* q); };\n#pragma pack(pop)\n"
           "void %s::Set(RefObj* q) {\n"
           "    RefObj* old = field;\n"
           "    if (q != old) { if (q) q->v0(); field = q; if (old) old->v%d(); }\n"
           "}" % (c, pad, c, rel // 4))
    return src, "?Set@%s@@QAEXPAURefObj@@@Z" % c
