# cdecl getter of a dword at [arg+off]: mov eax,[esp+4]; mov eax,[eax+off]; ret
PATTERN = 'mov eax, dword ptr [esp + N] ; mov eax, dword ptr [eax + N] ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[-1]
    return ("void* FUN_%08x(char* p) { return *(void**)(p + 0x%x); }" % (va, off),
            "?FUN_%08x@@YAPAXPAD@Z" % va)
