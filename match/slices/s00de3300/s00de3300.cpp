// Decompiled from SporeApp.exe (gold6 batch, worker 33).
// Slice s00de3300: galaxy game-entry lifecycle, mouse-mode toggles, and the
// anonymous UI helpers (window image get/set, URL open, verb-icon labels).

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef float          f32;

// ---------------------------------------------------------------------------
// vtable call shapes
// ---------------------------------------------------------------------------
typedef void  (__thiscall* FnV)(void*);
typedef u32   (__thiscall* FnU)(void*);
typedef void  (__thiscall* Fn1)(void*, u32);
typedef void  (__thiscall* Fn2)(void*, u32, u32);
typedef void  (__thiscall* Fn3)(void*, u32, u32, u32);
typedef void  (__thiscall* FnP)(void*, void*);
typedef void  (__thiscall* Fn2P)(void*, u32, u32, void**);
typedef void  (__thiscall* FnUP)(void*, u32, void*);
typedef void* (__thiscall* FnPP)(void*);
typedef void* (__thiscall* FnC)(void*, u32);
typedef char  (__thiscall* FnQC)(void*, u32, u32, void**);

// ---------------------------------------------------------------------------
// free functions / runtime helpers
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_00df5f40();               // 0x00df5f40
extern "C" void* __cdecl FUN_0067cab0();               // 0x0067cab0
extern "C" void* __cdecl MessageServer();              // 0x0067dcc0
extern "C" void* __cdecl MovieSystem();                // 0x0067cb10
extern "C" void* __cdecl EA_Audio_GetSystemAT();       // 0x00a206f0
extern "C" void* __cdecl SP_App();                     // 0x0067dd10
extern "C" void* __cdecl SP_AppSystem();               // 0x0067dd00
extern "C" void* __cdecl SP_PropertyManager();         // 0x0067de30
extern "C" void  __cdecl op_del_array(void* p);        // 0x00f47380
extern "C" void  __cdecl KillSetiEffects(u32 id, u32 v);        // 0x00435ed0
extern "C" void* __cdecl FUN_00b3d410();                        // 0x00b3d410
extern "C" void* __cdecl SPUIHelpers_GetImageFromLayout(void* layout, u32 which); // 0x008061c0
extern "C" void  __cdecl FUN_008068d0(void* win, void* img, u32 a); // 0x008068d0
extern "C" char  __cdecl SPUIHelpers_CreateImageFromResource2(void* res, void** out,
                                                              s32 a, s32 b, s32 c); // 0x00806230
extern "C" void  __cdecl SPUIHelpers_GetMainWindowArea(void* area); // 0x00805ea0
extern "C" void  __cdecl FUN_00881720(int a, int b, int c, wchar_t* buf, int d, int e); // 0x00881720
extern "C" void  __cdecl SetDateFromTm(void* tm, void* dt);         // 0x0092e440
extern "C" char  __cdecl SP_GetPropertyAsString16(void* obj, u32 key, void* out); // 0x006a1400

// ---------------------------------------------------------------------------
// small helper objects defined in other translation units
// ---------------------------------------------------------------------------
struct Stopwatch {
    void Ctor(int a, int b);      // 0x0093a560
    void SetUnits(int u);         // 0x0093a1a0
    void Restart();               // 0x00571e80
    u8   mPad[0x18];
};

struct EaString16 {
    u32 mpBegin;                  // +0x00
    u32 mpEnd;                    // +0x04
    u32 mpCap;                    // +0x08
    void Assign(u32 first, u32 last);      // 0x00423650
    void RangeInit(const wchar_t* text);   // 0x00579a90
};

struct Obj198Sub {
    void* mpVtbl;                 // +0x00
};

struct Obj198 {
    u8        mn00[4];            // +0x00
    Obj198Sub mSub04;             // +0x04
    void Do();                    // 0x00dde570
};

struct GameApi {
    void ShowGalaxy(u32 on);              // 0x00de5470
    void FUN_de53d0(u32 a);               // 0x00de53d0
    void FUN_de86d0(u32 a, u32 b);        // 0x00de86d0
    void FUN_de52d0();                    // 0x00de52d0
    void FUN_e00650(u32 id, u32 arg);     // 0x00e00650
};

struct UI {
    void* FindWindowByID(u32 id);   // 0x00e012b0
    void  SetVisibility(u32 v);     // 0x00e01350
};

struct Layout {
    void* FindWindowByID(u32 id, u32 one);   // 0x008105b0
};

struct F8Obj {
    u8     mPad00[0xb8];
    Layout* mpLayoutB8;             // +0xb8
};

struct Root {
    void FUN_df95d0();              // 0x00df95d0
};

struct EntryBase {
    void BaseCtor();                // 0x00e00630
};

// Galaxy game-entry object (vtable 0x0147dd00) plus the members the UI code touches.
struct GameEntry : EntryBase {
    void*      mpVtbl;              // +0x00
    u32        mn04;                // +0x04
    Stopwatch  mStopwatch;          // +0x08
    EaString16 mStr20;              // +0x20
    u32        mn2C;                // +0x2c
    EaString16 mStr30;              // +0x30
    u32        mn3C;                // +0x3c
    u32        mn40;                // +0x40
    u32        mn44;                // +0x44
    u32        mp48;                // +0x48
    u8         mPad4C[0xac];        // +0x4c
    void*      mpF8;                // +0xf8
    u8         mPadFC[0x48];        // +0xfc
    u8         mLayout144[0x18];    // +0x144
    void*      mp15C;               // +0x15c
    u8         mPad160[0x24];       // +0x160
    void*      mp184;               // +0x184
    u8         mPad188[0x10];       // +0x188
    Obj198*    mp198;               // +0x198
    u8         mPad19C[0x3c];       // +0x19c
    u32        mp1D8;               // +0x1d8
    u32        mn1DC;               // +0x1dc
    u8         mPad1E0[0x11];       // +0x1e0
    u8         mb1F1;               // +0x1f1

    void       FUN_de3300();                       // 0x00de3300
    GameEntry* Ctor_de3370();                      // 0x00de3370
    void       OnModalWindowEnd(u32 a2, u32 a3);   // 0x00de33e0
    void       Dtor_de35d0();                      // 0x00de35d0
    void       BlowSavedGameUpRealGood();          // 0x00de3650
    void       FUN_de38b0(u32 id, u32 arg);        // 0x00de38b0
    void       ShowGalaxy(u32 on);                 // 0x00de5470
    void       FUN_de53d0(u32 a);                  // 0x00de53d0
    void       FUN_de86d0(u32 a, u32 b);           // 0x00de86d0
    void       FUN_de52d0();                       // 0x00de52d0
    void       FUN_e00650(u32 id, u32 arg);        // 0x00e00650
};

struct AudioSys {
    u32  GetGroup();                // vtable slot 0x20
};

struct Mgr {
    u32  FUN_8013c0();              // 0x008013c0
    bool FindLocal(u32 id);         // 0x00801bb0
};

struct CursorCtx {
    void GetInfo(void* out, void* arg);   // 0x007c4180
};

struct ObjE3 {
    void Do(u32 a, u32 mode, u32 b);   // 0x00e3e350
};

struct AnimObj {
    u8  mPad00[0xa4];
    u32 mnA4;                       // +0xa4
};

struct Vec3f {
    f32 x;                          // +0x00
    f32 y;                          // +0x04
    f32 z;                          // +0x08
};

struct Vec4f {
    f32 x;                          // +0x00
    f32 y;                          // +0x04
    f32 z;                          // +0x08
    f32 w;                          // +0x0c
};

struct Vec3i {
    s32 x;                          // +0x00
    s32 y;                          // +0x04
    s32 z;                          // +0x08
};

struct Vec3iList {
    s32 mpBegin;                    // +0x00
    s32 mpEnd;                      // +0x04
};

struct RandomLCG {
    u32 RandomUint32Uniform(u32 n); // 0x00a68fb0
};

struct VisualOut {
    u8  mPad00[0x80];
    f32 mf80;                       // +0x80
    f32 mf84;                       // +0x84
    f32 mf88;                       // +0x88
};

struct Mat33 {
    f32 m[9];
};

struct Xform {
    u16   mn00;                     // +0x00
    u16   mn02;                     // +0x02
    f32   mf04;                     // +0x04
    f32   mf08;                     // +0x08
    f32   mf0C;                     // +0x0c
    f32   mf10;                     // +0x10
    Mat33 mMat;                     // +0x14
};

struct WString16 {
    u32 mpBegin;                    // +0x00
    u32 mpEnd;                      // +0x04
    u32 mpCap;                      // +0x08
    u32 mnPadC;                     // +0x0c
};

struct DateTime {
    u8  mPad[8];
    void Set(int v);                // 0x0092e3d0
    int  GetParameter(int p);       // 0x0092df80
};

struct CString20 {
    CString20();                                        // 0x006b5060
    CString20(u32 a, u32 b, const wchar_t* c);          // 0x006b5770
    ~CString20();                                       // 0x006b5240
    CString20& operator=(const CString20& other);       // 0x006b5430
    const wchar_t* GetText();                           // 0x006b55c0
    u8 mPad[0x14];
};

// ===========================================================================
// 0x00de3300 -- leave the galaxy view and shut the mode down
// ===========================================================================
// @ 0x00de3300
void GameEntry::FUN_de3300()
{
    void* p = FUN_00df5f40();
    ((Fn2)(*(void***)p)[0x60 / 4])(p, 0, 1);
    p = FUN_00df5f40();
    ((Fn1)(*(void***)p)[0x5c / 4])(p, 0);
    ((GameEntry*)*(u32*)0x16a1344)->ShowGalaxy(0);
    ((GameEntry*)*(u32*)0x16a1344)->ShowGalaxy(1);
    ((GameEntry*)*(u32*)0x16a1344)->mp198->Do();
    mp48 = 0;
    p = FUN_00df5f40();
    return ((Root*)p)->FUN_df95d0();
}

// ===========================================================================
// 0x00de3370 -- constructor for the galaxy game-entry object
// ===========================================================================
// @ 0x00de3370
GameEntry* GameEntry::Ctor_de3370()
{
    BaseCtor();
    mpVtbl = (void*)0x147dd00;
    mStopwatch.Ctor(0, 0);
    mStr20.mpBegin = 0x1667bac;
    mStr20.mpEnd = 0x1667bac;
    mStr20.mpCap = 0x1667bae;
    mStr30.mpCap = 0x1667bae;
    mStr30.mpBegin = 0x1667bac;
    mStr30.mpEnd = 0x1667bac;
    mp48 = 0;
    mStopwatch.SetUnits(4);
    *(u32*)0x16a11b4 = (u32)this;
    return this;
}

// ===========================================================================
// 0x00de33e0 -- modal-window end handler for the galaxy entry
// ===========================================================================
// @ 0x00de33e0
void GameEntry::OnModalWindowEnd(u32 a2, u32 a3)
{
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de53d0(0);
    if (mp48 == 0)
        return ((GameEntry*)*(u32*)0x16a1344)->FUN_de86d0(2, 0);

    for (u32 i = 0;
         i < (u32)(((s32)((*(GameEntry**)0x16a1344)->mn1DC -
                          (*(GameEntry**)0x16a1344)->mp1D8)) >> 2); ++i) {
        void* e = ((void**)(*(GameEntry**)0x16a1344)->mp1D8)[i];
        ((Fn1)(*(void***)e)[0x30 / 4])(e, 0);
    }

    void* audio = EA_Audio_GetSystemAT();
    if (a3 == 0x5107b1a) {
        u32 v = 0;
        if (audio != 0)
            v = ((FnU)(*(void***)audio)[0x20 / 4])(audio);
        audio = EA_Audio_GetSystemAT();
        if (audio != 0) {
            ((Fn1)(*(void***)audio)[0x38 / 4])(audio, 0x3475365);
            ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475381, 0xb7d87b0c);
            ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475385, v);
            ((FnV)(*(void***)audio)[0x58 / 4])(audio);
        }
        mn40 = *(u32*)0x16a0f18;
        Mgr* mgr = (Mgr*)FUN_0067cab0();
        mn44 = mgr->FUN_8013c0();
        mgr = (Mgr*)FUN_0067cab0();
        mgr->FindLocal(0x1003);
        return;
    }

    u32 v = 0;
    if (audio != 0)
        v = ((FnU)(*(void***)audio)[0x20 / 4])(audio);
    audio = EA_Audio_GetSystemAT();
    if (audio != 0) {
        ((Fn1)(*(void***)audio)[0x38 / 4])(audio, 0x3475365);
        ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475381, 0x6bd55b2e);
        ((Fn2)(*(void***)audio)[0x40 / 4])(audio, 0x3475385, v);
        ((FnV)(*(void***)audio)[0x58 / 4])(audio);
    }
    mp48 = 0;
    Vec3f ctx;
    ctx.x = 0.0f;
    ctx.y = 0.0f;
    ctx.z = 0.0f;
    GameEntry* g = *(GameEntry**)0x16a1344;
    if (g->mp198 != 0) {
        Obj198Sub* sub = &g->mp198->mSub04;
        ((FnUP)(*(void***)sub)[4 / 4])(sub, 0x2ca298e9, &ctx);
    }
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de86d0(2, 0);
}

// ===========================================================================
// 0x00de35d0 -- destructor for the galaxy game-entry object
// ===========================================================================
// @ 0x00de35d0
void GameEntry::Dtor_de35d0()
{
    mpVtbl = (void*)0x147dd00;
    *(u32*)0x16a11b4 = 0;
    u32 p = mStr30.mpBegin;
    if ((s32)((mStr30.mpCap - p) & 0xfffffffe) > 2 && p != 0)
        op_del_array((void*)p);
    p = mStr20.mpBegin;
    if ((s32)((mStr20.mpCap - p) & 0xfffffffe) > 2 && p != 0)
        op_del_array((void*)p);
    mpVtbl = (void*)0x147dba8;
}

// ===========================================================================
// 0x00de3650 -- tear down the saved game (effects + picker strings)
// ===========================================================================
// @ 0x00de3650
void GameEntry::BlowSavedGameUpRealGood()
{
    if (mp48 == 0)
        return;

    GameEntry* g = *(GameEntry**)0x16a1344;
    void* out = 0;
    void* obj = g->mp15C;
    ((Fn2P)(*(void***)obj)[8 / 4])(obj, 0x339dccf3, 0, &out);

    if (out != 0) {
        VisualOut* vo = (VisualOut*)out;
        f32 f80 = vo->mf80;
        f32 f84 = vo->mf84;
        f32 f88 = vo->mf88;
        Mat33 mat = *(const Mat33*)0x16a122c;
        Xform x;
        x.mMat = mat;
        x.mf04 = ((f84 * *(f32*)0x16a1238 + f88 * *(f32*)0x16a1244)
                  + *(f32*)0x16a122c * f80) + *(f32*)0x16a1250;
        x.mf08 = *(f32*)0x16a1254
                 + ((f84 * *(f32*)0x16a123c + f88 * *(f32*)0x16a1248)
                    + *(f32*)0x16a1230 * f80);
        x.mf0C = *(f32*)0x16a1258
                 + ((f84 * *(f32*)0x16a1240 + f88 * *(f32*)0x16a124c)
                    + *(f32*)0x16a1234 * f80);
        x.mn00 = 4;
        x.mn02 = 1;
        x.mf10 = *(f32*)0x1485720;
        ((FnP)(*(void***)out)[0x18 / 4])(out, &x);
        ((Fn1)(*(void***)out)[8 / 4])(out, 0);
    }

    Vec3f ctx;
    ctx.x = 0.0f;
    ctx.y = 0.0f;
    ctx.z = 0.0f;
    GameEntry* g2 = *(GameEntry**)0x16a1344;
    if (g2->mp198 != 0) {
        Obj198Sub* sub = &g2->mp198->mSub04;
        ((FnUP)(*(void***)sub)[4 / 4])(sub, 0x2ca298e9, &ctx);
    }
    mStopwatch.Restart();
    if (mp48 != (u32)&mStr20) {
        EaString16* s = (EaString16*)mp48;
        mStr20.Assign(s->mpBegin, s->mpEnd);
    }
    if (out != 0)
        ((FnV)(*(void***)out)[4 / 4])(out);
}

// ===========================================================================
// 0x00de38b0 -- first-time-action notification hook
// ===========================================================================
// @ 0x00de38b0
void GameEntry::FUN_de38b0(u32 id, u32 arg)
{
    if ((((u32*)0x16a1848)[id >> 5] >> (id & 0x1f)) & 1)
        return;
    if (id == 0x1b && (*(GameEntry**)0x16a1344)->mb1F1 == 0) {
        void* audio = EA_Audio_GetSystemAT();
        KillSetiEffects(0x5da7b944,
                        audio != 0 ? ((FnU)(*(void***)audio)[0x20 / 4])(audio) : 0);
        ((GameEntry*)*(u32*)0x16a1344)->FUN_de52d0();
    }
    FUN_e00650(id, arg);
}

// ===========================================================================
// 0x00de3930 -- mouse-enter handler
// ===========================================================================
// @ 0x00de3930
void __cdecl FUN_00de3930()
{
    void* ms = MessageServer();
    ((Fn3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2ed, 0, 0);
    void* movie = MovieSystem();
    if (movie != 0)
        ((Fn1)(*(void***)movie)[0x40 / 4])(movie, 1);
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de53d0(1);
    for (void** p = (void**)(*(GameEntry**)0x16a1344)->mp1D8;
         p != (void**)(*(GameEntry**)0x16a1344)->mn1DC; ++p) {
        void* e = *p;
        ((Fn1)(*(void***)e)[0x30 / 4])(e, 1);
    }
    GameEntry* g = *(GameEntry**)0x16a1344;
    void* w = ((UI*)g->mp184)->FindWindowByID(0x10f33e0);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10ed874);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, (u32)(g->mb1F1 == 0));
    g = *(GameEntry**)0x16a1344;
    ((UI*)g->mp184)->SetVisibility((u32)(g->mb1F1 == 0));
    g = *(GameEntry**)0x16a1344;
    w = ((Layout*)g->mLayout144)->FindWindowByID(0x615a5ff, 1);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    g = *(GameEntry**)0x16a1344;
    if (g->mpF8 != 0) {
        w = ((F8Obj*)g->mpF8)->mpLayoutB8->FindWindowByID(0x2e5a4a8, 1);
        if (w != 0)
            ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    }
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10ed852);
    if (w == 0) {
        g->mpF8 = 0;
        return;
    }
    void* w2 = ((FnC)(*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
    if (w2 == 0) {
        g->mpF8 = 0;
        return;
    }
    ((Fn2)(*(void***)w2)[0x28 / 4])(w2, 4, 1);
    g->mpF8 = 0;
}

// ===========================================================================
// 0x00de3ae0 -- mouse-leave handler
// ===========================================================================
// @ 0x00de3ae0
void __cdecl FUN_00de3ae0()
{
    void* ms = MessageServer();
    ((Fn3)(*(void***)ms)[0x14 / 4])(ms, 0x695d2f5, 0, 0);
    ((GameEntry*)*(u32*)0x16a1344)->FUN_de53d0(0);
    for (void** p = (void**)(*(GameEntry**)0x16a1344)->mp1D8;
         p != (void**)(*(GameEntry**)0x16a1344)->mn1DC; ++p) {
        void* e = *p;
        ((Fn1)(*(void***)e)[0x30 / 4])(e, 0);
    }
    GameEntry* g = *(GameEntry**)0x16a1344;
    void* w = ((UI*)g->mp184)->FindWindowByID(0x10ed874);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 0);
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10f33e0);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 1);
    g = *(GameEntry**)0x16a1344;
    w = ((Layout*)g->mLayout144)->FindWindowByID(0x615a5ff, 1);
    if (w != 0)
        ((Fn2)(*(void***)w)[0x7c / 4])(w, 1, 1);
    g = *(GameEntry**)0x16a1344;
    w = ((UI*)g->mp184)->FindWindowByID(0x10ed852);
    if (w != 0) {
        void* w2 = ((FnC)(*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
        if (w2 != 0)
            ((Fn2)(*(void***)w2)[0x28 / 4])(w2, 4, 0);
    }
}

// ===========================================================================
// 0x00de3be0 -- animation-state to editor-tool dispatch
// ===========================================================================
// @ 0x00de3be0
void __cdecl FUN_00de3be0(AnimObj* p)
{
    switch (p->mnA4) {
    case 1:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c01, 1);
        return;
    case 2:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c02, 1);
        return;
    case 4:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c04, 1);
        return;
    case 5:
        ((ObjE3*)FUN_00b3d410())->Do(1, (u32)0x1654c05, 1);
        return;
    }
}

// ===========================================================================
// 0x00de3c70 -- map a cursor position onto the main window area
// ===========================================================================
// @ 0x00de3c70
void __cdecl FUN_00de3c70(void* param1, f32* param2, f32* param3)
{
    void* app = SP_App();
    void* x = ((FnPP)(*(void***)app)[0x58 / 4])(app);
    Vec3f local;
    ((CursorCtx*)x)->GetInfo(&local, param1);
    Vec4f area;
    SPUIHelpers_GetMainWindowArea(&area);
    const f32 one = *(f32*)0x1485720;
    *param2 = ((area.z - area.x) * (local.x + one)) * *(f32*)0x1471064;
    *param3 = (one - (local.y + one) * *(f32*)0x1471064) * (area.w - area.y);
}

// ===========================================================================
// 0x00de3d00 -- place a layout-supplied image into a window
// ===========================================================================
// @ 0x00de3d00
bool __cdecl FUN_00de3d00(Layout* layout, u32 id, u32 which)
{
    void* img = SPUIHelpers_GetImageFromLayout(layout, which);
    if (img != 0) {
        void* win = layout->FindWindowByID(id, 1);
        if (win != 0)
            FUN_008068d0(win, img, 0);
    }
    return false;
}

// ===========================================================================
// 0x00de3d40 -- pick a random vector different from the excluded one
// ===========================================================================
// @ 0x00de3d40
void __cdecl FUN_00de3d40(Vec3i* out, Vec3iList* list, Vec3i* exclude)
{
    s32* base = (s32*)list->mpBegin;
    if (base != (s32*)list->mpEnd) {
        if ((list->mpEnd - list->mpBegin) / 12 == 1) {
            out->x = base[0];
            out->y = base[1];
            out->z = base[2];
            return;
        }
        u32 i;
        do {
            i = ((RandomLCG*)0x1601760)->RandomUint32Uniform(
                    (u32)((list->mpEnd - list->mpBegin) / 12));
            base = (s32*)list->mpBegin;
        } while (base[i * 3] == exclude->x &&
                 base[i * 3 + 1] == exclude->y &&
                 base[i * 3 + 2] == exclude->z);
        out->x = base[i * 3];
        out->y = base[i * 3 + 1];
        out->z = base[i * 3 + 2];
        return;
    }
    out->x = 0;
    out->y = 0;
    out->z = 0;
}

// ===========================================================================
// 0x00de3e00 -- resolve a window's image
// ===========================================================================
// @ 0x00de3e00
u32 __cdecl sGetWindowImage(void* w)
{
    if (w != 0) {
        void* a = ((FnPP)(*(void***)w)[0xa8 / 4])(w);
        if (a != 0) {
            void* b = ((FnC)(*(void***)a)[0xc / 4])(a, 0xef3c47cf);
            if (b != 0)
                return ((FnU)(*(void***)b)[0x18 / 4])(b);
        }
    }
    return 0;
}

// ===========================================================================
// 0x00de3e40 -- open the URL stored in a property
// ===========================================================================
// @ 0x00de3e40
void __cdecl FUN_00de3e40(u32 arg)
{
    void* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        void* old = prop;
        prop = 0;
        ((FnV)(*(void***)old)[4 / 4])(old);
    }
    char ok = ((FnQC)(*(void***)pm)[0x2c / 4])(pm, *(u32*)0x15a2df8, 0, &prop);
    if (ok) {
        WString16 ws;
        ws.mpBegin = 0x1667bac;
        ws.mpEnd = 0x1667bac;
        ws.mpCap = 0x1667bae;
        if (SP_GetPropertyAsString16(prop, arg, &ws)) {
            void* app = SP_AppSystem();
            ((Fn1)(*(void***)app)[0x5c / 4])(app, ws.mpBegin);
        }
        if ((s32)((ws.mpCap - ws.mpBegin) & 0xfffffffe) > 2 && ws.mpBegin != 0)
            op_del_array((void*)ws.mpBegin);
    }
    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
}

// ===========================================================================
// 0x00de3f00 -- set a window's image from a resource
// ===========================================================================
// @ 0x00de3f00
bool __cdecl FUN_00de3f00(void* win, u32 res, void* image)
{
    if (win != 0) {
        void* a = ((FnPP)(*(void***)win)[0xa8 / 4])(win);
        if (a != 0) {
            void* b = ((FnC)(*(void***)a)[0xc / 4])(a, 0xef3c47cf);
            if (b != 0) {
                void* cur = image;
                if (cur != 0)
                    ((FnV)(*(void***)cur)[0 / 4])(cur);
                if (cur == 0)
                    SPUIHelpers_CreateImageFromResource2((void*)res, &cur, 0, -1, -1);
                if (cur != 0) {
                    ((Fn1)(*(void***)b)[0x14 / 4])(b, (u32)cur);
                    ((FnV)(*(void***)win)[0x90 / 4])(win);
                    if (cur != 0)
                        ((FnV)(*(void***)cur)[4 / 4])(cur);
                    return true;
                }
            }
        }
    }
    return false;
}

// ===========================================================================
// 0x00de3fa0 -- build the localized verb-icon label for a mode
// ===========================================================================
// @ 0x00de3fa0
EaString16* __cdecl FUN_00de3fa0(EaString16* out, u32 sel)
{
    CString20 str;
    switch (sel) {
    case 0:
        str = CString20(0x2b7a0311, 0x5b08702, 0);
        break;
    case 1:
        str = CString20(0x2b7a0311, 0x5b08703, 0);
        break;
    case 2:
        str = CString20(0x2b7a0311, 0x5b08704, 0);
        break;
    case 4:
        str = CString20(0x2b7a0311, 0x5b08705, 0);
        break;
    case 5:
        str = CString20(0x2b7a0311, 0x5b08706, 0);
        break;
    }
    const wchar_t* text = str.GetText();
    out->mpBegin = 0;
    out->mpEnd = 0;
    out->mpCap = 0;
    out->RangeInit(text);
    return out;
}

// ===========================================================================
// 0x00de40e0 -- format the current date into a label string
// ===========================================================================
// @ 0x00de40e0
EaString16* __cdecl FUN_00de40e0(EaString16* out, void* tm)
{
    DateTime dt;
    dt.Set(2);
    SetDateFromTm(tm, &dt);
    int a = dt.GetParameter(6);
    int b = dt.GetParameter(2);
    int c = dt.GetParameter(1);
    wchar_t buf[256];
    FUN_00881720(a, b, c, buf, 0xff, 0);
    out->mpBegin = 0;
    out->mpEnd = 0;
    out->mpCap = 0;
    out->RangeInit(buf);
    return out;
}
