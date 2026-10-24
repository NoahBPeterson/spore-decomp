// Slice s00d1c010 -- SP::cGameEditModeStrategy (retail edit-mode game strategy).
//
// Layout notes (retail member offsets are read from the disassembly; the PDB
// layout is modelled locally with role-named members and explicit padding for
// the untouched gaps).
//
//   this == object+0x00 for the cIModeStrategy methods (the cIModeStrategy
//   subobject vtable sits at object+0x00).  The two cIGonzagoSubsystem
//   overrides (0xd1c560 PreGameModeTransition / 0xd1c9e0 PostGameModeTransition)
//   are reached through the +0x08 subobject vtable, so they see this == object+0x08.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef long long      i64;
typedef float          f32;
typedef double         f64;
typedef unsigned int   size_t;
typedef signed char    i8;

#define FORCEINLINE __forceinline

// vtable slot fetch: VFN(p, byteOffset) reads p->vftable[byteOffset/4]
#define VFN(p, byteOff)  (((void**)(*(void**)(p)))[(byteOff) / 4])

// ------------------------------------------------------------- cdecl externs
extern "C" void  *GameInputManager();                                   // 0x00b3d250
extern "C" void  *GameTimeManager();                                    // 0x00b3d380
extern "C" void  *EA_Messaging_GetServer();                             // 0x00883860
extern "C" void   EA_Messaging_RemoveHandler(void*, void*, void*, u32, u32);//0x00571db0
extern "C" void  *PlanetModel();                                        // 0x00b3d350
extern "C" u8     GetPropertyAsKey(void*, u32, void*);                  // 0x006a1250
extern "C" void  *operator_new(u32, const char*, int, int, int, int);   // 0x00f473a0
extern "C" void  *MessageServer();                                      // 0x0067dcc0
extern "C" void  *FUN_00b3d240();                                       // 0x00b3d240
extern "C" void  *FUN_00b3d290(const char*, void*, void*, void*, f32, f32);//0x00b3d290
extern "C" void  *GetGameTerrainCursor();                               // 0x00b30d70
extern "C" void  *EffectsManagerPtr();                                  // 0x0067ddd0
extern "C" void  *NounManager();                                        // 0x00b3d300
extern "C" u32    FNV1_String16(const u16*, u32, int);                  // 0x00932f30
extern "C" u8     FUN_00d1c610(int, int);                               // 0x00d1c610
// thiscall(this only) helpers modelled with __fastcall (ecx == first arg)
extern "C" void   __fastcall FUN_00b8c0f0(void*);                       // 0x00b8c0f0
extern "C" void   __fastcall FUN_00ac6960(void*);                       // 0x00ac6960
extern "C" void   __fastcall FUN_00ac4570(void*, void*, void*);         // 0x00ac4570 (self,a,b)
// cdecl helpers
extern "C" void   FUN_00b99670();                                       // 0x00b99670
extern "C" void   FUN_00b99530(int, int, int);                          // 0x00b99530
extern "C" void   FUN_00ba1280();                                       // 0x00ba1280

// --------------------------------------------------------------- vtable ids
extern u8 vtbl_1477530;   // 0x01477530
extern u8 vtbl_13eb384;   // 0x013eb384
extern u8 vtbl_1479f20;   // 0x01479f20
extern u8 vtbl_1479f10;   // 0x01479f10
extern u8 vtbl_1479ec0;   // 0x01479ec0
extern u8 vtbl_1479eb8;   // 0x01479eb8
extern u8 vtbl_13eb394;   // 0x013eb394
extern u8 vtbl_13eb938;   // 0x013eb938

// ------------------------------------------------------------- global state
extern void* g_sInstance;              // 0x0169dca8
extern u32   g1582738;                 // 0x01582738 (message id array[0])
extern u16*  g15826ac;                 // 0x015826ac (sLastLoadedScenario begin)
extern u16*  g15826b0;                 // 0x015826b0 (sLastLoadedScenario end)
extern u32   g169dd74;                 // 0x0169dd74
extern u32   g169dd70;                 // 0x0169dd70
extern f32   g169dcac;                 // 0x0169dcac
extern f32   g169dcb0;                 // 0x0169dcb0
extern f32   g169dcb4;                 // 0x0169dcb4
extern f32   g169dd64;                 // 0x0169dd64
extern f32   g169dd68;                 // 0x0169dd68
extern f32   g169dd6c;                 // 0x0169dd6c
extern void* g169dd28;                 // 0x0169dd28 (SpVector<cCurvePoint> begin)
extern void* g169dd2c;                 // 0x0169dd2c
extern f32   g_HK_REAL_ZERO;           // 0x01485378

// ------------------------------------------------------------ call typedefs
typedef void (__thiscall *VFnV)(void*);
typedef int  (__thiscall *VFnVI)(void*);
typedef void (__thiscall *VFnVi)(void*, int);
typedef void (__thiscall *VFnVii)(void*, int, int);
typedef int  (__thiscall *VFnVii_i)(void*, int, int);
typedef void (__thiscall *VFnVp)(void*, void*);
typedef void (__thiscall *VFnVpp)(void*, void*, void*);
typedef void* (__thiscall *VFnVp_r)(void*);
typedef void (__thiscall *VFnV4)(void*, int, int, int, int);
typedef u32  (__thiscall *VFnV4_i)(void*, int, int, int, int);
typedef void (__thiscall *VFnVFFi)(void*, f32, f32, int);
typedef void (__thiscall *VFnViFFi)(void*, int, f32, f32, int);

// ------------------------------------------------------------------- types
struct IfaceObj {
    void** mpVftable;                  // +0x00
};

struct cGameEditInputStrategy {
    void** mpVftable;                  // +0x00
    u8     mPad04[0x38];               // +0x04 .. +0x3b
    IfaceObj mNested3c;                // +0x3c
};

struct cGameEditDisplayStrategy {
    void** mpVftable;                  // +0x00
};

struct AutoRefVec {
    void*   mpBegin;                   // +0x00
    void*   mpEnd;                     // +0x04
    void*   mpCapacity;                // +0x08
    void    dtorRaw();                 // 0x00ad92d0
    void*   erase(void* first, void* last); // 0x00b48e40
};

struct cPlanetModel {
    u8     mPad00[0x24];               // +0x00 .. +0x23
    void*  mField24;                   // +0x24
};

struct Msg5 {
    void** mpVftable;                  // +0x00
    int    mField04;                   // +0x04
    int    mField08;                   // +0x08
    int    mField0c;                   // +0x0c
    int    mField10;                   // +0x10
    int    mField14;                   // +0x14
    int    mField18;                   // +0x18
    u8     mPad1c[0x14];               // +0x1c .. +0x2f
    int    mField30;                   // +0x30
    Msg5*  ctorRaw(int arg);           // 0x00421c80
};

struct cGameNounManager {
    void** mpVftable;                  // +0x00
    void   RemoveNounsOfType(int type);// 0x00b22650
    void   FUN_00b25fe0();             // 0x00b25fe0
};

struct cGameTimeManager {
    void** mpVftable;                  // +0x00
    void   DecPauseGate(u32 id);       // 0x00b32250
};

namespace SP {

struct cGonzagoSubsystem {
    void** mpVftable0;                 // +0x00
    void** mpVftable4;                 // +0x04
    u8     mPad08[0x14];               // +0x08 .. +0x1b
    void   ctorRaw();                  // 0x00b5b960
    void   dtorRaw();                  // 0x00b5b9a0
};

struct cGameEditModeStrategy {
    void**               mpVftable0;          // +0x00  cIModeStrategy
    void**               mpVftable4;          // +0x04  IHandler
    cGonzagoSubsystem    mBase;               // +0x08  cGonzagoSubsystem (0x1c)
    cGameEditInputStrategy*  mpInputStrategy; // +0x24
    cGameEditDisplayStrategy* mpDisplayStrategy;// +0x28
    void*                mpServer;            // +0x2c
    void*                mpHandler;           // +0x30
    void*                mpIdArray;           // +0x34
    u32                  mnIdArrayCount;      // +0x38
    u32                  mnPriority;          // +0x3c
    AutoRefVec           mSelectableMembers;   // +0x40

    cGameEditModeStrategy();                                  // 0x00d1c150
    ~cGameEditModeStrategy();                                 // 0x00d1c200

    void FUN_00d1c010();                                      // 0x00d1c010
    void FUN_00d1c0a0(f32 a, f32 b, int c);                   // 0x00d1c0a0
    void FUN_00d1c0d0(int a, f32 b, f32 c, int d);            // 0x00d1c0d0
    void OnKeyUp();                                           // 0x00d1c090
    u8   Init(int unused);                                    // 0x00d1c100
    u8   FUN_00d1c2e0(int key, int state);                    // 0x00d1c2e0
    u8   FUN_00d1c400(int a, f32 b, f32 c, int d);            // 0x00d1c400
    u8   Shutdown();                                          // 0x00d1c5d0
    u32  SaveScenario();                                      // 0x00d1cb00
};

// view of the object as its +0x08 cIGonzagoSubsystem subobject (this == object+0x08)
struct cGameEditModeStrategyGz {
    void**      mpVftable0;            // +0x00  cIGonzagoSubsystem
    void**      mpVftable4;            // +0x04  RefCountTemplate
    u8          mPad08[0x30];          // +0x08 .. +0x37
    AutoRefVec  mMembers;              // +0x38  (== object+0x40)
    void FUN_00d1c560(int guard, int mode);   // 0x00d1c560
    void FUN_00d1c9e0(int guard, void* mode); // 0x00d1c9e0
};

}  // namespace SP

// ===========================================================================
// SP::cGameEditModeStrategy::cGameEditModeStrategy
// ===========================================================================
// @ 0x00d1c150
SP::cGameEditModeStrategy::cGameEditModeStrategy()
{
    mpVftable0 = (void**)&vtbl_1477530;
    mpVftable4 = (void**)&vtbl_13eb384;
    mBase.ctorRaw();
    mpInputStrategy = 0;
    mpDisplayStrategy = 0;
    mpVftable0 = (void**)&vtbl_1479f20;
    mpVftable4 = (void**)&vtbl_1479f10;
    mBase.mpVftable0 = (void**)&vtbl_1479ec0;
    mBase.mpVftable4 = (void**)&vtbl_1479eb8;
    mpServer = 0;
    mpHandler = 0;
    mpIdArray = 0;
    mnIdArrayCount = 0;
    mnPriority = 0;
    mSelectableMembers.mpBegin = 0;
    mSelectableMembers.mpEnd = 0;
    mSelectableMembers.mpCapacity = 0;
    g_sInstance = this;
}

// ===========================================================================
// SP::cGameEditModeStrategy::~cGameEditModeStrategy
// ===========================================================================
// @ 0x00d1c200
SP::cGameEditModeStrategy::~cGameEditModeStrategy()
{
    mpVftable0 = (void**)&vtbl_1479f20;
    mpVftable4 = (void**)&vtbl_1479f10;
    mBase.mpVftable0 = (void**)&vtbl_1479ec0;
    mBase.mpVftable4 = (void**)&vtbl_1479eb8;
    g_sInstance = 0;
    mSelectableMembers.dtorRaw();
    if (mpServer != 0) {
        EA_Messaging_RemoveHandler(mpServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
        mpServer = 0;
    }
    mBase.dtorRaw();
    mpVftable4 = (void**)&vtbl_13eb394;
    mpVftable0 = (void**)&vtbl_13eb938;
}

// ===========================================================================
// FUN_00d1c010  (cIModeStrategy slot +0x1c -- Deactivate)
// ===========================================================================
// @ 0x00d1c010
void SP::cGameEditModeStrategy::FUN_00d1c010()
{
    ((VFnV)mpInputStrategy->mNested3c.mpVftable[2])(&mpInputStrategy->mNested3c);
    ((VFnV)mpInputStrategy->mpVftable[3])(mpInputStrategy);
    ((VFnV)mpInputStrategy->mNested3c.mpVftable[3])(&mpInputStrategy->mNested3c);
    cGameEditDisplayStrategy* disp = mpDisplayStrategy;
    mpInputStrategy = 0;
    if (disp != 0)
        ((VFnVi)disp->mpVftable[0])(disp, 1);
    mpDisplayStrategy = 0;
    ((cGameTimeManager*)GameTimeManager())->DecPauseGate(0x4bf38a7);
}

// ===========================================================================
// FUN_00d1c0a0  (cIModeStrategy slot +0x34)
// ===========================================================================
// @ 0x00d1c0a0
void SP::cGameEditModeStrategy::FUN_00d1c0a0(f32 a, f32 b, int c)
{
    void* m = GameInputManager();
    ((VFnVFFi)VFN(m, 0x5c))(m, a, b, c);
}

// ===========================================================================
// FUN_00d1c0d0  (cIModeStrategy slot +0x38)
// ===========================================================================
// @ 0x00d1c0d0
void SP::cGameEditModeStrategy::FUN_00d1c0d0(int a, f32 b, f32 c, int d)
{
    void* m = GameInputManager();
    ((VFnViFFi)VFN(m, 0x60))(m, a, b, c, d);
}

// ===========================================================================
// SP::cGameEditModeStrategy::OnKeyUp
// ===========================================================================
// @ 0x00d1c090
void SP::cGameEditModeStrategy::OnKeyUp()
{
    void* m = GameInputManager();
    void** vt = *(void***)m;
    ((VFnV)vt[0x50 / 4])(m);
}

// ===========================================================================
// SP::cGameEditModeStrategy::Init
// ===========================================================================
// @ 0x00d1c100
u8 SP::cGameEditModeStrategy::Init(int unused)
{
    void* server = EA_Messaging_GetServer();
    void* handler = (this != 0) ? (void*)&mpVftable4 : 0;
    mpServer = server;
    mpHandler = handler;
    mpIdArray = &g1582738;
    mnIdArrayCount = 1;
    mnPriority = 0;
    if (server != 0 && handler != 0)
        ((VFnVpp)VFN(server, 0x24))(server, handler, (void*)g1582738);
    return 1;
}

// ===========================================================================
// FUN_00d1c2e0  (cIModeStrategy slot +0x24 -- OnKeyDown)
// ===========================================================================
// @ 0x00d1c2e0
u8 SP::cGameEditModeStrategy::FUN_00d1c2e0(int key, int state)
{
    if (state == 1 && key == 0x45) {
        cPlanetModel* model = (cPlanetModel*)PlanetModel();
        i32* p = (i32*)model->mField24;
        if (p != 0) {
            i32* r = (i32*)((VFnVI)VFN(p, 8))(p);
            if (r != 0)
                ((VFnV)VFN(r, 0))(r);
            i32 local[3];
            local[0] = 0;
            local[1] = 0;
            local[2] = 0;
            u8 ok = GetPropertyAsKey(r, 0x3d03f84, local);
            if (ok) {
                Msg5* alloc = (Msg5*)operator_new(0x40, (const char*)0x13ebc58, 0, 0, 0, 0);
                Msg5* msg = (alloc != 0) ? alloc->ctorRaw(0) : (Msg5*)0;
                if (msg != 0)
                    ((VFnV)VFN(msg, 4))(msg);
                msg->mField30 = 0x3d7106b;
                msg->mField08 = local[0];
                msg->mField10 = local[2];
                msg->mField18 = ((VFnVI)VFN(p, 0x18))(p);
                i32* srv = (i32*)MessageServer();
                ((VFnV4)VFN(srv, 0x18))(srv, msg->mField30, (int)msg, 0, 0);
                ((VFnV)VFN(msg, 8))(msg);
            }
            if (r != 0)
                ((VFnV)VFN(r, 4))(r);
        }
        return 1;
    }
    void* m = GameInputManager();
    return (u8)((VFnVii_i)VFN(m, 0x4c))(m, key, state);
}

// ===========================================================================
// FUN_00d1c400  (cIModeStrategy slot +0x2c -- OnMouseDown)
// ===========================================================================
// @ 0x00d1c400
u8 SP::cGameEditModeStrategy::FUN_00d1c400(int a, f32 b, f32 c, int d)
{
    if ((g169dd74 & 1) == 0)
        g169dd74 |= 1;
    void* mgr = FUN_00b3d240();
    f32 vx = g169dcac;
    f32 vy = g169dcb0;
    f32 vz = g169dcb4;
    f32 out[3];
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    ((VFnVp)VFN(mgr, 0x38))(mgr, out);
    if (out[0] * out[0] + vx * vx + vy * vy > g_HK_REAL_ZERO && ((d & 1) != 0)) {
        if (g169dd70 == 0) {
            g169dd64 = vx;
            g169dd68 = vy;
            g169dd6c = vz;
        } else {
            FUN_00ac4570(g169dd28, g169dd2c, 0);
            FUN_00b3d290((const char*)0x1565b54, &g169dd64, out, &g169dd28, 0.0f, 1.0f);
            FUN_00ac6960(0);
        }
        g169dd70 = (g169dd70 + 1) & 0x80000001;
        return 1;
    }
    void* m = GameInputManager();
    u32 r = ((VFnV4_i)VFN(m, 0x54))(m, a, (int)out[1], (int)out[2], d);
    return (u8)r;
}

// ===========================================================================
// FUN_00d1c560  (cIGonzagoSubsystem slot +0x14 -- PreGameModeTransition)
// this == object+0x08
// ===========================================================================
// @ 0x00d1c560
void SP::cGameEditModeStrategyGz::FUN_00d1c560(int guard, int mode)
{
    if (((VFnVI)mpVftable0[0x1c / 4])(this) != mode) {
        ((VFnVi)mpVftable0[0x40 / 4])(this, mode);
        if (guard == 0x1654c06) {
            void* cur = GetGameTerrainCursor();
            ((VFnVi)VFN(cur, 0x58))(cur, 0);
            mMembers.erase(mMembers.mpBegin, mMembers.mpEnd);
            if (mode == -1 || mode == 0x2ccd1d2) {
                void* pm = PlanetModel();
                FUN_00b8c0f0(pm);
            }
        }
        ((VFnV)mpVftable0[0x48 / 4])(this);
    }
}

// ===========================================================================
// SP::cGameEditModeStrategy::Shutdown
// ===========================================================================
// @ 0x00d1c5d0
u8 SP::cGameEditModeStrategy::Shutdown()
{
    mSelectableMembers.erase(mSelectableMembers.mpBegin, mSelectableMembers.mpEnd);
    if (mpServer != 0) {
        EA_Messaging_RemoveHandler(mpServer, mpHandler, mpIdArray, mnIdArrayCount, mnPriority);
        mpServer = 0;
    }
    return 1;
}

// ===========================================================================
// FUN_00d1c9e0  (cIGonzagoSubsystem slot +0x18 -- PostGameModeTransition)
// this == object+0x08
// ===========================================================================
// @ 0x00d1c9e0
void SP::cGameEditModeStrategyGz::FUN_00d1c9e0(int guard, void* mode)
{
    if (((VFnVp_r)mpVftable0[0x20 / 4])(this) == mode)
        return;
    ((VFnVp)mpVftable0[0x44 / 4])(this, mode);
    if (guard == 0x1654c06) {
        if (mode != (void*)0x1654c06)
            goto after;
    } else if (mode != (void*)0x1654c06) {
        ((VFnV)mpVftable0[0x4c / 4])(this);
        return;
    }
    {
        void* eff = EffectsManagerPtr();
        ((VFnVii)VFN(eff, 0x98))(eff, 8, 1);
        ((cGameNounManager*)NounManager())->RemoveNounsOfType(0x36be27e);
        if (g15826ac != g15826b0)
            FUN_00d1c610((int)FNV1_String16(g15826ac, 0x811c9dc5, 1), 1);
        void* cur = GetGameTerrainCursor();
        ((VFnVp)VFN(cur, 0x58))(cur, &mMembers);
        ((VFnV)mpVftable0[0x4c / 4])(this);
        return;
    }
after:
    if (mode == (void*)-1 || mode == (void*)0x2ccd1d2) {
        ((cGameNounManager*)NounManager())->FUN_00b25fe0();
    } else {
        FUN_00b99670();
        FUN_00b99530(0, 0, 0);
        FUN_00ba1280();
    }
    if (mode != (void*)0x1654c01) {
        void* eff = EffectsManagerPtr();
        ((VFnVii)((void**)eff)[0x98 / 4])(eff, 8, 0);
    }
    ((VFnV)mpVftable0[0x4c / 4])(this);
}

// ===========================================================================
// FUN_00d1c610  -- scenario-record loader (approx; PDB name unreliable)
// ===========================================================================
// @ 0x00d1c610
extern "C" u8 FUN_00d1c610(int hash, int flag)
{
    (void)hash;
    (void)flag;
    return 0;
}

// ===========================================================================
// SP::cGameEditModeStrategy::SaveScenario  (approx)
// ===========================================================================
// @ 0x00d1cb00
u32 SP::cGameEditModeStrategy::SaveScenario()
{
    return 0;
}