// Decompiled from SporeApp.exe (gold6 batch, worker 33).
// Slice s00d084d0: community-editor shopping/economy helpers, UI launch,
// camera/HUD toggles, and the building/vehicle cost switches.

typedef unsigned int   u32;
typedef int            s32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef float          f32;

// ---------------------------------------------------------------------------
// calling shapes
// ---------------------------------------------------------------------------
typedef void  (__thiscall* FnV)(void*);
typedef void  (__thiscall* Fn1)(void*, u32);
typedef void  (__thiscall* Fn2)(void*, u32, u32);
typedef char  (__thiscall* FnC2)(void*, u32, u32);
typedef void* (__thiscall* FnP1)(void*, u32);
typedef void* (__thiscall* FnP0)(void*);
typedef void  (__thiscall* FnGet3)(void*, u32, u32, void**);
typedef char  (__thiscall* FnGet2)(void*, u32, void**);
typedef void  (__thiscall* FnStr)(void*, u32, u32, void**);
typedef void  (__thiscall* Fn3S)(void*, u32, const char*);

// ---------------------------------------------------------------------------
// free functions / runtime helpers
// ---------------------------------------------------------------------------
extern "C" void* __cdecl SP_PropertyManager();                       // 0x0067de30
extern "C" char  __cdecl SP_GetPropertyAsKeyInstance(void*, u32, u32*); // 0x006a12a0
extern "C" void* __cdecl SP_GameInputManager();                      // 0x00b3d250
extern "C" void* __cdecl GetCameraCtl();                             // 0x00b3d280
extern "C" void* __cdecl SP_App();                                   // 0x0067dd10
extern "C" u32   __cdecl SP_GetCurrentGameMode();                    // 0x00b5b800
extern "C" void* __cdecl GameTimeManager();                          // 0x00b3d380
extern "C" void* __cdecl FUN_0067caf0();                             // 0x0067caf0
extern "C" void* __cdecl FUN_0067cac0();                             // 0x0067cac0
extern "C" void  __cdecl FUN_00572020(void*, u32);                   // 0x00572020
extern "C" void  __cdecl sub_64a990(void*);                          // 0x0064a990
extern "C" u32   __cdecl SP_GetPlayerEmpireID();                     // 0x01021090
extern "C" float __cdecl FUN_00bcde40(u32);                          // 0x00bcde40
extern "C" float __cdecl FUN_00bcde70(u32);                          // 0x00bcde70
extern "C" float __cdecl FUN_00bcdea0(u32);                          // 0x00bcdea0
extern "C" float __cdecl FUN_00bce400(u32);                          // 0x00bce400
extern "C" char  __cdecl FUN_00b673c0(void*);                        // 0x00b673c0
extern "C" char  __cdecl FUN_00b188b0(void*);                        // 0x00b188b0
extern "C" char  __cdecl FUN_00b18740(void*);                        // 0x00b18740
extern "C" char  __cdecl FUN_00b18760(void*);                        // 0x00b18760
extern "C" char  __cdecl FUN_00b187b0(void*);                        // 0x00b187b0
extern "C" char  __cdecl FUN_00b18790(void*);                        // 0x00b18790
extern "C" char  __cdecl FUN_00b187f0(void*);                        // 0x00b187f0
extern "C" void  __cdecl FUN_00b69990(void*);                        // 0x00b69990

// ---------------------------------------------------------------------------
// small objects defined in other translation units
// ---------------------------------------------------------------------------
struct CString14 {
    u8   mPad[0x14];
    char Load(u32 key, u32 id, s32 a);   // 0x006b54b0
};

struct PropObj {
    u8  mPad00[0x12];
    u16 mn12;                            // +0x12
};

struct GetIntF {
    u32* GetInt();                       // 0x0041e990
};

struct InputMgr {
    void Do(u32 id, const char* name);   // vtable +0x40
};

struct CameraCtl {
    void Do(u32* v, u32 a);              // 0x00b13bb0
};

struct HudObj {
    u8  mPad00[0x18];
    u32 mn18;
    u8  mPad1C[0x0c];
    u32 mn28;
    char IsSet();                        // 0x00678ed0
};

struct HintsObj {
    char SetFlag(int a, char b);         // 0x0067c420
};

struct GameTime {
    u32 DecPauseGate(u32 id);            // 0x00b32250
};

struct CivObj {
    float GetCost(u32 a, u32 b);         // 0x00bf2170
};

struct CityObj {
    CivObj* GetCivilization();            // 0x00bd9bf0
};

struct LaunchInit {
    void Init();                         // 0x00644b10
    void Destroy();                      // 0x00644b60
};

// ---------------------------------------------------------------------------
// 0x00d08930 -- register the community-editor menu commands
// ---------------------------------------------------------------------------
// @ 0x00d08930
void FUN_00d08930()
{
    void* mgr = SP_GameInputManager();
    if (mgr == 0)
        return;
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e80, (const char*)0x14792a4);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e82, (const char*)0x1479288);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e81, (const char*)0x147926c);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e83, (const char*)0x1479250);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e84, (const char*)0x1479234);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e85, (const char*)0x1479218);
    ((Fn3S)(*(void***)mgr)[0x40 / 4])(mgr, 0x3e86, (const char*)0x1479200);
}

// ---------------------------------------------------------------------------
// 0x00d08a70 -- release the audio handle at +0x2b8
// ---------------------------------------------------------------------------
struct Obj8A70 {
    u8    mPad00[0x2b8];
    void* mp2B8;                        // +0x2b8
    u32   Do(u32 a, u32 b);
};

// @ 0x00d08a70
u32 Obj8A70::Do(u32 a, u32 b)
{
    if (mp2B8 != 0) {
        FUN_00572020(mp2B8, 0);
        mp2B8 = 0;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00d08aa0 -- camera control transform with the first argument's address
// ---------------------------------------------------------------------------
// @ 0x00d08aa0
void __stdcall FUN_00d08aa0(u32 a1, u32 a2, u32 a3, u32 a4)
{
    if (GetCameraCtl() != 0)
        ((CameraCtl*)GetCameraCtl())->Do(&a1, a4);
}

// ---------------------------------------------------------------------------
// 0x00d08ad0 -- creature/community visibility gate
// ---------------------------------------------------------------------------
// @ 0x00d08ad0
void FUN_00d08ad0(void* obj)
{
    if (obj == 0)
        return;
    if (!FUN_00b673c0(obj))
        return;
    u32 mode = SP_GetCurrentGameMode();
    if (mode == 0x1654c02)
        return;
    if ((u32)(mode + 0xfe9ab3fc) <= 1) {
        if (FUN_00b188b0(obj))
            return;
        if (FUN_00b18740(obj) && !FUN_00b18760(obj))
            return;
        if (FUN_00b187b0(obj))
            return;
        if (FUN_00b18790(obj))
            return;
        if (FUN_00b187f0(obj))
            return;
    }
    FUN_00b69990(obj);
}

// ---------------------------------------------------------------------------
// 0x00d08f60 -- unpause the community editor and show the hint
// ---------------------------------------------------------------------------
// @ 0x00d08f60
void FUN_00d08f60()
{
    GameTime* gt = (GameTime*)GameTimeManager();
    gt->DecPauseGate(0x4bf38a7);
    void* hud = FUN_0067caf0();
    if (((HudObj*)hud)->IsSet()) {
        ((HintsObj*)FUN_0067cac0())->SetFlag(1, 1);
    }
}

// ---------------------------------------------------------------------------
// 0x00d089d0 -- building cost from (model type, sub type)
// ---------------------------------------------------------------------------
// @ 0x00d089d0
int FUN_00d089d0(u32 modelType, u32 subType)
{
    u32 empire = SP_GetPlayerEmpireID();
    if (modelType == 0x81c74dbc) {
        if (subType < 0x4e3f7778) {
            if (subType == 0x4e3f7777)
                return (int)FUN_00bcde70(empire);
            if (subType == 0x99e92f05)
                return 0;
            if (subType == 0x47c10953)
                return (int)FUN_00bcde40(empire);
        } else if (subType == 0x72c49181) {
            return (int)FUN_00bcdea0(empire);
        }
        return 0x19;
    }
    if (modelType == 0x142462a)
        return (int)FUN_00bce400(empire);
    return -1;
}

// ---------------------------------------------------------------------------
// 0x00d084d0 -- CanAffordWithReason
// ---------------------------------------------------------------------------
struct Request84D0 {
    u32 mn00;
    u32 mn04;
    u32 mn08;
};

struct Props84D0 {
    CString14 mStr00;                    // +0x00
    CString14 mStr14;                    // +0x14
    u32       mn28;
    u32       mn2C;
    u8        mb30;
};

struct Obj84D0 {
    int Do(Request84D0* req, Props84D0* out);
};

// @ 0x00d084d0
int Obj84D0::Do(Request84D0* req, Props84D0* out)
{
    void* self = (void*)this;
    void* prop = 0;
    void* pm = SP_PropertyManager();
    if (prop != 0) {
        void* old = prop;
        prop = 0;
        ((FnV)(*(void***)old)[4 / 4])(old);
    }
    ((FnGet3)(*(void***)pm)[0x2c / 4])(pm, req->mn00, req->mn08, &prop);

    u32 key = 0;
    if (SP_GetPropertyAsKeyInstance(prop, 0x2196ad5, &key)) {
        switch (key) {
        case 0x42bf8c1d:
        case 0x2b885df4:
            goto done1;
        case 0x142462a:
            if (!((FnC2)(*(void***)self)[0xc / 4])(self, 2, 1)) {
                if (out) {
                    ((CString14*)out)->Load(0x496bfb26, 0x10a, 0);
                    out->mStr14.Load(0x496bfb26, 0x20a, 0);
                    out->mn2C = 0xb879e6e8;
                    out->mn28 = 0xff00ff00;
                }
                goto done4;
            }
            if (((FnC2)(*(void***)self)[0xc / 4])(self, 7, 1))
                goto fallback;
            if (out) {
                ((CString14*)out)->Load(0x496bfb26, 0x108, 0);
                out->mStr14.Load(0x496bfb26, 0x208, 0);
                out->mn2C = 0x19788c55;
                out->mn28 = 0xffff0000;
            }
            goto done4;
        case 0xfcafd26:
            goto done2;
        case 0x4d863c8b:
            goto fallback;
        case 0x81c74dbc:
            if (req->mn00 == 0x115fa309) {
                if (out) {
                    ((CString14*)out)->Load(0x496bfb26, 0x109, 0);
                    out->mStr14.Load(0x496bfb26, 0x209, 0);
                    out->mn2C = 0xb879e6e8;
                    out->mn28 = 0xff00ff00;
                }
                goto done4;
            }
            if (!((FnC2)(*(void***)self)[0xc / 4])(self, 1, 1)) {
                if (out) {
                    ((CString14*)out)->Load(0x496bfb26, 0x103, 0);
                    out->mStr14.Load(0x496bfb26, 0x203, 0);
                    out->mn2C = 0xb879e6e8;
                    out->mn28 = 0xff00ff00;
                }
                goto done4;
            }
            if (((FnC2)(*(void***)self)[0xc / 4])(self, 7, 1))
                goto fallback;
            if (out) {
                ((CString14*)out)->Load(0x496bfb26, 0x108, 0);
                out->mStr14.Load(0x496bfb26, 0x208, 0);
                out->mn2C = 0x19788c55;
                out->mn28 = 0xffff0000;
            }
            goto done4;
        case 0x8bfac054: {
            u32 v = 0;
            if (SP_GetPropertyAsKeyInstance(prop, 0x5338876f, &v) && v == 0x98e03c0d) {
                if (out) {
                    ((CString14*)out)->Load(0x496bfb26, 0x10d, 0);
                    out->mStr14.Load(0x496bfb26, 0x20d, 0);
                    out->mn2C = 0xb879e6e8;
                    out->mn28 = 0xff00ff00;
                }
                goto done6;
            }
            if (!((FnC2)(*(void***)self)[0xc / 4])(self, 6, 1)) {
                if (out) {
                    ((CString14*)out)->Load(0x496bfb26, 0x106, 0);
                    out->mStr14.Load(0x496bfb26, 0x206, 0);
                    out->mn2C = 0xb879e6e8;
                    out->mn28 = 0xff00ff00;
                }
                goto done5;
            }
            goto done1;
        }
        default:
            goto done2;
        }
    }

fallback:
    {
        void* sub = 0;
        u32 v = 0;
        if (prop != 0 &&
            ((FnGet2)(*(void***)prop)[0x24 / 4])(prop, 0x2166464, &sub) &&
            ((PropObj*)sub)->mn12 == 9) {
            v = *((GetIntF*)sub)->GetInt();
        }
        if (((FnC2)(*(void***)self)[0xc / 4])(self, 0, v))
            goto done1;
        if (out) {
            ((CString14*)out)->Load(0x496bfb26, 0x101, 0);
            out->mStr14.Load(0x496bfb26, 0x201, 0);
            out->mn2C = 0;
            out->mb30 = 1;
        }
        goto done2;
    }

done1:
    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
    return 1;
done2:
    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
    return 2;
done4:
    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
    return 4;
done5:
    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
    return 5;
done6:
    if (prop != 0)
        ((FnV)(*(void***)prop)[4 / 4])(prop);
    return 6;
}

// ---------------------------------------------------------------------------
// 0x00d08d80 -- UI placement request dispatch
// ---------------------------------------------------------------------------
struct Req8D80 {
    u8  mPad00[8];
    u32 mn08;                            // +0x08
    f32 mf0C;                            // +0x0c
    f32 mf10;                            // +0x10
    u32 mn14;                            // +0x14
    u32 mn18;                            // +0x18
};

// @ 0x00d08d80
char __stdcall FUN_00d08d80(Req8D80* req)
{
    void* ctl;
    void* app = SP_App();
    if (app != 0)
        ctl = ((FnP0)(*(void***)app)[0x2c / 4])(app);
    else
        ctl = 0;

    switch (req->mn08 - 1) {
    case 0:
    case 1:
    case 4:
        break;
    default:
        return 0;
    case 5:
        if (req->mn18 == 1000) {
            char r;
            if (ctl == 0)
                return 0;
            r = ((char (__thiscall*)(void*, u32, f32, f32, u32))
                 (*(void***)ctl)[0x2c / 4])(ctl, 1000, req->mf0C, req->mf10, req->mn14);
            if (!r)
                return 0;
            goto ret1;
        }
        break;
    case 6:
        if (req->mn18 == 1000) {
            if (ctl == 0)
                return 0;
            if (!((char (__thiscall*)(void*, u32, f32, f32, u32))
                  (*(void***)ctl)[0x30 / 4])(ctl, 1000, req->mf0C, req->mf10, req->mn14))
                return 0;
            goto ret1;
        }
        break;
    case 7:
        if (ctl == 0)
            return 0;
        if (((char (__thiscall*)(void*, f32, f32, u32))
             (*(void***)ctl)[0x34 / 4])(ctl, req->mf0C, req->mf10, req->mn14))
            goto ret1;
        return 0;
    case 8:
        if (ctl == 0)
            return 0;
        if (!((char (__thiscall*)(void*, u32, f32, f32, u32))
              (*(void***)ctl)[0x38 / 4])(ctl, req->mn18, req->mf0C, req->mf10, req->mn14))
            return 0;
        goto ret1;
    }
ret1:
    return 1;
}

// ---------------------------------------------------------------------------
// 0x00d08fa0 -- vehicle cost from model type
// ---------------------------------------------------------------------------
struct Editor8FA0 {
    u8    mPad00[0x40];
    void* mp40;                          // +0x40
    int   GetVehicleCost(u32 type);
};

// @ 0x00d08fa0
int Editor8FA0::GetVehicleCost(u32 type)
{
    void* c = 0;
    if (mp40 != 0)
        c = ((FnP1)(*(void***)mp40)[0xc / 4])(mp40, 0xee9b2232);
    CityObj* city = (CityObj*)c;

    switch (type) {
    case 0x7d433fad:
        return (int)city->GetCivilization()->GetCost(0, 0);
    case 0x2a5147a9:
        return (int)city->GetCivilization()->GetCost(2, 1);
    case 0x1a4e0708:
        return (int)city->GetCivilization()->GetCost(2, 2);
    case 0x1f2a25b6:
        return (int)city->GetCivilization()->GetCost(1, 1);
    case 0x2090a11b:
        return (int)city->GetCivilization()->GetCost(2, 2);
    case 0x441cd3e6:
        return (int)city->GetCivilization()->GetCost(0, 2);
    case 0x449c040f:
        return (int)city->GetCivilization()->GetCost(1, 2);
    case 0x8f963dcb:
        return (int)city->GetCivilization()->GetCost(0, 1);
    case 0x9ad7d4aa:
        return (int)city->GetCivilization()->GetCost(1, 0);
    case 0xbc1041e6:
        return (int)city->GetCivilization()->GetCost(2, 0);
    case 0xc0b74287:
        return (int)city->GetCivilization()->GetCost(2, 0);
    case 0xc15695da:
        return (int)city->GetCivilization()->GetCost(2, 1);
    case 0xf670aa43:
        return (int)city->GetCivilization()->GetCost(2, 0);
    }
    return 0x19;
}

// ---------------------------------------------------------------------------
// 0x00d08b50 -- open the shopping browser for a model type
// ---------------------------------------------------------------------------
struct Launch8B50 {
    u32 mn00;                            // +0x00
    u32 mn04;                            // +0x04
    u32 mn08;                            // +0x08
    u32 mn0C;                            // +0x0c
    u8  mb10;                            // +0x10
    u8  mb11;
    u8  mb12;
    u8  mb13;
    u8  mb14;                            // +0x14
    u8  mPad15[3];
    u32 mn18;                            // +0x18
    u32 mn1C;                            // +0x1c
    u32 mn20;                            // +0x20
    u8  mb24;                            // +0x24
    u8  mPad25[3];
    u32 mn28;                            // +0x28
    u8  mb2C;                            // +0x2c
    u8  mPad2D[3];
    u32 mn30;                            // +0x30
    u32 mn34;                            // +0x34
    u32 mn38;                            // +0x38
    u32 mn3C;                            // +0x3c
    u32 mn40;                            // +0x40
    u32 mn44;                            // +0x44
};

struct Editor8B50 {
    u8  mPad00[0x48];
    u32 mn48;                            // +0x48
    void Setup(u32 modelType, u32 p3, u32 p4, u32 p5, u8 p6);
};

// @ 0x00d08b50
void Editor8B50::Setup(u32 modelType, u32 p3, u32 p4, u32 p5, u8 p6)
{
    mn48 = modelType;

    u32 h;
    switch ((s32)modelType) {
    case 0x2090a11b: h = 0x5b38a3b2; break;
    case 0xc15695da: h = 0xaafaf799; break;
    case 0x99e92f05: h = 0x695cbb72; break;
    case 0x8f963dcb: h = 0xbdf55802; break;
    case 0x98e03c0d: h = 0x9c5c0628; break;
    case 0x9ad7d4aa: h = 0xa32e702d; break;
    case 0xbc1041e6: h = 0xa1986101; break;
    case 0x1a4e0708: h = 0xa64eb2c3; break;
    case 0xccc35c46: h = 0x58d29fb5; break;
    case 0xf670aa43: h = 0x7d042d12; break;
    case 0x1f2a25b6: h = 0x46934e5d; break;
    case 0x47c10953: h = 0x47f2ebb2; break;
    case 0x441cd3e6: h = 0x11e8c369; break;
    case 0x2a5147a9: h = 0x8a551fdc; break;
    case 0x372e2c04: h = 0x261aee8b; break;
    case 0x449c040f: h = 0xbbe19f1e; break;
    case 0x72c49181: h = 0xed90d2e6; break;
    case 0x4e3f7777: h = 0x8049b6dc; break;
    case 0x65672ade: h = 0x40e24ee9; break;
    case 0x7d433fad: h = 0xb7c9952c; break;
    default: return;
    }

    Launch8B50 launch;
    ((LaunchInit*)&launch)->Init();
    launch.mb14 = 1;
    launch.mn38 = (u32)((char*)this + 4);
    launch.mn30 = 0xad0e52;
    launch.mn04 = SP_GetCurrentGameMode();
    launch.mn18 = p3;
    launch.mn1C = p4;
    launch.mn00 = h;
    launch.mn20 = p5;
    launch.mb24 = p6;
    launch.mb10 = 1;
    sub_64a990(&launch);
    ((LaunchInit*)&launch)->Destroy();
}
