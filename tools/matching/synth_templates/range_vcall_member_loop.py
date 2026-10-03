# for (; a < b; ++a) { I* q = a->p; if (q) q->vN(); } as __stdcall(first,last); stride/offset/slot vary.
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; cmp esi, edi ; jae +N ; mov edi, edi ; mov ecx, dword ptr [esi + N] ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; add esi, N ; cmp esi, edi ; jb +N ; pop edi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    # N order: esp+8, esp+0x10, member off, vtable off, stride, ret 8 (variable positions; pick by role)
    off = [n for n in N][2]
    vt = N[3] // 4
    stride = N[4]
    s = "S_%08x" % va
    virt = "".join("virtual void v%d(); " % i for i in range(vt + 1))
    pad = "char pad[%d]; " % off if off else ""
    pad2 = "char pad2[%d]; " % (stride - off - 4) if stride - off - 4 > 0 else ""
    src = ("struct I_%08x { %s};\nstruct %s { %sI_%08x* p; %s};\n"
           "void __stdcall FUN_%08x(%s* a, %s* b) {\n"
           "  for (; a < b; ++a) { I_%08x* q = a->p; if (q) q->v%d(); }\n}") % (va, virt, s, pad, va, pad2, va, s, s, va, vt)
    return src, "?FUN_%08x@@YGXPAU%s@@0@Z" % (va, s)
