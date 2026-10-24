// Slice s0107a510 -- UI tool widget value/state setters.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

extern "C" void __cdecl FUN_0107a5b0_SideEffect();       // external state change

namespace SP {

// Widget that shows a tool value and tracks its own visible state.
class cToolWidget {
public:
    void FUN_0107a510();
    __declspec(noinline) void FUN_0107a5b0();
    void FUN_0107a6b0();
    void FUN_0107a9a0();
    void FUN_0107a300();                                 // 0x0107a300
    void FUN_0107ab20(int32_t value);
    void FUN_0107abb0();

    uint8_t  pad000[0x90];                               // +0x000 .. +0x08f
    int32_t  mField90;                                   // +0x090
    uint8_t  pad094[0xe8 - 0x94];                        // +0x094 .. +0x0e7
    bool     mFlagE8;                                    // +0x0e8
};

class cSPUITools {
public:
    void GetToolAvailability();
};

} // namespace SP

namespace UTFWin {

class InteractiveWinProc {
public:
    virtual void v000();                                 // +0x00
    void OnWinProcAdd(void* pWin);                       // 0x010829f0
};

} // namespace UTFWin

// Feed list attached to the tool window (ref-counted, released through slot 1).
class FeedList {
public:
    virtual void v000();                                 // +0x00
    virtual void Release();                              // +0x04
    void FUN_006628d0();                                 // 0x006628d0
    void FUN_00663350(void* pWin);                       // 0x00663350
};

// Sub-object at +0x44 of the tool window.
class cToolSub {
public:
    void FUN_00e0a5c0();                                 // 0x00e0a5c0

    uint8_t mPayload[0x74];                              // +0x00 .. +0x73
};

// Timed tooltip attached to the tool window at +0xb8.
class cUITimedTooltip {
public:
    void UpdateTimeoutA();                               // 0x00e36540
    void Shutdown();                                     // 0x00e36500

    uint8_t mPayload[0x8c];                              // +0x00 .. +0x8b
};

class cToolWindow : public UTFWin::InteractiveWinProc {
public:
    void FUN_0107adf0();
    void FUN_0107ae40(void* pWin);
    void ShutdownCard();                                 // 0x00e18810

    uint8_t          pad004[0x3c];                       // +0x004 .. +0x03f
    bool             mFlag40;                            // +0x040
    uint8_t          pad041[3];                          // +0x041 .. +0x043
    cToolSub         mSub44;                             // +0x044 .. +0x0b7
    cUITimedTooltip  mTooltip;                           // +0x0b8 .. +0x143
    FeedList*        mpFeedList;                         // +0x144
};

using namespace SP;

// @ 0x107a510 SP::cToolWidget::FUN_0107a510
void __thiscall cToolWidget::FUN_0107a510()
{
}

// @ 0x107a5b0 SP::cToolWidget::FUN_0107a5b0
__declspec(noinline) void __thiscall cToolWidget::FUN_0107a5b0()
{
    FUN_0107a5b0_SideEffect();                           // clobbers ecx like the original
}

// @ 0x107a6b0 SP::cToolWidget::FUN_0107a6b0
void __thiscall cToolWidget::FUN_0107a6b0()
{
}

// @ 0x107a9a0 SP::cToolWidget::FUN_0107a9a0
void __thiscall cToolWidget::FUN_0107a9a0()
{
}

// @ 0x107ab20 SP::cToolWidget::FUN_0107ab20
void __thiscall cToolWidget::FUN_0107ab20(int32_t value)
{
    bool wasActive = mFlagE8;
    mField90 = value;
    if (wasActive)
        FUN_0107a300();
}

// @ 0x107ab40 FUN_0107ab40
void __cdecl FUN_0107ab40()
{
}

// @ 0x107abb0 SP::cToolWidget::FUN_0107abb0
void __thiscall cToolWidget::FUN_0107abb0()
{
    if (!mFlagE8) {
        FUN_0107a5b0();
        mFlagE8 = true;
    }
}

// @ 0x107ac20 FUN_0107ac20
void __cdecl FUN_0107ac20()
{
}

// @ 0x107ac90 FUN_0107ac90
void __cdecl FUN_0107ac90()
{
}

// @ 0x107adf0 FUN_0107adf0
void __thiscall cToolWindow::FUN_0107adf0()
{
    if (mpFeedList) {
        mpFeedList->FUN_006628d0();
        FeedList* pOld = mpFeedList;
        if (pOld) {
            mpFeedList = 0;
            pOld->Release();
        }
    }
    mSub44.FUN_00e0a5c0();
    mTooltip.Shutdown();
    ShutdownCard();
}

// @ 0x107ae40 FUN_0107ae40
void __thiscall cToolWindow::FUN_0107ae40(void* pWin)
{
    OnWinProcAdd(pWin);
    if (mFlag40) {
        mTooltip.UpdateTimeoutA();
        mpFeedList->FUN_00663350(pWin);
    }
}

// @ 0x107ae70 FUN_0107ae70
void __cdecl FUN_0107ae70()
{
}

// @ 0x107af00 FUN_0107af00
void __cdecl FUN_0107af00()
{
}

// @ 0x107afa0 FUN_0107afa0
void __cdecl FUN_0107afa0()
{
}

// @ 0x107b120 SP::cSPUITools::GetToolAvailability
void __thiscall cSPUITools::GetToolAvailability()
{
}
