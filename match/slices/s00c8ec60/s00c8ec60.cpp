// Simulator tribe containers, hotspot search, tribe tools and tribe
// serialization helpers.

typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define nullptr 0

float fabs(float fValue);

// ---------------------------------------------------------------------------
// Small value types.
// ---------------------------------------------------------------------------
class cSPVector3 {
public:
    float mx;
    float my;
    float mz;
};

struct cSpeciesKey {
    uint32_t mnA;
    uint32_t mnB;
    uint32_t mnC;
};

void* operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                   const char* pFile, int32_t nLine);          // 0x00f473a0

// ---------------------------------------------------------------------------
// Spatial node used by the tribe members (embedded vtable object).
// ---------------------------------------------------------------------------
class cTransformNode {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual cSPVector3* GetPosition();                      // 0x02c
    virtual void v30(); virtual void v34();
    virtual void GetOrientation(cSPVector3* pOut);          // 0x038
    virtual void FUN_00c8f03c(void* pValue);                // 0x03c
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual cSPVector3* GetScale(cSPVector3* pOut);         // 0x05c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70();
    virtual float GetRadius();                              // 0x074

    bool Write(void* pStream);                              // 0x00c88a90
};

// ---------------------------------------------------------------------------
// Reference counted helper interfaces.
// ---------------------------------------------------------------------------
class cRefCounted {
public:
    virtual void v00();
    virtual void Release();                                 // 0x004
    virtual void v08();
    virtual void Disable(int32_t nA);                       // 0x00c
};

class cRefCountedNode {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(int32_t nA);
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void AddRef();                                  // 0x0bc
    virtual void Release();                                 // 0x0c0
};

// Block iterator used by the chunked pointer containers.
struct cPointerBlockIter {
    void** mpCur;                                           // 0x00
    void** mpBegin;                                         // 0x04
    void** mpEnd;                                           // 0x08
    void** mpBlockIt;                                       // 0x0c
};

class cPointerVector {
public:
    cPointerVector* Init(int32_t nCount, int32_t nUnused);  // 0x00c8ed30

    void** mpBegin;                                         // 0x00
    void** mpEnd;                                           // 0x04
    void** mpCapEnd;                                        // 0x08
};

// Holder with an embedded node at +0x34.
class cSpatialThing {
public:
    uint8_t mPad000[0x34];                                  // 0x000
    cTransformNode mNode;                                   // 0x034
};

// Creature sub objects used by the tribe iteration routines.
class cCombatantNode {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual float GetValue58();                             // 0x058

    void SetValue(float fValue);                            // 0x00f924e0
};

class cTreeStimuli {
public:
    void* Play(int32_t nA, void* pB, float fC, void* pD);   // 0x00bc97f0
    void ClearAll(int32_t nA, int32_t nB);                  // 0x00bc98f0

    uint8_t mPad000[0x1c0];                                 // 0x000
    uint32_t mnField1C0;                                    // 0x1c0
};

class cBehaviorTree {
public:
    uint8_t mPad000[0x08];                                  // 0x000
    cTreeStimuli mStimuli;                                  // 0x008
};

class cStimulusEntry {
public:
    uint8_t mPad000[0x0c];                                  // 0x000
    int32_t mnField0C;                                      // 0x00c
    int32_t mnField10;                                      // 0x010
    cSPVector3 mPosition;                                   // 0x014
};

class cCreature {
public:
    uint8_t mPad000[0xc0];                                  // 0x000
    cTransformNode mNode;                                   // 0x0c0
    uint8_t mPad0C4[0x4e4];                                 // 0x0c4
    cCombatantNode mCombatant;                              // 0x5a8
    uint8_t mPad5AC[0x5a0];                                 // 0x5ac
    cBehaviorTree* mpBehaviorTree;                          // 0xb4c

    bool IsLeader();                                        // 0x00c232d0
    void FUN_00c0b9d0(float fValue);                        // 0x00c0b9d0
};

class cGameNounManager {
public:
    void RemoveNoun(void* pNoun);                           // 0x00b225d0
};

cGameNounManager* NounManager();                            // 0x00b3d300
cGameNounManager* __stdcall NounManagerOf(void* pNoun);     // 0x00b3d300

class cValueNode {
public:
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28();
    virtual void* SetValue(float fValue);                   // 0x02c
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void w40(); virtual void w44(); virtual void w48(); virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68(); virtual void w6c();
    virtual void w70();
    virtual float FUN_00c8f074(float fValue, void* pValue);    // 0x074
};

class cValueOwner {
public:
    virtual void x00(); virtual void x04(); virtual void x08();
    virtual void* GetChild();                               // 0x008
    virtual void* GetValue(void* pThis);                    // 0x00c
};

class cStreamHolder {
public:
    virtual void z00(); virtual void z04(); virtual void z08(); virtual void z0c();
    virtual void z10(); virtual void z14();
    virtual void* GetStream();                              // 0x018
};

class cOutStream {
public:
    virtual void y00(); virtual void y04(); virtual void y08(); virtual void y0c();
    virtual void y10(); virtual void y14(); virtual void y18(); virtual void y1c();
    virtual cStreamHolder* GetHolder();                     // 0x020
};

class cResultOwner {
public:
    void FUN_00bc8400();                                    // 0x00bc8400
};

// ---------------------------------------------------------------------------
// Tribe.
// ---------------------------------------------------------------------------
class cTribe {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void** GetAgents();                             // 0x090
    virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0();
    virtual cSpatialThing* GetThing(int32_t nType);         // 0x0b4

    class cCreature* PickAPeon();
    class cTool* GetToolOfType(int32_t nType);
    int32_t GetAdultPopulation();
    int32_t FUN_00c8f3a0();
    void FUN_00c8f3d0(int32_t nA1, void* pA2, float fA3, void* pA4,
                      cSPVector3* pA5, uint32_t nA6);
    void SetStimuli(int32_t nA1, int32_t nA2, float fA3, void* pA4);
    void FUN_00c8f540(cSPVector3* pPosition, float fRadius, int32_t nA, void* pB,
                      void* pC, void* pD);
    void FUN_00c8f660(int32_t nValue);
    bool FUN_00c8f730(int32_t nId);
    void ResetDefaultToolPlacement(int32_t nType);
    bool Write(void* pStream);
    bool FUN_00c8fa60();
    void FUN_00c8fb50();

    uint32_t FUN_00c8e990();                                // 0x00c8e990

    uint8_t mPad004[0x11c];                                 // 0x004
    cTransformNode mNode;                                   // 0x120
    uint8_t mPad124[0xe8];                                  // 0x124
    cTransformNode mNode2;                                  // 0x20c
    uint8_t mPad210[0x20];                                  // 0x210
    cTransformNode mNode3;                                  // 0x230
    uint8_t mPad234[0x94];                                  // 0x234
    float mfField2C8;                                       // 0x2c8
    uint8_t mPad2CC[0x68];                                  // 0x2cc
    uint8_t mbField334;                                     // 0x334
    uint8_t mPad335[0x03];                                  // 0x335
    int32_t mnField338;                                     // 0x338
    uint8_t mbField33C;                                     // 0x33c
    uint8_t mPad33D[0x03];                                  // 0x33d
    cCreature** mppPeonBegin;                               // 0x340
    cCreature** mppPeonEnd;                                 // 0x344
    uint8_t mPad348[0x0c];                                  // 0x348
    uint32_t mnField354;                                    // 0x354
    uint32_t mnField358;                                    // 0x358
    uint8_t mPad35C[0x10];                                  // 0x35c
    void** mppToolBegin;                                    // 0x36c
    void** mppToolEnd;                                      // 0x370
    uint8_t mPad374[0x1558];                                // 0x374
    void* mpField18CC;                                      // 0x18cc
    void* mpField18D0[14];                                  // 0x18d0
    cSpeciesKey* mpKeys;                                    // 0x1904
    uint8_t mPad1908[0xbc];                                 // 0x1908
    cRefCountedNode* mpField19C4;                           // 0x19c4
    cRefCountedNode* mpField19C8;                           // 0x19c8
    cRefCountedNode* mpField19CC;                           // 0x19cc
    cRefCountedNode* mpField19D0;                           // 0x19d0
};

class cTool {
public:
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
    virtual void t30(); virtual void t34(); virtual void t38(); virtual void t3c();
    virtual void t40(); virtual void t44(); virtual void t48(); virtual void t4c();
    virtual void t50(); virtual void t54();
    virtual int32_t GetType();                              // 0x058

    int32_t GetId();                                        // 0x00c9d110
};

class cCommunity {
public:
    void func58h(int32_t nA);                               // 0x00c8f2b0
    void func58hBase(int32_t nA);                           // 0x00c886d0

    uint8_t mPad000[0x248];                                 // 0x000
    cSpatialThing* mpField248;                              // 0x248
};

class cSpeciesManager {
public:
    bool GetReplacementKey(const cSpeciesKey& key, uint32_t nId, cSpeciesKey* pOut);   // 0x004df7d0
    void* GetProfile(const cSpeciesKey& key);                                           // 0x004df550
};

class cVarListSerializer {
public:
    cVarListSerializer(cTribe* pOwner, const void* pVarList, int32_t nFlags);   // 0x00692f90
    bool Serialize(void* pStream);                                             // 0x00692900

    uint8_t mPad000[0xa00];                                 // 0x000
};

class cValueSink {
public:
    void FUN_00ac7ab0();                                    // 0x00ac7ab0
    float FUN_00ac7d10();                                   // 0x00ac7d10
};

void* __stdcall FUN_00b3d2b0(float fValue, void* pTarget, uint32_t nId);   // 0x00b3d2b0
void* FUN_00bc8000(uint32_t nId, void* pValue);                     // 0x00bc8000
void* FUN_00bc8400(uint32_t nId, void* pValue);                     // 0x00bc8400
void* FUN_00bc97f0(int32_t nA1, void* pA2, float fA3, void* pA4);   // 0x00bc97f0
void* FUN_00ba5df0(void* pKeys, cSpeciesKey* pKey);                 // 0x00ba5df0
void* SP_CoordToIndex(void* pOut, int32_t nSize, float* pCoords);  // 0x00684bf0
void* PlanetModel(void* pOut, const void* pElement, const void* pExtra);   // 0x00b3d350
void* GetSetting9();                                                // 0x00401090
bool FUN_00c24560(cCreature* pCreature);                            // 0x00c24560
bool FUN_00c005b0(cTribe* pTribe, void* pStream);                   // 0x00c005b0
bool FUN_00b6e2d0(cTransformNode* pNode, void* pStream);            // 0x00b6e2d0
bool FUN_00cee3d0(cTransformNode* pNode, void* pStream);            // 0x00cee3d0
void* EA_WriteUint32(void* pStream, const uint32_t* pValue, int32_t nCount, int32_t nA);   // 0x0093aa70

// ---------------------------------------------------------------------------
// Hot spot table used by the closest hot spot search.
// ---------------------------------------------------------------------------
struct cHotSpot {
    uint8_t mPad000[0x08];                                  // 0x000
    cSPVector3 mPosition;                                   // 0x008
    float mfField14;                                        // 0x014
    uint8_t mPad018[0x08];                                  // 0x018
    uint32_t mnField20;                                     // 0x020
    uint32_t mnField24;                                     // 0x024
    uint32_t mnField28;                                     // 0x028
    uint8_t mPad02C[0x14];                                  // 0x02c
    uint8_t mbField40;                                      // 0x040
    uint8_t mPad041[0x1f];                                  // 0x041
};

cHotSpot* g_pHotSpotBegin = nullptr;
cHotSpot* g_pHotSpotEnd = nullptr;
float g_fOne = 1.0f;
float g_fHotSpotValue = 1.0f;
const char g_szSimulator[] = "Simulator";
const char g_szAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---------------------------------------------------------------------------
// 0x00c8ec60
// ---------------------------------------------------------------------------
// @ 0x00c8ec60
void FUN_00c8ec60(void** pBegin, void** pEnd, void** ppObject)
{
    if (pBegin != pEnd) {
        void* pObject = *ppObject;
        do {
            void* pTarget = (pObject != nullptr) ? (void*)((uint8_t*)pObject + 0xc0) : nullptr;
            if (*pBegin == pTarget)
                break;
            ++pBegin;
        } while (pBegin != pEnd);
    }
}

// ---------------------------------------------------------------------------
// 0x00c8ecb0
// ---------------------------------------------------------------------------
// @ 0x00c8ecb0
void FUN_00c8ecb0(void** pOut, void** pCurrent, void** pBegin, void** pEnd,
                  void** pBlockIt, void** pStop, void* pA7, void* pA8,
                  void* pUnused9, void** ppValue)
{
    if (pCurrent != pStop) {
        for (;;) {
            if (*pCurrent == *ppValue)
                break;

            ++pCurrent;
            if (pCurrent == pEnd) {
                ++pBlockIt;
                pCurrent = (void**)*pBlockIt;
                pEnd = pCurrent + 0x40;
                pBegin = pCurrent;
            }

            if (pCurrent == pStop)
                break;
        }
    }

    pOut[2] = pEnd;
    pOut[3] = pBlockIt;
    pOut[0] = pCurrent;
    pOut[1] = pBegin;
}

// ---------------------------------------------------------------------------
// 0x00c8ed30
// ---------------------------------------------------------------------------
// @ 0x00c8ed30
cPointerVector* cPointerVector::Init(int32_t nCount, int32_t nUnused)
{
    int32_t* pData;
    if (nCount != 0) {
        pData = (int32_t*)operator_new(nCount * 0x1c, g_szSimulator, 0, 0,
                                       g_szAllocatorFile, 0xd1);
    }
    else {
        pData = nullptr;
    }

    mpBegin = (void**)pData;
    mpEnd = (void**)pData;
    mpCapEnd = (void**)(pData + nCount * 7);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00c8ed90
// ---------------------------------------------------------------------------
// @ 0x00c8ed90
cPointerBlockIter* FUN_00c8ed90(cPointerBlockIter* pOut, void** pCurrent, void* pA3,
                                void** pEnd, void** ppBlock, void** pStop, void* pA7,
                                void* pA8, void* pA9, void** pBlockCur, void** pBlockBegin,
                                void** pBlockEnd, void** pBlockIt)
{
    pOut->mpBegin = pBlockBegin;
    pOut->mpCur = pBlockCur;
    pOut->mpEnd = pBlockEnd;
    pOut->mpBlockIt = pBlockIt;

    while (pCurrent != pStop) {
        if (pOut->mpCur != nullptr) {
            void* pValue = *pCurrent;
            *pOut->mpCur = pValue;
            if (pValue != nullptr)
                ((cRefCountedNode*)pValue)->v00();
        }

        ++pCurrent;
        if (pCurrent == pEnd) {
            ++ppBlock;
            pCurrent = (void**)*ppBlock;
            pEnd = pCurrent + 0x40;
        }

        pOut->mpCur = pOut->mpCur + 1;
        if (pOut->mpCur == pOut->mpEnd) {
            pOut->mpBlockIt = pOut->mpBlockIt + 1;
            void** pNext = (void**)*pOut->mpBlockIt;
            pOut->mpBegin = pNext;
            pOut->mpEnd = pNext + 0x40;
            pOut->mpCur = pNext;
        }
    }

    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00c8ee40
// ---------------------------------------------------------------------------
// @ 0x00c8ee40
void** FUN_00c8ee40(void** pBegin, void** pEnd, void** pOut)
{
    if (pBegin == pEnd)
        return pOut;

    do {
        cRefCountedNode* pSource = (*pBegin != nullptr)
                                       ? (cRefCountedNode*)((uint8_t*)*pBegin + 0x34)
                                       : nullptr;
        cRefCountedNode* pOld = (cRefCountedNode*)*pOut;
        if (pSource != pOld) {
            if (pSource != nullptr)
                pSource->AddRef();
            *pOut = pSource;
            if (pOld != nullptr)
                pOld->Release();
        }

        ++pBegin;
        ++pOut;
    } while (pBegin != pEnd);

    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00c8eeb0
// ---------------------------------------------------------------------------
// @ 0x00c8eeb0
void** FUN_00c8eeb0(void** pBegin, void** pEnd, void** pOut)
{
    if (pEnd == pBegin)
        return pOut;

    do {
        --pEnd;
        --pOut;

        cRefCountedNode* pSource = (*pEnd != nullptr)
                                       ? (cRefCountedNode*)((uint8_t*)*pEnd + 0x34)
                                       : nullptr;
        cRefCountedNode* pOld = (cRefCountedNode*)*pOut;
        if (pSource != pOld) {
            if (pSource != nullptr)
                pSource->AddRef();
            *pOut = pSource;
            if (pOld != nullptr)
                pOld->Release();
        }
    } while (pEnd != pBegin);

    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00c8ef20
// ---------------------------------------------------------------------------
// @ 0x00c8ef20
void cSpatialThing_FUN_00c8ef20(cSpatialThing* pThis, cSPVector3* pOut)
{
    cTransformNode* pNode = &pThis->mNode;
    float fRadius = pNode->GetRadius();

    cSPVector3 aOrientation;
    cSPVector3* pOrientation = pNode->GetScale(&aOrientation);

    cSPVector3* pPosition = pThis->mNode.GetPosition();

    pOut->mx = pPosition->mx + fRadius * pOrientation->mx;
    pOut->my = pPosition->my + fRadius * pOrientation->my;
    pOut->mz = pPosition->mz + fRadius * pOrientation->mz;
}

// ---------------------------------------------------------------------------
// 0x00c8efc0
// ---------------------------------------------------------------------------
// @ 0x00c8efc0
void cTribe_FUN_00c8efc0(cTribe* pThis)
{
    if (pThis->mppToolBegin != nullptr) {
        NounManagerOf(pThis->mppToolBegin)->RemoveNoun(pThis->mppToolBegin);
        if (pThis->mppToolBegin != nullptr) {
            cRefCounted* pNoun = (cRefCounted*)pThis->mppToolBegin;
            pThis->mppToolBegin = nullptr;
            pNoun->Release();
        }
    }

    if (pThis->mppToolEnd != nullptr) {
        NounManagerOf(pThis->mppToolEnd)->RemoveNoun(pThis->mppToolEnd);
        if (pThis->mppToolEnd != nullptr) {
            cRefCounted* pNoun = (cRefCounted*)pThis->mppToolEnd;
            pThis->mppToolEnd = nullptr;
            pNoun->Release();
        }
    }

    if (pThis->mpField19C4 != nullptr) {
        pThis->mpField19C4->v0c(1);
        if (pThis->mpField19C4 != nullptr) {
            cRefCountedNode* pNode = pThis->mpField19C4;
            pThis->mpField19C4 = nullptr;
            pNode->Release();
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c8f040 SP::cTribe::HotSpotGetClosest
// ---------------------------------------------------------------------------
// @ 0x00c8f040
int32_t HotSpotGetClosest(cSPVector3* pPosition, float fRadius)
{
    float fX = pPosition->mx;
    float fY = pPosition->my;
    float fZ = pPosition->mz;
    float fAbsX = fabs(fX);
    float fAbsY = fabs(fY);
    float fAbsZ = fabs(fZ);

    float fU;
    float fV;
    uint32_t nFace;

    if (fAbsZ < fAbsX || fAbsZ < fAbsY) {
        if (fAbsY < fAbsX) {
            fU = (fY / fX + 1.0f) * 0.5f;
            fV = (fZ / fAbsX + 1.0f) * 0.5f;
            nFace = 2;
            if (fX < 0.0f)
                nFace = 3;
        }
        else {
            fU = (fZ / fY + 1.0f) * 0.5f;
            fV = (fX / fAbsY + 1.0f) * 0.5f;
            if (fY < 0.0f)
                nFace = 5;
            else
                nFace = 4;
        }
    }
    else {
        fU = (fX / fZ + 1.0f) * 0.5f;
        fV = (fY / fAbsZ + 1.0f) * 0.5f;
        if (fZ < 0.0f)
            nFace = 1;
        else
            nFace = 0;
    }

    uint8_t aCoords[12];
    uint32_t anIndices[3];
    float aFace[3];
    aFace[0] = fU;
    aFace[1] = fV;
    aFace[2] = (float)nFace;
    SP_CoordToIndex(aCoords, 0x80, aFace);
    (void)anIndices;

    int32_t nBest = -1;
    bool bFound = false;
    float fBestSq = fRadius * fRadius;

    for (cHotSpot* pSpot = g_pHotSpotBegin; pSpot != g_pHotSpotEnd; ++pSpot) {
        if (pSpot->mbField40 == 0)
            continue;

        float fDx = pSpot->mPosition.mx - pPosition->mx;
        float fDy = pSpot->mPosition.my - pPosition->my;
        float fDz = pSpot->mPosition.mz - pPosition->mz;
        float fDistSq = fDz * fDz + fDy * fDy + fDx * fDx;

        if (!(fDistSq < fBestSq))
            continue;

        if (!bFound) {
            if (g_fOne < pSpot->mfField14) {
                nBest = ((pSpot->mnField20 & 0xffff8fff) + (pSpot->mnField28 << 13)) * 0x10000 +
                        pSpot->mnField24;
                bFound = true;
            }
            else {
                nBest = ((pSpot->mnField20 & 0xffff8fff) + (pSpot->mnField28 << 13)) * 0x10000 +
                        pSpot->mnField24;
            }
            fBestSq = fDistSq;
        }
        else if (g_fOne < pSpot->mfField14) {
            nBest = ((pSpot->mnField20 & 0xffff8fff) + (pSpot->mnField28 << 13)) * 0x10000 +
                    pSpot->mnField24;
            fBestSq = fDistSq;
        }
    }

    return nBest;
}

// ---------------------------------------------------------------------------
// 0x00c8f2b0 Simulator::cCommunity::func58h
// ---------------------------------------------------------------------------
// @ 0x00c8f2b0
void cCommunity::func58h(int32_t nA)
{
    func58hBase(nA);

    cSpatialThing* pThing = mpField248;
    if (pThing != nullptr)
        pThing->mNode.FUN_00c8f03c((void*)nA);
}

// ---------------------------------------------------------------------------
// 0x00c8f2e0
// ---------------------------------------------------------------------------
// @ 0x00c8f2e0
cSPVector3* __stdcall FUN_00c8f2e0(cSPVector3* pOut, cSpatialThing* pThing)
{
    cSPVector3* pPosition = pThing->mNode.GetPosition();

    pOut->mx = pPosition->mx;
    pOut->my = pPosition->my;
    pOut->mz = pPosition->mz;
    return pOut;
}

// ---------------------------------------------------------------------------
// 0x00c8f310 SP::cTribe::PickAPeon
// ---------------------------------------------------------------------------
// @ 0x00c8f310
cCreature* cTribe::PickAPeon()
{
    for (cCreature** ppIt = mppPeonBegin; ppIt != mppPeonEnd; ++ppIt) {
        cCreature* pPeon = *ppIt;
        if (pPeon != nullptr) {
            if (!pPeon->IsLeader())
                return pPeon;
        }
    }

    cCreature** ppFirst = mppPeonBegin;
    if (ppFirst != mppPeonEnd)
        return *ppFirst;

    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c8f370 SP::cTribe::GetAdultPopulation
// ---------------------------------------------------------------------------
// @ 0x00c8f370
int32_t cTribe::GetAdultPopulation()
{
    if (mbField334 != 0 && mbField33C == 0)
        return mnField338;

    return (int32_t)(mnField358 - mnField354) >> 2;
}

// ---------------------------------------------------------------------------
// 0x00c8f3a0
// ---------------------------------------------------------------------------
// @ 0x00c8f3a0
int32_t cTribe::FUN_00c8f3a0()
{
    if (mbField334 != 0 && mbField33C == 0)
        return mnField338;

    uint32_t* pList = (uint32_t*)GetAgents();
    return (int32_t)(pList[1] - pList[0]) >> 2;
}

// ---------------------------------------------------------------------------
// 0x00c8f3d0
// ---------------------------------------------------------------------------
// @ 0x00c8f3d0
void cTribe::FUN_00c8f3d0(int32_t nA1, void* pA2, float fA3, void* pA4,
                          cSPVector3* pA5, uint32_t nA6)
{
    uint32_t* pList = (uint32_t*)GetAgents();

    for (uint32_t* pIt = (uint32_t*)pList[0]; pIt != (uint32_t*)pList[1]; ++pIt) {
        cCreature* pCreature = (cCreature*)*pIt;
        if (!FUN_00c24560(pCreature))
            continue;
        if (pCreature->mpBehaviorTree == nullptr)
            continue;

        cStimulusEntry* pEntry =
            (cStimulusEntry*)pCreature->mpBehaviorTree->mStimuli.Play(nA1, pA4, fA3, nullptr);
        pEntry->mnField0C = (int32_t)pA4;
        pEntry->mnField10 = (int32_t)nA6;
        pEntry->mPosition = *pA5;
    }
}

// ---------------------------------------------------------------------------
// 0x00c8f470 SP::cTribe::SetStimuli
// ---------------------------------------------------------------------------
// @ 0x00c8f470
void cTribe::SetStimuli(int32_t nA1, int32_t nA2, float fA3, void* pA4)
{
    uint32_t* pList = (uint32_t*)GetAgents();

    for (uint32_t* pIt = (uint32_t*)pList[0]; pIt != (uint32_t*)pList[1]; ++pIt) {
        cCreature* pCreature = (cCreature*)*pIt;
        pCreature->mpBehaviorTree->mStimuli.Play(nA1, (void*)nA2, fA3, pA4);
    }

    if (pA4 != nullptr && nA1 == 0 && nA2 == 0x4000) {
        cValueOwner* pOwner = (cValueOwner*)pA4;
        cValueOwner* pValue = (cValueOwner*)pOwner->GetValue(this);
        if (pValue != nullptr) {
            cValueNode* pFirst = (cValueNode*)pValue->GetChild();
            cValueNode* pSecond = (cValueNode*)pValue->GetChild();
            void* pAux = pValue->GetValue(this);

            float fScaled = pFirst->FUN_00c8f074(fA3, pAux);
            void* pResult = pSecond->SetValue(fScaled);
            cResultOwner* pOwner = (cResultOwner*)FUN_00bc8000(0xb9d14c31, pResult);
            pOwner->FUN_00bc8400();
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00c8f540
// ---------------------------------------------------------------------------
// @ 0x00c8f540
void cTribe::FUN_00c8f540(cSPVector3* pPosition, float fRadius, int32_t nA,
                          void* pB, void* pC, void* pD)
{
    uint32_t* pList = (uint32_t*)GetAgents();

    for (uint32_t* pIt = (uint32_t*)pList[0]; pIt != (uint32_t*)pList[1]; ++pIt) {
        cCreature* pCreature = (cCreature*)*pIt;
        cTransformNode* pNode = &pCreature->mNode;

        cSPVector3* pMemberPosition = pNode->GetPosition();
        float fDx = pMemberPosition->mx - pPosition->mx;
        float fDy = pMemberPosition->my - pPosition->my;
        float fDz = pMemberPosition->mz - pPosition->mz;

        float fMemberRadius = pNode->GetRadius();
        float fLimit = fMemberRadius + fRadius;

        float fDistSq = fDz * fDz + fDy * fDy + fDx * fDx;
        if (!(fLimit * fLimit > fDistSq))
            continue;

        cStimulusEntry* pEntry =
            (cStimulusEntry*)pCreature->mpBehaviorTree->mStimuli.Play(nA, pB, (float)(int32_t)pC, pD);
        pEntry->mPosition = *pPosition;
        pEntry->mnField0C = (int32_t)fRadius;
        (void)fMemberRadius;
    }
}

// ---------------------------------------------------------------------------
// 0x00c8f660
// ---------------------------------------------------------------------------
// @ 0x00c8f660
void cTribe::FUN_00c8f660(int32_t nValue)
{
    if (nValue > 0) {
        cTransformNode* pNode = (this != nullptr) ? &mNode2 : nullptr;
        uint32_t nId = FUN_00c8e990();
        cValueSink* pSink = (cValueSink*)FUN_00b3d2b0((float)nValue, pNode, nId);
        pSink->FUN_00ac7ab0();
        return;
    }

    if (nValue != 0) {
        cTransformNode* pNode = (this != nullptr) ? &mNode2 : nullptr;
        cValueSink* pSink = (cValueSink*)FUN_00b3d2b0((float)-nValue, pNode, 0);
        pSink->FUN_00ac7d10();
    }
}

// ---------------------------------------------------------------------------
// 0x00c8f6e0 SP::cTribe::GetToolOfType
// ---------------------------------------------------------------------------
// @ 0x00c8f6e0
cTool* cTribe::GetToolOfType(int32_t nType)
{
    for (void** ppIt = mppToolBegin; ppIt != mppToolEnd; ++ppIt) {
        cTool* pTool = (cTool*)*ppIt;
        if (pTool != nullptr) {
            if (nType == pTool->GetType())
                return pTool;
        }
    }

    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x00c8f730
// ---------------------------------------------------------------------------
// @ 0x00c8f730
bool cTribe::FUN_00c8f730(int32_t nId)
{
    for (void** ppIt = mppToolBegin; ppIt != mppToolEnd; ++ppIt) {
        cTool* pTool = (cTool*)*ppIt;
        if (nId == pTool->GetId())
            return true;
    }

    return false;
}

// ---------------------------------------------------------------------------
// 0x00c8f770 SP::cTribe::ResetDefaultToolPlacement
// ---------------------------------------------------------------------------
// @ 0x00c8f770
void cTribe::ResetDefaultToolPlacement(int32_t nType)
{
    if (GetToolOfType(nType) != nullptr)
        return;

    cSPVector3 aPosition = *mNode.GetPosition();

    cSpatialThing* pThing = GetThing(nType);
    pThing->mNode.FUN_00c8f03c(this);

    cSPVector3 aScale;
    cSPVector3* pScale = mNode.GetScale(&aScale);

    cSPVector3 aOrientation;
    void* pSurface = PlanetModel(&aOrientation, &aPosition, pScale);
    ((cSpatialThing*)pSurface)->mNode.GetOrientation(&aOrientation);

    cTransformNode* pNode = &pThing->mNode;
    pNode->GetOrientation(&aPosition);
    pNode->FUN_00c8f03c(&aScale);
}

// ---------------------------------------------------------------------------
// 0x00c8f820 SP::cTribe::Write
// ---------------------------------------------------------------------------
// @ 0x00c8f820
bool cTribe::Write(void* pStream)
{
    cOutStream* pOut = (cOutStream*)pStream;
    uint32_t nMagic = 0x4f396a66;
    EA_WriteUint32(pOut->GetHolder()->GetStream(), &nMagic, 1, 0);

    bool bOk = false;
    if (FUN_00c005b0(this, pStream)) {
        if (mNode.Write(pStream)) {
            if (FUN_00cee3d0(&mNode2, pStream)) {
                if (FUN_00c005b0(this, pStream)) {
                    if (FUN_00b6e2d0(&mNode3, pStream))
                        bOk = true;
                }
            }
        }
    }

    void** ppObjects = &mpField18CC;
    cSpeciesKey* pKeys = mpKeys;
    for (int32_t i = 0; i < 7; ++i) {
        void* pFirst = ppObjects[i * 2];
        void* pSecond = ppObjects[i * 2 + 1];

        if (pFirst != nullptr)
            pKeys[i].mnA = *(uint32_t*)((uint8_t*)pFirst + 0x504);
        else
            pKeys[i].mnA = 0;

        if (pSecond != nullptr) {
            pKeys[i].mnB = *(uint32_t*)((uint8_t*)pSecond + 0x504);
            pKeys[i].mnC = *(uint32_t*)((uint8_t*)pSecond + 0x508);
        }
        else {
            pKeys[i].mnB = 0;
            pKeys[i].mnC = 0;
        }
    }

    cRefCountedNode** apNodes[4];
    apNodes[0] = &mpField19C4;
    apNodes[1] = &mpField19C8;
    apNodes[2] = &mpField19CC;
    apNodes[3] = &mpField19D0;
    for (int32_t i = 0; i < 4; ++i) {
        cRefCountedNode* pNode = *apNodes[i];
        if (pNode == nullptr)
            continue;
        pNode->v2c();
        pNode = *apNodes[i];
        if (pNode == nullptr)
            continue;
        *apNodes[i] = nullptr;
        pNode->Release();
    }

    cVarListSerializer serializer(this, &g_szSimulator, 0x1a80d26);
    if (bOk) {
        if (serializer.Serialize(pStream))
            return true;
    }

    return false;
}

// ---------------------------------------------------------------------------
// 0x00c8fa60
// ---------------------------------------------------------------------------
// @ 0x00c8fa60
bool cTribe::FUN_00c8fa60()
{
    cSpeciesManager* pManager = (cSpeciesManager*)GetSetting9();

    if (mpField18CC != nullptr)
        return true;

    cSpeciesKey aKey;
    if (!pManager->GetReplacementKey(*mpKeys, 0xbbaaecee, &aKey))
        return true;

    aKey.mnA = 0;
    aKey.mnB = 0;
    aKey.mnC = 0;
    pManager->GetReplacementKey(*mpKeys, 0xbbaaecee, &aKey);

    FUN_00ba5df0(mpKeys, &aKey);
    *mpKeys = aKey;

    mpField18CC = pManager->GetProfile(aKey);

    for (int32_t i = 1; i < 14; ++i) {
        if (*(uint32_t*)((uint8_t*)mpKeys + i * 0xc) != 0 && mpField18D0[i - 1] == nullptr) {
            *(cSpeciesKey*)((uint8_t*)mpKeys + i * 0xc) = *mpKeys;
            mpField18D0[i - 1] = mpField18CC;
        }
    }

    return true;
}

// ---------------------------------------------------------------------------
// 0x00c8fb50
// ---------------------------------------------------------------------------
// @ 0x00c8fb50
void cTribe::FUN_00c8fb50()
{
    cCreature** pPeonEnd = mppPeonEnd;

    for (cCreature** ppIt = mppPeonBegin; ppIt != pPeonEnd; ++ppIt) {
        cCreature* pPeon = *ppIt;
        pPeon->FUN_00c0b9d0(g_fHotSpotValue);

        float fValue = pPeon->mCombatant.GetValue58();
        pPeon->mCombatant.SetValue(fValue);
    }

    mfField2C8 = 0.0f;
}
