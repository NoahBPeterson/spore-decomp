# member (wchar_t string at +off).assign(p, p + strlen(p)) via inline length loop, tail call to external range-assign
PATTERN = 'mov edx, dword ptr [esp + N] ; cmp word ptr [edx], N ; mov eax, edx ; je +N ; lea esp, [esp] ; add eax, N ; cmp word ptr [eax], N ; jne +N ; sub eax, edx ; sar eax, N ; lea eax, [edx + eax*N] ; push eax ; push edx ; add ecx, N ; call EXT ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct WStr { void assign(const wchar_t* b, const wchar_t* e); };
"""
def emit(va, A, N):
    off = N[-2]
    return ("struct C_%08x { char pad[%d]; WStr s; void f(const wchar_t* p); };\n"
            "void C_%08x::f(const wchar_t* p) { const wchar_t* e = p; while (*e) ++e; s.assign(p, p + (e - p)); }" % (va, off, va),
            "?f@C_%08x@@QAEXPB_W@Z" % va)
