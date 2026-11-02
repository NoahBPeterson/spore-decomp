// src/game/SPGonzago/SPUIShared.cpp -- migrated from slice(s) s00ec5e80, s00e2f6e0, s00e2e6e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIShared.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cRelationshipManager.h"
#include "cSPUILayout.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cViewer.h"
#include "SP/cSPAssetData.h"
#include "SP/cSPUIAssetView.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl operator_new(uint32_t nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
extern char   g_szStripLayout[];        // 0x01481838 "UI/cSPUIRelationshipStripLayout"
extern wchar_t g_szStripName[];         // 0x01481814 L"RelationshipStrip"
extern void*  g_stripDtorVtable[];      // 0x01481858 the panel's vtable while it tears itself down
extern void*  g_summarizerVtable[];     // 0x013ec458 Simulator::cContentValidationSummarizer
extern uint32_t g_uiImageKey;           // 0x00ef3c47cf

// ---- items of slice s00e2e6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  g_stripListenerVtable[];  // 0x014817a8 the message listener the strip registers
uint32_t __cdecl GetCurrentGameMode();                                 // 0x00b5b800
void*    __cdecl WindowManager();                                      // 0x0067caa0
void*    __cdecl MessageServer();                                      // 0x0067dcc0
void*    __cdecl FUN_00810000(void* pThis);                            // 0x00810000
class tIWindow;
class tIWindowEx;
class tIWindow {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04 Release
    virtual void* v08();                        // +0x08
    virtual void* v0c(uint32_t nKey);           // +0x0c
    virtual void* v10();                        // +0x10
    virtual void  v14(void* pState);            // +0x14
    virtual void  v18();                        // +0x18
    virtual void  v1c();                        // +0x1c
    virtual void  v20();                        // +0x20
    virtual void  v24();                        // +0x24
    virtual void  v28(int32_t nState);          // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void  v30(int32_t nA, int32_t nB);  // +0x30
    virtual void*    v34();                     // +0x34
    virtual void*    v38();                     // +0x38
    virtual void*    v3c(uint32_t nKey, int32_t nFlag); // +0x3c
    virtual void*    v40();                     // +0x40
    virtual void*    v44();                     // +0x44
    virtual uint32_t v48();                     // +0x48
    virtual int32_t  v4c();                     // +0x4c
    virtual void*    v50();                     // +0x50
    virtual uint32_t v54();                     // +0x54
    virtual uint32_t v58();                     // +0x58
    virtual void     v5c(int32_t nState);       // +0x5c sets the strip state
    virtual void     v60(int32_t nState);       // +0x60
    virtual void     v64();                     // +0x64
    virtual void     v68();                     // +0x68
    virtual void     v6c();                     // +0x6c
    virtual float    v70();                     // +0x70
    virtual void     v74();                     // +0x74
    virtual void     v78();                     // +0x78
    virtual void     v7c(int32_t nA, int32_t nB); // +0x7c visible/state pair
    virtual void     v80();                     // +0x80
    virtual void     v84();                     // +0x84
    virtual void     v88();                     // +0x88
    virtual void     v8c(void* pValue);         // +0x8c
    virtual void     v90();                     // +0x90
    virtual void     v94();                     // +0x94
    virtual void*    v98();                     // +0x98
    virtual void*    v9c();                     // +0x9c
    virtual void*    va0();                     // +0xa0
    virtual void*    va4();                     // +0xa4
    virtual void*    va8();                     // +0xa8
    virtual void*    vac();                     // +0xac
    virtual void*    vb0();                     // +0xb0
    virtual void*    vb4();                     // +0xb4
    virtual void*    vb8();                     // +0xb8
    virtual void*    vbc();                     // +0xbc
    virtual void*    vc0();                     // +0xc0
    virtual void*    vc4();                     // +0xc4
    virtual void*    vc8();                     // +0xc8
    virtual void*    vcc();                     // +0xcc
    virtual void*    vd0();                     // +0xd0
    virtual void*    vd4();                     // +0xd4
    virtual void*    vd8();                     // +0xd8
    virtual void*    vdc();                     // +0xdc
    virtual void*    ve0();                     // +0xe0
    virtual void*    ve4();                     // +0xe4
    virtual void*    ve8();                     // +0xe8
    virtual void*    vec();                     // +0xec
    virtual void*    vf0(uint32_t nKey, int32_t nFlag); // +0xf0
};
class tIWindowEx : public tIWindow {
};
class tRefObj {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04 Release
    virtual void* v08();                        // +0x08
};
class tChildHolder {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    uint32_t   mPad04[0x03];                    // +0x004
    tIWindow*  mp10;                            // +0x010
};
class tChildOwner {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    uint32_t   mPad04[0x03];                    // +0x004
    tIWindow   mWindow;                         // +0x010
};
class cSPUILayout_s00e2_e6e0 {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08

    cSPUILayout_s00e2_e6e0* FUN_00810000();                                            // 0x00810000
    tIWindow* FindWindowByID(uint32_t nID, int32_t nFlag);                  // 0x008105b0
    bool      Init(const wchar_t* pName, uint32_t nColor, int32_t nA, int32_t nB); // 0x00812160
    bool      SetParentWin(tIWindow* pParent, int32_t nA, int32_t nB);      // 0x008121b0
    void      Shutdown(uint32_t nFlag);                                     // 0x00811ad0
};
class cRelationshipManager {
public:
    bool  FUN_00d01b50(uint32_t nEmpireA, uint32_t nEmpireB);   // 0x00d01b50
    float FUN_00d00d00(uint32_t nEmpireA, uint32_t nEmpireB);   // 0x00d00d00
    int32_t FUN_00d00780(float fValue);                         // 0x00d00780
};
cRelationshipManager* __cdecl RelationshipManager();    // 0x00b3d2c0
class cMessageServer {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    virtual void* v0c();                        // +0x0c
    virtual void* v10();                        // +0x10
    virtual void* v14();                        // +0x14
    virtual void* v18();                        // +0x18
    virtual void* v1c();                        // +0x1c
    virtual void* v20();                        // +0x20
    virtual void  v24(void* pListener, uint32_t nTag);      // +0x24
};
class cWindowManager {
public:
    virtual void*    v00();                     // +0x00
    virtual tIWindow* v04();                    // +0x04 main window
};
struct tVisitMsg {
    uint32_t mn00;                  // +0x00
    void*    mp04;                  // +0x04 value pushed into the window
    bool     mb08;                  // +0x08 result the visitor returns
};
char   __cdecl FUN_00806230(tIWindow* pWindow, void** ppImage, char cA, int nB, int nC); // 0x00806230
bool   __cdecl VisitWindowTreeDepthFirst(tIWindow* pWindow, bool (*pFn)(tIWindow*, tVisitMsg*), void* pContext); // 0x00807d30
struct tWindowSpec {
    uint32_t  mn00;                 // +0x00 window id
    void*     mp04;                 // +0x04 parent window id
    uint8_t   mPad08[0x0c];         // +0x008
    bool      mb14;                 // +0x014 visible
    uint8_t   mPad15[0x03];         // +0x015
    void*     mp18;                 // +0x018 visit context
};
struct tListRec {
    uint32_t mn00;                  // +0x00
    uint32_t mn04;                  // +0x04
    uint32_t mPad08[0x05];          // +0x008
};
class cSPUIRelationshipStrip {
public:
    uint32_t     mpVtable;          // +0x00 (0x01481804)
    uint32_t     mn04;              // +0x04
    cSPUILayout_s00e2_e6e0* mp08;              // +0x08 the strip layout

    void FUN_00e2ec40();                                            // 0x00e2ec40
    void Init(tIWindow* pParent);                                   // 0x00e2ec60
    void FUN_00e2ed40();                                            // 0x00e2ed40
    void FUN_00e2ed70(int32_t nState);                              // 0x00e2ed70
    void FUN_00e2ef80(float fAmount);                               // 0x00e2ef80
};
class cRelationshipPanel {
public:
    uint32_t       mpVtable;        // +0x00 (0x01481858, then 0x013ec458)
    uint32_t       mn04;            // +0x04
    void*          mp08;            // +0x08 layout
    tChildOwner*   mp0c;            // +0x0c
    tIWindow*      mp10;            // +0x10 the strip window
    tRefObj*       mp14;            // +0x14
    tRefObj*       mp18;            // +0x18

    void FUN_00e2f160();            // 0x00e2f160
    void FUN_00e2f1c0();            // 0x00e2f1c0
    void FUN_00e2f250();            // 0x00e2f250
};
class cRelationsStrip {
public:
    uint32_t      mPad00[0x14];     // +0x000
    tChildHolder* mp50;             // +0x050
    int32_t       mn54;             // +0x054

    void FUN_00e2f270(bool bSelected);     // 0x00e2f270
};
class tRecordList {
public:
    uint32_t   mPad00[0x04];        // +0x000
    tListRec*  mpBegin;             // +0x010
    tListRec*  mpEnd;               // +0x014

    bool FUN_00e2f3c0(uint32_t nKey);       // 0x00e2f3c0
};
class cStripListener {
public:
    uint32_t     mpVtable;          // +0x00
    uint32_t     mPad04[0x10];      // +0x004
    cMessageServer* mp44;           // +0x044
    void*        mp48;              // +0x048
    void*        mp4c;              // +0x04c
    uint32_t     mn50;              // +0x050
    uint32_t     mn54;              // +0x054

    bool Init();                    // 0x00e2f370
};
// ---- items of slice s00e2e6e0 end

// ---- items of slice s00e2f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef int intptr_t;
#define nullptr 0
struct Rect {
    float mX;
    float mY;
    float mWidth;
    float mHeight;
};
class IRefCounted {
public:
    virtual void AddRef();                      // 0x00
    virtual void Release();                     // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);     // 0x0c
    virtual void v10();
};
class IWindow : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    virtual void SetVisible(bool bVisible);
    virtual void v20();
    virtual void v24();
    virtual void v28(int a);
    virtual void v2c();
    virtual Rect* GetArea();
    virtual void SetPosition(float fX, float fY);
    virtual void SetScale(float fScale);
};
class cSPUILayout_s00e2_f6e0 {
public:
    void Init(const wchar_t* pName, uint32_t a, int b, uint32_t c);  // 0x00812160 (cSPUILayout::Init)
    IWindow* FindWindowByID(uint32_t nId, int bFind);  // 0x008105b0 (cSPUILayout::FindWindowByID)
};
class cSPUIAnimator_s00e2_f6e0 {
public:
    void AddAnimation(void* pAnimation, void* pTarget, int nKind);  // 0x007f8d10 (cSPUIAnimator::AddAnimation)
    void RemoveAnimation(void* pTarget, int nIndex);  // 0x007f6210 (cSPUIAnimator::RemoveAnimation)
    void Update();  // 0x007f63b0 (cSPUIAnimator::Update)
};
class cSPAssetData : public IRefCounted {
public:
    virtual void v14();
    virtual void v18();
    bool IsDiscovered();
    uint8_t mPad18[0x08];
};
class cSPUIAssetView : public IWindow {
public:
    void Bind(IWindow* pParent, cSPAssetData* pData, int a, int b);
};
class cMessageTarget {
public:
    virtual void v00();
    virtual void v04();
};
class cSPUIAssetDiscoveryCard : public IRefCounted {
public:
    void Init();
    void ApplyFrame(int* pData);
    cSPUIAssetDiscoveryCard* Clone();

    cSPUILayout_s00e2_f6e0* mpLayout;              // 0x00
    IWindow* mpParentWin;               // 0x04
    uint8_t mPad08[0x08];               // 0x08
    IWindow* mpTextWindow;              // 0x10
    cSPAssetData* mpAssetData;          // 0x14
    cSPUIAssetView* mpAssetView;        // 0x18
};
class cSPUIAssetDiscoveryManager : public cMessageTarget {
public:
    void Init();
    void ReloadTuning();
    void Shutdown();
    void Reset();
    void Update(uint nMilliseconds);
    int HandleCardMessage(int nMessage, int nData, int nFlags);
    int HandleAssetMessage(int nMessage, int nData);
    void ReleaseCurrentCard();
    void PushCard(cSPUIAssetDiscoveryCard** ppCard, int nFlags);

    uint8_t mPad14[0x0c];               // 0x14
    void* mpMessageTarget;              // 0x20
    uint8_t mPad24[0x08];               // 0x24
    cSPUIAssetDiscoveryCard** mpCardsBegin;   // 0x2c
    cSPUIAssetDiscoveryCard** mpCardsCur;     // 0x30
    cSPUIAssetDiscoveryCard** mpCardsEnd;     // 0x34
    cSPUIAssetDiscoveryCard** mpCardsCap;     // 0x38
    cSPUIAssetDiscoveryCard* mpCurrentCard;   // 0x3c
    cSPUIAssetDiscoveryCard* mpSelectedCard;  // 0x50
    int mnPaused;                       // 0x54
    int mnAnimationState;               // 0x58
    cSPUIAnimator_s00e2_f6e0* mpAnimator;          // 0x5c
    uint64_t mnElapsed;                 // 0x60
    int mnSlideInStart;                 // 0x68
    int mnSlideOutStart;                // 0x6c
    int mnRotateStart;                  // 0x70
    int mnZoomStart;                    // 0x74
    int mnStopLow;                      // 0x78
    int mnStopHigh;                     // 0x7c
    int mnScaleLow;                     // 0x80
    int mnScaleHigh;                    // 0x84
    int mnRotateLow;                    // 0x88
    int mnRotateHigh;                   // 0x8c
    int mnZoomLow;                      // 0x90
    int mnZoomHigh;                     // 0x94
    int mnFinalLow;                     // 0x98
    int mnFinalHigh;                    // 0x9c
    float mFinalScale;                  // 0xa0
    float mTimeStart;                   // 0xa4
    float mTimeScaleBack;               // 0xa8
    float mTimeRotate;                  // 0xac
    float mTimeStop;                    // 0xb0
    float mTime;                        // 0xb4
    int mCount;                         // 0xb8
    int64_t mTimeStopMS;                // 0xbc
    int64_t mTimeStartMS;               // 0xc4
    int64_t mTimeScaleBackMS;           // 0xcc
    int64_t mTimeRotateMS;              // 0xd4
    int64_t mTimeMS;                    // 0xdc
};
void* PropertyManager();
bool QueryTuningFloat(void* pDefinition, uint32_t nKey, float* pOut);
bool QueryTuningInt(void* pDefinition, uint32_t nKey, int* pOut);
bool QueryDefinition(void* pPropertyManager, uint32_t nKey, void** ppOut);
void* CenterWindowInRect(void* pLayout, void* pArea);
void GetMainWindowArea(Rect* pOut);
void* CreateAssetData(int nKind);
void* CreateAssetView();
void* Controller_Award(uint32_t nAchievement);
void AwardAchievement(void* pController, uint32_t nAchievement);
void ResetCardState();
extern uint8_t gGameModeSpace;
// ---- items of slice s00e2f6e0 end

// ---- items of slice s00ec5e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
int  __cdecl FUN_00ec6a00(int state);           // 0x00ec6a00
// ---- items of slice s00ec5e80 end

// @ 0x00e2ec60
void cSPUIRelationshipStrip::Init(tIWindow* pParent)
{
    if (mp08 != 0)
        return;

    void* pMem = operator_new(0x18, g_szStripLayout, 0, 0, 0, 0);
    cSPUILayout_s00e2_e6e0* pNew = pMem != 0 ? ((cSPUILayout_s00e2_e6e0*)pMem)->FUN_00810000() : 0;

    cSPUILayout_s00e2_e6e0* pOld = mp08;
    if (pNew != pOld)
    {
        if (pNew != 0)
            pNew->v04();
        mp08 = pNew;
        if (pOld != 0)
            pOld->v08();
    }

    mp08->Init(g_szStripName, 0x40464100, 1, 0x5b598fa);
    mp08->SetParentWin(pParent, 1, 0x5b598fa);
    pParent->v94();
    pParent->v7c(1, 1);

    tIWindowEx* pWindow = (tIWindowEx*)mp08->FindWindowByID(0x956d74f6, 1);
    if (pWindow != 0)
    {
        if (GetCurrentGameMode() != 0x1654c02)
            pWindow->v5c(-1);
        else
            pWindow->v5c(0xff372829);
    }
}

// @ 0x00e2ed40
void cSPUIRelationshipStrip::FUN_00e2ed40()
{
    if (mp08 == 0)
        return;
    mp08->Shutdown(1);
    cSPUILayout_s00e2_e6e0* pOld = mp08;
    if (pOld != 0)
    {
        mp08 = 0;
        pOld->v08();
    }
}

// @ 0x00e2ed70
void cSPUIRelationshipStrip::FUN_00e2ed70(int32_t nState)
{
    for (uint32_t i = 0; i < 6; ++i)
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d01 + i, 1);
        tIWindowEx* pIcon = (tIWindowEx*)pSlot->v0c(0x0105a93d);
        if (pIcon != 0)
            pIcon->v14((void*)1);
    }

    switch (nState)
    {
    case 1:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d05, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        ((tIWindowEx*)mp08->FindWindowByID(0x4b47d01, 1))->v7c(1, 0);
        break;
    }
    case 2:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d01, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        ((tIWindowEx*)mp08->FindWindowByID(0x4b47d05, 1))->v7c(1, 0);
        break;
    }
    case 3:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d02, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    case 4:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d03, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    case 5:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d06, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    case 6:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d04, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    }
}

// @ 0x00e2ef80
void cSPUIRelationshipStrip::FUN_00e2ef80(float fAmount)
{
    for (uint32_t i = 0; i < 6; ++i)
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d01 + i, 1);
        tIWindowEx* pIcon = (tIWindowEx*)pSlot->v0c(0x0105a93d);
        if (pIcon != 0)
            pIcon->v14((void*)1);
    }

    ((tIWindowEx*)mp08->FindWindowByID(0x4b47d05, 1))->v7c(1, 0);

    switch (RelationshipManager()->FUN_00d00780(fAmount))
    {
    case 0:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d06, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    case 1:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d01, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    case 2:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d02, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    case 3:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d03, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    case 4:
    {
        tIWindowEx* pSlot = (tIWindowEx*)mp08->FindWindowByID(0x4b47d04, 1);
        pSlot->v7c(1, 1);
        ((tIWindowEx*)pSlot->v0c(0x0105a93d))->v14((void*)0);
        break;
    }
    }
}

// @ 0x00e2f160
void cRelationshipPanel::FUN_00e2f160()
{
    mpVtable = (uint32_t)g_stripDtorVtable;
    if (mp18 != 0)
        mp18->v04();
    if (mp14 != 0)
        mp14->v04();
    if (mp10 != 0)
        mp10->v04();
    if (mp0c != 0)
        mp0c->mWindow.v04();
    if (mp08 != 0)
        ((cSPUILayout_s00e2_e6e0*)mp08)->v08();
    mpVtable = (uint32_t)g_summarizerVtable;
}

// @ 0x00e2f1c0
void cRelationshipPanel::FUN_00e2f1c0()
{
    if (mp0c != 0)
    {
        mp0c->v08();
        tChildOwner* pOld = mp0c;
        if (pOld != 0)
        {
            mp0c = 0;
            pOld->mWindow.v04();
        }
    }
    if (mp10 != 0)
    {
        mp10->v20();
        tIWindow* pOld = mp10;
        if (pOld != 0)
        {
            mp10 = 0;
            pOld->v04();
        }
    }
    if (mp08 != 0)
    {
        ((cSPUILayout_s00e2_e6e0*)mp08)->Shutdown(1);
        cSPUILayout_s00e2_e6e0* pOld = (cSPUILayout_s00e2_e6e0*)mp08;
        if (pOld != 0)
        {
            mp08 = 0;
            pOld->v08();
        }
    }
    if (mp14 != 0)
    {
        tRefObj* pOld = mp14;
        mp14 = 0;
        pOld->v04();
    }
    if (mp18 != 0)
    {
        tRefObj* pOld = mp18;
        mp18 = 0;
        pOld->v04();
    }
}

// @ 0x00e2f250
void cRelationshipPanel::FUN_00e2f250()
{
    mp10->v30(0, 1);
    mp10->v2c();
}

// @ 0x00e2f270
void cRelationsStrip::FUN_00e2f270(bool bSelected)
{
    if (mp50 != 0)
        mp50->mp10->v28(bSelected == false);
    if (bSelected)
        ++mn54;
    else
        --mn54;
}

// @ 0x00e2f2b0
bool __cdecl FUN_00e2f2b0(tIWindow* pWindow, tVisitMsg* pMsg)
{
    if (pWindow->v4c() == 0)
    {
        pWindow->v8c(pMsg->mp04);
        pWindow->v90();
    }
    return pMsg->mb08;
}

// @ 0x00e2f300
bool __cdecl FUN_00e2f300(tIWindow* pWindow, tVisitMsg* pMsg)
{
    uint32_t nState = (uint32_t)pMsg->mp04;
    if (pWindow->v4c() == (int32_t)nState)
    {
        pWindow->v8c((void*)0);
        pWindow->v90();
    }
    return pMsg->mb08;
}

// @ 0x00e2f340
void __cdecl FUN_00e2f340(tIWindow* pWindow, tVisitMsg* pMsg)
{
    uint32_t nState = (uint32_t)pMsg->mp04;
    if (pWindow->v4c() == (int32_t)nState)
        VisitWindowTreeDepthFirst(pWindow, FUN_00e2f300, pMsg);
}

// @ 0x00e2f370
bool cStripListener::Init()
{
    void* pListener = this != 0 ? (void*)((uint8_t*)this + 8) : 0;
    cMessageServer* pServer = (cMessageServer*)MessageServer();
    mp44 = pServer;
    mp48 = pListener;
    mp4c = g_stripListenerVtable;
    mn50 = 1;
    mn54 = 0;
    if (pServer != 0 && pListener != 0)
        pServer->v24(pListener, 0xf62def);
    return true;
}

// @ 0x00e2f3c0
bool tRecordList::FUN_00e2f3c0(uint32_t nKey)
{
    tListRec* p = mpBegin;
    while (p != mpEnd)
    {
        if (nKey == p->mn00)
            return true;
        p = (tListRec*)((uint8_t*)p + 0x1c);
    }
    return false;
}

// @ 0x00e2f3f0
void __stdcall FUN_00e2f3f0(tWindowSpec* pSpec, int32_t nState)
{
    tIWindow* pWindow = ((cWindowManager*)WindowManager())->v04();
    if (pWindow == 0)
        return;
    pWindow = (tIWindow*)((tIWindowEx*)pWindow)->vf0(pSpec->mn00, 1);
    if (pWindow == 0)
        return;
    if (pSpec->mp04 != 0)
        pWindow = (tIWindow*)((tIWindowEx*)pWindow)->vf0((uint32_t)pSpec->mp04, 0);
    if (pWindow == 0)
        return;

    ((tIWindowEx*)pWindow)->v7c(1, 1);
    void* pContext = pSpec->mp18;
    if (pContext != 0)
    {
        if (((tIWindowEx*)pWindow)->v4c() != 0)
            return;
        VisitWindowTreeDepthFirst(pWindow, FUN_00e2f2b0, pContext);
    }
    else
    {
        ((tIWindowEx*)pWindow)->v5c(nState);
    }
}

// @ 0x00e2f480
void __stdcall FUN_00e2f480(tWindowSpec* pSpec)
{
    tIWindow* pWindow = ((cWindowManager*)WindowManager())->v04();
    if (pWindow == 0)
        return;
    pWindow = (tIWindow*)((tIWindowEx*)pWindow)->vf0(pSpec->mn00, 1);
    if (pWindow == 0)
        return;
    if (pSpec->mp04 != 0)
        pWindow = (tIWindow*)((tIWindowEx*)pWindow)->vf0((uint32_t)pSpec->mp04, 0);
    if (pWindow == 0)
        return;

    ((tIWindowEx*)pWindow)->v7c(1, !pSpec->mb14);
    if (pSpec->mp18 != 0)
    {
        FUN_00e2f340(pWindow, (tVisitMsg*)pSpec->mp18);
        return;
    }
    ((tIWindowEx*)pWindow)->v5c(0xffffffff);
}

// @ 0x00e2f5c0
void __cdecl SetImageFromKey(tIWindow* pWindow, uint32_t* pImageKey)
{
    tRefObj* pImage = 0;
    if (pWindow != 0 && ((tIWindowEx*)pWindow)->va8() != 0)
    {
        tIWindowEx* pOwner = (tIWindowEx*)((tIWindowEx*)pWindow)->va8();
        tIWindowEx* pImage2 = (tIWindowEx*)pOwner->v0c(g_uiImageKey);
        if (*pImageKey != 0)
        {
            if (pImage != 0)
            {
                pImage = 0;
                pImage->v04();
            }
            FUN_00806230(pWindow, (void**)&pImage, 0, -1, -1);
            pImage2->v14(pImage);
        }
        else
        {
            pImage2->v14((void*)0);
        }
        pWindow->v90();
    }
    if (pImage != 0)
        pImage->v04();
}

// @ 0x00e2f6e0
void cSPUIAssetDiscoveryCard::Init()
{
    if (mpLayout == nullptr) {
        cSPUILayout_s00e2_f6e0* pLayout = nullptr;
        void* pMemory = (void*)(intptr_t)operator_new(0x18, "UI/AssetDiscovery_Layout", 0, 0, 0, 0);
        if (pMemory != nullptr) {
            Rect area;
            GetMainWindowArea(&area);
            pLayout = (cSPUILayout_s00e2_f6e0*)CenterWindowInRect(pMemory, &area);
        }

        cSPUILayout_s00e2_f6e0* pOldLayout = mpLayout;
        if (pLayout != pOldLayout) {
            if (pLayout != nullptr)
                ((IRefCounted*)pLayout)->AddRef();
            mpLayout = pLayout;
            if (pOldLayout != nullptr)
                pOldLayout->FindWindowByID(0, 0);
        }
        mpLayout->Init(L"AssetDiscovery", 0x40464100u, 1, 0x2edd95cau);
    }

    IWindow* pWindow = mpLayout->FindWindowByID(0xb4ae091du, 1);
    IWindow* pOldParent = mpParentWin;
    if (pWindow != pOldParent) {
        if (pWindow != nullptr)
            pWindow->AddRef();
        mpParentWin = pWindow;
        if (pOldParent != nullptr)
            pOldParent->Release();
    }

    IWindow* pText = mpLayout->FindWindowByID(0xd4e16e94u, 1);
    IWindow* pOldText = mpTextWindow;
    if (pText != pOldText) {
        if (pText != nullptr)
            pText->AddRef();
        mpTextWindow = pText;
        if (pOldText != nullptr)
            pOldText->Release();
    }

    Rect area;
    GetMainWindowArea(&area);
    mpParentWin->v28(0);

    if (mpAssetData == nullptr) {
        cSPAssetData* pData = nullptr;
        uint32_t nMode = GetCurrentGameMode();
        void* pMemory = nullptr;
        if (nMode == 0 || (nMode + 0xfe9ab3fcu) < 2)
            pMemory = (void*)(intptr_t)operator_new(0x9c, "UI/AssetDiscovery_Data", 0, 0, 0, 0);
        else
            pMemory = (void*)(intptr_t)operator_new(0xb0, "UI/AssetDiscovery_Data", 0, 0, 0, 0);

        if (pMemory != nullptr)
            pData = (cSPAssetData*)CreateAssetData(0);

        cSPAssetData* pOldData = mpAssetData;
        if (pData != pOldData) {
            if (pData != nullptr)
                pData->AddRef();
            mpAssetData = pData;
            if (pOldData != nullptr)
                pOldData->Release();
        }
    }

    mpAssetData->v14();
    if (mpAssetData->IsDiscovered()) {
        uint32_t nMode = GetCurrentGameMode();
        if (nMode != (uint32_t)(intptr_t)&gGameModeSpace) {
            void* pController = Controller_Award(0xbde3bf2fu);
            AwardAchievement(pController, 0xbde3bf2fu);
        }
    }

    if (mpAssetView == nullptr) {
        cSPUIAssetView* pView = nullptr;
        void* pMemory = (void*)(intptr_t)operator_new(0x108, "UI/AssetDiscovery_View", 0, 0, 0, 0);
        if (pMemory != nullptr)
            pView = (cSPUIAssetView*)CreateAssetView();

        cSPUIAssetView* pOldView = mpAssetView;
        if (pView != pOldView) {
            if (pView != nullptr)
                pView->AddRef();
            mpAssetView = pView;
            if (pOldView != nullptr)
                pOldView->Release();
        }
    }

    mpAssetView->Bind(mpParentWin, mpAssetData, 0, 0);
    ResetCardState();
    mpAssetView->v28(0);
}

// @ 0x00e2f980
void cSPUIAssetDiscoveryManager::ReloadTuning()
{
    void* pPropertyManager = PropertyManager();
    void* pDefinition = nullptr;

    if (QueryDefinition(pPropertyManager, 0x5c770db7u, &pDefinition)) {
        uint32_t nFlags = 0;
        int nValue = 0;

        if (QueryTuningFloat(pDefinition, 0x2b12f9ecu, &mTimeStart))
            nFlags = 1;
        if (QueryTuningFloat(pDefinition, 0xa6f83fb3u, &mTimeScaleBack))
            nFlags = 1;
        if (QueryTuningFloat(pDefinition, 0x907d189du, &mTimeRotate))
            nFlags = 1;
        if (QueryTuningInt(pDefinition, 0xfd338528u, &nValue))
            mCount = nValue;
        if (QueryTuningFloat(pDefinition, 0x56e50a98u, &mTime))
            nFlags = 1;
        if (QueryTuningInt(pDefinition, 0x74cff359u, &nValue))
            mCount = nValue;
        if (QueryTuningInt(pDefinition, 0x7a927f57u, &nValue))
            mCount = nValue;

        mTimeStopMS = (int64_t)(mTimeStart * 1000.0f + 0.5f);
        mTimeStartMS = (int64_t)(mTimeScaleBack * 1000.0f + 0.5f);
        mTimeScaleBackMS = (int64_t)(mTimeRotate * 1000.0f + 0.5f);
        mTimeRotateMS = (int64_t)((float)nValue * 1000.0f + 0.5f);
        mTimeMS = (int64_t)(mTime * 1000.0f + 0.5f);
        (void)nFlags;
    }
}

// @ 0x00e2fc40
int cSPUIAssetDiscoveryManager::HandleCardMessage(int nMessage, int nData, int nFlags)
{
    if (nMessage == 0xf62def) {
        if (nData == 0x5c770db7)
            ReloadTuning();
        return 1;
    }
    if (nMessage != 0x533b6aa4) {
        if (nMessage == 0xd33b6aa2) {
            if (mpSelectedCard != nullptr)
                ((IRefCounted*)mpSelectedCard)->AddRef();
            ++mCount;
        }
        return 0;
    }
    if (mpSelectedCard != nullptr)
        ((IRefCounted*)mpSelectedCard)->AddRef();
    --mCount;
    return 0;
}

// @ 0x00ec6a00
int __cdecl FUN_00ec6a00(int state)
{
    switch (state) {
    case 0:  return 0xaaa0016;
    case 1:  return 0xaaa0010;
    case 2:  return 0xaaa0020;
    case 3:  return 0xaaa0013;
    case 4:  return 0xaaa0012;
    case 5:  return 0xaaa0017;
    case 6:  return 0xaaa0021;
    case 7:  return 0xaaa0023;
    case 8:  return 0xaaa0018;
    case 9:  return 0xaaa0019;
    case 10: return 0xaaa0022;
    case 11: return 0xaaa0015;
    case 12: return 0xaaa0014;
    case 13: return 0xaaa0011;
    case 14: return 0xaaa0070;
    default: return 0;
    }
}
