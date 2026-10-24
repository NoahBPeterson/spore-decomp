// Slice s004a89e0 — Spore editor matrix/vector helpers (/Od /Ob1 /arch:SSE2 /fp:fast).
#include "types.h"

struct V3 {
    float x, y, z;
    float& operator[](int i) { return ((float*)this)[i]; }
    void VecCopyCtor(const V3& o);                       // 0x04098a0
};

// ================= cSPEditorBlock =================
struct cSPEditorBlock;
struct BlockVec {
    cSPEditorBlock** mpBegin;
    cSPEditorBlock** mpEnd;
    void** mpCapacity;
};
struct cSPEditorBlock {
    char pad0[0x340];
    BlockVec mChildren;              // +0x340
    char pad1[0xdc8 - 0x34c];
    uint32_t mFlags[4];              // +0xdc8

    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
};

// @ 0x004a96d0
bool AllChildrenNoFlag(cSPEditorBlock* param_1)
{
    if (param_1 == 0) return false;
    if (!param_1->IsFlagSet(0xb)) return false;
    BlockVec& v = param_1->mChildren;
    int i = 0;
    int n = v.mpEnd - v.mpBegin;
    for (; i < n; ++i) {
        cSPEditorBlock* elem = v.mpBegin[i];
        if (elem->IsFlagSet(0xb) || elem->IsFlagSet(0xc)) return false;
    }
    return true;
}

// @ 0x004a9840
cSPEditorBlock* GetFirstFootBlock(cSPEditorBlock* param_1)
{
    if (param_1 == 0) return 0;
    if (param_1->IsFlagSet(0x2d)) return param_1;
    BlockVec& v = param_1->mChildren;
    int i = 0;
    int n = v.mpEnd - v.mpBegin;
    for (; i < n; ++i) {
        cSPEditorBlock* elem = v.mpBegin[i];
        cSPEditorBlock* r = GetFirstFootBlock(elem);
        if (r != 0) return r;
    }
    return 0;
}

// @ 0x004a8f40
V3* NegateX(V3* param_1, V3* param_2)
{
    V3 v;
    v.x = param_2->x;
    v.y = param_2->y;
    v.z = param_2->z;
    v[0] *= -1.0f;
    param_1->x = v.x;
    param_1->y = v.y;
    param_1->z = v.z;
    return param_1;
}

// @ 0x004a8fc0
void TransposeInto(float* param_1, float* param_2)
{
    float v1 = param_1[1];
    float v2 = param_1[2];
    float v3 = param_1[3];
    float v4 = param_1[4];
    float v5 = param_1[5];
    float v6 = param_1[6];
    float v7 = param_1[7];
    float v8 = param_1[8];
    param_2[0] = param_1[0];
    param_2[1] = v1;
    param_2[2] = v2;
    param_2[3] = 0.0f;
    param_2[4] = v3;
    param_2[5] = v4;
    param_2[6] = v5;
    param_2[7] = 0.0f;
    param_2[8] = v6;
    param_2[9] = v7;
    param_2[10] = v8;
    param_2[11] = 0.0f;
}

// @ 0x004a8d70
struct M3 {
    V3 m[3];
    M3(float a, float b, float c, float d, float e, float f,
       float g, float h, float i);
    void AssignMat(const M3& o);                         // 0x0449cc0
};
M3::M3(float a, float b, float c, float d, float e, float f,
       float g, float h, float i)
{
    m[0].x = a; m[0].y = b; m[0].z = c;
    m[1].x = d; m[1].y = e; m[1].z = f;
    m[2].x = g; m[2].y = h; m[2].z = i;
}

// @ 0x004a8e10 — BuildFacingMatrix: two bases through the matrix, then Matrix3FromFacingAndUp.
struct V3g { float x, y, z; };
struct M3g { V3g m[3]; };
V3g* __cdecl VecMulMat(V3g* out, const V3g* v, const M3g* m);        // 0x041daf0
void* __cdecl Matrix3FromFacingAndUp(void* out, const void* f, const void* u); // 0x069b440
void* BuildFacingMatrix(void* param_1, void* param_2, unsigned char param_3)
{
    V3g f;
    V3g u;
    V3g tf;
    V3g tu;
    V3g* rf = VecMulMat(&tf, (const V3g*)0x015d63f4, (const M3g*)param_2);
    f.x = rf->x;
    f.y = rf->y;
    f.z = rf->z;
    V3g* ru = VecMulMat(&tu, (const V3g*)0x015d6324, (const M3g*)param_2);
    u.x = ru->x;
    u.y = ru->y;
    u.z = ru->z;
    if (param_3 == 0) {
        f.x = -f.x;
        u.x = -u.x;
    }
    else {
        f.z = -f.z;
        u.z = -u.z;
    }
    Matrix3FromFacingAndUp(param_1, &f, &u);
    return param_1;
}

// @ 0x004a9610 — ConvertToMatrix: quaternion -> Matrix33, then copy out.
struct M33 {
    float m[9];
    M33(const M33& o);                                   // 0x041cb40
};
void* __cdecl QuaternionToMatrix(void* out, const void* q);          // 0x04a9b40
void ConvertToMatrix(void* param_1, void* param_2)
{
    const float* p = (const float*)param_1;
    float q[4];
    q[3] = p[3];
    q[0] = p[0];
    q[1] = p[1];
    q[2] = p[2];
    char tmp[36];
    void* r = QuaternionToMatrix(tmp, q);
    M33 out(*(const M33*)r);
    *(M33*)param_2 = out;
}

// @ 0x004a89e0 — BuildOrientation: orthonormal basis from two vectors.
V3* __cdecl VecNegate(V3* out, const V3* v);                         // 0x0422020
V3* __cdecl VecCross(V3* out, const V3* a, const V3* b);             // 0x044e460
V3* __cdecl VecNormalize(V3* out, const V3* v);                      // 0x0436ce0
float __cdecl VecLength(const V3* v);                                // 0x040ae50
float __cdecl VecDot3(const V3* a, const V3* b);                     // 0x0455cc0
void* BuildSomeMatrix(void* param_1, void* param_2, void* param_3)
{
    V3 A;
    V3 B;
    V3 C;
    V3 Bn;
    VecNegate(&A, (const V3*)param_2);
    B.VecCopyCtor(*(const V3*)param_3);
    VecCross(&C, &A, &B);
    if (VecLength(&C) >= 0.005f) {
        VecCross(&Bn, &C, &A);
        VecNormalize(&A, &A);
        VecNormalize(&B, &Bn);
        VecNormalize(&C, &C);
    }
    else {
        if (VecDot3(&A, &B) >= 0.0f) {
            A.x = 0.0f; A.y = 0.0f; A.z = 1.0f;
            B.x = 0.0f; B.y = 1.0f; B.z = 0.0f;
            C.x = -1.0f; C.y = 0.0f; C.z = 0.0f;
        }
        else {
            A.x = 0.0f; A.y = 0.0f; A.z = -1.0f;
            B.x = 0.0f; B.y = 1.0f; B.z = 0.0f;
            C.x = 1.0f; C.y = 0.0f; C.z = 0.0f;
        }
    }
    M3 m(C.x, C.y, C.z, A.x, A.y, A.z, B.x, B.y, B.z);
    ((M3*)param_1)->AssignMat(m);
    return param_1;
}

// @ 0x004a92c0 — HavokAlignedRoutine: three rows into an hkRot, then Assign.
struct hkVec4 { float v[4]; };
struct hkRot {
    hkVec4 c0, c1, c2;
    void Assign(const hkRot& o);                         // 0x044a8c0
};
void HavokAlignedRoutine(void* param_1, void* param_2)
{
    const float* p = (const float*)param_1;
    hkRot r;
    r.c2.v[0] = p[6]; r.c2.v[1] = p[7]; r.c2.v[2] = p[8]; r.c2.v[3] = 0.0f;
    r.c1.v[0] = p[3]; r.c1.v[1] = p[4]; r.c1.v[2] = p[5]; r.c1.v[3] = 0.0f;
    r.c0.v[0] = p[0]; r.c0.v[1] = p[1]; r.c0.v[2] = p[2]; r.c0.v[3] = 0.0f;
    ((hkRot*)param_2)->Assign(r);
}
