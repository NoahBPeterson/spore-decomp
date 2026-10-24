// Slice s00d0def0: SP::cCommunityEditor::HandleSwatchRolloverOff @ 0x00D0DEF0.
//
// Resolves the palette item behind a swatch rollover, then switches the community
// editor's active placement mode from the item's type hash.  The two Cast hashes
// select the swatch-planner and palette-swatch interfaces; the five handled item
// types set the pending-action hash and a per-mode editor value.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace SP {

class cPaletteItem {
public:
    char     pad00[0x24];                  // +0x00
    uint32_t mTypeID;                      // +0x24
};

class cCommunity {
public:
    virtual void  v00();                   // +0x00
    virtual void  v04();                   // +0x04
    virtual void  v08();                   // +0x08
    virtual void* Cast(uint32_t id);       // +0x0c
};

class cSPSwatchPlanner {
public:
    virtual void  v00();                   // +0x00
    virtual void  v04();                   // +0x04
    virtual void  v08();                   // +0x08
    virtual void* Cast(uint32_t id);       // +0x0c
    virtual void* GetItem();               // +0x10
    char      pad04[0x38];                 // +0x04..+0x3b
    uint32_t  mField3c;                    // +0x3c
    bool      CanDrag();                   // 0x005F1460
};

class cSPPaletteSwatch {
public:
    bool          IsItemAvailable();       // 0x005F33C0
    bool          CheckType();             // 0x005F22D0
    cPaletteItem* GetItem();               // 0x005F33F0
};

class cSwatch {
public:
    virtual int AddRef();                  // +0x00
    virtual int Release();                 // +0x04
    virtual void VSlot08();                // +0x08
    virtual void* Cast(uint32_t type);     // +0x0c
};

// Object returned by cSwatch::Cast: slot 0x10 gives the palette item.
class cCastResult {
public:
    virtual void VSlot00();                // +0x00
    virtual void VSlot04();                // +0x04
    virtual void VSlot08();                // +0x08
    virtual void VSlot0c();                // +0x0c
    virtual void* GetItem();               // +0x10
};

// Non-virtual accessor: returns the palette item stored at +0x180 of the cast result.
class cCastItemOwner {
public:
    cPaletteItem* GetItemField180();
};

class cCommunityEditor {
public:
    char        pad000[0x40];              // +0x00..+0x3f
    cCommunity* mpCommunity;               // +0x40
    char        pad044[0xc0 - 0x44];       // +0x44..+0xbf
    void*       mpManipulatedObject;       // +0xc0
    char        pad0c4[0xf4 - 0xc4];       // +0xc4..+0xf3
    uint32_t    mLastSwapPointIndex;       // +0xf4
    char        pad0f8[0x184];             // +0xf8..+0x27b
    uint32_t    mPendingActionHash;        // +0x27c

    void FUN_00d0db30();                   // 0x00D0DB30 (thiscall, no args)
    void StartVehicleAttractorEffects(void* value); // 0x00D0DDC0
    void HandleSwatchRolloverOff(cSPSwatchPlanner* pSwatch); // 0x00D0DEF0
    void FUN_00d0dea0();                   // 0x00D0DEA0 (thiscall, no args)
    void HandleSwatchRolloverOn(cSwatch* pSwatch); // 0x00D0E0C0
};

} // namespace SP

extern "C" void* FUN_00d08ec0(void* p);                       // 0x00D08EC0
extern "C" int   FUN_00d08ee0(void* p);                       // 0x00D08EE0
extern "C" int   WeaponClassFromHash(uint32_t hash);          // 0x00C9ED00
int __fastcall   FUN_00bd7f40(void* p);                       // 0x00BD7F40
int __fastcall   FUN_00bd7f50(void* p);                       // 0x00BD7F50
int __fastcall   FUN_00bd7f60(void* p);                       // 0x00BD7F60

// @ 0x00d0def0
void SP::cCommunityEditor::HandleSwatchRolloverOff(SP::cSPSwatchPlanner* pSwatch)
{
    if (pSwatch == 0)
        return;

    SP::cSPSwatchPlanner* first =
        (SP::cSPSwatchPlanner*)pSwatch->Cast(0x87e8a1af);
    SP::cSPPaletteSwatch* second =
        (SP::cSPPaletteSwatch*)pSwatch->Cast(0x3349c94);

    if (first != 0) {
        if (!first->CanDrag())
            return;

        SP::cPaletteItem* item = (SP::cPaletteItem*)first->GetItem();
        uint32_t type = item->mTypeID;
        switch (type) {
        case 0x142462a: {
            void* cast = FUN_00d08ec0(&mpCommunity);
            int value = FUN_00bd7f60(cast);
            mPendingActionHash = 0xf089377b;
            mLastSwapPointIndex = (uint32_t)value;
            FUN_00d0db30();
            return;
        }
        case 0x4d863c8b: {
            void* cast = 0;
            if (mpCommunity != 0)
                cast = mpCommunity->Cast(0xee9b2232);
            int value = FUN_00bd7f50(cast);
            mPendingActionHash = 0xf081d484;
            mLastSwapPointIndex = (uint32_t)value;
            FUN_00d0db30();
            return;
        }
        case 0x8bfac054:
            if (first->mField3c == 0x98e03c0d)
                return;
            StartVehicleAttractorEffects((void*)WeaponClassFromHash(first->mField3c));
            return;
        case 0x81c74dbc: {
            void* cast = 0;
            if (mpCommunity != 0)
                cast = mpCommunity->Cast(0xee9b2232);
            int value = FUN_00bd7f40(cast);
            mPendingActionHash = 0x9fdf8751;
            mLastSwapPointIndex = (uint32_t)value;
            FUN_00d0db30();
            return;
        }
        case 0xfcafd26:
            break;
        default:
            return;
        }
    } else {
        if (second == 0)
            return;
        if (!second->IsItemAvailable())
            return;
        if (!second->CheckType())
            return;

        SP::cPaletteItem* item = second->GetItem();
        uint32_t type = item->mTypeID;
        switch (type) {
        case 0x4d863c8b: {
            void* cast = FUN_00d08ec0(&mpCommunity);
            int value = FUN_00bd7f50(cast);
            mPendingActionHash = 0xf081d484;
            mLastSwapPointIndex = (uint32_t)value;
            FUN_00d0db30();
            return;
        }
        case 0xfcafd26:
            break;
        default:
            return;
        }
    }

    int value = FUN_00d08ee0(&mpCommunity);
    mPendingActionHash = 0xeeef054f;
    mLastSwapPointIndex = (uint32_t)(value + 0x3b4);
    FUN_00d0db30();
}

// @ 0x00d0e0c0
// Restored from before the gold7 rewrite (byte-exact): looks up the object a swatch rollover refers to and, for the
// five palette item types, resets the editor's manipulation state when nothing is being manipulated.
void SP::cCommunityEditor::HandleSwatchRolloverOn(SP::cSwatch* pSwatch) {
    if (pSwatch == 0) return;
    SP::cCastResult* pA = (SP::cCastResult*)pSwatch->Cast(0x87e8a1af);
    SP::cCastResult* pB = (SP::cCastResult*)pSwatch->Cast(0x3349c94);
    SP::cPaletteItem* pItem;
    if (!pB) {
        if (!pA) return;
        pItem = (SP::cPaletteItem*)pA->GetItem();
    } else {
        if (pA) pItem = (SP::cPaletteItem*)pA->GetItem();
        else pItem = ((SP::cCastItemOwner*)pB)->GetItemField180();
    }

    uint32_t type = pItem->mTypeID;
    if (type <= 0x4d863c8b) {
        if (type != 0x4d863c8b && type != 0x142462a && type != 0xfcafd26) return;
    } else {
        if (type != 0x81c74dbc && type != 0x8bfac054) return;
    }

    if (mpManipulatedObject == 0) {
        FUN_00d0dea0();
        mLastSwapPointIndex = 0;
        mPendingActionHash = 0;
    }
}
