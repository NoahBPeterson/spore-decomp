# /Od scalar deleting destructor: ~C(); if (flags & 1) EASTL_allocator_deallocate(this); return this;
# Frame size varies (unused locals); pad with an unused char array.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov eax, dword ptr [ebp + N] ; and eax, N ; je +N ; mov ecx, dword ptr [ebp - N] ; push ecx ; call EXT ; add esp, N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\n"
def emit(va, A, N):
    t = "%08x" % va
    pad = max(N[0] - 8, 4)
    if N[0] == 0x50:
        loc = "  char pad[56];\n  char pad2[16];\n"
    elif N[0] >= 0x4c:  # arrays >= 64 bytes are 8-aligned: frame = 12 + 64
        loc = "  char pad[64];\n" + ("  char pad2[%d];\n" % (N[0] - 0x4c) if N[0] > 0x4c else "")
    else:
        loc = "  char pad[%d];\n" % pad
    src = ("struct C_%s { void D(); void* F(unsigned f); };\n"
           "void* C_%s::F(unsigned f) {\n%s  D();\n  if (f & 1) EASTL_allocator_deallocate(this);\n  return this;\n}") % (t, t, loc)
    return src, "?F@C_%s@@QAEPAXI@Z" % t
