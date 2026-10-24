// SporeApp.exe slice s00be30e0 -- agent-group action (spawn / repair / facing) (gold6, worker 36)

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// small shared types
// ---------------------------------------------------------------------------

struct cVec3 {
    float x;                                                // +0x00
    float y;                                                // +0x04
    float z;                                                // +0x08
};

struct cMat4 {
    float m[16];                                            // +0x00
};

// 12-byte resource key.
struct ResourceKey {
    uint32_t mInstanceID;                                   // +0x00
    uint32_t mGroupID;                                      // +0x04
    uint32_t mTypeID;                                       // +0x08
};

// eastl vector of pointers (begin/end/capacity).
struct cPtrList {
    void**           mpBegin;                               // +0x00
    void**           mpEnd;                                 // +0x04
    void**           mpCap;                                 // +0x08
};

// eastl vector of ref-counted pointers with erasure.
struct cRefList {
    void**           mpBegin;                               // +0x00
    void**           mpEnd;                                 // +0x04
    void**           mpCap;                                 // +0x08
    void**  erase(void** pFirst, void** pLast);             // 0x00e25bd0
};

// eastl::map<uint32_t, uint32_t>.
struct cUIntMap {
    uint8_t   mPad00[0xac];                                 // +0x00 .. +0xab
    uint32_t* operator[](const uint32_t& nKey);             // 0x00643a40
};

// ---------------------------------------------------------------------------
// engine sub-objects
// ---------------------------------------------------------------------------

// Spatial component of a noun (noun+0x34).
struct cSpatial {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028();
    virtual cVec3* GetPosition();                           // +0x2c
    virtual void v030(); virtual void v034();
    virtual void SetPosition(const cVec3* pPosition);       // +0x38
    virtual void SetOrientation(const cMat4* pMatrix);      // +0x3c
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058();
    virtual void* v05c(void* pOut);                         // +0x5c
    virtual void v060(); virtual void v064();
    virtual void* v068();                                   // +0x68
    virtual void v06c(); virtual void v070(); virtual void v074(); virtual void v078();
    virtual void v07c(); virtual void v080(); virtual void v084(); virtual void v088();
    virtual void v08c(); virtual void v090();
    virtual void SetKey(const ResourceKey* pKey);           // +0x94
};

// Combatant component of a noun (noun+0x120).
struct cCombatant {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028();
    virtual cVec3* GetPosition();                           // +0x2c
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054();
    virtual float v058();                                   // +0x58 (health fraction)
    virtual void* v05c(void* pOut);                         // +0x5c

    int32_t GetDamageState();                               // 0x008e7f80
    void    PartialRepair(float fAmount);                   // 0x00bfd1a0
    bool    IsDeadOrDying();                                // 0x00bfc600
};

// Object whose vtable slot +0x4c yields a stable id.
struct cIDSource {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048();
    virtual uint32_t v04c();                                // +0x4c
};

// A noun (agent) managed by the action.
struct cNoun {
    virtual void v000();                                    // +0x00 (on destroy)
    virtual void v004();                                    // +0x04 (release)
    virtual void v008(); virtual void v00c(); virtual void v010(); virtual void v014();
    virtual void v018(); virtual void v01c(); virtual void v020(); virtual void v024();
    virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034();
    virtual uint32_t GetTypeID();                           // +0x38
    virtual void v03c(); virtual void v040();
    virtual void v044(); virtual void v048(); virtual void v04c(); virtual void v050();
    virtual void v054(); virtual void v058(); virtual void v05c(); virtual void v060();
    virtual void v064(); virtual void v068(); virtual void v06c(); virtual void v070();
    virtual void v074(); virtual void v078(); virtual void v07c(); virtual void v080();
    virtual void v084(); virtual void v088(); virtual void v08c(); virtual void v090();
    virtual void v094(const ResourceKey* pKey);             // +0x94
    uint8_t      mPad004[0x30];                             // +0x004 .. +0x033
    cSpatial     mSpatial;                                  // +0x34
    uint8_t      mPad058[0xe8];                             // +0x38 .. +0x11f
    cCombatant   mCombatant;                                // +0x120

    int32_t GetTimerA();                                    // 0x00bcc800
    int32_t GetTimerB();                                    // 0x00bcd250
    bool    IsSpecial();                                    // 0x00c3f540
};

// Slot record manager embedded in the action.
struct cSlotMgr {
    uint8_t  mPad00[0x64];                                  // +0x00 .. +0x63

    void  RemoveAgent(void* pAgent);                        // 0x00afae50
    void* FindSlot(void* pKey);                             // 0x00afad70
    void* SlotAt(uint32_t nSlot);                           // 0x00af9ff0
};

// Timer sub-object.
struct cSPTimer {
    uint8_t  mPad00[0x20];                                  // +0x00 .. +0x1f

    bool     IsRunning();                                   // 0x00feba90
    uint64_t GetElapsedTime();                              // 0x00bc3190
    void     Stop();                                        // 0x00bc3110
};

// Planet model.
struct cPlanetModel {
    cMat4* BuildSurfaceOrientation2();                      // 0x00b7f250
};

// Noun manager.
struct cGameNounManager {
    uint8_t mPad00[0x04];                                   // +0x00
    void RemoveNoun();                                      // 0x00b225d0
};

// Effect emitter.
struct cEffectEmitter {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(uint32_t nEffect, const void* pA, const void* pB);   // +0x60
};

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------

void* __cdecl FUN_00bd98c0();                               // 0x00bd98c0
void* __cdecl FUN_00be1fb0();                               // 0x00be1fb0
void  __cdecl FUN_00be2440(void* pThis, int32_t nA, int32_t nB);   // 0x00be2440
void  __cdecl FUN_00be2b10(const char* pKey, cPtrList* pOut);      // 0x00be2b10
void  __cdecl FUN_00be2070(void* pNoun, int32_t nFlags);    // 0x00be2070
char  __cdecl FUN_00c004c0(int32_t nArg);                   // 0x00c004c0
void* __cdecl FUN_00b3d240();                               // 0x00b3d240
void  __cdecl FUN_00be10d0();                               // 0x00be10d0
void  __cdecl FUN_00d5aae0(void* pContainer, void** ppOut, void* pArg);   // 0x00d5aae0
void  __cdecl FUN_00afa030(void* pSlot, void* pNoun);       // 0x00afa030
void  __cdecl FUN_00ff2810(void* pAction, void* pPlanet);   // 0x00ff2810
void* __cdecl FUN_01021260();                               // 0x01021260
void  __cdecl FUN_009360d0();                               // 0x009360d0
void* __cdecl operator_new(uint32_t nSize, const char* pFile, int32_t a, int32_t b,
                           const char* pAlloc, int32_t nLine);      // 0x00f473a0
void  __cdecl operator_delete_array(void* pBlock);          // 0x00f47380
void  __cdecl eastl_copy_impl(void** pFirst, void** pLast, void** pDest);   // 0x006782c0
void  __cdecl SP_SetKeyKind(ResourceKey* pKey, uint32_t nKind, uint32_t nAux);   // 0x0068c6d0
cPlanetModel* __cdecl SP_PlanetModel(const void* pA, const void* pB, const void* pC);   // 0x00b3d350
cGameNounManager* __stdcall SP_NounManager(void* pNoun);    // 0x00b3d300
void  __cdecl SP_NormalizedSafe(const void* pIn, void* pOut);   // 0x00449c20
void  __cdecl SlotConstruct(void* pValue);                  // 0x00bdd470
void  __cdecl SlotDestroy(void* pValue);                    // 0x00bdd380
void* __cdecl SlotCopyRange(void* pFirst, void* pLast, void* pDest);   // 0x00bdd5c0
void  __cdecl SlotDestroyRange(void* pFirst, void* pLast, void* pUnused);   // 0x00bd8480
void  __cdecl SlotMoveBackward(void* pPos, void* pFirst, void* pLast);   // 0x00bdd640

extern const float kZeroEpsilon;                            // 0x013ec4b8
extern const float kRepairFraction;                         // 0x01470f1c
extern const float kGrowFraction;                           // 0x01485544
extern const float kOne;                                    // 0x01485720
extern const float kNegOne;                                 // 0x013eb1bc

// ---------------------------------------------------------------------------
// element vector used by 0x00be30e0 (0x80-byte slot records)
// ---------------------------------------------------------------------------

struct cSlotVector {
    uint8_t* mpBegin;                                       // +0x00
    uint8_t* mpEnd;                                         // +0x04
    uint8_t* mpCap;                                         // +0x08

    void Insert(uint8_t* pPos, const uint8_t* pValue);      // 0x00be30e0
};

// ---------------------------------------------------------------------------
// the action object
// ---------------------------------------------------------------------------

struct cAgentAction {
    virtual void v000();
    virtual void v004();
    virtual void v008();
    virtual void v00c();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01c();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02c();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03c();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04c();
    virtual void v050();
    virtual void v054();
    virtual cVec3* v058(cVec3* pOut);                       // +0x58 (world position)

    uint8_t      mPad004[0x64];                             // +0x004 .. +0x06b (align pad + 0x60)
    uint8_t      mField6c;                                  // +0x06c
    uint8_t      mPad06d[0x77];                             // +0x06d .. +0x0e3
    cRefList     mRefs0e4;                                  // +0x0e4
    uint8_t      mPad0f0[0x30];                             // +0x0f0 .. +0x11f
    cCombatant   mComponent120;                             // +0x120
    uint8_t      mPad124[0xbc];                             // +0x124 .. +0x1df
    uint32_t*    mpIDs1e0;                                  // +0x1e0
    uint32_t*    mpIDs1e4;                                  // +0x1e4
    uint8_t      mPad1e8[0x48];                             // +0x1e8 .. +0x22f
    cSPTimer     mTimer230;                                 // +0x230
    cSPTimer     mTimer250;                                 // +0x250
    cSPTimer     mTimer270;                                 // +0x270
    uint64_t     mTimestamp290;                             // +0x290
    uint8_t      mPad298[0x70];                             // +0x298 .. +0x307
    uint8_t      mField308[0x38];                           // +0x308 .. +0x33f
    cPtrList     mAgents340;                                // +0x340
    uint8_t      mPad348[0x0c];                             // +0x348 .. +0x353
    cPtrList     mAgents354;                                // +0x354
    uint8_t      mPad35c[0x88];                             // +0x35c .. +0x3eb
    cSlotMgr     mCircleA3ec;                               // +0x3ec
    cSlotMgr     mCircleB450;                               // +0x450
    cSlotMgr     mCircleC4b4;                               // +0x4b4
    uint8_t      mPad518[0x78];                             // +0x518 .. +0x58f
    cIDSource*   mpField590;                                // +0x590
    uint8_t      mPad594[0x0c];                             // +0x594 .. +0x59f
    cUIntMap     mMap5a0;                                   // +0x5a0 .. +0x649
    int32_t      mField64c;                                 // +0x64c
    float        mField650;                                 // +0x650
    uint8_t      mPad654[0x19c];                            // +0x654 .. +0x7ef
    int32_t      mField7f0;                                 // +0x7f0
    int32_t      mField7f4;                                 // +0x7f4
    uint8_t      mPad7f8[0x18];                             // +0x7f8 .. +0x80f
    cNoun*       mpField810;                                // +0x810

    bool  RemoveID(uint32_t nID);                           // 0x00be3230
    void  IncrementCounter();                               // 0x00be32b0
    void  IncrementCounterBy(int32_t nTimes);               // 0x00be32f0
    bool  RemoveAgent(void* pAgent);                        // 0x00be3350
    void  DestroyAgent(cNoun* pNoun);                       // 0x00be33e0
    void  DestroyAgentsOfType(uint32_t nUnused, int32_t nType);   // 0x00be3420
    void  RemoveSlotAgent(cNoun* pNoun);                    // 0x00be34a0
    void  RemoveAgentAndFlag(cNoun* pNoun);                 // 0x00be34e0
    bool  SpawnAgent(cNoun* pNoun, bool bNotify);           // 0x00be3500
    bool  FaceTarget();                                     // 0x00be3850
    bool  FaceSlot(uint32_t nSlot);                         // 0x00be3990
    void  UpdateRepair();                                   // 0x00be3ad0
    void  UpdateTimers();                                   // 0x00be3de0
    void  AdvanceFloatCounter(float fDelta);                // 0x00be3f00
    cRefList* ClearRefs();                                  // 0x00be3fe0
};

// ===========================================================================
// 0x00be30e0 : insert one 0x80-byte record into the slot vector
// ===========================================================================
// @ 0x00be30e0
void cSlotVector::Insert(uint8_t* pPos, const uint8_t* pValue)
{
    if (mpEnd == mpCap) {
        int32_t nCount = (int32_t)(mpEnd - mpBegin) >> 7;
        int32_t nNewCount = nCount > 0 ? nCount * 2 : 1;
        uint8_t* pNew = 0;
        if (nNewCount != 0)
            pNew = (uint8_t*)operator_new((uint32_t)nNewCount << 7, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        uint8_t* pBegin = mpBegin;
        uint8_t* pSplit = (uint8_t*)SlotCopyRange(pBegin, pPos, pNew);
        SlotDestroyRange(pBegin, pPos, pNew);
        if (pSplit != 0)
            SlotConstruct((void*)pValue);
        uint8_t* pResult = (uint8_t*)SlotCopyRange(pPos, mpEnd, pSplit + 0x80);
        SlotDestroyRange(pPos, mpEnd, pSplit + 0x80);
        if (pBegin && ((int32_t*)pBegin)[-1] != 0)
            operator_delete_array(pBegin);
        mpBegin = pNew;
        mpEnd = pResult;
        mpCap = pNew + ((uint32_t)nNewCount << 7);
        return;
    }
    uint8_t* pSource = (uint8_t*)pValue;
    if (pPos <= pValue && pValue < mpEnd)
        pSource = (uint8_t*)pValue + 0x80;
    if (mpEnd != 0)
        SlotDestroy(mpEnd - 0x80);
    SlotMoveBackward(pPos, mpEnd - 0x80, mpEnd);
    SlotConstruct(pSource);
    mpEnd = mpEnd + 0x80;
}

// ===========================================================================
// 0x00be3230 : drop the first occurrence of an id
// ===========================================================================
// @ 0x00be3230
bool cAgentAction::RemoveID(uint32_t nID)
{
    bool bResult = false;
    int32_t nCount = (int32_t)((uint8_t*)mpIDs1e4 - (uint8_t*)mpIDs1e0) >> 2;
    if (nCount > 0) {
        int32_t nIndex = -1;
        for (int32_t i = 0; i < nCount; ++i) {
            if (mpIDs1e0[i] == nID)
                nIndex = i;
        }
        if (nIndex >= 0) {
            for (int32_t i = nIndex; i < nCount - 1; ++i)
                mpIDs1e0[i] = mpIDs1e0[i + 1];
            mpIDs1e4 = (uint32_t*)((uint8_t*)mpIDs1e4 - 4);
            bResult = true;
        }
    }
    if (mpIDs1e4 == mpIDs1e0)
        FUN_00be10d0();
    return bResult;
}

// ===========================================================================
// 0x00be32b0 : one tick of the shared counter
// ===========================================================================
// @ 0x00be32b0
void cAgentAction::IncrementCounter()
{
    if (mField64c > 99) {
        return;
    }
    ++mField64c;
    if (mpField590)
        ++*mMap5a0[mpField590->v04c()];
}

// @ 0x00be32f0
void cAgentAction::IncrementCounterBy(int32_t nTimes)
{
    if (nTimes > 0) {
        for (int32_t i = nTimes; i != 0; --i) {
            if (mField64c > 99)
                continue;
            ++mField64c;
            if (mpField590)
                ++*mMap5a0[mpField590->v04c()];
        }
    }
}

// ===========================================================================
// 0x00be3350 : remove one agent from the managed list
// ===========================================================================
// @ 0x00be3350
bool cAgentAction::RemoveAgent(void* pAgent)
{
    bool bResult = false;
    void** pEnd = mAgents340.mpEnd;
    void** it = mAgents340.mpBegin;
    if (it != pEnd) {
        do {
            if (*it == pAgent)
                break;
            ++it;
        } while (it != pEnd);
        if (it != pEnd) {
            if (it + 1 < mAgents340.mpEnd)
                eastl_copy_impl(it + 1, mAgents340.mpEnd, it);
            mAgents340.mpEnd = mAgents340.mpEnd - 1;
            cNoun* pRemoved = (cNoun*)*mAgents340.mpEnd;
            if (pRemoved)
                pRemoved->v004();
            mCircleA3ec.RemoveAgent(pAgent);
            bResult = true;
        }
    }
    FUN_00be2440(this, 0, 0);
    return bResult;
}

// @ 0x00be33e0
void cAgentAction::DestroyAgent(cNoun* pNoun)
{
    if (!pNoun)
        return;
    pNoun->v000();
    SP_NounManager(pNoun)->RemoveNoun();
    RemoveAgent(pNoun);
    pNoun->v004();
}

// @ 0x00be3420
void cAgentAction::DestroyAgentsOfType(uint32_t nUnused, int32_t nType)
{
    (void)nUnused;
    int32_t nCount = (int32_t)((uint8_t*)mAgents340.mpEnd - (uint8_t*)mAgents340.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount; ++i) {
        cNoun* pNoun = (cNoun*)mAgents340.mpBegin[i];
        if ((int32_t)pNoun->GetTypeID() == nType && !pNoun->IsSpecial()) {
            pNoun->v000();
            SP_NounManager(pNoun)->RemoveNoun();
            RemoveAgent(pNoun);
            pNoun->v004();
            return;
        }
    }
}

// @ 0x00be34a0
void cAgentAction::RemoveSlotAgent(cNoun* pNoun)
{
    cNoun* pResult;
    FUN_00d5aae0(mField308, (void**)&pResult, pNoun);
    cNoun* pAgent = pResult;
    mCircleB450.RemoveAgent(pAgent);
    SP_NounManager(pAgent)->RemoveNoun();
}

// @ 0x00be34e0
void cAgentAction::RemoveAgentAndFlag(cNoun* pNoun)
{
    if (RemoveAgent(pNoun))
        mField6c = 1;
}

// ===========================================================================
// 0x00be3500 : place a spawned agent in the target slot
// ===========================================================================
// @ 0x00be3500
bool cAgentAction::SpawnAgent(cNoun* pNoun, bool bNotify)
{
    void* pSlot = mCircleA3ec.FindSlot(pNoun->mSpatial.GetPosition());
    if (!pSlot)
        return false;

    FUN_00afa030(pSlot, pNoun);

    cVec3 position;
    position.x = *(float*)((uint8_t*)pSlot + 0x0c);
    position.y = *(float*)((uint8_t*)pSlot + 0x10);
    position.z = *(float*)((uint8_t*)pSlot + 0x14);
    pNoun->mSpatial.SetPosition(&position);

    cVec3 normal;
    cVec3 out;
    if (pNoun->GetTypeID() == 0x18ea1eb) {
        out = *(cVec3*)mComponent120.v05c(&out);
    } else if (mField7f4 == 1) {
        cVec3* pOrigin = mComponent120.GetPosition();
        normal.x = pOrigin->x - position.x;
        normal.y = pOrigin->y - position.y;
        normal.z = pOrigin->z - position.z;
        SP_NormalizedSafe(&normal, &out);
    } else if (mField7f4 == 2) {
        mComponent120.v05c(&out);
        FUN_009360d0();
        SP_NormalizedSafe(&out, &normal);
        mComponent120.v05c(&normal);
    }
    cMat4 orientation;
    pNoun->mSpatial.SetOrientation(SP_PlanetModel(&out, &normal, &orientation)->BuildSurfaceOrientation2());
    if (bNotify)
        FUN_00be2440(this, 0, 0);
    return true;
}

// ===========================================================================
// 0x00be3720 : broadcast an order to the noun group selected by command id
// ===========================================================================
// @ 0x00be3720
void __stdcall AgentCommand(uint32_t nAction, uint32_t nA, uint32_t nB, uint32_t nC)
{
    cPtrList list;
    list.mpBegin = 0;
    list.mpEnd = 0;
    list.mpCap = 0;
    switch (nAction) {
    case 0x4e3f7777: FUN_00be2b10((const char*)0x18eb106, &list); break;
    case 0x99e92f05: FUN_00be2b10((const char*)0x18ea1eb, &list); break;
    case 0x47c10953: FUN_00be2b10((const char*)0x18ea2cc, &list); break;
    case 0x72c49181: FUN_00be2b10((const char*)0x1a56aba, &list); break;
    }
    int32_t nCount = (int32_t)((uint8_t*)list.mpEnd - (uint8_t*)list.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount; ++i) {
        cNoun* pNoun = (cNoun*)list.mpBegin[i];
        if (!pNoun)
            continue;
        ResourceKey key;
        pNoun->v094(&key);
        if (pNoun->mCombatant.GetDamageState() == 2) {
            ResourceKey newKey = key;
            newKey.mInstanceID = nA;
            newKey.mGroupID = nB;
            newKey.mTypeID = nC;
            SP_SetKeyKind(&newKey, 0x7e, 0);
            pNoun->v094(&newKey);
        }
    }
    for (void** it = list.mpBegin; it < list.mpEnd; ++it) {
        if (*it)
            ((cNoun*)*it)->v004();
    }
    if (list.mpBegin && ((int32_t*)list.mpBegin)[-1] != 0)
        operator_delete_array(list.mpBegin);
}

// ===========================================================================
// 0x00be3850 : face the current target
// ===========================================================================
// @ 0x00be3850
bool cAgentAction::FaceTarget()
{
    cNoun* pNoun = (cNoun*)FUN_00bd98c0();
    if (!pNoun)
        return false;

    cNoun* pData = (cNoun*)FUN_00be1fb0();
    FUN_00afa030(pData, pNoun);
    cVec3 position;
    position.x = *(float*)((uint8_t*)pNoun + 0x0c);
    position.y = *(float*)((uint8_t*)pNoun + 0x10);
    position.z = *(float*)((uint8_t*)pNoun + 0x14);
    pData->mSpatial.SetPosition(&position);

    cVec3 origin;
    cVec3* pRef = v058(&origin);
    cVec3 normal;
    normal.x = position.x - pRef->x;
    normal.y = position.y - pRef->y;
    normal.z = position.z - pRef->z;
    float fInv = 1.0f / sqrtf(normal.x * normal.x + normal.y * normal.y
                              + normal.z * normal.z + kZeroEpsilon);
    cVec3 dir;
    dir.x = normal.x * fInv;
    dir.y = normal.y * fInv;
    dir.z = normal.z * fInv;
    cMat4 orientation;
    pData->mSpatial.SetOrientation(SP_PlanetModel(&dir, &origin, &orientation)->BuildSurfaceOrientation2());

    if (mpField810) {
        void* pActive = FUN_01021260();
        FUN_00ff2810(this, *(void**)((uint8_t*)pActive + 0x13c));
    }
    return true;
}

// ===========================================================================
// 0x00be3990 : face the agent held by one slot
// ===========================================================================
// @ 0x00be3990
bool cAgentAction::FaceSlot(uint32_t nSlot)
{
    uint8_t* pSlot = (uint8_t*)mCircleC4b4.SlotAt(nSlot);
    if (!pSlot || *pSlot != 0)
        return false;

    cNoun* pData = (cNoun*)FUN_00be1fb0();
    FUN_00afa030(pData, pSlot);
    cVec3 position;
    position.x = *(float*)(pSlot + 0x0c);
    position.y = *(float*)(pSlot + 0x10);
    position.z = *(float*)(pSlot + 0x14);
    pData->mSpatial.SetPosition(&position);

    cVec3 origin;
    cVec3* pRef = v058(&origin);
    cVec3 normal;
    normal.x = position.x - pRef->x;
    normal.y = position.y - pRef->y;
    normal.z = position.z - pRef->z;
    float fInv = 1.0f / sqrtf(normal.x * normal.x + normal.y * normal.y
                              + normal.z * normal.z + kZeroEpsilon);
    cVec3 dir;
    dir.x = normal.x * fInv;
    dir.y = normal.y * fInv;
    dir.z = normal.z * fInv;
    cMat4 orientation;
    pData->mSpatial.SetOrientation(SP_PlanetModel(&dir, &origin, &orientation)->BuildSurfaceOrientation2());
    return true;
}

// ===========================================================================
// 0x00be3ad0 : periodic repair pass over both agent lists
// ===========================================================================
// @ 0x00be3ad0
void cAgentAction::UpdateRepair()
{
    if (FUN_00c004c0(0))
        return;
    if (++mField7f0 >= 2)
        mField7f0 = 0;

    int32_t nCount = (int32_t)((uint8_t*)mAgents340.mpEnd - (uint8_t*)mAgents340.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount; ++i) {
        cNoun* pNoun = (cNoun*)mAgents340.mpBegin[i];
        if (pNoun->mCombatant.GetDamageState() == 2) {
            if (pNoun->GetTimerA() <= 30000 || pNoun->IsSpecial())
                continue;
            DestroyAgent(pNoun);
            continue;
        }
        float fThreshold = *(float*)((uint8_t*)pNoun + 0x158);
        if (fThreshold < pNoun->mCombatant.v058()) {
            pNoun->mCombatant.PartialRepair(kRepairFraction);
            if (mField7f0 != 0)
                continue;
            cVec3* pOrigin = pNoun->mSpatial.GetPosition();
            cVec3 normal;
            normal.x = pOrigin->x;
            normal.y = pOrigin->y;
            normal.z = pOrigin->z;
            float fInv = 1.0f / sqrtf(normal.x * normal.x + normal.y * normal.y
                                      + normal.z * normal.z + kZeroEpsilon);
            float fScale = *(float*)pNoun->mSpatial.v068() * kGrowFraction;
            normal.x = normal.x * fInv * fScale + normal.x;
            normal.y = normal.y * fInv * fScale + normal.y;
            normal.z = normal.z * fInv * fScale + normal.z;
            cEffectEmitter* pEmitter = (cEffectEmitter*)FUN_00b3d240();
            ResourceKey exclusions;
            void* pArg = pNoun->mSpatial.v05c(&exclusions);
            pEmitter->v060(0x3704925, &normal, pArg);
        }
    }

    int32_t nCount2 = (int32_t)((uint8_t*)mAgents354.mpEnd - (uint8_t*)mAgents354.mpBegin) >> 2;
    for (int32_t i = 0; i < nCount2; ++i) {
        cNoun* pNoun = (cNoun*)mAgents354.mpBegin[i];
        if (pNoun->mCombatant.GetDamageState() == 2) {
            if (pNoun->GetTimerB() <= 120000)
                continue;
            FUN_00be2070(pNoun, 0);
            continue;
        }
        float fThreshold = *(float*)((uint8_t*)pNoun + 0x5c0);
        if (fThreshold < pNoun->mCombatant.v058()) {
            pNoun->mCombatant.PartialRepair(kOne);
            if (mField7f0 != 0)
                continue;
            cEffectEmitter* pEmitter = (cEffectEmitter*)FUN_00b3d240();
            ResourceKey exclusions;
            cVec3* pOrigin = pNoun->mSpatial.GetPosition();
            void* pArg = pNoun->mSpatial.v05c(&exclusions);
            pEmitter->v060(0x3704925, pOrigin, pArg);
        }
    }
}

// ===========================================================================
// 0x00be3de0 : expire the three action timers
// ===========================================================================
// @ 0x00be3de0
void cAgentAction::UpdateTimers()
{
    if (mTimer230.IsRunning()) {
        if (!mTimer230.IsRunning() || mTimer230.GetElapsedTime() >= 120000) {
            int32_t nCount = (int32_t)((uint8_t*)mAgents340.mpEnd - (uint8_t*)mAgents340.mpBegin) >> 2;
            for (int32_t i = 0; i < nCount; ++i) {
                if (((cNoun*)mAgents340.mpBegin[i])->mCombatant.IsDeadOrDying())
                    break;
            }
            mTimer230.Stop();
            if (mpField810) {
                cNoun* pNoun = mpField810;
                mpField810 = 0;
                if (pNoun)
                    pNoun->v004();
            }
            FUN_00be2440(this, 0, 0);
        }
    }
    if (mTimer250.IsRunning()) {
        if (!mTimer250.IsRunning() || mTimer250.GetElapsedTime() >= 30000)
            mTimer250.Stop();
    }
    if (mTimer270.IsRunning()) {
        if (!mTimer270.IsRunning() || mTimer270.GetElapsedTime() >= mTimestamp290)
            mTimer270.Stop();
    }
}

// ===========================================================================
// 0x00be3f00 : integrate a fractional counter into the shared counter
// ===========================================================================
// @ 0x00be3f00
void cAgentAction::AdvanceFloatCounter(float fDelta)
{
    mField650 += fDelta;
    if (mField650 >= kOne) {
        do {
            if (mField64c <= 99) {
                ++mField64c;
                if (mpField590)
                    ++*mMap5a0[mpField590->v04c()];
            }
            mField650 -= kOne;
        } while (mField650 >= kOne);
    }
    if (mField650 <= kNegOne) {
        do {
            if (mField64c > 0 && mField64c > 20)
                --mField64c;
            mField650 += kOne;
        } while (mField650 <= kNegOne);
    }
}

// ===========================================================================
// 0x00be3fe0 : release every tracked noun reference
// ===========================================================================
// @ 0x00be3fe0
cRefList* cAgentAction::ClearRefs()
{
    mRefs0e4.erase(mRefs0e4.mpBegin, mRefs0e4.mpEnd);
    return &mRefs0e4;
}
