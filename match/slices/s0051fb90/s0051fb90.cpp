// Slice 8: nSPSkinner vector/normalize helpers and a small packed-value unpacker.
// Flags: /Od /Ob1 /Oi /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc); /Oi is required for sqrtf to
// lower to the x87 _CIsqrt import and /fp:fast for the scalar SSE dot product.
#include "types.h"
#include <math.h>

void* FUN_0050a880(void* out, int p);          // 0x0050a880
int   FUN_004fddb0(void* v);                   // 0x004fddb0
void* FUN_0044e460(void* out, ...);             // 0x0044e460
void* FUN_00436ce0(void* out, void* a);        // 0x00436ce0
void  FUN_004a9d20(void* a, void* b);          // 0x004a9d20
float FUN_011e0738(float x);                   // 0x011e0738 lib_cblock sqrt
void  FUN_00520220(int p, float* outA, float* outB);

extern float g_1485720;   // 1.0f
extern float g_1485378;   // 0.0f

// @ 0x00520110
unsigned FUN_00520110(int p, unsigned v)
{
    if (v & 0x80000000u)
        return (unsigned)*(unsigned char*)(*(int*)(p + 0x20) + (v & 0x7fffffffu));
    return v;
}

struct V3_s0051_fb90 { float x, y, z; };

// @ 0x00520140
void FUN_00520140(int p, int flags, float* outDir, float* outVal)
{
    V3_s0051_fb90 vec;
    FUN_0044e460(&vec, (float*)p, (float*)flags);
    float len2 = (vec.x * vec.x + vec.y * vec.y) + vec.z * vec.z;
    if (len2 <= g_1485378) {
        FUN_00520220(p, outDir, outVal);
    } else {
        float inv = sqrtf(len2);
        FUN_004a9d20(&vec, &inv);
        *(V3_s0051_fb90*)outVal = vec;
        V3_s0051_fb90 cross;
        V3_s0051_fb90* t = (V3_s0051_fb90*)FUN_0044e460(&cross, &vec, (float*)p);
        V3_s0051_fb90 nrm;
        V3_s0051_fb90* n = (V3_s0051_fb90*)FUN_00436ce0(&nrm, t);
        *(V3_s0051_fb90*)outDir = *n;
    }
}

// @ 0x00520220
void FUN_00520220(int p, float* outA, float* outB)
{
    float v[3]; v[0] = g_1485720; v[1] = g_1485720; v[2] = g_1485720;
    float tmp[3];
    int idx = FUN_004fddb0(FUN_0050a880(tmp, p));
    v[idx] = 0.0f;
    float t2[3], t3[3];
    float* n1 = (float*)FUN_00436ce0(t3, FUN_0044e460(t2, v, p));
    outA[0] = n1[0]; outA[1] = n1[1]; outA[2] = n1[2];
    float t4[3], t5[3];
    float* n2 = (float*)FUN_00436ce0(t5, FUN_0044e460(t4, p, outA));
    outB[0] = n2[0]; outB[1] = n2[1]; outB[2] = n2[2];
}

// ---------------------------------------------------------------- FUN_0051fb90 helpers

extern float g_1471064;   // 0x1471064 (0.5f)

struct S0051Mat3 { V3_s0051_fb90 xAxis, yAxis, zAxis; };

struct S0051Elem {
    char          pad00[0x14];
    V3_s0051_fb90 a;        // +0x14
    V3_s0051_fb90 b;        // +0x20
    float         scale;    // +0x2c
    S0051Mat3     mat;      // +0x30
    V3_s0051_fb90 t;        // +0x54
    char          pad60[0x2c];
};

struct S0051Mesh {
    char       pad00[0x98];
    S0051Elem* mpElems;     // +0x98
};

struct S0051Mapper {
    char           pad00[0x08];
    S0051Mesh*     mpMesh;  // +0x08
    char           pad0c[0x14];
    unsigned char* mpRemap; // +0x20 (packed -> index remap table)
};

struct Vector2_s0051_fb90 { float x, y; };

struct S0051HitFlags {
    char     pad00[0x1c];
    uint32_t flags;         // +0x1c
};

struct S0051Skinner {
    char           pad00[0x190];
    uint32_t*      mpPacked;                                              // +0x190
    V3_s0051_fb90* GetSkinnedPoint(V3_s0051_fb90* out, int idx, Vector2_s0051_fb90 v); // 0x50c490
    void           GetFaceNormal(V3_s0051_fb90* out, int idx);                          // 0x5121c0
};

void FUN_0041daf0(V3_s0051_fb90* out, const V3_s0051_fb90* v, const S0051Mat3* m);  // 0x41daf0
void FUN_0041dc10(V3_s0051_fb90* out, const V3_s0051_fb90* a, const V3_s0051_fb90* b); // 0x41dc10
void FUN_0041db10(V3_s0051_fb90* out, const V3_s0051_fb90* a, const V3_s0051_fb90* b); // 0x41db10
void FUN_0041dca0(V3_s0051_fb90* out, const V3_s0051_fb90* v, const float* s);        // 0x41dca0
void FUN_0041dba0(V3_s0051_fb90* v, const float* s);                                  // 0x41dba0
void FUN_0041ddb0(V3_s0051_fb90* a, const V3_s0051_fb90* b);                          // 0x41ddb0
void FUN_00422020(V3_s0051_fb90* out, const V3_s0051_fb90* v);                        // 0x422020

// @ 0x0051fb90
void FUN_0051fb90(int kind, V3_s0051_fb90* v2, int idx, Vector2_s0051_fb90 v4,
                  S0051HitFlags* self, S0051Mapper* mapper, S0051Skinner* skinner,
                  V3_s0051_fb90* out)
{
    V3_s0051_fb90 result;

    switch (kind) {
    case 3:
        result = *v2;
        break;

    case 5: {
        V3_s0051_fb90 faceN;
        skinner->GetFaceNormal(&faceN, idx);
        uint32_t   raw  = skinner->mpPacked[idx] >> 16;
        S0051Elem* elem = &mapper->mpMesh->mpElems[FUN_00520110((int)mapper, raw)];
        V3_s0051_fb90 yAxis = elem->mat.yAxis;
        V3_s0051_fb90 cross;
        FUN_0044e460(&cross, &faceN, &yAxis);
        V3_s0051_fb90 nrm;
        FUN_00436ce0(&nrm, &cross);
        result = nrm;
        break;
    }

    case 6: {
        uint32_t   raw  = (skinner->mpPacked[idx] >> 8) & 0xff;
        S0051Elem* elem = &mapper->mpMesh->mpElems[FUN_00520110((int)mapper, raw)];
        V3_s0051_fb90 tmp;
        FUN_0041daf0(&tmp, v2, &elem->mat);
        result = tmp;
        break;
    }

    case 7: {
        uint32_t   raw  = (skinner->mpPacked[idx] >> 8) & 0xff;
        S0051Elem* elem = &mapper->mpMesh->mpElems[FUN_00520110((int)mapper, raw)];

        V3_s0051_fb90 sum;
        FUN_0041dc10(&sum, &elem->a, &elem->b);
        float half = g_1471064;
        V3_s0051_fb90 pos;
        FUN_0041dca0(&pos, &sum, &half);
        FUN_0041dba0(&pos, &elem->scale);
        V3_s0051_fb90 rotated;
        FUN_0041daf0(&rotated, &pos, &elem->mat);
        pos = rotated;
        FUN_0041ddb0(&pos, &elem->t);

        V3_s0051_fb90  skinned;
        V3_s0051_fb90* r = skinner->GetSkinnedPoint(&skinned, idx, v4);
        V3_s0051_fb90  rel;
        FUN_0041db10(&rel, r, &pos);

        V3_s0051_fb90 yAxis = elem->mat.yAxis;
        V3_s0051_fb90 cross;
        FUN_0044e460(&cross, &rel, &yAxis);
        V3_s0051_fb90 nrm;
        FUN_00436ce0(&nrm, &cross);
        result = nrm;
        break;
    }

    default: {
        uint32_t   raw  = skinner->mpPacked[idx] >> 16;
        S0051Elem* elem = &mapper->mpMesh->mpElems[FUN_00520110((int)mapper, raw)];
        V3_s0051_fb90 tmp;
        FUN_0041daf0(&tmp, v2, &elem->mat);
        result = tmp;
        break;
    }
    }

    if (self->flags & 0x10) {
        V3_s0051_fb90 neg;
        FUN_00422020(&neg, &result);
        result = neg;
    }
    *out = result;
}
