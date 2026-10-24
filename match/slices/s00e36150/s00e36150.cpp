// s00e36150 -- the space-stage tooltip panel, the timed tooltip widget it
// drives, and the game-mode id helpers.
//
//   0x00e36150 cSPUITooltipPanel ctor         0x00e36670 bounds accumulation
//   0x00e36260 dtor                           0x00e36890 tooltip deleting dtor
//   0x00e362f0 render                         0x00e368e0 layout reload callback
//   0x00e36480 cUITimedTooltip ctor           0x00e369f0 layout update
//   0x00e364d0 dtor                           0x00e36b30 layout init
//   0x00e36500 shutdown                       0x00e36c80 game-mode hash
//   0x00e36540 timeout A                      0x00e36cd0 .. 0x00e36e80 timeouts
//   0x00e365a0 timeout B                      0x00e36de0 state reset
//   0x00e36620 hide                           0x00e36ed0 game level
//   0x00e36650 find window                    0x00e36f50 mode index
//                                             0x00e36fb0 slot accessor
//                                             0x00e36fd0 editor state
#include "types.h"

#define nullptr 0

// ---------------------------------------------------------------------------
// engine types
// ---------------------------------------------------------------------------

struct Vector4 {
    float x;
    float y;
    float z;
    float w;
};

struct RectF {
    float x0;
    float y0;
    float x1;
    float y1;
};

struct cTooltipSlot {
    float m_fX;
    float m_fY;
    float m_fW;
};

// every engine object here shares the same reference-counted base: slot +0 is
// AddRef, slot +4 is Release.
class IBase {
public:
    virtual void* Slot00() = 0;
    virtual void* Slot04() = 0;
    virtual void* Slot08() = 0;
    virtual void* Slot0c() = 0;
    virtual void* Slot10() = 0;
    virtual void* Slot14() = 0;
    virtual void* Slot18() = 0;
    virtual void* Slot1c() = 0;
    virtual void* Slot20() = 0;
    virtual void* Slot24() = 0;
    virtual void* Slot28() = 0;
    virtual void* Slot2c() = 0;
    virtual void* Slot30() = 0;
    virtual void* Slot34() = 0;
    virtual void* Slot38() = 0;
    virtual void* Slot3c() = 0;
    virtual void* Slot40() = 0;
    virtual void* Slot44() = 0;
    virtual void* Slot48() = 0;
    virtual void* Slot4c() = 0;
    virtual void* Slot50() = 0;
    virtual void* Slot54() = 0;
    virtual void* Slot58() = 0;
    virtual void* Slot5c() = 0;
    virtual ~IBase() {}
};

// EA's high-resolution stopwatch: two 64-bit counter snapshots, the counter
// source id and the multiplier that turns ticks into the caller's unit.
namespace EA {
class Stopwatch {
public:
    Stopwatch() {}
    Stopwatch(int32_t nSource, bool bStart);     // 0x0093a560
    void Restart();                              // 0x00571e80
    int64_t GetElapsedTime();                    // 0x0093a5e0
    int64_t GetElapsedTimeFloat();               // 0x0093a3a0
    void SetBoolProperty();                      // 0x0093a2e0

    int64_t m_nStart;                            // +0x00
    int64_t m_nStop;                             // +0x08
    int32_t m_nSource;                           // +0x10
    float m_fRate;                               // +0x14
};
}

// the UI layout document
class cSPUILayout {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
    virtual void Release2();                     // +0x08
    void Shutdown(uint32_t nFlags);              // 0x00811ad0
    void SetVisibility(bool bVisible);           // 0x00810590
    bool IsVisible();                            // 0x00810070
    void* FindWindowByID(uint32_t nId, bool bFlag);            // 0x008105b0
    bool SetParentWin(void* pWin, bool bFlag, uint32_t nId);   // 0x008121b0
    bool Init(const void* pKey, bool bFlag, uint32_t nId);     // 0x008120d0
    void SetReloadCallback(void (__cdecl* pCallback)(void*, cSPUILayout*,
                                                     bool),
                           void* pUser);                       // 0x00810090
    void* GetWindow();                                         // 0x00810570
    cSPUILayout* InitDocument();                               // 0x00810000
};

// a UTFWin window
class IWin {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
    virtual void SetVisible2(bool bVisible);     // +0x08
    virtual void W0c();  virtual void W10();  virtual void W14();  virtual void W18();
    virtual void W1c();  virtual void W20();  virtual void W24();  virtual void W28();
    virtual void W2c();  virtual void W30();  virtual void W34();  virtual void W38();
    virtual void W3c();  virtual void W40();  virtual void W44();  virtual void W48();
    virtual void W4c();  virtual void W50();  virtual void W54();  virtual void W58();
    virtual void W5c();  virtual void W60();  virtual void W64();  virtual void W68();
    virtual void SetRect6c(RectF* pRect);        // +0x6c
    virtual void W70();  virtual void W74();  virtual void W78();
    virtual void SetFlags7c(bool bFlag, bool bOther);          // +0x7c
    virtual void W80();  virtual void W84();  virtual void W88();  virtual void W8c();
    virtual void W90();  virtual void W94();  virtual void W98();  virtual void W9c();
    virtual void Wa0();  virtual void Wa4();  virtual void Wa8();  virtual void Wac();
    virtual void Wb0();  virtual void Wb4();  virtual void Wb8();  virtual void Wbc();
    virtual void Wc0();  virtual void Wc4();  virtual void Wc8();  virtual void Wcc();
    virtual void Wd0();  virtual void Wd4();
    virtual void SetParentd8(IWin* pParent);     // +0xd8
};

// the UI animator that gates the tooltip fades
class cSPUIAnimator : public IBase {
public:
    bool Empty();                                // 0x007f6340
};

// a UI element node; the element tree iterators are offsets into a global
// arena, so a node pointer is arena-base + offset
class IWinNode : public IBase {
public:
    virtual void* S00() = 0;  virtual void* S04() = 0;  virtual void* S08() = 0;
    virtual void* S0c() = 0;  virtual void* S10() = 0;  virtual void* S14() = 0;
    virtual void* S18() = 0;  virtual void* S1c() = 0;  virtual void* S20() = 0;
    virtual void* S24() = 0;
    virtual uint32_t S28() = 0;
    virtual void* S2c() = 0;  virtual void* S30() = 0;  virtual void* S34() = 0;
    virtual RectF* S38() = 0;
    virtual void* S3c() = 0;  virtual void* S40() = 0;  virtual void* S44() = 0;
    virtual void* S48() = 0;  virtual void* S4c() = 0;  virtual void* S50() = 0;
    virtual void* S54() = 0;  virtual void* S58() = 0;  virtual void* S5c() = 0;
    virtual void* S60() = 0;  virtual void* S64() = 0;  virtual void* S68() = 0;
    virtual void* S6c() = 0;
    virtual void S70(float fX, float fY) = 0;
    virtual void S74(float fWidth, float fHeight) = 0;
    virtual void* S78() = 0;  virtual void* S7c() = 0;  virtual void* S80() = 0;
    virtual void* S84() = 0;  virtual void* S88() = 0;  virtual void* S8c() = 0;
    virtual void* S90() = 0;  virtual void* S94() = 0;  virtual void* S98() = 0;
    virtual void* S9c() = 0;  virtual void* SA0() = 0;  virtual void* SA4() = 0;
    virtual void* SA8() = 0;  virtual void* SAc() = 0;  virtual void* SB0() = 0;
    virtual void* SB4() = 0;  virtual void* SB8() = 0;  virtual void* SBc() = 0;
    virtual void* SC0() = 0;  virtual void* SC4() = 0;  virtual void* SC8() = 0;
    virtual void Scc(uint32_t** ppIter) = 0;
    virtual void Sd0(uint32_t** ppEnd) = 0;
};

// the graphics window manager
class cWindowManager {
public:
    virtual void M00();
    virtual void* GetView();                     // +0x04
    virtual void SetWindow(IWin* pWindow, bool bFlag);            // +0x08
    virtual void SetViewport(float fWidth, float fHeight);        // +0x0c
    virtual void M10();  virtual void M14();  virtual void M18();  virtual void M1c();
    virtual void M20();
    virtual void Reset24();                      // +0x24
};

// the view object the window manager hands out
class IView {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
    virtual void V08();  virtual void V0c();  virtual void V10();  virtual void V14();
    virtual void V18();  virtual void V1c();  virtual void V20();  virtual void V24();
    virtual void V28();  virtual void V2c();  virtual void V30();
    virtual Vector4* GetBounds();                // +0x34
};

// the offline viewer the tooltip renders through
class cViewer {
public:
    cViewer* Construct();                        // 0x007c3f70
    bool Init(bool bFlag);                       // 0x007c4dd0
    void SetRaster(void* pRaster, bool bFlag);   // 0x007c4be0
    void Shutdown();                             // 0x007c4000
};

// the bounding box accumulated while rendering
class cBoundingBox {
public:
    virtual void* S00();
    virtual void* S04();
    virtual void* S08();
    virtual void AddPoints(uint32_t a1, uint32_t a2, const Vector4* pPoints,
                           uint32_t a3);         // +0x0c
};

// the editor singleton touched by the state reset
class cEditor {
public:
    uint8_t mPad000[0x284];                      // +0x000
    int32_t m_nState;                            // +0x284
};

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------

extern uint8_t* gspUIElementBase;                // 0x01440aec

uint32_t __cdecl SP_GetCurrentGameMode();        // 0x00b5b800
void* __cdecl SP_WindowManager();                // 0x0067caa0
void* __cdecl cSPBoundingBox_AddBoundingBox();   // 0x0067cad0
void __cdecl FUN_00808b20(IWin* pTarget, IWin* pSource, char cArg);   // 0x00808b20
void* __cdecl FUN_009512c0();                    // 0x009512c0
void* __stdcall FUN_009512d0(uint32_t nSize, uint32_t nAlign,
                             const char* pType, void* pAlloc);         // 0x009512d0
void* __stdcall FUN_00962a10(void* pWindow);     // 0x00962a10
void* __stdcall operator_new(uint32_t nSize, const void* pFile,
                             uint32_t a, uint32_t b, uint32_t c,
                             uint32_t d);        // 0x00f473a0
void __stdcall operator_delete_array(void* pObject);           // 0x00f47380
void* __cdecl FUN_00b3d410();                    // 0x00b3d410
uint32_t __cdecl GetGameModeHash();              // 0x00e36c80

Vector4* __cdecl AccumulateBounds(Vector4* pOut, IWinNode* pNode, bool bDeep,
                                  bool bFilter);  // 0x00e36670

// ---------------------------------------------------------------------------
// the tooltip panel: a window the tooltip is drawn into
// ---------------------------------------------------------------------------

class cSPUITooltipPanel : public IBase {
public:
    cSPUITooltipPanel(float fSize, cSPUILayout* pLayout, void* pRaster,
                      void* pOwner);                            // 0x00e36150
    ~cSPUITooltipPanel();                                       // 0x00e36260
    void Render(uint32_t a1, uint32_t a2, uint32_t a3,
                uint32_t a4);                                   // 0x00e362f0

    uint32_t m_nKey08;                           // +0x008
    IWin* m_pWindow0c;                           // +0x00c
    cSPUILayout* m_pLayout10;                    // +0x010
    void* m_pRaster14;                           // +0x014
    void* m_pOwner18;                            // +0x018
    IWin* m_pTargetWin1c;                        // +0x01c
    RectF m_rect20;                              // +0x020
};

// @ 0x00e36150
cSPUITooltipPanel::cSPUITooltipPanel(float fSize, cSPUILayout* pLayout,
                                     void* pRaster, void* pOwner)
    : m_nKey08(0),
      m_pWindow0c(0),
      m_pLayout10(pLayout),
      m_pRaster14(pRaster),
      m_pOwner18(pOwner),
      m_pTargetWin1c(0)
{
    if (m_pLayout10 != nullptr)
        m_pLayout10->Release1();

    m_rect20.x0 = 0.0f;
    m_rect20.y0 = 0.0f;
    m_rect20.x1 = fSize;
    m_rect20.y1 = fSize;

    m_pTargetWin1c = (IWin*)m_pLayout10->GetWindow();
    m_pWindow0c = (IWin*)FUN_009512d0(0x20c, 4, "UI/UTFWin/Window",
                                      FUN_009512c0());
    if (m_pWindow0c != nullptr)
        m_pWindow0c = (IWin*)FUN_00962a10(m_pWindow0c);

    m_pLayout10->SetParentWin(m_pWindow0c, true, 0x5b598fa);
}

// @ 0x00e36260
cSPUITooltipPanel::~cSPUITooltipPanel()
{
    if (m_pLayout10 == nullptr) {
        if (m_pTargetWin1c != nullptr) {
            m_pTargetWin1c->SetParentd8(m_pWindow0c);
            m_pWindow0c->SetRect6c(&m_rect20);
        }
    } else {
        m_pLayout10->SetParentWin(m_pTargetWin1c, false, 0x5b598fa);
    }

    if (m_pTargetWin1c != nullptr)
        m_pTargetWin1c->Release1();
    if (m_pLayout10 != nullptr)
        m_pLayout10->Release2();
    if (m_pWindow0c != nullptr)
        m_pWindow0c->Release1();
}

// @ 0x00e362f0
void cSPUITooltipPanel::Render(uint32_t a1, uint32_t a2, uint32_t a3,
                               uint32_t a4)
{
    cWindowManager* pManager = (cWindowManager*)SP_WindowManager();
    cViewer viewer;
    viewer.Construct();
    viewer.Init(false);
    viewer.SetRaster(&m_pRaster14, true);

    IView* pView = (IView*)pManager->GetView();
    if (pView != nullptr)
        pView->AddRef0();

    Vector4 bounds = *pView->GetBounds();
    pManager->SetWindow(m_pWindow0c, false);
    pManager->SetViewport(m_rect20.x1 - m_rect20.x0,
                          m_rect20.y1 - m_rect20.y0);
    pManager->Reset24();

    Vector4 points;
    points.x = 0.0f;
    points.y = 0.0f;
    points.z = 0.0f;
    points.w = 0.0f;
    cBoundingBox* pBox = (cBoundingBox*)cSPBoundingBox_AddBoundingBox();
    pBox->AddPoints(a4, a4, &points, a4);

    pManager->SetViewport(m_rect20.x1 - m_rect20.x0 + (bounds.x - a3),
                          m_rect20.y1 - m_rect20.y0 + (bounds.y - a4));
    pManager->Reset24();
    pManager->SetWindow(m_pWindow0c, false);

    if (pView != nullptr)
        pView->Release1();
    viewer.Shutdown();
}

// ---------------------------------------------------------------------------
// the timed tooltip widget
// ---------------------------------------------------------------------------

class cUITimedTooltip : public IBase {
public:
    cUITimedTooltip();                                          // 0x00e36480
    ~cUITimedTooltip();                                         // 0x00e364d0
    void Shutdown();                                            // 0x00e36500
    void UpdateTimeoutA();                                      // 0x00e36540
    void UpdateTimeoutB(IWin* pWindow);                         // 0x00e365a0
    void Hide();                                                // 0x00e36620
    void* FindWindow(uint32_t nId, bool bFlag);                 // 0x00e36650
    void* DestroyDeleting(bool bDelete);                        // 0x00e36890
    void UpdateLayout();                                        // 0x00e369f0
    bool Init(const uint32_t& nKey, uint32_t nId, uint32_t nWidth,
              uint32_t nHeight, uint32_t a5, uint32_t a6);      // 0x00e36b30
    void ResetState();                                          // 0x00e36de0
    bool UpdateA();                                             // 0x00e36cd0
    bool UpdateB();                                             // 0x00e36d30
    bool UpdateC();                                             // 0x00e36d80
    bool UpdateD();                                             // 0x00e36e20
    bool UpdateE();                                             // 0x00e36e80
    cTooltipSlot* GetSlot(int32_t nIndex);                      // 0x00e36fb0

    uint32_t m_nPad04;                           // +0x004
    uint32_t m_nKey08;                           // +0x008
    cSPUILayout* m_pLayout;                      // +0x00c
    IWin* m_pWindow;                             // +0x010
    uint8_t mPad14[0x4];                         // +0x014
    EA::Stopwatch m_swA;                         // +0x018
    EA::Stopwatch m_swB;                         // +0x030
    uint32_t m_nTimeoutA;                        // +0x048
    uint32_t m_nTimeoutB;                        // +0x04c
    float m_f50;                                 // +0x050
    float m_f54;                                 // +0x054
    float m_f58;                                 // +0x058
    float m_f5c;                                 // +0x05c
    uint8_t mPad60[0x390];                       // +0x060
    uint32_t m_nMode3f0;                         // +0x3f0
    uint8_t mPad3f4[0x4];                        // +0x3f4
    EA::Stopwatch m_sw3f8;                       // +0x3f8
    float m_fThreshold410;                       // +0x410
    uint8_t mPad414[0x4];                        // +0x414
    EA::Stopwatch m_sw418;                       // +0x418
    float m_fThreshold430;                       // +0x430
    uint8_t mPad434[0x4];                        // +0x434
    EA::Stopwatch m_sw438;                       // +0x438
    float m_fThreshold450;                       // +0x450
    bool m_bFlag454;                             // +0x454
    uint8_t mPad455[0x3];                        // +0x455
    cSPUIAnimator* m_pAnimator458;               // +0x458
    uint8_t mPad45c[0x4c];                       // +0x45c
    EA::Stopwatch m_sw4a8;                       // +0x4a8
    float m_fThreshold4c0;                       // +0x4c0
    uint8_t mPad4c4[0x4];                        // +0x4c4
    EA::Stopwatch m_sw4c8;                       // +0x4c8
    float m_fThreshold4e0;                       // +0x4e0
    uint8_t mPad4e4[0x9c];                       // +0x4e4
    cTooltipSlot m_slots[4];                     // +0x580
};

// @ 0x00e36480
cUITimedTooltip::cUITimedTooltip()
    : m_nPad04(0),
      m_nKey08(0),
      m_pLayout(0),
      m_pWindow(0),
      m_swA(0, false),
      m_swB(0, false)
{
    m_nTimeoutA = 0;
    m_nTimeoutB = 0;
    m_f50 = 0.0f;
    m_f54 = 0.0f;
    m_f58 = 0.0f;
    m_f5c = 0.0f;
}

// @ 0x00e364d0
cUITimedTooltip::~cUITimedTooltip()
{
    if (m_pWindow != nullptr)
        m_pWindow->Release1();
    if (m_pLayout != nullptr)
        m_pLayout->Release2();
}

// @ 0x00e36890
void* cUITimedTooltip::DestroyDeleting(bool bDelete)
{
    if (m_pWindow != nullptr)
        m_pWindow->Release1();
    if (m_pLayout != nullptr)
        m_pLayout->Release2();
    if (bDelete)
        operator_delete_array(this);
    return this;
}

// @ 0x00e36500
void cUITimedTooltip::Shutdown()
{
    if (m_pLayout != nullptr)
        m_pLayout->Shutdown(1);
    if (m_pLayout != nullptr) {
        cSPUILayout* pLayout = m_pLayout;
        m_pLayout = nullptr;
        pLayout->Release2();
    }
    if (m_pWindow != nullptr) {
        IWin* pWindow = m_pWindow;
        m_pWindow = nullptr;
        pWindow->Release1();
    }
}

// @ 0x00e36540
void cUITimedTooltip::UpdateTimeoutA()
{
    if (m_pLayout == nullptr)
        return;
    if (m_swA.m_nStart == 0)
        return;
    if (m_swA.GetElapsedTime() > (int64_t)m_nTimeoutA) {
        m_pLayout->SetVisibility(true);
        m_swA.m_nStart = 0;
        m_swA.m_nStop = 0;
    }
}

// @ 0x00e365a0
void cUITimedTooltip::UpdateTimeoutB(IWin* pWindow)
{
    if (m_pLayout == nullptr)
        return;

    FUN_00808b20(pWindow, m_pWindow, 0);

    if (m_swB.m_nStart != 0) {
        if (m_swB.GetElapsedTime() > (int64_t)m_nTimeoutB) {
            m_pLayout->SetVisibility(true);
            m_swB.m_nStart = 0;
            m_swB.m_nStop = 0;
            return;
        }
    }
    m_swA.Restart();
}

// @ 0x00e36620
void cUITimedTooltip::Hide()
{
    if (m_pLayout == nullptr)
        return;
    if (!m_pLayout->IsVisible())
        return;
    m_pLayout->SetVisibility(false);
    m_swB.Restart();
}

// @ 0x00e36650
void* cUITimedTooltip::FindWindow(uint32_t nId, bool bFlag)
{
    if (m_pLayout == nullptr)
        return nullptr;
    return m_pLayout->FindWindowByID(nId, bFlag);
}

// @ 0x00e36670
Vector4* __cdecl AccumulateBounds(Vector4* pOut, IWinNode* pNode, bool bDeep,
                                  bool bFilter)
{
    pOut->x = 0.0f;
    pOut->y = 0.0f;
    pOut->z = 0.0f;
    pOut->w = 0.0f;

    uint32_t* pIter;
    uint32_t* pEnd;
    pNode->Scc(&pIter);
    pNode->Sd0(&pEnd);

    while (pIter != pEnd) {
        IWinNode* pChild = (IWinNode*)(gspUIElementBase + *pIter);
        if (!bFilter || (pChild->S28() & 1) != 0) {
            RectF childRect = *pChild->S38();
            RectF grown = childRect;

            if (bDeep) {
                Vector4 inner;
                AccumulateBounds(&inner, pChild, bDeep, bFilter);
                grown.x0 = inner.x + childRect.x0;
                grown.y0 = inner.y + childRect.y0;
                grown.x1 = grown.x0 + (childRect.x1 - childRect.x0);
                grown.y1 = grown.y0 + (childRect.y1 - childRect.y0);

                if (childRect.x0 != childRect.x1
                    && childRect.y0 != childRect.y1) {
                    grown = childRect;
                    if (inner.x != inner.z && inner.y != inner.w) {
                        if (grown.x0 < inner.x)
                            grown.x0 = inner.x;
                        if (grown.y0 < inner.y)
                            grown.y0 = inner.y;
                        if (grown.x1 < inner.z)
                            grown.x1 = inner.z;
                        if (grown.y1 < inner.w)
                            grown.y1 = inner.w;
                    }
                }
            }

            if (pOut->x != pOut->z && pOut->y != pOut->w) {
                if (grown.x0 == grown.x1 || grown.y0 == grown.y1) {
                    grown.x0 = pOut->x;
                    grown.y0 = pOut->y;
                    grown.x1 = pOut->z;
                    grown.y1 = pOut->w;
                } else {
                    if (grown.x0 > pOut->x)
                        grown.x0 = pOut->x;
                    if (grown.y0 > pOut->y)
                        grown.y0 = pOut->y;
                    if (grown.x1 < pOut->z)
                        grown.x1 = pOut->z;
                    if (grown.y1 < pOut->w)
                        grown.y1 = pOut->w;
                }
            }

            pOut->x = grown.x0;
            pOut->y = grown.y0;
            pOut->z = grown.x1;
            pOut->w = grown.y1;
        }
        pIter = (uint32_t*)*pIter;
    }
    return pOut;
}

// @ 0x00e368e0
void __cdecl ReloadTooltip(void* pUser, cSPUILayout* pLayout, bool bDisplay)
{
    if (!bDisplay)
        return;

    cUITimedTooltip* pTooltip = (cUITimedTooltip*)pUser;
    IWin* pFound = nullptr;
    if (pTooltip->m_pLayout != nullptr)
        pFound = (IWin*)pTooltip->m_pLayout->FindWindowByID(pTooltip->m_nKey08,
                                                            true);

    if (pFound != pTooltip->m_pWindow) {
        if (pFound != nullptr)
            pFound->AddRef0();
        IWin* pOld = pTooltip->m_pWindow;
        pTooltip->m_pWindow = pFound;
        if (pOld != nullptr)
            pOld->Release1();
    }

    if (pTooltip->m_pWindow == nullptr) {
        if (pTooltip->m_pLayout != nullptr) {
            cSPUILayout* pOldLayout = pTooltip->m_pLayout;
            pTooltip->m_pLayout = nullptr;
            pOldLayout->Release2();
        }
        return;
    }

    pTooltip->m_pLayout->SetVisibility(false);
    pTooltip->m_pWindow->SetFlags7c(true, false);
    pTooltip->m_pLayout->SetParentWin(nullptr, true, 0x5b598f6);

    Vector4 bounds;
    AccumulateBounds(&bounds, (IWinNode*)pTooltip->m_pWindow, true, true);

    RectF* pRect = ((IWinNode*)pTooltip->m_pWindow)->S38();
    pTooltip->m_f50 = bounds.x;
    pTooltip->m_f54 = bounds.y;
    pTooltip->m_f58 = (pRect->x1 - pRect->x0) - bounds.z;
    pTooltip->m_f5c = (pRect->y1 - pRect->y0) - bounds.w;
}

// @ 0x00e369f0
void cUITimedTooltip::UpdateLayout()
{
    if (m_pLayout == nullptr)
        return;

    Vector4 bounds;
    AccumulateBounds(&bounds, (IWinNode*)m_pWindow, true, true);

    float fDX = m_f50 - bounds.x;
    float fDY = m_f54 - bounds.y;
    if (fDX != 0.0f || fDY != 0.0f) {
        uint32_t* pIter;
        uint32_t* pEnd;
        ((IWinNode*)m_pWindow)->Scc(&pIter);
        ((IWinNode*)m_pWindow)->Sd0(&pEnd);
        while (pIter != pEnd) {
            IWinNode* pNode = (IWinNode*)(gspUIElementBase + *pIter);
            RectF* pRect = pNode->S38();
            pNode->S70(pRect->x0 + fDX, pRect->y0 + fDY);
            pIter = (uint32_t*)*pIter;
        }
    }

    ((IWinNode*)m_pWindow)->S74(m_f58 + ((bounds.z - bounds.x) + m_f50),
                                m_f5c + ((bounds.w - bounds.y) + m_f54));
}

// @ 0x00e36b30
bool cUITimedTooltip::Init(const uint32_t& nKey, uint32_t nId, uint32_t nWidth,
                           uint32_t nHeight, uint32_t a5, uint32_t a6)
{
    m_nTimeoutA = nWidth;
    m_nTimeoutB = nHeight;

    cSPUILayout* pLayout = (cSPUILayout*)operator_new(
        0x18, (const void*)0x13f6b3c, 0, 0, 0, 0);
    if (pLayout != nullptr)
        pLayout = pLayout->InitDocument();

    if (pLayout != m_pLayout) {
        if (pLayout != nullptr)
            pLayout->Release1();
        cSPUILayout* pOld = m_pLayout;
        m_pLayout = pLayout;
        if (pOld != nullptr)
            pOld->Release2();
    }

    if (!m_pLayout->Init(&nKey, false, 0x5b598f6)) {
        if (m_pLayout != nullptr) {
            cSPUILayout* pOld = m_pLayout;
            m_pLayout = nullptr;
            pOld->Release2();
        }
        return m_pLayout != nullptr;
    }

    m_nKey08 = nId;
    m_pLayout->SetReloadCallback(ReloadTooltip, this);
    ReloadTooltip(this, m_pLayout, true);
    return m_pLayout != nullptr;
}

// @ 0x00e36de0
void cUITimedTooltip::ResetState()
{
    m_nMode3f0 = 9;
    m_bFlag454 = false;
}

// @ 0x00e36cd0
bool cUITimedTooltip::UpdateA()
{
    EA::Stopwatch& sw = m_sw418;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold430) {
        if (m_pAnimator458->Empty()) {
            sw.SetBoolProperty();
            return true;
        }
    }
    return false;
}

// @ 0x00e36d30
bool cUITimedTooltip::UpdateB()
{
    EA::Stopwatch& sw = m_sw3f8;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold410) {
        sw.SetBoolProperty();
        return true;
    }
    return false;
}

// @ 0x00e36d80
bool cUITimedTooltip::UpdateC()
{
    EA::Stopwatch& sw = m_sw438;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold450) {
        sw.SetBoolProperty();
        return true;
    }
    return false;
}

// @ 0x00e36e20
bool cUITimedTooltip::UpdateD()
{
    EA::Stopwatch& sw = m_sw4c8;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold4e0) {
        if (m_pAnimator458->Empty()) {
            sw.SetBoolProperty();
            return true;
        }
    }
    return false;
}

// @ 0x00e36e80
bool cUITimedTooltip::UpdateE()
{
    EA::Stopwatch& sw = m_sw4a8;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold4c0) {
        sw.SetBoolProperty();
        return true;
    }
    return false;
}

// @ 0x00e36fb0
cTooltipSlot* cUITimedTooltip::GetSlot(int32_t nIndex)
{
    return &m_slots[nIndex];
}

// ---------------------------------------------------------------------------
// game-mode ids
// ---------------------------------------------------------------------------

// @ 0x00e36c80
uint32_t __cdecl GetGameModeHash()
{
    switch (SP_GetCurrentGameMode()) {
    case 0x1654c00:
        return 0xa426730b;
    case 0x1654c01:
        return 0xad56080c;
    case 0x1654c02:
        return 0xf71fa311;
    case 0x1654c04:
        return 0xbeb528cb;
    case 0x1654c05:
        return 0x2db6dad3;
    default:
        return 0;
    }
}

// @ 0x00e36ed0
int32_t __cdecl GetGameLevel(int32_t nGameMode)
{
    int32_t nMode = nGameMode;
    if (nGameMode == -1)
        nMode = (int32_t)SP_GetCurrentGameMode();
    switch (nMode) {
    case 0x1654c00:
        return 0;
    case 0x1654c01:
        return 1;
    case 0x1654c02:
        return 2;
    case 0x1654c04:
        return 3;
    case 0x1654c05:
        return 4;
    case 0x1654c10:
        return 5;
    default:
        return nGameMode;
    }
}

// @ 0x00e36f50
uint32_t __cdecl GetGameModeIndex(uint32_t nHash)
{
    switch (nHash) {
    case 0xa426730b:
        return 0;
    case 0xad56080c:
        return 1;
    case 0xf71fa311:
        return 2;
    case 0xbeb528cb:
        return 3;
    case 0x2db6dad3:
        return 4;
    default:
        return 0;
    }
}

// @ 0x00e36fd0
void __cdecl SetEditorState()
{
    cEditor* pEditor = (cEditor*)FUN_00b3d410();
    if (pEditor->m_nState == 1)
        pEditor->m_nState = 2;
}
