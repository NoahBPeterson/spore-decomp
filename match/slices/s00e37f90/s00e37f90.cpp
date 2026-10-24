// s00e37f90 -- the Sporepedia asset timeline: the track-clipping helper, the
// key-frame lookup, the card construction, the layout pass and the two step
// functions that walk the track list.
//
//   0x00e37f90 key pair lookup        0x00e38240 sporepedia card build
//   0x00e38020 track clipping         0x00e38450 timeline layout
//   0x00e389e0 icon animation         0x00e38bb0 step back
//                                     0x00e38c90 step forward
#include "types.h"

#define nullptr 0

// ---------------------------------------------------------------------------
// engine types
// ---------------------------------------------------------------------------

struct Vector2 {
    float x;
    float y;
};

struct RectF {
    float x0;
    float y0;
    float x1;
    float y1;
};

struct Vec4 {
    float x;
    float y;
    float z;
    float w;
};

// the resource-manager key triple
struct Key {
    uint32_t m_nGroup;
    uint32_t m_nType;
    uint32_t m_nInstance;
};

// EA's high-resolution stopwatch: two 64-bit counter snapshots, the counter
// source id and the multiplier that turns ticks into the caller's unit.
namespace EA {
class Stopwatch {
public:
    Stopwatch() {}
    Stopwatch(int32_t nSource, bool bStart);     // 0x0093a560
    void Restart();                              // 0x00571e80

    int64_t m_nStart;                            // +0x00
    int64_t m_nStop;                             // +0x08
    int32_t m_nSource;                           // +0x10
    float m_fRate;                               // +0x14
};
}

// a UTFWin control; the slots this slice reaches are named after their offset
class IWindow {
public:
    virtual void T00();  virtual void T04();  virtual void T08();  virtual void T0c();
    virtual void T10();  virtual void T14();  virtual void T18();
    virtual void SetContent1c(void* pItem, void* pData, uint32_t a, uint32_t b);  // +0x1c
    virtual void Reset20();                      // +0x20
    virtual void T24();
    virtual void SetFlag28(bool bFlag);          // +0x28
    virtual void T2c();
    virtual void SetFlag30(bool a, bool b);      // +0x30
    virtual RectF* GetRect34();                  // +0x34
    virtual RectF* GetRect38();                  // +0x38
    virtual void T3c();  virtual void T40();  virtual void T44();  virtual void T48();
    virtual void T4c();  virtual void T50();  virtual void T54();  virtual void T58();
    virtual void T5c();
    virtual void SetRect60(const RectF* pRect);  // +0x60
    virtual void SetPos64(float fX, float fY);   // +0x64
    virtual void SetSize68(float fWidth, float fHeight);          // +0x68
    virtual void T6c();  virtual void T70();  virtual void T74();  virtual void T78();
    virtual void SetFlags7c(bool a, bool b);     // +0x7c
};

// the UI layout document
class cSPUILayout {
public:
    virtual void L00();  virtual void L04();  virtual void L08();
    void* FindWindowByID(uint32_t nId, bool bFlag);            // 0x008105b0
};

// the raw key-frame animation record the UI factories fill in
struct AnimRaw {
    float m_fa;
    float m_fb;
    float m_fc;
    float m_fd;
    float m_fe;
};

// the UI animator that plays the icon animations
class cSPUIAnimator {
public:
    void AddAnimation(void* pAnim, void* pRef, int32_t nFlag);   // 0x007f8d10
};

// the auto-refcount holder used for the sporepedia card objects
class cAutoRef {
public:
    void* m_pObject;                             // +0x00
};

// a timeline track node
class cTrackNode {
public:
    Vector2* LookupKey(Vector2* pKey);           // 0x00e470a0

    uint8_t mPad000[0xf0];                       // +0x000
    uint32_t m_nKeyCount;                        // +0x0f0
};

// the sporepedia card data / view created on demand
class cSporepediaCardData {
public:
    virtual void D00();                          // +0x00
    virtual void Get(void* pOut);                // +0x04
    virtual void Release();                      // +0x08
    void* Construct();                           // 0x00642100
};

class cSporepediaCardView {
public:
    void* Construct();                           // 0x00657f70
};

// ---------------------------------------------------------------------------
// imports
// ---------------------------------------------------------------------------

void* __cdecl cSPBoundingBox_Unused();           // placeholder, never called
float __cdecl SPUIHelpers_GetElapsedSeconds(float fTime, int32_t nMode,
                                            IWindow* pWindow, int32_t nFlag);
void* __stdcall SPUICreateWindowAnimationTargetPosition(
    Vector2* pOut, IWindow* pWindow, const Vector2* pOffset, float fTime,
    float fDelay);                               // 0x007f80d0
AnimRaw* __stdcall SPUICreateWindowAnimationRotation(
    AnimRaw* pOut, IWindow* pWindow, float fA, float fB, float fC, float fD,
    float fE);                                   // 0x007f8140
Vec4* __cdecl SPUIHelpers_GetMainWindowArea(Vec4* pOut);               // 0x00805ea0
void __stdcall SetWindowImage(void* pImage, const Key* pKey,
                              int32_t nFlag);   // 0x00807bb0
bool __cdecl IsWorldLayoutFlagSet(int32_t nFlag);                      // 0x00685520
void* __cdecl FUN_00401010();                    // 0x00401010
void* __cdecl FUN_00401090();                    // 0x00401090
void* __cdecl FUN_004df400();                    // 0x004df400
bool __cdecl ResourceKeyNotEqual(const Key* pKey, const Key* pOther);  // 0x005f78f0
void __stdcall FUN_006428c0(void* pData);        // 0x006428c0
void __stdcall AssignCardView(cAutoRef* pRef, void* pView);            // 0x00b5f950

// the app-wide property list the sporepedia gate queries
class cPropertyList {
public:
    bool GetDescription(uint32_t nKey);          // 0x006a25a0
};

void* __stdcall operator_new(uint32_t nSize, const char* pType,
                             uint32_t a, uint32_t b, uint32_t c,
                             uint32_t d);        // 0x00f473a0

extern cPropertyList* gspAppProperties;          // 0x015fd918
extern Key gKeyCardData;                         // 0x016acc4c
extern bool gbCardInitialised;                   // 0x016acc58
extern bool gbBackgroundLayoutSeeded;            // 0x016acc5c
extern const float gkfIdleDelay;                 // 0x015a5890

// ---------------------------------------------------------------------------
// the timeline that walks one track per asset
// ---------------------------------------------------------------------------

class Timeline {
public:
    Vector2 GetKeyPair(uint32_t nX, int32_t nOffset);           // 0x00e37f90
    bool ClipTracks(Vector2* pFirst, Vector2* pSecond, Vector2* pThird,
                    Vector2* pFourth, bool bFlip);              // 0x00e38020
    bool StepBack();                                            // 0x00e38bb0
    bool Step();                                                // 0x00e38c90
    void PlayIconAnimation();                                   // 0x00e389e0

    cTrackNode* FindNode(uint32_t nX, int32_t nOffset);         // 0x00e37e50

    uint8_t mPad000[0x3c];                       // +0x000
    IWindow* m_pHolder;                          // +0x03c
    uint8_t mPad040[0x144];                      // +0x040
    cTrackNode** m_apNodes;                      // +0x184
    uint8_t mPad188[0x1c0];                      // +0x188
    cSPUILayout* m_pLayout;                      // +0x348
    uint8_t mPad34c[0x28];                       // +0x34c
    IWindow* m_apTracks[39];                     // +0x374
    float m_fDelay410;                           // +0x410
    uint8_t mPad414[0x24];                       // +0x414
    EA::Stopwatch m_sw438;                       // +0x438
    float m_f450;                                // +0x450
    uint8_t mPad454[0x4];                        // +0x454
    cSPUIAnimator* m_pAnimator;                  // +0x458
    uint8_t mPad45c[0x2c];                       // +0x45c
    uint32_t m_nTrackCount;                      // +0x488
    uint8_t mPad48c[0x4];                        // +0x48c
    uint32_t m_nIndex;                           // +0x490
    uint8_t mPad494[0x8];                        // +0x494
    bool m_bLast;                                // +0x49c
};

// @ 0x00e37f90
Vector2 Timeline::GetKeyPair(uint32_t nX, int32_t nOffset)
{
    Vector2 result;
    result.x = 0.0f;
    result.y = 0.0f;

    cTrackNode* pNode = FindNode(nX, nOffset);
    if (pNode != nullptr) {
        Vector2 key;
        if (pNode->m_nKeyCount != 0) {
            Vector2* pKey = pNode->LookupKey(&key);
            result.x = pKey->x;
            result.y = FindNode(nX, nOffset - 1)->LookupKey(&key)->y;
            return result;
        }
        result = *pNode->LookupKey(&key);
    }
    return result;
}

// @ 0x00e38020
bool Timeline::ClipTracks(Vector2* pFirst, Vector2* pSecond, Vector2* pThird,
                          Vector2* pFourth, bool bFlip)
{
    if (m_pHolder == nullptr)
        return false;

    RectF* pHolderRect = m_pHolder->GetRect38();
    float fHeight = pHolderRect->y1 - pHolderRect->y0;

    Vector2 origin;
    origin.x = 0.0f;
    origin.y = 0.0f;
    m_pHolder->SetPos64(origin.x, origin.y);
    const float* pBounds = (const float*)m_pHolder->GetRect34();
    float fTop = pBounds[1];

    Vector2 offset;
    offset.x = 0.0f;
    offset.y = fHeight;
    m_pHolder->SetPos64(offset.x, offset.y);
    const float* pInner = (const float*)m_pHolder->GetRect34();
    float fBottom = pInner[1];

    float fLow = (fBottom - fTop) * 0.375f + fTop;
    float fHigh = (fBottom - fTop) * 0.625f + fTop;
    bool bResult = false;

    if (fLow <= pThird->y && pFourth->y < fHigh) {
        float fMid = (pFourth->x - pThird->x) * 0.5f + pThird->x;
        pFourth->y = fTop;
        pFourth->x = (pFourth->x - pThird->x) * 0.5f + pThird->x;
        (void)fMid;
        bResult = true;
    } else if (fHigh < pThird->y && pThird->y <= fLow) {
        pThird->y = fBottom;
        pThird->x = (pThird->x - pThird->x) * 0.5f + pThird->x;
        *pFirst = *pThird;
        bResult = true;
    }

    if (fLow <= pSecond->y && pFourth->y < fHigh) {
        pFourth->x = (pSecond->x - pFourth->x) * 0.5f + pFourth->x;
        pFourth->y = fTop;
        pFourth->x = (pFourth->x - pThird->x) * 0.5f + pThird->x;
    } else if (fHigh < pSecond->y && pSecond->y <= fLow) {
        pFirst->x = (pSecond->x - pFirst->x) * 0.5f + pFirst->x;
        pFirst->y = fBottom;
        (void)bFlip;
    }
    return bResult;
}

// @ 0x00e38c90
bool Timeline::Step()
{
    uint32_t nIndex = m_nIndex;
    bool bResult = false;
    if (nIndex < m_nTrackCount) {
        m_fDelay410 = 0.2f;
        m_apTracks[nIndex]->SetFlags7c(true, true);
        PlayIconAnimation();
        m_nIndex++;
        bResult = true;
    }
    return bResult;
}

// @ 0x00e38bb0
bool Timeline::StepBack()
{
    uint32_t nIndex = m_nIndex - 1;
    bool bResult = false;
    if (nIndex < m_nTrackCount) {
        if (nIndex == m_nTrackCount - 1)
            m_bLast = true;
        IWindow* pTrack = m_apTracks[nIndex];
        if (m_pAnimator != nullptr && pTrack != nullptr) {
            float fTime = SPUIHelpers_GetElapsedSeconds(m_f450, 0, pTrack, 1);
            AnimRaw anim;
            void* pAnim = SPUICreateWindowAnimationRotation(
                &anim, pTrack, 0.0f, 1.0f, 0.0f, gkfIdleDelay, fTime);
            m_pAnimator->AddAnimation(pAnim, nullptr, 1);
            m_sw438.Restart();
        }
        bResult = true;
    }
    return bResult;
}

// ---------------------------------------------------------------------------
// the timeline that owns the per-track sporepedia card views
// ---------------------------------------------------------------------------

class TimelineCards {
public:
    void UpdateCard();                           // 0x00e38240
    void Layout();                               // 0x00e38450
    void AnimateIcon();                          // 0x00e389e0

    cSPUILayout* m_pLayout;                      // +0x348
    cSPUILayout* m_pOverlayLayout;               // +0x34c
    IWindow* m_apTracks[10];                     // +0x374
    void* m_apImages[10];                        // +0x39c
    cAutoRef m_cardData;                         // +0x3c4
    cAutoRef m_apCardViews[10];                  // +0x3c8
    EA::Stopwatch m_sw3f8;                       // +0x3f8
    float m_fDelay410;                           // +0x410
    EA::Stopwatch m_sw418;                       // +0x418
    EA::Stopwatch m_sw438;                       // +0x438
    float m_f450;                                // +0x450
    cSPUIAnimator* m_pAnimator;                  // +0x458
    uint8_t mPad45c[0x2c];                       // +0x45c
    uint32_t m_nTrackCount;                      // +0x488
    uint32_t m_nIndex;                           // +0x490
    float m_fScroll;                             // +0x494
    float m_fCell;                               // +0x498
};

// @ 0x00e38240
void TimelineCards::UpdateCard()
{
    if (gspAppProperties->GetDescription(0x6dd5a65c))
        return;
    if (m_nIndex >= m_nTrackCount)
        return;
    if (m_apTracks[m_nIndex] == nullptr)
        return;

    Key key;
    key.m_nGroup = 0;
    key.m_nType = 0;
    key.m_nInstance = 0;
    if (!FUN_00401010())
        return;

    if (!gbCardInitialised) {
        gbCardInitialised = true;
        gKeyCardData.m_nGroup = 0;
        gKeyCardData.m_nType = 0;
        gKeyCardData.m_nInstance = 0;
    }

    if (!ResourceKeyNotEqual(&key, &gKeyCardData))
        return;
    if (key.m_nType == 0x476a98c7)
        return;

    FUN_00401090();
    Key other = *(const Key*)FUN_004df400();
    if (!ResourceKeyNotEqual(&key, &other))
        return;

    gKeyCardData = key;

    cSporepediaCardData* pData = (cSporepediaCardData*)m_cardData.m_pObject;
    if (pData != nullptr)
        pData->Release();
    if (pData == nullptr) {
        pData = (cSporepediaCardData*)operator_new(
            0x78, "UI/TimelineSporepediaCardData", 0, 0, 0, 0);
        if (pData != nullptr)
            FUN_006428c0(pData->Construct());
    }
    pData = (cSporepediaCardData*)m_cardData.m_pObject;
    uint32_t aInfo[2];
    aInfo[0] = 0;
    aInfo[1] = 0;
    pData->Get(aInfo);

    IWindow* pTrack = m_apTracks[m_nIndex];
    if (m_apCardViews[m_nIndex].m_pObject != nullptr)
        ((IWindow*)m_apCardViews[m_nIndex].m_pObject)->Reset20();
    if (m_apCardViews[m_nIndex].m_pObject == nullptr) {
        cSporepediaCardView* pView = (cSporepediaCardView*)operator_new(
            0x108, "UI/TimelineSporepediaCardView", 0, 0, 0, 0);
        if (pView != nullptr)
            AssignCardView(&m_apCardViews[m_nIndex], pView->Construct());
    }

    IWindow* pView = (IWindow*)m_apCardViews[m_nIndex].m_pObject;
    pView->SetContent1c(pTrack, m_cardData.m_pObject, 0, 0);
    pView->SetFlag30(false, false);
    pView->SetFlag28(true);
}

// @ 0x00e38450
void TimelineCards::Layout()
{
    Vec4 area;
    SPUIHelpers_GetMainWindowArea(&area);
    float fHeight = area.w - area.y;

    Vec4 area2;
    SPUIHelpers_GetMainWindowArea(&area2);
    float fWidth = area2.z - area2.x;

    IWindow* pBar = (IWindow*)m_pLayout->FindWindowByID(0x64d0819, true);
    RectF* pBarRect = pBar->GetRect38();
    float fBarHeight = pBarRect->y1 - pBarRect->y0;

    RectF* pTrackRect = m_apTracks[0]->GetRect34();
    float fAspect = (pTrackRect->x1 - pTrackRect->x0)
                    / (pTrackRect->y1 - pTrackRect->y0);
    float fCell = fAspect * fBarHeight;

    float fStep = fWidth / (float)m_nTrackCount;
    float fGap = fStep - fCell;
    m_fCell = fGap;
    if (0.0f < fGap) {
        m_fCell = (fGap * 0.33333334f) * 2.0f;
    } else {
        fCell = fStep / fAspect;
        fGap = fStep;
    }

    for (uint32_t i = 0; i < m_nTrackCount; ++i)
        m_apTracks[i]->SetSize68(fGap, fCell);

    IWindow* pLine = (IWindow*)m_pLayout->FindWindowByID(0x64d0818, true);
    RectF* pLineRect = pLine->GetRect38();
    float fLineY0 = pLineRect->y0;
    float fLineY1 = pLineRect->y1;

    IWindow* pFrame = (IWindow*)m_pLayout->FindWindowByID(0x6456c48, true);
    RectF* pFrameRect = pFrame->GetRect38();
    RectF frame = *pFrameRect;
    frame.y1 = (fLineY1 - fLineY0) * 0.8f;

    IWindow* pFrame2 = (IWindow*)m_pLayout->FindWindowByID(0x6456c48, true);
    pFrame2->SetRect60(&frame);

    if (!IsWorldLayoutFlagSet(2))
        return;

    IWindow* pBackground = (IWindow*)m_pOverlayLayout->FindWindowByID(0x762350f,
                                                                      true);
    if (pBackground == nullptr || gbBackgroundLayoutSeeded)
        return;
    gbBackgroundLayoutSeeded = true;

    float fScaleX = fHeight * 0.00125f;
    float fScaleY = fStep * 0.0016666667f;

    RectF* pBackRect = pBackground->GetRect34();
    RectF back = *pBackRect;
    back.x1 = (pBackRect->x1 - pBackRect->x0) * fScaleX + pBackRect->x0;
    back.y0 = pBackRect->y0 * fScaleY;
    back.y1 = back.y0 + (pBackRect->y1 - pBackRect->y0);
    pBackground->SetRect60(&back);

    IWindow* pInner = (IWindow*)m_pOverlayLayout->FindWindowByID(0x765e17a, true);
    RectF inner = { 0.0f, 0.0f, 0.0f, 0.0f };
    if (pInner != nullptr) {
        RectF* pInnerRect = pInner->GetRect34();
        inner.x0 = pInnerRect->x0;
        inner.y0 = pInnerRect->y0;
        inner.x1 = (pInnerRect->x1 - pInnerRect->x0) * fScaleX;
        inner.y1 = (pInnerRect->y1 - pInnerRect->y0) * fScaleX;
        pInner->SetRect60(&inner);

        IWindow* pHandle = (IWindow*)m_pOverlayLayout->FindWindowByID(0x76236bd,
                                                                      true);
        if (pHandle != nullptr) {
            RectF* pHandleRect = pHandle->GetRect34();
            RectF handle = *pHandleRect;
            handle.x0 = pHandleRect->x0 * fScaleY;
            handle.y0 = pHandleRect->y0 * fScaleY;
            handle.x1 = (pHandleRect->x1 - pHandleRect->x0) * fScaleY + handle.x0;
            handle.y1 = (pHandleRect->y1 - pHandleRect->y0) * fScaleY + handle.y0;
            pHandle->SetRect60(&handle);
        }
    }

    IWindow* pMarker = (IWindow*)m_pOverlayLayout->FindWindowByID(0x765e179,
                                                                  true);
    if (pMarker != nullptr) {
        RectF* pMarkerRect = pMarker->GetRect34();
        RectF marker = *pMarkerRect;
        marker.y0 = pMarkerRect->y0;
        marker.x1 = marker.x0 + fScaleY;
        marker.y1 = marker.y0 + inner.y1;
        pMarker->SetRect60(&marker);

        IWindow* pTick = (IWindow*)m_pOverlayLayout->FindWindowByID(0x76236be,
                                                                    true);
        if (pTick != nullptr) {
            RectF* pTickRect = pTick->GetRect34();
            RectF tick = *pTickRect;
            tick.x0 = pTickRect->x0 * fScaleY;
            tick.y0 = pTickRect->y0 * fScaleY;
            tick.x1 = (pTickRect->x1 - pTickRect->x0) * fScaleY + tick.x0;
            tick.y1 = (pTickRect->y1 - pTickRect->y0) * fScaleY + tick.y0;
            pTick->SetRect60(&tick);
        }
    }

    IWindow* pEnd = (IWindow*)m_pOverlayLayout->FindWindowByID(0x76236bc, true);
    if (pEnd != nullptr) {
        RectF* pEndRect = pEnd->GetRect34();
        RectF end = *pEndRect;
        end.x0 = pEndRect->x0 * fScaleY;
        end.x1 = (pEndRect->x1 - pEndRect->x0) * fScaleY + end.x0;
        pEnd->SetRect60(&end);
    }
}

// @ 0x00e389e0
void TimelineCards::AnimateIcon()
{
    if (m_pAnimator == nullptr)
        return;
    if (m_apTracks[m_nIndex] == nullptr)
        return;

    Key image;
    image.m_nGroup = 0xfada8c70;
    image.m_nType = 0x2f7d0004;
    image.m_nInstance = 0x02e9a2ca;
    SetWindowImage(m_apImages[m_nIndex], &image, -1);

    Vec4 area;
    SPUIHelpers_GetMainWindowArea(&area);
    float fAreaW = area.z - area.x;
    float fAreaH = area.w - area.y;

    RectF* pRect = m_apTracks[m_nIndex]->GetRect38();
    float fW = pRect->x1 - pRect->x0;
    float fH = pRect->y1 - pRect->y0;
    m_apTracks[m_nIndex]->SetPos64(fAreaW, fAreaH - fH);

    float fDelay = m_fScroll + m_fCell;
    m_fScroll = (fW + m_fScroll) + m_fCell;

    float fTime = SPUIHelpers_GetElapsedSeconds(m_fDelay410, 2,
                                                m_apTracks[m_nIndex], 0);
    Vector2 target;
    target.x = fDelay;
    target.y = fAreaH;
    void* pAnim = SPUICreateWindowAnimationTargetPosition(
        &target, m_apTracks[m_nIndex], &target, fTime, fDelay);
    m_pAnimator->AddAnimation(pAnim, nullptr, 0);
    m_sw3f8.Restart();
    m_sw418.Restart();
}

// ---------------------------------------------------------------------------
// Step() reaches the icon animation through the object's own entry point; the
// card-owning layout shares the object, so the call forwards.
// ---------------------------------------------------------------------------

// forwarder for the step functions; never inlined so Step keeps its call
__declspec(noinline) void Timeline::PlayIconAnimation()
{
    ((TimelineCards*)this)->AnimateIcon();
}
