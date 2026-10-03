# /Od /Ob1 module: fill an N-dword stack temp via an external cdecl out-param function
# (e.g. Matrix3_SetIdentity / Matrix4_SetZero), then struct-assign it to a global (rep movsd).
# Source shape: void f() { T t; Init(&t); g = t; }  with T a POD of N dwords.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; push esi ; push edi ; lea eax, [ebp - N] ; push eax ; call EXT ; add esp, N ; mov ecx, N ; lea esi, [ebp - N] ; mov edi, A ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "template<int K> struct PodN { int d[K]; };\ntemplate<int K> void ext_fill(PodN<K>*);\n"
def emit(va, A, N):
    k = N[3]
    if N[0] != 4 * k or N[2] != 4:
        return "// unexpected sizes", "?unexpected_%08x@@YAXXZ" % va
    g = "g_%08x" % A[0]
    src = ("extern PodN<%d> %s;\nvoid FUN_%08x() { PodN<%d> t; ext_fill(&t); %s = t; }"
           % (k, g, va, k, g))
    return src, "?FUN_%08x@@YAXXZ" % va
