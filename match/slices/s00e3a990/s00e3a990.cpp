// Slice s00e3a990: SP::cSPUITimeline playback / state machine.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define VSLOT(n) virtual void _v##n();

namespace EA {
#pragma pack(push, 4)
class Stopwatch {
public:
    uint8_t mnPad00[0x18];              // +0x00
    void Restart();                     // 0x00571e80
    float GetElapsedTimeFloat() const;  // 0x005ff1a0
};
#pragma pack(pop)
} // namespace EA

// ---------------------------------------------------------------------------
// external UI helpers
// ---------------------------------------------------------------------------
class cUIWindow {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void SetVisible(int32_t nState, int32_t nFlags); // +0x7c
};

class cSPUILayout {
public:
    cUIWindow* FindWindowByID(uint32_t nId, int32_t nParam); // 0x008105b0
};

class cSPUIAnimator {
public:
    void ClearAll();                    // 0x007f8f00
};

class cTimelinePlayItem {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void SetVisible(int32_t nState, int32_t nFlags); // +0x7c
};

class cTimelineTrack;

void PlayTimelineClip(void* pClip);     // 0x00e38ce0
bool IsTimelineWindowReady();           // 0x00e36e80
bool IsTimelinePlaybackDone();          // 0x00e36e20
bool IsWorldLayoutFlagSet(int32_t nFlag); // 0x00685520

// ---------------------------------------------------------------------------
// SP::cSPUITimeline (shipping layout reaches 0x52c)
// ---------------------------------------------------------------------------
class cSPUITimeline {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    uint8_t mnPad04[0x30];              // +0x004
    void* mpSourceLayout;               // +0x034
    uint8_t mnPad38[4];                 // +0x038
    void* mpSelectedTrack;              // +0x03c
    uint8_t mnPad40[0xa8];              // +0x040
    void* mpTracksSentinel;             // +0x0e8
    cTimelineTrack* mpTracksRoot;       // +0x0ec
    uint8_t mnPadF0[0x1a8];             // +0x0f0
    uint32_t mnCachedPaletteId;         // +0x298
    uint8_t mnPad29c[0xac];             // +0x29c
    cSPUILayout* mpLeftLayout;          // +0x348
    cSPUILayout* mpRightLayout;         // +0x34c
    uint8_t mnPad350[0x24];             // +0x350
    cTimelinePlayItem* mPlayItems[31];  // +0x374
    uint32_t mnMode;                    // +0x3f0
    uint8_t mnPad3f4[0x64];             // +0x3f4
    cSPUIAnimator* mpAnimator;          // +0x458
    void* mpClip;                       // +0x45c
    uint8_t mnPad460[0x28];             // +0x460
    uint32_t mnPlayItemCount;           // +0x488
    uint8_t mnPad48c[4];                // +0x48c
    uint32_t mnPlayIndex;               // +0x490
    uint8_t mnPad494[0x0c];             // +0x494
    uint32_t mnState;                   // +0x4a0
    uint8_t mnPad4a4[0x24];             // +0x4a4
    EA::Stopwatch mStopwatch;           // +0x4c8
    float mFadeDelay;                   // +0x4e0
    float mFadeTime;                    // +0x4e4
    bool mbFadeActive;                  // +0x4e8
    uint8_t mnPad4e9[7];                // +0x4e9
    uint32_t mnTimerStartLow;           // +0x4f0
    uint32_t mnTimerStartHigh;          // +0x4f4
    uint32_t mnTimerEndLow;             // +0x4f8
    uint32_t mnTimerEndHigh;            // +0x4fc
    uint32_t mnTimerMode;               // +0x500
    uint8_t mnPad504[4];                // +0x504
    bool mbTimerReset;                  // +0x508
    uint8_t mnPad509[7];                // +0x509
    uint32_t mnExtraStartLow;           // +0x510
    uint32_t mnExtraStartHigh;          // +0x514
    uint32_t mnExtraEndLow;             // +0x518
    uint32_t mnExtraEndHigh;            // +0x51c
    uint32_t mnExtraMode;               // +0x520
    uint8_t mnPad524[4];                // +0x524
    bool mbExtraReset;                  // +0x528

    // out-of-slice members
    void UpdateTransition(float fTime);                 // 0x00e3abf0
    void UpdatePlayback();                              // 0x00e389e0
    void ResetClip();                                   // 0x00e38450
    void FinishTransition();                            // 0x00e38fd0
    void SetRunning(int32_t nRunning);                  // 0x00e39300
    void InitGonzagoSubsystem(int32_t nFlag);           // 0x00e39350
    void PlayClip(void* pClip);                         // 0x00e38ce0

    cTimelineTrack* FindNextTrack(uint32_t nFlags, float* pProgress);
    cTimelineTrack* FindPreviousTrack(uint32_t nFlags, float* pProgress);
    bool ShowNextPlayItem();
    void StartPlayback();
    void RestorePlayback();
    void HidePanels();
    void ShowPanels();
    bool LoadImage(cUIWindow* pWindow, void* pResource);
    bool HandleMessage(void* pMessage);
    uint32_t GetSelectedPaletteId();
    void UpdateState();
};

class cTimelineTrack {
public:
    bool IsEnabled();                   // vtable +0x28
    float* GetRange();                  // vtable +0x38
    float* GetTime(void* pOut, void* pParam, int32_t nExtra); // vtable +0xc4
};

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::FindNextTrack
// @ 0x00e3a990
// ---------------------------------------------------------------------------
cTimelineTrack* cSPUITimeline::FindNextTrack(uint32_t nFlags, float* pProgress)
{
    (void)nFlags;
    (void)pProgress;
    return 0;
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::FindPreviousTrack
// @ 0x00e3aac0
// ---------------------------------------------------------------------------
cTimelineTrack* cSPUITimeline::FindPreviousTrack(uint32_t nFlags,
                                                float* pProgress)
{
    (void)nFlags;
    (void)pProgress;
    return 0;
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::UpdateTransition
// @ 0x00e3abf0
// ---------------------------------------------------------------------------
void cSPUITimeline::UpdateTransition(float fTime)
{
    (void)fTime;
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::UpdateState
// @ 0x00e3afb0
// ---------------------------------------------------------------------------
void cSPUITimeline::UpdateState()
{
    switch (mnState) {
    case 1:
        PlayClip(mpClip);
        mnState = 3;
        break;
    case 2:
        if (IsTimelineWindowReady()) {
            PlayClip(mpClip);
            mnState = 3;
        }
        break;
    case 3:
        if (IsTimelineWindowReady()) {
            mStopwatch.Restart();
            mnState = 4;
        }
        break;
    case 4:
        if (IsTimelinePlaybackDone()) {
            FinishTransition();
            mnState = 2;
        } else if (mbFadeActive) {
            if (mFadeDelay - mStopwatch.GetElapsedTimeFloat() <= mFadeTime) {
                cUIWindow* pWindow =
                    mpLeftLayout->FindWindowByID(0x6456c48, 1);
                pWindow->SetVisible(2, 0);
                mbFadeActive = false;
            }
        }
        break;
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::ShowNextPlayItem
// @ 0x00e3b0b0
// ---------------------------------------------------------------------------
bool cSPUITimeline::ShowNextPlayItem()
{
    bool bResult = false;

    if (mnPlayIndex < mnPlayItemCount) {
        mPlayItems[mnPlayIndex]->SetVisible(1, 1);
        UpdatePlayback();
        ++mnPlayIndex;
        bResult = true;
    }
    return bResult;
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::StartPlayback
// @ 0x00e3b0f0
// ---------------------------------------------------------------------------
void cSPUITimeline::StartPlayback()
{
    mnPlayIndex = 0;
    ResetClip();
    SetRunning(1);
    InitGonzagoSubsystem(1);
    if (mpClip != (void*)0x1654c10)
        mnMode = 1;
    mbTimerReset = false;
    if (mnTimerMode == 1) {
        mnTimerStartLow = 0;
        mnTimerStartHigh = 0;
    } else {
        mnTimerStartLow = 0;
        mnTimerStartHigh = 0;
    }
    mnTimerEndLow = 0;
    mnTimerEndHigh = 0;
    mnState = 1;
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::RestorePlayback
// @ 0x00e3b180
// ---------------------------------------------------------------------------
void cSPUITimeline::RestorePlayback()
{
    SetRunning(0);
    cUIWindow* pWindow = mpLeftLayout->FindWindowByID(0x64d29c0, 1);
    if (pWindow != 0)
        pWindow->SetVisible(1, 0);
    if (IsWorldLayoutFlagSet(2)) {
        pWindow = mpRightLayout->FindWindowByID(0x64d29c0, 1);
        if (pWindow != 0)
            pWindow->SetVisible(1, 0);
    }
    mpAnimator->ClearAll();
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::HidePanels
// @ 0x00e3b1f0
// ---------------------------------------------------------------------------
void cSPUITimeline::HidePanels()
{
    SetRunning(0);
    mpAnimator->ClearAll();
    mnMode = 12;
    cUIWindow* pWindow = mpLeftLayout->FindWindowByID(0x64d29c0, 1);
    pWindow->SetVisible(1, 1);
    InitGonzagoSubsystem(0);
    mbExtraReset = false;
    if (mnExtraMode == 1) {
        mnExtraStartLow = 0;
        mnExtraStartHigh = 0;
        mnExtraEndLow = 0;
        mnExtraEndHigh = 0;
    } else {
        mnExtraStartLow = 0;
        mnExtraStartHigh = 0;
        mnExtraEndLow = 0;
        mnExtraEndHigh = 0;
    }
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::LoadImage
// @ 0x00e3b2a0
// ---------------------------------------------------------------------------
bool cSPUITimeline::LoadImage(cUIWindow* pWindow, void* pResource)
{
    (void)pWindow;
    (void)pResource;
    return false;
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::HandleMessage
// @ 0x00e3b390
// ---------------------------------------------------------------------------
bool cSPUITimeline::HandleMessage(void* pMessage)
{
    (void)pMessage;
    return false;
}

// ---------------------------------------------------------------------------
// SP::cSPUITimeline::GetSelectedPaletteId
// @ 0x00e3b5d0
// ---------------------------------------------------------------------------
uint32_t cSPUITimeline::GetSelectedPaletteId()
{
    return mnCachedPaletteId;
}

// ---------------------------------------------------------------------------
// IsPaletteIdPresent
// @ 0x00e3b630
// ---------------------------------------------------------------------------
bool IsPaletteIdPresent(uint32_t nId)
{
    (void)nId;
    return false;
}

// ---------------------------------------------------------------------------
// rbtree insertion helper, 8-byte value
// @ 0x00e3b670
// ---------------------------------------------------------------------------
void InsertTrackRef(void* pResult, void* pParent, const void* pValue,
                    bool bLeft)
{
    (void)pResult;
    (void)pParent;
    (void)pValue;
    (void)bLeft;
}

// ---------------------------------------------------------------------------
// rbtree insertion helper, 12-byte value
// @ 0x00e3b700
// ---------------------------------------------------------------------------
void InsertTrackPoint(void* pResult, void* pParent, const void* pValue,
                      bool bLeft)
{
    (void)pResult;
    (void)pParent;
    (void)pValue;
    (void)bLeft;
}

// ---------------------------------------------------------------------------
// rbtree insertion helper, 20-byte value
// @ 0x00e3b790
// ---------------------------------------------------------------------------
void InsertTrackRect(void* pResult, void* pParent, const void* pValue,
                     bool bLeft)
{
    (void)pResult;
    (void)pParent;
    (void)pValue;
    (void)bLeft;
}
