// Slice s00e2e6e0: the relationship-strip UI helpers - the empire friendliness badge, the five icon
// states of a relationship strip, the screen-position helpers that clamp a strip into the main window
// area, the strip's own layout/init/state switches and the shared window-find helpers underneath them.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; call targets are masked during comparison)
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl operator_new(uint32_t nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
extern "C" void  __cdecl operator_delete_array(void* pBlock);                                                          // 0x00f47380

extern char   g_szStripLayout[];        // 0x01481838 "UI/cSPUIRelationshipStripLayout"
extern wchar_t g_szStripName[];         // 0x01481814 L"RelationshipStrip"

extern void*  g_stripVtable[];          // 0x01481804 the strip object's own vtable
extern void*  g_stripDtorVtable[];      // 0x01481858 the panel's vtable while it tears itself down
extern void*  g_summarizerVtable[];     // 0x013ec458 Simulator::cContentValidationSummarizer
extern void*  g_stripListenerVtable[];  // 0x014817a8 the message listener the strip registers

// UI status strings, in fallback order
extern char   g_szStatusNone[];         // 0x015a56bc
extern char   g_szStatusUnknown[];      // 0x015a56c8
extern char   g_szStatusTerraform[];    // 0x015a56d4
extern char   g_szStatusTerraformed[];  // 0x015a56e0
extern char   g_szStatusProbe[];        // 0x015a56ec
extern char   g_szStatusOther[];        // 0x015a56f8
extern char   g_szStatusLocked[];       // 0x015a5704
extern char   g_szStatusBusy[];         // 0x015a5710

extern float  g_kOne;                   // 0x01485720 1.0f
extern float  g_kHalf;                  // 0x01471064 0.5f
extern float  g_kHundred;               // 0x013ec4d0 100.0f
extern float  g_kPercent;               // 0x013eb960 0.01f
extern float  g_kSignMask;              // 0x013eb8b0 0x80000000
extern float  g_kTenPercent;            // 0x01488874 0.1f
extern float  g_kTwenty;                // 0x013eecd8 20.0f

extern uint32_t g_gameModeGalaxy;       // 0x01654c02
extern uint32_t g_uiStripWindowID;      // 0x004b47d01 first of the six icon windows
extern char     g_szIconKey[];          // 0x0105a93d
extern uint32_t g_uiImageKey;           // 0x00ef3c47cf
extern uint32_t g_uiStripTag;           // 0x00f62def

uint32_t __cdecl GetPlayerEmpireID();                                  // 0x01021090
uint32_t __cdecl GetCurrentGameMode();                                 // 0x00b5b800
void*    __cdecl NounManager();                                        // 0x00b3d300
void*    __cdecl WindowManager();                                      // 0x0067caa0
void*    __cdecl MessageServer();                                      // 0x0067dcc0
void*    __cdecl App();                                                // 0x0067dd10
void*    __stdcall TerraformingManager(void* pNoun);                   // 0x00b3d430
void*    __cdecl FUN_00810000(void* pThis);                            // 0x00810000

// ---------------------------------------------------------------------------------------------
// the UTFWin window interface: one virtual per vtable byte offset
// ---------------------------------------------------------------------------------------------
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

// the same interface seen through its extended window type
class tIWindowEx : public tIWindow {
};

// the progress strip reads its three counts through the same window slots
class tIProgressWindow {
public:
    virtual void*    v00();                     // +0x00
    virtual void*    v04();                     // +0x04
    virtual void*    v08();                     // +0x08
    virtual void*    v0c(uint32_t nKey);        // +0x0c
    virtual void*    v10();                     // +0x10
    virtual void     v14(void* pState);         // +0x14
    virtual void     v18();                     // +0x18
    virtual void     v1c();                     // +0x1c
    virtual void     v20();                     // +0x20
    virtual void     v24();                     // +0x24
    virtual void     v28(int32_t nState);       // +0x28
    virtual void     v2c();                     // +0x2c
    virtual void     v30(int32_t nA, int32_t nB);// +0x30
    virtual void*    v34();                     // +0x34
    virtual void*    v38();                     // +0x38
    virtual void*    v3c(uint32_t nKey, int32_t nFlag); // +0x3c
    virtual void*    v40();                     // +0x40
    virtual void*    v44();                     // +0x44
    virtual uint32_t v48();                     // +0x48
    virtual int32_t  v4c();                     // +0x4c
    virtual void*    v50();                     // +0x50
    virtual uint32_t v54();                     // +0x54 friendly count
    virtual uint32_t v58();                     // +0x58 neutral count
    virtual uint32_t v5c();                     // +0x5c hostile count
};

// a plain ref-counted object (v00/v04/v08 only)
class tRefObj {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04 Release
    virtual void* v08();                        // +0x08
};

// a ref-counted object holding a window pointer at +0x10
class tChildHolder {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    uint32_t   mPad04[0x03];                    // +0x004
    tIWindow*  mp10;                            // +0x010
};

// a ref-counted object holding an embedded child window at +0x10
class tChildOwner {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08
    uint32_t   mPad04[0x03];                    // +0x004
    tIWindow   mWindow;                         // +0x010
};

class cSPUILayout {
public:
    virtual void* v00();                        // +0x00
    virtual void* v04();                        // +0x04
    virtual void* v08();                        // +0x08

    cSPUILayout* FUN_00810000();                                            // 0x00810000
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

// the app object only exposes its viewer getter
class tAppBase {
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
    virtual void* v24();                        // +0x24
    virtual void* v28();                        // +0x28
    virtual void* v2c();                        // +0x2c
    virtual void* v30();                        // +0x30
    virtual void* v34();                        // +0x34
    virtual void* v38();                        // +0x38
    virtual void* v3c();                        // +0x3c
    virtual void* v40();                        // +0x40
    virtual void* v44();                        // +0x44
    virtual void* v48();                        // +0x48
    virtual void* v4c();                        // +0x4c
    virtual void* v50();                        // +0x50
    virtual void* v54();                        // +0x54
};

struct tArea;
class tViewer;

class tApp2 : public tAppBase {
public:
    virtual tViewer* v58();                     // +0x58 the viewer
};

class tViewer {
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
    virtual void* v24();                        // +0x24

    void GetCameraLocationInfo(int32_t nA, int32_t nB, tArea* pCamera, tArea* pDirection); // 0x007c3d30
    void CenterOverObject(tArea* pOut, tArea* pIn);                                       // 0x007c4180
};

class cTerraformingManager {
public:
    int32_t F670();                             // 0x00bbc670
};

class cSimNoun {
public:
    virtual void*     v00();                    // +0x00
    virtual void*     v04();                    // +0x04
    virtual void*     v08();                    // +0x08
    virtual void*     v0c();                    // +0x0c
    virtual void*     v10();                    // +0x10
    virtual void*     v14();                    // +0x14
    virtual void*     v18();                    // +0x18
    virtual void*     v1c();                    // +0x1c
    virtual void*     v20();                    // +0x20
    virtual void*     v24();                    // +0x24
    uint32_t          mPad04[0x0a];             // +0x004
    uint32_t          mn2c;                     // +0x02c flags
    uint32_t          mPad30[0x28];             // +0x030
    void*             mpd0;                     // +0x0d0
    void*             mpd4;                     // +0x0d4

    int32_t GetNounType();                      // 0x00b8dab0
    int32_t FUN_00b8d9b0();                     // 0x00b8d9b0
};

// a 4-float rectangle / area handed around by the UI helpers
struct tArea {
    float x;                        // +0x00
    float y;                        // +0x04
    float z;                        // +0x08
    float w;                        // +0x0c
};

struct tRectEdge {
    float x0;                       // +0x00
    float y0;                       // +0x04
    float x1;                       // +0x08
    float y1;                       // +0x0c
};

// the context handed to the depth-first window visitors
struct tVisitMsg {
    uint32_t mn00;                  // +0x00
    void*    mp04;                  // +0x04 value pushed into the window
    bool     mb08;                  // +0x08 result the visitor returns
};

tArea* __cdecl GetMainWindowArea(tArea* pOut);                                  // 0x00805ea0
void   __cdecl FUN_00807430(void* pWindow, float fAmount);                      // 0x00807430
char   __cdecl FUN_00806230(tIWindow* pWindow, void** ppImage, char cA, int nB, int nC); // 0x00806230
bool   __cdecl VisitWindowTreeDepthFirst(tIWindow* pWindow, bool (*pFn)(tIWindow*, tVisitMsg*), void* pContext); // 0x00807d30

// a window-search spec used by the two find helpers
struct tWindowSpec {
    uint32_t  mn00;                 // +0x00 window id
    void*     mp04;                 // +0x04 parent window id
    uint8_t   mPad08[0x0c];         // +0x008
    bool      mb14;                 // +0x014 visible
    uint8_t   mPad15[0x03];         // +0x015
    void*     mp18;                 // +0x018 visit context
};

// a 0x1c-byte record with a key at +0
struct tListRec {
    uint32_t mn00;                  // +0x00
    uint32_t mn04;                  // +0x04
    uint32_t mPad08[0x05];          // +0x008
};

// ---------------------------------------------------------------------------------------------
// @ 0x00e2e6e0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e2e6e0(uint32_t nEmpire, tIWindow* pWindow)
{
    uint32_t nPlayer = GetPlayerEmpireID();
    bool bFriend = nEmpire == nPlayer;
    if (nEmpire != 0xffffffffu && nPlayer != 0xffffffffu && nPlayer != nEmpire)
        bFriend = RelationshipManager()->FUN_00d01b50(nEmpire, nPlayer);
    if (pWindow != 0)
    {
        pWindow->v7c(1, bFriend);
        if (bFriend)
        {
            float fAmount = g_kHundred;
            if (nEmpire != nPlayer)
                fAmount = RelationshipManager()->FUN_00d00d00(nEmpire, nPlayer);
            FUN_00807430(pWindow, fAmount * g_kPercent);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2e790
// ---------------------------------------------------------------------------------------------
void __cdecl UpdateProgessIcons(cSPUILayout* pLayout, tIWindowEx* pWindow)
{
    if (pLayout == 0 || pWindow == 0)
        return;

    tIProgressWindow* pCounts = (tIProgressWindow*)pWindow;
    uint32_t nFriendly = pCounts->v54();
    uint32_t nNeutral = pCounts->v58();
    uint32_t nHostile = pCounts->v5c();
    uint32_t i = 0;
    tIWindowEx* pSlot = (tIWindowEx*)pLayout->FindWindowByID(0xf4440000, 1);
    while (pSlot != 0)
    {
        tIWindowEx* pIcon = (tIWindowEx*)pSlot->v0c(0x0105a93d);
        if (pIcon != 0)
        {
            if (i < nFriendly)
            {
                pSlot->v7c(1, 1);
                pIcon->v14((void*)0);
            }
            else if (i < nNeutral)
            {
                pSlot->v7c(1, 1);
                pIcon->v14((void*)1);
            }
            else if (i < nHostile && nHostile > 0)
            {
                pSlot->v7c(1, 1);
                pIcon->v14((void*)2);
            }
            else
            {
                pSlot->v7c(1, 0);
            }
        }
        ++i;
        pSlot = (tIWindowEx*)pLayout->FindWindowByID(0xf4440000 + i, 1);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2e8a0
// ---------------------------------------------------------------------------------------------
void* __cdecl FUN_00e2e8a0(void* pBegin, void* pEnd, uint32_t nKeyA, uint32_t nKeyB)
{
    uint32_t* p = (uint32_t*)pBegin;
    uint32_t* pLast = (uint32_t*)pEnd;
    while (p != pLast && (p[0] != nKeyA || p[1] != nKeyB))
        p += 7;
    return p;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2e8d0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e2e8d0(float fX, float fY, float fOffset, tRectEdge* pEdge, float* pfX, float* pfY,
                          uint32_t* pFlag)
{
    float fHalfW = (pEdge->x1 - pEdge->x0) * g_kHalf;
    float fHigh = (pEdge->y1 - pEdge->y0) + fOffset;
    fHalfW = -fHalfW;
    fHigh = -fHigh;
    *pfX = fHalfW + fX;
    *pfY = fHigh + fY;

    tArea area;
    GetMainWindowArea(&area);
    if (area.x > *pfX)
        *pfX = area.x;

    float fExtent = pEdge->x1 - pEdge->x0;
    if (*pfX + fExtent > area.z)
    {
        *pfX = area.z - fExtent;
        *pFlag = 0;
        return;
    }
    *pFlag = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2e990
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e2e990(tArea* pVec, float fOffset, tRectEdge* pEdge, float* pfX, float* pfY,
                          uint32_t* pFlag)
{
    tArea vView;
    ((tApp2*)App())->v58()->CenterOverObject(&vView, pVec);

    tArea area;
    GetMainWindowArea(&area);
    *pfX = (vView.x + g_kOne) * area.z * g_kHalf;
    *pfY = (g_kOne - vView.y) * area.w * g_kHalf;

    float fHalfW = (pEdge->x1 - pEdge->x0) * g_kHalf;
    float fHigh = (pEdge->y1 - pEdge->y0) + fOffset;
    fHalfW = -fHalfW;
    fHigh = -fHigh;
    *pfX = fHalfW + *pfX;
    *pfY = fHigh + *pfY;

    tArea area2;
    GetMainWindowArea(&area2);
    if (area2.x > *pfX)
        *pfX = area2.x;

    float fExtent = pEdge->x1 - pEdge->x0;
    if (*pfX + fExtent > area2.z)
    {
        *pfX = area2.z - fExtent;
        *pFlag = 0;
        return;
    }
    *pFlag = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2eab0
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e2eab0(tIWindowEx* pWindow, uint32_t nA, uint32_t nB, uint32_t nC, uint32_t nD,
                          float fOffset)
{
    tArea vCamera;
    tArea vDir;
    ((tApp2*)App())->v58()->GetCameraLocationInfo(0, 0, &vCamera, &vDir);

    float fDistance = pWindow->v70();
    fDistance *= g_kTenPercent;
    if (fDistance <= g_kTwenty)
        fDistance = g_kTwenty;

    tArea* pPos = (tArea*)pWindow->v2c();
    tArea vOffset;
    vOffset.x = vDir.x * fDistance + pPos->x;
    vOffset.y = vDir.y * fDistance + pPos->y;
    vOffset.z = vDir.z * fDistance + pPos->z;

    FUN_00e2e990(&vOffset, fOffset, (tRectEdge*)nA, (float*)nB, (float*)nC, (uint32_t*)nD);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2eba0
// ---------------------------------------------------------------------------------------------
char* __cdecl FUN_00e2eba0(cSimNoun* pNoun)
{
    switch (pNoun->GetNounType())
    {
    case 1:
        if (pNoun->FUN_00b8d9b0() != 0)
            return g_szStatusBusy;
        if (((cTerraformingManager*)TerraformingManager(pNoun))->F670() != 0)
        {
            if ((pNoun->mn2c & 0x800) != 0)
                return g_szStatusLocked;
            if (pNoun->mpd0 != pNoun->mpd4)
                return g_szStatusTerraform;
            return g_szStatusUnknown;
        }
        break;
    case 2:
        return g_szStatusTerraformed;
    case 4:
        return g_szStatusProbe;
    case 5:
        return g_szStatusOther;
    }
    return g_szStatusNone;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2ec40
// ---------------------------------------------------------------------------------------------
class cSPUIRelationshipStrip {
public:
    uint32_t     mpVtable;          // +0x00 (0x01481804)
    uint32_t     mn04;              // +0x04
    cSPUILayout* mp08;              // +0x08 the strip layout

    void FUN_00e2ec40();                                            // 0x00e2ec40
    void Init(tIWindow* pParent);                                   // 0x00e2ec60
    void FUN_00e2ed40();                                            // 0x00e2ed40
    void FUN_00e2ed70(int32_t nState);                              // 0x00e2ed70
    void FUN_00e2ef80(float fAmount);                               // 0x00e2ef80
};

void cSPUIRelationshipStrip::FUN_00e2ec40()
{
    mn04 = 0;
    mpVtable = (uint32_t)g_stripVtable;
    mp08 = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2ec60
// ---------------------------------------------------------------------------------------------
void cSPUIRelationshipStrip::Init(tIWindow* pParent)
{
    if (mp08 != 0)
        return;

    void* pMem = operator_new(0x18, g_szStripLayout, 0, 0, 0, 0);
    cSPUILayout* pNew = pMem != 0 ? ((cSPUILayout*)pMem)->FUN_00810000() : 0;

    cSPUILayout* pOld = mp08;
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2ed40
// ---------------------------------------------------------------------------------------------
void cSPUIRelationshipStrip::FUN_00e2ed40()
{
    if (mp08 == 0)
        return;
    mp08->Shutdown(1);
    cSPUILayout* pOld = mp08;
    if (pOld != 0)
    {
        mp08 = 0;
        pOld->v08();
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2ed70
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2ef80
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// the panel that owns the strip's layout and its message listener
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f160
// ---------------------------------------------------------------------------------------------
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
        ((cSPUILayout*)mp08)->v08();
    mpVtable = (uint32_t)g_summarizerVtable;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f1c0
// ---------------------------------------------------------------------------------------------
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
        ((cSPUILayout*)mp08)->Shutdown(1);
        cSPUILayout* pOld = (cSPUILayout*)mp08;
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f250
// ---------------------------------------------------------------------------------------------
void cRelationshipPanel::FUN_00e2f250()
{
    mp10->v30(0, 1);
    mp10->v2c();
}

// ---------------------------------------------------------------------------------------------
// the strip's selection holder
// ---------------------------------------------------------------------------------------------
class cRelationsStrip {
public:
    uint32_t      mPad00[0x14];     // +0x000
    tChildHolder* mp50;             // +0x050
    int32_t       mn54;             // +0x054

    void FUN_00e2f270(bool bSelected);     // 0x00e2f270
};

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f270
// ---------------------------------------------------------------------------------------------
void cRelationsStrip::FUN_00e2f270(bool bSelected)
{
    if (mp50 != 0)
        mp50->mp10->v28(bSelected == false);
    if (bSelected)
        ++mn54;
    else
        --mn54;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f2b0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00e2f2b0(tIWindow* pWindow, tVisitMsg* pMsg)
{
    if (pWindow->v4c() == 0)
    {
        pWindow->v8c(pMsg->mp04);
        pWindow->v90();
    }
    return pMsg->mb08;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f300
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f340
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00e2f340(tIWindow* pWindow, tVisitMsg* pMsg)
{
    uint32_t nState = (uint32_t)pMsg->mp04;
    if (pWindow->v4c() == (int32_t)nState)
        VisitWindowTreeDepthFirst(pWindow, FUN_00e2f300, pMsg);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f3c0
// ---------------------------------------------------------------------------------------------
class tRecordList {
public:
    uint32_t   mPad00[0x04];        // +0x000
    tListRec*  mpBegin;             // +0x010
    tListRec*  mpEnd;               // +0x014

    bool FUN_00e2f3c0(uint32_t nKey);       // 0x00e2f3c0
};

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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f370
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f3f0
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f480
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// @ 0x00e2f5c0
// ---------------------------------------------------------------------------------------------
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
