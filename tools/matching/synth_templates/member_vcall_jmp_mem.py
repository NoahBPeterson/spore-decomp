# thunk: this->field->vfunc() tail call as jmp [eax+slot]
PATTERN = 'mov ecx, dword ptr [ecx + N] ; mov eax, dword ptr [ecx] ; jmp dword ptr [eax + N]'
FLAGS = ["/O1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
import os
_pe = None
def _slot(va):
    global _pe
    if _pe is None:
        import pefile
        root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
        _pe = pefile.PE(os.path.join(root, "work/SporeApp.analysis.bin"), fast_load=True)
    d = _pe.get_data(va - _pe.OPTIONAL_HEADER.ImageBase, 8)
    assert d[5] == 0xff and d[6] == 0x60
    return d[7]
def emit(va, A, N):
    off, v = N[0], _slot(va)
    k = v // 4
    virts = " ".join("virtual void v%d();" % i for i in range(k + 1))
    pad = "char pad[%d]; " % off if off else ""
    src = ("struct I_%08x { %s };\nstruct S_%08x { %sI_%08x* p; void FUN_%08x(); };\n"
           "void S_%08x::FUN_%08x() { p->v%d(); }" % (va, virts, va, pad, va, va, va, va, k))
    return src, "?FUN_%08x@S_%08x@@QAEXXZ" % (va, va)
