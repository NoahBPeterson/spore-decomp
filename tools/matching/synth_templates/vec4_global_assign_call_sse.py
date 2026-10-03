# Dynamic-initializer-like: tmp = f() (sret Vec4, cdecl); global.init() (thiscall, no args); global.v = tmp
# (user operator= copying 4 floats, /arch:SSE movss). Callees are relocations, so shared names are fine.
PATTERN = 'lea eax, [esp - N] ; sub esp, N ; push eax ; call EXT ; add esp, N ; mov ecx, A ; call EXT ; movss xmm0, dword ptr [esp] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [A], xmm0 ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = r'''struct V4 { float x,y,z,w; V4& operator=(const V4&o){x=o.x;y=o.y;z=o.z;w=o.w;return *this;} };
struct H4 { V4 v; void init(); };
extern V4 __cdecl mk_v4();
'''
def emit(va, A, N):
    g = "g_%08x" % A[0]
    src = ("extern H4 %s;\nvoid FUN_%08x() { V4 t = mk_v4(); %s.init(); %s.v = t; }" % (g, va, g, g))
    return src, "?FUN_%08x@@YAXXZ" % va
