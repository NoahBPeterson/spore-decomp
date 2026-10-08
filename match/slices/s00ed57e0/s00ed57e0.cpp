// Slice s00ed57e0: scenario play-mode HUD (cScenarioPlayModeUI-like): InitForLoad builds the layout and
// its sub-UIs. Module flags: /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Allocation (EA operator new with a name tag)
// ---------------------------------------------------------------------------
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void* operator new(unsigned int size, int align, const char* name, void* alloc);       // 0x009512d0
void* GetUIAllocator();                                                                // 0x009512c0

// ---------------------------------------------------------------------------
// Reference-counted pointer: AddRef the new value, store, Release the old one
// ---------------------------------------------------------------------------
template <class T> struct ARC {
    T* p;
    ARC& operator=(T* n)
    {
        T* o = p;
        if (n != o) {
            if (n) n->AddRef();
            p = n;
            if (o) o->Release();
        }
        return *this;
    }
};

// Two flavours of intrusive refcount interface (by vtable slot of AddRef / Release)
struct RC01 { virtual void AddRef(); virtual void Release(); };
struct RC12 { virtual void s0(); virtual void AddRef(); virtual void Release(); };

struct ResKey { uint instance; uint type; uint group; };

struct IWindow {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24();
    virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34();
    virtual void w35(); virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
    virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44();
    virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49();
    virtual void w50(); virtual void w51(); virtual void w52(); virtual void w53(); virtual void w54();
    virtual void w55(); virtual void w56(); virtual void w57(); virtual void w58(); virtual void w59();
    virtual void w60(); virtual void w61(); virtual void w62(); virtual void w63(); virtual void w64();
    virtual void AddWinProc(void* proc);                                  // slot 65 (+0x104)
};

// SP::cString (size 0x1c)
struct cString {
    char data[0x1c];
    cString(uint tableId, uint instanceId, uint placeholder);             // 0x006b5770 (ret 0xc)
    ~cString();                                                           // 0x006b5240
    const wchar_t* GetText();                                             // 0x006b55c0
};

struct cSPUILayout : RC12 {
    char pad[0x14];                                                       // size 0x18
    cSPUILayout();                                                        // 0x00810000
    bool Init(const ResKey* key, bool b, uint instance);                  // 0x008120d0 (ret 0xc)
    void Shutdown(bool b);                                                // 0x00811ad0 (ret 4)
    IWindow* FindWindowByID(uint id, bool b);                             // 0x008105b0 (ret 8)
    void SetVisibility(bool b);                                           // 0x00810590 (ret 4)
};

struct ComplexityMeter : RC01 {                                           // size 0x58
    char pad[0x54];
    ComplexityMeter();                                                    // 0x00ed02c0
    void Setup(IWindow* win, uint v);                                     // 0x00ed0400 (ret 8)
};
struct ChecklistUI : RC01 {                                               // size 0x38
    char pad[0x34];
    ChecklistUI();                                                        // 0x00ef7900
    void SelectCategory(IWindow* win, int cat);                           // 0x00efb9c0 (ret 8)
};
struct PanelA : RC12 {                                                    // size 0xa0
    char pad[0x9c];
    PanelA();                                                             // 0x00ed2e40
    bool Init();                                                          // 0x00ed3c00
};
struct PanelB : RC12 {                                                    // size 0x40
    char pad[0x3c];
    PanelB();                                                             // 0x00ee9180
    virtual void s3();
    virtual bool Init(int a);                                             // slot 4 (+0x10)
};
struct EditModeScriptUI : RC12 {                                          // size 0x10c
    char pad[0x108];
    EditModeScriptUI();                                                   // 0x00edd580
    bool Init();                                                          // 0x00ee3940
};
struct PanelC : RC01 {                                                    // size 0xe0
    char pad[0xdc];
    PanelC();                                                             // 0x00edaf10
    void Setup(IWindow* win);                                             // 0x00edb4c0 (ret 4)
};
struct GlobalOptions : RC01 {                                             // size 0x58
    char pad[0x54];
    GlobalOptions();                                                      // 0x00e00ec0
};
struct Posse : RC01 {                                                     // size 0x20c
    char pad[0x208];
    Posse();                                                              // 0x00e25710
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6();
    virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16();
    virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21();
    virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26();
    virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
    virtual void p32();
    virtual bool Load(const void* key);                                   // slot 33 (+0x84)
    virtual void q34(); virtual void q35();
    virtual void SetPos(float x, float y, int a, int b);                  // slot 36 (+0x90)
    virtual void r37(); virtual void r38(); virtual void r39(); virtual void r40(); virtual void r41();
    virtual void r42(); virtual void r43(); virtual void r44(); virtual void r45();
    virtual void SetCaption(const wchar_t* text);                         // slot 46 (+0xb8)
    virtual void s47();
    virtual void SetVisible(int v);                                       // slot 48 (+0xc0)
    void F00e21950(int v);                                                // 0x00e21950 (ret 4)
};

struct WinMgrInner {
    virtual void s0();
    virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4(); virtual void m5();
    virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9(); virtual void m10();
    virtual void m11(); virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19(); virtual void m20();
    virtual void m21(); virtual void m22(); virtual void m23(); virtual void m24(); virtual void m25();
    virtual void m26(); virtual void m27(); virtual void m28(); virtual void m29(); virtual void m30();
    virtual void m31(); virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39(); virtual void m40();
    virtual void m41(); virtual void m42(); virtual void m43(); virtual void m44(); virtual void m45();
    virtual void m46(); virtual void m47(); virtual void m48(); virtual void m49(); virtual void m50();
    virtual void m51(); virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual IWindow* FindWindowByID(uint id, bool b);                     // slot 60 (+0xf0)
};
struct WinMgr {
    virtual void s0();
    virtual WinMgrInner* GetInner();                                      // slot 1 (+4)
};
WinMgr* WindowManager();                                                  // 0x0067caa0

struct MsgServer {
    virtual void s0();
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual void RegisterHandler(void* handler, uint msg);                // slot 9 (+0x24)
};
MsgServer* MessageServer();                                               // 0x0067dcc0

struct AutoHandler {
    MsgServer* mpServer;
    void* mpHandler;
    const uint* mpIds;
    uint mnIds;
    uint mField;
};
extern uint gMsgIds[];                                                    // 0x01489d38

struct UIGlobals { char pad[0x74]; struct { char pad[0xd0]; uint value; }* p; };
extern struct UIGlobals* gUIGlobals;                                      // 0x016c7aa4

extern char gPosseKey[];                                                  // 0x015ac28c

struct ScenarioHUD {
    int pad0[2];                            // +0
    char mProc[8];                          // +8   IWinProc sub-object
    char mHandler[4];                       // +0x10 IHandler sub-object
    ARC<PanelA> mPanelA;                    // +0x14
    ARC<EditModeScriptUI> mScriptUI;        // +0x18
    int pad1c;
    int mCurrentIndex;                      // +0x20
    ARC<cSPUILayout> mLayout;               // +0x24
    ARC<PanelB> mPanelB;                    // +0x28
    ARC<PanelC> mPanelC;                    // +0x2c
    ARC<ComplexityMeter> mMeterWorld;       // +0x30
    ARC<ComplexityMeter> mMeterTerra;       // +0x34
    ARC<ChecklistUI> mChecklist0;           // +0x38
    ARC<ChecklistUI> mChecklist1;           // +0x3c
    ARC<Posse> mPosse;                      // +0x40
    ARC<GlobalOptions> mGlobalOptions;      // +0x44
    char pad48[0x28];
    AutoHandler mAutoHandler;               // +0x70
    char pad84[0x10];
    bool mFlag94;                           // +0x94

    void F00ed5890(int v);                  // 0x00ed5890 (ret 4)
    bool InitForLoad();                     // 0x00ed5d70
};

// @ 0x00ed5d70
bool ScenarioHUD::InitForLoad()
{
    {
        ResKey key = { 0x396f69f5, 0x510a95b, 0x40464100 };
        mLayout = new ("UI", 0, 0, 0, 0) cSPUILayout();
        if (!mLayout.p->Init(&key, true, 0x2edd95ca)) {
            mLayout.p->Shutdown(true);
            mLayout = 0;
            return false;
        }
    }
    IWindow* w = mLayout.p->FindWindowByID(0xffffffff, true);
    if (w)
        w->AddWinProc(&mProc);

    w = mLayout.p->FindWindowByID(0x73bd748, true);
    if (w) {
        mMeterWorld = new ("UI/cScenarioComplexityMeter/World", 0, 0, 0, 0) ComplexityMeter();
        mMeterWorld.p->Setup(w, gUIGlobals->p->value);
    }
    w = mLayout.p->FindWindowByID(0x74b85c8, true);
    if (w) {
        mMeterTerra = new ("UI/cScenarioComplexityMeter/Terra", 0, 0, 0, 0) ComplexityMeter();
        mMeterTerra.p->Setup(w, gUIGlobals->p->value);
    }
    w = mLayout.p->FindWindowByID(0x771f0a0, true);
    if (w) {
        mChecklist0 = new ("UI/cScenarioTutorialsChecklistUI", 0, 0, 0, 0) ChecklistUI();
        mChecklist0.p->SelectCategory(w, 0);
    }
    w = mLayout.p->FindWindowByID(0x7736c78, true);
    if (w) {
        mChecklist1 = new ("UI/cScenarioTutorialsChecklistUI", 0, 0, 0, 0) ChecklistUI();
        mChecklist1.p->SelectCategory(w, 1);
    }

    mPanelA = new ("UI", 0, 0, 0, 0) PanelA();
    if (!mPanelA.p->Init())
        mPanelA = 0;

    mPanelB = new ("UI", 0, 0, 0, 0) PanelB();
    if (!mPanelB.p->Init(0))
        mPanelB = 0;

    if (mLayout.p->FindWindowByID(0x7108388, true)) {
        mScriptUI = new ("UI/cScenarioEditModeScriptUI", 0, 0, 0, 0) EditModeScriptUI();
        if (!mScriptUI.p->Init())
            mScriptUI = 0;
    }

    w = mLayout.p->FindWindowByID(0x272eb68e, true);
    if (w) {
        mPanelC = new ("UI", 0, 0, 0, 0) PanelC();
        mPanelC.p->Setup(w);
    }

    if (!mGlobalOptions.p)
        mGlobalOptions = new ("Simulator/cSPUIGlobalOptions", 0, 0, 0, 0) GlobalOptions();

    mPosse = new (4, "UI/Posse", GetUIAllocator()) Posse();
    if (mPosse.p->Load(gPosseKey)) {
        cString title(0xefdb68ec, 0x760b242, 0);
        Posse* po = mPosse.p;
        po->SetCaption(title.GetText());
        mPosse.p->SetPos(0.0f, 250.0f, 0, 0);
        mPosse.p->SetVisible(0);
        mPosse.p->F00e21950(1);
    } else {
        mPosse = 0;
    }

    w = WindowManager()->GetInner()->FindWindowByID(0x774b060, true);
    if (w)
        w->AddWinProc(&mProc);

    void* h = &mHandler;
    mAutoHandler.mpServer = MessageServer();
    mAutoHandler.mpHandler = h;
    mAutoHandler.mpIds = gMsgIds;
    mAutoHandler.mnIds = 1;
    mAutoHandler.mField = 0;
    if (mAutoHandler.mpServer && h)
        mAutoHandler.mpServer->RegisterHandler(h, 0x30c11c7);

    if (mLayout.p)
        mLayout.p->SetVisibility(false);
    mFlag94 = false;
    F00ed5890(-1);
    mCurrentIndex = -1;
    return true;
}
