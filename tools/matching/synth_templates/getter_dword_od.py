# Member getter returning a 4-byte wrapper struct by value (copied through a temp) from [this+off], /Od.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax + N] ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    d = dict(v=va, off=N[3])
    src = ("struct C_%(v)08x { char pad[%(off)d]; unsigned f; inline unsigned In() const { return f; } unsigned FUN_%(v)08x(); };\n"
           "unsigned C_%(v)08x::FUN_%(v)08x() { return In(); }\n") % d
    return src, "?FUN_%08x@C_%08x@@QAEIXZ" % (va, va)
