# __stdcall const char* f(int x): x==1 ? long_help : short_desc (cheat help text selectors)
PATTERN = 'mov eax, dword ptr [esp + N] ; sub eax, N ; mov eax, A ; jne +N ; mov eax, A ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    src = ("extern char s_%08x[];\nextern char s_%08x[];\n"
           "const char* __stdcall FUN_%08x(int x) {\n"
           "    switch (x) {\n    case 1: return s_%08x;\n    default: return s_%08x;\n    }\n}\n"
           % (A[0], A[1], va, A[1], A[0]))
    return src, "?FUN_%08x@@YGPBDH@Z" % va
