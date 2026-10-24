// Decompiled source for bfs3 slice 43: Havok hkGskBaseAgent / Gskf collision
// agents.  Large entry points are approximated (see partial.txt).
#include "types.h"

#define VFN(p, slot) (((void**)*(void**)p)[(slot)/4])

struct hkCollisionInput;

// hkCdBody: shape*, motion*, transform*, radius/translation at +0xc (retail).
class hkCdBody { public:
    void* mShape;                 // +0x00
    void* mMotion;                // +0x04
    void* mTransform;             // +0x08
    float mField0c;               // +0x0c
};

struct __declspec(align(16)) hkVector4 { float x, y, z, w; };
struct __declspec(align(16)) hkTransform {
    float m[16];
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // 0x010810f0
};
class hkGsk {
public:
    int getClosestFeature(const void* a, const void* b, const hkTransform& xf, hkVector4& out); // 0x0110e510
    int m_dimA;                    // +0x00
    int m_dimB;                    // +0x04
    int m_maxDimA;                 // +0x08
    int m_maxDimB;                 // +0x0c
    bool m_doNotHandlePenetration; // +0x10
    int m_featureChange;           // +0x14
};

// 12-byte shape cache consumed by the GSK (written by 0x01113e90 / 0x01113fd0):
// two feature indices, two "unset" words, then the vertex counts / shape types.
struct hkGskCachePart {
    unsigned short m_indexA;       // +0x00
    unsigned short m_indexB;       // +0x02
    unsigned short m_unset0;       // +0x04
    unsigned short m_unset1;       // +0x06
    signed char    m_numA;         // +0x08
    signed char    m_numB;         // +0x09
    signed char    m_typeA;        // +0x0a
    signed char    m_typeB;        // +0x0b
};

struct hkCdPoint {
    hkVector4 mP;                 // +0x00
    hkVector4 mN;                 // +0x10
    const hkCdBody* mBodyA;       // +0x20
    const hkCdBody* mBodyB;       // +0x24
};

class hkCdPointCollector { public:
    virtual void v00() = 0;
    virtual void addCdPoint(const hkCdPoint& p) = 0;   // +0x04
};

class hkCdBodyPairCollector { public:
    virtual void v00() = 0;
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b) = 0; // +0x04
};

struct hkProcessCollisionInput {};
struct hkProcessCollisionOutput {};

// ---------------------------------------------------------------------------
// hkGskBaseAgent (only the offsets touched by this slice)
// ---------------------------------------------------------------------------
class hkGskBaseAgent {
public:
    void* mpVtbl;            // +0x00
    char pad04[8];           // +0x04
    hkGskCachePart mCache;   // +0x0c (cached shape info, reused by getPenetrations)
    float mField18;          // +0x18
    float mField1c;          // +0x1c
    float mField20;          // +0x20
    float mField24;          // +0x24
    float mField28;          // +0x28
    float mField2c;          // +0x2c

    void invalidateTim(hkCollisionInput& in);            // 0x010ed240
    void warpTime(float a, int b, hkCollisionInput& in);   // 0x010ed260
    static void staticGetClosestPoints(const hkCdBody& a, const hkCdBody& b,
                                       const hkCollisionInput& in, hkCdPointCollector& out); // 0x010ed430
    void getPenetrations(const hkCdBody& a, const hkCdBody& b,
                         const hkCollisionInput& in, hkCdBodyPairCollector& out); // 0x010ed840
    static void staticGetPenetrations(const hkCdBody& a, const hkCdBody& b,
                                      const hkCollisionInput& in, hkCdBodyPairCollector& out); // 0x010edaa0
    void getClosestPoints(const hkCdBody& a, const hkCdBody& b,
                          const hkCollisionInput& in, hkCdPointCollector& out); // 0x010edc50
};

// hkSimpleClosestContactCollector (vtable base + fields)
struct hkSimpleClosestContactCollector {
    virtual void addCdPoint(const hkCdPoint& p);   // +0x00 (slot 0, implicit vptr)
    float mField04;                                // +0x04
    bool mHasPoint;                                // +0x08
    char pad09[3];
    int mField0c;
    hkCdPoint mPoint;                              // +0x10 (32 bytes -> +0x2c last)
};

// ---------------------------------------------------------------------------
// external real callees
// ---------------------------------------------------------------------------
void hkTransform_setMulInverseMul(void* out, const void* a, const void* b); // 0x010810f0
// the shape-cache builders take the cache in ecx (thiscall): __fastcall + dummy edx
void __fastcall hkGskCache_init(void* self, void* edxDummy, void* shapeA, void* shapeB, const void* xf); // 0x01113e90
void __fastcall FUN_01113fd0(void* self, void* edxDummy, void* shapeA, void* shapeB, const void* xf);    // 0x01113fd0
struct hkGskQuery;
int  FUN_0110fa20(const hkGskQuery* q, void* state, hkVector4& out2, hkVector4& out1); // 0x0110fa20
void FUN_0111c2e0(void* p, int n, int a, int b, int c);                      // 0x0111c2e0
void __fastcall FUN_0110cd00(void* gskThis, void* edxDummy, void* cache);    // 0x0110cd00
// thiscall targets (first arg in ecx) - declared __fastcall so that ecx carries `this`
void __fastcall FUN_0110cde0(void* gskThis, void* edxDummy, const hkVector4& q, void* out); // 0x0110cde0
void __fastcall FUN_010814a0(void* dst, void* edxDummy, const hkTransform& xf, const hkVector4& in); // 0x010814a0
extern const char DAT_014a4ba4[];

// result of hkGsk::convertFeatureToClosestDistance (0x0110cde0)
struct hkGskClosestInfo {
    hkVector4 mPoint;      // +0x00
    hkVector4 mNormal;     // +0x10
    float     mDistance;   // +0x20
};
void hkArrayUtil_reserveExactly(void* array, int n, int elemsize);           // 0x0107f4a0
void hkThreadMemory_deallocateChunk(void* mem, void* p, int size, int cls);  // 0x0107db10
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long index, void* value);
extern unsigned long g_tls1;   // 0x016e42a8
extern unsigned long g_tls2;   // 0x016e42a4
extern unsigned long g_tlsMem; // 0x016e4174 (hkThreadMemory*)
extern const char DAT_014a530c[];
extern const char DAT_014a4bb8[];
void FUN_010ec700(void* self, const hkCdBody& a, const hkCdBody& b,
                  const hkProcessCollisionInput& in, hkProcessCollisionOutput& out); // 0x010ec700

// ---- monitor stream timers (TLS 0x016e42a4 = write pointer, 0x016e42a8 = end) -------------
typedef unsigned int hkUint32;
__forceinline hkUint32 hk_rdtsc() { hkUint32 t_; __asm { rdtsc } __asm { mov t_, eax } return t_; }
struct hkMonitorEnd { const char* m_command; hkUint32 m_time0; hkUint32 m_time1; };
extern const char DAT_014a5350[];
extern const char DAT_0149cc34[];
extern const char DAT_014a5368[];
extern const char DAT_014a5364[];
extern const char DAT_014a5358[];
extern const char DAT_0143cd94[];

// scoped monitor block: {command, time0, time1, endCommand}
struct hkMonitorBlock { const char* m_command; hkUint32 m_time0; hkUint32 m_time1; const char* m_endCommand; };

#define HK_TIMER_BEGIN2(cmd, endcmd) do { \
    if (TlsGetValue(g_tls2) < TlsGetValue(g_tls1)) { \
        hkMonitorBlock* c_ = (hkMonitorBlock*)TlsGetValue(g_tls2); \
        c_->m_command = cmd; c_->m_endCommand = endcmd; c_->m_time0 = hk_rdtsc(); \
        TlsSetValue(g_tls2, c_ + 1); } } while (0)

#define HK_TIMER_BEGIN1(cmd) do { \
    if (TlsGetValue(g_tls2) < TlsGetValue(g_tls1)) { \
        hkMonitorEnd* c_ = (hkMonitorEnd*)TlsGetValue(g_tls2); \
        c_->m_command = cmd; c_->m_time0 = hk_rdtsc(); \
        TlsSetValue(g_tls2, c_ + 1); } } while (0)
#define HK_TIMER_END1() do { \
    if (TlsGetValue(g_tls2) < TlsGetValue(g_tls1)) { \
        hkMonitorEnd* c_ = (hkMonitorEnd*)TlsGetValue(g_tls2); \
        c_->m_command = DAT_0149cc34; c_->m_time0 = hk_rdtsc(); \
        TlsSetValue(g_tls2, c_ + 1); } } while (0)
#define HK_TIMER_END1C(cmd) do { \
    if (TlsGetValue(g_tls2) < TlsGetValue(g_tls1)) { \
        hkMonitorEnd* c_ = (hkMonitorEnd*)TlsGetValue(g_tls2); \
        c_->m_command = cmd; c_->m_time0 = hk_rdtsc(); \
        TlsSetValue(g_tls2, c_ + 1); } } while (0)

// query record handed to hkGsk::closestPoint (0x0110fa20)
struct hkGskQuery {
    const hkTransform* mXf;        // +0x00  relative transform
    const void*        mXfA;       // +0x04
    const void*        mShapeA;    // +0x08
    const void*        mShapeB;    // +0x0c
    const void*        mXfIn;      // +0x10
};

// ---------------------------------------------------------------------------
// small members
// ---------------------------------------------------------------------------

// @ 0x010ed230  (helper: Release(1) if non-null; ecx = object)
struct IReleasable {
    virtual void Release1(int) = 0;
};
void __fastcall FUN_010ed230(IReleasable* p)
{
    if (p != 0)
        p->Release1(1);
}

// @ 0x010ed240
void hkGskBaseAgent::invalidateTim(hkCollisionInput&)
{
    *(int*)&mField2c = 0;
    *(int*)&mField28 = 0;
    *(int*)&mField24 = 0;
    *(int*)&mField20 = 0;
    *(int*)&mField18 = (int)0xbf800000;
}

// @ 0x010ed260
void hkGskBaseAgent::warpTime(float a, int b, hkCollisionInput&)
{
    if (a == mField18) {
        *(int*)&mField18 = b;
        return;
    }
    *(int*)&mField18 = (int)0xbf800000;
    *(int*)&mField2c = 0;
    *(int*)&mField28 = 0;
    *(int*)&mField24 = 0;
    *(int*)&mField20 = 0;
}

// @ 0x010eddd0
void hkSimpleClosestContactCollector::addCdPoint(const hkCdPoint& p)
{
    if (!mHasPoint || p.mN.w < *(float*)((char*)this + 0x2c)) {
        mHasPoint = true;
        *(float*)((char*)this + 0x10) = p.mP.x;
        *(float*)((char*)this + 0x14) = p.mP.y;
        *(float*)((char*)this + 0x18) = p.mP.z;
        *(float*)((char*)this + 0x1c) = p.mP.w;
        *(float*)((char*)this + 0x20) = p.mN.x;
        *(float*)((char*)this + 0x24) = p.mN.y;
        *(float*)((char*)this + 0x28) = p.mN.z;
        *(float*)((char*)this + 0x2c) = p.mN.w;
        *(float*)((char*)this + 4) = p.mN.w;
    }
}

// shape interface: slot 2 of the vtable (+0x08) is the shape type id
struct hkShape {
    virtual void v00() = 0;
    virtual void v04() = 0;
    virtual int getShapeType() = 0;      // +0x08
};

struct hkGskBuilder { hkGskBuilder* build(hkCdBody* a, hkCdBody* b, int flags); };

// @ 0x010ed2a0  hkGskBuilder::build (hkGskCache builder using two bodies)
hkGskBuilder* hkGskBuilder::build(hkCdBody* a, hkCdBody* b, int flags)
{
    char* p = (char*)this;
    *(int*)(p + 8) = flags;
    *(unsigned short*)(p + 6) = 1;
    *(void**)p = (void*)0x14a531c;
    void* shapeA = a->mShape;
    void* shapeB = b->mShape;
    hkTransform xf;
    xf.setMulInverseMul(*(const hkTransform*)a->mTransform, *(const hkTransform*)b->mTransform);
    void* cache = p + 0xc;
    int k = ((hkShape*)shapeB)->getShapeType();
    if (k == 6)
        FUN_01113fd0(cache, 0, shapeA, shapeB, &xf);
    else
        hkGskCache_init(cache, 0, shapeA, shapeB, &xf);
    *(int*)(p + 0x2c) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x20) = 0;
    *(int*)(p + 0x2c) = -1082130432;
    *(int*)(p + 0x18) = -1082130432;
    // depth = min of the two bodies' depth fields, taken from the last node of the
    // +0x0c parent chain (next at +0x0c, depth float at +0x20)
    void* n1 = (void*)a;
    while (*(void**)((char*)n1 + 0xc) != 0)
        n1 = *(void**)((char*)n1 + 0xc);
    void* n2 = (void*)b;
    while (*(void**)((char*)n2 + 0xc) != 0)
        n2 = *(void**)((char*)n2 + 0xc);
    float depthA = *(float*)((char*)n1 + 0x20);
    float depthB = *(float*)((char*)n2 + 0x20);
    *(float*)(p + 0x1c) = depthA > depthB ? depthB : depthA;
    (void)shapeA;
    return this;
}

// @ 0x010ed380  (point/plane query: closest point in a's frame, radius pushed into w)
void FUN_010ed380(const hkCdBody* a, const hkCdBody* b, const void*, hkGsk* gsk, hkVector4* out)
{
    hkTransform xf;
    xf.setMulInverseMul(*(const hkTransform*)a->mTransform, *(const hkTransform*)b->mTransform);
    hkVector4 p;
    gsk->getClosestFeature(a->mShape, b->mShape, xf, p);
    const hkTransform* xa = (const hkTransform*)a->mTransform;
    out->x = p.z * xa->m[8] + p.y * xa->m[4] + p.x * xa->m[0];
    out->y = p.z * xa->m[9] + p.y * xa->m[5] + p.x * xa->m[1];
    out->z = p.z * xa->m[10] + p.y * xa->m[6] + p.x * xa->m[2];
    out->w = 0.0f;                       // dead store: the original keeps it (0x010ed413)
    // the depth test reads the shapes' own +0xc field, not the bodies' one
    out->w = p.w - *(const float*)((const char*)a->mShape + 0xc)
                 - *(const float*)((const char*)b->mShape + 0xc);
}

// @ 0x010edaa0
void hkGskBaseAgent::staticGetPenetrations(const hkCdBody& a, const hkCdBody& b,
                                           const hkCollisionInput&, hkCdBodyPairCollector& out)
{
    HK_TIMER_BEGIN1(DAT_014a5350);
    hkTransform xf;
    xf.setMulInverseMul(*(const hkTransform*)a.mTransform, *(const hkTransform*)b.mTransform);
    void* shapeA = a.mShape;
    void* shapeB = b.mShape;
    hkGskCachePart cache;
    if (((int(__thiscall*)(void*))VFN(shapeB, 8))(shapeB) == 6)
        FUN_01113fd0(&cache, 0, shapeA, shapeB, &xf);
    else
        hkGskCache_init(&cache, 0, shapeA, shapeB, &xf);

    hkGsk gsk;
    gsk.m_dimA = cache.m_numA;
    gsk.m_dimB = cache.m_numB;
    gsk.m_maxDimA = cache.m_typeA;
    gsk.m_maxDimB = cache.m_typeB;
    gsk.m_doNotHandlePenetration = true;
    gsk.m_featureChange = 0;

    hkVector4 bufA[12];              // 0xc0 bytes, 16-byte aligned (P+0x90)
    hkVector4 bufB[12];              // 0xc0 bytes, 16-byte aligned (P+0x150)
    ((void(__thiscall*)(void*, void*, int, void*))VFN(shapeA, 0x28))(shapeA, &cache, gsk.m_dimA, bufA);
    ((void(__thiscall*)(void*, void*, int, void*))VFN(shapeB, 0x28))(
        shapeB, (char*)&cache + 2 * gsk.m_dimA, gsk.m_dimB, bufB);

    int ret;
    hkVector4 p;
    ret = gsk.getClosestFeature(shapeA, shapeB, xf, p);
    HK_TIMER_END1();
    float depth = p.w - *(const float*)((const char*)a.mShape + 0xc)
                     - *(const float*)((const char*)b.mShape + 0xc);
    if (ret != 0 || !(depth > 0.0f))
        out.addCdBodyPair(a, b);
}

// @ 0x010edc50
void hkGskBaseAgent::getClosestPoints(const hkCdBody& a, const hkCdBody& b,
                                      const hkCollisionInput& in, hkCdPointCollector& out)
{
    HK_TIMER_BEGIN1(DAT_014a5350);
    hkTransform xf;
    xf.setMulInverseMul(*(const hkTransform*)a.mTransform, *(const hkTransform*)b.mTransform);
    hkGskQuery q;
    q.mXf = &xf;
    q.mXfA = a.mTransform;
    q.mShapeA = a.mShape;
    q.mShapeB = b.mShape;
    q.mXfIn = *(const void**)((const char*)&in + 8);
    hkVector4 n, p;
    if (FUN_0110fa20(&q, (char*)this + 0xc, n, p) == 0) {
        hkCdPoint pt;
        pt.mP = p;
        pt.mN = n;
        pt.mBodyA = &a;
        pt.mBodyB = &b;
        out.addCdPoint(pt);
    }
    HK_TIMER_END1();
}

// @ 0x010ed430
void hkGskBaseAgent::staticGetClosestPoints(const hkCdBody& a, const hkCdBody& b,
                                            const hkCollisionInput& in, hkCdPointCollector& out)
{
    HK_TIMER_BEGIN1(DAT_014a5350);
    hkTransform xf;
    xf.setMulInverseMul(*(const hkTransform*)a.mTransform, *(const hkTransform*)b.mTransform);
    hkGskCachePart cache;
    if (((int(__thiscall*)(void*))VFN(b.mShape, 8))(b.mShape) == 6)
        FUN_01113fd0(&cache, 0, a.mShape, b.mShape, &xf);
    else
        hkGskCache_init(&cache, 0, a.mShape, b.mShape, &xf);

    HK_TIMER_BEGIN1(DAT_014a4ba4);
    hkGsk gsk;
    gsk.m_dimA = cache.m_numA;
    gsk.m_dimB = cache.m_numB;
    gsk.m_maxDimA = cache.m_typeA;
    gsk.m_maxDimB = cache.m_typeB;
    gsk.m_doNotHandlePenetration = false;
    gsk.m_featureChange = 0;

    hkVector4 bufA[12];
    hkVector4 bufB[12];
    ((void(__thiscall*)(void*, void*, int, void*))VFN(a.mShape, 0x28))(a.mShape, &cache, gsk.m_dimA, bufA);
    ((void(__thiscall*)(void*, void*, int, void*))VFN(b.mShape, 0x28))(
        b.mShape, (char*)&cache + 2 * gsk.m_dimA, gsk.m_dimB, bufB);

    hkVector4 q;
    if (gsk.getClosestFeature(a.mShape, b.mShape, xf, q) == 0) {
        hkGskClosestInfo info;
        FUN_0110cde0(&gsk, 0, q, &info);

        hkVector4 pa;                    // closest point in a's frame
        FUN_010814a0(&pa, 0, *(const hkTransform*)a.mTransform, info.mPoint);

        float rA = *(const float*)((const char*)a.mShape + 0xc);
        float rB = *(const float*)((const char*)b.mShape + 0xc);
        float depth = info.mDistance - rA - rB;
        float tol = *(const float*)((const char*)&in + 8);
        if (!(depth > tol)) {
            const float* p = (const float*)&info.mPoint;
            float nrA = -rA;
            info.mNormal.x = p[0] * nrA + info.mNormal.x;
            info.mNormal.y = p[1] * nrA + info.mNormal.y;
            info.mNormal.z = p[2] * nrA + info.mNormal.z;
            info.mNormal.w = p[3] * nrA + info.mNormal.w;

            float nd = -depth;
            float X = p[0] * nd + info.mNormal.x;
            float Y = p[1] * nd + info.mNormal.y;
            float Z = p[2] * nd + info.mNormal.z;
            const float* m = xf.m;
            X -= m[12];
            Y -= m[13];
            Z -= m[14];

            hkVector4 n;                 // separation in b's frame
            n.x = (m[1] * Y + m[2] * Z) + m[0] * X;
            n.y = (m[5] * Y + m[6] * Z) + m[4] * X;
            n.z = (m[9] * Y + m[10] * Z) + m[8] * X;

            const float* mb = (const float*)((const char*)b.mTransform);
            hkCdPoint pt;
            pt.mP.x = (mb[8] * n.z + mb[4] * n.y) + mb[0] * n.x + mb[12];
            pt.mP.y = (mb[9] * n.z + mb[5] * n.y) + mb[1] * n.x + mb[13];
            pt.mP.z = (mb[10] * n.z + mb[6] * n.y) + mb[2] * n.x + mb[14];
            pt.mP.w = 0.0f;
            pt.mN.x = pa.x;
            pt.mN.y = pa.y;
            pt.mN.z = pa.z;
            pt.mN.w = depth;
            pt.mBodyA = &a;
            pt.mBodyB = &b;
            out.addCdPoint(pt);
        }
    }
    HK_TIMER_END1();
}

// @ 0x010ed840
void hkGskBaseAgent::getPenetrations(const hkCdBody& a, const hkCdBody& b,
                                     const hkCollisionInput& in, hkCdBodyPairCollector& out)
{
    HK_TIMER_BEGIN2(DAT_014a5368, DAT_014a5364);
    HK_TIMER_BEGIN1(DAT_014a5358);
    hkTransform xf;
    xf.setMulInverseMul(*(const hkTransform*)a.mTransform, *(const hkTransform*)b.mTransform);

    hkGskCachePart* cache = &mCache;
    hkGsk gsk;
    gsk.m_dimA = cache->m_numA;
    gsk.m_dimB = cache->m_numB;
    gsk.m_maxDimA = cache->m_typeA;
    gsk.m_maxDimB = cache->m_typeB;
    gsk.m_doNotHandlePenetration = true;
    gsk.m_featureChange = 0;

    hkVector4 bufA[12];
    hkVector4 bufB[12];
    ((void(__thiscall*)(void*, void*, int, void*))VFN(a.mShape, 0x28))(a.mShape, cache, gsk.m_dimA, bufA);
    ((void(__thiscall*)(void*, void*, int, void*))VFN(b.mShape, 0x28))(
        b.mShape, (char*)cache + 2 * gsk.m_dimA, gsk.m_dimB, bufB);

    hkVector4 p;
    int ret = gsk.getClosestFeature(a.mShape, b.mShape, xf, p);
    if (gsk.m_featureChange != 0)
        FUN_0110cd00(&gsk, 0, cache);

    hkVector4* dst = (hkVector4*)((char*)this + 0x20);
    const hkTransform* xa = (const hkTransform*)a.mTransform;
    if (ret == 0) {
        float depth = p.w - *(const float*)((const char*)a.mShape + 0xc)
                         - *(const float*)((const char*)b.mShape + 0xc);
        dst->x = p.z * xa->m[8] + p.y * xa->m[4] + p.x * xa->m[0];
        dst->y = p.z * xa->m[9] + p.y * xa->m[5] + p.x * xa->m[1];
        dst->z = p.z * xa->m[10] + p.y * xa->m[6] + p.x * xa->m[2];
        dst->w = 0.0f;
        dst->w = depth;
        if (!(depth > 0.0f))
            out.addCdBodyPair(a, b);
    } else {
        dst->w = 0; dst->z = 0; dst->y = 0; dst->x = 0;
        out.addCdBodyPair(a, b);
    }
    HK_TIMER_END1C(DAT_0143cd94);
}

// @ 0x010ed000  hkGskfAgent::processCollision
void __fastcall FUN_010ed000(void* self, void* edxDummy, const hkCdBody& a, const hkCdBody& b,
                             const hkProcessCollisionInput& in, hkProcessCollisionOutput& out)
{
    hkGskBaseAgent* agent = (hkGskBaseAgent*)self;
    (void)edxDummy;
    HK_TIMER_BEGIN2(DAT_014a530c, DAT_014a4bb8);
    const float* ma = (const float*)a.mTransform;     // a's motion state (swept transform)
    const float* mb = (const float*)b.mTransform;
    const float* pi = (const float*)&in;
    float T = pi[6];                                  // +0x18  time step
    if (pi[4] != agent->mField18) {                   // +0x10 vs cached step +0x18
        HK_TIMER_END1C(DAT_0143cd94);
        return;
    }
    float dx = ma[0x40 / 4] - ma[0x50 / 4];
    float dy = ma[0x44 / 4] - ma[0x54 / 4];
    float dz = ma[0x48 / 4] - ma[0x58 / 4];
    float bx = mb[0x50 / 4] - mb[0x40 / 4];
    float by = mb[0x54 / 4] - mb[0x44 / 4];
    float bz = mb[0x58 / 4] - mb[0x48 / 4];
    float sA = T * ma[0x5c / 4];
    float sB = T * mb[0x5c / 4];
    float cst = ma[0xa0 / 4] * ma[0x9c / 4] * sA + mb[0xa0 / 4] * mb[0x9c / 4] * sB;
    // x is rounded through esp+0x30 (weighted by mField20), y survives extended (mField24)
    float X = bx * sB + dx * sA;
    float sep = (bz * sB + dz * sA) * agent->mField28 + (by * sB + dy * sA) * agent->mField24;
    sep = sep + X * agent->mField20;
    sep = sep + cst;
    if (agent->mField2c > pi[2]) {                    // in+8: latest valid toi
        float toi = agent->mField2c - sep;
        agent->mField2c = toi;
        if (toi > pi[2]) {
            agent->mField18 = pi[5];                  // in+0x14
            FUN_010ec700(agent, a, b, in, out);
        }
    }
    HK_TIMER_END1C(DAT_0143cd94);
}

// @ 0x010ede30  (__stdcall) hkArray<hkVector4> copy helper: when the source is not a
// 16-byte-aligned block of stride-16 elements the elements are staged through a
// temporary hkArray (12 bytes copied per element) that is released afterwards.
struct hkArrayHead { void* m_data; int m_size; int mCapacityAndFlags; };

void __stdcall FUN_010ede30(hkArrayHead* a, int x, int y, int z)
{
    if (a->mCapacityAndFlags == 0x10 && (((unsigned)a->m_data) & 0xf) == 0) {
        FUN_0111c2e0(a->m_data, a->m_size, x, y, z);
        return;
    }
    int n = a->m_size;
    int stride = n / 16 * 4;
    hkArrayHead tmp;
    tmp.m_data = 0;
    tmp.m_size = 0;
    tmp.mCapacityAndFlags = (int)0x80000000;
    for (int i = 0; i < n; ++i) {
        int cap = tmp.mCapacityAndFlags & 0x3fffffff;
        if (cap < i + 1) {
            int newCap = cap * 2;
            if (i + 1 >= newCap)
                newCap = i + 1;
            hkArrayUtil_reserveExactly(&tmp, newCap, 0x10);
        }
        tmp.m_size = i + 1;
        const char* src = (const char*)a->m_data + i * stride;
        char* dst = (char*)tmp.m_data + i * 16;
        *(int*)(dst + 0) = *(const int*)(src + 0);
        *(int*)(dst + 4) = *(const int*)(src + 4);
        *(int*)(dst + 8) = *(const int*)(src + 8);
    }
    FUN_0111c2e0(tmp.m_data, a->m_size, x, y, z);
    if (tmp.mCapacityAndFlags >= 0)
        hkThreadMemory_deallocateChunk((void*)TlsGetValue(g_tlsMem), tmp.m_data,
                                       (tmp.mCapacityAndFlags & 0x3fffffff) * 16, 0x14);
}
