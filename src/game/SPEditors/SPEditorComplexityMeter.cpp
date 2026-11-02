// src/game/SPEditors/SPEditorComplexityMeter.cpp -- migrated from slice(s) s005a6e60 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorComplexityMeter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cPropertyManager.h"
#include "cSPColorRGB.h"
#include "cSPColorRGBA.h"
#include "SP/cSPEditorComplexityMeter.h"
#include "SP/cSPEditorEconomy.h"
#include "cSPUILayout.h"
#include "cSPVerbIconRollover.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_handlers[2];         // @ 0x013f6bf0
extern int      g_stepTime;            // @ 0x0150f9d4
extern float    g_highlightRGB[3];     // @ 0x0150f738

// ---- items of slice s005a6e60 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
namespace EA {
namespace Messaging {
int RemoveHandler(void* server, void* owner, void* userData, int n, int flags);   // @ 0x00571db0
}
}
namespace SP {
class cString_s005a_6e60 {
public:
    cString_s005a_6e60();
    cString_s005a_6e60(uint32_t a, uint32_t b, const wchar_t* text);  // @ 0x006b5770
    ~cString_s005a_6e60();
    const wchar_t* GetText();                              // @ 0x006b55c0
    char pad[0x14];
};
}
namespace SP {
struct cSPColorRGB { float r, g, b; };
}
namespace SP {
struct cSPColorRGBA { float r, g, b, a; };
}
namespace SP {
uint32_t ColorRGBToU32(const cSPColorRGB* c);              // @ 0x00458a40
}
namespace SP {
uint32_t ColorRGBAToU32(const cSPColorRGBA* c);            // @ 0x004580c0
}
void* WindowManager();                 // @ 0x0067caa0
void  TrayHide(void* tray);            // @ 0x00605300
void  SetTextProperty(uint32_t id, void* variant, int a, int b);   // @ 0x00828c30
class IMessageServer {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void PostMessage(uint32_t id, void* message, int flags);   // 0x14
    PV(6) PV(7) PV(8)
    virtual void AddHandler(void* owner, uint32_t id);                 // 0x24
};
IMessageServer* MessageServer();       // @ 0x0067dcc0
class cRefCountValue {
public:
    virtual void Destroy(char flags);   // 0x00
    virtual void Slot1();               // 0x04
    int mRefCount;                      // +0x04
};
class IWindow_s005a_6e60 {
public:
    virtual void AddRef();                        // 0x00
    virtual void Release();                       // 0x04
    PV(2)                                         // 0x08
    virtual void* FindWindowByID(uint32_t id);    // 0x0c
    virtual void* GetChild();                     // 0x10
    PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    virtual const float* GetRect34();              // 0x34
    virtual const float* GetRect38();              // 0x38
    PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    virtual void SetColor(uint32_t color);         // 0x5c
    virtual void SetArea(const float* rect);       // 0x60
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
    virtual void SetVisible(int a, int b);         // 0x7c
    PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
    PV(60) PV(61) PV(62) PV(63) PV(64)
    virtual void OnOwner(void* owner);             // 0x104
    virtual void SetCorner(const float* pos, float x, float y);   // 0xc0
};
class IComplexityBar {
public:
    PV(0)                                          // 0x00
    virtual void SetPercent(float pct);            // 0x04
};
class cSPUILayout_s005a_6e60 {
public:
    PV(0)                                          // 0x00
    virtual void AddRef();                         // 0x04
    virtual void Release();                        // 0x08
    bool Init(const void* key, bool a, int b);     // @ 0x008120d0
    bool SetParentWin(void* parent, bool a, int b);// @ 0x008121b0
    void* FindWindowByID(int id, int a);           // @ 0x008105b0
};
class cConnectionDialog : public cSPUILayout_s005a_6e60 {
public:
    cConnectionDialog* ctor();                     // @ 0x00810000 (returns this)
};
class cSPVerbIconRollover_s005a_6e60 {
public:
    virtual void AddRef();                         // 0x00
    PV(1) PV(2) PV(3)                              // 0x04..0x0c
    virtual void Release();                        // 0x10
    PV(5) PV(6) PV(7)                              // 0x14..0x1c
    virtual void Show();                           // 0x20
    cSPVerbIconRollover_s005a_6e60();
    cSPVerbIconRollover_s005a_6e60* ctor();                   // @ 0x006051d0 (returns this)
    void Layout();                                 // @ 0x006053a0
    void UpdateCurve();                            // @ 0x006052f0
    void SetVisibility(uint32_t a, uint32_t b);    // @ 0x006052c0
    void SetPositionAndOffset(float a, float b, float c, float d);  // @ 0x008283a0
    void* GetRootWindow();                         // @ 0x00828100
};
class IRolloverTarget {
public:
    PV(0)                                          // 0x00
    virtual void* FindByID(uint32_t id);           // 0x04
};
class cUIThing {
public:
    char pad[0x10];
    short m10;
    short m12;
    cUIThing(void* arg);
    void Helper(int a, int b, void* c, int d, int e);  // 0x0093dd80
};
class cDualString {
public:
    SP::cString_s005a_6e60 mName;    // +0x0
    SP::cString_s005a_6e60 mName2;   // +0x14
    uint32_t m28;         // +0x28
    void* m2c;            // +0x2c
    bool m30;             // +0x30
    cDualString();
};
namespace SP {
class cMeterB1 { public: virtual int v0(); };
}
namespace SP {
class cMeterB2 { public: virtual int v0(); };
}
namespace SP {
class cMeterB3 { public: cMeterB3() : mC(0) {} virtual int v0(); int mC; };
}
namespace SP {
class cSPEditorComplexityMeter_s005a_6e60 : public cMeterB1, public cMeterB2, public cMeterB3 {
public:
    void* f10;           // +0x10  layout window (cSPUILayout)
    IWindow_s005a_6e60* f14;        // +0x14  meter window
    IWindow_s005a_6e60* f18;        // +0x18  animation window
    IWindow_s005a_6e60* f1c;        // +0x1c  frame window
    cRefCountValue* f20; // +0x20  ref-counted value
    float f24;           // +0x24
    float f28;           // +0x28
    float f2c;           // +0x2c
    float f30;           // +0x30
    float f34;           // +0x34  complexity percent
    int   f38;           // +0x38  animation counter
    bool  f3c;           // +0x3c
    bool  f3d;           // +0x3d
    char  pad3e[2];      // +0x3e
    cSPVerbIconRollover_s005a_6e60* f40;  // +0x40  rollover layout
    void* f44;           // +0x44  message server
    void* f48;           // +0x48  handler owner
    void* f4c;           // +0x4c  handler id list
    int   f50;           // +0x50
    int   f54;           // +0x54

    cSPEditorComplexityMeter_s005a_6e60();  // 0x005a6e60 (SP::cSPEditorComplexityMeter::cSPEditorComplexityMeter_s005a_6e60)
    virtual ~cSPEditorComplexityMeter_s005a_6e60();  // 0x005a6e60 (SP::cSPEditorComplexityMeter::cSPEditorComplexityMeter_s005a_6e60)

    void Init(void* parentWin, void* src);          // va 005a6fc0 0x005a6fc0
    void Update(int delta);                         // va 005a7220
    void SetComplexityPercent(float value);         // va 005a7410
    bool SetValueTextForRollover(void* unused, int* evt);  // va 005a74d0
};
}
extern uint32_t g_handlers[2];         // @ 0x013f6bf0
extern int      g_stepTime;            // @ 0x0150f9d4
extern float    g_highlightRGB[3];     // @ 0x0150f738
class IFrameWin {
public:
    PV(0) PV(1) PV(2) PV(3)
    virtual void* GetChildAt(void* owner, int flags);   // 0x10
};
class cEditorPanel {
public:
    char pad1c[0x1c];
    IFrameWin* f1c;    // +0x1c
    char pad20[0x18];
    bool f38;          // +0x38
    bool HandleMessage(int msgId, void** payload);   // @ 0x005a7380
};
// ---- items of slice s005a6e60 end

// @ 0x005a6e60
SP::cSPEditorComplexityMeter_s005a_6e60::cSPEditorComplexityMeter_s005a_6e60()
: f10(0), f14(0), f18(0), f1c(0), f20(0), f34(0.0f), f38(0),
      f3c(false), f3d(false), f40(0), f44(0), f48(0), f4c(0), f50(0), f54(0) {}

// @ 0x005a6ee0
SP::cSPEditorComplexityMeter_s005a_6e60::~cSPEditorComplexityMeter_s005a_6e60()
{
    if (f44 != 0) {
        void* server = f44;
        f44 = 0;
        EA::Messaging::RemoveHandler(server, f48, f4c, f50, f54);
    }
    if (f40 != 0)
        f40->Release();
    if (f20 != 0) {
        if (--f20->mRefCount == 0) {
            f20->mRefCount = 1;
            f20->Destroy(1);
        }
    }
    if (f1c != 0)
        f1c->Release();
    if (f18 != 0)
        f18->Release();
    if (f14 != 0)
        f14->Release();
    if (f10 != 0)
        ((cSPUILayout_s005a_6e60*)f10)->Release();
}

// @ 0x005a6fc0
void SP::cSPEditorComplexityMeter_s005a_6e60::Init(void* parentWin, void* src)
{
    // mOriginalComplexityMeterArea.mTop = src (intrusive pointer, count at +0x04)
    if ((void*)f20 != src) {
        cRefCountValue* s = (cRefCountValue*)src;
        if (s != 0)
            s->mRefCount++;
        cRefCountValue* old = f20;
        f20 = s;
        if (old != 0 && --old->mRefCount == 0) {
            old->mRefCount = 1;
            old->Destroy(1);
        }
    }

    cConnectionDialog* dlg = (cConnectionDialog*)operator new(0x18, "Editor", 0, 0, 0, 0);
    if (dlg != 0)
        dlg = dlg->ctor();
    cSPUILayout_s005a_6e60* layout = dlg;

    // mWinComplexityMeter.mpObject = layout
    if (layout != (cSPUILayout_s005a_6e60*)f10) {
        if (layout != 0)
            layout->AddRef();
        cSPUILayout_s005a_6e60* old = (cSPUILayout_s005a_6e60*)f10;
        f10 = layout;
        if (old != 0)
            old->Release();
    }

    struct Key { uint32_t a, b, c; } key;
    key.a = 0x2793d3e9;
    key.b = 0x0510a95b;
    key.c = 0x40464100;
    ((cSPUILayout_s005a_6e60*)f10)->Init(&key, true, 0x5b598fa);
    ((cSPUILayout_s005a_6e60*)f10)->SetParentWin(parentWin, true, 0x5b598fa);

    IWindow_s005a_6e60* w1 = (IWindow_s005a_6e60*)((cSPUILayout_s005a_6e60*)f10)->FindWindowByID(0x330c1ca5, 1);
    if (w1 != f1c) {
        if (w1 != 0)
            w1->AddRef();
        IWindow_s005a_6e60* old = f1c;
        f1c = w1;
        if (old != 0)
            old->Release();
    }
    if (f1c != 0)
        f1c->SetVisible(1, 1);

    IWindow_s005a_6e60* w2 = (IWindow_s005a_6e60*)((cSPUILayout_s005a_6e60*)f10)->FindWindowByID(0x530c12d0, 1);
    if (w2 != f14) {
        if (w2 != 0)
            w2->AddRef();
        IWindow_s005a_6e60* old = f14;
        f14 = w2;
        if (old != 0)
            old->Release();
    }

    IWindow_s005a_6e60* w3 = (IWindow_s005a_6e60*)((cSPUILayout_s005a_6e60*)f10)->FindWindowByID(0x5bad010, 1);
    if (w3 != f18) {
        if (w3 != 0)
            w3->AddRef();
        IWindow_s005a_6e60* old = f18;
        f18 = w3;
        if (old != 0)
            old->Release();
    }

    if (f14 != 0) {
        const float* r = f14->GetRect34();
        f24 = r[0];
        f28 = r[1];
        f2c = r[2];
        f30 = r[3];
    }

    cSPVerbIconRollover_s005a_6e60* roll = (cSPVerbIconRollover_s005a_6e60*)operator new(0x78, "Editor", 0, 0, 0, 0);
    if (roll != 0)
        roll = roll->ctor();

    if (roll != f40) {
        if (roll != 0)
            roll->AddRef();
        cSPVerbIconRollover_s005a_6e60* old = f40;
        f40 = roll;
        if (old != 0)
            old->Release();
    }
    if (f40 != 0)
        f40->Layout();

    if (f18 != 0)
        f18->OnOwner(this);

    f44 = MessageServer();
    f48 = (void*)((char*)this + 4);
    f4c = (void*)g_handlers;
    f50 = 2;
    f54 = 0;

    if (f44 != 0 && f48 != 0) {
        IMessageServer* ms = (IMessageServer*)f44;
        for (unsigned i = 0; i < 2; i++)
            ms->AddHandler(f48, g_handlers[i]);
    }
}

// @ 0x005a7220
void SP::cSPEditorComplexityMeter_s005a_6e60::Update(int delta)
{
    if (f14 != 0 && f18 != 0) {
        IComplexityBar* bar = (IComplexityBar*)f18->FindWindowByID(0x10edf11);
        if (bar != 0) {
            float pct = f34 * 100.0f;
            if (pct < 0.0f)
                pct = 0.0f;
            if (pct > 100.0f)
                pct = 100.0f;
            bar->SetPercent(pct);
        }
    }

    if (f3c) {
        if (f3d)
            goto tick;
        f38 = 0;
        f3d = true;
    }
    if (!f3d)
        return;

tick:
    {
        int half = g_stepTime / 2;
        int dist = (f38 < half) ? (half - f38) : (f38 - half);
        float ratio = (float)dist / (float)half;

        SP::cSPColorRGBA rgba;
        rgba.r = g_highlightRGB[0];
        rgba.g = g_highlightRGB[1];
        rgba.b = g_highlightRGB[2];
        rgba.a = ratio;
        f18->SetColor(SP::ColorRGBAToU32(&rgba));

        f38 += delta;
        if (f38 > g_stepTime) {
            if (!f3c) {
                SP::cSPColorRGB rgb;
                rgb.r = g_highlightRGB[0];
                rgb.g = g_highlightRGB[1];
                rgb.b = g_highlightRGB[2];
                f18->SetColor(SP::ColorRGBToU32(&rgb));
                f3d = false;
                return;
            }
            f38 %= g_stepTime;
        }
    }
}

// @ 0x005a7380
bool cEditorPanel::HandleMessage(int msgId, void** payload)
{
    if (msgId == 0x522f9cd) {
        if (*payload != 0) {
            IRolloverTarget* target = (IRolloverTarget*)*payload;
            void* obj = target->FindByID(0x31e56741);
            if (obj != 0) {
                cDualString str;
                void* found = f1c->GetChildAt((char*)obj + 0x40, 0);
                f38 = (found == (void*)3);
                (void)str;
            }
        }
        return true;
    }
    if (msgId == 0x522f9ce) {
        f38 = false;
        return true;
    }
    return false;
}

// @ 0x005a7410
void SP::cSPEditorComplexityMeter_s005a_6e60::SetComplexityPercent(float value)
{
    float v = (0.0f > value) ? 0.0f : value;
    v = (v < 1.0f) ? v : 1.0f;
    f34 = v;
    if (f14 != 0) {
        float rect[4];
        rect[0] = f24;
        rect[1] = f28;
        rect[2] = (f2c - f24) * v + f24;
        rect[3] = f30;
        f14->SetArea(rect);
    }
}

// @ 0x005a74a0
cUIThing::cUIThing(void* arg)
{
    m10 = 0;
    m12 = 0;
    Helper(0x13, 9, arg, 0x10, 1);
}

// @ 0x005a74d0
bool SP::cSPEditorComplexityMeter_s005a_6e60::SetValueTextForRollover(void* unused, int* evt)
{
    if (evt[2] == 10 && evt[3] == 1) {
        if (evt[6] != (int)(size_t)f18) {
            if (f40 != 0)
                TrayHide(f40);
        } else if (f40 != 0) {
            SP::cString_s005a_6e60 keyA(0x7153bbb1, 0x5f110b3, 0);
            SP::cString_s005a_6e60 keyB(0x7153bbb1, 0x5f110b4, 0);

            cUIThing v1((void*)keyA.GetText());
            cUIThing v2((void*)keyB.GetText());
            cUIThing v3((void*)keyA.GetText());
            SetTextProperty(0x331cc0e, &v1, 1, 0);
            SetTextProperty(0x4d97708, &v2, 1, 0);
            SetTextProperty(0x331cc0f, &v3, 1, 0);

            f40->SetVisibility(0x4d97710, 0);
            f40->Show();
            f40->Layout();

            const float* posRect = f18->GetRect38();
            IWindow_s005a_6e60* region = (IWindow_s005a_6e60*)f18->GetChild();
            float corner[2];
            corner[0] = (posRect[2] + posRect[0]) * 0.5f;
            corner[1] = (posRect[3] + posRect[1]) * 0.5f;
            region->SetCorner(corner, corner[0], corner[1]);

            IWindow_s005a_6e60* wm = (IWindow_s005a_6e60*)WindowManager();
            wm = (IWindow_s005a_6e60*)wm->GetChild();
            const float* scr = wm->GetRect34();
            float dx = (scr[2] - scr[0]) * 0.025f;
            float dy = (scr[3] - scr[1]) * 0.033333335f;

            IWindow_s005a_6e60* root = (IWindow_s005a_6e60*)f40->GetRootWindow();
            if (root != 0) {
                const float* rr = root->GetRect38();
                dx = -(rr[2] - rr[0]) - dx;
            }
            f40->UpdateCurve();
            f40->SetPositionAndOffset(0.0f, 0.0f, dx, dy);
        }
    }
    return false;
}

// @ 0x005a7810
cDualString::cDualString()
{
    m2c = 0;
    m30 = false;
    m28 = 0xffff0000;
}
