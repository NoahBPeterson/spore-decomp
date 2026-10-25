// SP::cSPSpaceToolData / Simulator::cSpaceInventoryItem tool-property accessors
// from SPGonzago (part of the cSPToolManager tool-data family).
//
// Every accessor walks the same inlined helper: the property-list id stored at
// +0x178 is looked up in the shared strategy map returned by 0x00b3d390 and the
// map's Find (0x0104f850); when the id is zero or the lookup fails the fixed
// default id 0xB0DA49D9 is used instead.  The found property list is then driven
// through its vtable.  Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"

// ---------------------------------------------------------------------------
// Layouts.  Ghidra's class names for this module are unreliable, so the shared
// object layout is spelled out once with a named field per touched offset.
// ---------------------------------------------------------------------------
struct CPropertyList;

struct CStrategyMap
{
    /* 000h */ uint8_t  mPad_000[0x38];
    /* 038h */ uint32_t mHash_038;       // eastl hashtable: allocator/head
    /* 03ch */ void*    mpBuckets_03c;   // bucket array
    /* 040h */ uint32_t mBucketCount_040;
    /* 044h */ uint32_t mCount_044;
    CPropertyList* Find(uint32_t nID);   // 0x0104f850
};

struct CToolObject
{
    /* 000h */ uint8_t  mPad_000[0x7c];
    /* 07ch */ int32_t  mField_07c;
    /* 080h */ uint8_t  mByte_080;                 // "selected/active" byte
    /* 081h */ uint8_t  mPad_081[0x88 - 0x81];
    /* 088h */ uint8_t  mTimerA_088[0xa8 - 0x88];  // cSPTimer (+0x88)
    /* 0a8h */ uint8_t  mTimerB_0a8[0x108 - 0xa8]; // cSPTimer (+0xa8) and misc
    /* 108h */ void*    mPtr_108[3];               // charge-effect slots
    /* 114h */ void*    mPtr_114;                  // cached charge-bar owner
    /* 118h */ void*    mPtr_118;                  // auto-released object (vtbl+0xc0)
    /* 11ch */ uint8_t  mPad_11c[0x128 - 0x11c];
    /* 128h */ void*    mPtr_128;                  // auto-released object (vtbl+4)
    /* 12ch */ uint8_t  mPad_12c[0x174 - 0x12c];
    /* 174h */ uint32_t mFlags_174;
    /* 178h */ uint32_t mPropertyID_178;
    /* 17ch */ uint8_t  mPad_17c[0x1a4 - 0x17c];
    /* 1a4h */ uint32_t mEnergyCost_1a4;
    /* 1a8h */ uint8_t  mPad_1a8[0x1c0 - 0x1a8];
    /* 1c0h */ float    mField_1c0;
    /* 1c4h */ float    mField_1c4;
};

// The property list is driven through its vtable; slots up to 0x44 are declared
// so the used entries sit at their real index.
struct CPropertyList
{
    virtual void     vfn00();
    virtual void     vfn04();
    virtual void     vfn08();
    virtual int      vfn0c(uint32_t nID);
    virtual void     vfn10();
    virtual void     vfn14();
    virtual bool     vfn18(CToolObject* pOwner);
    virtual bool     vfn1c(CToolObject* pOwner);
    virtual bool     vfn20(CToolObject* pOwner, int nA, int nB);
    virtual void     vfn24();
    virtual void     vfn28();
    virtual void     vfn2c();
    virtual void     vfn30();
    virtual void     vfn34();
    virtual void     vfn38(CToolObject* pOwner);
    virtual void     vfn3c();
    virtual void     vfn40();
    virtual uint32_t vfn44(uint32_t nValue);
};

// Callbacks whose bodies live outside this slice.
CStrategyMap* GetToolStrategyMap();                 // 0x00b3d390: returns [0x0167eb08]
bool __fastcall SP_cSPTimer_IsRunning(void* pTimer);         // 0x00feba90  SP::cSPTimer::IsRunning
uint64_t __fastcall SP_cSPTimer_GetElapsedTime(void* pTimer); // 0x00bc3190  SP::cSPTimer::GetElapsedTime
extern const float kToolTimerScale;                 // 0x013ec5b4

bool __fastcall FUN_0104ff10(CToolObject* pThis);   // 0x0104ff10
bool __fastcall FUN_0104fe50(CToolObject* pThis);   // 0x0104fe50
bool __fastcall FUN_0104feb0(CToolObject* pThis);   // 0x0104feb0

// The default property-list id used when the tool id is zero or unknown.
#define kDefaultPropertyID 0xB0DA49D9u

// Single-bit predicate over a packed flag word; keeps the bit test as a shift
// rather than letting the bitfield/byte-test form appear.
__forceinline bool IsFlagSet(uint32_t uWord, unsigned nBitIndex)
{
    return ((uWord >> nBitIndex) & 1) != 0;
}

__forceinline CPropertyList* GetToolProperty(uint32_t nID)
{
    if (nID)
    {
        CPropertyList* pList = GetToolStrategyMap()->Find(nID);
        if (pList)
            return pList;
    }
    return GetToolStrategyMap()->Find(kDefaultPropertyID);
}

// ---------------------------------------------------------------------------
// 0x0104fff0: report whether this tool is still running its effect.
// ---------------------------------------------------------------------------
// @ 0x0104fff0
int32_t __fastcall FUN_0104fff0(CToolObject* pThis)
{
    if (!IsFlagSet(pThis->mFlags_174, 5) || pThis->mField_07c > 0)
    {
        if (!FUN_0104ff10(pThis))
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0104f930: SP::cSPSpaceToolData::GetStrategy
// ---------------------------------------------------------------------------
// @ 0x0104f930
CPropertyList* __fastcall FUN_0104f930(CToolObject* pThis)
{
    return GetToolProperty(pThis->mPropertyID_178);
}

// ---------------------------------------------------------------------------
// 0x0104fe10: Simulator::cSpaceInventoryItem::func40h
// ---------------------------------------------------------------------------
// @ 0x0104fe10
void __fastcall FUN_0104fe10(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    pList->vfn20(pThis, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x01050020: SP::cSPSpaceToolData::GetUseCost
// ---------------------------------------------------------------------------
// @ 0x01050020
void __fastcall FUN_01050020(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    pList->vfn44(pThis->mEnergyCost_1a4);
}

// ---------------------------------------------------------------------------
// 0x0104fe50: property flag 0x060079DE
// ---------------------------------------------------------------------------
// @ 0x0104fe50
bool __fastcall FUN_0104fe50(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    return (pList ? pList->vfn0c(0x060079DEu) : 0) != 0;
}

// ---------------------------------------------------------------------------
// 0x0104feb0: property flag 0x061D959A
// ---------------------------------------------------------------------------
// @ 0x0104feb0
bool __fastcall FUN_0104feb0(CToolObject* pThis)
{
    CPropertyList* pList = GetToolProperty(pThis->mPropertyID_178);
    return (pList ? pList->vfn0c(0x061D959Au) : 0) != 0;
}

// ---------------------------------------------------------------------------
// 0x0104fbb0: SP::cSPToolManager::ActivateTool -- initialise the property list,
// then run its activate (vfn18) step and release the list again.
// ---------------------------------------------------------------------------
// @ 0x0104fbb0
bool __stdcall FUN_0104fbb0(CToolObject* pTool)
{
    CPropertyList* pList = 0;
    if (pTool->mPropertyID_178)
        pList = GetToolStrategyMap()->Find(pTool->mPropertyID_178);
    if (pList == 0)
        pList = GetToolStrategyMap()->Find(kDefaultPropertyID);
    if (pList)
        pList->vfn00();
    bool bResult = pList->vfn18(pTool);
    pList->vfn04();
    return bResult;
}

// ---------------------------------------------------------------------------
// Shared helpers whose bodies live outside this slice.  Ones with an unknown
// signature are declared cdecl and cast to the real calling convention at the
// use site (the codebase-wide convention for these reconstructions).
// ---------------------------------------------------------------------------
void* __cdecl FUN_00921580(void* pNode);                    // 0x00921580 eastl::RBTreeIncrement
void  __cdecl FUN_00921880(void* pNode, void* pHeader);     // 0x00921880 eastl::RBTreeErase
void  __cdecl FUN_00f47380(void* p);                        // 0x00f47380 operator delete
void  __cdecl FUN_00571db0(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t); // 0x00571db0 RemoveHandler
void  __cdecl FUN_006b5240();                               // 0x006b5240 SP::cString::~cString
void  __cdecl FUN_006b5060();                               // 0x006b5060 SP::cString::cString
void  __cdecl FUN_0104ef30();                               // 0x0104ef30 EraseEffectTree (thiscall + node)
void  __cdecl FUN_00961d60();                               // 0x00961d60 eastl::hashtable::DoFreeNodes
void  __cdecl FUN_00b5b9a0();                               // 0x00b5b9a0 cGonzagoSubsystem::~cGonzagoSubsystem
void  __cdecl FUN_00b5b960();                               // 0x00b5b960 cGonzagoSubsystem::cGonzagoSubsystem
void  __cdecl FUN_00645ed0();                               // 0x00645ed0 eastl::hashtable::find
void  __cdecl FUN_00920090();                               // 0x00920090 create default strategy
void  __cdecl FUN_0104c510();                               // 0x0104c510 strategy post-create
void  __cdecl FUN_00b6ff20();                               // 0x00b6ff20 hashtable insert/slot
void  __cdecl FUN_0104cc40();                               // 0x0104cc40 IsDeselectedAfterUse (thiscall)
void  __cdecl FUN_01002bd0();                               // 0x01002bd0 SpaceGameGet
void  __cdecl FUN_00a1ad60();                               // 0x00a1ad60 GetPlayerInventory (thiscall)
void  __cdecl FUN_00ff4540();                               // 0x00ff4540 player-inventory tool hook
void  __cdecl FUN_00bc3170();                               // 0x00bc3170 cSPTimer::Reset (thiscall)
uint32_t __cdecl FUN_00b5b800();                            // 0x00b5b800 GetCurrentGameMode
void* __cdecl FUN_00ffbe50();                               // 0x00ffbe50 GetUFOSimulator
void* __cdecl FUN_010666a0();                               // 0x010666a0 cSPUISpace accessor
void  __cdecl FUN_01065ed0();                               // 0x01065ed0 cSPUISpace::HideToolChargeBar
void  __cdecl FUN_0093a780();                               // 0x0093a780 EA::IO::ReadInt32
void  __cdecl FUN_00c879a0();                               // 0x00c879a0 object pre-read hook
void  __cdecl FUN_00692f90();                               // 0x00692f90 cVarListSerializer::cVarListSerializer
void  __cdecl FUN_00693e10();                               // 0x00693e10 cVarListSerializer::Read
void  __cdecl FUN_0104f650();                               // 0x0104f650 rbtree insert helper

extern const float g_f16e12cc;   // 0x016e12cc
extern const float g_f16e12d0;   // 0x016e12d0
extern const float g_f16e12d4;   // 0x016e12d4
extern const float g_f1485720;   // 0x01485720 == 1.0f
extern const float g_f1470f1c;   // 0x01470f1c == 2.0f

// ---------------------------------------------------------------------------
// The PaintSystem / cSPToolManager singleton layout (ctor 0x0104f960 and
// dtor 0x0104f740 are both methods of this object).
// ---------------------------------------------------------------------------
struct CToolManager
{
    /* 000h */ void*    mvfn00;
    /* 004h */ void*    mvfn04;
    /* 008h */ uint8_t  mPad_008[0x1c - 0x08];
    /* 01ch */ void*    mvfn1c;
    /* 020h */ void*    mp20;
    /* 024h */ void*    mp24;
    /* 028h */ void*    mp28;
    /* 02ch */ float    mf2c;
    /* 030h */ float    mf30;
    /* 034h */ float    mf34;
    /* 038h */ uint32_t mu38;              // hashtable head/allocator
    /* 03ch */ void*    mpBuckets;          // bucket array (inline at +0x154df28)
    /* 040h */ uint32_t mBucketCount;
    /* 044h */ uint32_t mu44;
    /* 048h */ float    mf48;
    /* 04ch */ float    mf4c;
    /* 050h */ uint32_t mu50;
    /* 054h */ uint8_t  mPad_054[8];
    /* 05ch */ void*    mpTreeAnchor;       // eastl rbtree anchor (self when empty)
    /* 060h */ void*    mpTreeBegin;
    /* 064h */ void*    mpEffectRoot;       // root of the AutoHandler/effect tree
    /* 068h */ uint8_t  mb68;
    /* 069h */ uint8_t  mPad_069[3];
    /* 06ch */ uint32_t mTreeCount;
    /* 070h */ uint8_t  mPad_070[4];
    /* 074h */ uint8_t  mStrings[26 * 0x14]; // 26 SP::cString objects
    /* 27ch */ uint32_t mHandlerID;
    /* 280h */ uint32_t mh280;
    /* 284h */ uint32_t mh284;
    /* 288h */ uint32_t mh288;
    /* 28ch */ uint32_t mh28c;
    /* 290h */ float    mf290;
    /* 294h */ float    mf294;
    /* 298h */ float    mf298;
};

struct CToolEffectPacket
{
    uint16_t mFlags;     // +0x00
    int16_t  mCount;     // +0x02
    float    mv[4];      // +0x04
    float    mM[9];      // +0x14
};

// ---------------------------------------------------------------------------
// 0x0104f2a0: SP::cSPToolManager::UpdateToolEffects -- reap expired handlers,
// then push one transform packet per surviving (effect, spatial) handler pair.
// ---------------------------------------------------------------------------
// @ 0x0104f2a0
void __fastcall FUN_0104f2a0(CToolManager* pThis)
{
    void* pHeader = (char*)pThis + 0x5c;
    void* pNode = pThis->mpTreeBegin;

    while (pNode != pHeader)
    {
        void* pEffect = *(void**)((char*)pNode + 0x10);
        bool bAlive = (pEffect != 0) &&
            ((bool(__thiscall*)(void*))(*(void***)pEffect)[0x10 / 4])(pEffect);
        if (!bAlive)
        {
            --pThis->mTreeCount;
            void* pNext = FUN_00921580(pNode);
            FUN_00921880(pNode, pHeader);
            void* pSpatial = *(void**)((char*)pNode + 0x14);
            if (pSpatial != 0)
                ((void(__thiscall*)(void*))(*(void***)pSpatial)[0xc0 / 4])(pSpatial);
            if (pEffect != 0)
                ((void(__thiscall*)(void*))(*(void***)pEffect)[4 / 4])(pEffect);
            FUN_00f47380(pNode);
            pNode = pNext;
        }
        else
        {
            pNode = FUN_00921580(pNode);
        }
    }

    pNode = pThis->mpTreeBegin;
    while (pNode != pHeader)
    {
        void* pEffect = *(void**)((char*)pNode + 0x10);
        void* pSpatial = *(void**)((char*)pNode + 0x14);
        if (pEffect != 0 && pSpatial != 0)
        {
            float* pq = (float*)((void*(__thiscall*)(void*))
                (*(void***)pSpatial)[0x30 / 4])(pSpatial);
            const float q0 = pq[0], q1 = pq[1], q2 = pq[2], q3 = pq[3];

            CToolEffectPacket pkt;
            pkt.mFlags = 0;
            pkt.mCount = 0;
            pkt.mv[3] = 1.0f;
            pkt.mM[0] = 1.0f - (q2 * q2 + q1 * q1) * 2.0f;
            pkt.mM[1] = (q3 * q2 + q1 * q0) * 2.0f;
            pkt.mM[2] = (q2 * q0 - q3 * q1) * 2.0f;
            pkt.mM[3] = (q1 * q0 - q3 * q2) * 2.0f;
            pkt.mM[4] = 1.0f - (q2 * q2 + q0 * q0) * 2.0f;
            pkt.mM[5] = (q3 * q0 + q2 * q1) * 2.0f;
            pkt.mM[6] = (q3 * q1 + q2 * q0) * 2.0f;
            pkt.mM[7] = (q2 * q1 - q3 * q0) * 2.0f;
            pkt.mM[8] = 1.0f - (q1 * q1 + q0 * q0) * 2.0f;

            pkt.mFlags |= 2;
            ++pkt.mCount;
            float* pPos = (float*)((void*(__thiscall*)(void*))
                (*(void***)pSpatial)[0x2c / 4])(pSpatial);
            pkt.mv[0] = pPos[0];
            pkt.mv[1] = pPos[1];
            pkt.mv[2] = pPos[2];

            pkt.mFlags |= 4;
            ++pkt.mCount;
            ((void(__thiscall*)(void*, void*))
                (*(void***)pEffect)[0x18 / 4])(pEffect, &pkt);
        }
        pNode = FUN_00921580(pNode);
    }
}

// ---------------------------------------------------------------------------
// 0x0104f740: PaintSystem destructor (three vtable resets, messaging teardown,
// 26 cString destructors, effect tree erase, hashtable teardown, base dtor).
// ---------------------------------------------------------------------------
// @ 0x0104f740
void __fastcall FUN_0104f740(CToolManager* pThis)
{
    pThis->mvfn00 = (void*)0x149ade0;
    pThis->mvfn04 = (void*)0x149add8;
    pThis->mvfn1c = (void*)0x149add0;

    if (pThis->mHandlerID != 0)
    {
        uint32_t id = pThis->mHandlerID;
        uint32_t a = pThis->mh280;
        uint32_t b = pThis->mh284;
        uint32_t c = pThis->mh288;
        uint32_t d = pThis->mh28c;
        pThis->mHandlerID = 0;
        FUN_00571db0(id, a, b, c, d);
    }

    char* pStr = (char*)pThis + 0x27c;
    for (int i = 0; i < 26; ++i)
    {
        pStr -= 0x14;
        ((void(__thiscall*)(void*))FUN_006b5240)(pStr);
    }

    ((void(__thiscall*)(void*, void*))FUN_0104ef30)(
        (char*)pThis + 0x58, pThis->mpEffectRoot);

    ((void(__thiscall*)(void*, void*, uint32_t))FUN_00961d60)(
        &pThis->mu38, pThis->mpBuckets, pThis->mBucketCount);
    pThis->mu44 = 0;
    if (pThis->mBucketCount > 1)
        FUN_00f47380(pThis->mpBuckets);

    pThis->mvfn1c = (void*)0x13eb394;
    ((void(__thiscall*)(void*))FUN_00b5b9a0)(pThis);
}

// ---------------------------------------------------------------------------
// 0x0104f850: CStrategyMap::Find -- hashtable lookup, creating and inserting
// the default strategy object on a miss.
// ---------------------------------------------------------------------------
// @ 0x0104f850
CPropertyList* CStrategyMap::Find(uint32_t nID)
{
    void* pIter[2];
    pIter[0] = 0;
    pIter[1] = 0;
    uint32_t key = nID;
    ((void(__thiscall*)(void*, void**, uint32_t*))FUN_00645ed0)(
        &this->mHash_038, pIter, &key);

    if (pIter[0] != ((void**)this->mpBuckets_03c)[this->mBucketCount_040])
        return (CPropertyList*)*(void**)((char*)pIter[0] + 4);

    void* pValue = 0;
    void* pCreated = ((void*(__stdcall*)(uint32_t, void**, uint32_t, uint32_t))
        FUN_00920090)(nID, &pValue, 0, 0);
    ((void(__thiscall*)(void*))FUN_0104c510)(pCreated);

    if (pValue == 0)
        return 0;

    uint32_t pairKey = nID;
    void** pSlot = (void**)
        ((void*(__thiscall*)(void*, uint32_t*))FUN_00b6ff20)(
            &this->mHash_038, &pairKey);

    void* pOld = *pSlot;
    if (pValue != pOld)
    {
        ((void(__thiscall*)(void*))(*(void***)pValue)[0])(pValue);
        *pSlot = pValue;
        if (pOld != 0)
            ((void(__thiscall*)(void*))(*(void***)pOld)[1])(pOld);
    }
    ((void(__thiscall*)(void*))(*(void***)pValue)[1])(pValue);
    return (CPropertyList*)pValue;
}

// ---------------------------------------------------------------------------
// 0x0104f960: PaintSystem constructor.
// ---------------------------------------------------------------------------
// @ 0x0104f960
CToolManager* __fastcall FUN_0104f960(CToolManager* pThis)
{
    ((void(__thiscall*)(void*))FUN_00b5b960)(pThis);

    pThis->mvfn1c = (void*)0x13eb394;
    pThis->mvfn00 = (void*)0x149ade0;
    pThis->mvfn04 = (void*)0x149add8;
    pThis->mvfn1c = (void*)0x149add0;

    pThis->mp20 = 0;
    pThis->mp24 = 0;
    pThis->mp28 = 0;
    pThis->mf2c = g_f16e12cc;
    pThis->mf30 = g_f16e12d0;
    pThis->mf34 = g_f16e12d4;
    pThis->mf48 = g_f1485720;
    pThis->mf4c = g_f1470f1c;

    pThis->mBucketCount = 1;
    pThis->mpBuckets = (void*)0x154df28;
    pThis->mu44 = 0;
    pThis->mu50 = 0;

    pThis->mpTreeAnchor = (char*)pThis + 0x5c;
    pThis->mpTreeBegin  = (char*)pThis + 0x5c;
    pThis->mpEffectRoot = 0;
    pThis->mb68 = 0;
    pThis->mTreeCount = 0;

    for (int i = 0; i < 26; ++i)
        ((void(__thiscall*)(void*))FUN_006b5060)(
            (char*)pThis + 0x74 + i * 0x14);

    pThis->mHandlerID = 0;
    pThis->mh280 = 0;
    pThis->mh284 = 0;
    pThis->mh288 = 0;
    pThis->mh28c = 0;
    pThis->mf290 = g_f16e12cc;
    pThis->mf294 = g_f16e12d0;
    pThis->mf298 = g_f16e12d4;

    return pThis;
}

// ---------------------------------------------------------------------------
// 0x0104fa90: SP::cSPToolManager::UseToolStop.
// ---------------------------------------------------------------------------
// @ 0x0104fa90
bool __fastcall FUN_0104fa90(CToolManager* pThis, int, CToolObject* pTool)
{
    if (pTool == 0)
        return false;

    CPropertyList* pList = 0;
    if (pTool->mPropertyID_178 != 0)
        pList = GetToolStrategyMap()->Find(pTool->mPropertyID_178);
    if (pList == 0)
        pList = GetToolStrategyMap()->Find(kDefaultPropertyID);
    if (pList != 0)
        pList->vfn00();
    pList->vfn38(pTool);

    if (((bool(__thiscall*)(CToolObject*))FUN_0104cc40)(pTool))
    {
        void* pGame = ((void*(__cdecl*)())FUN_01002bd0)();
        void* pInv = ((void*(__thiscall*)(void*))FUN_00a1ad60)(pGame);
        if (pInv != 0)
            ((void(__thiscall*)(void*, CToolObject*))FUN_00ff4540)(pInv, pTool);
    }

    pTool->mByte_080 = 0;
    ((void(__thiscall*)(void*))FUN_00bc3170)((char*)pTool + 0xc8);

    if (FUN_00b5b800() == 0x1654c05u)
    {
        void* pSim = FUN_00ffbe50();
        void* pInv = ((void*(__thiscall*)(void*))FUN_00a1ad60)(pSim);
        void* pCompare = (pInv != 0) ? (void*)((char*)pInv + 0x34) : 0;
        if (pTool->mPtr_114 == pCompare)
        {
            void* pUI = FUN_010666a0();
            ((void(__thiscall*)(void*))FUN_01065ed0)(pUI);
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        void* p = pTool->mPtr_108[i];
        if (p != 0)
        {
            ((void(__thiscall*)(void*, int))(*(void***)p)[0xc / 4])(p, 0);
            p = pTool->mPtr_108[i];
            if (p != 0)
            {
                pTool->mPtr_108[i] = 0;
                ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
            }
        }
    }

    pList->vfn04();
    return true;
}

// ---------------------------------------------------------------------------
// 0x0104fc10: SP::cSPToolManager::DeactivateTool.
// ---------------------------------------------------------------------------
// @ 0x0104fc10
bool __fastcall FUN_0104fc10(CToolManager* pThis, int, CToolObject* pTool)
{
    CPropertyList* pList = 0;
    if (pTool->mPropertyID_178 != 0)
        pList = GetToolStrategyMap()->Find(pTool->mPropertyID_178);
    if (pList == 0)
        pList = GetToolStrategyMap()->Find(kDefaultPropertyID);
    if (pList != 0)
        pList->vfn00();

    if (pTool->mByte_080 != 0 || SP_cSPTimer_IsRunning((char*)pTool + 0xc8))
        FUN_0104fa90(pThis, 0, pTool);

    if (pTool->mPtr_118 != 0)
    {
        void* p = pTool->mPtr_118;
        pTool->mPtr_118 = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    }
    if (pTool->mPtr_128 != 0)
    {
        void* p = pTool->mPtr_128;
        pTool->mPtr_128 = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }

    bool bResult = pList->vfn1c(pTool);
    pList->vfn04();
    return bResult;
}

// ---------------------------------------------------------------------------
// 0x0104fcd0: red-black-tree lower_bound + insert; returns the value block
// (five dwords) attached to the located node.
// ---------------------------------------------------------------------------
// @ 0x0104fcd0
void* __fastcall FUN_0104fcd0(void* pThis, int, void** ppArg)
{
    void* pHeader = (char*)pThis + 4;
    void* pPos = pHeader;
    void* pNode = *(void**)((char*)pThis + 0xc);
    uint32_t key = *(uint32_t*)ppArg;

    while (pNode != 0)
    {
        if (*(uint32_t*)((char*)pNode + 0x10) < key)
        {
            pNode = *(void**)pNode;
        }
        else
        {
            pPos = pNode;
            pNode = *(void**)((char*)pNode + 4);
        }
    }

    if (pPos == pHeader || key < *(uint32_t*)((char*)pPos + 0x10))
    {
        void* pValue = *ppArg;
        if (pValue != 0)
            ((void(__thiscall*)(void*))(*(void***)pValue)[0])(pValue);

        void* pOut = 0;
        void* pair[2];
        pair[0] = pValue;
        pair[1] = 0;
        ((void*(__thiscall*)(void*, void**, void*, void*, void*))FUN_0104f650)(
            pThis, &pOut, pPos, pair,
            (void*)((uint32_t)ppArg & 0xffffff00u));
        pPos = pOut;

        if (pValue != 0)
            ((void(__thiscall*)(void*))(*(void***)pValue)[1])(pValue);
    }

    return (char*)pPos + 0x14;
}

// ---------------------------------------------------------------------------
// 0x0104fd70: read the tool-data header, serialise the variable list into the
// tool object, flush the object, and (when the flag byte is set) activate it.
// ---------------------------------------------------------------------------
// @ 0x0104fd70
bool __fastcall FUN_0104fd70(char* pThis, int, void* pObj)
{
    void* pA = ((void*(__thiscall*)(void*))
        (*(void***)pObj)[0x20 / 4])(pObj);
    void* pReader = ((void*(__thiscall*)(void*))
        (*(void***)pA)[0x18 / 4])(pA);

    int32_t value = 0;
    ((void(__cdecl*)(void*, void*, int, int))FUN_0093a780)(
        pReader, &value, 1, 0);

    bool bPre = ((bool(__thiscall*)(char*, void*))FUN_00c879a0)(pThis, pObj);

    struct CVarListSerializer
    {
        double  mAlign;
        uint8_t mData[0xa0c];
    } serializer;

    char* pOwner = pThis - 0xc;
    ((void(__thiscall*)(void*, char*, void*, uint32_t))FUN_00692f90)(
        &serializer, pOwner, (void*)0x15b8850, 0x1a80d26u);

    bool bRead = ((bool(__thiscall*)(void*, void*))FUN_00693e10)(
        &serializer, pObj);

    bool bResult = bRead && bPre;

    ((void(__thiscall*)(void*))
        (*(void***)pOwner)[0x4c / 4])(pOwner);

    if (pThis[0x1c] != 0)
    {
        GetToolStrategyMap();
        FUN_0104fbb0((CToolObject*)pOwner);
    }

    return bResult;
}

// ---------------------------------------------------------------------------
// 0x0104ff10: dual cSPTimer threshold test.
// ---------------------------------------------------------------------------
// @ 0x0104ff10
bool __fastcall FUN_0104ff10(CToolObject* pThis)
{
    if (FUN_0104fe50(pThis))
        return false;
    if (FUN_0104feb0(pThis))
        return false;

    if (SP_cSPTimer_IsRunning((char*)pThis + 0x88))
    {
        uint32_t threshold = (uint32_t)(pThis->mField_1c0 * kToolTimerScale);
        if ((int32_t)threshold < 0)
            threshold = 0xffffffffu;

        uint64_t elapsed = SP_cSPTimer_GetElapsedTime((char*)pThis + 0x88);
        if (elapsed < (uint64_t)threshold)
            return true;
    }

    if (SP_cSPTimer_IsRunning((char*)pThis + 0xa8))
    {
        int32_t threshold = (int32_t)(pThis->mField_1c4 * kToolTimerScale);
        if (threshold < 0)
            threshold = -1;

        uint64_t elapsed = SP_cSPTimer_GetElapsedTime((char*)pThis + 0xa8);
        if (elapsed < (uint64_t)(int64_t)threshold)
        {
            int32_t check = (int32_t)(pThis->mField_1c4 * kToolTimerScale);
            if (check >= 0 && check != -1)
                return true;
        }
    }

    return false;
}