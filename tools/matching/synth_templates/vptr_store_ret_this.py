# Base ctor: this->vptr = vtbl; return this  (mov eax,ecx; mov [eax],A; ret)
PATTERN = 'mov eax, ecx ; mov dword ptr [eax], A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    return ("""extern char vt_%08x[];
struct Obj%08x { void* vp; Obj%08x* init(); };
Obj%08x* Obj%08x::init() { vp = vt_%08x; return this; }""" % (va, va, va, va, va, va)), "?init@Obj%08x@@QAEPAU1@XZ" % va
