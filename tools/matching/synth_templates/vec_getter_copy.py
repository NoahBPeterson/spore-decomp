# bool f(V3* out, O* o): temp 16-byte struct returned by member call on o->p, copy y,z,x to out.
PATTERN = 'mov ecx, dword ptr [esp + N] ; mov ecx, dword ptr [ecx + N] ; sub esp, N ; lea eax, [esp] ; push eax ; call EXT ; mov eax, dword ptr [esp + N] ; mov edx, dword ptr [esp + N] ; mov ecx, dword ptr [esp + N] ; mov dword ptr [eax + N], edx ; mov edx, dword ptr [esp] ; mov dword ptr [eax + N], ecx ; mov dword ptr [eax], edx ; mov al, N ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct V3_ { int x, y, z; };
struct W4_ { int x, y, z, w; };
struct P_ { W4_ get(); };
struct O_ { int a; P_* p; };
"""
def emit(va, A, N):
    return ("struct P%08x_ { W4_ get(); };\nstruct O%08x_ { int a; P%08x_* p; };\n"
            "bool FUN_%08x(V3_* out, O%08x_* o) { W4_ t = o->p->get(); out->y = t.y; out->z = t.z; out->x = t.x; return true; }"
            % (va, va, va, va, va)), "?FUN_%08x@@YA_NPAUV3_@@PAUO%08x_@@@Z" % (va, va)
