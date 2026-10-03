# __stdcall const char* f(int x): default short string, x != 0 selects long string (cheat help selectors)
PATTERN = 'cmp dword ptr [esp + N], N ; mov eax, A ; je +N ; mov eax, A ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    src = ("extern char s_%08x[];\nextern char s_%08x[];\n"
           "const char* __stdcall FUN_%08x(int x) {\n"
           "    const char* r = s_%08x;\n    if (x) r = s_%08x;\n    return r;\n}\n"
           % (A[0], A[1], va, A[0], A[1]))
    return src, "?FUN_%08x@@YGPBDH@Z" % va
