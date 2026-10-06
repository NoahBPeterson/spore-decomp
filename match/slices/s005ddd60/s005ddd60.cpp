#include "types.h"

// Slice s005ddd60: SP::cSPEditorUI (init / update / shutdown / dialog helpers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
// Retail layout differs from the 2008 PDB: three cSPUILayout members at +0x14/+0x2c/+0x44.

struct Widget;
struct Widget {
    virtual void v0();
    virtual void Release();
    virtual void v2();
    virtual Widget* GetChild(unsigned id);
    virtual Widget* GetParent();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual int GetFlags();
    virtual void v9();
    virtual void SetState(int, int);
    virtual void v11();
    virtual unsigned GetColor();
    virtual float* GetArea();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void SetLayoutId(unsigned id);
    virtual void v21();
    virtual void v22();
    virtual void SetColor(unsigned c);
    virtual void SetArea(const float* r);
    virtual void SetSize(float w, float h);
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void SetFlag(int flag, int on);
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void Refresh();
    virtual void Notify();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void Slot42(int, int);
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void RemoveChild(Widget* w);
    virtual void v56();
    virtual void v57();
    virtual void AddChild(Widget* w);
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void AddWinProc(void* p);
    virtual void RemoveWinProc(void* p);
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual void v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void GridSetItem(int, int, void* v);
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual void v110();
    virtual void v111();
    virtual void GridSetData(int, int, void* v);
};

struct Key { unsigned inst, type, group; };

struct Layout {
    Widget* FindWindowByID(int id, int recurse);       // 0x008105b0
    bool Init(const Key* key, int a, unsigned id);     // 0x008120d0
    bool Init(const wchar_t* name, unsigned group, int a, unsigned id); // 0x00812160
    void SetParentWin(Widget* w, int a, unsigned id);  // 0x008121b0
    void SetVisibility(int v);                         // 0x00810590
    void Shutdown(int a);                              // 0x00811ad0
    void Ctor();                                       // 0x00810000
    char pad[0x18];
};

template <class T> struct Ref { T* p; Ref& Set(T* v); };   // 0x00b5f950 (AutoRefCount::operator=)

// Small refcounted window-proc helpers allocated by Init (16 bytes).
struct IBase { virtual void a(); };
struct RCBase { virtual void rcv(); int rc; RCBase() : rc(0) {} };
struct BlockerBase : IBase, RCBase { Widget* app; };
struct BlockerA : BlockerBase { virtual void a(); virtual void rcv(); BlockerA() {} };
struct BlockerB : BlockerBase { virtual void a(); virtual void rcv(); BlockerB() { app = 0; } };
void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0

struct TooltipProc { void Ctor(); };                 // 0x00835cc0
void* AllocTooltip(int size, const char* name, int a, void* pool);   // 0x009512d0 (cdecl)
void* GetTooltipPool();                                // 0x009512c0
Widget* CreateWindowFor(Widget* parent);               // 0x00806370 (cdecl)
void SetWindowAlpha(Widget* w, float a);               // 0x00804fc0 (cdecl)
struct WMgr { virtual void v0(); virtual Widget* GetRoot(); };
WMgr* WindowManager();                                 // 0x0067caa0
struct LayoutMgr { Widget* GetWorldMainWindow(); };    // 0x00810620
LayoutMgr* __stdcall GetLayoutManager(unsigned id);    // 0x00805070
struct CursorMgr { void SetLocalCursor(); };           // 0x00801bb0
CursorMgr* __stdcall GetCursorManager(int id);         // 0x0067cab0
Widget* InterfaceCast(Widget* w);                      // 0x005dc6a0 (cdecl)
void* MakeGridCell(void* item, int a, int b, int c);   // 0x004bb510 (cdecl)
unsigned ColorRGBAToU32(const float* c);               // 0x004580c0 (cdecl)

struct TerrainTool { void Brush5a2200(float v); void Brush5a2240(float v); };   // 0x005a2200 / 0x005a2240
struct AppMode {
    void NewModel(int);
    TerrainTool* FUN_00574590();
    bool IsAvailable();                // 0x00b1e4d0
    char pad[0x31c];
    int mMode;                         // +0x31c
    char pad2[0x14];
    void** mItemsBegin;                // +0x334
    void** mItemsEnd;                  // +0x338
};
struct WinCtl { void Release(); void FUN_005fe650(); };

extern unsigned g_basicButtonIds[18];  // 0x01519a60
extern char* g_ptr15fd918;             // 0x015fd918 (struct whose +0x3c holds a state block)

extern char vtblA_13f92dc[], vtblA_13f92c0[], vtblA_13f92b0[], vtblA_13f92a0[];
extern char vtblB_14426a0[], vtblB_13eb384[], vtblB_13ec458[], vtblC_13f925c[];

struct EditorUI {
    void* vt0; void* vt4; void* vt8; void* vtc; int f10;
    Layout mLayout;      // +0x14
    Layout mCamera;      // +0x2c
    Layout mPalette;     // +0x44
    AppMode* mApp;       // +0x5c
    Widget* f60;
    Widget* mBudget;     // +0x64
    Widget* mComplexity; // +0x68
    Widget* mHighlight;  // +0x6c
    Widget* mCapture;    // +0x70
    Widget* mGrid;       // +0x74
    Ref<Widget> mClick;  // +0x78
    Ref<BlockerBase> mClickProc;   // +0x7c
    Widget* f80;
    Widget* f84;
    Ref<TooltipProc> mTooltip;     // +0x88
    Ref<Widget> mBlock;            // +0x8c
    Ref<BlockerBase> mBlockProc;   // +0x90
    int f94;
    int mFade;           // +0x98
    int f9c;
    char fa0, fa1, fa2, fa3;
    int fa4, fa8, fac, fb0;
    void* fb4; EditorUI* fb8; int fbc, fc0, fc4, fc8, fcc;
    char fd0, fd1, fd2, fd3;
    int fd4, fd8, fdc, fe0;
    char fe4, fe5, fe6, fe7;
    WinCtl* mfe8;        // +0xe8
    char fec, fed, fee, fef;
    int ff0; char ff4, ff5, ff6, ff7;
    int ff8, ffc;
    char f100, f101, f102, f103, f104, f105, f106, f107;
    int f108; char f10c, f10d, f10e, f10f;
    int f110; char f114, f115, f116, f117;
    int f118, f11c, f120, f124, f128;

    void SetMode(int);
    void FUN_005de9e0();
    EditorUI* Construct();
    bool Init(AppMode* app, int a2, unsigned a3, int a4);
    void Update(int dt);
    void EnableBasicEditorButtons(int a, char b);
    bool Shutdown();
    void StopListeningToMessages();
    void StartListeningToMessages();
    void UpdateUIBasedOnModelSaveability();
    void UpdateSaveButtons();
    void FUN_005dc970(int a);
    void FUN_005dd090(int a);
    void FUN_005dd390();
    void FUN_005dc5a0(unsigned a);
    Widget* FUN_005dc310(unsigned id);
    void SetSelected(unsigned id, int a, int b);
};

static __forceinline Widget* FindWindow(EditorUI* p, unsigned id)
{
    Widget* w = p->mLayout.FindWindowByID(id, 1);
    if (!w)
        w = p->mCamera.FindWindowByID(id, 1);
    return w;
}

static __forceinline void ReleaseRef(Widget** pp)
{
    Widget* o = *pp;
    if (o) {
        *pp = 0;
        ((WinCtl*)o)->Release();
    }
}

// @ 0x005de9e0
// Complete; 101 bytes off: cl keeps `this` in edi and w in esi (original reuses esi for
// both, leaving edi for the child widget).  Behaviour identical.
void EditorUI::FUN_005de9e0()
{
    SetMode(0);
    mApp->NewModel(0);
    Widget* w = FindWindow(this, 0xf019c2e7);
    if (w) {
        Widget* p = w->GetChild(0x8ed27e7a);
        p->SetState(4, 1);
        p->SetState(0x20, 1);
        w->Notify();
    }
}

// @ 0x005ddd60
bool EditorUI::Init(AppMode* app, int a2, unsigned a3, int a4)
{
    mApp = app;
    if (!app)
        return false;
    fa0 = (char)a4;
    if (a2) {
        Key key; key.inst = a2; key.type = 0x510a95b; key.group = a3;
        if (!mLayout.Init(&key, 1, 0x5b598fa))
            return false;
    }
    if (!mCamera.Init(L"EditorSharedUI", a3, 1, 0x5b598fa))
        return false;
    mPalette.Init(L"CameraControls", a3, 1, 0x5b598fa);

    Widget* a = mLayout.FindWindowByID(-1, 1);
    Widget* b = mCamera.FindWindowByID(-1, 1);
    if (a) {
        a->AddWinProc((char*)this + 4);
        a->SetFlag(1, 0);
        if (mHighlight)
            mHighlight->SetFlag(1, 0);
        mBudget = FindWindow(this, 0x5100b176);
        mComplexity = FindWindow(this, 0xf006f308);
        mHighlight = FindWindow(this, 0xf006f309);
        if (mHighlight)
            mHighlight->SetFlag(1, 0);
        if (mComplexity)
            mComplexity->SetFlag(1, 1);
        f80 = FindWindow(this, 0x908891a7);
        f84 = FindWindow(this, 0xf383c97d);

        WindowManager();
        Widget* world = GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
        mClick.Set(CreateWindowFor(world));
        mClick.p->SetFlag(0x40, 1);
        mClick.p->SetFlag(2, 1);
        SetWindowAlpha(mClick.p, 0.0f);
        mClick.p->SetFlag(1, 0);
        mClick.p->SetFlag(0x10, 0);
        float* area = a->GetArea();
        float r[4];
        r[0] = area[0]; r[1] = area[1]; r[2] = area[2]; r[3] = area[3];
        mClick.p->SetArea(r);
        mClick.p->SetSize((r[2] - r[0]) * 0.5f, (r[3] - r[1]) * 0.5f);
        mClick.p->SetLayoutId(0x52dac0d);
        mClick.p->GetParent()->AddChild(mClick.p);

        mClickProc.Set(new ("Editor", 0, 0, 0, 0) BlockerA);
        mClickProc.p->app = (Widget*)mApp;
        mClick.p->AddWinProc(mClickProc.p);

        ReleaseRef((Widget**)&mBlock);
        ReleaseRef((Widget**)&mBlockProc);
        mBlock.Set(CreateWindowFor(world));
        mBlock.p->SetFlag(2, 1);
        mBlock.p->SetFlag(1, 0);
        mBlockProc.Set(new ("Editor", 0, 0, 0, 0) BlockerB);
        mBlockProc.p->app = (Widget*)mApp;
        mBlock.p->AddWinProc(mBlockProc.p);

        FUN_005dc5a0(0x58a3350);
        Widget* tip = FindWindow(this, 0x612efea);
        if (tip) {
            void* mem = AllocTooltip(0x68, "UI/Tooltip", 4, GetTooltipPool());
            TooltipProc* tp = 0;
            if (mem) {
                tp = (TooltipProc*)mem;
                tp->Ctor();
            }
            mTooltip.Set(tp);
            tip->AddWinProc(mTooltip.p);
        }
    }
    if (b) {
        b->AddWinProc((char*)this + 4);
        b->SetFlag(1, 1);
        mCapture = FindWindow(this, 0xd0353720);
        if (mCapture) {
            Widget* g = FUN_005dc310(0x503517b0);
            if (g)
                mGrid = InterfaceCast(g);
            int n = (int)(mApp->mItemsEnd - mApp->mItemsBegin);
            if (n == 1) {
                mCapture->SetFlag(n, 0);
            } else {
                mCapture->SetFlag(1, 1);
                for (int i = 0; i < n; ++i) {
                    void* item = mApp->mItemsBegin[i];
                    mGrid->GridSetItem(0, i, MakeGridCell(item, 0, 1, 0));
                    mGrid->GridSetData(0, i, mApp->mItemsBegin[i]);
                }
                mGrid->Slot42(0, 0);
            }
        }
    }
    Widget* bw = FindWindow(this, 0x1140129d);
    if (bw)
        bw->SetFlag(1, mApp->IsAvailable());
    GetCursorManager(0x1002)->SetLocalCursor();
    if (*(int*)(*(char**)(g_ptr15fd918 + 0x3c) + 0x118) != 0) {
        Widget* w1 = FindWindow(this, 0x4766ff0);
        w1->SetFlag(1, 1);
        Widget* w2 = FindWindow(this, 0x47bc9d0);
        w2->SetFlag(1, 1);
    }
    Widget* pp = mLayout.FindWindowByID(0x4fcc580, 1);
    if (pp) {
        mPalette.SetParentWin(pp, 1, 0x5b598fa);
        mPalette.SetVisibility(1);
    } else {
        mPalette.SetVisibility(0);
    }
    SetSelected(0xf019c2e7, 1, 1);
    WindowManager()->GetRoot()->AddWinProc((char*)this + 4);
    FUN_005dd090(1);
    StartListeningToMessages();
    return a4 != 0;
}

// @ 0x005de450
void EditorUI::Update(int dt)
{
    int t = mFade - dt;
    int zero = 0;
    const int* pick = &t;
    if (t <= 0)
        pick = &zero;
    mFade = *pick;
    Widget* w = FindWindow(this, 0x3088953b);
    if (w) {
        unsigned c = w->GetColor();
        float f[4];
        f[3] = (float)mFade * 0.00014285714f;
        f[0] = (float)((c >> 16) & 0xff) * 0.003921569f;
        f[1] = (float)((c >> 8) & 0xff) * 0.003921569f;
        f[2] = (float)(c & 0xff) * 0.003921569f;
        w->SetColor(ColorRGBAToU32(f));
        w->Refresh();
    }
    Widget* p;
    p = mPalette.FindWindowByID(0x4cab570, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2200(-0.015f);
    }
    p = mPalette.FindWindowByID(0x4cab571, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2200(0.015f);
    }
    p = mPalette.FindWindowByID(0x4cab56f, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2240(-0.02f);
    }
    p = mPalette.FindWindowByID(0x4cab56e, 1);
    if (p && (p->GetChild(0x8ed27e7a)->GetFlags() & 2)) {
        TerrainTool* tt = mApp->FUN_00574590();
        if (tt) tt->Brush5a2240(0.02f);
    }
    if (f10c) {
        FUN_005dd390();
        f10c = 0;
    }
}

static __forceinline void SetButton(Widget* w, int on, char c)
{
    w->SetFlag(2, on);
    w->SetFlag(0x10, c == 0);
    w->Notify();
}

// @ 0x005de690
void EditorUI::EnableBasicEditorButtons(int a, char b)
{
    char c = (char)a;
    fd1 = c;
    const unsigned* ids = g_basicButtonIds;
    do {
        Widget* w = FindWindow(this, *ids);
        if (w)
            SetButton(w, a, c);
        ++ids;
    } while ((int)ids < (int)(g_basicButtonIds + 18));
    if (b) {
        Widget* w = FindWindow(this, 0x70218642);
        if (w && mApp->mMode != 2)
            SetButton(w, a, c);
        w = FindWindow(this, 0xf019c2f3);
        if (w && mApp->mMode != 1)
            SetButton(w, a, c);
        w = FindWindow(this, 0xf019c2e7);
        if (w && mApp->mMode != 0)
            SetButton(w, a, c);
    }
    UpdateUIBasedOnModelSaveability();
    UpdateSaveButtons();
    FUN_005dc970(a);
}

static __forceinline void DetachPair(Widget** pOwner, Widget** pProc)
{
    Widget* owner = *pOwner;
    if (owner) {
        if (*pProc) {
            owner->RemoveWinProc(*pProc);
            ReleaseRef(pProc);
        }
        if (owner->GetParent())
            owner->GetParent()->RemoveChild(*pOwner);
        ReleaseRef(pOwner);
    }
}

// @ 0x005de870
bool EditorUI::Shutdown()
{
    if (mfe8) {
        mfe8->FUN_005fe650();
        if (mfe8) {
            WinCtl* o = mfe8;
            mfe8 = 0;
            o->Release();
        }
    }
    WindowManager();
    Widget* world = GetLayoutManager(0x5b598fa)->GetWorldMainWindow();
    FUN_005dd090(1);
    world->RemoveWinProc((char*)this + 4);
    StopListeningToMessages();
    mLayout.Shutdown(1);
    mCamera.Shutdown(1);
    mPalette.Shutdown(1);
    DetachPair((Widget**)&mBlock, (Widget**)&mBlockProc);
    DetachPair((Widget**)&mClick, (Widget**)&mClickProc);
    return true;
}

// @ 0x005dea60
EditorUI* EditorUI::Construct()
{
    vt4 = vtblB_14426a0;
    vt8 = vtblB_13eb384;
    vtc = vtblB_13ec458;
    f10 = 0;
    vt0 = vtblA_13f92dc;
    vt4 = vtblA_13f92c0;
    vt8 = vtblA_13f92b0;
    vtc = vtblA_13f92a0;
    mLayout.Ctor();
    mCamera.Ctor();
    mPalette.Ctor();
    mApp = 0; f60 = 0; mBudget = 0; mComplexity = 0; mHighlight = 0; mCapture = 0; mGrid = 0;
    mClick.p = 0; mClickProc.p = 0; f80 = 0; f84 = 0; mTooltip.p = 0; mBlock.p = 0; mBlockProc.p = 0;
    mFade = 0; f9c = 0;
    fa0 = 0; fa2 = 0; fa3 = (char)0xff; fa1 = 1;
    fa8 = 0; fac = 0; fb0 = 0;
    fb4 = vtblC_13f925c;
    fbc = 0; fc0 = 0; fc4 = 0; fcc = 0;
    fd0 = 1; fd1 = 1;
    fd8 = 0; fdc = 0; fe0 = 0; fd4 = 0;
    fe4 = 0; fe5 = 0; mfe8 = 0; fec = 0; ff0 = 0; ff4 = 0; ff8 = 0; ffc = 0;
    f100 = 0; f101 = 0; f102 = 0; f103 = 1; f104 = 0; f105 = 0; f106 = 1;
    f108 = 0; f10c = 0; f110 = 0; f114 = 0; f118 = 0; f11c = 0; f120 = 0; f124 = 0; f128 = 0;
    fb8 = this;
    return this;
}
