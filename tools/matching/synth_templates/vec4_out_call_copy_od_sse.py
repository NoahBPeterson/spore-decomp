# /Od /Ob1 /arch:SSE: fill a 4-float stack temp through a cdecl out-pointer call (Vector4_SetUnitX/
# SetUnitZ/SetZero/...), then copy the four floats to globals with movss:
#   push ebp; mov ebp,esp; sub esp,0x10; lea eax,[ebp-0x10]; push eax; call f; add esp,4;
#   movss xmm0,[ebp-k]; movss [g+..],xmm0 x4; mov esp,ebp; pop ebp; ret
# Almost certainly the dynamic initializer of a file-scope Vector4 (e.g. "Vector4 g = Vector4::UnitX();")
# in an unoptimized module. Shape-equivalent only: return-by-value/copy-ctor/operator= spellings
# either elide the temporary or copy through a reloaded pointer; the explicit out-pointer call
# plus per-field stores is what reproduces the bytes.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; lea eax, [ebp - N] ; push eax ; call EXT ; add esp, N ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; movss xmm0, dword ptr [ebp - N] ; movss dword ptr [A], xmm0 ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/arch:SSE", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Vec4Tmp { float x, y, z, w; };\nvoid Vector4_Out(Vec4Tmp*);\n"
_F = "xyzw"
def emit(va, A, N):
    if N[:3] != [0x10, 0x10, 4] or any(o not in (0x10, 0xc, 8, 4) for o in N[3:7]):
        return "// unexpected frame", "?unexpected_%08x@@YAXXZ" % va
    decl = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    body = "".join("g_%08x = t.%s; " % (d, _F[(0x10 - o) // 4]) for d, o in zip(A, N[3:7]))
    return (decl + "void FUN_%08x() { Vec4Tmp t; Vector4_Out(&t); %s}" % (va, body)), "?FUN_%08x@@YAXXZ" % va
