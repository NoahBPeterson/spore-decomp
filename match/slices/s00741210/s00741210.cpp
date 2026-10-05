// Slice s00741210 (0x00741210-0x00741aa0): SP::cModelInstance geometry construction.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"
#include <intrin.h>

// External callees (masked relocations).
extern "C" void FUN_007403c0(void* p);   // 0x7403c0
extern "C" void FUN_007418f0(void* a, void* b);   // 0x7418f0

struct ResBase {
    virtual void v0();
    virtual void v1();
};

struct cMI_Construct {
    char    pad0[8];
    void*   mBegin8;                  // +0x8
    void*   mEndc;                    // +0xc
    char    pad10[0xc4 - 0x10];
    ResBase* mResource;               // +0xc4

    void AddGeometryFromArena(ResBase* p);          // 0x741210
    bool ConstructFromArenaResource(ResBase* p);    // 0x741a40
    void Sub3c0(ResBase* p);                        // 0x7403c0
};

// ---------------------------------------------------------------------------
// @ 0x00741a40  SP::cModelInstance::ConstructFromArenaResource
// ---------------------------------------------------------------------------
bool cMI_Construct::ConstructFromArenaResource(ResBase* p)
{
    ResBase* old = mResource;
    if (p != old) {
        if (p)
            p->v0();
        mResource = p;
        if (old)
            old->v1();
    }
    AddGeometryFromArena(p);
    if (mBegin8 == mEndc)
        return false;
    Sub3c0(p);
    return true;
}

// ===========================================================================
// Remaining geometry helpers (large; reconstruction in progress).
// ===========================================================================
struct cMI_Geo {
    char pad[0x154];
    void AddGeometryFromArena(int a2);          // 0x741210
    void Sub18f0(void* a2, void* a3);           // 0x7418f0
    void Sub1aa0(void* a2, void* a3);           // 0x741aa0
};

// ---------------------------------------------------------------------------
// @ 0x00741aa0  eastl::vector<8-byte refcounted>::insert
// ---------------------------------------------------------------------------
struct RefCounted {
    virtual void v0();
    virtual void v1();
    volatile int mnRefCount;         // +0x4
};

struct RefPair8 {
    int         value;               // +0x0
    RefCounted* p;                   // +0x4
};

struct Vec8 {
    RefPair8* mpBegin;               // +0x0
    RefPair8* mpEnd;                 // +0x4
    RefPair8* mpCapacity;            // +0x8
    RefPair8* insert(RefPair8* pos, const RefPair8* v);
    void DoInsertValue(RefPair8* pos, const RefPair8* v);   // 0x7418f0
};

RefPair8* Vec8::insert(RefPair8* pos, const RefPair8* v)
{
    RefPair8* p = mpEnd;
    int idx = (int)(pos - mpBegin);
    if (pos == p && p != mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            p->value = v->value;
            RefCounted* r = v->p;
            p->p = r;
            if (r) {
                _InterlockedIncrement((volatile long*)&r->mnRefCount);
            }
        }
    } else {
        DoInsertValue(pos, v);
    }
    return mpBegin + idx;
}

// @ 0x00741210
void cMI_Geo::AddGeometryFromArena(int a2) { (void)a2; }

// @ 0x007418f0
void cMI_Geo::Sub18f0(void* a2, void* a3) { (void)a2; (void)a3; }

// @ 0x00741aa0
void cMI_Geo::Sub1aa0(void* a2, void* a3) { (void)a2; (void)a3; }

// ---------------------------------------------------------------------------
// @ 0x00741710  SP::cLoadQueue<...>::StallUntilLoaded  (partial)
// ---------------------------------------------------------------------------
void __cdecl StallUntilLoaded(void* self, void* entries)
{
    (void)self; (void)entries;
}
