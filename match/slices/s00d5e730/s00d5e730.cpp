// Slice s00d5e730: Simulator::cCityVisualizer construction/teardown and
// vignette update helpers.  Optimized module flags: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"
#include <new>

// ---------------------------------------------------------------------------
// @ 0x00d5ed70
// eastl::vector<Elem1C>::push_back() (append a default-constructed element).
// Elem1C is 0x1c bytes and holds an eastl::vector<EA::AutoRefCount<cStarRecord>>
// at +0x08.  Fast path placement-news a fresh element; slow path builds a
// temporary and calls DoInsertValue.
// ---------------------------------------------------------------------------
struct StarVec {                                        // eastl::vector<AutoRefCount<cStarRecord>>
    void* mBegin;                                       // +0x00
    void* mEnd;                                         // +0x04
    void* mCap;                                         // +0x08
    StarVec() : mBegin(0), mEnd(0), mCap(0) {}
    ~StarVec();
};

struct Elem1C {                                         // 0x1c-byte element
    void*   m00;                                        // +0x00 (uninitialised POD)
    void*   m04;                                        // +0x04
    StarVec v;                                          // +0x08
    void*   m14;                                        // +0x14 (uninitialised POD)
    void*   m18;                                        // +0x18
    Elem1C() {}
};

struct Elem1CVec {
    Elem1C* mBegin;                                     // +0x00
    Elem1C* mEnd;                                       // +0x04
    Elem1C* mCap;                                       // +0x08
    void DoInsertValue(Elem1C* pos, Elem1C* value);     // 0xd5e5c0
    void push_back();
};

void Elem1CVec::push_back()
{
    if (mEnd < mCap) {
        Elem1C* p = mEnd;
        mEnd = p + 1;
        new (p) Elem1C();
    } else {
        Elem1C tmp;
        DoInsertValue(mEnd, &tmp);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00d5edc0
// eastl::vector<SP::cActionCircle>::erase(first, last): copy the tail down,
// destruct the moved-from tail, then shrink mEnd.
// ---------------------------------------------------------------------------
struct cActionCircle {                                  // 100-byte element
    uint32_t m00;
    char     pad[96];
    ~cActionCircle();                                   // 0xafbad0
};

struct ActionCircleVec {
    cActionCircle* mBegin;                              // +0x00
    cActionCircle* mEnd;                                // +0x04
    cActionCircle* mCap;                                // +0x08
    cActionCircle* erase(cActionCircle* first, cActionCircle* last);
};

cActionCircle* FUN_00d5d530(cActionCircle* first, cActionCircle* last, cActionCircle* result); // 0xd5d530

cActionCircle* ActionCircleVec::erase(cActionCircle* first, cActionCircle* last)
{
    cActionCircle* newEnd = FUN_00d5d530(last, mEnd, first);
    cActionCircle* e = mEnd;
    while (newEnd < e) {
        newEnd->~cActionCircle();
        ++newEnd;
    }
    mEnd -= (last - first);
    return first;
}

// ---------------------------------------------------------------------------
// Not reconstructed in this pass (listed as no-source partials in partial.txt).
// These four SP::cCityVisualizer members are large and need the retail class
// layout, which is not available: the 2008 dev-build PDB layout (size 0xb80)
// diverges from retail (the constructor writes fields through +0xc68, and the
// retail cActionCircle is 100 bytes vs 92 in the dev build), so every member
// offset after mPlaza shifts.  Approximate sketches would be behaviourally
// wrong, so none are emitted.
//
// @ 0x00d5e730  SP::cCityVisualizer::cCityVisualizer        (824 bytes)
//   Sets the vftable (0x147bbb0) and default-constructs ~15 sub-objects
//   (three cActionCircles at +0xc/+0x70/+0xd4, cGonzagoTimers, cSPVector3s,
//   several eastl vectors) plus ~150 scalar field stores.  Needs the exact
//   retail member layout and member types (int vs float vs bool) to reproduce
//   the individual `mov dword` / `mov byte` / `movss` stores.
//
// @ 0x00d5ea70  SP::cCityVisualizer::~cCityVisualizer       (754 bytes)
//   Mirrored teardown: resets the vftable and destroys the same sub-objects
//   (cGonzagoTimer / cActionCircle destructors and vector destructors) in
//   reverse order.  Same layout dependency as the constructor.
//
// @ 0x00d5ef80  SP::cCityVisualizer::VignetteCheat          (1349 bytes)
//   Large vignette-selection/update algorithm with heavy float/x87 math,
//   eastl vector walks and many sub-calls; not reproduced.
//
// @ 0x00d5f4d0  SP::cCityVisualizer::StartSpecialVignette  (687 bytes)
//   Vignette start-up: builds a candidate vector, compares circle distances
//   in float, then dispatches; not reproduced.
// ---------------------------------------------------------------------------