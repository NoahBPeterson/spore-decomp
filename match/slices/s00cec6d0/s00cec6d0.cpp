// Slice s00cec6d0: the building tuning table's constructor/destructor, the city display strategy's
// civ-UI rebuild and the helper next to it (the minimap vehicle walk).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; call targets and data addresses are masked during
// comparison)
// ---------------------------------------------------------------------------------------------
void* __cdecl operator new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                           const char* pFile, int32_t nLine);                       // 0x00f473a0
void  __cdecl operator_delete(void* pBlock);                                        // 0x00f47380
double __cdecl sqrt(double dValue);                                                 // CRT intrinsic

char g_emptyString[2];                  // 0x01667bac ?gEmptyString16@eastl@@3PA_WA
                                        //          the shared empty string every default-built
                                        //          tuning string points at
float g_fRealZero;                      // 0x01485378 _HK_REAL_ZERO
float g_fRealOne;                       // 0x01485720 _HK_REAL_ONE

uint8_t  g_funCD7D10;                   // 0x00cd7d10 game-data vector callback
uint8_t  g_funD3D420;                   // 0x00d3d420 game-data vector callback
uint8_t  g_funB1E500;                   // 0x00b1e500 game-data vector callback
uint8_t  g_funAE5EA0;                   // 0x00ae5ea0 game-data vector callback
uint8_t  g_funACDFF0;                   // 0x00acdff0 game-data vector callback
uint8_t  g_funAE72D0;                   // 0x00ae72d0 game-data vector callback
uint8_t  g_classKey403df5c[4];          // 0x0403df5c the class the first vehicle lookup walks
uint8_t  g_classKey18c43e8[4];          // 0x018c43e8 the class the city-object lookup walks
uint8_t  g_classKey18c6de8[4];          // 0x018c6de8 the class the second vehicle lookup walks

// ---------------------------------------------------------------------------------------------
// helper functions (retail addresses in comments)
// ---------------------------------------------------------------------------------------------
void* __cdecl FUN_009512c0();                                                       // 0x009512c0
void* __cdecl FUN_009512d0(uint32_t nSize, int32_t nDtor, const char* pName,
                           void* pHeap);                                            // 0x009512d0
void* __cdecl FUN_00b993c0(int32_t nTribeId);                                       // 0x00b993c0
void* __cdecl FUN_00b25c30(void* pManager);                                         // 0x00b25c30
void* __cdecl FUN_00e057a0(void* pCivUI);                                           // 0x00e057a0

// ---------------------------------------------------------------------------------------------
// the tuning table's string member: an eastl string whose empty state is the engine's shared
// empty string and which owns its buffer once the capacity passes one character
// ---------------------------------------------------------------------------------------------
class cTuningString {
public:
    char* mpBegin;                              // +0x00
    char* mpEnd;                                // +0x04
    char* mpEndAlloc;                           // +0x08

    cTuningString()
    {
        mpBegin = g_emptyString;
        mpEnd = g_emptyString;
        mpEndAlloc = g_emptyString + 1;
    }
    ~cTuningString()
    {
        if ((int32_t)mpEndAlloc - (int32_t)mpBegin > 1 && mpBegin != 0)
            operator_delete(mpBegin);
    }
};

namespace SP {

// ---------------------------------------------------------------------------------------------
// the building tuning table: nine building groups, each opening with the localised building name
// ---------------------------------------------------------------------------------------------
class cBuildingTuning {
public:
    uint8_t       mPad000[0x1c];                // +0x000 .. +0x01b
    cTuningString kSleepBuildingName;           // +0x01c
    uint8_t       mPad028[0x20];                // +0x028 .. +0x047
    cTuningString kEntertainmentBuildingName;   // +0x048
    uint8_t       mPad054[0x14];                // +0x054 .. +0x067
    cTuningString kCulturalBuildingName;        // +0x068
    uint8_t       mPad074[0x24];                // +0x074 .. +0x097
    cTuningString kIndustryBuildingName;        // +0x098
    uint8_t       mPad0a4[0x1c];                // +0x0a4 .. +0x0bf
    cTuningString kFoodBuildingName;            // +0x0c0
    uint8_t       mPad0cc[0x14];                // +0x0cc .. +0x0df
    cTuningString kDiplomaticBuildingName;      // +0x0e0
    uint8_t       mPad0ec[0x3c];                // +0x0ec .. +0x127
    cTuningString kMilitaryBuildingName;        // +0x128
    uint8_t       mPad134[0x0c];                // +0x134 .. +0x13f
    cTuningString kDefenseBuildingName;         // +0x140
    uint8_t       mPad14c[0x08];                // +0x14c .. +0x153
    cTuningString kMissionBuildingName;         // +0x154

    cBuildingTuning();                                                  // 0x00cece70
    ~cBuildingTuning();                                                 // 0x00cecd50
};

// ---------------------------------------------------------------------------------------------
// @ 0x00cece70
// ---------------------------------------------------------------------------------------------
cBuildingTuning::cBuildingTuning()
{
}

// ---------------------------------------------------------------------------------------------
// @ 0x00cecd50
// ---------------------------------------------------------------------------------------------
cBuildingTuning::~cBuildingTuning()
{
}

// ---------------------------------------------------------------------------------------------
// a localised string: title text plus the hashes that look it up in the text table
// ---------------------------------------------------------------------------------------------
class cString {
public:
    uint32_t mnTableHash;                       // +0x000 the text table it is looked up in
    uint32_t mnKeyHash;                         // +0x004 the key inside that table
    void*    mpText;                            // +0x008 the resolved text
    void*    mpTextEnd;                         // +0x00c
    void*    mpTextAlloc;                       // +0x010

    cString(uint32_t nTableHash, uint32_t nKeyHash,
            const wchar_t* pDefaultText);                                   // 0x006b5770
    ~cString();                                                             // 0x006b5240
    const wchar_t* GetText();                                               // 0x006b55c0
};

}   // namespace SP

// ---------------------------------------------------------------------------------------------
// small value types (spelled out rather than as arrays so the functions carry no local buffers)
// ---------------------------------------------------------------------------------------------
struct fVector2 {
    float fx;                                   // +0x00
    float fy;                                   // +0x04
};

struct fVector3 {
    float fx;                                   // +0x00
    float fy;                                   // +0x04
    float fz;                                   // +0x08
};

struct fRect {
    float fLeft;                                // +0x00
    float fTop;                                 // +0x04
    float fRight;                               // +0x08
    float fBottom;                              // +0x0c
};

// ---------------------------------------------------------------------------------------------
// counted, vtable-bearing engine objects
// ---------------------------------------------------------------------------------------------
class cRefObject {
public:
    virtual void AddRef();                      // +0x000
    virtual void Release();                     // +0x004
};

// the listener subobject a window hosts at +0x68: its own reference counting interface
class cWindowListener {
public:
    virtual void v00();                         // +0x000
    virtual void AddRef();                      // +0x004
    virtual void Release();                     // +0x008
};

// the global civ UI window (Simulator/cSPGlobalUI-CivUI)
class cGlobalCivUI {
public:
    virtual void AddRef();                      // +0x000
    virtual void Release();                     // +0x004
    virtual void Init(void* pArgs);             // +0x008
    virtual void Shutdown();                    // +0x00c tears the owned panels down
    uint8_t        mPad004[0x64];               // +0x004 .. +0x067
    cWindowListener mListener;                  // +0x068

    class cWindowObject* FindWindowByID(uint32_t nWindowID);                 // 0x00e012b0
};

// a plain window handle target
class cWindowObject {
public:
    virtual void AddRef();                      // +0x000
    virtual void Release();                     // +0x004
    virtual void Init(void* pArgs);             // +0x008
    virtual void v0c();                         // +0x00c
    virtual void v10();                         // +0x010
    virtual void v14();                         // +0x014
    virtual void v18();                         // +0x018
    virtual void v1c();                         // +0x01c
    virtual void v20();                         // +0x020
    virtual void v24();                         // +0x024
    virtual void v28();                         // +0x028
    virtual void v2c();                         // +0x02c
    virtual void v30();                         // +0x030
    virtual void v34();                         // +0x034
    virtual fRect* GetRect();                   // +0x038 the window's client rect
    uint8_t mPad004[0x78];                      // +0x004 .. +0x07b
    void    SetChildWindow(void* pIWindow);     // retail slot +0x0d8
};

// the posse bar the strategy keeps in mPosses[]
class cPosseWindow : public cRefObject {
public:
    virtual void v08();                         // +0x008
    virtual void v0c();                         // +0x00c
    uint8_t mPad010[0x70];                      // +0x010 .. +0x07f
    // retail slot map: +0x080 BindPosseBar, +0x094 SetMode, +0x0b8 SetText
    bool BindPosseBar(const wchar_t* pBarName, float fFill);                 // +0x080
    void DestroyPosseBar();                                                  // +0x088
    void SetMode(int32_t nMode);                                             // +0x094
    void SetText(const wchar_t* pText);                                      // +0x0b8

    cPosseWindow* PosseCtor();                                               // 0x00e25710
};

// the counted handle every strategy member is built from
class cAutoRef {
public:
    cRefObject* mpObject;                       // +0x00
};

// the strategy's vehicle-posse tree (an eastl set keyed by noun): the anchor sits at +0x04 and the
// node count at +0x14, the eight bytes behind it are unused
class EventTree {
public:
    uint32_t mnAllocTag;                        // +0x00
    void*    mpAnchorLeft;                      // +0x04 points at itself while the tree is empty
    void*    mpAnchorRight;                     // +0x08
    void*    mpRoot;                            // +0x0c
    uint8_t  mbColor;                           // +0x10
    uint8_t  mPad011[3];                        // +0x11 .. +0x13
    uint32_t mnSize;                            // +0x14
    uint32_t mPad018;                           // +0x18

    void Destroy(void* pRoot);                                               // 0x00f240d0
};

// the allocator a vector was built with (carried by value, three words wide here)
class cEastlAllocator {
public:
    uint32_t mnTag;                             // +0x00
    uint32_t mnPad004;                          // +0x04
    uint32_t mnPad008;                          // +0x08
};

// an eastl pointer vector: the three iterator slots followed by the allocator it was built with
class cNounPtrVector {
public:
    void**          mpBegin;                    // +0x00
    void**          mpEnd;                      // +0x04
    void**          mpEndAlloc;                 // +0x08
    cEastlAllocator mAllocator;                 // +0x0c .. +0x17

    // 0x00b93c60: only allocates nCount slots and leaves mpBegin == mpEnd == the allocation
    void   Resize(int32_t nCount, cEastlAllocator* pAllocator);
};

// 0x00829110: copies [ppFirst, ppLast) into the storage starting at ppDst, referencing every
// element it stores; the out iterator is seeded with ppSeed and left past the copy at *ppOut
void** __cdecl _Construct(void*** ppOut, void** ppFirst, void** ppLast, void** ppDst,
                          void** ppSeed);

// the game-data container a noun-manager query hands back: the matching vector at +0x04
class cGameDataVector {
public:
    void*          mpOwner;                     // +0x00
    cNounPtrVector mVector;                     // +0x04
};

class cGameNounManager;

cGameNounManager* __cdecl NounManager();                                         // 0x00b3d300

class cGameNounManager {
public:
    cGameDataVector* GetGameDataVector(const void* pFilter1, const void* pFilter2,
                                       const void* pFilter3, const void* pFilter4,
                                       const void* pClassKey);                   // 0x00b21340
    void* SetGameDataOwner2();                                                  // 0x00bfc5f0
};

// the civ minimap window (UI/CivMinimap)
class cIWindow {
public:
    virtual void v00();                         // +0x000
};

class cMinimapWindow : public cRefObject {
public:
    cIWindow mWindowInterface;                  // +0x004 the interface handed to the parent window
    uint8_t  mPad008[0x33c];                    // +0x008 .. +0x343
    float    mfAngles[3];                       // +0x344 .. +0x34f the view angles

    void SetDirection(const fVector3& rDirection);                           // 0x00e0c1f0
    void SetViewMode(int32_t nMode);                                         // 0x00e0ad00
    void Refresh();                                                          // 0x00e0e1a0

    cMinimapWindow* MinimapCtor(int32_t nWidth, int32_t nHeight, const fVector2* pMin,
                                const fVector2* pMax, int32_t nA, int32_t nB); // 0x00e0fc90
};

// the process-wide simulator object
class cSimSingleton {
public:
    uint8_t  mPad000[0x14];                     // +0x000 .. +0x013
    int32_t* mpPlayerTribeId;                   // +0x014 the player's tribe id, -1 when unset

    cSimSingleton* SimSingletonCtor();                                       // 0x00ae5c30
};

cSimSingleton* g_pSimSingleton;                 // 0x0167a60c

// an object that can hand out the point it looks at
class cLookAt {
public:
    virtual fVector3* PointAt();                // retail slot +0x02c
};

class cTribeObject {
public:
    uint8_t  mPad000[0x120];                    // +0x000 .. +0x11f
    cLookAt  mLookAt;                           // +0x120
};

class cTribeView {
public:
    uint8_t  mPad000[0x34];                     // +0x000 .. +0x033
    cLookAt  mLookAt;                           // +0x034
};

namespace Simulator {

// ---------------------------------------------------------------------------------------------
// the city display strategy: only the members these functions touch are named
// ---------------------------------------------------------------------------------------------
class cCityDisplayStrategy {
public:
    virtual void v00();                         // +0x000
    uint8_t   mPad004[0x60];                    // +0x004 .. +0x063
    cAutoRef  mGlobalCivUI;                     // +0x064 the SPGlobalUI-CivUI window
    cAutoRef  mSelectionPosse;                  // +0x068
    cAutoRef  mPosses[4];                       // +0x06c .. +0x07b
    EventTree mVehiclePosseMaps[4];             // +0x07c .. +0x0eb
    uint32_t  mn0ec;                            // +0x0ec cleared by the constructor
    cAutoRef  mMiniMapWin;                      // +0x0f0 the UI/CivMinimap window
    uint32_t  mn0f4;                            // +0x0f4
    uint32_t  mn0f8;                            // +0x0f8
    uint32_t  mn0fc;                            // +0x0fc
    uint32_t  mn100;                            // +0x100
    uint32_t  mn104;                            // +0x104
    uint32_t  mn108;                            // +0x108
    void*     mpSelectionStreamers[5];          // +0x10c .. +0x11f

    void FUN_00cec6d0();                                                // 0x00cec6d0
    void DestroyAndRecreateCivUI(uint8_t bBuild);                       // 0x00cec7a0
    void NoteVehicleAdded(void* pNoun);                                 // 0x00ceb430
    void RebuildPosseBars();                                            // 0x00ce90c0
    void RefreshCityObject(void* pNoun);                                // 0x00ce8de0
};

}   // namespace Simulator

void __cdecl FUN_00ce8f70(void* pNoun, void* pMinimap);                         // 0x00ce8f70

namespace Simulator {

// ---------------------------------------------------------------------------------------------
// @ 0x00cec6d0
// ---------------------------------------------------------------------------------------------
void cCityDisplayStrategy::FUN_00cec6d0()
{
    if (mMiniMapWin.mpObject == 0)
        return;

    cGameNounManager* pManager = NounManager();
    cGameDataVector* pVehicles = pManager->GetGameDataVector(&g_funCD7D10, &g_funD3D420,
                                                             &g_funAE5EA0, &g_funB1E500,
                                                             &g_classKey403df5c);
    cNounPtrVector* pVector = &pVehicles->mVector;
    cNounPtrVector local;
    local.Resize((int32_t)(pVector->mpEnd - pVector->mpBegin), &pVector->mAllocator);

    void** ppCopiedEnd = local.mpBegin;
    _Construct(&ppCopiedEnd, pVector->mpBegin, pVector->mpEnd, local.mpBegin, ppCopiedEnd);

    for (void** pp = local.mpBegin; pp != ppCopiedEnd; ++pp)
        FUN_00ce8f70(*pp, mMiniMapWin.mpObject);

    for (void** pp = local.mpBegin; pp < ppCopiedEnd; ++pp)
    {
        cRefObject* pObject = (cRefObject*)*pp;
        if (pObject != 0)
            pObject->Release();
    }

    // the allocator counts its live blocks in the word in front of the buffer
    if (local.mpBegin != 0 && ((uint32_t*)local.mpBegin)[-1] != 0)
        operator_delete(local.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00cec7a0
// ---------------------------------------------------------------------------------------------
void cCityDisplayStrategy::DestroyAndRecreateCivUI(uint8_t bBuild)
{
    // tear the current civ UI down: its panels first, then the window's listener
    cGlobalCivUI* pCivUI = (cGlobalCivUI*)mGlobalCivUI.mpObject;
    if (pCivUI != 0)
    {
        pCivUI->Shutdown();
        pCivUI = (cGlobalCivUI*)mGlobalCivUI.mpObject;
        if (pCivUI != 0)
        {
            mGlobalCivUI.mpObject = 0;
            pCivUI->mListener.Release();
        }
    }

    // the four posses and their lookup trees
    for (int32_t i = 0; i < 4; ++i)
    {
        cPosseWindow* pPosse = (cPosseWindow*)mPosses[i].mpObject;
        if (pPosse != 0)
        {
            pPosse->DestroyPosseBar();
            if (mPosses[i].mpObject != 0)
            {
                mPosses[i].mpObject = 0;
                pPosse->Release();
            }
        }

        EventTree& rTree = mVehiclePosseMaps[i];
        rTree.Destroy(rTree.mpRoot);
        void* pAnchor = &rTree.mpAnchorLeft;
        rTree.mpAnchorLeft = pAnchor;
        rTree.mpAnchorRight = pAnchor;
        rTree.mpRoot = 0;
        rTree.mbColor = 0;
        rTree.mnSize = 0;
    }

    if (bBuild == 0)
        return;

    // the four posse bar labels, resolved through the localised text table
    SP::cString kMilitary(0xbeb528cb, 0x4d175ca, L"!!!Military");
    SP::cString kReligious(0xbeb528cb, 0x4d175cb, L"!!!Religious");
    SP::cString kEconomic(0xbeb528cb, 0x4d175cc, L"!!!Economic");
    SP::cString kHarvester(0xbeb528cb, 0x4d175cd, L"!!!Harvester");

    const wchar_t* apBarText[4];
    apBarText[0] = kMilitary.GetText();
    apBarText[1] = kReligious.GetText();
    apBarText[2] = kEconomic.GetText();
    apBarText[3] = kHarvester.GetText();

    // one bar per political category
    for (int32_t i = 0; i < 4; ++i)
    {
        cPosseWindow* pNew = (cPosseWindow*)FUN_009512d0(0x20c, 4, "UI/Posse", FUN_009512c0());
        if (pNew != 0)
            pNew = pNew->PosseCtor();

        cPosseWindow* pOld = (cPosseWindow*)mPosses[i].mpObject;
        if (pNew != pOld)
        {
            if (pNew != 0)
                pNew->AddRef();
            mPosses[i].mpObject = (cRefObject*)pNew;
            if (pOld != 0)
                pOld->Release();
        }

        cPosseWindow* pBar = (cPosseWindow*)mPosses[i].mpObject;
        if (!pBar->BindPosseBar(L"PosseBar", 3.1251f))
        {
            if (mPosses[i].mpObject != 0)
            {
                mPosses[i].mpObject = 0;
                pBar->Release();
            }
        }
        else
        {
            pBar->SetText(apBarText[i]);
            ((cPosseWindow*)mPosses[i].mpObject)->SetMode(2);
        }
    }

    RebuildPosseBars();

    cGameDataVector* pCityObjects = NounManager()->GetGameDataVector(&g_funCD7D10, &g_funD3D420,
                                                                     &g_funACDFF0, &g_funB1E500,
                                                                     &g_classKey18c43e8);

    // the global civ UI window, created on first use
    if (mGlobalCivUI.mpObject == 0)
    {
        cGlobalCivUI* pNew = (cGlobalCivUI*)operator new(0xf8, "Simulator/cSPGlobalUI-CivUI",
                                                         0, 0, 0, 0);
        if (pNew != 0)
            pNew = (cGlobalCivUI*)FUN_00e057a0(pNew);

        cGlobalCivUI* pOld = (cGlobalCivUI*)mGlobalCivUI.mpObject;
        if (pNew != pOld)
        {
            if (pNew != 0)
                pNew->mListener.AddRef();
            mGlobalCivUI.mpObject = (cRefObject*)pNew;
            if (pOld != 0)
                pOld->mListener.Release();
        }
        ((cGlobalCivUI*)mGlobalCivUI.mpObject)->Init(&g_classKey403df5c);
    }

    // the minimap window, sized from the civ UI's map rect
    cWindowObject* pCivWindow = ((cGlobalCivUI*)mGlobalCivUI.mpObject)->FindWindowByID(0x190722e);
    fRect* pMapRect = pCivWindow->GetRect();
    fRect afRect;
    afRect.fLeft = pMapRect->fLeft;
    afRect.fTop = pMapRect->fTop;
    afRect.fRight = pMapRect->fRight;
    afRect.fBottom = pMapRect->fBottom;

    cMinimapWindow* pNewMap = (cMinimapWindow*)FUN_009512d0(0x9a8, 8, "UI/CivMinimap",
                                                            FUN_009512c0());
    if (pNewMap != 0)
    {
        fVector2 fMin;
        fMin.fx = 0.0f;
        fMin.fy = 0.0f;
        fVector2 fMax;
        fMax.fx = -1.0f;
        fMax.fy = 1.0f;
        pNewMap = pNewMap->MinimapCtor((int32_t)(afRect.fRight - afRect.fLeft),
                                       (int32_t)(afRect.fBottom - afRect.fTop),
                                       &fMin, &fMax, 0, 0);
    }

    cMinimapWindow* pOldMap = (cMinimapWindow*)mMiniMapWin.mpObject;
    if (pNewMap != pOldMap)
    {
        if (pNewMap != 0)
            pNewMap->AddRef();
        mMiniMapWin.mpObject = (cRefObject*)pNewMap;
        if (pOldMap != 0)
            pOldMap->Release();
    }

    void* pIWindow = 0;
    if (mMiniMapWin.mpObject != 0)
        pIWindow = &((cMinimapWindow*)mMiniMapWin.mpObject)->mWindowInterface;
    pCivWindow->SetChildWindow(pIWindow);

    if (mMiniMapWin.mpObject != 0)
    {
        if (g_pSimSingleton == 0)
        {
            cSimSingleton* pSingleton = (cSimSingleton*)operator new(0xc8, "Simulator/SimSingleton",
                                                                     0, 0, 0, 0);
            if (pSingleton != 0)
                pSingleton = pSingleton->SimSingletonCtor();
            g_pSimSingleton = pSingleton;
        }

        // aim the minimap at the direction the player's tribe looks in
        cLookAt* pLookAt;
        if (*g_pSimSingleton->mpPlayerTribeId == -1)
        {
            cTribeObject* pTribe = (cTribeObject*)NounManager()->SetGameDataOwner2();
            if (pTribe != 0)
                pLookAt = &pTribe->mLookAt;
            else
                pLookAt = &((cTribeObject*)FUN_00b25c30(NounManager()))->mLookAt;
        }
        else
        {
            pLookAt = &((cTribeView*)FUN_00b993c0(*g_pSimSingleton->mpPlayerTribeId))->mLookAt;
        }

        fVector3* pView = pLookAt->PointAt();
        fVector3 afDir;
        afDir.fx = pView->fx;
        afDir.fy = pView->fy;
        float fScale = (float)(1.0 / sqrt(afDir.fy * afDir.fy + afDir.fx * afDir.fx + 1e-08f));
        afDir.fx = fScale * afDir.fx;
        afDir.fy = afDir.fy * fScale;
        afDir.fz = fScale * g_fRealZero;

        cMinimapWindow* pMap = (cMinimapWindow*)mMiniMapWin.mpObject;
        pMap->SetDirection(afDir);
        pMap->mfAngles[0] = 0.0f;
        pMap->mfAngles[1] = 0.0f;
        pMap->mfAngles[2] = g_fRealOne;
        pMap->SetViewMode(4);
        pMap->Refresh();

        // refresh every city object and vehicle the new map covers
        for (void** pp = pCityObjects->mVector.mpBegin; pp != pCityObjects->mVector.mpEnd; ++pp)
            RefreshCityObject(*pp);

        cGameDataVector* pVehicleNouns = NounManager()->GetGameDataVector(&g_funCD7D10,
                                                                          &g_funD3D420,
                                                                          &g_funAE72D0,
                                                                          &g_funB1E500,
                                                                          &g_classKey18c6de8);
        for (void** pp = pVehicleNouns->mVector.mpBegin; pp != pVehicleNouns->mVector.mpEnd; ++pp)
        {
            if (mMiniMapWin.mpObject != 0)
                NoteVehicleAdded(*pp);
        }
    }
}

}   // namespace Simulator
