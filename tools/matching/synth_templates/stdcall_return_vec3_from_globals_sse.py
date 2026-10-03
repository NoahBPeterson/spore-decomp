# __stdcall Vector3 [name]([int unused]) returning a struct by value (hidden sret pointer at [esp+4],
# ret 4 / ret 8) built from three file-scope floats, /O2 /arch:SSE. Returning by value (not an
# out-pointer) makes cl load the sret pointer first, as the original does.
PATTERN = 'mov eax, dword ptr [esp + N] ; movss xmm0, dword ptr [A] ; movss dword ptr [eax], xmm0 ; movss xmm0, dword ptr [A] ; movss dword ptr [eax + N], xmm0 ; movss xmm0, dword ptr [A] ; movss dword ptr [eax + N], xmm0 ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = "struct V3 { float x, y, z; };\n"

def emit(va, A, N):
    s = "".join("extern float g_%08x;\n" % a for a in sorted(set(A)))
    extra = N[-1] == 8
    s += "V3 __stdcall FUN_%08x(%s) { V3 v; v.x = g_%08x; v.y = g_%08x; v.z = g_%08x; return v; }" % (va, "int" if extra else "", A[0], A[1], A[2])
    return s, "?FUN_%08x@@YG?AUV3@@%s" % (va, "H@Z" if extra else "XZ")
