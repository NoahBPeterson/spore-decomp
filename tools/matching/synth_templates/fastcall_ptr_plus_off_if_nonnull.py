# if (p) return p + N; return 0;  (MI upcast to secondary base) as a __fastcall free function on ecx.
PATTERN = 'test ecx, ecx ; je +N ; lea eax, [ecx + N] ; ret  ; xor eax, eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off = N[-1]
    return ("char* __fastcall FUN_%08x(char* p) { return p ? p + %d : 0; }" % (va, off),
            "?FUN_%08x@@YIPADPAD@Z" % va)
