// slice s005a6e60 — editor complexity meter / badness calculator ctors+dtors and
// assorted editor helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// Pad one unnamed vtable slot; the index the compiler assigns then lines up with the
// retail vtable offset the disassembly shows.
#define PV(n) virtual void pv##n();

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete(void* p);                                       // @ 0x00f47380

namespace EA { namespace Messaging {
int RemoveHandler(void* server, void* owner, void* userData, int n, int flags);   // @ 0x00571db0
}}

namespace SP {
class cString {
public:
    cString();
    cString(uint32_t a, uint32_t b, const wchar_t* text);  // @ 0x006b5770
    ~cString();
    const wchar_t* GetText();                              // @ 0x006b55c0
    char pad[0x14];
};
struct cSPColorRGB { float r, g, b; };
struct cSPColorRGBA { float r, g, b, a; };

uint32_t ColorRGBToU32(const cSPColorRGB* c);              // @ 0x00458a40
uint32_t ColorRGBAToU32(const cSPColorRGBA* c);            // @ 0x004580c0
}

// ---- engine singletons / helpers -------------------------------------------
void* WindowManager();                 // @ 0x0067caa0
void* PropertyManager();               // @ 0x0067de30
void  TrayHide(void* tray);            // @ 0x00605300
void  SetTextProperty(uint32_t id, void* variant, int a, int b);   // @ 0x00828c30

// ---- message server --------------------------------------------------------
class IMessageServer {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void PostMessage(uint32_t id, void* message, int flags);   // 0x14
    PV(6) PV(7) PV(8)
    virtual void AddHandler(void* owner, uint32_t id);                 // 0x24
};
IMessageServer* MessageServer();       // @ 0x0067dcc0

// ---- intrusive ref-counted object (count at +0x04) --------------------------
class cRefCountValue {
public:
    virtual void Destroy(char flags);   // 0x00
    virtual void Slot1();               // 0x04
    int mRefCount;                      // +0x04
};

// ---- editor UI window ------------------------------------------------------
class IWindow {
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

// the inner complexity bar (only SetPercent at 0x04 is used)
class IComplexityBar {
public:
    PV(0)                                          // 0x00
    virtual void SetPercent(float pct);            // 0x04
};

// ---- layout window (its AddRef/Release sit one slot later) -----------------
class cSPUILayout {
public:
    PV(0)                                          // 0x00
    virtual void AddRef();                         // 0x04
    virtual void Release();                        // 0x08
    bool Init(const void* key, bool a, int b);     // @ 0x008120d0
    bool SetParentWin(void* parent, bool a, int b);// @ 0x008121b0
    void* FindWindowByID(int id, int a);           // @ 0x008105b0
};

class cConnectionDialog : public cSPUILayout {
public:
    cConnectionDialog* ctor();                     // @ 0x00810000 (returns this)
};

// rollover help icon layout (its AddRef is slot 0 and Release slot 4)
class cSPVerbIconRollover {
public:
    virtual void AddRef();                         // 0x00
    PV(1) PV(2) PV(3)                              // 0x04..0x0c
    virtual void Release();                        // 0x10
    PV(5) PV(6) PV(7)                              // 0x14..0x1c
    virtual void Show();                           // 0x20
    cSPVerbIconRollover();
    cSPVerbIconRollover* ctor();                   // @ 0x006051d0 (returns this)
    void Layout();                                 // @ 0x006053a0
    void UpdateCurve();                            // @ 0x006052f0
    void SetVisibility(uint32_t a, uint32_t b);    // @ 0x006052c0
    void SetPositionAndOffset(float a, float b, float c, float d);  // @ 0x008283a0
    void* GetRootWindow();                         // @ 0x00828100
};

// ---- property group / manager ----------------------------------------------
extern uint32_t g_limbTuningGroup;     // @ 0x0151042c

class cPropertyGroup {
public:
    PV(0)                                          // 0x00
    virtual void Release();                        // 0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual const void* GetProperty(uint32_t id);   // 0x28
    virtual bool HasProperty(uint32_t id);          // 0x2c
};

class cPropertyManager {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool GetGroup(uint32_t id, void** out);   // 0x2c
};

// ---- rollover target object (only slot 1 is used) --------------------------
class IRolloverTarget {
public:
    PV(0)                                          // 0x00
    virtual void* FindByID(uint32_t id);           // 0x04
};

// ======================= SP::cSPEditorGeneralBadnessCalculator ==============
namespace SP {
class cBadnessBase1 { public: virtual ~cBadnessBase1() {} virtual int v0(); };
class cBadnessBase2 {
public:
    cBadnessBase2() : m80(0) {}
    virtual ~cBadnessBase2() {}
    virtual int v0();
    int m80;
};
class cSPEditorGeneralBadnessCalculator : public cBadnessBase1, public cBadnessBase2 {
public:
    float mDistanceFromOriginalPosition;            // +0x0c
    float mChangeInUpperLimb;                       // +0x10
    float mChangeInLowerLimb;                       // +0x14
    float mArmAngleChange;                          // +0x18
    float mUpperLimbLength;                         // +0x1c
    float mDistanceFromCameraPlane;                 // +0x20
    float mChangeInDistanceFromParallelPlane;       // +0x24
    float mArmAngle;                                // +0x28
    float mChangeInDistanceFromSymmetryPlane;       // +0x2c
    float mPlaneOfSymmetryAlignment;                // +0x30
    float mLowerLimbLength;                         // +0x34
    float mInvalidLength;                           // +0x38
    float mCameraAngle;                             // +0x3c
    bool  mSnapToCardinalOrientations;              // +0x40
    char  pad41[0x37];                              // +0x41.. (keeps the retail size)

    cSPEditorGeneralBadnessCalculator();
    ~cSPEditorGeneralBadnessCalculator();

    void SetTuningValues(void* group);              // va 005a7930
};

// @ 0x005a7920
cSPEditorGeneralBadnessCalculator::~cSPEditorGeneralBadnessCalculator() {}

// @ 0x005a7900
cSPEditorGeneralBadnessCalculator::cSPEditorGeneralBadnessCalculator() {}
}  // namespace SP

// ---- generic UI element ctor -----------------------------------------------
class cUIThing {
public:
    char pad[0x10];
    short m10;
    short m12;
    cUIThing(void* arg);
    void Helper(int a, int b, void* c, int d, int e);  // 0x0093dd80
};

// @ 0x005a74a0
cUIThing::cUIThing(void* arg) {
    m10 = 0;
    m12 = 0;
    Helper(0x13, 9, arg, 0x10, 1);
}

// ---- dual-cString data ctor -------------------------------------------------
class cDualString {
public:
    SP::cString mName;    // +0x0
    SP::cString mName2;   // +0x14
    uint32_t m28;         // +0x28
    void* m2c;            // +0x2c
    bool m30;             // +0x30
    cDualString();
};

// @ 0x005a7810
cDualString::cDualString() {
    m2c = 0;
    m30 = false;
    m28 = 0xffff0000;
}

// ---- SP::cSPEditorEconomy ----------------------------------------------------
extern char g_changedMsgVt0;   // @ 0x013ff7f0
extern char g_changedMsgVt1;   // @ 0x013f6c9c

namespace SP {
class cSPEditorEconomy {
public:
    void SendChangedMessage();                     // va 005a7840
};
}

// @ 0x005a7840
void SP::cSPEditorEconomy::SendChangedMessage() {
    struct ChangedMessage {
        void*    vt0;    // +0x00
        void*    vt1;    // +0x04
        uint32_t f8;     // +0x08
        uint32_t id;     // +0x0c
        void*    owner;  // +0x10
    } msg;
    msg.f8 = 0;
    msg.vt0 = &g_changedMsgVt0;
    msg.vt1 = &g_changedMsgVt1;
    msg.id = 0x3150c27;
    msg.owner = this;
    MessageServer()->PostMessage(msg.id, &msg, 0);
}

// ---- SP::cSPEditorComplexityMeter ------------------------------------------
namespace SP {
class cMeterB1 { public: virtual int v0(); };
class cMeterB2 { public: virtual int v0(); };
class cMeterB3 { public: cMeterB3() : mC(0) {} virtual int v0(); int mC; };

class cSPEditorComplexityMeter : public cMeterB1, public cMeterB2, public cMeterB3 {
public:
    void* f10;           // +0x10  layout window (cSPUILayout)
    IWindow* f14;        // +0x14  meter window
    IWindow* f18;        // +0x18  animation window
    IWindow* f1c;        // +0x1c  frame window
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
    cSPVerbIconRollover* f40;  // +0x40  rollover layout
    void* f44;           // +0x44  message server
    void* f48;           // +0x48  handler owner
    void* f4c;           // +0x4c  handler id list
    int   f50;           // +0x50
    int   f54;           // +0x54

    cSPEditorComplexityMeter();
    virtual ~cSPEditorComplexityMeter();

    void Init(void* parentWin, void* src);          // va 005a6fc0
    void Update(int delta);                         // va 005a7220
    void SetComplexityPercent(float value);         // va 005a7410
    bool SetValueTextForRollover(void* unused, int* evt);  // va 005a74d0
};
}  // namespace SP

extern uint32_t g_handlers[2];         // @ 0x013f6bf0
extern int      g_stepTime;            // @ 0x0150f9d4
extern float    g_highlightRGB[3];     // @ 0x0150f738

// @ 0x005a6e60
SP::cSPEditorComplexityMeter::cSPEditorComplexityMeter()
    : f10(0), f14(0), f18(0), f1c(0), f20(0), f34(0.0f), f38(0),
      f3c(false), f3d(false), f40(0), f44(0), f48(0), f4c(0), f50(0), f54(0) {}

// @ 0x005a6ee0
SP::cSPEditorComplexityMeter::~cSPEditorComplexityMeter()
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
        ((cSPUILayout*)f10)->Release();
}

// @ 0x005a6fc0
void SP::cSPEditorComplexityMeter::Init(void* parentWin, void* src)
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
    cSPUILayout* layout = dlg;

    // mWinComplexityMeter.mpObject = layout
    if (layout != (cSPUILayout*)f10) {
        if (layout != 0)
            layout->AddRef();
        cSPUILayout* old = (cSPUILayout*)f10;
        f10 = layout;
        if (old != 0)
            old->Release();
    }

    struct Key { uint32_t a, b, c; } key;
    key.a = 0x2793d3e9;
    key.b = 0x0510a95b;
    key.c = 0x40464100;
    ((cSPUILayout*)f10)->Init(&key, true, 0x5b598fa);
    ((cSPUILayout*)f10)->SetParentWin(parentWin, true, 0x5b598fa);

    IWindow* w1 = (IWindow*)((cSPUILayout*)f10)->FindWindowByID(0x330c1ca5, 1);
    if (w1 != f1c) {
        if (w1 != 0)
            w1->AddRef();
        IWindow* old = f1c;
        f1c = w1;
        if (old != 0)
            old->Release();
    }
    if (f1c != 0)
        f1c->SetVisible(1, 1);

    IWindow* w2 = (IWindow*)((cSPUILayout*)f10)->FindWindowByID(0x530c12d0, 1);
    if (w2 != f14) {
        if (w2 != 0)
            w2->AddRef();
        IWindow* old = f14;
        f14 = w2;
        if (old != 0)
            old->Release();
    }

    IWindow* w3 = (IWindow*)((cSPUILayout*)f10)->FindWindowByID(0x5bad010, 1);
    if (w3 != f18) {
        if (w3 != 0)
            w3->AddRef();
        IWindow* old = f18;
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

    cSPVerbIconRollover* roll = (cSPVerbIconRollover*)operator new(0x78, "Editor", 0, 0, 0, 0);
    if (roll != 0)
        roll = roll->ctor();

    if (roll != f40) {
        if (roll != 0)
            roll->AddRef();
        cSPVerbIconRollover* old = f40;
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
void SP::cSPEditorComplexityMeter::Update(int delta)
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

// @ 0x005a7410
void SP::cSPEditorComplexityMeter::SetComplexityPercent(float value)
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

// @ 0x005a74d0
bool SP::cSPEditorComplexityMeter::SetValueTextForRollover(void* unused, int* evt)
{
    if (evt[2] == 10 && evt[3] == 1) {
        if (evt[6] != (int)(size_t)f18) {
            if (f40 != 0)
                TrayHide(f40);
        } else if (f40 != 0) {
            SP::cString keyA(0x7153bbb1, 0x5f110b3, 0);
            SP::cString keyB(0x7153bbb1, 0x5f110b4, 0);

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
            IWindow* region = (IWindow*)f18->GetChild();
            float corner[2];
            corner[0] = (posRect[2] + posRect[0]) * 0.5f;
            corner[1] = (posRect[3] + posRect[1]) * 0.5f;
            region->SetCorner(corner, corner[0], corner[1]);

            IWindow* wm = (IWindow*)WindowManager();
            wm = (IWindow*)wm->GetChild();
            const float* scr = wm->GetRect34();
            float dx = (scr[2] - scr[0]) * 0.025f;
            float dy = (scr[3] - scr[1]) * 0.033333335f;

            IWindow* root = (IWindow*)f40->GetRootWindow();
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

// ---- a generic editor panel with a frame window and an enabled flag --------
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

// @ 0x005a7930
void SP::cSPEditorGeneralBadnessCalculator::SetTuningValues(void* group)
{
    cPropertyManager* pm = (cPropertyManager*)PropertyManager();
    void* holder = 0;
    if (!pm->GetGroup(g_limbTuningGroup, &holder))
        return;

    cPropertyGroup* g = (cPropertyGroup*)holder;
    mDistanceFromOriginalPosition      = *(const float*)g->GetProperty(0x241149f);
    mChangeInUpperLimb                 = *(const float*)g->GetProperty(0x241204b);
    mChangeInLowerLimb                 = *(const float*)g->GetProperty(0x2412051);
    mDistanceFromCameraPlane           = *(const float*)g->GetProperty(0x242175b);
    mChangeInDistanceFromParallelPlane = *(const float*)g->GetProperty(0x2421763);
    mArmAngle                          = *(const float*)g->GetProperty(0x2421767);
    mChangeInDistanceFromSymmetryPlane = *(const float*)g->GetProperty(0x2421776);
    mPlaneOfSymmetryAlignment          = *(const float*)g->GetProperty(0x242177b);
    mCameraAngle                       = *(const float*)g->GetProperty(0x242359a);
    mInvalidLength                     = *(const float*)g->GetProperty(0x242359e);
    mLowerLimbLength                   = *(const float*)g->GetProperty(0x24235a4);
    mUpperLimbLength                   = *(const float*)g->GetProperty(0x2423fe1);
    mArmAngleChange                    = *(const float*)g->GetProperty(0x2423fda);
    mSnapToCardinalOrientations        = (*(const unsigned char*)g->GetProperty(0x255d634)) != 0;

    if (holder != 0)
        g->Release();
}