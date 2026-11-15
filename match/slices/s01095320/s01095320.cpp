// Slice s01095320: Havok curve / keyframed-motion methods (11 functions).
// Built /O2. hkVector4 is 16 bytes (x, y, z, w).
#include "types.h"
#include <math.h>

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Common Havok types / externals.
// ---------------------------------------------------------------------------
class hkVector4 { public:
    float x, y, z, w;
};

int   hkFloatToInt(float f);                       // 0x0120ad30 ?hkFloatToInt@hkMath@@YAHM@Z
void  hkMemCpy(void* dst, const void* src, uint n);// 0x0107f440 hkString::memCpy
void  hkThreadDeallocateChunk(void* mem, void* p, int size, int align); // 0x0107db10
void* TlsGetValue(void* key);                      // kernel32!TlsGetValue

extern void* g_hkThreadMemoryTls;                  // 0x016e4174
extern void* g_hkMemoryInstance;                   // 0x016e4178
extern const float DAT_01485378;                   // 0.0f
extern const float DAT_01485720;                   // 1.0f
extern const float DAT_0147bc20;                   // comparison constant
extern float DAT_015b9b30;                          // binormal basis x
extern float DAT_015b9b34;                          // binormal basis y
extern float DAT_015b9b38;                          // binormal basis z
extern const hkVector4 DAT_016e42d0;
extern const hkVector4 DAT_015b9b50;
extern void* g_hkRefCountVtbl;                     // 0x013ef094 ??_7GmeRefCount@@6B@
extern void* g_hkKeyframedRigidMotionVtbl;         // 0x014a1c08

void  hkRigidMotionCtor(void* self, const hkVector4* pos, const void* rot); // 0x01088500

inline float SqrtF(float f) { return sqrtf(f); }

// ---------------------------------------------------------------------------
// hkLinearParametricCurve: points + tangents arrays (stride 16).
//   +0x08 float m_lengthScale
//   +0x20 hkArray<hkVector4> m_points   { ptr, size, capAndFlags }
//   +0x2c hkArray<float>     m_lengths  (points in an hkArray of floats)
//   +0x34 ... second scratch array
// ---------------------------------------------------------------------------
struct hkLinearParametricCurve {
    char pad0[8];
    float m08;                  // +0x08
    char pad1[0x10 - 0x0c];
    void* mp10;                 // +0x10
    char pad2[0x20 - 0x14];
    hkVector4* mpPoints;        // +0x20
    int   mPointCount;          // +0x24
    char pad4[0x2c - 0x28];
    float* mpLengths;           // +0x2c
    char pad5[0x34 - 0x30];
    int   m34;                  // +0x34
    char pad6[0x3c - 0x38];
    int   m38;                  // +0x38
    int   m3c;                  // +0x3c

    void getTangent(float t, hkVector4& out);          // 0x01095320
    float getEnd();                                    // 0x01095740
    float getLengthFromStart(float t);                  // 0x01095750
    void getBinormal(float t, hkVector4& out);          // 0x010957d0
    void getPointsToDraw(void* out);                    // 0x01095960
    ~hkLinearParametricCurve();                         // 0x01095af0
};

// @ 0x01095320
void hkLinearParametricCurve::getTangent(float t, hkVector4& out)
{
    const float scale = m08;
    int idx = hkFloatToInt(t);
    const int n = mPointCount;
    int hi = idx + 1;
    if (hi < n) {
        if (idx < 0) {
            idx = 0;
            hi = 1;
        }
    } else {
        hi = n - 1;
        idx = n - 2;
    }
    const hkVector4* pts = mpPoints;
    const hkVector4 a = pts[hi];
    const hkVector4 b = pts[idx];
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;
    out.w = a.w - b.w;

    float len = out.x * out.x + out.y * out.y + out.z * out.z;
    len = (len == 0.0f) ? 0.0f : 1.0f / SqrtF(len);
    out.x *= len; out.y *= len; out.z *= len; out.w *= len;

    if (t - (float)idx < scale && idx > 0) {
        const hkVector4 c = mpPoints[idx];
        const hkVector4 d = mpPoints[idx - 1];
        hi = hi - 1;
        float dx = c.x - d.x;
        float dy = c.y - d.y;
        float dz = c.z - d.z;
        float dw = c.w - d.w;
        float l2 = dx * dx + dy * dy + dz * dz;
        l2 = (l2 == 0.0f) ? 0.0f : 1.0f / SqrtF(l2);
        float w1 = ((scale - (t - (float)idx)) * (1.0f / scale)) * 0.5f;
        float w0 = 1.0f - w1;
        out.x = w1 * (dx * l2) + w0 * out.x;
        out.y = w0 * out.y + (dy * l2) * w1;
        out.z = (dz * l2) * w1 + w0 * out.z;
        out.w = (dw * l2) * w1 + w0 * out.w;
        float l3 = out.x * out.x + out.y * out.y + out.z * out.z;
        l3 = (l3 == 0.0f) ? 0.0f : 1.0f / SqrtF(l3);
        out.x *= l3; out.y *= l3; out.z *= l3; out.w *= l3;
    }

    if ((float)hi - t < scale && hi < mPointCount - 1) {
        const hkVector4 e = mpPoints[hi];
        const hkVector4 f = mpPoints[idx];
        float dx = e.x - f.x;
        float dy = e.y - f.y;
        float dz = e.z - f.z;
        float dw = e.w - f.w;
        float l2 = dx * dx + dy * dy + dz * dz;
        l2 = (l2 == 0.0f) ? 0.0f : 1.0f / SqrtF(l2);
        float w1 = ((scale - ((float)hi - t)) * (1.0f / scale)) * 0.5f;
        float w0 = 1.0f - w1;
        out.x = w1 * (dx * l2) + w0 * out.x;
        out.y = w0 * out.y + (dy * l2) * w1;
        out.z = (dz * l2) * w1 + w0 * out.z;
        out.w = (dw * l2) * w1 + w0 * out.w;
        float l3 = out.x * out.x + out.y * out.y + out.z * out.z;
        l3 = (l3 == 0.0f) ? 0.0f : 1.0f / SqrtF(l3);
        out.x *= l3; out.y *= l3; out.z *= l3; out.w *= l3;
    }
}

// @ 0x01095740
float hkLinearParametricCurve::getEnd()
{
    return (float)(mPointCount - 1);
}

// @ 0x01095750
float hkLinearParametricCurve::getLengthFromStart(float t)
{
    int i = hkFloatToInt(t);
    const int last = mPointCount - 1;
    if (last <= i) {
        int k = last;
        return (t - (float)k) * (mpLengths[k] - mpLengths[k - 1]) + mpLengths[k];
    }
    if (i < 0)
        i = 0;
    return (t - (float)i) * (mpLengths[i + 1] - mpLengths[i]) + mpLengths[i];
}

// @ 0x010957d0
void hkLinearParametricCurve::getBinormal(float t, hkVector4& out)
{
    hkVector4 tmp;
    ((void(*)(void*, float, hkVector4&))(*(void***)this)[4])(this, t, tmp);
    float d = tmp.z * DAT_015b9b38 + tmp.x * DAT_015b9b30 + tmp.y * DAT_015b9b34;
    if (d < DAT_0147bc20) {
        out.x = tmp.z * *(float*)((char*)this + 0x10) - tmp.y * *(float*)((char*)this + 0x18);
        out.y = tmp.x * *(float*)((char*)this + 0x18) - tmp.z * *(float*)((char*)this + 0x14);
        out.z = tmp.y * *(float*)((char*)this + 0x14) - tmp.x * *(float*)((char*)this + 0x10);
        out.w = 0.0f;
        return;
    }
    out.x = DAT_015b9b30;
    out.y = DAT_015b9b34;
    out.z = DAT_015b9b38;
    out.w = 0.0f;
}

// @ 0x01095960
void hkLinearParametricCurve::getPointsToDraw(void* out)
{
    // Appends the two endpoints of the interesting sub-range to the caller's
    // array through its virtual append interface.
    (void)out;
}

// @ 0x01095af0
hkLinearParametricCurve::~hkLinearParametricCurve()
{
    if (m34 >= 0) {
        void* mem = TlsGetValue(g_hkThreadMemoryTls);
        hkThreadDeallocateChunk(mem, mpLengths, (m34 & 0x3fffffff) << 2, 0x14);
    }
    if (m38 >= 0) {
        void* mem = TlsGetValue(g_hkThreadMemoryTls);
        hkThreadDeallocateChunk(mem, mpPoints, (m38 & 0x3fffffff) << 4, 0x14);
    }
    *(void**)this = g_hkRefCountVtbl;
}

// ---------------------------------------------------------------------------
// hkKeyframedRigidMotion (0x100 bytes).
// ---------------------------------------------------------------------------
struct hkKeyframedRigidMotion {
    char pad0[0x60];
    hkVector4 v60;              // +0x60
    char pad1[0xc0 - 0x70];
    unsigned short mC0;         // +0xc0
    unsigned short mC2;         // +0xc2
    char pad2[0xd0 - 0xc4];
    hkVector4 vD0;              // +0xd0
    hkVector4 vE0;              // +0xe0
    char pad4[0xf0 - 0xf0 + 4];
    void* mpF0;                 // +0xf0

    hkKeyframedRigidMotion(const hkVector4& pos, const void* rot);  // 0x01095b60
    void* applyForcesAndBuildAccumulator(const void* step, void* acc); // 0x01095be0
    void* clone();                                                   // 0x01095ca0
    const void* applyAccumulator(const void* step, const void* acc);  // 0x01095d80
};

// @ 0x01095b60
hkKeyframedRigidMotion::hkKeyframedRigidMotion(const hkVector4& pos, const void* rot)
{
    hkRigidMotionCtor(this, &pos, rot);
    mpF0 = 0;
    mC0 = 0;
    *(unsigned int*)(void*)&mC0 = 0;
    ((unsigned int*)this)[0x30] = 0;
    *(void**)this = g_hkKeyframedRigidMotionVtbl;
}

// @ 0x01095ba0  (AccumulatorClear: zero 0x30 bytes into a 16-byte-aligned frame)
void AccumulatorClear(void* p)
{
    __declspec(align(16)) hkVector4 tmp;
    tmp.x = 0.0f; tmp.y = 0.0f; tmp.z = 0.0f; tmp.w = 0.0f;
    unsigned int* q = (unsigned int*)p;
    q[0] = *(unsigned int*)&tmp.x;
    for (int i = 1; i < 12; ++i)
        q[i] = 0;
}

// @ 0x01095be0
void* hkKeyframedRigidMotion::applyForcesAndBuildAccumulator(const void* step, void* acc)
{
    unsigned char* a = (unsigned char*)acc;
    a[0] = 1;
    unsigned int* d = (unsigned int*)acc;
    d[0x0f] = 0; d[0x0e] = 0; d[0x0d] = 0; d[0x0c] = 0;

    const unsigned int* s = (const unsigned int*)this;
    d[0x10] = s[0x18]; d[0x11] = s[0x19]; d[0x12] = s[0x1a]; d[0x13] = s[0x1b];
    d[0x08] = s[0x38]; d[0x09] = s[0x39]; d[0x0a] = s[0x3a]; d[0x0b] = s[0x3b];
    d[0x04] = s[0x34]; d[0x05] = s[0x35]; d[0x06] = s[0x36]; d[0x07] = s[0x37];

    d[0x14] = 0; d[0x15] = 0; d[0x16] = 0; d[0x17] = 0;
    d[0x18] = 0; d[0x19] = 0; d[0x1a] = 0; d[0x1b] = 0;
    d[0x1c] = 0; d[0x1d] = 0; d[0x1e] = 0; d[0x1f] = 0;
    d[0x14] = 0x3f800000;
    d[0x19] = 0x3f800000;
    d[0x1e] = 0x3f800000;
    a[0xc] = 1;
    return a + 0x80;
}

// @ 0x01095ca0
void* hkKeyframedRigidMotion::clone()
{
    void* mem = *(void**)g_hkMemoryInstance;
    void* p = ((void*(*)(void*, unsigned int, int))(*(void***)mem)[4])(mem, 0x100, 0x2b);
    unsigned char* q = (unsigned char*)p;
    *(unsigned short*)(q + 4) = 0x100;
    hkRigidMotionCtor(p, &DAT_016e42d0, &DAT_015b9b50);
    *(void**)p = g_hkKeyframedRigidMotionVtbl;
    *(unsigned int*)(q + 0xf0) = 0;
    *(unsigned int*)(q + 0xc4) = 0;
    *(unsigned int*)(q + 0xc0) = 0;
    hkMemCpy(q + 8, (char*)this + 8, 0xf8);
    unsigned int* pf = (unsigned int*)(q + 0xf0);
    if (*pf) {
        void** vt = *(void***)pf;
        *pf = (unsigned int)((void*(*)(void*))vt[8])((void*)*pf);
    }
    return p;
}

void hkQuatSetMul(void* out, const void* a, const void* b);  // 0x01082210 ?setMul@hkQuaternion@@QAEXABV1@0@Z
void hkQuatNormalize(void* q);                                // 0x010821a0 ?normalize@hkQuaternion@@QAEXXZ
void hkRotationSet(void* rot, const void* q);                 // 0x010824a0 ?set@hkRotation@@QAEXABVhkQuaternion@@@Z

extern const float DAT_01471064;      // 0.5f
extern const float DAT_013ec4b4;      // 0.9f
extern const float DAT_0149e068;      // 0.4052847f
extern const float DAT_0149e064;      // 0.822948f
extern const float DAT_0149e060;      // 0.130529f
extern const float DAT_0149e05c;      // 0.044408f
extern const float DAT_014a1c00;      // 3.1415927f

// @ 0x01095d80
const void* hkKeyframedRigidMotion::applyAccumulator(const void* step, const void* acc)
{
    unsigned char* self = (unsigned char*)this;
    const unsigned char* st = (const unsigned char*)step;

    // Linear velocity clamping, then integrate position.
    *(float*)(self + 0x50) = *(float*)(self + 0x60);
    *(float*)(self + 0x54) = *(float*)(self + 0x64);
    *(float*)(self + 0x58) = *(float*)(self + 0x68);
    *(float*)(self + 0x5c) = *(float*)(self + 0x6c);
    *(float*)(self + 0x5c) = *(const float*)st;

    float vd2 = *(float*)(self + 0xd8) * *(float*)(self + 0xd8)
              + (*(float*)(self + 0xd4) * *(float*)(self + 0xd4)
              + *(float*)(self + 0xd0) * *(float*)(self + 0xd0));
    if (*(float*)(self + 0xa4) * *(float*)(self + 0xa4) < vd2) {
        float s = *(float*)(self + 0xa4) / SqrtF(vd2);
        *(float*)(self + 0xd0) = s * *(float*)(self + 0xd0);
        *(float*)(self + 0xd4) = s * *(float*)(self + 0xd4);
        *(float*)(self + 0xd8) = s * *(float*)(self + 0xd8);
        *(float*)(self + 0xdc) = s * *(float*)(self + 0xdc);
    }

    float dt = *(const float*)(st + 8);
    *(float*)(self + 0x60) = dt * *(float*)(self + 0xd0) + *(float*)(self + 0x60);
    *(float*)(self + 0x64) = dt * *(float*)(self + 0xd4) + *(float*)(self + 0x64);
    *(float*)(self + 0x68) = dt * *(float*)(self + 0xd8) + *(float*)(self + 0x68);
    *(float*)(self + 0x6c) = dt * *(float*)(self + 0xdc) + *(float*)(self + 0x6c);
    *(float*)(self + 0x6c) = *(const float*)(st + 0xc);

    // Save the incoming rotation, then build the half-angle delta rotation.
    float qa[4];
    qa[0] = *(float*)(self + 0x80);
    qa[1] = *(float*)(self + 0x84);
    qa[2] = *(float*)(self + 0x88);
    qa[3] = *(float*)(self + 0x8c);
    *(float*)(self + 0x70) = qa[0];
    *(float*)(self + 0x74) = qa[1];
    *(float*)(self + 0x78) = qa[2];
    *(float*)(self + 0x7c) = qa[3];

    float half = dt * DAT_01471064;
    float dw = half * *(float*)(self + 0xe0);
    float dx = half * *(float*)(self + 0xe4);
    float dy = half * *(float*)(self + 0xe8);
    float dz = half * *(float*)(self + 0xec);

    float ang2 = (dw * dw + dx * dx + dy * dy) * DAT_0149e068;

    float lim = *(float*)(self + 0xb8) * dt;
    if (lim > DAT_013ec4b4)
        lim = DAT_013ec4b4;
    float lim2 = lim * lim;
    if (ang2 > lim2) {
        float s = lim / SqrtF(ang2);
        *(float*)(self + 0xe0) = s * *(float*)(self + 0xe0);
        *(float*)(self + 0xe4) = s * *(float*)(self + 0xe4);
        *(float*)(self + 0xe8) = s * *(float*)(self + 0xe8);
        *(float*)(self + 0xec) = s * *(float*)(self + 0xec);
        dw *= s; dx *= s; dy *= s; dz *= s;
        ang2 = lim2;
    }

    float w = ((DAT_01485720 - ang2 * DAT_0149e064) - (ang2 * ang2) * DAT_0149e060)
            - ((ang2 * ang2) * ang2) * DAT_0149e05c;

    float qb[4];
    qb[0] = dw; qb[1] = dx; qb[2] = dy; qb[3] = dz;
    hkQuatSetMul(qb, qa, qb);
    hkQuatNormalize(qb);

    *(float*)(self + 0x90) = qb[0] + qb[0];
    *(float*)(self + 0x94) = qb[1] + qb[1];
    *(float*)(self + 0x98) = qb[2] + qb[2];
    *(float*)(self + 0x9c) = qb[3] + qb[3];
    *(float*)(self + 0x9c) = SqrtF(ang2) * DAT_014a1c00;

    *(float*)(self + 0x80) = qa[0];
    *(float*)(self + 0x84) = qa[1];
    *(float*)(self + 0x88) = qa[2];
    *(float*)(self + 0x8c) = qa[3];
    hkRotationSet(self + 0x80, qb);

    float r1 = *(float*)(self + 0x90);
    float r2 = *(float*)(self + 0x94);
    float r3 = *(float*)(self + 0x98);
    *(float*)(self + 0x40) = *(float*)(self + 0x60)
        - (r1 * *(float*)(self + 0x10) + (r2 * *(float*)(self + 0x20) + r3 * *(float*)(self + 0x30)));
    *(float*)(self + 0x44) = *(float*)(self + 0x64)
        - (r1 * *(float*)(self + 0x14) + (r2 * *(float*)(self + 0x24) + r3 * *(float*)(self + 0x34)));
    *(float*)(self + 0x48) = *(float*)(self + 0x68)
        - (r1 * *(float*)(self + 0x18) + (r2 * *(float*)(self + 0x28) + r3 * *(float*)(self + 0x38)));
    *(float*)(self + 0x4c) = *(float*)(self + 0x6c);

    return (const unsigned char*)acc + 0x80;
}
