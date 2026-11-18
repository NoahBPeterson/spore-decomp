// Builds the plunder-target list: clears the out vector, reserves room for the
// current empire table, copies every empire in the table whose id is neither the
// current empire nor the "none" sentinel, sorts the result and reports whether
// anything was found.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// memmove used by the inlined erase(begin(), end()); 0x011e0744.
extern "C" void* __cdecl MemMoveRange(void* pDest, const void* pSrc, uint32_t nBytes);
// eastl::RBTreeIncrement; 0x00921580.
extern "C" void* __cdecl RBTreeIncrement(void* pNode);
// Sorts a range of empire pointers with the global comparator object.
struct cEmpirePointerLess;
extern const cEmpirePointerLess sEmpirePointerLess;                   // 0x01601760
void SortEmpires(void** pFirst, void** pLast, const cEmpirePointerLess& compare);  // 0x00afb8a0

class cEmpire;
class cStarManager;

class cStarManager {
public:
    cEmpire* GetEmpireByID(uint32_t nEmpireID);                 // 0x00ba9370
};

cStarManager* __cdecl GetStarManager();                         // 0x00b3d2a0
uint32_t      __cdecl CurrentEmpireID();                        // 0x01021090
void*         __cdecl GetSimulatorContext();                    // 0x01002bd0

// ---------------------------------------------------------------------------
// eastl::rbtree node base: colour plus three links (0x10 bytes).
// ---------------------------------------------------------------------------
struct RBNodeBase {
    int32_t      mColor;                                        // +0x00
    RBNodeBase*  mpLeft;                                        // +0x04
    RBNodeBase*  mpRight;                                       // +0x08
    RBNodeBase*  mpParent;                                      // +0x0c
};

// A table node, keyed by empire id; the key sits right behind the node base.
struct cEmpireNode : RBNodeBase {
    uint32_t mEmpireID;                                         // +0x10
};

// Empire table as seen through the owning simulator object (starts at +0xac of
// that object).  The anchor node is embedded, so end() is its own address.
struct cEmpireMap {
    uint32_t    mPad00;                                         // +0x00
    RBNodeBase  mAnchor;                                        // +0x04
    uint32_t    mnSize;                                         // +0x14

    cEmpireNode* begin() { return (cEmpireNode*)mAnchor.mpLeft; }
    cEmpireNode* end()   { return (cEmpireNode*)&mAnchor; }
};

struct cSimulatorState {
    uint8_t      mPad00[0x30];
    void*        mpTableOwner;                                  // +0x30
};

struct cTableOwner {
    uint8_t     mPad00[0xac];
    cEmpireMap  mEmpireMap;                                     // +0xac
};

// The out vector of empire pointers (eastl::vector<cEmpire*>).
class cEmpireVector {
public:
    cEmpire** mpBegin;                                          // +0x00
    cEmpire** mpEnd;                                            // +0x04
    cEmpire** mpCapacity;                                       // +0x08

    void reserve(uint32_t nCount);                              // 0x00d01790
    void DoInsertValue(cEmpire** pPosition, cEmpire* const& value);  // 0x00b96600

    // eastl::vector::erase(first, last), inlined by the original: the length is a
    // byte difference and the new end is formed by subtracting the element count.
    void erase(cEmpire** pFirst, cEmpire** pLast)
    {
        MemMoveRange(pFirst, pLast, (uint32_t)((uint8_t*)mpEnd - (uint8_t*)pLast));
        mpEnd -= pLast - pFirst;
    }

    void push_back(cEmpire* const& value)
    {
        if (mpEnd < mpCapacity) {
            cEmpire** pSlot = mpEnd;
            mpEnd = pSlot + 1;
            if (pSlot)
                *pSlot = value;
        } else {
            DoInsertValue(mpEnd, value);
        }
    }
};

// @ 0x010129c0
bool __stdcall GatherPlunderTargets(cEmpireVector* pTargets)
{
    cStarManager* pStarManager = GetStarManager();
    uint32_t nOwnEmpireID = CurrentEmpireID();
    cSimulatorState* pState = (cSimulatorState*)GetSimulatorContext();
    cEmpireMap* pEmpireMap =
        &((cTableOwner*)pState->mpTableOwner)->mEmpireMap;

    pTargets->erase(pTargets->mpBegin, pTargets->mpEnd);
    pTargets->reserve(pEmpireMap->mnSize);

    for (cEmpireNode* pNode = pEmpireMap->begin(); pNode != pEmpireMap->end();
         pNode = (cEmpireNode*)RBTreeIncrement(pNode)) {
        uint32_t nEmpireID = pNode->mEmpireID;
        if (nEmpireID != nOwnEmpireID && nEmpireID != (uint32_t)-1) {
            cEmpire* pEmpire = pStarManager->GetEmpireByID(nEmpireID);
            if (pEmpire)
                pTargets->push_back(pEmpire);
        }
    }

    SortEmpires((void**)pTargets->mpBegin, (void**)pTargets->mpEnd,
                sEmpirePointerLess);

    return pTargets->mpBegin != pTargets->mpEnd;
}
