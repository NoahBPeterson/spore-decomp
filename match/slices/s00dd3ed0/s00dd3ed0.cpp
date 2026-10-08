// Slice s00dd3ed0 -- SP::cSPUICommScreen::Init (0x00dd4260, 1560 bytes, __thiscall, ret 4).
//
// Builds the space-comm screen: loads the UI layout, creates the texture preloader, registers the
// screen as winproc on six windows, sizes/centres the main comm window (floor()ed to whole pixels),
// creates the two vertical scroll frames and re-parents the text/button roots into them, hides the
// eight response/preview windows, resets the response count and speaker text, loads six localized
// strings and finally registers the screen's message handler with the message server.
// Layout is the retail one (AutoRefCount members at +0x0c ... +0x30), not the 2008 PDB's.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH frame in the original).
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
    Rect(const Rect& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
    Rect& operator=(const Rect& o) { x1 = o.x1; y1 = o.y1; x2 = o.x2; y2 = o.y2; return *this; }
};

struct IWindow {
    virtual int AddRef();                                   // +0x00
    virtual int Release();                                  // +0x04
    PV2                                                     // 2..3
    virtual IWindow* GetParent();                           // slot 4 (+0x10)
    PV8 PV                                                  // 5..13
    virtual const Rect& GetRealArea();                      // slot 14 (+0x38)
    PV8 PV                                                  // 15..23
    virtual void SetArea(const Rect& r);                    // slot 24 (+0x60)
    virtual void SetLocation(float x, float y);             // slot 25 (+0x64)
    PV                                                      // 26
    virtual void SetLayoutArea(const Rect& r);              // slot 27 (+0x6c)
    PV2 PV                                                  // 28..30
    virtual void SetFlag(int flag, bool on);                // slot 31 (+0x7c)
    PV8 PV8 PV4 PV2                                         // 32..53
    virtual void AddWindow(IWindow* w);                     // slot 54 (+0xd8)
    virtual void RemoveWindow(IWindow* w);                  // slot 55 (+0xdc)
    PV8 PV                                                  // 56..64
    virtual void AddWinProc(void* proc);                    // slot 65 (+0x104)
};

struct cSPUILayout {                                        // refcount at +4 / +8
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    char data[0x14];
    void Init(const void* key, bool visible, uint32_t parentID);   // 0x008120d0 (thiscall, ret 0xc)
    IWindow* FindWindowByID(uint32_t id, bool recursive);          // 0x008105b0
    cSPUILayout();                                                 // 0x00810000
};

struct cTexturePreload {                                    // refcount at +0 / +4
    virtual int AddRef();
    virtual int Release();
    char data[0x30];
    cTexturePreload(int arg);                               // 0x007b07e0
};

struct cString {                                            // SP::cString, 0x14 bytes
    uint32_t d[5];
    void Load(uint32_t table, uint32_t id, int flag);       // 0x006b54b0 (thiscall, ret 0xc)
};

struct MessageServer {
    PV8 PV                                                  // slots 0..8
    virtual void AddHandler(void* handler, uint32_t id);    // slot 9 (+0x24)
};
MessageServer* __cdecl GetMessageServer();                  // 0x0067dcc0
extern uint32_t gMsgID;                                     // 0x015a2b30

struct AutoHandler {                                        // EA::Messaging::AutoHandler (0x14 bytes)
    MessageServer* mpServer;
    void* mpHandler;
    uint32_t* mpIdArray;
    uint32_t mnIdArrayCount;
    int mnPriority;
};

template <class T> struct Ref {                             // EA::AutoRefCount
    T* p;
    Ref& operator=(T* q) {
        if (q != p) { T* old = p; if (q) q->AddRef(); p = q; if (old) old->Release(); }
        return *this;
    }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};

IWindow* __cdecl CreateScrollFrameVertical(const wchar_t* name, Ref<IWindow>* out, int flag);   // 0x00807600
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);                 // 0x00f473a0

static __forceinline void HideWindow(cSPUILayout* layout, uint32_t id)
{
    IWindow* w = layout->FindWindowByID(id, true);
    if (w)
        w->SetFlag(1, false);
}

class cSPUICommScreen {
public:
    void* vtbl;                                             // +0x00 IWinProc
    char mHandlerSub[8];                                    // +0x04 (message-handler subobject)
    Ref<cSPUILayout> mLayout;                               // +0x0c
    uint32_t pad10;
    Ref<IWindow> mScrollHolder;                             // +0x14
    Ref<IWindow> mTextScrollRoot;                           // +0x18
    Ref<IWindow> mButtonsHolder;                            // +0x1c
    Ref<IWindow> mButtonsRoot;                              // +0x20
    Ref<IWindow> mTextRoot;                                 // +0x24
    Ref<IWindow> mButtonsList;                              // +0x28
    uint32_t pad2c;
    Ref<cTexturePreload> mPreload;                          // +0x30
    uint32_t pad34[3];
    bool mOpen;                                             // +0x40
    char pad41[3];
    cString mStr[6];                                        // +0x44, +0x58, +0x6c, +0x80, +0x94, +0xa8
    uint32_t padbc[2];
    AutoHandler mHandler;                                   // +0xc4

    void Dispose();                                         // 0x00dd3d30
    void SetResponseCount(int n);                           // 0x00dd3ed0
    void SetSpeakerText(const wchar_t* text);               // 0x00dd2ad0
    void Init(const void* key);
};

// @ 0x00DD4260
void cSPUICommScreen::Init(const void* key)
{
    if (mLayout.p != 0)
        Dispose();

    mLayout = new ("UI", 0, 0, 0, 0) cSPUILayout;
    mLayout->Init(key, true, 0x5b598fa);
    mOpen = false;

    mPreload = new ("UI", 0, 0, 0, 0) cTexturePreload(-1);

    {
        uint32_t ids[6] = { 0x57df5ca, 0x57df5c8, 0x57df5c9, 0x5e51d28, 0x5e51d30, 0x1c3bb0c };
        for (uint32_t i = 0; i < 6; ++i) {
            IWindow* w = mLayout->FindWindowByID(ids[i], true);
            if (w)
                w->AddWinProc(this);
        }
    }

    IWindow* main = mLayout->FindWindowByID(0x1c3bb0c, true);
    const Rect& r = main->GetRealArea();
    Rect rc;
    rc.x1 = r.x1;
    rc.y1 = r.y1;
    rc.x2 = r.x2;
    float h = r.y2 - rc.y1;
    if (h > 768.0f)
        h = 768.0f;
    rc.y2 = h;
    float w43 = h * 1.3333334f;
    rc.y1 = 0.0f;
    rc.x1 = 0.0f;
    rc.x2 = w43;
    main->SetLayoutArea(rc);

    IWindow* parent = main->GetParent();
    const Rect& pr = parent->GetRealArea();
    Rect pa = pr;
    const Rect& cr = main->GetRealArea();
    rc = cr;
    main->SetLocation((float)floor((double)(((pa.x2 - pa.x1) - (rc.x2 - rc.x1)) * 0.5f + pa.x1)),
                      (float)floor((double)(pa.y2 - (rc.y2 - rc.y1))));

    mTextScrollRoot = 0;
    mScrollHolder = CreateScrollFrameVertical(L"ScrollFrameVerticalGeneric", &mTextScrollRoot, 1);
    mButtonsRoot = 0;
    mButtonsHolder = CreateScrollFrameVertical(L"ScrollFrameVerticalGeneric", &mButtonsRoot, 1);

    IWindow* w1 = mLayout->FindWindowByID(0x4ade899, true);
    w1->AddWindow(mScrollHolder);
    mScrollHolder->SetArea(w1->GetRealArea());
    mScrollHolder->SetLocation(0.0f, 0.0f);

    IWindow* w2 = mLayout->FindWindowByID(0x4b30b3b, true);
    w2->AddWindow(mButtonsHolder);
    mButtonsHolder->SetArea(w2->GetRealArea());
    mButtonsHolder->SetLocation(0.0f, 0.0f);

    mTextRoot = mLayout->FindWindowByID(0x4adc3bf, true);
    mButtonsList = mLayout->FindWindowByID(0x18072cb, true);

    mTextRoot->GetParent()->RemoveWindow(mTextRoot);
    mTextScrollRoot->AddWindow(mTextRoot);
    mButtonsList->GetParent()->RemoveWindow(mButtonsList);
    mButtonsRoot->AddWindow(mButtonsList);

    HideWindow(mLayout.p, 0x1c3bb0c);
    HideWindow(mLayout.p, 0x5e4e5f0);
    HideWindow(mLayout.p, 0x5e4e5f8);
    HideWindow(mLayout.p, 0x5e3c090);
    HideWindow(mLayout.p, 0x5e62a48);
    HideWindow(mLayout.p, 0x5da83b8);
    HideWindow(mLayout.p, 0x5dbd7d8);
    HideWindow(mLayout.p, 0x6429c80);

    SetResponseCount(0);
    SetSpeakerText(L"");
    mStr[0].Load(0x2db6dad3, 0x66f61c1, 0);
    mStr[1].Load(0x2db6dad3, 0x6790598, 0);
    mStr[2].Load(0x2db6dad3, 0x6790599, 0);
    mStr[3].Load(0x2db6dad3, 0x679ed24, 0);
    mStr[4].Load(0x2db6dad3, 0x66f7a1c, 0);
    mStr[5].Load(0x2db6dad3, 0x66f7a1d, 0);

    void* handler = mHandlerSub;
    MessageServer* server = GetMessageServer();
    mHandler.mpServer = server;
    mHandler.mpHandler = handler;
    mHandler.mpIdArray = &gMsgID;
    mHandler.mnIdArrayCount = 1;
    mHandler.mnPriority = 0;
    if (server != 0 && handler != 0)
        server->AddHandler(handler, gMsgID);
}
