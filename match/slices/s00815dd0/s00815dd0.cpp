// Slice s00815dd0 (batch w2g7 #4), 32-bit MSVC 2008.
//   UTFWin::cSPUIMaterialEffect  : 00816790 (helper), 008167d0, ctor 00816860, dtor 00816910
//   UI::CalloutMessageBox        : 00816990, 00816a20, 00816b20, 00816b90, 00816ca0, ctor 00816cb0
//   cSPUIMainWin::Init           : 00815dd0
//
// Relocations (callees, globals, vtables) are masked by the checker, so the
// external identities only need the right calling convention / arity.

#include <intrin.h>
typedef unsigned int      u32;
typedef unsigned short    u16;
typedef unsigned char     u8;
typedef unsigned __int64  u64;

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
extern "C" void  cSPUITooltipManager_Init();
extern "C" void  sInitDropShadowQuality();
extern "C" void  FUN_00956d90();
extern "C" void  FUN_0096ef80();
extern "C" void  UTFWin_RegisterUIBehaviors();
extern "C" void  FUN_0082f760();
extern "C" void* Alloc(u32 size, const char* name, int, int, int, int);
extern "C" void  FUN_0067cba0(void*);
extern "C" void  FUN_0067cbb0(void*);
extern "C" void  FUN_0067cbd0(void*);
extern "C" void  FUN_00957f40(void*);
extern "C" void* SP_WindowManager();
extern "C" void* SP_MessageServer();
extern "C" void* SP_CheatManager();
extern "C" void* GetManager();
extern "C" int   FUN_0067cab0();
extern "C" void  FUN_00815310(void*, void*);
struct Helper815310 { void Fn(void* arg); };
extern "C" void  FUN_008085d0(void*, void*, int, int, void*);
extern "C" void  UI_WindowManager_ctor(void*);
extern "C" void  UI_LayerManager_ctor(void*);
extern "C" void  UI_TooltipManager_ctor(void*);
extern "C" void  UI_SerializationService_ctor(void*);
extern "C" void  cSPUIDebugConsole_ctor(void*);
extern "C" void  cSPUIStringBinder_ctor(void*);
extern "C" void  cSPUILayout_ctor(void*);
extern "C" void  cSPUILayout_Init(void*, u32, int, int, const wchar_t*);
extern "C" void  cSPUILayout_SetVisibility(void*, int);
extern "C" void* cSPUILayout_FindWindowByID(void*, u32, int);
extern "C" void  cSPUILayout_Shutdown(void*, int);
extern "C" void  SPUIHelpers_SetWindowSPMaterial(void*, void*, u8);
extern "C" void  SPUIHelpers_EndModal(void*, void*, int);
extern "C" void  SPUIHelpers_BeginModal(void*, void*, int);
extern "C" void  SPUIHelpers_AnchorWindowToWindow(void*, void*, int, int);
extern "C" void  SPUIHelpers_UpdateMouseFocus(int);
extern "C" int   SP_GetPropertyAsText(int id, int owner, void* out);
extern "C" const wchar_t* cString_GetText(void*);
extern "C" void  cString_ctor(void*);
extern "C" void  cString_dtor(void*);
extern "C" int   FUN_005ff1c0(void*);
extern "C" void  cString_SetColorLocalized(int);
extern "C" void  cSPUILayerManager_Init(void*);
extern "C" void  cSPUIImageAtlasMap_Init();
extern "C" void  cSPUIPropertyEditor_Init(void*);
extern "C" void  cSPUIDebugConsole_Init(void*);
extern "C" void  FUN_00802a20(void*, int);
extern "C" void  FUN_00802a30(void*, int);
extern "C" void  FUN_00835610(void*);
extern "C" void  FUN_00833790(void*);
extern "C" void  FUN_00998df0(void*, void*);
extern "C" void  FUN_00997b60(void*);
extern "C" void  FUN_0098b700(void*);
extern "C" void  FUN_00811f20(void*);
extern "C" void  FUN_008178b0(void*, int);
extern "C" void  FUN_00817a40(void*);
extern "C" void  UI_PropertyEditor_ctor(void*);
extern "C" void  UI_cConnectionDialog_ctor(void*);
extern "C" void  EA_Stopwatch_ctor(void*, int);
extern "C" void  EA_LimitStopwatch_SetTimeLimit(void*, int, int);
extern "C" void  FUN_008129c0();
extern "C" void  FUN_00813760_p();
extern "C" void  FUN_008137f0_p();
extern "C" void  InitFonts_p();
extern "C" void  UpdateMouseScale_p();
extern "C" void  InitTitleScreen_p();
extern "C" int   CmdLineHasSwitch();
extern "C" void  FactoryRegister();

// ---------------------------------------------------------------------------
// raw vtable-call helpers
// ---------------------------------------------------------------------------
static inline void* Vcp1(void* p, int off, void* a) {
    return ((void*(__thiscall*)(void*, void*))(*(void***)p)[off / 4])(p, a);
}
static inline void* Vcp0(void* p, int off) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void  Vv0(void* p, int off) {
    ((void(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline void  Vv1(void* p, int off, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline void  Vv2(void* p, int off, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[off / 4])(p, a, b);
}
static inline int   Vi0(void* p, int off) {
    return ((int(__thiscall*)(void*))(*(void***)p)[off / 4])(p);
}
static inline int   Vi1(void* p, int off, int a) {
    return ((int(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}
static inline char  Vb1(void* p, int off, int a) {
    return ((char(__thiscall*)(void*, int))(*(void***)p)[off / 4])(p, a);
}

// ===========================================================================
// UTFWin::cSPUIMaterialEffect
// ===========================================================================
struct IObj;

struct MaterialTarget {
    char pad_00[0x58];
    u32  mat;      // +0x58
    char pad_5c[0x80 - 0x5c];
    u32* tex;      // +0x80
    u8   flag;     // +0x84
};

// @ 0x00816790
extern "C" void FUN_00816790(IObj* p) {
    if (!p) return;
    MaterialTarget* o = (MaterialTarget*)Vcp1(p, 0x0c, (void*)0x2f009dd0);
    if (o && o->mat && o->tex)
        SPUIHelpers_SetWindowSPMaterial((void*)o->mat, (void*)*o->tex, o->flag);
}

struct MatEffect {
    char  pad_00[0x60];
    u32   f60, f64, f68, f6c;   // +0x60
    u32   f70, f74, f78, f7c;   // +0x70
    u32*  p80;                  // +0x80
    u8    b84;                  // +0x84
    char  pad_85[3];
    float f88;                  // +0x88

    void  sub8167d0(IObj* p, float f);
    void  ctor816860();
    void  dtor816910();
};

// @ 0x008167d0
void MatEffect::sub8167d0(IObj* p, float f) {
    if (f > 0.5f) {
        if (f88 <= 0.5f) p80 = &f70;
    } else if (f < 0.5f) {
        if (f88 >= 0.5f) p80 = &f60;
    } else {
        return;
    }
    void* x = Vcp0(p, 0x14);
    int   y = Vi1(this, 0x0c, 0xee3f516e);
    Vv2(x, 0x1c, 0x816790, y);
    f88 = f;
}

// @ 0x00816860
void MatEffect::ctor816860() {
    ((void(__thiscall*)(void*))0x963db0)(this);   // FadeEffect base ctor
    *(void**)((char*)this + 0x00) = (void*)0x1418d00;
    *(void**)((char*)this + 0x04) = (void*)0x1418ce4;
    *(void**)((char*)this + 0x0c) = (void*)0x1418ca8;
    f60 = f64 = 0x1667bac;
    f68 = 0x1667bae;
    f70 = f74 = 0x1667bac;
    f78 = 0x1667bae;
    p80 = 0;
    b84 = 0;
    f88 = 0.5f;
}

// @ 0x00816910
void MatEffect::dtor816910() {
    *(void**)((char*)this + 0x00) = (void*)0x1418d00;
    *(void**)((char*)this + 0x04) = (void*)0x1418ce4;
    *(void**)((char*)this + 0x0c) = (void*)0x1418ca8;
    if (((int)((f78 - f70) & 0xfffffffe)) > 2 && f70)
        ((void(__cdecl*)(void*))0xf47380)((void*)f70);
    if (((int)((f68 - f60) & 0xfffffffe)) > 2 && f60)
        ((void(__cdecl*)(void*))0xf47380)((void*)f60);
    ((void(__thiscall*)(void*))0x980420)(this);
}

// ===========================================================================
// UI::CalloutMessageBox
// ===========================================================================
struct cSPUILayout {
    char pad_00[0x0c];
    void* FindWindowByID(u32 id, int arg);     // 0x8105b0
    void  Init(u32 a, int b, int c, const wchar_t* s); // 0x812160
    void  Shutdown(int arg);                   // 0x811ad0
};

struct CalloutMessageBox {
    char        pad_00[0x0c];
    cSPUILayout layout;    // +0x0c
    char        pad_18[0x24 - 0x18];
    int         mEnterBtn; // +0x24
    int         mEscBtn;   // +0x28
    u8          b2c;       // +0x2c
    int         mResult;   // +0x30
    u8          b34;       // +0x34
    char        pad_35[0x38 - 0x35];
    char        stopwatch[0x20]; // +0x38
    void*       mpCallback;      // +0x58
    u8          b5c;             // +0x5c
    char        pad_5d[0x60 - 0x5d];
    u32         f60, f64, f68, f6c;
    u8          b70;

    bool  sub816990();
    void  sub816a20(int, int, int, int);
    void  sub816b20(int id, int owner);
    int   sub816b90(int id, void* msg);
    void* sub816ca0();
    void  ctor816cb0(int cb);
};

// @ 0x00816990
bool CalloutMessageBox::sub816990() {
    void* win = layout.FindWindowByID(0x6318e78, 1);
    if (win) {
        void* wm = SP_WindowManager();
        if (Vb1(wm, 0x80, (int)win)) {
            Vv2(win, 0x7c, 1, 0);
            SPUIHelpers_EndModal(win, (void*)mResult, 0);
        }
        wm = SP_WindowManager();
        int eax = Vi0(wm, 0x04);
        void* ecx = eax ? (void*)(eax - 4) : 0;
        ((Helper815310*)ecx)->Fn(this);
    }
    layout.Shutdown(0);
    SPUIHelpers_UpdateMouseFocus(1);
    return true;
}

// @ 0x00816a20
void CalloutMessageBox::sub816a20(int, int, int, int) {
    layout.FindWindowByID(0x6318e78, 1);
    mResult = 0x1510d07;
    void* win = layout.FindWindowByID(0x6318e78, 1);
    void* wm = SP_WindowManager();
    if (win) {
        void* lm = ((void*(__cdecl*)(int))0x805070)(0x5b598f7);
        void* world = ((void*(__thiscall*)(void*))0x810620)(lm);
        if (b5c && Vi0(win, 0x10) == 0)
            Vv1(world, 0xd8, (int)win);
        Vv2(win, 0x7c, 1, 1);
        if (b5c) {
            int a = Vi0(wm, 0x04);
            SPUIHelpers_AnchorWindowToWindow((void*)a, win, 0x300, 0);
        }
        if (!Vi1(wm, 0x80, (int)win))
            SPUIHelpers_BeginModal(win, mpCallback, 0);
    }
}

// @ 0x00816b20
void CalloutMessageBox::sub816b20(int id, int owner) {
    char str[0x14];
    cString_ctor(str);
    if (SP_GetPropertyAsText(id, owner, str)) {
        void* win = layout.FindWindowByID(id, 1);
        if (win) {
            Vv2(win, 0x7c, 1, 1);
            const wchar_t* txt = cString_GetText(str);
            Vv1(win, 0x80, (int)txt);
        }
    }
    cString_dtor(str);
}

// @ 0x00816b90
int CalloutMessageBox::sub816b90(int id, void* msg) {
    u32* m = (u32*)msg;
    u32 t = m[2];
    if (t == 1) {
        if (m[5] & 0x47) return 1;
        if (m[4] == 0xd) {
            if (b2c) {
                mResult = -15;
            } else {
                if (mEnterBtn == -1) goto checkEsc;
                mResult = mEnterBtn + 0x5107b17;
            }
            sub816990();
        }
    checkEsc:
        if (m[4] != 0x1b) return 1;
        if (b2c) {
            mResult = -15;
            sub816990();
            return 1;
        }
        if (mEscBtn == -1) return 1;
        mResult = mEscBtn + 0x5107b17;
        sub816990();
        return 1;
    }
    if (t == 0xc) {
        if (b34 && FUN_005ff1c0(&stopwatch[0]) &&
            id == (int)layout.FindWindowByID(0x6318e78, 1)) {
            mResult = 0x1511161;
            sub816990();
        }
        return 0;
    }
    if (t != 0x287259f6) return 0;
    {
        int r = Vi0(*(void**)m, 0x1c);
        if ((u32)r < 0x5107b17 || ((u32)r > 0x5107b1a && r != -15)) {
            mResult = 0x1510d08;
            sub816990();
            return 1;
        }
        mResult = r;
        sub816990();
        return 1;
    }
}

// @ 0x00816ca0
void* CalloutMessageBox::sub816ca0() {
    return layout.FindWindowByID(0x6318e78, 0);
}

// @ 0x00816cb0
void CalloutMessageBox::ctor816cb0(int cb) {
    *(void**)((char*)this + 0x00) = (void*)0x1418dd4;
    *(void**)((char*)this + 0x04) = (void*)0x1418dc4;
    cSPUILayout_ctor(&layout);
    mEnterBtn = -1;
    mEscBtn = -1;
    b2c = 0;
    mResult = 0x1510d07;
    b34 = 0;
    EA_Stopwatch_ctor(stopwatch, 4);
    EA_LimitStopwatch_SetTimeLimit(stopwatch, 0, 0);
    mpCallback = (void*)cb;
    b5c = 1;
    f60 = f64 = f68 = f6c = 0;
    b70 = 0;
}

// ===========================================================================
// cSPUIMainWin::Init
// ===========================================================================

// Opaque heap objects. Every method here is a __thiscall member at the address in its name.
struct RawObj {
    void* Fn958cf0();            // 0x00958cf0 WindowMgr ctor (size 0x838)
    void* Fn80edb0();            // 0x0080edb0 LayerManager ctor (0x98)
    void* Fn8352d0();            // 0x008352d0 TooltipManager ctor (0x30)
    void* Fn999520();            // 0x00999520 SerializationService ctor (0x34)
    void* Fn833790();            // 0x00833790 (0xc)
    void* Fn8320d0();            // 0x008320d0 cSPUIDebugConsole ctor (0x214)
    void* Fn997b60();            // 0x00997b60 (0x20)
    void* Fn998df0(void* wm);    // 0x00998df0 (0x98)
    void  Fn811f20();            // 0x00811f20 cSPUILayoutManager ctor (0x44)
    void* Fn8025e0();            // 0x008025e0 cSPUICursorManager ctor (0x5c)
    void* Fn81e2b0();            // 0x0081e2b0 PropertyEditor ctor (0x14)
    void* Fn803020();            // 0x00803020 cSPUIStringBinder ctor (0x50)
    void* Fn810000();            // 0x00810000 cConnectionDialog ctor (0x18)
    void* Fn817a40();            // 0x00817a40 (0x88)
    void  Fn83c800();            // 0x0083c800 ArgScript command base ctor
    void  Fn83a9f0(int);         // 0x0083a9f0 cArgumentSpec ctor
    void  Fn80f530();            // 0x0080f530 LayerManager::Init
    void  Fn835610();            // 0x00835610 TooltipManager::LoadProps
    void  Fn802160();            // 0x00802160 cursor AddStandardCursors
    void  Fn823a00();            // 0x00823a00 PropertyEditor::Init
    void  Fn802cd0();            // 0x00802cd0 console Init
    void  Fn802a20(int);         // 0x00802a20
    void  Fn802a30(int);         // 0x00802a30 console Show
    void  Fn812160(const wchar_t*, u32, int, u32); // 0x00812160 cSPUILayout::Init
    void  Fn810590(int);         // 0x00810590 SetVisibility
    void* Fn8105b0(u32, int);    // 0x008105b0 FindWindowByID
    void  Fn8178b0(int);         // 0x008178b0
    void  Fn8115a0();            // 0x008115a0 cSPUILayoutManager::InitMessaging
    int   Fn92b300(const wchar_t*, int, int, int); // 0x0092b300 EA::CommandLine::FindSwitch
};
extern "C" void* FUN_00f473a0(unsigned int, const char*, int, int, int, int);  // operator new (heap)
extern "C" void* FUN_00926020(unsigned int, const char*, int, int, int, int);  // ZoneObject::operator new

extern "C" void  FUN_00813b20();       // cSPUITooltipManager::Init
extern "C" void  FUN_00813120();
extern "C" void  FUN_00956d90();
extern "C" void  FUN_0096ef80();
extern "C" void  FUN_008005f0();       // UTFWin::RegisterUIBehaviors
extern "C" void  FUN_0082f760();
extern "C" void  FUN_00957f40(void*);
extern "C" void  FUN_0067cba0(void*);
extern "C" void  FUN_0067cbd0(void*);
extern "C" void  FUN_0067cbb0(void*);
extern "C" void* FUN_0067dd50();
extern "C" void* FUN_006895b0();
extern "C" void* FUN_0067dcc0();       // SP::MessageServer
extern "C" void* FUN_0067dcd0();       // GetManager
extern "C" void* FUN_0067de20();       // SP::CheatManager
extern "C" void* FUN_0067de40();
extern "C" void* FUN_0067dce0();
extern "C" void* FUN_0067caa0();       // SP::WindowManager
extern "C" int   FUN_0067cab0();
extern "C" void* FUN_0080fee0();
extern "C" char  FUN_0080ff20();
extern "C" void  FUN_0080a700();       // cSPUIImageAtlasMap::Init
extern "C" void  FUN_008129c0();       // RegisterLayoutCheat
extern "C" void  FUN_007f4850();
extern "C" bool  FUN_006ab760(const void* str, const wchar_t* lit);
extern "C" void  FUN_00989650(void (*)());
extern "C" void  FUN_008085d0(void*, void*, int, int, void*);
extern "C" void  FUN_006b5030(int);
extern "C" void  FUN_00813c60();
extern "C" void  FUN_00812c90();
extern "C" void  FUN_00812d00();
extern "C" void  FUN_0083bcd0(void* spec, ...);
extern u32 g_01545188, g_01545198, g_0154519c;
extern RawObj* g_015fd920;               // command-line object
extern float g_015451e8, g_015451ec;     // mouse scale
extern u8 g_0164d211;                    // zh-cn flag

struct cSPUIMainWin {
    char  pad_00[4];
    u32   sub4_vt;
    char  pad_08[0x214 - 8];
    u32   listener;       // +0x214 (message-listener subobject)
    bool  mInitialized;   // +0x218
    char  pad_219[3];
    u8    flags21c;       // +0x21c
    char  pad_21d[0x260 - 0x21d];
    void* mpWindowMgr;    // +0x260
    void* mpSerial;       // +0x264
    char  pad_268[0x270 - 0x268];
    void* mpLayer;        // +0x270
    void* mpTooltip;      // +0x274
    char  pad_278[0x27c - 0x278];
    void* mpMsgBox;       // +0x27c
    void* mpStringMgr;    // +0x280
    char  pad_284[0x2a4 - 0x284];
    void* mpCursor;       // +0x2a4
    char  pad_2a8[0x2d0 - 0x2a8];
    void* mpPropEditor;   // +0x2d0
    bool  mPropEditorInit;// +0x2d4
    char  pad_2d5[3];
    void* mpDebugConsole; // +0x2d8

    bool Init();
    void InitFonts();             // 0x00815ce0
    void InitHitMaskFactory();    // 0x00813760
    void InitStringFactories();   // 0x008137f0
    void UpdateMouseScale();      // 0x008131b0
    void InitTitleScreen();       // 0x00813980
};

static inline void Vv3(void* p, int off, int a, int b, int c) {
    ((void(__thiscall*)(void*, int, int, int))(*(void***)p)[off / 4])(p, a, b, c);
}
static __forceinline void AssignRef(void** slot, void* nv, int addIdx, int relIdx) {
    void* old = *slot;
    if (nv != old) {
        if (nv) Vv0(nv, addIdx);
        *slot = nv;
        if (old) Vv0(old, relIdx);
    }
}

// helper: operator new + out-of-line ctor, null-checked like the original
#define NEWOBJ(var, size, name, ctorcall) \
    do { void* _m = FUN_00f473a0(size, name, 0, 0, 0, 0); var = _m ? ((RawObj*)_m)->ctorcall : 0; } while (0)

// @ 0x00815dd0
bool cSPUIMainWin::Init() {
    if (mInitialized) return true;
    mInitialized = true;

    FUN_00813b20();
    FUN_00813120();
    FUN_00956d90();
    FUN_0096ef80();
    FUN_008005f0();
    InitFonts();
    InitHitMaskFactory();
    InitStringFactories();
    FUN_0082f760();

    NEWOBJ(mpWindowMgr, 0x838, "UI/WindowManager", Fn958cf0());
    {
        void* disp = FUN_0067dd50();
        struct R8 { int a[8]; };
        R8 rect = *(R8*)Vcp0(disp, 0x1c);
        ((void(__thiscall*)(void*, float, float))(*(void***)mpWindowMgr)[0x0c / 4])
            (mpWindowMgr, (float)rect.a[2], (float)rect.a[1]);
    }
    Vv0(mpWindowMgr, 0x24);
    ((void(__thiscall*)(void*, int))(*(void***)&sub4_vt)[0x50 / 4])(&sub4_vt, -0x10);
    Vv2(mpWindowMgr, 0x08, (int)&sub4_vt, 1);
    UpdateMouseScale();
    if (g_015451e8 < 0.001) g_015451e8 = 1.0f;
    if (g_015451ec < 0.001) g_015451ec = 1.0f;
    FUN_00957f40(mpWindowMgr);
    FUN_0067cba0(mpWindowMgr);

    NEWOBJ(mpLayer, 0x98, "UI/LayerManager", Fn80edb0());
    Vv0(mpLayer, 0x00);
    ((RawObj*)mpLayer)->Fn80f530();
    FUN_0067cbd0(mpLayer);

    {
        void* tm;
        NEWOBJ(tm, 0x30, "UI/TooltipManager", Fn8352d0());
        AssignRef(&mpTooltip, tm, 4, 8);
    }
    ((RawObj*)mpTooltip)->Fn835610();

    NEWOBJ(mpSerial, 0x34, "UI/SerializationService", Fn999520());
    {
        void* o;
        NEWOBJ(o, 0x0c, "", Fn833790());
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        void* o;
        NEWOBJ(o, 0x214, "", Fn8320d0());
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        void* o;
        NEWOBJ(o, 0x20, "", Fn997b60());
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        // inline-constructed two-base ref-counted service: vptrs at +0 and +4, count at +8
        u32* o = (u32*)FUN_00f473a0(0x0c, "", 0, 0, 0, 0);
        if (o) {
            ((volatile u32*)o)[1] = 0x13ef094;
            ((volatile u32*)o)[2] = 0;
            ((volatile u32*)o)[0] = 0x14188c4;
            ((volatile u32*)o)[1] = 0x14188c0;
        }
        Vv1(mpSerial, 0x04, (int)o);
    }
    {
        void* o = FUN_00f473a0(0x98, "", 0, 0, 0, 0);
        if (o) o = ((RawObj*)o)->Fn998df0(mpWindowMgr);
        Vv1(mpSerial, 0x04, (int)o);
    }

    void* ms = FUN_0067dcc0();
    void* lst = &listener;
    Vv2(ms, 0x20, (int)lst, 0xf62def);
    Vv2(ms, 0x20, (int)lst, 0x1ee1001);
    Vv2(ms, 0x20, (int)lst, 0x1ee1003);
    Vv2(ms, 0x20, (int)lst, 0x1ee100d);
    Vv2(ms, 0x20, (int)lst, 0x1ee1006);
    Vv2(ms, 0x20, (int)lst, 0x1ee1007);
    Vv2(ms, 0x20, (int)lst, 0x1ee1010);
    Vv2(ms, 0x20, (int)lst, 0x1ee1011);
    Vv2(ms, 0x20, (int)lst, 0x1ee1008);
    Vv2(ms, 0x20, (int)lst, 0x1ee1002);
    Vv2(ms, 0x20, (int)lst, 0x546bbb8);
    Vv2(ms, 0x20, (int)lst, 0x61205e6);
    Vv2(FUN_006895b0(), 0x20, (int)&g_01545188, 1);
    Vv2(ms, 0x20, (int)lst, (int)g_01545188);

    {
        void* lm = FUN_00f473a0(0x44, "", 0, 0, 0, 0);
        if (lm) ((RawObj*)lm)->Fn811f20();
    }
    Vv0(FUN_0080fee0(), 0x08);
    ((RawObj*)FUN_0080fee0())->Fn8115a0();
    FUN_008129c0();

    {
        // UI/SPUILayoutResourceFactory: inline ctor (vptr, atomic-zero refcount, final vptr)
        u32* res = (u32*)FUN_00926020(8, "UI/SPUILayoutResourceFactory", 0, 0, 0, 0);
        if (res) {
            ((volatile u32*)res)[0] = 0x13effa8;
            _InterlockedExchange((volatile long*)&res[1], 0);
            ((volatile u32*)res)[0] = 0x14186c4;
        }
        Vv3(FUN_0067dcd0(), 0x44, 1, (int)res, 0);
    }
    if (FUN_0080ff20()) FUN_0080a700();

    {
        void* cur = 0;
        void* m = FUN_00926020(0x5c, "UI/WindowManager", 0, 0, 0, 0);
        if (m) cur = ((RawObj*)m)->Fn8025e0();
        AssignRef(&mpCursor, cur, 4, 8);
        FUN_0067cbb0(mpCursor);
        void* mgr = FUN_0067dcd0();
        char ok = ((char(__thiscall*)(void*, int, int, int))(*(void***)mgr)[0x44 / 4])(mgr, 1, FUN_0067cab0(), 0);
        ((RawObj*)mpCursor)->Fn802160();
        if (ok) {
            void* c = mpCursor;
            Vv1(mpWindowMgr, 0x38, c ? (int)((char*)c + 8) : 0);
        }
    }
    ((void(__thiscall*)(void*, int))(*(void***)&sub4_vt)[0x78 / 4])(&sub4_vt, 0x1002);

    if (!mPropEditorInit) {
        mPropEditorInit = true;
        void* pe;
        NEWOBJ(pe, 0x14, "UI/PropertyEditor", Fn81e2b0());
        AssignRef(&mpPropEditor, pe, 8, 12);
        ((RawObj*)mpPropEditor)->Fn823a00();
    }

    {
        void* sb;
        NEWOBJ(sb, 0x50, "", Fn803020());
        AssignRef(&mpDebugConsole, sb, 0, 4);
        ((RawObj*)mpDebugConsole)->Fn802cd0();
        ((RawObj*)mpDebugConsole)->Fn802a20(0xc350);
        ((RawObj*)mpDebugConsole)->Fn802a30(0);
        Vv1(FUN_0067de20(), 0x30, (int)mpDebugConsole);
    }

    // ArgScript cheat commands (command object = base + vptr + cArgumentSpec at +0x10)
    {
        char* c = (char*)FUN_00f473a0(0xd8, "App", 0, 0, 0, 0);
        if (c) {
            ((RawObj*)c)->Fn83c800();
            *(volatile u32*)c = 0x1418abc;
            ((RawObj*)(c + 0x10))->Fn83a9f0(1);
            FUN_0083bcd0(c + 0x10, "Show pause screen", "<bool>", &g_01545198, "show or hide", 0);
        }
    }
    FUN_0067de20();
    {
        char* c = (char*)FUN_00f473a0(0xd8, "App", 0, 0, 0, 0);
        if (c) {
            ((RawObj*)c)->Fn83c800();
            ((RawObj*)(c + 0x10))->Fn83a9f0(1);
            *(volatile u32*)c = 0x14189e4;
            FUN_0083bcd0(c + 0x10, "toggles UI for image capture", 0);
        }
        Vv3(FUN_0067de20(), 0x18, (int)g_0154519c, (int)c, 0);
    }
    {
        char* c = (char*)FUN_00f473a0(0xdc, "App", 0, 0, 0, 0);
        if (c) {
            ((RawObj*)c)->Fn83c800();
            ((RawObj*)(c + 0x10))->Fn83a9f0(1);
            *(volatile u32*)c = 0x1418a80;
            FUN_0083bcd0(c + 0x10, "Enable localized text colorize", "<bool>", c + 0xd8, "enable or disable", 0);
        }
    }
    FUN_0067de20();

    if (g_015fd920 && g_015fd920->Fn92b300(L"colorLocalized", 0, 0, 0) != -1) {
        void* wmn = FUN_0067caa0();
        if (wmn) {
            Vv1(wmn, 0x90, 1);
            FUN_006b5030(1);
        }
    }

    if (flags21c & 1) {
        InitTitleScreen();
        Vv2(ms, 0x20, (int)lst, 0x366b9aa);
    }

    {
        void* cd;
        NEWOBJ(cd, 0x18, "", Fn810000());
        AssignRef(&mpMsgBox, cd, 4, 8);
        ((RawObj*)mpMsgBox)->Fn812160(L"GlobalUIPause", 0x40464100, 1, 0xa01a43c8);
        ((RawObj*)mpMsgBox)->Fn810590(0);
        void* w = ((RawObj*)mpMsgBox)->Fn8105b0(0x3868d60, 1);
        FUN_008085d0(w, (void*)FUN_00812d00, 1, 0, this);
    }
    FUN_007f4850();
    g_0164d211 = FUN_006ab760(Vcp0(FUN_0067de40(), 0x14), L"zh-cn");
    FUN_00989650(FUN_00813c60);
    Vv3(FUN_0067dce0(), 0x2c, 7, (int)FUN_00812c90, 0);

    if (flags21c & 2) {
        void* st;
        NEWOBJ(st, 0x88, "", Fn817a40());
        AssignRef(&mpStringMgr, st, 0, 4);
        ((RawObj*)mpStringMgr)->Fn8178b0(0);
    }
    return true;
}
