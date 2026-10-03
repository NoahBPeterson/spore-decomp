# this->ptr(+N0)->field(+N1) getter
PATTERN = 'mov eax, dword ptr [ecx + N] ; mov eax, dword ptr [eax + N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    s = "struct S_%08x { int get(); };\nint S_%08x::get() { return *(int*)(*(char**)((char*)this + 0x%x) + 0x%x); }" % (va, va, N[0], N[1])
    return s, "?get@S_%08x@@QAEHXZ" % va
