// =============================================================================================
// SporeApp.exe slice s00d39800  (batch gold7, worker 5)
//
// 11 routines from the Simulator creature-mode / collision-callback area:
//
//   0x00d39800  SP::cCreatureModeStrategy::Write - variable-list serialisation
//   0x00d399b0  SP::cCreatureModeStrategy::RunCinematicIfNotOccurred
//   0x00d39a10  SP::cCreatureModeTuning::LoadPrivateTuningVariables
//   0x00d39c30  creature-mode hashtable rehash helper
//   0x00d39d50  sift-down helper for 8-byte key/value pairs
//   0x00d39f70  locating-call effect spawner
//   0x00d3a0d0  SP::NotifyNounCreatureCollision
//   0x00d3a450  creature-mode collision callback dispatch
//   0x00d3a5a0  creature-mode telemetry EvaluateEvent
//   0x00d3a710  creature-mode strategy predicate from a property set
//   0x00d3a7f0  creature-mode module registration
//
// Layout: offsets are taken from the disassembly of this build. Every touched field is named.
// Flags: /O2 /Ob2 /MD /Gy /TP /arch:SSE /GS-
// =============================================================================================
#include "types.h"

// ---------------------------------------------------------------------------------------------
// external helpers (retail addresses; not defined here)
// ---------------------------------------------------------------------------------------------
void*   __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                             const char* pFile, int32_t nLine);                 // 0x00f473a0
void    __cdecl operator_delete(void* pBlock);                                  // 0x00f47380

bool    __cdecl WriteUint32(void* pStream, void* pSrc, uint32_t nCount, int32_t nEndian); // 0x0093aa70

void*   __cdecl ConfigManager();                                                // 0x0067dd30
void*   __cdecl EffectsManagerPtr();                                            // 0x0067ddd0
void*   __cdecl PropertyManager();                                              // 0x0067de30
void*   __cdecl NounManager();                                                  // 0x00b3d300
void*   __fastcall GetAvatar(void* pManager);                                   // 0x00b1fdb0 (ecx = manager)

// a serialisable property object; GetFloat/GetInt are __thiscall members
class cProperty {
public:
    uint8_t  mPad00[0x12];                          // +0x00
    int16_t  mnType;                                // +0x12  (0xd == float property)
    float*   GetFloat();                            // 0x0041ea70
    int32_t* GetInt();                              // 0x0041e990
};

void    __cdecl Matrix3Assign(void* pDst, const void* pSrc);                    // 0x0041cb40
void*   __cdecl PlanetModel(void* pOut, const void* pSrc);                      // 0x00b3d350
void    __cdecl BuildSurfaceOrientation(void* pPlanet, const void* pMatrix);    // 0x00b7f190
void*   __cdecl Matrix3FromQuaternion(void* pOut, const void* pQuat);           // 0x0059c190
void    __cdecl SpawnLocatingCallResponse(void* pAvatar, const void* pParam);   // 0x00d38cc0

// ---------------------------------------------------------------------------------------------
// image data / tuning globals
// ---------------------------------------------------------------------------------------------
extern void*    g_sTestSystem;                                              // 0x015fd928
extern float    g_fTuning90;                                                // 0x01582e90
extern float    g_fTuning94;                                                // 0x01582e94
extern float    g_fTuning98;                                                // 0x01582e98
extern float    g_fTuning9c;                                                // 0x01582e9c
extern float    g_fTuningA0;                                                // 0x01582ea0
extern float    g_fTuningA4;                                                // 0x01582ea4
extern float    g_fTuningA8;                                                // 0x01582ea8
extern float    g_fTuningAC;                                                // 0x01582eac
extern void*    g_pLocatingEffect;                                          // 0x0169e2d4
extern float    g_fLocX;                                                    // 0x0169e308
extern float    g_fLocY;                                                    // 0x0169e30c
extern float    g_fLocZ;                                                    // 0x0169e310
extern uint8_t  g_locMatrix;                                                // 0x0169e2e4
extern float    g_fRealOne;                                                 // 0x01485720

// collision + creature-mode globals/helpers
extern float    g_fEps38;                                                   // 0x01582f38
extern float    g_fVal40;                                                   // 0x01582f40
extern float    g_fVal44;                                                   // 0x01582f44
extern float    g_fVal48;                                                   // 0x01582f48
extern float    g_fVal3c;                                                   // 0x01582f3c
extern float    g_fValAc4;                                                  // 0x01550ac4
extern void*    g_pModeInstance;                                            // 0x0169e294

void*  __cdecl NormalizedSafe(void* pOut, const float* pIn, int32_t nPad);  // 0x00449c20
float  __declspec(noinline) Sqrtf(float f)
{
    __asm {
        fld   f
        fsqrt
        fstp  f
    }
    return f;
}
void*  __cdecl PlayIdleAnimation(void* pBase, int32_t nA, int32_t nB);      // 0x00bc96a0
void*  __cdecl FUN_00ac80d0(void* pA, uint32_t nKey);                       // 0x00ac80d0
uint32_t __cdecl FUN_00b18e00(void* pA);                                    // 0x00b18e00
int32_t __cdecl FUN_00c0f8f0(void* pCreature, uint32_t nKey);               // 0x00c0f8f0
float  __cdecl GetPropertyTFloat(void* pSet, uint32_t nKey, float fDefault); // 0x004e1c70
void   __cdecl FUN_00bc97f0(int32_t a, int32_t b, float f, int32_t d);      // 0x00bc97f0
void   __cdecl RayCastParts(const float* pA, const float* pB, void* pBody, uint32_t* pOut,
                            int32_t a, int32_t b, int32_t c, int32_t d);     // 0x009b6450
void   __cdecl HitBody(void* pBody, uint32_t nId, const float* pVec, int32_t a, int32_t b,
                       float f);                                            // 0x009bb680

// ---------------------------------------------------------------------------------------------
// the serialisation stream and the provider it hands out
// ---------------------------------------------------------------------------------------------
class ISerializerStream {
public:
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();                            // +0x1c element marker
    virtual void* v20();                            // +0x20 returns the active IO provider
};

class IIOProvider {
public:
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void* v18();                            // +0x18 EA::IO stream
};

static void* GetIOStream(ISerializerStream* pStream)
{
    return ((IIOProvider*)pStream->v20())->v18();
}

// ---------------------------------------------------------------------------------------------
// cVarListSerializer (constructed inline inside cCreatureModeStrategy::Write)
// ---------------------------------------------------------------------------------------------
struct cDataSerializationInfo {
    int32_t mId;                                    // +0x00
    int32_t mDataSize;                              // +0x04
    uint8_t mbSerialized;                           // +0x08
    uint8_t mPad09[3];                              // +0x09
    void*   mpBinderContext;                        // +0x0c
    void*   mpSerializer;                           // +0x10
};

struct cDataSerializerGeneric {
    void*   mpSerializer;                           // +0x00
    int32_t mId;                                    // +0x04
    uint8_t mPad08[0x10];                           // +0x08
    void*   mpBinderContext;                        // +0x18
    uint8_t mPad1c[4];                              // +0x1c
    void*   mpAccessFunc;                           // +0x20
    void*   mpWriteFunc;                            // +0x24
    void*   mpReadFunc;                             // +0x28
    uint8_t mPad2c[0x10];                           // +0x2c
};

class cVarListSerializer {
public:
    cDataSerializationInfo mDataSerializationInfos[128]; // +0x000 (0x14 each)
    int32_t        mSerializableVarCount;           // +0xa00
    int32_t        mSerializedVarCount;             // +0xa04
    uint32_t       mSignature;                      // +0xa08
    void*          mpObject;                        // +0xa0c
    cDataSerializerGeneric* mpSerializerList;       // +0xa10

    cVarListSerializer(void* pObject, cDataSerializerGeneric* pList, uint32_t nSignature); // 0x00692f90
    bool Serialize(ISerializerStream* pStream);                                            // 0x00692900
};

// ---------------------------------------------------------------------------------------------
// SP::cCreatureModeStrategy - only the sub-objects this slice touches
// ---------------------------------------------------------------------------------------------
// a 0x18-stride record held in the strategy's vector at +0x44/+0x48
struct cModeEntry {
    float    mfValue;                               // +0x00
    uint8_t* mpBegin;                               // +0x04  a 0xc-stride array begin
    uint8_t* mpEnd;                                 // +0x08
};

class cCreatureModeStrategy {
public:
    void*   mpVtbl00;                               // +0x0000
    uint8_t mPad04[0x44 - 0x04];                    // +0x0004
    cModeEntry* mpVec44Begin;                       // +0x0044
    cModeEntry* mpVec44End;                         // +0x0048

    // 0x00d39800
    bool Write(ISerializerStream* pStream);
    // 0x00d399b0
    int32_t RunCinematicIfNotOccurred(int32_t nA, int32_t nB, bool bForce);
    // 0x00d38980
    bool HasCreatureTutorialOccurred(void* pSomething);
    // 0x00d389d0
    int32_t RunCinematic(int32_t nA, void* pSomething);
    // 0x00d39670
    int32_t AddStat(int32_t nA, int32_t nB);
};

// ---------------------------------------------------------------------------------------------
// 0x00d39800 - variable-list serialise
// ---------------------------------------------------------------------------------------------
// @ 0x00d39800
bool cCreatureModeStrategy::Write(ISerializerStream* pStream)
{
    uint32_t nMarker = 0x012191ca;
    WriteUint32(GetIOStream(pStream), &nMarker, 1, 0);

    cVarListSerializer serializer((void*)((char*)this - 8), (cDataSerializerGeneric*)0x015833f0, 0x1a80d26);
    bool bOk = serializer.Serialize(pStream);
    if (!bOk)
        return bOk;

    int32_t nEntries = (int32_t)((int32_t)((char*)mpVec44End - (char*)mpVec44Begin) / 0x18);
    WriteUint32(GetIOStream(pStream), &nEntries, 1, 0);

    int32_t nOffset = 0;
    for (int32_t i = 0; i < nEntries; ++i) {
        cModeEntry* pRec = (cModeEntry*)((char*)mpVec44Begin + nOffset);
        float fValue = pRec->mfValue;
        int32_t nSub = (int32_t)((int32_t)((char*)pRec->mpEnd - (char*)pRec->mpBegin) / 0xc);
        WriteUint32(GetIOStream(pStream), &nSub, 1, 0);
        WriteUint32(GetIOStream(pStream), &fValue, 1, 0);
        for (int32_t j = 0; j < nSub; ++j)
            WriteUint32(GetIOStream(pStream), pRec->mpBegin + j * 0xc, 3, 0);
        nOffset += 0x18;
    }
    return bOk;
}

// ---------------------------------------------------------------------------------------------
// 0x00d399b0 - run the creature tutorial cinematic unless it already ran
// ---------------------------------------------------------------------------------------------
// @ 0x00d399b0
int32_t cCreatureModeStrategy::RunCinematicIfNotOccurred(int32_t nA, int32_t nB, bool bForce)
{
    if (g_sTestSystem == 0 ||
        *(void**)((char*)g_sTestSystem + 0x70) == (void*)((char*)g_sTestSystem + 0x70)) {
        if (!bForce) {
            void* pCfg = ConfigManager();
            int32_t nV = ((int32_t(__thiscall*)(void*, uint32_t))(*(void***)pCfg)[0x30 / 4])(pCfg, 0x4ea96cb);
            if (nV == 0)
                return 0;
        }
        if (!HasCreatureTutorialOccurred((void*)nB))
            return RunCinematic(nA, (void*)nB);
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00d39a10 - load the private creature-mode tuning floats
// ---------------------------------------------------------------------------------------------
// The source list exposes a vtable slot +0x24 that resolves a keyed property.
class cTuningSource {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual bool v24(uint32_t nKey, cProperty** ppOut); // +0x24
};

// @ 0x00d39a10
void LoadPrivateTuningVariables(cTuningSource* pList)
{
    if (pList == 0)
        return;
    cProperty* pProp;
    const int16_t nType = 0xd;

    if (pList->v24(0x46dee850, &pProp) && pProp->mnType == nType)
        g_fTuning90 = *pProp->GetFloat();
    if (pList->v24(0x9243c96e, &pProp) && pProp->mnType == nType)
        g_fTuning94 = *pProp->GetFloat();
    if (pList->v24(0x2307fc8b, &pProp) && pProp->mnType == nType)
        g_fTuning98 = *pProp->GetFloat();
    if (pList->v24(0xe98ea09, &pProp) && pProp->mnType == nType)
        g_fTuning9c = *pProp->GetFloat();
    if (pList->v24(0xce6bd0a6, &pProp) && pProp->mnType == nType)
        g_fTuningA0 = *pProp->GetFloat();
    if (pList->v24(0x34877c4f, &pProp) && pProp->mnType == nType)
        g_fTuningA4 = *pProp->GetFloat();
    if (pList->v24(0x4ee78a9b, &pProp) && pProp->mnType == nType)
        g_fTuningA8 = *pProp->GetFloat();
    if (pList->v24(0x861d7203, &pProp) && pProp->mnType == nType)
        g_fTuningAC = *pProp->GetFloat();
}

// ---------------------------------------------------------------------------------------------
// 0x00d39c30 - rehash a creature-mode hashtable into a freshly-sized bucket array
// ---------------------------------------------------------------------------------------------
// a single hash-chain node; the key is at +0x00, the chain link at +0x184
struct cModeHashNode {
    uint32_t       mKey;                            // +0x000
    uint8_t        mPad04[0x184 - 0x04];            // +0x004
    cModeHashNode* mpNext;                          // +0x184
};

class cModeHash {
public:
    uint8_t  mPad00[0x04];                          // +0x00
    void**   mpBuckets;                             // +0x04
    uint32_t mnBucketCount;                         // +0x08
    uint8_t  mPad0c[0x1c - 0x0c];                   // +0x0c
    void*    mpFreeList;                            // +0x1c
    uint8_t  mPad20[0x24 - 0x20];                   // +0x20
    void**   mpPoolBegin;                           // +0x24
    void**   mpPoolEnd;                             // +0x28
    uint8_t  mPad2c[0x30 - 0x2c];                   // +0x2c
    void**   mpPoolHead;                            // +0x30

    void Rehash(uint32_t nNewCount);                // 0x00d39c30
};

void** __stdcall AllocBuckets(uint32_t nCount);     // 0x00d39bc0

// @ 0x00d39c30
void cModeHash::Rehash(uint32_t nNewCount)
{
    void** pNew = AllocBuckets(nNewCount);
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        cModeHashNode* pNode = (cModeHashNode*)mpBuckets[i];
        while (pNode != 0) {
            uint32_t nBucket = pNode->mKey % nNewCount;
            mpBuckets[i] = pNode->mpNext;
            pNode->mpNext = (cModeHashNode*)pNew[nBucket];
            pNew[nBucket] = pNode;
            pNode = (cModeHashNode*)mpBuckets[i];
        }
    }
    if (mnBucketCount > 1 && mpBuckets != mpPoolHead) {
        if (mpBuckets >= mpPoolBegin && mpBuckets < mpPoolEnd) {
            mpBuckets[0] = mpFreeList;
            mpFreeList = mpBuckets;
        } else {
            operator_delete(mpBuckets);
        }
    }
    mpBuckets = pNew;
    mnBucketCount = nNewCount;
}

// ---------------------------------------------------------------------------------------------
// 0x00d39d50 - sift-down step for an 8-byte key/value min-heap
// ---------------------------------------------------------------------------------------------
void __cdecl HeapAdjust(int32_t* pArr, int32_t nA, int32_t nHole, int32_t a5, int32_t a6,
                        int32_t a7);                // 0x00d38c50

// @ 0x00d39d50
void __cdecl SiftDown(int32_t* pArr, int32_t nA, int32_t nLen, int32_t nHole, int32_t a5,
                      int32_t a6, int32_t a7)
{
    int32_t nChild = nHole * 2 + 2;
    while (nChild < nLen) {
        if (pArr[nChild * 2 + 1] > pArr[nChild * 2 - 1])
            --nChild;
        pArr[nHole * 2] = pArr[nChild * 2];
        pArr[nHole * 2 + 1] = pArr[nChild * 2 + 1];
        nHole = nChild;
        nChild = nChild * 2 + 2;
    }
    if (nChild == nLen) {
        pArr[nHole * 2] = pArr[nChild * 2 - 2];
        pArr[nHole * 2 + 1] = pArr[nChild * 2 - 1];
        nHole = nChild - 1;
    }
    HeapAdjust(pArr, nA, nHole, a5, a6, a7);
}

// ---------------------------------------------------------------------------------------------
// 0x00d3a7f0 - register the creature-mode module callbacks
// ---------------------------------------------------------------------------------------------
void* __stdcall RegisterThing(void* pFn);            // 0x00b3d240
void  __fastcall SetThingA(void* pObj);             // 0x00b33ce0
void  __fastcall SetThingB(void* pObj);             // 0x00b33cf0
void* __cdecl GetThing(void);                       // 0x00b3d3c0
void  __fastcall InstallThing(void* pObj);          // 0x00b72880

// @ 0x00d3a7f0
bool __cdecl RegisterCreatureModeModule()
{
    SetThingA(RegisterThing((void*)0x00d39010));
    SetThingB(RegisterThing((void*)0x00d39070));
    InstallThing(GetThing());
    return true;
}

// ---------------------------------------------------------------------------------------------
// shared noun/creature view for the collision + telemetry routines
// ---------------------------------------------------------------------------------------------
class cNoun {
public:
    virtual void     v00();                         // +0x00
    virtual void     v04();                         // +0x04
    virtual void     v08();                         // +0x08
    virtual void     v0c();                         // +0x0c
    virtual void     v10();                         // +0x10
    virtual void     v14();                         // +0x14
    virtual void     v18();                         // +0x18
    virtual void     v1c();                         // +0x1c
    virtual uint32_t GetType();                     // +0x20
};

class cEgg {
public:
    void SetState(int32_t nState);                  // 0x00c6a670
};

void __cdecl NotifyNounCreatureCollision(void* pA, void* pB, void* p3, void* p4, void* p5,
                                         void* p6, void* p7, float f8);          // 0x00d3a0d0
void __cdecl NotifyNounToNounCollision(void* pA, void* pB, void* p3, void* p4, void* p5,
                                       void* p6, void* p7, float f8);             // 0x00d38dd0

// the collision-event record passed to the callback below
struct cCollisionEvent {
    int32_t mnMode;                                 // +0x00
    float   mfA;                                    // +0x04
    uint8_t mVec08[0x18];                           // +0x08
    uint8_t mVec20[0x0c];                           // +0x20
    uint8_t mVec2c[0x0c];                           // +0x2c
    uint8_t mVec38[0x0c];                           // +0x38
    uint8_t mVec44[0x0c];                           // +0x44
    uint8_t mVec50[0x0c];                           // +0x50
    uint8_t mVec5c[0x0c];                           // +0x5c
    void*   mpA;                                    // +0x68
    void*   mpB;                                    // +0x6c
    float   mf70;                                   // +0x70
    float   mf74;                                   // +0x74
};

static uint32_t NounType(void* pNoun)
{
    return ((cNoun*)pNoun)->GetType();
}

// the creature view touched by NotifyNounCreatureCollision
class cCreature {
public:
    uint8_t  mPad000[0xb4c];                        // +0x0000
    void*    mpObjB4c;                              // +0x0b4c
    uint8_t  mPadB50[0xb54 - 0xb50];                // +0x0b50
    void*    mpObjB54;                              // +0x0b54
    uint32_t mnFlagsB58;                            // +0x0b58
    uint8_t  mPadB5c[0xb5e - 0xb5c];                // +0x0b5c
    uint8_t  mbFlagB5e;                             // +0x0b5e
};

// @ 0x00d3a0d0
void __cdecl NotifyNounCreatureCollision(void* pA, void* pB, void* p3, const float* pDir,
                                         const float* pPos, void* p6, const float* pVel, float f8)
{
    float fSq = pVel[0] * pVel[0] + pVel[1] * pVel[1] + pVel[2] * pVel[2];
    if (fSq <= g_fEps38)
        return;
    float fDot = pDir[2] * pVel[2] + pDir[1] * pVel[1] + pDir[0] * pVel[0];
    if (fDot <= 0.0f)
        return;

    cCreature* pCreature = (cCreature*)pB;
    if (pCreature->mbFlagB5e == 0) {
        uint32_t nType = NounType(pA);
        if (nType == 0x2a8fb3f) {
            if (g_fVal40 < f8) {
                if (g_fVal44 < fSq) {
                    float aNorm[3];
                    NormalizedSafe(aNorm, pDir, 0);
                    ((void(__thiscall*)(void*, float, int32_t, int32_t, void*))
                        (*(void***)pCreature->mpObjB4c)[0x18 / 4])(pCreature->mpObjB4c,
                        Sqrtf(fSq) * g_fVal48, 0, 6, aNorm);
                }
                goto lab_2f6;
            }
        } else if (nType != 0x2c9cc91 && nType != 0x3a2511e) {
            goto lab_2f6;
        }
        {
            void* pAnim = PlayIdleAnimation((char*)pCreature->mpObjB4c + 8, 0, 0x40000);
            if (pAnim == 0 || *(int32_t*)((char*)pAnim + 0xc) != 3) {
                bool bSpecial = false;
                if (nType == 0x2a8fb3f) {
                    bSpecial = true;
                } else if (nType == 0x3a2511e) {
                    void* pRes = FUN_00ac80d0(pA, 0x3a2511e);
                    if (pRes != 0)
                        bSpecial = *(int32_t*)((char*)pRes + 0x110) == 6;
                }
                if ((pCreature->mnFlagsB58 >> 9 & 1) != 0)
                    goto lab_2f6;
                uint32_t nKey = FUN_00b18e00(pA);
                if (FUN_00c0f8f0(pCreature, nKey) != -1)
                    goto lab_2f6;
                uint32_t nMaskA, nMaskB;
                if (bSpecial) {
                    nMaskA = 0x1000;
                    nMaskB = 0;
                } else {
                    nMaskA = 0;
                    nMaskB = 0x800;
                }
                void* pCb = pCreature->mpObjB4c;
                if ((*(uint32_t*)((char*)pCb + 0x1c8) & nMaskA) != 0 ||
                    (*(uint32_t*)((char*)pCb + 0x1cc) & nMaskB) != 0 ||
                    *(int32_t*)((char*)pCb + 0x1d8) == 0x3697fb7)
                    goto lab_2f6;
                if (bSpecial) {
                    float fV = GetPropertyTFloat(*(void**)((char*)g_pModeInstance + 0xb4),
                                                 0x3ac3fddb, 5.0f);
                    ((void(__thiscall*)(void*, float))(*(void***)pB)[0x94 / 4])(pB, fV);
                } else {
                    FUN_00bc97f0(0, 0x800, 5.0f, 0);
                }
            }
        }
    }

lab_2f6:
    {
        bool bOk = ((bool(__thiscall*)(void*))((*(void***)((char*)pB + 0xc0))[0x48 / 4]))
                       ((char*)pB + 0xc0);
        if (bOk && pCreature->mpObjB54 != 0) {
            void* pBody = *(void**)((char*)pCreature->mpObjB54 + 0x17c);
            if (pBody != 0 && NounType(pA) != 0x3a2511e) {
                float aPos[3] = { pPos[0], pPos[1], pPos[2] };
                uint32_t nOut = 0;
                float aNorm[3];
                NormalizedSafe(aNorm, pDir, 0);
                float aScaled[3] = { aNorm[0], aNorm[1], aNorm[2] };
                RayCastParts(aPos, aScaled, pBody, &nOut, 0, 0, 0, 0);
                float fLen = Sqrtf(fSq);
                float fScale = (g_fVal3c <= fLen) ? fLen : g_fVal3c;
                aScaled[0] *= fScale;
                aScaled[1] *= fScale;
                aScaled[2] *= fScale;
                HitBody(pBody, nOut, aScaled, 0, 0, g_fValAc4);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00d3a450 - creature-mode collision callback dispatcher
// ---------------------------------------------------------------------------------------------
// @ 0x00d3a450
void __cdecl CreatureModeCollisionCallback(cCollisionEvent* pEvent)
{
    switch (pEvent->mnMode) {
    case 1: {
        cEgg* pEgg = (cEgg*)pEvent->mpA;
        if (NounType(pEgg) == 0x2a034cd && pEvent->mfA > 10.0f) {
            cEgg* pEgg2 = (cEgg*)pEvent->mpA;
            if (pEgg2 != 0 && NounType(pEgg2) == 0x2a034cd)
                pEgg2->SetState(4);
            else
                ((cEgg*)0)->SetState(4);
        }
        break;
    }
    case 2: {
        uint32_t nTypeA = NounType(pEvent->mpA);
        uint32_t nTypeB = NounType(pEvent->mpB);
        if (nTypeA == 0x18eb45e) {
            if (nTypeB == nTypeA)
                return;
            void* pA = pEvent->mpA;
            if (pA == 0 || NounType(pA) != 0x18eb45e)
                pA = 0;
            NotifyNounCreatureCollision(pEvent->mpB, pA, pEvent->mVec50, pEvent->mVec20,
                                        pEvent->mVec08, pEvent->mVec5c, pEvent->mVec44, pEvent->mf74);
        } else if (nTypeB == 0x18eb45e) {
            void* pB = pEvent->mpB;
            if (pB == 0 || NounType(pB) != 0x18eb45e)
                pB = 0;
            NotifyNounCreatureCollision(pEvent->mpA, pB, pEvent->mVec5c, pEvent->mVec2c,
                                        pEvent->mVec08, pEvent->mVec50, pEvent->mVec38, pEvent->mf70);
        } else {
            NotifyNounToNounCollision(pEvent->mpA, pEvent->mpB, pEvent->mVec5c, pEvent->mVec2c,
                                      pEvent->mVec08, pEvent->mVec50, pEvent->mVec38, pEvent->mf70);
        }
        break;
    }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00d3a710 - resolve a creature-mode strategy id from a property set
// ---------------------------------------------------------------------------------------------
class cPropertyManager {
public:
    virtual void v00();                             // +0x00
    virtual void v04();                             // +0x04
    virtual void v08();                             // +0x08
    virtual void v0c();                             // +0x0c
    virtual void v10();                             // +0x10
    virtual void v14();                             // +0x14
    virtual void v18();                             // +0x18
    virtual void v1c();                             // +0x1c
    virtual void v20();                             // +0x20
    virtual void v24();                             // +0x24
    virtual void v28();                             // +0x28
    virtual bool v2c(int32_t nA, int32_t nB, void** ppOut); // +0x2c
};

class cRefProp {
public:
    virtual void v00();                             // +0x00
    virtual void v04();                             // +0x04
    virtual void v08();                             // +0x08
    virtual void v0c();                             // +0x0c
    virtual void v10();                             // +0x10
    virtual void v14();                             // +0x14
    virtual void v18();                             // +0x18
    virtual void v1c();                             // +0x1c
    virtual void v20();                             // +0x20
    virtual bool v24(uint32_t nKey, cProperty** ppOut); // +0x24
};

// @ 0x00d3a710
int32_t __stdcall ResolveCreatureModeStrategy(int32_t nA, int32_t nB)
{
    int32_t nRet = 0;
    cRefProp* pRef = 0;
    cPropertyManager* pMgr = (cPropertyManager*)PropertyManager();
    if (pRef != 0) {
        cRefProp* pOld = pRef;
        pRef = 0;
        pOld->v04();
    }
    if (pMgr->v2c(nA, nB, (void**)&pRef)) {
        int32_t nX = 0;
        if (pRef != 0) {
            cProperty* pProp;
            if (pRef->v24(0x22e7847, &pProp) && pProp->mnType == 9)
                nX = *pProp->GetInt();
        }
        int32_t nY = 0;
        if (pRef != 0) {
            cProperty* pProp;
            if (pRef->v24(0x22e785c, &pProp) && pProp->mnType == 9)
                nY = *pProp->GetInt();
        }
        if (nX > 0) {
            int32_t nTmp = (nY <= 0) * 2 + 2;
            nRet = nTmp;
        } else if (nY > 0)
            nRet = 1;
    }
    if (pRef != 0)
        pRef->v04();
    return nRet;
}

// ---------------------------------------------------------------------------------------------
// 0x00d3a5a0 - creature-mode telemetry event evaluation
// ---------------------------------------------------------------------------------------------
void*  __fastcall FUN_00c04590(void* pNoun);         // 0x00c04590 (ecx = noun)
void*  __cdecl FUN_0067cb30();                      // 0x0067cb30
void*  __fastcall FUN_00c0bc00_2(void* pThis, void* pOut, void* pZero); // 0x00c0bc00 (this=pThis, 2 args)
void*  __fastcall FUN_00c0bc00_3(void* pThis, void* pA, void* pB, void* pC); // 0x00c0bc00 (this=pThis, 3 args)
void*  __cdecl FUN_00e39710(uint32_t nKey, void* p); // 0x00e39710
bool   __fastcall GetServerId(void* pAsset, void* pKey, void* pOut, int32_t nZero); // 0x0054e530

void* __fastcall AddStat(void* pStrategy, int32_t nA, int32_t nB);  // 0x00d39670 (ecx = strategy)

// @ 0x00d3a5a0
bool __stdcall EvaluateCreatureEvent(uint32_t nEvent, int32_t* pData)
{
    if (*pData == 0)
        return false;
    if ((void*)*pData != GetAvatar(NounManager()))
        return false;

    void* pStrategy = g_pModeInstance;

    if (nEvent == 0xd335362c) {
        void* pB = (void*)pData[1];
        if (pB == 0 || NounType(pB) != 0x18eb45e)
            return false;
        if (FUN_00c04590(pB) == 0)
            return false;
        FUN_00c04590(pB);
        void* pStat = AddStat(pStrategy, 2, 2);
        void* pMgr = FUN_0067cb30();
        void* pAsset = *(void**)((char*)pMgr + 0x58);
        if (pAsset == 0)
            return false;
        uint32_t nOut0 = 0xffffffff;
        uint32_t nOut1 = 0xffffffff;
        void* pKey = FUN_00c0bc00_2(pB, &nOut0, 0);
        if (GetServerId(pAsset, pKey, &nOut0, 0)
            && (nOut0 & nOut1) != 0xffffffff) {
            *(uint32_t*)((char*)*(void**)((char*)pStat + 0xc) + 0x2c) = nOut1;
            *(uint32_t*)((char*)*(void**)((char*)pStat + 0xc) + 0x30) = nOut0;
        }
        return false;
    }

    if (nEvent == 0xd3353630) {
        AddStat(pStrategy, 7, 0);
        return false;
    }

    if (nEvent == 0xd3353639) {
        void* pAvatar = GetAvatar(NounManager());
        if (pAvatar == 0)
            return false;
        uint32_t a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;
        void* pKey = FUN_00c0bc00_3(pAvatar, &a, &b, &c);
        FUN_00e39710(0x6d231de6, pKey);
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// 0x00d39f70 - spawn the locating-call response effect
// ---------------------------------------------------------------------------------------------
class cEffectMgr {
public:
    virtual void     v00();                         // +0x00
    virtual void     v04();                         // +0x04
    virtual void     v08(void* p);                  // +0x08
    virtual void     v0c();                         // +0x0c
    virtual bool     v10();                         // +0x10
    virtual void     v14();                         // +0x14
    virtual void     v18(void* pDesc);              // +0x18
    virtual void     v1c();                         // +0x1c
    virtual void     v20();                         // +0x20
    virtual void     v24();                         // +0x24
    virtual void     v28();                         // +0x28
    virtual bool     v2c(void* pA, int32_t nB, void** ppOut); // +0x2c
};

class cTransform3 {
public:
    void Assign(const void* pSrc);                  // 0x0041cb40
};

// effect descriptor built on the stack: flags/count header, a position, and a 3x3 basis
struct cLocEffectDesc {
    uint16_t mFlags;                                    // +0x00
    uint16_t mCount;                                    // +0x02
    float    mfPosX;                                    // +0x04
    float    mfPosY;                                    // +0x08
    float    mfPosZ;                                    // +0x0c
    float    mfOne;                                     // +0x10
    float    mMatrix[9];                                // +0x14
};

void  __cdecl BuildPlaneOrientation(void* pPlanet, const void* pMatrix); // 0x00b7f190
void* __cdecl MatrixFromQuat(void* pOut, const void* pQuat);             // 0x0059c190

// @ 0x00d39f70
void __cdecl SpawnLocatingCallEffect(void* pParam)
{
    cEffectMgr* pOld = (cEffectMgr*)g_pLocatingEffect;
    if (pOld != 0 && pOld->v10())
        return;

    cEffectMgr* pMgr = (cEffectMgr*)EffectsManagerPtr();
    cEffectMgr* pCur = (cEffectMgr*)g_pLocatingEffect;
    if (pCur != 0) {
        g_pLocatingEffect = 0;
        pCur->v04();
    }
    if (!pMgr->v2c(pParam, 0, &g_pLocatingEffect))
        return;

    cLocEffectDesc desc;
    desc.mFlags = 0;
    desc.mCount = 0;
    desc.mfPosX = g_fLocX;
    desc.mfPosY = g_fLocY;
    desc.mfPosZ = g_fLocZ;
    desc.mfOne = g_fRealOne;
    ((cTransform3*)&desc.mMatrix)->Assign(&g_locMatrix);

    const float* pVec = (const float*)pParam;
    desc.mfPosX = pVec[0];
    desc.mfPosY = pVec[1];
    desc.mfPosZ = pVec[2];
    desc.mFlags |= 4;
    desc.mCount++;

    float aQuat[9];
    void* pPlanet = PlanetModel(aQuat, pParam);
    BuildPlaneOrientation(pPlanet, aQuat);
    const float* pMat = (const float*)MatrixFromQuat(aQuat, aQuat);
    for (int32_t i = 0; i < 9; ++i)
        desc.mMatrix[i] = pMat[i];

    desc.mFlags |= 2;
    desc.mCount++;
    ((cEffectMgr*)g_pLocatingEffect)->v18(&desc);
    ((cEffectMgr*)g_pLocatingEffect)->v08(0);

    void* pAvatar = GetAvatar(NounManager());
    SpawnLocatingCallResponse(pAvatar, pParam);
}
