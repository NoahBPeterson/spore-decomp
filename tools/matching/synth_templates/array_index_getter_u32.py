# __thiscall getter returning this->arr[i] (u32 array at offset N[1]); N = [4, 4, off] roughly, offset is last
PATTERN = 'mov eax, dword ptr [esp + N] ; mov eax, dword ptr [ecx + eax*N + N] ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[2]
    return ("struct S_%08x { unsigned pad[%d]; unsigned a[1]; unsigned get(int i) const; };\n"
            "unsigned S_%08x::get(int i) const { return a[i]; }" % (va, off // 4, va)), "?get@S_%08x@@QBEIH@Z" % va
