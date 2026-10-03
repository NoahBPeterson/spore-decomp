# this->A(); this->B(); where both are thiscall members: push esi; mov esi,ecx; call; mov ecx,esi; pop esi; jmp
PATTERN = 'push esi ; mov esi, ecx ; call EXT ; mov ecx, esi ; pop esi ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("struct C_%08x { void a(); void b(); void f(); };\n"
            "void C_%08x::f() { a(); b(); }" % (va, va)), "?f@C_%08x@@QAEXXZ" % va
