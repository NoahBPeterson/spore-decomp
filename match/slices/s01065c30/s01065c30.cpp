// Slice s01065c30: SP::cSPUISpace UI helpers + cCommandDeleteCargoButtonState + misc.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

// --- vtable wrappers
struct Win {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void w28(); virtual void w29();
    virtual int v78(uint id);                // +0x78
    virtual int SetShown(int a, int b);      // +0x7c
    virtual void SetText(const char* s);     // +0x80
};

// IWindow sub-object used only through its +0x28 slot (two integer args).
struct Win28 {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9();
    virtual void call28(int a, int b);       // +0x28
};

// Objects returned by 0x01077b40 / cSPUILayout use AddRef at +4, Release at +8.
struct IRefCounted {
    virtual void dtor();                     // +0x00
    virtual void AddRef();                   // +0x04
    virtual void Release();                  // +0x08
};
struct Winc {
    virtual void w0(); virtual void w1(); virtual void w2();
    virtual void* v3(uint id);               // +0xc
    virtual void* v4();                      // +0x10
    virtual void v5(int);                    // +0x14
    virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void v10();                      // +0x28
    virtual void w11();
    virtual void* v12();                     // +0x38
    virtual void* v13();                     // +0x3c
    virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17();
    virtual void w18(); virtual void w19(); virtual void w20(); virtual void w21();
    virtual void w22(); virtual void w23(); virtual void w24(); virtual void w25();
    virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29();
    virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33();
    virtual void w34(); virtual void w35(); virtual void w36(); virtual void w37();
    virtual void w38(); virtual void w39(); virtual void w40(); virtual void w41();
    virtual void w42(); virtual void w43(); virtual void w44(); virtual void w45();
    virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49();
    virtual void w50(); virtual void w51(); virtual void w52(); virtual void w53();
    virtual void w54(); virtual void w55(); virtual void w56(); virtual void w57();
    virtual void w58(); virtual void w59(); virtual void w60(); virtual void w61();
    virtual void w62(); virtual void w63(); virtual void w64(); virtual void w65();
    virtual void w66(); virtual void w67(); virtual void w68(); virtual void w69();
    virtual void w70(); virtual void w71(); virtual void w72(); virtual void w73();
    virtual void w74(); virtual void w75(); virtual void w76(); virtual void w77();
    virtual void* v78(uint id);              // +0x104  (approx index 65)
};

struct Layout {
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3();
    virtual void l4(); virtual void l5(); virtual void l6(); virtual void l7();
    virtual void l8(); virtual void l9();
    virtual Win* FindWindow(uint id, int a);  // +0x28 approx
};

// --- callees
void* ConfigManager();                                   // 0x0067dd30
void* SpaceGameGet();                                    // 0x01002bd0
void* GetUFOSimulator();                                 // 0x00ffbe50
void* App();                                             // 0x0067dd10
void* GameTimeManager(uint id);                          // 0x00b3d380
void* StarManager();                                     // 0x00b3d2a0
void* NounManager();                                     // 0x00b3d300
void* GetPlayerEmpire();                                 // 0x01021300
int   GetUniverseContext();                              // 0x01021080
int   GetActivePlanet();                                 // 0x01021260
void* GetPlayerInventoryOf(void* sim);                   // 0x00a1ad60
void* FUN_0067cac0(uint id);                             // 0x0067cac0
void  FUN_0067c830(uint id);                             // 0x0067c830
void  FUN_0067c8c0(uint id, int a);                      // 0x0067c8c0
void* FUN_01077b40(void* w);                             // 0x01077b40
void* FUN_00b8dab0(void* o);                             // 0x00b8dab0
void* FUN_00b8de30(void* o);                             // 0x00b8de30
void* FUN_00b8e090(void* o);                             // 0x00b8e090
void* __stdcall GetSetting9(void* x);                    // 0x00401090
void* FUN_004df550(void* x);                             // 0x004df550
char  FUN_00c30910(void* emp);                           // 0x00c30910
void* FUN_00c70e00(void* planet);                        // 0x00c70e00
void* operator_new(int size, const char* file, int line, int a, const char* file2, int line2);  // 0x00f473a0
void* FUN_008014a0();                                    // 0x008014a0
void* FUN_008014b0();                                    // 0x008014b0
void* FUN_00e012d0(uint id, float v);                    // 0x00e012d0
void* FUN_00e50750(void* a, void* b, void* c);           // 0x00e50750
void* GetMainWindowArea(void* out);                      // 0x00805ea0
char __fastcall FUN_00c372c0(void* inv);                 // 0x00c372c0
char __fastcall FUN_00c37300(void* inv);                 // 0x00c37300
void  EA_SetNumberString(int lo, int hi, void* buf, int n);  // 0x00881ae0
void  FUN_00834a00(int a);                               // 0x00834a00
void  FUN_00834c60(int a);                               // 0x00834c60
void* FUN_01046fc0();                                    // 0x01046fc0
bool  FUN_010449e0(int a);                               // 0x010449e0
// Member-shaped wrappers for thiscall callees.
struct cPlanet {
    int   GetKind();          // 0x00b8dab0
    void* Project();          // 0x00b8de30
    void* GetSpeciesKey();    // 0x00b8e090
    int   GetToolMode();      // 0x00c70e00
};
struct cSpaceGame {
    void* GetAvatar();        // 0x00b1fdb0
};
struct StarMgr {
    void* GetEmpireByID(uint id); // 0x00ba9370
};
struct cEmpire {
    char IsScannable();       // 0x00c30910
};
struct SpeciesMgr {
    void* GetProfile();       // 0x004df550
};
struct SimSpaceGame {
    void* GetPlayerInventory(); // 0x00a1ad60
};
struct cSpaceGameObj {
    char pad0[0x14];
    void* pSpace;               // +0x14
};
struct cPropView {
    bool Test(int i);         // 0x010449e0
};
struct Inv508 {
    virtual void i0();  virtual void i1();  virtual void i2();  virtual void i3();
    virtual void i4();  virtual void i5();  virtual void i6();  virtual void i7();
    virtual void i8();  virtual void i9();  virtual void i10(); virtual void i11();
    virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
    virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
    virtual void i20(); virtual void i21();
    virtual float Get();      // +0x58
};
void  SetWindowImage(void* win, void* data, int a);      // 0x00807bb0
char  CalloutMessageBox(void* self, void* key);          // 0x00809db0
void  SPUIHelpers_SetTooltipText(void* win, void* text); // 0x00806de0
void* cString_ctor(void* s, int a, int b, int c);        // 0x006b5770
void* cString_GetText(void* s, int a, int b);            // 0x006b55c0
void  cString_dtor(void* s);                             // 0x006b5240
bool  Layout_Init(void* l, const wchar_t* name, int a, int b, int c);  // 0x00812160
void  Layout_Shutdown(void* l, int a);                   // 0x00811ad0
void  Layout_SetVisibility(void* l, int v);              // 0x00810590
// 0x00810590 is __thiscall: ecx = layout window, one stack arg (ret 4).
struct LayoutWindow {
    void SetVisibility(int v);                           // @ 0x00810590
};
void* FUN_00ba9370(void* mgr, int id);                   // 0x00ba9370

struct V4 { virtual int AddRef(); virtual int Release(); };
struct GMT { virtual void g0(); virtual void g1(); virtual void g2(); virtual void g3();
             virtual void g4(); virtual void g5(); virtual void g6(); virtual void g7();
             virtual void g8();
             virtual void Inc(uint id); virtual void Dec(uint id); };
extern "C" float sqrtf(float);
extern "C" double atan2(double, double);

extern void* g_rand;                 // 0x01601760
extern float g_180;                  // 0x013eb17c
extern float g_15b90e0;              // 0x015b90e0
extern float g_13eb8a0;              // 0x013eb8a0 (0.25)
extern float g_149c1fc;              // 0x0149c1fc (20.0)
extern float g_16e2838;              // 0x016e2838
extern int   g_16e283c;              // 0x016e283c
extern float g_1485378;              // 0x01485378 (0.0)
extern float g_15b9420, g_15b9424, g_15b9428;
extern uint  g_ids149c178[6];        // 0x0149c178
extern void* g_149c1f0;              // vtable ptr for 010665c0

// ===========================================================================
// @ 0x01065c30  SP::cSPUISpace::ShowCameraControls
// ===========================================================================
struct SPUISpace {
    char pad0[0x224];
    Win* mGlobalUI;                 // +0x224
    void ShowCameraControls(int param);
    void ShowToolChargeBar();
    void HideToolChargeBar();
    void ToggleStarmapFilters(int param);
    void UpdateGlobal();
    void FUN_01066230(char param);
    void FUN_010666b0();
};
struct LayoutUI {
    Win* FindWindowByID(uint id, int flag);   // 0x008105b0
};
struct GlobalUI {
    char pad0[8];
    LayoutUI* mLayout;                        // +0x08
    Win* FindWindowByID(uint id);             // 0x00e012b0
    void SetProgress(uint id, float v);       // 0x00e012d0
};
struct AppObj {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual void a20(); virtual void a21();
    virtual void* GetViewer();                // +0x58
};
struct cViewer {
    void GetCameraLocationInfo(void* a, void* b, float* cam, void* c); // 0x007c3d30
};
// Virtual shapes used by FUN_01066180.
struct VtP {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void* v10();                 // +0x10
    virtual void v14(int v);             // +0x14
};
struct VtS {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual float* v38();                // +0x38
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28();
    virtual void v74(float a, float b);  // +0x74
};
struct TextZoomName {
    void Activate(uint v);                    // 0x00834a00
    void Deactivate(uint v);                  // 0x00834c60
};
void SPUISpace::ShowCameraControls(int param) {
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x4cab570)->SetShown(1, param);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x4cab571)->SetShown(1, param);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x4cab56e)->SetShown(1, param);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x4cab56f)->SetShown(1, param);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x5cab570)->SetShown(1, param);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x5cab571)->SetShown(1, param);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x5cab56e)->SetShown(1, param);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x5cab56f)->SetShown(1, param);
}

// ===========================================================================
// @ 0x01065d20
// ===========================================================================
struct T5d20 {
    char pad0[0x618];
    int mState;                     // +0x618
    void f();
    bool isStateSpecial();
    void reset();
};
// ConfigManager lookup is vtable slot +0x30 (the original loads [edx+0x30]).
struct ConfigMgr {
    virtual void* v0(); virtual void* v1(); virtual void* v2(); virtual void* v3();
    virtual void* v4(); virtual void* v5(); virtual void* v6(); virtual void* v7();
    virtual void* v8(); virtual void* v9(); virtual void* v10(); virtual void* v11();
    virtual void* Lookup(uint id);   // +0x30
};
// Manager returned by FUN_0067cac0(id): both calls below are __thiscall.
struct CfgMgr {
    void F_67c830(uint id);          // @ 0x0067c830  (ret 4)
    void Set(uint id, int on);       // @ 0x0067c8c0  (ret 8)
};
void T5d20::f() {
    if (((ConfigMgr*)ConfigManager())->Lookup(0x4ea96cb) == 0) { mState = 8; return; }
    switch (mState) {
    case 0: mState = 1; ((CfgMgr*)FUN_0067cac0(0x43c18587))->F_67c830(0x43c18587); return;
    case 1: mState = 2; ((CfgMgr*)FUN_0067cac0(0x1930f01e))->F_67c830(0x1930f01e); return;
    case 2: mState = 3; return;
    case 3: mState = 4; return;
    case 4: mState = 5; ((CfgMgr*)FUN_0067cac0(0xf98be0b8))->F_67c830(0xf98be0b8); return;
    case 5: mState = 6; return;
    case 6: mState = 7; ((CfgMgr*)FUN_0067cac0(0xe43f6bbd))->F_67c830(0xe43f6bbd); return;
    case 7: break;
    default: return;
    }
    mState = 8;
}

// ===========================================================================
// @ 0x01065e20
// ===========================================================================
bool T5d20::isStateSpecial() {
    int x = mState;
    if (x != 1 && x != 2 && x != 5 && x != 7) return false;
    return true;
}

// ===========================================================================
// @ 0x01065e40
// ===========================================================================
void T5d20::reset() {
    mState = 8;
    ((CfgMgr*)FUN_0067cac0(0x43c18587))->Set(0x43c18587, 1);
    ((CfgMgr*)FUN_0067cac0(0x1930f01e))->Set(0x1930f01e, 1);
    ((CfgMgr*)FUN_0067cac0(0xf98be0b8))->Set(0xf98be0b8, 1);
    ((CfgMgr*)FUN_0067cac0(0xe43f6bbd))->Set(0xe43f6bbd, 1);
}

// ===========================================================================
// @ 0x01065ea0  SP::cSPUISpace::ShowToolChargeBar
// ===========================================================================
void SPUISpace::ShowToolChargeBar() {
    Win* w = ((GlobalUI*)mGlobalUI)->FindWindowByID(0x341ba47);
    if (w) w->SetShown(1, 1);
}

// ===========================================================================
// @ 0x01065ed0  SP::cSPUISpace::HideToolChargeBar
// ===========================================================================
void SPUISpace::HideToolChargeBar() {
    Win* w = ((GlobalUI*)mGlobalUI)->FindWindowByID(0x341ba47);
    if (w) w->SetShown(1, 0);
}

// ===========================================================================
// @ 0x01065f00  SP::cSPUISpace::GetDominantSpeciesThumbnailKey
// ===========================================================================
void FUN_01065f00(uint* out, void* planet) {
    cPlanet* pl = (cPlanet*)planet;
    uint a = 0, b = 0, c = 0;
    int t = pl->GetKind();
    if (t == 2 || t == 4) goto get;
    if (t != 5) goto done;
    {
        void* game = pl->Project();
        void* avatar = ((cSpaceGame*)game)->GetAvatar();
        void* emp = ((StarMgr*)StarManager())->GetEmpireByID((uint)avatar);
        if (!((cEmpire*)emp)->IsScannable() && emp != GetPlayerEmpire()) {
            out[0] = *(uint*)&g_15b9420;
            out[1] = *(uint*)&g_15b9424;
            out[2] = *(uint*)&g_15b9428;
            return;
        }
    }
get:
    {
        void* key = pl->GetSpeciesKey();
        void* setting = GetSetting9(key);
        void* prof = ((SpeciesMgr*)setting)->GetProfile();
        if (prof) {
            a = *(uint*)((char*)prof + 0x504);
            c = *(uint*)((char*)prof + 0x50c);
            b = 0x2f7d0004;
        }
    }
done:
    out[0] = a; out[1] = b; out[2] = c;
}

// ===========================================================================
// @ 0x01065fe0  SP::cSPUISpace::UpdateGlobal
// ===========================================================================
void SPUISpace::UpdateGlobal() {
    void* inv = ((SimSpaceGame*)GetUFOSimulator())->GetPlayerInventory();
    float f = *(float*)((char*)inv + 0x540);
    float div = ((Inv508*)((char*)inv + 0x508))->Get();
    ((GlobalUI*)mGlobalUI)->SetProgress(0x1c404ac, f / div);
    int n = (int)f;
    if ((float)n < f) ++n;
    void* layout = *(void**)((char*)mGlobalUI + 8);
    Win* w = ((LayoutUI*)layout)->FindWindowByID(0x4d039a8, 1);
    if (w) {
        char buf[0x20];
        EA_SetNumberString(n, n >> 31, buf, 0x20);
        w->SetText(buf);
    }
    char b1 = FUN_00c372c0(inv);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x6396b68)->SetShown(2, b1);
    ((GlobalUI*)mGlobalUI)->SetProgress(0x5481520,
        *(float*)((char*)inv + 0x7f4) / *(float*)((char*)inv + 0x7f8));
    char b2 = FUN_00c37300(inv);
    ((GlobalUI*)mGlobalUI)->FindWindowByID(0x6396b78)->SetShown(2, b2);
}

// ===========================================================================
// @ 0x01066120
// ===========================================================================
struct T6120 {
    char pad0[0x224];
    void* mGlobal;
    void* f(uint id);
};
void* T6120::f(uint id) {
    Win* w = ((GlobalUI*)mGlobal)->FindWindowByID(id);
    if (w) return FUN_01077b40(w);
    return 0;
}

// ===========================================================================
// @ 0x01066150
// ===========================================================================
int __stdcall FUN_01066150(int x) {
    if ((uint)(x + 0x50000000) > 0xf) return 0;
    return x + 0x10;
}

// ===========================================================================
// @ 0x01066180
// ===========================================================================
void FUN_01066180(void* p, float f) {
    VtP* vp = (VtP*)p;
    VtS* s = (VtS*)vp->v10();
    s->v74(1.0f, 1.0f);
    vp->v14(0);
    if (f > 0.0f) {
        float* r = s->v38();
        if (f < r[2] - r[0])
            s->v74(f, 1.0f);
    }
    vp->v14(1);
}

// ===========================================================================
// @ 0x01066200  SP::cSPUISpace::ToggleStarmapFilters
// ===========================================================================
void SPUISpace::ToggleStarmapFilters(int param) {
    Win* w = ((GlobalUI*)mGlobalUI)->FindWindowByID(0x2e1ad08);
    if (w) w->SetShown(1, param);
}

// ===========================================================================
// @ 0x01066230
// ===========================================================================
void SPUISpace::FUN_01066230(char param) {
    uint flag = (uint)this;
    ((char*)&flag)[0] = 0;
    Win* w = ((GlobalUI*)mGlobalUI)->FindWindowByID(0x5d646c8);
    void* planet = (void*)GetActivePlanet();
    if (planet) {
        bool k2 = ((cPlanet*)planet)->GetToolMode() > 1;
        bool b1;
        int ctx = GetUniverseContext();
        if (ctx == 2) b1 = true;
        else {
            ctx = GetUniverseContext();
            if (ctx == 1) {
                void* inv = ((SimSpaceGame*)GetUFOSimulator())->GetPlayerInventory();
                b1 = (*(char*)((char*)inv + 0x74c) == 0);
            } else b1 = false;
        }
        if (k2 && !b1 && param == 0) ((char*)&flag)[0] = 1;
    }
    w->SetShown(2, (int)flag);
}

// ===========================================================================
// @ 0x01066310
// ===========================================================================
void __stdcall FUN_01066310(int* src) {
    void* p = operator_new(0x18, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
    int* d = (int*)p;
    if (d) { d[0]=src[0]; d[1]=src[1]; d[2]=src[2]; d[3]=src[3]; d[4]=src[4]; }
    d[5] = 0;
}

// ===========================================================================
// @ 0x01066390
// ===========================================================================
float FUN_01066390(float* p, float s) {
    void* viewer = ((AppObj*)App())->GetViewer();
    float cam[3];
    ((cViewer*)viewer)->GetCameraLocationInfo(0, 0, cam, 0);
    float a[3];
    a[0] = p[0] + cam[0] * s;
    a[1] = p[1] + cam[1] * s;
    a[2] = p[2] + cam[2] * s;
    float x1, y1, x2, y2;
    FUN_00e50750(p, &x1, &y1);
    FUN_00e50750(a, &x2, &y2);
    float dx = x2 - x1;
    float dy = y2 - y1;
    float d = sqrtf(dx * dx + dy * dy);
    float area[4];
    float* r = (float*)GetMainWindowArea(area);
    float lim = r[3] * 0.25f;
    if (d > lim) d = lim;
    return d;
}

// ===========================================================================
// @ 0x01066480  SP::cCommandDeleteCargoButtonState::OnState1
// ===========================================================================
struct CmdDeleteCargo {
    char pad0[8];
    void* pItem;        // +0x08
    int   field0c;      // +0x0c
    uint  windowID;     // +0x10
    void* pSpace;       // +0x14
    int   state;        // +0x18
    bool OnState1();
    bool OnState2();
    bool Run();
};
bool CmdDeleteCargo::OnState1() {
    void* pc = 0;
    void* w = ((GlobalUI*)((SPUISpace*)pSpace)->mGlobalUI)->FindWindowByID(windowID);
    if (w) pc = FUN_01077b40(w);
    void* old = pItem;
    if (pc != old) {
        if (pc) ((IRefCounted*)pc)->AddRef();
        pItem = pc;
        if (old) ((IRefCounted*)old)->Release();
    }
    if (!pItem) { state = 2; return true; }
    if (!CalloutMessageBox(this, (void*)0x15b9268)) { state = 2; return true; }
    state = 1;
    int two = 2;
    return state == two;
}

// ===========================================================================
// @ 0x01066520
// ===========================================================================
bool CmdDeleteCargo::OnState2() {
    if (pItem && field0c == 0x5107b1a) {
        void* o = *(void**)((char*)pSpace + 0x238);
        ((Win*)o)->v78((uint)pItem);
    }
    Win* w = ((GlobalUI*)((SPUISpace*)pSpace)->mGlobalUI)->FindWindowByID(0xb2001000);
    if (w) w->SetShown(1, 0);
    return false;
}

// ===========================================================================
// @ 0x01066570
// ===========================================================================
bool CmdDeleteCargo::Run() {
    char r = 1;
    for (;;) {
        switch (state) {
        case 0:
            r = OnState1();
            break;
        case 1:
            if (field0c == 0x1510d07) return true;
            state = 2;
            break;
        case 2:
            OnState2();
            return false;
        default:
            return true;
        }
        if (r == 0) return true;
    }
}

// ===========================================================================
// @ 0x010665c0
// ===========================================================================
struct CmdCtor {
    void* mVtbl;      // +0x00
    int   m04;        // +0x04
    volatile int   m08;        // +0x08
    volatile int   m0c;        // +0x0c
    volatile int   m10;        // +0x10
    volatile int   m14;        // +0x14
    volatile int   m18;        // +0x18
    CmdCtor* init(int a, int b);
};
CmdCtor* CmdCtor::init(int a, int b) {
    int zero = 0;
    CmdCtor* p = this;
    p->mVtbl = (void*)0x149c1f0;
    p->m08 = zero;
    p->m14 = a;
    p->m10 = b;
    p->m0c = 0x1510d07;
    p->m18 = zero;
    return p;
}

// ===========================================================================
// @ 0x010665f0
// ===========================================================================
void FUN_010665f0() {
    void* m = GameTimeManager(0x4bf38a9);
    ((Winc*)m)->v10();
}

// ===========================================================================
// @ 0x01066610
// ===========================================================================
struct T6610 {
    char pad0[0xc];
    int mField;
    void set(int a, int b);
};
void T6610::set(int a, int b) {
    (void)a;
    (void)GameTimeManager(0x4bf38a9);
    mField = b;
}

// ===========================================================================
// @ 0x01066630
// ===========================================================================
void FUN_01066630(float* p1, float* p2, float* p3) {
    if ((g_16e283c & 1) == 0) {
        g_16e2838 = g_180 / g_15b90e0;
        g_16e283c |= 1;
    }
    *p2 = sqrtf(p1[0]*p1[0] + p1[1]*p1[1]) * g_149c1fc;
    *p3 = (float)(atan2((double)p1[1], (double)p1[0]) + g_15b90e0) * g_16e2838;
}

// ===========================================================================
// @ 0x010666a0
// ===========================================================================
void* FUN_010666a0() {
    void* g = SpaceGameGet();
    if (g) return ((cSpaceGameObj*)g)->pSpace;
    return 0;
}

// ===========================================================================
// @ 0x010666b0
// ===========================================================================
void SPUISpace::FUN_010666b0() {
    for (uint i = 0; i < 6; ++i) {
        Win* w = ((GlobalUI*)mGlobalUI)->FindWindowByID(g_ids149c178[i]);
        Win28* q = w ? (Win28*)((Winc*)w)->v3(0x8ed27e7a) : 0;
        void* o = FUN_01046fc0();
        bool b = ((cPropView*)o)->Test(i);
        q->call28(4, b ? 1 : 0);
    }
}

// ===========================================================================
// @ 0x01066720
// ===========================================================================
void FUN_01066720(int* key) {
    int local[3];
    local[0] = key[0];
    local[1] = 0x2f7d0004;
    local[2] = key[2];
    void* layout = 0;
    void* g = SpaceGameGet();
    if (g) {
        void* sp = ((cSpaceGameObj*)g)->pSpace;
        if (sp) {
            void* globalUI = ((SPUISpace*)sp)->mGlobalUI;
            layout = *(void**)((char*)globalUI + 8);
        }
    }
    Win* w = ((LayoutUI*)layout)->FindWindowByID(0xb0b00000, 1);
    SetWindowImage(w, local, -1);
}

// ===========================================================================
struct InputEvent {
    char pad0[8];
    int  key;       // +0x08
    int  flags;     // +0x0c
    char pad10[8];
    void* obj;      // +0x18
};
struct EvObj {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6();
    virtual int GetId();                     // +0x1c
};
struct SpaceZoom {
    char pad0[0x258];
    void* mp258;                             // +0x258
    char pad25c[0x698 - 0x25c];
    void** mZoomBegin;                       // +0x698
    void** mZoomEnd;                         // +0x69c
    void** mZoomCap;                         // +0x6a0
    bool FUN_01066780(int unused, InputEvent* ev);
};
// @ 0x01066780
bool SpaceZoom::FUN_01066780(int unused, InputEvent* ev) {
    (void)unused;
    if (!mp258) return true;
    if (ev->key == 0x1b) {
        if (ev->flags != 1) return true;
        int id = ((EvObj*)ev->obj)->GetId();
        void* z;
        if (id == 0x7edb1e8) z = mZoomBegin[0];
        else if (id == 0x7edb1e9) z = mZoomBegin[1];
        else if (id == 0x7edb1ea) z = mZoomBegin[2];
        else return true;
        if (!z) return true;
        ((TextZoomName*)z)->Activate(0);
        return true;
    }
    if (ev->key == 0x1c) {
        if (ev->flags != 1) return true;
        int id = ((EvObj*)ev->obj)->GetId();
        void* z;
        if (id == 0x7edb1e8) z = mZoomBegin[0];
        else if (id == 0x7edb1e9) z = mZoomBegin[1];
        else if (id == 0x7edb1ea) z = mZoomBegin[2];
        else return true;
        if (z) ((TextZoomName*)z)->Deactivate(0);
    }
    return true;
}

// ===========================================================================
struct LayoutObj {
    bool Init(const wchar_t* name, int a, int b, int c); // 0x00812160
    void Shutdown(int a);                                // 0x00811ad0
    void SetVisibility(int v);                           // 0x00810590
};
struct LayoutAlloc {
    void* Ctor();                                        // 0x00810000
};
struct cString {
    void* mData;             // +0x00
    int   mSize;             // +0x04
    void Ctor(uint id, int a, int b);                    // 0x006b5770
    void* GetText(int a, int b);                         // 0x006b55c0
    void Dtor();                                         // 0x006b5240
};
struct CmdObjBase {
    virtual void b0(); virtual void b1(); virtual void b2();
    char pad4[4];            // +0x04 .. +0x07
    void BaseCtor();                                     // 0x008014a0
    void BaseDtor();                                     // 0x008014b0
};
struct CmdObj : CmdObjBase {
    void* m08;               // +0x08
    void* mLayout;           // +0x0c
    CmdObj* Ctor();
    void Dtor();
};
// @ 0x01066880
CmdObj* CmdObj::Ctor() {
    BaseCtor();
    *(void**)this = (void*)0x149c230;
    m08 = 0;
    mLayout = 0;
    void* p = operator_new(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
    void* layout = 0;
    if (p) layout = ((LayoutAlloc*)p)->Ctor();
    void* old = mLayout;
    if (layout != old) {
        if (layout) ((IRefCounted*)layout)->AddRef();
        mLayout = layout;
        if (old) ((IRefCounted*)old)->Release();
    }
    if (!((LayoutObj*)mLayout)->Init((const wchar_t*)0x149c200, 0x40464100, 1, (int)0xe9f70df9)) {
        ((LayoutObj*)mLayout)->Shutdown(1);
        if (mLayout) {
            void* o = mLayout;
            mLayout = 0;
            ((IRefCounted*)o)->Release();
        }
        return this;
    }
    Win* w = ((LayoutUI*)mLayout)->FindWindowByID(0x37ab944, 1);
    if (w) {
        void* g = SpaceGameGet();
        void** vt = *(void***)w;
        ((void (__thiscall*)(void*, void*))vt[0x104 / 4])(w, *(void**)((char*)g + 0x14));
        cString s;
        s.Ctor(0xc0152a6d, 0x6565205, 0);
        void* text = s.GetText(-1, 1);
        SPUIHelpers_SetTooltipText(w, text);
        s.Dtor();
    }
    ((LayoutObj*)mLayout)->SetVisibility(0);
    return this;
}

// ===========================================================================
// @ 0x010669a0
void CmdObj::Dtor() {
    *(void**)this = (void*)0x149c230;
    if (mLayout) {
        Win* w = ((LayoutUI*)mLayout)->FindWindowByID(0x37ab944, 1);
        if (w) {
            void* g = SpaceGameGet();
            void** vt = *(void***)w;
            ((void (__thiscall*)(void*, void*))vt[0x108 / 4])(w, *(void**)((char*)g + 0x14));
        }
        ((LayoutObj*)mLayout)->Shutdown(1);
        if (mLayout) {
            void* o = mLayout;
            mLayout = 0;
            ((IRefCounted*)o)->Release();
        }
    }
    if (mLayout) ((IRefCounted*)mLayout)->Release();
    BaseDtor();
}

// ===========================================================================
// @ 0x01066a10
// ===========================================================================
struct T6a10 {
    char pad0[0xc];
    void* mWin;
    void hide();
};
void T6a10::hide() {
    if (mWin) ((LayoutWindow*)mWin)->SetVisibility(0);
}
