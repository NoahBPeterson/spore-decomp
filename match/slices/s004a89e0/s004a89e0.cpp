// Slice s004a89e0 — Spore editor matrix/vector helpers (/Od /Ob1 /arch:SSE2 /fp:fast).
#include "types.h"

struct V3 {
    float x, y, z;
    float& operator[](int i) { return ((float*)this)[i]; }
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
};
M3::M3(float a, float b, float c, float d, float e, float f,
       float g, float h, float i)
{
    m[0].x = a; m[0].y = b; m[0].z = c;
    m[1].x = d; m[1].y = e; m[1].z = f;
    m[2].x = g; m[2].y = h; m[2].z = i;
}

// @ 0x004a8e10 — Matrix3FromFacingAndUp wrapper (best effort).
extern void* UncheckedIdl0(void* out, void* tag, void* arg);
extern void Matrix3FromFacingAndUp(void* out, void* facing, void* up);
void* BuildFacingMatrix(void* param_1, void* param_2, unsigned char param_3)
{
    float f1[3];
    float u1[3];
    char buf1[12];
    char buf2[12];
    float* a = (float*)UncheckedIdl0(buf1, (void*)0x015d63f4, param_2);
    f1[0] = a[0]; f1[1] = a[1]; f1[2] = a[2];
    float* b = (float*)UncheckedIdl0(buf2, (void*)0x015d6324, param_2);
    u1[0] = b[0]; u1[1] = b[1]; u1[2] = b[2];
    if (param_3 == 0) {
        *(uint32_t*)&f1[0] ^= 0x80000000u;
        *(uint32_t*)&u1[0] ^= 0x80000000u;
    }
    else {
        *(uint32_t*)&f1[2] ^= 0x80000000u;
        *(uint32_t*)&u1[2] ^= 0x80000000u;
    }
    Matrix3FromFacingAndUp(param_1, f1, u1);
    return param_1;
}

// @ 0x004a9610 — matrix conversion (best effort).
extern void* FUN_004a9b40(void* out, const void* in);
extern void Matrix3Assign(void* out, void* in);
void ConvertToMatrix(void* param_1, void* param_2)
{
    float f[4];
    float* p = (float*)param_1;
    f[0] = p[0]; f[1] = p[1]; f[2] = p[2]; f[3] = p[3];
    char tmp[36];
    void* m = FUN_004a9b40(tmp, f);
    char out[36];
    Matrix3Assign(out, m);
    float* src = (float*)out;
    float* dst = (float*)param_2;
    for (int i = 0; i < 9; ++i) dst[i] = src[i];
}

// @ 0x004a89e0 — large matrix routine (best effort).
extern void* FUN_00422020(void* out, void* in);
extern void FUN_004098a0(void* in);
extern void* FUN_0044e460(void* out, void* a, void* b);
extern void* FUN_00436ce0(void* out, void* in);
extern double FUN_0040ae50(void* in);
extern double FUN_00455cc0(void* a, void* b);
extern void FUN_00449cc0(void* out);
void* BuildSomeMatrix(void* param_1, void* param_2, void* param_3)
{
    float v0[3], v1[3], v2[3], v3[3], v4[3], v5[3], v6[3], v7[3];
    char b1[12], b2[12];
    void* q = FUN_00422020(b1, param_2);
    v0[0] = ((float*)q)[0]; v0[1] = ((float*)q)[1]; v0[2] = ((float*)q)[2];
    FUN_004098a0(param_3);
    q = FUN_0044e460(b2, v0, v1);
    v2[0] = ((float*)q)[0]; v2[1] = ((float*)q)[1]; v2[2] = ((float*)q)[2];
    if ((double)0.005 <= FUN_0040ae50(v2)) {
        // best effort placeholder
    }
    FUN_00449cc0(v7);
    (void)v3; (void)v4; (void)v5; (void)v6;
    return param_1;
}

// @ 0x004a92c0 — 16-byte aligned Havok path (not reconstructed).
void HavokAlignedRoutine(void* param_1, void* param_2)
{
    (void)param_1;
    (void)param_2;
}
