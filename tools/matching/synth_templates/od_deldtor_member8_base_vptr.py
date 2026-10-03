# /Od scalar deleting dtor of D : B with implicit ~D (member at +8 with out-of-line ~Mem) and an inline
# base dtor that only resets the vptr (locals of the inlined base dtor pad the frame).
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; call EXT ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax], A ; mov ecx, dword ptr [ebp + N] ; and ecx, N ; je +N ; mov edx, dword ptr [ebp - N] ; push edx ; call EXT ; add esp, N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\nstruct Mem { ~Mem(); };\n"
def emit(va, A, N):
    c = "C_%08x" % va
    if N[0] >= 0x4c:
        padf = "char pad[64]; " + ("char pad2[%d]; " % (N[0] - 0x4c) if N[0] > 0x4c else "")
    else:
        padf = "char pad[%d]; " % max(N[0] - 8, 4)
    src = ("struct B_%s { B_%s(); virtual ~B_%s() { %s} int a; };\n"
           "struct %s : B_%s { Mem m; %s(); static void operator delete(void* p) { EASTL_allocator_deallocate(p); } };\n"
           "%s::%s() {}\n") % (c, c, c, padf, c, c, c, c, c)
    return src, "??_G%s@@UAEPAXI@Z" % c
