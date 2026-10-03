# Assignment of a default-constructed 9-float object (3x3 matrix zeroed by its ctor) to a
# file-scope global in an /O2 /arch:SSE module: the temporary is built on the stack with
# 9x movss of xmm0=0 and then struct-copied with rep movsd (ecx=9).
# Source shape: g = M3();  in a plain function (the global is extern, so no folding).
PATTERN = 'sub esp, N ; xorps xmm0, xmm0 ; push esi ; push edi ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = "struct Matrix3Z { float m[9]; Matrix3Z() { for (int i = 0; i < 9; i++) m[i] = 0.0f; } };\n"

def emit(va, A, N):
    return ("extern Matrix3Z g_%08x;\nvoid FUN_%08x() { g_%08x = Matrix3Z(); }" % (A[0], va, A[0]),
            "?FUN_%08x@@YAXXZ" % va)
