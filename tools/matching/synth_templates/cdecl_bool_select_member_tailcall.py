# cdecl wrapper (Obj* p, int x, bool b): if (!b) p->A(); else p->B();
# -> cmp byte [esp+0xc],0; mov ecx,[esp+4]; jne L; jmp A; L: jmp B
PATTERN = 'cmp byte ptr [esp + N], N ; mov ecx, dword ptr [esp + N] ; jne +N ; jmp EXT ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Obj { void A(); void B(); };\n"
def emit(va, A, N):
    return ("void FUN_%08x(Obj* p, int x, bool b) { if (!b) p->A(); else p->B(); }" % va,
            "?FUN_%08x@@YAXPAUObj@@H_N@Z" % va)
