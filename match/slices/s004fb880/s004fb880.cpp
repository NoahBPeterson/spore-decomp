// Slice s004fb880: force-field grid matrix helpers (unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast).
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
Vector3 operator*(const Vector3& a, const Vector3& b)
{
    Vector3 r;
    r.x = a.x * b.x;
    r.y = a.y * b.y;
    r.z = a.z * b.z;
    return r;
}
struct Axis { float x; float y; float PaddingForAlignment[1]; };
struct Matrix33 { Axis xAxis; Axis yAxis; Axis zAxis; };

float Determinant(const float* m);                  // 0x004fc680
void Matrix33_ctor(Matrix33* out, const void* src); // 0x0041cb40
void FUN_004ab450(void* out, void* a, void* b, void* c); // 0x004ab450

// @ 0x004fc680
float Determinant(const float* m)
{
    return m[0] * m[4] * m[8] + m[1] * m[5] * m[6] + m[2] * m[3] * m[7]
         - m[0] * m[5] * m[7] - m[1] * m[3] * m[8] - m[2] * m[4] * m[6];
}

// @ 0x004fc510
Vector3* MulComponents(Vector3* out, const Vector3* a, const Vector3* b)
{
    Vector3 r;
    r.x = a->x * b->x;
    r.y = a->y * b->y;
    r.z = a->z * b->z;
    Vector3 s = r;
    *out = s;
    return out;
}

// @ 0x004fc5a0
Vector3* SubInPlace(Vector3* a, const Vector3* b)
{
    float n12 = a->x - b->x;
    float t29 = a->y - b->y;
    float p30 = a->z - b->z;
    a->x = n12;
    a->y = t29;
    a->z = p30;
    return a;
}

// @ 0x004fc990
Matrix33* InvertScaled(Matrix33* out, const float* in, float* pDet)
{
    *pDet = Determinant(in);
    if (*pDet != 0.0f) {
        float inv[9];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int i1 = (i + 1) % 3;
                int i2 = (i + 2) % 3;
                int j1 = (j + 1) % 3;
                int j2 = (j + 2) % 3;
                inv[j * 3 + i] =
                    (*(const float*)((const char*)in + i1 * 0xc + j1 * 4) *
                     *(const float*)((const char*)in + i2 * 0xc + j2 * 4)
                   - *(const float*)((const char*)in + i2 * 0xc + j1 * 4) *
                     *(const float*)((const char*)in + i1 * 0xc + j2 * 4)) / *pDet;
            }
        }
        Matrix33_ctor(out, inv);
    }
    return out;
}

// @ 0x004fc700
Matrix33* InvertMatrix(Matrix33* out, const float* in)
{
    float det;
    InvertScaled(out, in, &det);
    return out;
}

// @ 0x004fbf20
Vector3* MulMatVec(Vector3* out, const float* m, const float* v)
{
    out->x = m[0] * v[0] + m[1] * v[1] + m[2] * v[2];
    out->y = m[3] * v[0] + m[4] * v[1] + m[5] * v[2];
    out->z = m[6] * v[0] + m[7] * v[1] + m[8] * v[2];
    return out;
}

// @ 0x004fc960
void FUN_004fc960(void* a, void* b, void* c)
{
    uint32_t p30;
    void* t29 = a;
    char n12[4];
    void* z = t29;
    FUN_004ab450(n12, z, b, c);
}

// ---------------------------------------------------------------------------
// Large functions reconstructed from the Ghidra decompile (not byte-exact; the
// /Od frames are not reproduced).
// ---------------------------------------------------------------------------
struct SphereFields {
    float mX[4];
    float mY[4];
    float mZ[4];
    float mRadiusSq[4];
    float mInvRadiusSq[4];
    float mStrength[4];
    float mScaledStrength[4];
    uint32_t mId[4];
    void Clear(int index);                                    // 0x004f81a0
    void Accumulate(const Vector3* pos, float* pScalar, Vector3* pVec, float* pMat);
};

Vector3* ScaleVec(Vector3* out, const float* s, const Vector3* v);     // 0x0041de40
Vector3* AddV(Vector3* out, const Vector3* a, const Vector3* b);       // 0x0041dc10
Vector3* MulScalarV(Vector3* out, const Vector3* v, const float* s);   // 0x0041dca0
Vector3* SubV(Vector3* out, const Vector3* a, const Vector3* b);       // 0x0041db10
void ScaleInPlace(Vector3* v, float s);                                // 0x0041dba0
void FUN_004f89a0();                                                   // 0x004f89a0
void operator_new__(void* p, int a, int n);                            // placement helper
extern "C" double __cdecl sqrt(double);

// @ 0x004fb880
void SphereFields::Accumulate(const Vector3* pos, float* pScalar, Vector3* pVec, float* pMat)
{
    for (int i = 0; i < 4; ++i) {
        if (mRadiusSq[i] != 0.0f) {
            Vector3 d;
            d.x = pos->x - mX[i];
            d.y = pos->y - mY[i];
            d.z = pos->z - mZ[i];
            float d2 = d.x * d.x + d.y * d.y + d.z * d.z;
            if (d2 < mRadiusSq[i]) {
                float t = d2 * mInvRadiusSq[i];
                float k = t - 1.0f;
                float k2 = k * k;
                float c1 = ((mScaledStrength[i] * 8.0f) * k2) * k;
                float c2 = ((mScaledStrength[i] * 24.0f) * mInvRadiusSq[i]) * k2;
                *pScalar = (mStrength[i] * k2) * k2 + *pScalar;
                pVec->x = c1 * d.x + pVec->x;
                pVec->y = c1 * d.y + pVec->y;
                pVec->z = c1 * d.z + pVec->z;
                Vector3 g;
                ScaleVec(&g, &c2, &d);
                pMat[0] = (g.x * d.x + c1) + pMat[0];
                pMat[1] = g.x * d.y + pMat[1];
                pMat[2] = g.x * d.z + pMat[2];
                pMat[4] = (g.y * d.y + c1) + pMat[4];
                pMat[5] = g.y * d.z + pMat[5];
                pMat[8] = (g.z * d.z + c1) + pMat[8];
            }
        }
    }
}

// Field grid layout shared by the two builders below.
struct FieldGrid {
    char pad00[0x0c];
    float mField0c;
    char pad10[0x04];
    int mField14;
    int mField18;
    int mField1c;
    Vector3 mV20;                 // +0x20
    Vector3 mV2c;                 // +0x2c
    float m38, m3c, m40;
    char pad44[0x0c];
    void* mField50;
    void* mField54;
};

Vector3* BuildOBB(FieldGrid* self, const Vector3* a, const Vector3* b, float* pMat, uint32_t* pFlags, float* pCorner); // 0x004fa6c0

// @ 0x004fbcc0
int MarchToSurface(FieldGrid* self, float radius, Vector3* pPoint, Vector3* pStart, Matrix33* pOut)
{
    const float kEps = 1e-10f;
    Vector3 cur = pStart ? *pStart : *pPoint;
    float step = radius;
    float stepSq = radius * radius;
    for (int iter = 0; iter < 0x28; ++iter) {
        Vector3 delta;
        float mat[9];
        BuildOBB(self, pPoint, &cur, mat, (uint32_t*)&delta, (float*)pOut);
        if (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z < kEps)
            return 1;
        float d = Determinant(mat);
        if (d == 0.0f)
            return 0;
        if (!(fabsf(d) < 3.402823466e+38f))
            return 0;
        Matrix33 inv;
        InvertMatrix(&inv, mat);
        Vector3 move;
        MulMatVec(&move, (const float*)&inv, &delta.x);
        float lenSq = move.x * move.x + move.y * move.y + move.z * move.z;
        if (stepSq < lenSq) {
            ScaleInPlace(&move, step / (float)sqrt((double)lenSq));
        }
        SubInPlace(pPoint, &move);
    }
    return 0;
}

// @ 0x004fc100
Vector3* RayBisect(void* self, Vector3* pOut, const Vector3* pFrom, const Vector3* pTo, float* pT)
{
    Vector3 base = *pFrom;
    Vector3 dir;
    SubV(&dir, pTo, pFrom);
    float limit = *(float*)((char*)self + 0x0c) * 0.1f;
    float* pBound = (float*)((char*)self + 0x44);
    float bound = (limit < *pBound || limit == *pBound) ? limit : *pBound;
    float lo = 0.0f;
    float hi = 1.0f;
    Vector3 pos = *pFrom;
    float t = 0.0f;
    int guard = 0x14;
    float value = 0.0f;
    do {
        t = (lo + hi) * 0.5f;
        Vector3 off;
        MulScalarV(&off, &dir, &t);
        Vector3 p;
        AddV(&p, &base, &off);
        pos = p;
        value = 0.0f;
        typedef void (*Fn)(const Vector3*, float*);
        Fn fn = *(Fn*)((char*)self + 8);
        fn(&pos, &value);
        if (value < 0.0f)
            hi = t;
        else
            lo = t;
    } while (bound < fabsf(value) && (--guard > 0));
    if (pT)
        *pT = t;
    *pOut = pos;
    return pOut;
}

// @ 0x004fc320
void FieldGridReset(FieldGrid* self, char clear)
{
    for (int i = 0; i < self->mField18; ++i)
        ((SphereFields*)((char*)(int)self->mField1c + i * 0x80))->Clear(-1);
    self->mField14 = 0;
    self->mV20.x = 3.402823466e+38f;
    self->mV20.y = 3.402823466e+38f;
    self->mV20.z = 3.402823466e+38f;
    self->mV2c.x = -3.402823466e+38f;
    self->mV2c.y = -3.402823466e+38f;
    self->mV2c.z = -3.402823466e+38f;
    self->m38 = 0.0f;
    self->m3c = 0.0f;
    self->m40 = 0.0f;
    if (clear) {
        FUN_004f89a0();
        operator_new__(self->mField54, 0, 0x800);
    }
}

