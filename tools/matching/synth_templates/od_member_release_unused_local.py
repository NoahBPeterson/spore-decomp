# /Od thunk: Release() on an embedded member at offset N with an unused 12-byte local:
#   push ebp; mov ebp,esp; sub esp,10h; mov [ebp-10h],ecx; mov ecx,[ebp-10h]; add ecx,off; call Release
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; call EXT ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[-1]
    src = ("struct M_%08x { void Release(); };\n"
           "struct O_%08x { char pad[%d]; M_%08x m; void F(); };\n"
           "void O_%08x::F() { unsigned unused[3]; m.Release(); }\n") % (va, va, off, va, va)
    return src, "?F@O_%08x@@QAEXXZ" % va
