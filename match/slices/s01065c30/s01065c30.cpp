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
    virtual void w28(); virtual void w29(); virtual void w30();
    virtual int SetShown(int a, int b);      // +0x7c
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
void* GetSetting9(void* x);                              // 0x00401090
void* FUN_004df550(void* x);                             // 0x004df550
char  FUN_00c30910(void* emp);                           // 0x00c30910
void* FUN_00c70e00(void* planet);                        // 0x00c70e00
void* operator_new(int size, const char* file, int line, int a, const char* file2, int line2);  // 0x00f473a0
void* FUN_008014a0();                                    // 0x008014a0
void* FUN_008014b0();                                    // 0x008014b0
void* FUN_00e012d0(uint id, float v);                    // 0x00e012d0
void* FUN_00e50750(void* a, void* b, void* c);           // 0x00e50750
void* GetMainWindowArea(void* out);                      // 0x00805ea0
void* FUN_00c372c0(void* inv);                           // 0x00c372c0
void* FUN_00c37300(void* inv);                           // 0x00c37300
void  EA_SetNumberString(int lo, int hi, void* buf, int n);  // 0x00881ae0
void  FUN_00834a00(int a);                               // 0x00834a00
void  FUN_00834c60(int a);                               // 0x00834c60
void  FUN_01046fc0(int a);                               // 0x01046fc0
bool  FUN_010449e0(int a);                               // 0x010449e0
void  SetWindowImage(void* win, void* data, int a);      // 0x00807bb0
char  CalloutMessageBox(void* self, void* key);          // 0x00809db0
void  SPUIHelpers_SetTooltipText(void* win, void* text); // 0x00806de0
void* cString_ctor(void* s, int a, int b, int c);        // 0x006b5770
void* cString_GetText(void* s, int a, int b);            // 0x006b55c0
void  cString_dtor(void* s);                             // 0x006b5240
bool  Layout_Init(void* l, const wchar_t* name, int a, int b, int c);  // 0x00812160
void  Layout_Shutdown(void* l, int a);                   // 0x00811ad0
void  Layout_SetVisibility(void* l, int v);              // 0x00810590
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
extern void* g_149c178;              // 0x0149c178 (id array)
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
};
struct GlobalUI {
    Win* FindWindowByID(uint id);   // 0x00e012b0
};
void SPUISpace::ShowCameraControls(int param) {
    static const uint ids[8] = {0x4cab570,0x4cab571,0x4cab56e,0x4cab56f,
                                0x5cab570,0x5cab571,0x5cab56e,0x5cab56f};
    for (int i = 0; i < 8; ++i)
        ((GlobalUI*)mGlobalUI)->FindWindowByID(ids[i])->SetShown(1, param);
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
struct ConfigMgr { virtual void* v0(); virtual void* Lookup(uint id); };
void T5d20::f() {
    if (((ConfigMgr*)ConfigManager())->Lookup(0x4ea96cb) == 0) { mState = 8; return; }
    switch (mState) {
    case 0: mState = 1; FUN_0067cac0(0x43c18587); FUN_0067c830(0x43c18587); return;
    case 1: mState = 2; FUN_0067cac0(0x1930f01e); FUN_0067c830(0x1930f01e); return;
    case 2: mState = 3; return;
    case 3: mState = 4; return;
    case 4: mState = 5; FUN_0067cac0(0xf98be0b8); FUN_0067c830(0xf98be0b8); return;
    case 5: mState = 6; return;
    case 6: mState = 7; FUN_0067cac0(0xe43f6bbd); FUN_0067c830(0xe43f6bbd); return;
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
    FUN_0067cac0(0x43c18587); FUN_0067c8c0(0x43c18587, 1);
    FUN_0067cac0(0x1930f01e); FUN_0067c8c0(0x1930f01e, 1);
    FUN_0067cac0(0xf98be0b8); FUN_0067c8c0(0xf98be0b8, 1);
    FUN_0067cac0(0xe43f6bbd); FUN_0067c8c0(0xe43f6bbd, 1);
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
void FUN_01065f00(void* self, int* out) {
    (void)self;
    int t = (int)FUN_00b8dab0(self);
    if (t != 2 && t != 4) {
        if (t != 5) { out[0]=0; out[1]=0; out[2]=0; return; }
        void* av = FUN_00b8de30(self);
        (void)av;
        int emp = (int)FUN_00ba9370(StarManager(), 0);
        if (!FUN_00c30910((void*)emp) && (int)GetPlayerEmpire() != emp) {
            out[0] = (int)g_15b9420;
            out[1] = (int)g_15b9424;
            out[2] = (int)g_15b9428;
            return;
        }
    }
    {
        void* p = GetSetting9(FUN_00b8e090(self));
        int prof = (int)FUN_004df550(p);
        if (prof) {
            out[0] = *(int*)(prof + 0x504);
            out[1] = 0x2f7d0004;
            out[2] = *(int*)(prof + 0x50c);
            return;
        }
    }
    out[0] = 0; out[1] = 0; out[2] = 0;
}

// ===========================================================================
// @ 0x01065fe0  SP::cSPUISpace::UpdateGlobal
// ===========================================================================
void SPUISpace::UpdateGlobal() {
    void* inv = GetPlayerInventoryOf(GetUFOSimulator());
    float f = *(float*)((char*)inv + 0x540);
    // FUN_00e012d0(0x1c404ac, f / inventory->v58())
    FUN_00e012d0(0x1c404ac, f);
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
void FUN_01066180(void* p) {
    void* s = ((Winc*)p)->v4();
    (void)s;
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
void FUN_01066230(void* self, char param) {
    Win* w = ((GlobalUI*)(*(void**)((char*)self + 0x224)))->FindWindowByID(0x5d646c8);
    bool flag = false;
    void* planet = (void*)GetActivePlanet();
    if (planet) {
        int k = (int)FUN_00c70e00(planet);
        bool b1;
        int ctx = GetUniverseContext();
        if (ctx == 2) b1 = true;
        else {
            b1 = false;
            if (ctx == 1) {
                void* inv = GetPlayerInventoryOf(GetUFOSimulator());
                if (*(char*)((char*)inv + 0x74c) == 0) b1 = true;
            }
        }
        if (k >= 2 && !b1 && param != 0) flag = true;
    }
    w->SetShown(2, flag);
}

// ===========================================================================
// @ 0x01066310
// ===========================================================================
void __stdcall FUN_01066310(int* src) {
    void* p = operator_new(0x18, "Simulator", 0, 0, "EASTL/allocator.h", 0xd1);
    int* d = (int*)p;
    if (d) { d[0]=src[0]; d[1]=src[1]; d[2]=src[2]; d[3]=src[3]; d[4]=src[4]; }
    d[5] = 0;
}

// ===========================================================================
// @ 0x01066390
// ===========================================================================
float FUN_01066390(float* p, float s) {
    (void)p; (void)s;
    return 0.0f;
}

// ===========================================================================
// @ 0x01066480  SP::cCommandDeleteCargoButtonState::OnState1
// ===========================================================================
struct CmdDeleteCargo {
    char pad0[8];
    void* pItem;        // +8
    int   windowID;     // +0xc
    void* pSpace;       // +0x10
    int   state;        // +0x18
    bool OnState1();
};
bool CmdDeleteCargo::OnState1() {
    void* w = ((GlobalUI*)(*(void**)((char*)pSpace + 0x224)))->FindWindowByID((uint)windowID);
    void* pc = w ? FUN_01077b40(w) : 0;
    if (pc != pItem) {
        if (pc) ((V4*)pc)->AddRef();
        pItem = pc;
        if (pItem) ((V4*)pItem)->Release();
    }
    if (pItem) {
        if (CalloutMessageBox(this, (void*)0x15b9268)) {
            state = 1;
            return state == 2;
        }
        state = 2;
        return true;
    }
    state = 2;
    return true;
}

// ===========================================================================
// @ 0x01066520
// ===========================================================================
void FUN_01066520(void* self) {
    if (*(void**)((char*)self + 8) && *(int*)((char*)self + 0xc) == 0x5107b1a) {
        void* o = *(void**)(*(int*)((char*)self + 0x14) + 0x238);
        ((Winc*)o)->v78(*(uint*)((char*)self + 8));
    }
    Win* w = ((GlobalUI*)(*(void**)(*(int*)((char*)self + 0x14) + 0x224)))->FindWindowByID(0xb2001000);
    if (w) w->SetShown(1, 0);
}

// ===========================================================================
// @ 0x01066570
// ===========================================================================
bool FUN_01066570(void* self) {
    for (;;) {
        int st = *(int*)((char*)self + 0x18);
        if (st == 0) {
            if (!((CmdDeleteCargo*)self)->OnState1()) return true;
        } else if (st == 1) {
            if (*(int*)((char*)self + 0xc) == 0x1510d07) return true;
            *(int*)((char*)self + 0x18) = 2;
        } else if (st == 2) {
            FUN_01066520(self);
            return false;
        } else {
            return true;
        }
    }
}

// ===========================================================================
// @ 0x010665c0
// ===========================================================================
struct CmdCtor {
    void init(int a, int b);
};
void CmdCtor::init(int a, int b) {
    *(int*)((char*)this + 0) = 0x149c1f0;
    *(int*)((char*)this + 8) = 0;
    *(int*)((char*)this + 0x14) = a;
    *(int*)((char*)this + 0x10) = b;
    *(int*)((char*)this + 0xc) = 0x1510d07;
    *(int*)((char*)this + 0x18) = 0;
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
    if (g) return *(void**)((char*)g + 0x14);
    return 0;
}

// ===========================================================================
// @ 0x010666b0
// ===========================================================================
void FUN_010666b0(void* self) {
    for (uint i = 0; i < 6; ++i) {
        Win* w = ((GlobalUI*)(*(void**)((char*)self + 0x224)))->FindWindowByID(((uint*)&g_149c178)[i]);
        Win* q = w ? (Win*)((Winc*)w)->v3(0x8ed27e7a) : 0;
        FUN_01046fc0(i);
        bool b = FUN_010449e0(i);
        ((Winc*)q)->v10();
        (void)b;
    }
}

// ===========================================================================
// @ 0x01066720
// ===========================================================================
void FUN_01066720(int* key) {
    int local[3];
    local[0] = key[0];
    local[2] = key[2];
    local[1] = 0x2f7d0004;
    void* g = SpaceGameGet();
    (void)g; (void)local;
}

// ===========================================================================
// @ 0x01066780
// ===========================================================================
bool FUN_01066780(void* self, int a, int* ev) {
    if (*(int*)((char*)self + 0x258) == 0) return true;
    if (ev[2] == 0x1b) {
        if (ev[3] != 1) return true;
        int id = (int)((Winc*)ev[6])->v3(0);   // placeholder
        (void)id;
    }
    return true;
}

// ===========================================================================
// @ 0x01066880
// ===========================================================================
void* FUN_01066880(void* self) {
    FUN_008014a0();
    *(int*)((char*)self) = 0x149c230;
    *(int*)((char*)self + 8) = 0;
    *(int*)((char*)self + 0xc) = 0;
    void* p = operator_new(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
    void* win = p ? p : 0;
    *(void**)((char*)self + 0xc) = win;
    if (!Layout_Init(win, L"RolloverSpaceCityButton", 0x40464100, 1, (int)0xe9f70df9)) {
        Layout_Shutdown(win, 1);
        *(void**)((char*)self + 0xc) = 0;
        return self;
    }
    Layout_SetVisibility(win, 0);
    return self;
}

// ===========================================================================
// @ 0x010669a0
// ===========================================================================
void FUN_010669a0(void* self) {
    *(int*)((char*)self) = 0x149c230;
    void* w = *(void**)((char*)self + 0xc);
    if (w) {
        Win* c = ((Layout*)w)->FindWindow(0x37ab944, 1);
        if (c) { void* g = SpaceGameGet(); ((Winc*)c)->v3(*(uint*)((char*)g + 0x14)); }
        Layout_Shutdown(w, 1);
        *(void**)((char*)self + 0xc) = 0;
    }
    FUN_008014b0();
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
    if (mWin) Layout_SetVisibility(mWin, 0);
}
