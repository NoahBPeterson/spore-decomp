# PARTIAL (not byte-exact, original uses dec/js + call [edx+N] + rotated loop that /O2 will not emit). Reverse loop calling virtual slot on each non-null element of a pointer array member, then reverse pass erasing null entries (shift down).
PATTERN = 'push ebx ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esi + N] ; dec edi ; js +N ; mov ebx, dword ptr [esp + N] ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [eax + edi*N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; push ebx ; call dword ptr [edx + N] ; dec edi ; jns +N ; mov edx, dword ptr [esi + N] ; dec edx ; js +N ; mov eax, dword ptr [esi + N] ; cmp dword ptr [eax + edx*N], N ; jne +N ; mov ebx, dword ptr [esi + N] ; dec ebx ; mov ecx, ebx ; cmp edx, ecx ; mov dword ptr [esi + N], ebx ; mov eax, edx ; jge +N ; jmp +N ; lea esp, [esp] ; lea ecx, [ecx] ; mov ecx, dword ptr [esi + N] ; mov edi, dword ptr [ecx + eax*N + N] ; lea ecx, [ecx + eax*N] ; mov dword ptr [ecx], edi ; mov ecx, dword ptr [esi + N] ; inc eax ; cmp eax, ecx ; jl +N ; dec edx ; jns +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def _slot(va):
    import sys, os
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
    from card import load_funcs, bounds
    st, _ = load_funcs()
    code = bounds(va, st)
    k = code.index(b"\xff\x52")
    return code[k + 2] // 4
def emit(va, A, N):
    cnt, arr = N[1], N[3]
    slot = _slot(va)
    v = "".join("virtual void v%d(int); " % i for i in range(slot + 1))
    src = ("struct I_%08x { %s};\n"
           "struct O_%08x { char pad[%d]; I_%08x** d; int n; };\n"
           "void FUN_%08x(O_%08x* o, int a) {\n"
           "  int i = o->n; while (i > 0) { --i; I_%08x* p = o->d[i]; if (p) p->v%d(a); }\n"
           "  for (int k = o->n - 1; k >= 0; --k) {\n"
           "    if (o->d[k] == 0) { int j = k; int m = o->n - 1; o->n = m; if (j < m) do { o->d[j] = o->d[j + 1]; ++j; } while (j < o->n); }\n"
           "  }\n}"
           % (va, v, va, arr, va, va, va, va, slot))
    return src, "?FUN_%08x@@YAXPAUO_%08x@@H@Z" % (va, va)
