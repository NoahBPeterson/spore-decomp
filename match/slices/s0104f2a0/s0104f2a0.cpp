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
    /* 038h */ uint32_t mTable_038[4];   // eastl hashtable (find reads +0x38/+0x3c/+0x40)
    CPropertyList* Find(uint32_t nID);   // 0x0104f850
};

struct CToolObject
{
    /* 000h */ uint8_t  mPad_000[0x7c];
    /* 07ch */ int32_t  mField_07c;
    /* 080h */ uint8_t  mPad_080[0x88 - 0x80];
    /* 088h */ uint8_t  mTimerA_088[0xa8 - 0x88];
    /* 0a8h */ uint8_t  mTimerB_0a8[0x174 - 0xa8];
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
    virtual void     vfn38();
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