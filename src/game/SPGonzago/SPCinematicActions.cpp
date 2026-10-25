// src/game/SPGonzago/SPCinematicActions.cpp -- migrated from slice(s) s00ad20e0, s004215f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCinematicActions.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char vtbl_App_cLocaleChangeMessage[];     // 0x013eb918
extern char vtbl_UI_BehaviorMessage[];           // 0x013eb90c
extern char vtbl_SlotMessage[];                  // 0x013eb844
#include <intrin.h>
#include "SP/tNavigationGoal.h"
#include <string.h>

// ---- items of slice s004215f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
struct Elem24 { uint32_t d[6]; void Destruct(uint32_t flags); };   // 0x18-byte element, deleting-dtor style at 0x00429410
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

// @ 0x00421e30
Elem24Vec2::~Elem24Vec2()
{
    DestroyRange(mBegin, mEnd);
    ScratchSlots<3>();
    Free();
}

