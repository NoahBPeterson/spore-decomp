# void S::f(P* p) { p->vA("str", imm, this); p->vB(); }   (this passed through as 3rd arg, ret 4)
# PARTIAL: /O1 gives all bytes except the 2nd vtable load register: original uses edx
# ("mov edx,[esi]; call [edx+N]") while cl picks eax. 2 bytes differ per instance. /O2 is worse (preloads edx).
PATTERN = 'push esi ; mov esi, dword ptr [esp + N] ; mov eax, dword ptr [esi] ; push ecx ; push N ; push A ; mov ecx, esi ; call dword ptr [eax + N] ; mov edx, dword ptr [esi] ; mov ecx, esi ; call dword ptr [edx + N] ; pop esi ; ret N'
FLAGS = ["/O1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def _slots(va):
    import sys, os
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
    from card import load_funcs, bounds
    st, _ = load_funcs()
    code = bounds(va, st)
    i = code.index(b"\xff\x50")
    j = code.index(b"\xff\x52")
    return code[i + 2] // 4, code[j + 2] // 4
def emit(va, A, N):
    imm = N[1]
    k1, k2 = _slots(va)
    top = max(k1, k2)
    virts = " ".join(("virtual void v%d(const char*, int, void*);" % i) if i == k1 else
                     ("virtual void v%d();" % i) for i in range(top + 1))
    src = ("struct P_%08x { %s };\n"
           "struct S_%08x { void FUN_%08x(P_%08x* p); };\n"
           "void S_%08x::FUN_%08x(P_%08x* p) { p->v%d((const char*)0x%x, %d, this); p->v%d(); }"
           % (va, virts, va, va, va, va, va, va, k1, A[0], imm, k2))
    return src, "?FUN_%08x@S_%08x@@QAEXPAUP_%08x@@@Z" % (va, va, va)
