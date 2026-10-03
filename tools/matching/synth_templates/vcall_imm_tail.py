# Thunk: this->vfunc[off/4](imm) tail-called through a vtable slot (mov eax,[ecx]; mov edx,[eax+off]; push imm; call edx; ret)
PATTERN = 'mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; push N ; call edx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, imm = N[0], N[1]
    slot = off // 4
    pads = "".join("virtual void p%d(int);" % i for i in range(slot))
    imm = imm if imm < 0x80000000 else imm - (1 << 32)
    src = ("struct C%08x { %s virtual void f(int); void g(); };\n"
           "void C%08x::g() { f(%d); }\n") % (va, pads, va, imm)
    return src, "?g@C%08x@@QAEXXZ" % va
