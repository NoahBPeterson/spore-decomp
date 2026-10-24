// Slice s00c982a0: SP::cTribe::UpdateToolPosition (0x00c987b0, 2445 bytes). PARTIAL.
// Signature from the asm: __thiscall, one stack int (tool type), ret 4, no return value.
// Only the early-exit checks are written; the rest of the body (the 0x9-0xa / 0xb / 0xc / 0xd
// branches, the reservation-grid updates and the float position math) is still missing.
#include "types.h"

namespace SP {

class cGameData;

struct cActionSlot {                    // 0x18-byte element of cActionCircle's slot array
    void Clear();                       // 0x00afa0a0
    void Reserve(cGameData* gameData);  // 0x00afa030
    char pad0[0xc];
    void* mpPlacement;                  // 0x0c, handed back by cTribe::ReserveToolSlot
    char pad1[0x8];
};

struct cActionCircle {
    char pad0[0x14];
    float mPosition[3];                 // 0x14, weighted-position input of the slot search
    char pad20[0x30];
    cActionSlot* mpSlotsBegin;          // 0x50
    cActionSlot* mpSlotsEnd;            // 0x54
    int FindClosestFreeSlotWeighted(int weight);       // 0x00afa7c0
};

struct cActionCircleMap {
    cActionCircle* FindOrAdd(int* key);                // 0x00c27d20
};

struct cToolContext {                   // interface embedded in cGameData at +0xc0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int ComputeWeight(float* position, float radius);      // +0x2c
};

struct cGameData {                      // slice-local view: only +0xc0 is used here
    char pad0[0xc0];
    cToolContext mToolContext;          // 0xc0
};

class cTribe
{ public:
    void UpdateToolPosition(int toolType);
    void* GetToolOfType(int toolType);      // 0x00c8f6e0, thiscall, returns a tool pointer
    void FindSpot(int spot, int index);                        // 0x00c98750
    void* ReserveToolSlot(int weight, int* outIndex, cGameData* gameData);   // 0x00c986d0

    char pad0[0x394];
    cActionCircleMap mActionCircleMap;      // 0x394
};
}

void SP::cTribe::UpdateToolPosition(int toolType)
{
    // Fields above +0x2d0 are not in the 2008 PDB; accessed by raw offset.
    uint8_t* self = reinterpret_cast<uint8_t*>(this);
    void* tool = GetToolOfType(toolType);
    if (toolType == 0xd && *reinterpret_cast<int*>(self + 0x260) == 0)
        return;
    if (tool == 0 && toolType != 0xd && toolType != 0xc)
        return;
    // TODO: remaining body, see partial.txt.
}

// @ 0x00c98750
// Clear the slot at `index` of the action circle keyed by `spot` when the index is in range.
void SP::cTribe::FindSpot(int spot, int index)
{
    int key = spot;
    cActionCircle* circle = mActionCircleMap.FindOrAdd(&key);
    if (index >= 0 && index < (int)(circle->mpSlotsEnd - circle->mpSlotsBegin)) {
        cActionSlot* slot = circle->mpSlotsBegin + index;
        if (slot)
            slot->Clear();
    }
}

// @ 0x00c986d0
// Reserve the best free action circle slot for `gameData` and publish its index through outIndex.
void* SP::cTribe::ReserveToolSlot(int weight, int* outIndex, cGameData* gameData)
{
    int key = weight;
    cActionCircle* circle = mActionCircleMap.FindOrAdd(&key);
    cToolContext* context = &gameData->mToolContext;
    int score = context->ComputeWeight(circle->mPosition, 0.8f);
    int index = circle->FindClosestFreeSlotWeighted(score);
    *outIndex = index;
    if (index >= 0) {
        cActionSlot* slot = circle->mpSlotsBegin + index;
        if (slot) {
            slot->Reserve(gameData);
            return &slot->mpPlacement;
        }
    }
    return circle->mPosition;
}
