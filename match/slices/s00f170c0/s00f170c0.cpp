// Slice s00f170c0: UI message handler of the level-progress panel (0x00f170c0, 1952 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as s00f17f70; no /EHsc).
//
// HandleUIMessage(win, msg): Escape key (kMsgKeyDown, vkey 0x1b) starts the closing animation
// through the results recorder or hides a pop-up; a button-click message (0x7e1a521) is
// dispatched on the source window's control id and moves the panel's state machine (mState at
// +0xd4: 0 idle, 1 start, 2/3 count-up, 4..8 level-up pages, 9 pop-up, 10 closing); a custom
// message (0x287259f6) handles the top-level buttons.
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

typedef unsigned int uint;

// ----------------------------------------------------------------------------- UI stubs
struct IWin {
    PV4 PV2 PV                                       // slots 0..6
    virtual uint GetControlID();                     // +0x1c
    PV2                                              // slots 8, 9
    virtual unsigned char IsEnabled();               // +0x28
    PV8 PV8 PV4                                      // slots 11..30
    virtual void SetVisible(int a, bool b);          // +0x7c
    virtual void SetText(const wchar_t* text);       // +0x80
    PV8 PV8 PV8 PV2 PV                               // slots 33..59
    virtual IWin* FindChild(uint id, int recurse);   // +0xf0
    PV4 PV2                                          // slots 61..66
    virtual int GetCommand(int a);                   // +0x10c
};
struct Layout {
    IWin* FindWindowByID(uint id, int recurse);      // 0x008105b0
};

struct IAudioSystem {
    PV8
    virtual int Query();                             // +0x20
};
struct WinMgr {
    PV8 PV8 PV2
    virtual void s18();
    virtual void s19();
    virtual void Dispatch(int a, IWin* w);           // +0x4c
};
WinMgr* WindowManager();                             // 0x0067caa0

struct GlobalState {
    uint pad00[0x7c / 4];
    char* mpSub7c;                                   // +0x7c (int at +0x20)
};
extern GlobalState* g_16c7aa4;                       // 0x016c7aa4

struct cString {
    char data[0x14];
    cString(uint tableId, uint instanceId, uint placeholder);   // 0x006b5770 (ret 0xc)
    ~cString();                                                 // 0x006b5240
    const wchar_t* GetText();                                   // 0x006b55c0
};

// eastl::basic_string<wchar_t, fixed_vector_allocator> with a 32-wchar inline buffer
struct FixedString32 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    wchar_t* mpOverflow;
    wchar_t* mpPool;
    wchar_t  mBuffer[32];
    FixedString32() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 32;
        mpPool = mBuffer;
        mBuffer[0] = 0;
    }
    void DeallocateSelf();                           // 0x0057cb80
    ~FixedString32() { DeallocateSelf(); }
};

void SetVisibleHelper(IWin* w, int visible);         // 0x00e12f80 (cdecl)
void SetTextHelper(IWin* w, const wchar_t* text);    // 0x00e12fc0 (cdecl)
IAudioSystem* GetSystemAT();                         // 0x00a206f0
void KillSetiEffects(uint id, int audio);            // 0x00435ed0 (cdecl)
int GetRecorderState();                              // 0x00435e90 (cdecl)
void SetImageFromLayout(IWin* win, Layout* layout, int id, int a);   // 0x00806a60 (cdecl)
bool FUN_00f0e250(IWin* w);                          // cdecl
int FUN_00eec570();                                  // cdecl
void FUN_00f14120(FixedString32* out, const wchar_t* fmt, int a, int b);   // cdecl
extern const float kZeroA;                           // 0x01485378

struct SubA {
    uint pad00[0x24 / 4];
    void F126d0();                                   // 0x00f126d0 (thiscall)
};
struct SubB {
    void F12970();                                   // 0x00f12970 (thiscall)
};

struct Msg {
    IWin* source;      // +0
    int   field04;
    int   type;        // +8
    int   id;          // +0xc
    int   vkey;        // +0x10
    int   field14;
    int   cmd;         // +0x18
};

class cSPUIProgress {
public:
    uint pad00[0x10 / 4];
    char* mpPlayMode;                                // +0x10 (state at +0x90)
    uint mField14;                                   // +0x14
    Layout* mpLayout;                                // +0x18
    uint pad1c;
    uint pad20;
    SubA* mpSubA;                                    // +0x24
    uint pad28[(0xb4 - 0x28) / 4];
    SubB* mpSubB;                                    // +0xb4
    uint padb8;
    float mTimer;                                    // +0xbc
    float mCur;                                      // +0xc0
    float mStart;                                    // +0xc4
    float mEnd;                                      // +0xc8
    float mNext;                                     // +0xcc
    int   mLevel;                                    // +0xd0
    int   mState;                                    // +0xd4
    uint  mDelay;                                    // +0xd8
    IWin* mpWinA;                                    // +0xdc
    IWin* mpWinB;                                    // +0xe0

    void RecordResults(bool finished);               // 0x00f16580
    bool CheckFlag(int a);                           // 0x00f135b0

    bool HandleUIMessage(void* win, Msg* msg);
};

// @ 0x00f170c0
bool cSPUIProgress::HandleUIMessage(void* win, Msg* msg)
{
    bool result = false;
    switch (msg->type) {
    case 1: {
        if (msg->vkey != 0x1b) return false;
        if (mState != 0) return false;
        if (mpWinB && (mpWinB->IsEnabled() & 1)) {
            SetVisibleHelper(mpWinB, 0);
            mState = 9;
            return true;
        }
        if (!FUN_00f0e250(mpWinA)) return true;
        SetVisibleHelper(mpWinA, 0);
        mField14 = 1;
        mState = 10;
        RecordResults(true);
        return true;
    }
    case 0x7e1a521: {
        if (msg->source->GetCommand(0) != msg->cmd) return false;
        bool a = false;
        if (msg->source) a = msg->source->IsEnabled() & 1;
        bool b = false;
        if (msg->source) b = msg->source->IsEnabled() & 1;
        bool notB = (b == false);
        switch (msg->source->GetControlID()) {
        case 0x7c79820:
        case 0x7c796d0:
        case 0x7c79918: {
            if (mState == 1 && a) {
                SetVisibleHelper(mpWinA->FindChild(0x7c79d78, 1), 1);
                if (*(int*)(mpPlayMode + 0x90) == 5)
                    SetVisibleHelper(mpWinA->FindChild(0x7e09670, 1), 1);
                if (mCur != mEnd) {
                    mState = 2;
                    return true;
                }
            } else {
                if (mState == 10 && notB) {
                    if (mField14 != 1 || !CheckFlag(1)) {
                        mDelay = 3;
                        return true;
                    }
                    mpSubB->F12970();
                    return true;
                }
                if (mState != 9) return true;
                if (!notB) return true;
                IWin** pp = &mpWinA;
                if (msg->source == mpWinA) pp = &mpWinB;
                IWin* w = *pp;
                SetVisibleHelper(w, 1);
                WindowManager()->Dispatch(0, w);
            }
            mState = 0;
            return true;
        }
        case 0x7c79d78:
            if (mState != 2) return true;
            if (!a) return true;
            if (kZeroA < mTimer) {
                mState = 3;
                return true;
            }
            mState = 0;
            return true;
        case 0x774b418:
            if (!notB) return false;
            if (mState == 10) mDelay = 3;
            return false;
        case 0x7db8990:
            if (mState == 6 && a) {
                SetVisibleHelper(mpLayout->FindWindowByID(0x7e09668, 1), 0);
                mState = 7;
                return true;
            }
            if (!notB) return true;
            SetVisibleHelper(mpLayout->FindWindowByID(0x7e09668, 1), 1);
            return true;
        case 0x7e09668: {
            if (mState != 7) return true;
            if (!notB) return true;
            SetVisibleHelper(mpLayout->FindWindowByID(0x7db8990, 1), 0);
            SetVisibleHelper(mpLayout->FindWindowByID(0x7c66c00, 1), 1);
            FixedString32 str;
            FUN_00f14120(&str, L"%d/%d", mLevel, FUN_00eec570());
            SetTextHelper(mpLayout->FindWindowByID(0x7c79af8, 1), str.mpBegin);
            mpSubA->F126d0();
            mState = 8;
            return true;
        }
        case 0x7e098d0: {
            if (mState != 5) return true;
            if (!notB) return true;
            SetVisibleHelper(mpLayout->FindWindowByID(0x7db8991, 1), 0);
            SetVisibleHelper(mpLayout->FindWindowByID(0x7db8990, 1), 1);
            mState = 6;
            KillSetiEffects(0x3c035721, GetRecorderState());
            SetImageFromLayout(mpLayout->FindWindowByID(0x7c55300, 1), mpLayout, mLevel + 0x7d10de0, -1);
            *(int*)(g_16c7aa4->mpSub7c + 0x20) = mLevel;
            cString s1(0x623d2fc0, 0x7ceb16a, 0);
            Layout* l1 = mpLayout;
            SetTextHelper(l1->FindWindowByID(0x7c79b20, 1), s1.GetText());
            cString s2(0x623d2fc0, 0x7ceb16b, 0);
            Layout* l2 = mpLayout;
            SetTextHelper(l2->FindWindowByID(0x7c79b21, 1), s2.GetText());
            return true;
        }
        case 0x7e09670:
            if (!a) return true;
            SetVisibleHelper(msg->source, 0);
            return true;
        case 0x7eb2740:
            if (mState == 4 && a) {
                SetVisibleHelper(mpLayout->FindWindowByID(0x7e098d0, 1), 0);
                mState = 5;
                return true;
            }
            if (!notB) return true;
            SetVisibleHelper(mpLayout->FindWindowByID(0x7e098d0, 1), 1);
            return true;
        default:
            return false;
        }
    }
    case 0x287259f6: {
        switch (msg->id) {
        case 0x7c79940:
        case 0x7c79948:
            if (mpWinA) mpWinA->SetVisible(1, false);
            mField14 = (msg->id != 0x7c79948) + 1;
            mState = 10;
            RecordResults(true);
            return true;
        case 0x7c79c50: {
            IAudioSystem* audio = GetSystemAT();
            KillSetiEffects(0x9ef448c0, audio ? audio->Query() : 0);
            if (mpWinA) mpWinA->SetVisible(1, false);
            mState = 9;
            return true;
        }
        case 0x7c79c78: {
            IAudioSystem* audio = GetSystemAT();
            KillSetiEffects(0x9ef448c0, audio ? audio->Query() : 0);
            if (mpWinB) mpWinB->SetVisible(1, false);
            mState = 9;
            return true;
        }
        case 0x7e20437:
            if (!CheckFlag(0)) return true;
            mpSubB->F12970();
            return true;
        default:
            return false;
        }
    }
    }
    return result;
}
