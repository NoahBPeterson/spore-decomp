// Slice s00c759a0: refresh of the five property values stored at +0x10fc..+0x110c.
//
// Refresh takes the current player/terrain object returned by 0x01021300, asks it
// for its property key (0x00c30f90 returns the key at +0xc4), and when that key is
// a real one re-summarizes the object once per non-zero stored property value.
// The object only exposes retail offsets here; the five dwords at +0x10fc..+0x110c
// are the same values written by the sibling slice s00c75cc0 (0x00c75cc0).
#include "types.h"

// 0x01021300: current player-side object (empire/terrain sphere owner).
void* __cdecl FUN_01021300();
// 0x00555f70: fold one property value into the object identified by a key.
void __cdecl FUN_00555f70(void* key, uint32_t value);

// Game property key: the first dword is the type tag, 0 means "no key".
struct cKey {
    uint32_t mType;
    uint32_t mInstance;
    uint32_t mGroup;

    cKey* GetPtr();                     // 0x00c30f90 (returns this + 0xc4)
};

struct cKeyOwner {
    char  mPad_0000[0xc4];
    cKey  mKey;                         // +0x00c4

    cKey* GetKey();                     // 0x00c30f90
};

struct cPropertyObject {
    char mPad_0000[0x10fc];
    int  mProperty10fc;                 // +0x10fc
    int  mProperty1100;                 // +0x1100
    int  mProperty1104;                 // +0x1104
    int  mProperty1108;                 // +0x1108
    int  mProperty110c;                 // +0x110c

    void Refresh();                     // 0x00c759a0 (thiscall, no args)
};

// @ 0x00c759a0
void cPropertyObject::Refresh()
{
    cKeyOwner* owner = (cKeyOwner*)FUN_01021300();
    cKey* key = owner->GetKey();

    if (key->mType != 0) {
        if (mProperty10fc)
            FUN_00555f70(key, mProperty10fc);
        if (mProperty1100)
            FUN_00555f70(key, mProperty1100);
        if (mProperty1104)
            FUN_00555f70(key, mProperty1104);
        if (mProperty1108)
            FUN_00555f70(key, mProperty1108);
        if (mProperty110c)
            FUN_00555f70(key, mProperty110c);
    }
}
