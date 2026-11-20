// Slice s00c45610 -- SP::cSPMission::HasEnoughCargoSpaceForItemsOnAccept
// (retail 0x00c45610, 293 bytes, virtual slot 75, thiscall, returns bool).
//
// Asks the player's inventory whether it can take the keys the mission gives
// on accept. The give-on-accept animal and plant key vectors are offered to
// the inventory; every offer the inventory does not reject (-1) reduces the
// number of keys still to place, and the answer is whether that number fits
// in the free cargo slots the inventory reports.
//
// Retail offsets (from the disassembly, the header's are stale): the
// give-on-accept vectors sit at +0x1a8 (animals) and +0x1bc (plants); a vector
// object spans 0x14 bytes here, so only the first two words (begin/end) are
// read. The retail symbol is non-const (`...QAE_NXZ`).
//
// Flags: /O2 /MD /Gy /TP /GS-

#include "types.h"

typedef unsigned char u8;
typedef unsigned int u32;

namespace SP {

// EA::ResourceMan::Key, 0xc bytes.
struct Key {
    u32 mInstance;                                           // 0x000
    u32 mType;                                               // 0x004
    u32 mGroup;                                              // 0x008
};

// eastl::vector<EA::ResourceMan::Key, eastl::sp_vector_allocator>, 0x14 bytes.
struct KeyVector {
    Key *mpBegin;                                            // 0x00
    Key *mpEnd;                                              // 0x04
    Key *mpCapacityEnd;                                      // 0x08
    u32 mAllocator[2];                                       // 0x0c

    int size() const { return (int)(mpEnd - mpBegin); }
    Key &operator[](int i) { return mpBegin[i]; }
};

class cPlayerInventory;

class cSpaceGame {
 public:
    cPlayerInventory *GetPlayerInventory();                  // 0x00a1ad60
};

cSpaceGame *SpaceGameGet();                                  // 0x01002bd0

// Only the virtual slots this function dispatches through are named; the
// slots before them are kept so +0x64 and +0x8c stay correct.
class cPlayerInventory {
 public:
    virtual void vf00();                                     // slot 0,  vt+0x00
    virtual void vf04();                                     // slot 1
    virtual void vf08();                                     // slot 2
    virtual void vf0c();                                     // slot 3
    virtual void vf10();                                     // slot 4
    virtual void vf14();                                     // slot 5
    virtual void vf18();                                     // slot 6
    virtual void vf1c();                                     // slot 7
    virtual void vf20();                                     // slot 8
    virtual void vf24();                                     // slot 9
    virtual void vf28();                                     // slot 10
    virtual void vf2c();                                     // slot 11
    virtual void vf30();                                     // slot 12
    virtual void vf34();                                     // slot 13
    virtual void vf38();                                     // slot 14
    virtual void vf3c();                                     // slot 15
    virtual void vf40();                                     // slot 16
    virtual void vf44();                                     // slot 17
    virtual void vf48();                                     // slot 18
    virtual void vf4c();                                     // slot 19
    virtual void vf50();                                     // slot 20
    virtual void vf54();                                     // slot 21
    virtual void vf58();                                     // slot 22
    virtual void vf5c();                                     // slot 23
    virtual void vf60();                                     // slot 24
    virtual int CanStoreItem(u32 kind, Key const &key);      // slot 25, vt+0x64
    virtual void vf68();                                     // slot 26
    virtual void vf6c();                                     // slot 27
    virtual void vf70();                                     // slot 28
    virtual void vf74();                                     // slot 29
    virtual void vf78();                                     // slot 30
    virtual void vf7c();                                     // slot 31
    virtual void vf80();                                     // slot 32
    virtual void vf84();                                     // slot 33
    virtual void vf88();                                     // slot 34
    virtual int GetFreeCargoSlots();                         // slot 35, vt+0x8c
};

class cSPMission {
 public:
    bool HasEnoughCargoSpaceForItemsOnAccept();

    u8 mUnknown000[0x1a8];
    KeyVector mGiveOnAcceptAnimalKeys;                       // 0x1a8
    KeyVector mGiveOnAcceptPlantKeys;                        // 0x1bc
};

}  // namespace SP

// @ 0x00c45610
bool SP::cSPMission::HasEnoughCargoSpaceForItemsOnAccept()
{
    SP::cPlayerInventory *inventory = SP::SpaceGameGet()->GetPlayerInventory();
    if (inventory == 0) return false;

    int numNeeded = mGiveOnAcceptPlantKeys.size() + mGiveOnAcceptAnimalKeys.size();
    if (numNeeded <= 0) return true;

    int numFree = inventory->GetFreeCargoSlots();

    const int numPlants = mGiveOnAcceptPlantKeys.size();
    for (int i = 0; i < numPlants; ++i) {
        if (inventory->CanStoreItem(0, mGiveOnAcceptPlantKeys[i]) != -1) --numNeeded;
    }

    const int numAnimals = mGiveOnAcceptAnimalKeys.size();
    for (int i = 0; i < numAnimals; ++i) {
        if (inventory->CanStoreItem(1, mGiveOnAcceptAnimalKeys[i]) != -1) --numNeeded;
    }

    return numNeeded <= numFree;
}
