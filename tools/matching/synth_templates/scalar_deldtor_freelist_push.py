# Scalar deleting destructor (??_G) whose class-specific operator delete pushes the block onto a
# global intrusive freelist: *(void**)p = g_head; g_head = p. Dtor is external (call EXT).
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; test byte ptr [esp + N], N ; je +N ; mov eax, dword ptr [A] ; mov dword ptr [esi], eax ; mov dword ptr [A], esi ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    g = "g_%08x" % A[0]
    src = ("extern void* %s;\n"
           "struct %s {\n    virtual ~%s();\n"
           "    static void operator delete(void* p) {\n"
           "        *(void**)p = %s;\n        %s = p;\n    }\n};\n"
           "#pragma optimize(\"\", off)\n#pragma optimize(\"gty\", on)\n"
           "__declspec(noinline) %s::~%s() { ((void(*)())0)(); }") % (g, c, c, g, g, c, c)
    return src, "??_G%s@@UAEPAXI@Z" % c
