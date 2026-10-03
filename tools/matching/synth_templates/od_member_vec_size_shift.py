# Unoptimized member returning (end - begin) >> shift of an embedded vector at this+off.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; add eax, N ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ebp - N] ; mov eax, dword ptr [ecx + N] ; sub eax, dword ptr [edx] ; sar eax, N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    sh = N[-1]
    off = N[3]
    esz = 1 << sh
    return ("struct E_%08x { char b[%d]; };\nstruct V_%08x { E_%08x* b; E_%08x* e; int size() const { return (int)(e - b); } };\n"
            "struct C_%08x { char pad[%d]; V_%08x v; int FUN_%08x(); };\n"
            "int C_%08x::FUN_%08x() { return v.size(); }" % (va, esz, va, va, va, va, off, va, va, va, va),
            "?FUN_%08x@C_%08x@@QAEHXZ" % (va, va))
