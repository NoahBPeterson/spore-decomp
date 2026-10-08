// Slice s00d0def0 -- SP::cCommunityEditor::HandleSwatchRolloverOn (0x00d0e0c0, 170 bytes).
//
// Looks up the object that a swatch rollover refers to (by type hash through the swatch's
// Cast slot), then, for the five palette item types, resets the editor's manipulation state
// when no object is being manipulated.
#include "types.h"

namespace SP {

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

// Palette item: only the type hash at +0x24 is read here.
class cPaletteItem {
public:
    char pad00[0x24];
    uint32_t mTypeID;                      // +0x24
};

// Non-virtual accessor: returns the palette item stored at +0x180 of the cast result.
class cCastItemOwner {
public:
    cPaletteItem* GetItemField180();
};

class cCommunityEditor {
public:
    char pad000[0xc0];
    void* mpManipulatedObject;             // +0xc0
    char pad0c4[0xf4 - 0xc4];
    uint32_t mField0f4;                    // +0xf4
    char pad0f8[0x27c - 0xf8];
    uint32_t mField27c;                    // +0x27c

    void FUN_00d0dea0();                   // 0x00d0dea0 (thiscall, no args)
    void HandleSwatchRolloverOn(cSwatch* pSwatch);
};

void cCommunityEditor::HandleSwatchRolloverOn(cSwatch* pSwatch) {
    if (pSwatch == 0) return;
    cCastResult* pA = (cCastResult*)pSwatch->Cast(0x87e8a1af);
    cCastResult* pB = (cCastResult*)pSwatch->Cast(0x3349c94);
    cPaletteItem* pItem;
    if (!pB) {
        if (!pA) return;
        pItem = (cPaletteItem*)pA->GetItem();
    } else {
        if (pA) pItem = (cPaletteItem*)pA->GetItem();
        else pItem = ((cCastItemOwner*)pB)->GetItemField180();
    }

    uint32_t type = pItem->mTypeID;
    if (type <= 0x4d863c8b) {
        if (type != 0x4d863c8b && type != 0x142462a && type != 0xfcafd26) return;
    } else {
        if (type != 0x81c74dbc && type != 0x8bfac054) return;
    }

    if (mpManipulatedObject == 0) {
        FUN_00d0dea0();
        mField0f4 = 0;
        mField27c = 0;
    }
}

} // namespace SP
