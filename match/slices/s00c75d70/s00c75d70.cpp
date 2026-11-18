// Slice s00c75d70: unlock test for one of an empire's personality items (0x00C75D70).
//
// The object holds, at +0x129c, a pointer to a per-category table of item
// indices.  For the empire's category (+0x58, categories 0..7 only) the entry
// is looked up, the empire's personality-tuning property list is searched for
// the array 0x07676535, and the number of its values that the player tribe's
// current rank has reached is counted.  When the category's index falls inside
// that count, the item's resource id is written to *out and the mission it
// belongs to is checked.
//
// Sibling entry points (signatures taken from the retail call sites):
//   0x00b3d2a0  StarManager(empire)               __stdcall, callee pops
//   0x00baf700  cStarManager::GetEmpirePersonalityTuning, thiscall, no args
//   0x006a07d0  GetPropertyArrayInt, cdecl, (list, id, &count, &values)
//   0x00c75940  GetEmpirePersonalityItem, cdecl, (empire, index, &instance)
//   0x01002bd0  SpaceGame, cdecl, no args
//   0x00bfc5f0  cSpaceGame::GetPlayerTribe, thiscall, no args
//   0x00fe42a0  cPlayerTribe::GetRank, thiscall, no args
//   0x00feb9f0  cMissionManager look-up by instance id, __stdcall, one arg
//   0x00fee480  cMissionManager::IsComplete, thiscall, no args
#include "game/types.h"

namespace SP {

class cPropertyList;
class cMissionManager;

struct cEmpire {
    char mPad_0000[0x58];
    int  mCategory;                     // +0x58
};

struct cPlayerTribe {
    int GetRank();                      // 0x00fe42a0
};

struct cSpaceGame {
    cPlayerTribe* GetPlayerTribe();     // 0x00bfc5f0
};

struct cStarManager {
    cPropertyList* GetEmpirePersonalityTuning();   // 0x00baf700
};

struct cMissionManager {
    int IsComplete();                   // 0x00fee480
};

struct cPersonalityUnlockTable {
    char  mPad_0000[0x129c];
    int*  mItemIndex;                   // +0x129c

    bool TryGet(cEmpire* empire, int* out);
};

cStarManager* __stdcall StarManager(cEmpire* empire);                       // 0x00b3d2a0
cSpaceGame*   __cdecl   SpaceGame();                                        // 0x01002bd0
cMissionManager* __stdcall GetMissionManager(unsigned int instanceID);      // 0x00feb9f0

// 0x006a07d0: fills *count / *values from the property list entry `id`.
bool __cdecl GetPropertyArrayInt(cPropertyList* properties, unsigned int id,
                                 int* count, int** values);

// 0x00c75940: writes the entry's instance id to *instanceID.
bool __cdecl GetEmpirePersonalityItem(cEmpire* empire, int index, int* instanceID);

// @ 0x00c75d70
bool cPersonalityUnlockTable::TryGet(cEmpire* empire, int* out)
{
    *out = 0;
    if (empire->mCategory < 8) {
        int index = mItemIndex[empire->mCategory];
        cPropertyList* properties = StarManager(empire)->GetEmpirePersonalityTuning();

        int* values;
        int count = 0;
        GetPropertyArrayInt(properties, 0x07676535, &count, &values);

        int rank = SpaceGame()->GetPlayerTribe()->GetRank();
        int unlocked = 0;
        while (count > 0) {
            --count;
            if (rank >= values[count])
                ++unlocked;
        }

        if (index < unlocked && GetEmpirePersonalityItem(empire, index, out)
            && !GetMissionManager(*out)->IsComplete())
            return true;
    }
    return false;
}

}
