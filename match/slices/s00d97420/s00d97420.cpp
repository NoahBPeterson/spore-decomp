// Slice s00d97420 -- citizen tree culture-stage bookkeeping.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

class cSPCreatureCitizen;

// Agent circle owning the citizens that stand in one culture stage (100 bytes).
class cActionCircle {
public:
    void RemoveAgent(cSPCreatureCitizen* pAgent);        // 0x00afae50

    uint8_t mPayload[100];                               // +0x000 .. +0x063
};

// One AutoRefCount slot (4 bytes).
struct cCitizenRef {
    cSPCreatureCitizen* mpCitizen;                       // +0x00
};

// eastl::vector<AutoRefCount<cSPCreatureCitizen>> viewed as raw storage (20 bytes).
struct tCitizenVector {
    void* mpBegin;                                       // +0x00
    void* mpEnd;                                         // +0x04
    void* mpCapacity;                                    // +0x08
    void* mpAllocatorPool;                               // +0x0c
    void* mpAllocatorOwner;                              // +0x10
};

// One culture-stage record of a record page (0x198 bytes).
class cCultureRecord {
public:
    uint8_t         pad000[0x94];                        // +0x000 .. +0x093
    cActionCircle   mCircles[2];                         // +0x094 .. +0x15b
    tCitizenVector  mStageGroups[1];                     // +0x15c .. +0x16f
    uint8_t         pad170[0x198 - 0x170];               // +0x170 .. +0x197
};

// Page owning the culture-stage records.
class cCultureRecordPage {
public:
    uint8_t         pad000[0x390];                       // +0x000 .. +0x38f
    cCultureRecord  mRecords[1];                         // +0x390
};

// Per-attack info passed to the culture-attack callbacks.
struct tCultureAttackInfo {
    uint32_t mField0;                                    // +0x00
    int32_t  mRecordIndex;                               // +0x04
    int32_t  mStage;                                     // +0x08
};

class cSPCreatureCitizen {
public:
    uint8_t             pad000[0xfb8];                   // +0x000 .. +0x0fb7
    cCultureRecordPage* mpRecordPage;                    // +0xfb8
};

namespace spstl {

// Removes the first element matching the given key.
void __cdecl remove_1st(tCitizenVector* pVector, cSPCreatureCitizen** ppCitizen); // 0x00acca00

} // namespace spstl

namespace SP {

class CitizenTree {
public:
    void FUN_00d97420();
    void EnterCity_Activate();
    void CultureAttack_Activate();
    void CultureAttack_Tick();
    void CultureAttack_Deactivate();

    uint8_t           pad000[0x94];                      // +0x000 .. +0x093
    cActionCircle     mCircles[2];                       // +0x094 .. +0x15b
    tCitizenVector    mStageGroups[1];                   // +0x15c
};

} // namespace SP

using namespace SP;

// @ 0xd97420 SP::CitizenTree::FUN_00d97420
void __thiscall CitizenTree::FUN_00d97420()
{
}

// @ 0xd97720 SP::CitizenTree::EnterCity_Activate
void __thiscall CitizenTree::EnterCity_Activate()
{
}

// @ 0xd979b0 SP::CitizenTree::CultureAttack_Activate
void __thiscall CitizenTree::CultureAttack_Activate()
{
}

// @ 0xd97d40 SP::CitizenTree::RemoveFromCultureStageGroup
void __cdecl RemoveFromCultureStageGroup(CitizenTree* pTree, int32_t stage, cSPCreatureCitizen* pCitizen)
{
    pTree->mCircles[stage].RemoveAgent(pCitizen);
    spstl::remove_1st(&pTree->mStageGroups[stage], &pCitizen);
}

// @ 0xd97d80 SP::CitizenTree::CultureAttack_Tick
void __thiscall CitizenTree::CultureAttack_Tick()
{
}

// @ 0xd980e0 SP::CitizenTree::CultureAttack_Deactivate
void __cdecl CultureAttack_Deactivate(cSPCreatureCitizen* pCitizen, int32_t a2, int32_t a3,
                                      int32_t a4, int32_t a5, tCultureAttackInfo* pInfo)
{
    if (pInfo->mRecordIndex == -1)
        return;
    cCultureRecord* pRecord = &pCitizen->mpRecordPage->mRecords[pInfo->mRecordIndex];
    int32_t stage = pInfo->mStage;
    cSPCreatureCitizen* pAgent = pCitizen;
    pRecord->mCircles[stage].RemoveAgent(pCitizen);
    spstl::remove_1st(&pRecord->mStageGroups[stage], &pAgent);
}
