// Slice s00fc3000 -- SP::cJetStreamMap (EA::Swarm::cMapBase derived) setter/refresh + derived dtor.
//   00fc3000  cJetStreamMap::SetValues(JetStream)  -- sets mMapId and mMap (mMaps[5])
//   00fc30f0  cJetStreamMap::~cJetStreamMap (vtable-restoring derived dtor)
//   00fc3150  cJetStreamMap::SetValues(PressureMap) -- sets mMapId and mMap (mMaps[4])
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (see manifest).
#include "types.h"
#include <intrin.h>

// ---- refcounted object base (matches 0x00572680 RefCountedPtr::operator= shape) -------------
struct RefCounted {
    virtual ~RefCounted();                 // +0x00 vtable
    int mnRefCount;                        // +0x04
    inline void AddRef() { ++mnRefCount; }
    inline void Release() {
        int n = mnRefCount - 1;
        mnRefCount = mnRefCount - 1;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};

struct RefCountedPtr {
    RefCounted* mp;
    RefCountedPtr& operator=(RefCounted* p);
};

// ---- EA::Swarm layout (retail PDB sizes) ----------------------------------------------------
struct cIMap {                             // size 0x4
    void** vftable;
};
struct RefCountTemplate {                  // size 0x8 (int refcount)
    void** vftable;
    int mRefCount;
};
struct cMapBase : cIMap, RefCountTemplate {  // size 0xc
};
struct cBoundingBox {                      // +0xc..+0x27, 0x1c bytes
    uint32_t words[7];
};

struct cTerrainMapBase : RefCounted {};    // EA::RefCountTemplate<int> compatible

struct cTerrainMapSet : RefCounted {       // size 0x5c
    RefCounted* mMaps[11];                 // +0x8  (AutoRefCount<cTerrainMapBase>[11])
    char pad34[0x5c - 0x34];
};

struct cTerrainMapVector3;                 // AutoRefCount<SP::cTerrainMapVector3>

struct cJetStreamMap : cMapBase {          // size 0x38
    cBoundingBox mBoundingBox;             // +0x0c
    uint32_t mMapIdLo;                     // +0x28
    uint32_t mMapIdHi;                     // +0x2c
    RefCounted* mTerrainMapSet;            // +0x30 (AutoRefCount<SP::cTerrainMapSet>)
    RefCounted* mMap;                      // +0x34

    bool SetValues(RefCounted* p, uint32_t keyLo, uint32_t keyHi);   // 0xfc3000
    bool SetValuesPressure(RefCounted* p, uint32_t keyLo, uint32_t keyHi); // 0xfc3150
    ~cJetStreamMap();                                                // 0xfc30f0
};

// Globals holding the well-known keys (two dwords each).
extern uint32_t gKeyJetA;                   // 0x015b16e8
extern uint32_t gKeyJetB;                   // 0x015b16ec
extern uint32_t gKeyPresA;                  // 0x015b16f0
extern uint32_t gKeyPresB;                  // 0x015b16f4
extern uint32_t gKeyMapA;                   // 0x015b16d8
extern uint32_t gKeyMapB;                   // 0x015b16dc

// Helper that assigns an AutoRefCount member from a raw pointer (inlined in the originals,
// out-of-line at 0x00572680 as RefCountedPtr::operator=). Same shape.
static __forceinline void AssignRef(RefCounted*& slot, RefCounted* p)
{
    if (p != slot) {
        RefCounted* const old = slot;
        if (p)
            p->AddRef();
        slot = p;
        if (old)
            old->Release();
    }
}

// out-of-line refcount assignment (the original's RefCountedPtr::operator= at 0x00572680;
// FUN_00fc3000's pressure arm calls it instead of inlining, due to the inliner's budget)
static void AssignRefOutOfLine(RefCounted*& slot, RefCounted* p);

// @ 0x00fc3000
bool cJetStreamMap::SetValues(RefCounted* p, uint32_t keyLo, uint32_t keyHi)
{
    AssignRef(mTerrainMapSet, (cTerrainMapSet*)p);
    mMapIdLo = keyLo;
    mMapIdHi = keyHi;
    if (keyLo == gKeyJetA && keyHi == gKeyJetB) {
        RefCounted* sub = ((cTerrainMapSet*)mTerrainMapSet)->mMaps[5];
        AssignRef(mMap, sub);
    } else if (keyLo == gKeyPresA && keyHi == gKeyPresB) {
        RefCounted* sub = ((cTerrainMapSet*)mTerrainMapSet)->mMaps[6];
        AssignRefOutOfLine(mMap, sub);
    } else {
        if (mMap) {
            RefCounted* old = mMap;
            mMap = 0;
            old->Release();
        }
    }
    return true;
}

void AssignRefOutOfLine(RefCounted*& slot, RefCounted* p)
{
    if (p != slot) {
        RefCounted* const old = slot;
        if (p)
            p->AddRef();
        slot = p;
        if (old)
            old->Release();
    }
}

// @ 0x00fc3150
bool cJetStreamMap::SetValuesPressure(RefCounted* p, uint32_t keyLo, uint32_t keyHi)
{
    AssignRef(mTerrainMapSet, (cTerrainMapSet*)p);
    mMapIdLo = keyLo;
    mMapIdHi = keyHi;
    if (keyLo == gKeyMapA && keyHi == gKeyMapB) {
        RefCounted* sub = ((cTerrainMapSet*)mTerrainMapSet)->mMaps[4];
        AssignRef(mMap, sub);
    } else {
        if (mMap) {
            RefCounted* old = mMap;
            mMap = 0;
            old->Release();
        }
    }
    return true;
}

// @ 0x00fc30f0
cJetStreamMap::~cJetStreamMap()
{
    // restore the two base vtables first (the original stores them before touching the members)
    *(void***)this = (void**)0x014915c4;                        // cIMap vftable
    *((void***)this + 1) = (void**)0x014915c0;                  // RefCountTemplate vftable
    _ReadWriteBarrier();
    if (mMap) {
        RefCounted* p = mMap;
        p->Release();
    }
    if (mTerrainMapSet) {
        RefCounted* p = mTerrainMapSet;
        p->Release();
    }
    *((void***)this + 1) = (void**)0x013ef094;                  // ??_7GmeRefCount@@6B@
}
