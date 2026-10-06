// Slice s00815dd0 (batch w2g7 #4), 32-bit MSVC 2008.
//   UTFWin::cSPUIMaterialEffect  : 00816790 (helper), 008167d0, ctor 00816860, dtor 00816910
//   UI::CalloutMessageBox        : 00816990, 00816a20, 00816b20, 00816b90, 00816ca0, ctor 00816cb0
//   cSPUIMainWin::Init           : 00815dd0
//
// Relocations (callees, globals, vtables) are masked by the checker, so the
// external identities only need the right calling convention / arity.

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
extern "C" void  FUN_00989650(int, int, int);
extern "C" void  FUN_008129c0();
extern "C" void  FUN_0080ff20();
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
// cSPUIMainWin::Init  (large; behavioural transliteration, not byte-exact)
// ===========================================================================
struct cSPUIMainWin {
    char  pad_00[0x218];
    bool  mInitialized;   // +0x218
    u8    flags21c;       // +0x21c
    char  pad_21d[0x260 - 0x21d];
    void* mpHints;        // +0x260
    void* mpStatus;       // +0x264
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
    void* mpDebugConsole; // +0x2d8

    bool Init();
};

// @ 0x00815dd0
bool cSPUIMainWin::Init() {
    if (mInitialized) return true;
    mInitialized = true;

    cSPUITooltipManager_Init();
    sInitDropShadowQuality();
    FUN_00956d90();
    FUN_0096ef80();
    UTFWin_RegisterUIBehaviors();
    InitFonts_p();
    FUN_00813760_p();
    FUN_008137f0_p();
    FUN_0082f760();

    void* wm = Alloc(0x838, "UI/WindowManager", 0, 0, 0, 0);
    if (wm) UI_WindowManager_ctor(wm);
    mpHints = wm;

    Vv2(wm, 0x0c, 0, 0);            // SetSize
    Vv0(wm, 0x24);
    Vv1((void*)this, 0x50, -0x10);
    Vv2(wm, 0x08, (int)this, 1);

    UpdateMouseScale_p();
    if (*(float*)0x15451e8 < 0.001f) *(float*)0x15451e8 = 1.0f;
    if (*(float*)0x15451ec < 0.001f) *(float*)0x15451ec = 1.0f;
    FUN_00957f40(wm);
    FUN_0067cba0(wm);

    void* lm = Alloc(0x98, "UI/LayerManager", 0, 0, 0, 0);
    if (lm) UI_LayerManager_ctor(lm);
    mpLayer = lm;
    Vv0(lm, 0x00);
    cSPUILayerManager_Init(lm);
    FUN_0067cbd0(lm);

    void* tm = Alloc(0x30, "UI/TooltipManager", 0, 0, 0, 0);
    if (tm) { UI_TooltipManager_ctor(tm); Vv0(tm, 0x04); }
    mpTooltip = tm;
    FUN_00835610(mpTooltip);

    void* ss = Alloc(0x34, "UI/SerializationService", 0, 0, 0, 0);
    if (ss) UI_SerializationService_ctor(ss);
    mpStatus = ss;

    Vv1(mpStatus, 0x04, (int)Alloc(0x0c, (const char*)0x13f6b3c, 0, 0, 0, 0));
    if (*(void**)((char*)this + 0x264)) {}
    {
        void* a = Alloc(0x0c, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (a) FUN_00833790(a);
        Vv1(mpStatus, 0x04, (int)a);
    }
    {
        void* a = Alloc(0x214, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (a) cSPUIDebugConsole_ctor(a);
        Vv1(mpStatus, 0x04, (int)a);
    }
    {
        void* a = Alloc(0x20, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (a) FUN_00997b60(a);
        Vv1(mpStatus, 0x04, (int)a);
    }
    {
        void* a = Alloc(0x0c, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (a) FUN_0098b700(a);
        Vv1(mpStatus, 0x04, (int)a);
    }
    {
        void* a = Alloc(0x98, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (a) FUN_00998df0(a, mpHints);
        Vv1(mpStatus, 0x04, (int)a);
    }

    {
        void* ms = SP_MessageServer();
        static const u32 ids[11] = { 0xf62def, 0x1ee1001, 0x1ee1003, 0x1ee100d,
            0x1ee1006, 0x1ee1007, 0x1ee1010, 0x1ee1011, 0x1ee1008,
            0x1ee1002, 0x546bbb8 };
        for (int i = 0; i < 11; i++)
            Vv2(ms, 0x20, ids[i], (int)(this + 0x214));
        Vv2(ms, 0x20, 0x61205e6, (int)(this + 0x214));
    }
    {
        void* q = GetManager();
        Vv1(q, 0x20, 0x1545188);
        Vv2(SP_MessageServer(), 0x20, *(u32*)0x1545188, (int)(this + 0x214));
    }

    {
        void* a = Alloc(0x44, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (a) FUN_00811f20(a);
    }
    FactoryRegister();
    FUN_0080ff20();
    cSPUIImageAtlasMap_Init();

    if (!mPropEditorInit) {
        mPropEditorInit = true;
        void* pe = Alloc(0x14, "UI/PropertyEditor", 0, 0, 0, 0);
        if (pe) UI_PropertyEditor_ctor(pe);
        mpPropEditor = pe;
        cSPUIPropertyEditor_Init(pe);
    }

    void* sb = Alloc(0x50, (const char*)0x13f6b3c, 0, 0, 0, 0);
    if (sb) cSPUIStringBinder_ctor(sb);
    mpDebugConsole = sb;
    cSPUIDebugConsole_Init(sb);
    FUN_00802a20(sb, 0xc350);
    FUN_00802a30(sb, 0);
    Vv1(SP_CheatManager(), 0x30, (int)sb);

    if (CmdLineHasSwitch()) {
        void* wmn = SP_WindowManager();
        if (wmn) {
            Vv1(wmn, 0x90, 1);
            cString_SetColorLocalized(1);
        }
    }

    if (flags21c & 1) {
        InitTitleScreen_p();
        Vv2(SP_MessageServer(), 0x20, 0x366b9aa, (int)(this + 0x214));
    }

    {
        void* cd = Alloc(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (cd) UI_cConnectionDialog_ctor(cd);
        mpMsgBox = cd;
        cSPUILayout_Init(mpMsgBox, 0xa01a43c8, 1, 0x40464100, L"GlobalUIPause");
        cSPUILayout_SetVisibility(mpMsgBox, 0);
        cSPUILayout_FindWindowByID(mpMsgBox, 0x3868d60, 1);
        FUN_008085d0(0, 0, 0, 0, 0);
    }

    FUN_008129c0();
    {
        void* loc = *(void**)0x15fd920 ? (void*)0 : (void*)0;
        (void)loc;
    }
    FUN_00989650(0, 0, 0);
    {
        void* dm = (void*)0;
        Vv1(dm, 0x2c, 7);
    }

    if (flags21c & 2) {
        void* st = Alloc(0x88, (const char*)0x13f6b3c, 0, 0, 0, 0);
        if (st) FUN_00817a40(st);
        mpStringMgr = st;
        FUN_008178b0(st, 0);
    }

    return true;
}
