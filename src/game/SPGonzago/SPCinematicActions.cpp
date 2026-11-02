// src/game/SPGonzago/SPCinematicActions.cpp -- migrated from slice(s) s00572580, s004215f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCinematicActions.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char vtbl_App_cLocaleChangeMessage[];     // 0x013eb918
extern char vtbl_UI_BehaviorMessage[];           // 0x013eb90c
extern char vtbl_SlotMessage[];                  // 0x013eb844
#include <intrin.h>
#include <new>
#include <string.h>
#include <math.h>
#include <ctype.h>

// ---- items of slice s004215f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
struct Elem32 { uint32_t d[8]; ~Elem32(); };      // 0x20-byte element, dtor at 0x005477e0
struct Elem56 { uint32_t d[14]; ~Elem56(); };     // 0x38-byte element, dtor at 0x00429480
struct Elem24 { uint32_t d[6]; void Destruct(uint32_t flags); };   // 0x18-byte element, deleting-dtor style at 0x00429410
struct Elem32Vec {
    Elem32* mBegin;
    Elem32* mEnd;
    Elem32* mCap;
    void Free();                                   // 0x004273f0
    static void DestroyRange(Elem32* f, Elem32* l) { ScratchSlots<4>(); for (; f < l; ++f) f->~Elem32(); }
    ~Elem32Vec();
};
struct Elem56Vec {
    Elem56* mBegin;
    Elem56* mEnd;
    Elem56* mCap;
    void Free();                                   // 0x00427440
    static void DestroyRange(Elem56* f, Elem56* l) { ScratchSlots<9>(); for (; f < l; ++f) f->~Elem56(); }
    ~Elem56Vec();
};
struct Elem24Vec2 {
    Elem24* mBegin;
    Elem24* mEnd;
    Elem24* mCap;
    void Free();                                   // 0x004fd940
    static void DestroyRange(Elem24* f, Elem24* l) { ScratchSlots<3>(); for (; f < l; ++f) f->Destruct(0); }
    ~Elem24Vec2();
};
extern char vtbl_App_cLocaleChangeMessage[];     // 0x013eb918
extern char vtbl_UI_BehaviorMessage[];           // 0x013eb90c
extern char vtbl_SlotMessage[];                  // 0x013eb844
struct Listener { virtual void v0(); virtual void Release(); };
struct Slot { Listener* listener; uint32_t extra; };
struct SlotMessage {
    const void* vptr;          // +0x00
    volatile long refCount;    // +0x04
    uint32_t body[0x2c];       // +0x08 .. : 32 slots of 8 bytes; arg lives at +0x30, listener mask at +0x38

    SlotMessage* Construct(uint32_t arg);
    void Destruct();
};
// ---- items of slice s004215f0 end

// ---- items of slice s00572580 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
struct IRefCount {
    virtual int AddRef();     // +0x00
    virtual int Release();    // +0x04
};
namespace SP {
template <int N>
class MessageBasicRC_s0057_2580 { public:
    union Data {
        void* mpVoid;
        IRefCount* mpRC;
        uint64_t mUint64;
    };
    void* mpVtbl;
    int mnRefCount;
    Data mData[N];        // +0x08
    uint32_t mId;
    uint32_t mPad;
    uint32_t mRCFlags;

    void SetIRefCount(int i, IRefCount* p);
};
}
namespace SP {
template class MessageBasicRC_s0057_2580<5>;
}
// ---- items of slice s00572580 end

// @ 0x00421cf0
void SlotMessage::Destruct()
{
    vptr = vtbl_SlotMessage;
    for (int i = 0; i < 32; i++) {
        if (((1 << i) & body[12]) && ((Slot*)body)[i].listener)
            ((Slot*)body)[i].listener->Release();
    }
    vptr = vtbl_UI_BehaviorMessage;
    vptr = vtbl_App_cLocaleChangeMessage;
}

// @ 0x00421d70
Elem32Vec::~Elem32Vec()
{
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

// @ 0x00421dd0
Elem56Vec::~Elem56Vec()
{
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

// @ 0x00421e30
Elem24Vec2::~Elem24Vec2()
{
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

// @ 0x005726e0
namespace SP {
template <int N> void MessageBasicRC_s0057_2580<N>::SetIRefCount(int i, IRefCount* p)
{
    const uint32_t mask = 1 << i;
    if ((mRCFlags & mask) && mData[i].mpRC)
        mData[i].mpRC->Release();
    mData[i].mpRC = p;
    if (p)
        p->AddRef();
    mRCFlags |= mask;
}
}  // namespace SP
