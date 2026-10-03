# Ctor-like thiscall: this->f = imm; this->vptr = vtbl; return this (mov eax,ecx; mov [eax+N],N; mov [eax],A; ret)
PATTERN = 'mov eax, ecx ; mov dword ptr [eax + N], N ; mov dword ptr [eax], A ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    off, imm = N[0], N[1]
    pad = off // 4 - 1
    return ("""extern char vt_%08x[];
struct Obj%08x { void* vp; %s unsigned f; Obj%08x* init(); };
Obj%08x* Obj%08x::init() { f = %d; vp = vt_%08x; return this; }""" % (va, va, ('unsigned pad[%d];' % pad) if pad else '', va, va, va, imm, va)), "?init@Obj%08x@@QAEPAU1@XZ" % va
