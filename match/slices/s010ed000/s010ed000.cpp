// Decompiled source for bfs3 slice 43: Havok hkGskBaseAgent / Gskf collision
// agents.  Large entry points are approximated (see partial.txt).
#include "types.h"

#define VFN(p, slot) (((void**)*(void**)p)[(slot)/4])

struct hkCollisionInput;

// hkCdBody: shape*, motion*, transform*, radius/translation at +0xc (retail).
struct hkCdBody {
    void* mShape;                 // +0x00
    void* mMotion;                // +0x04
    void* mTransform;             // +0x08
    float mField0c;               // +0x0c
};

struct hkCdPoint {
    int m[8];                     // +0x00 .. +0x1c (raw dwords)
};

struct hkCdPointCollector {
    virtual void v00() = 0;
    virtual void addCdPoint(const hkCdPoint& p) = 0;   // +0x04
};

struct hkCdBodyPairCollector {
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
    char pad04[0x14];
    float mField18;          // +0x18
    float mField1c;          // +0x1c
    int mField20;            // +0x20
    int mField24;            // +0x24
    int mField28;            // +0x28
    int mField2c;            // +0x2c

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
void hkGskCache_init(void* self, void* shapeA, void* shapeB, const void* xf); // 0x01113e90
void FUN_01113fd0(void* a, void* b, const void* xf);                          // 0x01113fd0
void FUN_0110e510(void* a, void* b, const void* cache, void* out);            // 0x0110e510
int  FUN_0110fa20(void* cache, void* xf, void* out, void* out2);             // 0x0110fa20
void FUN_0111c2e0(void* p, int n, int a, int b, int c);                      // 0x0111c2e0
void hkArrayUtil_reserveExactly(void* array, int n, int elemsize);           // 0x0107f4a0
void hkThreadMemory_deallocateChunk(void* mem, void* p, int size, int cls);  // 0x0107db10
void* TlsGetValue(unsigned long);
void  TlsSetValue(unsigned long, void*);
extern unsigned long g_tls1;   // 0x016e42a8
extern unsigned long g_tls2;   // 0x016e42a4

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
    mField2c = 0;
    mField28 = 0;
    mField24 = 0;
    mField20 = 0;
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
    mField2c = 0;
    mField28 = 0;
    mField24 = 0;
    mField20 = 0;
}

// @ 0x010eddd0
void hkSimpleClosestContactCollector::addCdPoint(const hkCdPoint& p)
{
    if (!mHasPoint || *(float*)&p.m[7] < *(float*)((char*)this + 0x2c)) {
        mHasPoint = true;
        *(int*)((char*)this + 0x10) = p.m[0];
        *(int*)((char*)this + 0x14) = p.m[1];
        *(int*)((char*)this + 0x18) = p.m[2];
        *(int*)((char*)this + 0x1c) = p.m[3];
        *(int*)((char*)this + 0x20) = p.m[4];
        *(int*)((char*)this + 0x24) = p.m[5];
        *(int*)((char*)this + 0x28) = p.m[6];
        *(int*)((char*)this + 0x2c) = p.m[7];
        *(int*)((char*)this + 4) = p.m[7];
    }
}

// @ 0x010ed2a0  (hkGskCache builder using two bodies)
void FUN_010ed2a0(void* self, hkCdBody* a, hkCdBody* b, int flags)
{
    char* p = (char*)self;
    *(int*)(p + 8) = flags;
    *(unsigned short*)(p + 6) = 1;
    *(void**)p = (void*)0x14a531c;
    void* xa = a->mTransform;
    void* xb = b->mTransform;
    void* shapeA = a->mShape;
    void* shapeB = b->mShape;
    void* cache = p + 0xc;
    hkTransform_setMulInverseMul(cache, xb, xa);
    int k = ((int(__thiscall*)(void*))VFN(shapeB, 8))(shapeB);
    if (k == 6)
        FUN_01113fd0(shapeA, shapeB, cache);
    else
        hkGskCache_init(cache, shapeA, shapeB, 0);
    *(int*)(p + 0x2c) = -1082130432;  // 0xbf800000
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x20) = 0;
    *(int*)(p + 0x2c) = -1082130432;
    *(int*)(p + 0x18) = -1082130432;
    // depth = min of the two bodies' depth fields
    void* n1 = (char*)a + 0xc;
    while (n1 != 0) n1 = *(void**)((char*)n1 + 0xc);
    void* n2 = (char*)b + 0xc;
    while (n2 != 0) n2 = *(void**)((char*)n2 + 0xc);
    float d = *(float*)((char*)n2 + 0x20);
    if (*(float*)((char*)n1 + 0x20) < d)
        d = *(float*)((char*)n1 + 0x20);
    *(float*)(p + 0x1c) = d;
    (void)shapeA;
}

// @ 0x010ed380  (point/plane query)
void FUN_010ed380(void* a, void* b, int, int, float* out)
{
    char* pa = (char*)a;
    char* pb = (char*)b;
    void* shapeA = *(void**)pa;
    void* shapeB = *(void**)pb;
    hkTransform_setMulInverseMul(0, pb + 8, pa + 8);
    FUN_0110e510(shapeA, shapeB, 0, 0);
    float* xf = (float*)*(void**)(pa + 8);
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 0.0f;
    (void)xf;
}

// @ 0x010edaa0
void hkGskBaseAgent::staticGetPenetrations(const hkCdBody& a, const hkCdBody& b,
                                           const hkCollisionInput&, hkCdBodyPairCollector& out)
{
    const hkCdBody* pa = &a;
    const hkCdBody* pb = &b;
    (void)pa; (void)pb; (void)out;
}

// @ 0x010edc50
void hkGskBaseAgent::getClosestPoints(const hkCdBody& a, const hkCdBody& b,
                                      const hkCollisionInput&, hkCdPointCollector& out)
{
    (void)a; (void)b; (void)out;
}

// @ 0x010ed430
void hkGskBaseAgent::staticGetClosestPoints(const hkCdBody& a, const hkCdBody& b,
                                            const hkCollisionInput&, hkCdPointCollector& out)
{
    (void)a; (void)b; (void)out;
}

// @ 0x010ed840
void hkGskBaseAgent::getPenetrations(const hkCdBody& a, const hkCdBody& b,
                                     const hkCollisionInput& in, hkCdBodyPairCollector& out)
{
    staticGetPenetrations(a, b, in, out);
}

// @ 0x010ed000  hkGskfAgent::processCollision
void FUN_010ed000(void* self, const hkCdBody& a, const hkCdBody& b,
                  const hkProcessCollisionInput& in, hkProcessCollisionOutput& out)
{
    (void)self; (void)a; (void)b; (void)in; (void)out;
}

// @ 0x010ede30
void FUN_010ede30(float* array, int n, int a, int b, int c)
{
    (void)array; (void)n; (void)a; (void)b; (void)c;
}
