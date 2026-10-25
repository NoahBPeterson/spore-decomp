// src/game/SPGonzago/SPLocomotiveObject.cpp -- migrated from slice(s) s00c432e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPLocomotiveObject.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cLocomotiveObject.h"

// ---- items of slice s00c432e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSpatialVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
    void erase(void* first, void* last);                     // 0x00b48e40
};
}
namespace SP {
struct cUIntVector {
    uint32_t* mpBegin;                                       // +0x00
    uint32_t* mpEnd;                                         // +0x04
    uint32_t* mpCapacity;                                    // +0x08
    void DoInsertKey4(uint32_t* pos, const uint32_t* value); // 0x00b96600
};
}
namespace SP {
struct cSubD4 {
    void Reset();                                            // 0x00ac5330
};
}
namespace SP {
struct cLocomotiveObject_s00c4_32e0 {
    uint32_t       mPad00[0xd4 / 4];                         // +0x00 .. +0xd3
    cSubD4         mSubD4;                                   // +0xd4
    uint32_t       mPadD8[0x1a0 / 4];                        // +0xd8 .. +0x277
    cSpatialVector mNeighbors;                               // +0x278
    uint32_t       mPad284[0x20c / 4];                       // +0x284 .. +0x48f
    cUIntVector    mVectors;                                 // +0x490
    uint32_t       mPad49c[0x30 / 4];                        // +0x49c .. +0x4cb
    void*          mpField4cc;                               // +0x4cc

    void Shutdown();  // 0x00c43f90 (SP::cLocomotiveObject::Shutdown)
    void InsertUnique(uint32_t value);
};
}
extern "C" void FUN_00c8b2e0();                             // 0x00c8b2e0
// ---- items of slice s00c432e0 end

// @ 0x00c43f90
namespace SP {
void cLocomotiveObject_s00c4_32e0::Shutdown()
{
    if (mpField4cc) {
        mpField4cc = 0;
        ((void (__thiscall*)(void*))((void**)*(void**)mpField4cc)[0x04 / 4])(mpField4cc);
    }
    mNeighbors.erase(mNeighbors.mpBegin, mNeighbors.mpEnd);
    mSubD4.Reset();
    ((void (__thiscall*)(cLocomotiveObject_s00c4_32e0*))FUN_00c8b2e0)(this);
}
}  // namespace SP

// @ 0x00c43fe0
namespace SP {
void cLocomotiveObject_s00c4_32e0::InsertUnique(uint32_t value)
{
    uint32_t* it = mVectors.mpBegin;
    uint32_t* last = mVectors.mpEnd;
    while (it != last && *it != value)
        ++it;
    if (it == last) {
        if (last != mVectors.mpCapacity) {
            mVectors.mpEnd = last + 1;
            if (last)
                *last = value;
        } else {
            mVectors.DoInsertKey4(last, &value);
        }
    }
}
}  // namespace SP
