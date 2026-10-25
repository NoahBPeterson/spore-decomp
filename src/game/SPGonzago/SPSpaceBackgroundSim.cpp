// src/game/SPGonzago/SPSpaceBackgroundSim.cpp -- migrated from slice(s) s01399700, s01021e50, s01020e80 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceBackgroundSim.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cSimPlanetLowLOD.h"
#include "SP/cSolarSystem.h"
#include "SP/cStar.h"
#include "SP/cStarManager.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern void* DAT_016dda8c;                 // gspBackgroundSimManager singleton
extern float DAT_013f9428, DAT_01485720, DAT_013ec4b8;
extern void* DAT_01654c04;
extern void* DAT_01654c02;

// ---- items of slice s01020e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
extern void* DAT_016dda8c;                 // gspBackgroundSimManager singleton
extern float DAT_013f9428, DAT_01485720, DAT_013ec4b8;
extern void* DAT_01654c04;
extern void* DAT_01654c02;
void* __cdecl FUN_00ffbe50();                        // GetUFOSimulator
void* __cdecl FUN_00b5b800();                        // GetCurrentGameMode
void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int);
struct Ext {
    void* FUN_0101fb40();
    void* FUN_00c70f90(int);                 // float
    void  FUN_01017bb0();
    void* FUN_00c70c00();
    void  FUN_00c82f00();
    void* FUN_00c71e70();
    void* FUN_00c8b360();
    void  FUN_00c8b800();
    void* FUN_00c31730();
    void* FUN_00ba9370();
    void  FUN_00bb3750();
    void  FUN_00bb59b0();
    void* FUN_00b8de30();
void  FUN_00b3d2a0i(int);
void  FUN_00ad92d0();
    void* FUN_00ff3f00();
    void  FUN_0140efa0();
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }
// ---- items of slice s01020e80 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
__declspec(noinline) void* FUN_01021260();  // 0x01021260 (stays in the slice: not this object's)
void* FUN_01021300();  // 0x01021300 (stays in the slice: not this object's)

// ---- items of slice s01021e50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
struct cVTable {
    void* mpSlots[0x100];                       // 0x000
};
class cDispatchObject {
public:
    void* Call(int nSlot) {
        return ((void* (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    int32_t CallInt(int nSlot) {
        return ((int32_t (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    void CallVoid(int nSlot) {
        ((void (*)(cDispatchObject*))mpTable->mpSlots[nSlot >> 2])(this);
    }

    cVTable* mpTable;                           // 0x000
};
class cRefCounted {
public:
    virtual void AddRef();                      // slot 0x00
    virtual void Release();                     // slot 0x04
};
typedef int (__cdecl *cPointerCompare)(void*, void*);
class cPlanetList {
public:
    void Erase(void** ppFirst, void** ppLast);

    void** mpBegin;                             // 0x000
    void** mpEnd;                               // 0x004
    void** mpCapacity;                          // 0x008
};
void FUN_00bab900(cPlanetList* pList, cDispatchObject** ppPlanet);
void SwapPlanetSlots(void** ppLhs, void** ppRhs);           // 0x10216a0
void** SelectMedianPlanet(void** ppFirst, void** ppMiddle, void** ppLast,
                          cPointerCompare pCompare);        // 0x1021180
void BuildPlanetHeap(int32_t nFirst, int32_t nLast, cPointerCompare pCompare);
int32_t TakePlanetSlot(int32_t nFirst, int32_t nLast, int32_t nCount,
                       int32_t nIndex, cPointerCompare pCompare);
class cGameStateFlags {
public:
    uint8_t mPad000[0x48];                      // 0x000
    uint8_t mbFlag;                             // 0x048
};
class cGameState {
public:
    uint8_t mPad000[0x188];                     // 0x000
    cGameStateFlags* mpFlags;                   // 0x188
};
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const char* pName, int32_t nFlags);
    void Serialize(void* pData);

    uint8_t mPad000[0xa14];                     // 0x000
};
class cSPBackgroundSimManager {
public:
    void Read(cVarListSerializer* pSerializer);
    void ActivatePlanet(void* pPlanetKey);
    void Destroy(int32_t nFlags);
    void UpdatePlanetTerraforming(void* pPlanet, int32_t nDelta);

    int32_t mnElapsedTime;                      // 0x000
    cDispatchObject* mpSimulator;               // 0x004
    cDispatchObject* mpStar;                    // 0x008
    cDispatchObject* mpCommObject;              // 0x00c
    int32_t mnState;                            // 0x010
    int32_t mnUnused14;                         // 0x014
    int32_t mnTimeRemaining;                    // 0x018
    cRefCounted* mpRequest;                     // 0x01c
    cPlanetList mPlanets;                       // 0x020
    uint8_t mPad02c[0x1c];                      // 0x02c
};
cSPBackgroundSimManager* g_pBackgroundSim = nullptr;        // 0x16dda8c
uint8_t g_bBackgroundSimActive = 0;                         // 0x16dda88
uint8_t g_bBackgroundSimStarted = 0;                        // 0x16dda89
class cStarManager {
public:
    void GetOrActivatePlanet(void* pPlanetKey, cDispatchObject** ppPlanet);
    cDispatchObject* GetActiveStar();
    void Tick(int32_t nDelta);
};
void* StarManager();
void* GetStateManager();
void* __cdecl operator_new(uint32_t nSize, const char* pName);
void FUN_00d05010(void* pObject);
void InitBackgroundSimulator(void* pStar);
// ---- items of slice s01021e50 end

// ---- items of slice s01399700 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct PropDesc {
    const char* name;    // +0x00
    uint        hash;    // +0x04
    uint        offset;  // +0x08
    uint        f0c;     // +0x0c  (uninitialised in the original)
    uint        f10;     // +0x10  (uninitialised in the original)
    uint        f14;     // +0x14  (uninitialised in the original)
    void*       f18;     // +0x18
    void*       f1c;     // +0x1c
    void*       f20;     // +0x20
    void*       f24;     // +0x24
    void*       f28;     // +0x28
    void*       f2c;     // +0x2c
    void*       f30;     // +0x30
    void*       f34;     // +0x34
    void*       f38;     // +0x38
};
extern PropDesc g_props_1150[8];    // 0x15b70d0  (stride 0x3c)
void FUN_00692ca0();
void FUN_00692fb0();
void FUN_00692ff0();
void FUN_00693090();
void FUN_006930b0();
void FUN_00572810();
void FUN_00572840();
void FUN_0057cde0();
void FUN_00694f00();
void FUN_00694fc0();
void FUN_00675ca0();
void FUN_00ac8050();
void FUN_00ac88f0();
void FUN_00acbb80();
void FUN_00b1fbf0();
void FUN_00b6f550();
void FUN_00b6f860();
void FUN_00bca960();
void FUN_00bd1780();
void FUN_00bdd350();
void FUN_00c2e4e0();
void FUN_00c43790();
void FUN_00c6c390();
void FUN_00c86560();
void FUN_00c87090();
void FUN_010213f0();
void FUN_01021b70();
// ---- items of slice s01399700 end

// @ 0x01021180
int* FUN_01021180(int* a, int* b, int* c, int (*cmp)(int, int))
{
    if (cmp(*a, *b) != 0) {
        if (cmp(*b, *c) == 0) {
            if (cmp(*a, *c) != 0) return c;
            return a;
        }
        return b;
    }
    if (cmp(*a, *c) != 0) return a;
    if (cmp(*b, *c) != 0) return c;
    return b;
}

// @ 0x01021200
void __stdcall FUN_01021200(int a, int b)
{
    void* gm = FUN_00b5b800();
    if (gm != &DAT_01654c04) {
        gm = FUN_00b5b800();
        if (gm != &DAT_01654c02) return;
    }
    void* s = DAT_016dda8c;
    void* o = *(void**)((char*)s + 0xc);
    ((void(__thiscall*)(void*))VTP(o)[0xc / 4])(o);
    (void)a; (void)b;
}

// @ 0x01021240
int FUN_01021240()
{
    int* p = *(int**)((char*)DAT_016dda8c + 8);
    if (p) return *(int*)((char*)p + 0x48);
    return 0;
}

// @ 0x01021370
void* FUN_01021370()
{
    void* emp = FUN_01021300();
    if (!emp) return 0;
    void* home = E(FUN_01021300())->FUN_00c31730();
    if (home) return E(FUN_01021300())->FUN_00c31730();
    void* ap = FUN_01021260();
    return *(void**)((char*)ap + 0x13c);
}

// @ 0x010213b0
void FUN_010213b0(int param)
{
    if (param != 2) return;
    int* s = (int*)DAT_016dda8c;
    int* one = (int*)s[2];
    void* ufo = FUN_00ffbe50();
    if (one && ufo) {
        void* r = ((void*(__thiscall*)(void*))VTP(one)[0 / 4])(one);
        (void)r;
    }
}

// @ 0x01021960
void FUN_01021960(int param)
{
    int* s = (int*)DAT_016dda8c;
    if (s[4] == param) return;
    s[4] = param;
    if (param != 2) return;
    int* one = (int*)s[2];
    void* ufo = FUN_00ffbe50();
    if (one && ufo) {
        int* r = (int*)E(one)->FUN_00c8b360();
        (void)r;
    }
}

// @ 0x01021d40
void FUN_01021d40()
{
    void* p = FUN_00f473a0(0x34, "Simulator", 0, 0, 0, 0);
    float one = DAT_01485720;
    DAT_016dda8c = p;
    if (p) {
        *(u32*)((char*)p + 4) = 0;
        *(u32*)((char*)p + 8) = 0;
        *(u32*)((char*)p + 0xc) = 0;
        *(u32*)((char*)p + 0x10) = 0xffffffff;
        *(u32*)((char*)p + 0x18) = 0xffffffff;
        *(u32*)((char*)p + 0x1c) = 0;
        *(u32*)((char*)p + 0x20) = 0;
        *(u32*)((char*)p + 0x24) = 0;
        *(u32*)((char*)p + 0x28) = 0;
        *(float*)((char*)p + 0x14) = one;
    } else {
        *(float*)0x14 = one;
    }
}

// @ 0x01021e50
void** PartitionPlanets(void** ppFirst, void** ppUnused, void** ppLast, cDispatchObject* pPivot, cPointerCompare pCompare)
{
    void** ppLow = ppFirst;
    for (;;) {
        while (pCompare(pPivot, *ppLow) != 0)
            ++ppLow;
        while (pCompare(pPivot, *--ppLast) != 0)
            ;
        if (ppLow >= ppLast)
            break;
        SwapPlanetSlots(ppLow, ppLast);
        ++ppLow;
    }
    if (pPivot != nullptr)
        pPivot->CallVoid(0xc0);
    return ppLow;
}

// @ 0x01021ed0
void SortPlanetPartition(void** ppFirst, void** ppLast, void** ppUnused, cPointerCompare pCompare)
{
    void** ppLow = ppFirst;
    BuildPlanetHeap(0, (int32_t)(ppLast - ppFirst), pCompare);
    for (; ppLow < ppLast; ++ppLow) {
        if (pCompare(*ppFirst, *ppLow) == 0)
            continue;
        void* pValue = *ppLow;
        if (pValue != nullptr)
            ((cDispatchObject*)pValue)->CallVoid(0xbc);
        void* pOld = *ppFirst;
        if (pOld != pValue) {
            if (pOld != nullptr)
                ((cDispatchObject*)pOld)->CallVoid(0xbc);
            *ppFirst = pOld;
            if (pValue != nullptr)
                ((cDispatchObject*)pValue)->CallVoid(0xc0);
        }
        int32_t nCount = (int32_t)(ppLast - ppFirst);
        TakePlanetSlot(0, 0, nCount - 1, 0, pCompare);
        if (pValue != nullptr)
            ((cDispatchObject*)pValue)->CallVoid(0xc0);
    }
}

// @ 0x01021fd0
void QuickSortPlanets(void** ppFirst, void** ppLast, void** ppUnused, int32_t nDepth, cPointerCompare pCompare)
{
    for (;;) {
        if (((uint32_t)((uint8_t*)ppLast - (uint8_t*)ppFirst) & 0xfffffffc) <= 0x70)
            break;
        if (nDepth <= 0)
            break;
        void** ppMiddle = SelectMedianPlanet(ppFirst, ppFirst + ((ppLast - ppFirst) >> 1),
                                             ppLast - 1, pCompare);
        void* pPivot = *ppMiddle;
        if (pPivot != nullptr)
            ((cDispatchObject*)pPivot)->CallVoid(0xbc);
        void** ppSplit = PartitionPlanets(ppFirst, ppLast, ppLast,
                                          (cDispatchObject*)pPivot, pCompare);
        QuickSortPlanets(ppSplit, ppLast, ppLast, nDepth - 1, pCompare);
        ppLast = ppSplit;
    }
    if (nDepth == 0)
        SortPlanetPartition(ppFirst, ppLast, ppLast, pCompare);
}

// @ 0x010220e0
void cSPBackgroundSimManager::Read(cVarListSerializer* pSerializer)
{
    mPlanets.Erase(mPlanets.mpBegin, mPlanets.mpEnd);
    if (mpRequest != nullptr) {
        cRefCounted* pRequest = mpRequest;
        mpRequest = nullptr;
        pRequest->Release();
    }
    cVarListSerializer serializer(this, "StarManager", 0x1a80d26);
    serializer.Serialize(pSerializer);
}

// @ 0x01022150
void cSPBackgroundSimManager::ActivatePlanet(void* pPlanetKey)
{
    cDispatchObject* pPlanet = nullptr;
    ((cStarManager*)StarManager())->GetOrActivatePlanet(pPlanetKey, &pPlanet);

    void** ppSlot = mPlanets.mpBegin;
    while (ppSlot != mPlanets.mpEnd && *ppSlot != pPlanet)
        ++ppSlot;
    if (ppSlot == mPlanets.mpEnd) {
        if (mPlanets.mpEnd < mPlanets.mpCapacity) {
            void** ppNew = mPlanets.mpEnd;
            mPlanets.mpEnd = ppNew + 1;
            if (ppNew != nullptr)
                *ppNew = (void*)pPlanet;
        }
        else {
            FUN_00bab900(&mPlanets, &pPlanet);
        }
    }
    if (pPlanet != nullptr)
        pPlanet->CallVoid(0xbc);

    cGameState* pGame = (cGameState*)GetStateManager();
    pGame->mpFlags->mbFlag = 0;
    if (pPlanet != nullptr)
        pPlanet->CallVoid(0xc0);
}

// @ 0x010221f0
void InitBackgroundSimulator(void* pStar)
{
    cDispatchObject* pSimulator = nullptr;
    void* pMemory = operator_new(0x100, "Simulator");
    if (pMemory != nullptr)
        pSimulator = (cDispatchObject*)pMemory;
    if (pMemory != nullptr)
        FUN_00d05010(pMemory);

    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    cDispatchObject* pOld = pManager->mpCommObject;
    if (pSimulator != pOld) {
        if (pSimulator != nullptr)
            ((cDispatchObject*)((uint8_t*)pSimulator + 8))->CallVoid(0x08);
        pManager->mpCommObject = pSimulator;
        if (pOld != nullptr)
            ((cDispatchObject*)((uint8_t*)pOld + 8))->CallVoid(0x0c);
    }
    pManager->mpCommObject->CallVoid(0x04);

    if (!g_bBackgroundSimActive) {
        if (pManager->mpStar != nullptr) {
            cDispatchObject* pOldStar = pManager->mpStar;
            pManager->mpStar = nullptr;
            pOldStar->CallVoid(0x04);
        }
        pManager->mnElapsedTime = 0x3e8;
    }

    void* pWorld = ((cStarManager*)StarManager())->GetActiveStar();
    ((cDispatchObject*)pStar)->CallVoid(0x00);
    if (pManager->mpSimulator != nullptr) {
        cDispatchObject* pOldSim = pManager->mpSimulator;
        pManager->mpSimulator = nullptr;
        pOldSim->CallVoid(0x04);
    }
    pManager->mpStar = (cDispatchObject*)pStar;
    pManager->mnState = 1;
    pManager->mPlanets.Erase(pManager->mPlanets.mpBegin, pManager->mPlanets.mpEnd);
    pManager->mnTimeRemaining = -1;
    pManager->mnUnused14 = 0;
}

// @ 0x01022460
void ShutdownBackgroundSimulator()
{
    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    g_bBackgroundSimActive = 0;
    g_bBackgroundSimStarted = 0;

    if (pManager->mpSimulator != nullptr) {
        cDispatchObject* pSimulator = pManager->mpSimulator;
        pManager->mpSimulator = nullptr;
        pSimulator->CallVoid(0xc0);
    }
    if (pManager->mpStar != nullptr) {
        cDispatchObject* pStar = pManager->mpStar;
        pManager->mpStar = nullptr;
        pStar->CallVoid(0x04);
    }
    if (pManager->mpRequest != nullptr) {
        cRefCounted* pRequest = pManager->mpRequest;
        pManager->mpRequest = nullptr;
        pRequest->Release();
    }
    pManager->mPlanets.Erase(pManager->mPlanets.mpBegin, pManager->mPlanets.mpEnd);
    pManager->mnTimeRemaining = -1;

    cDispatchObject* pComm = pManager->mpCommObject;
    if (pComm != nullptr) {
        pComm->CallVoid(0x08);
        cDispatchObject* pNew = pManager->mpCommObject;
        if (pNew != nullptr) {
            pManager->mpCommObject = nullptr;
            ((cDispatchObject*)((uint8_t*)pNew + 8))->CallVoid(0x0c);
        }
    }
}

// @ 0x01022550
void StopBackgroundSim()
{
    cSPBackgroundSimManager* pManager = g_pBackgroundSim;
    if (pManager->mnTimeRemaining != -1) {
        ShutdownBackgroundSimulator();
        pManager = g_pBackgroundSim;
    }
    if (pManager != nullptr) {
        pManager->Destroy(1);
        g_pBackgroundSim = nullptr;
    }
}

// @ 0x013a1150
void PropTableInit_1150()
{
    PropDesc d;
    d.name = "mMillisecondsSinceLastUpdate"; d.hash = 0x366df4cu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00692ff0;
    d.f30 = (void*)&FUN_00693090; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057cde0;
    d.offset = 0u;
    g_props_1150[0] = d;

    d.name = "mActivePlanet"; d.hash = 0x338a74au;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_010213f0;
    d.f28 = (void*)&FUN_00bdd350; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f550;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 4u;
    g_props_1150[1] = d;

    d.name = "mpActiveStar"; d.hash = 0x3598939u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_010213f0;
    d.f28 = (void*)&FUN_00bca960; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f550;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 8u;
    g_props_1150[2] = d;

    d.name = "mCurrentContext"; d.hash = 0x366e013u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00692ff0;
    d.f30 = (void*)&FUN_00693090; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_0057cde0;
    d.offset = 0x10u;
    g_props_1150[3] = d;

    d.name = "mRotationRateFactor"; d.hash = 0x366e045u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00ac88f0; d.f2c = (void*)&FUN_006930b0;
    d.f30 = (void*)&FUN_00694fc0; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00acbb80;
    d.offset = 0x14u;
    g_props_1150[4] = d;

    d.name = "mPlayerEmpire"; d.hash = 0x366e0c2u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00572810;
    d.f28 = (void*)&FUN_00572840; d.f2c = (void*)&FUN_00693090;
    d.f30 = (void*)&FUN_00694f00; d.f34 = (void*)&FUN_00b1fbf0;
    d.f38 = (void*)&FUN_00675ca0;
    d.offset = 0x18u;
    g_props_1150[5] = d;

    d.name = "mTribeCivRelationships"; d.hash = 0x6494431u;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_01021b70;
    d.f28 = (void*)&FUN_00bd1780; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00c87090;
    d.f38 = (void*)&FUN_00ac8050;
    d.offset = 0xcu;
    g_props_1150[6] = d;

    d.name = "mPlayerColonies"; d.hash = 0x4f3cd9bu;
    d.f18 = 0; d.f1c = 0;
    d.f20 = (void*)&FUN_00692ca0; d.f24 = (void*)&FUN_00c86560;
    d.f28 = (void*)&FUN_00c43790; d.f2c = (void*)&FUN_00c2e4e0;
    d.f30 = (void*)&FUN_00692fb0; d.f34 = (void*)&FUN_00b6f860;
    d.f38 = (void*)&FUN_00c6c390;
    d.offset = 0x20u;
    g_props_1150[7] = d;
}
