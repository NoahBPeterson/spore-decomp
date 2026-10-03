# Dynamic initializer of a file-scope 3x3 float matrix set to identity, in an /O2 /arch:SSE module:
# builds the identity in a 36-byte stack temp (xmm1=1.0f from __real@3f800000, xmm0=0) and copies it
# into the global with rep movsd (ecx=9). Source shape: Matrix3 g = Matrix3().SetIdentity();
# where SetIdentity is an inline member returning *this by reference -- going through the reference
# blocks /O2's static-data folding (a value-returning Identity() or 9-float ctor folds to .data).
PATTERN = 'sub esp, N ; xorps xmm0, xmm0 ; movss xmm1, dword ptr [A] ; push esi ; push edi ; mov ecx, N ; lea esi, [esp + N] ; mov edi, A ; movss dword ptr [esp + N], xmm1 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm1 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm0 ; movss dword ptr [esp + N], xmm1 ; rep movsd dword ptr es:[edi], dword ptr [esi] ; pop edi ; pop esi ; add esp, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = """struct Matrix3 {
    float m[3][3];
    Matrix3() {}
    Matrix3& SetIdentity() {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
        return *this;
    }
};
"""
def emit(va, A, N):
    return "Matrix3 g_%08x = Matrix3().SetIdentity();" % A[1], "??__Eg_%08x@@YAXXZ" % A[1]
