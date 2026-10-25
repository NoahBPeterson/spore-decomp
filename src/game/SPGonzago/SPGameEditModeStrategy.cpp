// src/game/SPGonzago/SPGameEditModeStrategy.cpp -- migrated from slice(s) s00d1cdf0, s00d1c010 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameEditModeStrategy.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameEditInputStrategy.h"
#include "SP/cGameNounManager.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cPlanetModel.h"
#include "SP/cGameData.h"
#include "SP/cRotationRing.h"
#include "cSPUILayout.h"
#include "SP/cSpatialObject.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  *GameInputManager();                                   // 0x00b3d250
extern "C" void  *GameTimeManager();                                    // 0x00b3d380
extern "C" void  *EA_Messaging_GetServer();                             // 0x00883860
extern "C" void  *PlanetModel();                                        // 0x00b3d350
extern "C" void  *MessageServer();                                      // 0x0067dcc0
extern "C" void  *GetGameTerrainCursor();                               // 0x00b30d70
extern "C" void   __fastcall FUN_00b8c0f0(void*);                       // 0x00b8c0f0
extern void* g_sInstance;              // 0x0169dca8

// ---- items of slice s00d1c010 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
#define VFN(p, byteOff)  (((void**)(*(void**)(p)))[(byteOff) / 4])
extern "C" void  *GameInputManager();                                   // 0x00b3d250
extern "C" void  *GameTimeManager();                                    // 0x00b3d380
extern "C" void  *EA_Messaging_GetServer();                             // 0x00883860
extern "C" void   EA_Messaging_RemoveHandler(void*, void*, void*, u32, u32);//0x00571db0
extern "C" void  *PlanetModel();                                        // 0x00b3d350
extern "C" u8     GetPropertyAsKey(void*, u32, void*);                  // 0x006a1250
extern "C" void  *operator_new(u32, const char*, int, int, int, int);   // 0x00f473a0
extern "C" void  *MessageServer();                                      // 0x0067dcc0
extern "C" void  *GetGameTerrainCursor();                               // 0x00b30d70
extern "C" void   __fastcall FUN_00b8c0f0(void*);                       // 0x00b8c0f0
extern u8 vtbl_1477530;   // 0x01477530
extern u8 vtbl_13eb384;   // 0x013eb384
extern u8 vtbl_1479f20;   // 0x01479f20
extern u8 vtbl_1479f10;   // 0x01479f10
extern u8 vtbl_1479ec0;   // 0x01479ec0
extern u8 vtbl_1479eb8;   // 0x01479eb8
extern u8 vtbl_13eb394;   // 0x013eb394
extern u8 vtbl_13eb938;   // 0x013eb938
extern void* g_sInstance;              // 0x0169dca8
extern u32   g1582738;                 // 0x01582738 (message id array[0])
typedef void (__thiscall *VFnV)(void*);
typedef int  (__thiscall *VFnVI)(void*);
typedef void (__thiscall *VFnVi)(void*, int);
typedef int  (__thiscall *VFnVii_i)(void*, int, int);
typedef void (__thiscall *VFnVpp)(void*, void*, void*);
typedef void (__thiscall *VFnV4)(void*, int, int, int, int);
typedef void (__thiscall *VFnVFFi)(void*, f32, f32, int);
typedef void (__thiscall *VFnViFFi)(void*, int, f32, f32, int);
struct IfaceObj {
    void** mpVftable;                  // +0x00
};
struct cGameEditInputStrategy_s00d1_c010 {
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
struct cPlanetModel_s00d1_c010 {
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
struct cGameTimeManager {
    void** mpVftable;                  // +0x00
    void   DecPauseGate(u32 id);       // 0x00b32250
};
namespace SP {
struct cGonzagoSubsystem_s00d1_c010 {
    void** mpVftable0;                 // +0x00
    void** mpVftable4;                 // +0x04
    u8     mPad08[0x14];               // +0x08 .. +0x1b
    void   ctorRaw();                  // 0x00b5b960
    void   dtorRaw();                  // 0x00b5b9a0
};
}
namespace SP {
struct cGameEditModeStrategy {
    void**               mpVftable0;          // +0x00  cIModeStrategy
    void**               mpVftable4;          // +0x04  IHandler
    cGonzagoSubsystem_s00d1_c010    mBase;               // +0x08  cGonzagoSubsystem (0x1c)
    cGameEditInputStrategy_s00d1_c010*  mpInputStrategy; // +0x24
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
}
namespace SP {
struct cGameEditModeStrategyGz {
    void**      mpVftable0;            // +0x00  cIGonzagoSubsystem
    void**      mpVftable4;            // +0x04  RefCountTemplate
    u8          mPad08[0x30];          // +0x08 .. +0x37
    AutoRefVec  mMembers;              // +0x38  (== object+0x40)
    void FUN_00d1c560(int guard, int mode);   // 0x00d1c560
    void FUN_00d1c9e0(int guard, void* mode); // 0x00d1c9e0
};
}
// ---- items of slice s00d1c010 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void   EA_Messaging_RemoveHandler(void*, void*, void*, u32, u32);//0x00571db0
extern "C" u8     GetPropertyAsKey(void*, u32, void*);                  // 0x006a1250
extern "C" void  *operator_new(u32, const char*, int, int, int, int);   // 0x00f473a0
extern u8 vtbl_1477530;   // 0x01477530
extern u8 vtbl_13eb384;   // 0x013eb384
extern u8 vtbl_1479f20;   // 0x01479f20
extern u8 vtbl_1479f10;   // 0x01479f10
extern u8 vtbl_1479ec0;   // 0x01479ec0
extern u8 vtbl_1479eb8;   // 0x01479eb8
extern u8 vtbl_13eb394;   // 0x013eb394
extern u8 vtbl_13eb938;   // 0x013eb938
extern u32   g1582738;                 // 0x01582738 (message id array[0])

// ---- items of slice s00d1cdf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gDefVec_169dd88;    // 0x0169dd88  default (1,0,0)-ish vector
extern float gDefVec_169dd8c;    // 0x0169dd8c
extern float gDefVec_169dd90;    // 0x0169dd90
extern void* gListSrcA;              // 0x00cd7d10
extern void* gListSrcB;              // 0x00d3d420
extern void* gListSrcC;              // 0x00ace070
extern void* gListSrcD;              // 0x00b1e500
extern void* FUN_00b3d230(void);                 // SP::NounManager / App
extern void* FUN_00b3d240(void);
extern void* FUN_00b3d320(void);
extern void  FUN_00b3d3b0(void);
extern void  FUN_00b3d3b0v(void*);
extern void  FUN_00b3d3c0(void);
extern void  FUN_00b3d440(void*);
extern void  FUN_00b3d440x(void);
extern void  FUN_00b2ed10(void);
extern void  FUN_00b2f140(void);
extern void  FUN_00b781d0(void);
extern void  FUN_00b2ec80(void*);
extern void  FUN_00b2f350(void*);
extern void  FUN_00b01db0(void*);
extern void  FUN_00b0b150(void);
extern void  FUN_00b79aa0(void);
extern void* FUN_00b5b820(void);
extern void* FUN_00bc30b0(void);
extern char  FUN_00b7ec40(void);
extern void  FUN_00bc2f00(float, float*);
extern void  FUN_00b76d20(float*, void*, void*, void*, void*);
extern void  FUN_00b5e9a0(void*);
extern void  FUN_00bc40f0(void*);
extern void  FUN_00c83c90(void*, void*, void*);
extern char  FUN_00dc6640(void*, void*);
extern void  FUN_00bab900(void*, void*);
extern void* SP_PlanetModel(void);
extern void* SP_App(void);
extern void* SP_GetCurrentGameMode(void);
extern void* SP_GetGameDataVector(void*, void*, void*, void*, void*, int);
extern void  FUN_00ba0770v(void*);
extern void  FUN_00b0c1(void*);
extern float gDefVec_169dd94;
extern float gCached_169dd78;
extern float gCached_169dd7c;
extern float gCached_169dd80;
extern void* sLastLoadedScenario;
extern void* FUN_00f48a80(void);                 // 0x00f48a80
extern void* FUN_00401090(void);                 // 0x00401090
extern void* FUN_004df420(void);                 // 0x004df420
extern void  FUN_004cea40(void*, int, void*);    // 0x004cea40
extern int   FUN_004dff50(void*, int, int, int, int); // 0x004dff50
extern void  FUN_00b8d8a0(void*, void*, void*);  // 0x00b8d8a0
extern void* FUN_0067dd50(void);
extern void  SP_SetAvatarSpecies(void*, void*);
extern void* SP_PlanetModelKey(void*);
typedef unsigned int   uint;
extern uint  gEditState_169dca4; // 0x0169dca4
typedef void   (__thiscall *VFn0) (void*);
typedef void*  (__thiscall *VFnR) (void*);
typedef void   (__thiscall *VFn1) (void*, void*);
typedef void*  (__thiscall *VFnR1)(void*, void*);
typedef void   (__thiscall *VFn2) (void*, void*, void*);
typedef int    (__thiscall *VFnI) (void*);
#define VSLOT(o, off) (*(void**)((char*)(*(void**)(o)) + (off)))
struct cGameEditModeStrategy_s00d1_cdf0 {
    u8    mPad_00[0x24];
    void* mp_24;                  // +0x24  input strategy
    void* mp_28;                  // +0x28
    u8    mPad_2c[0x14];
    void** mpVec_40;              // +0x40
    void** mpVecEnd_44;           // +0x44
    void** mpVecCap_48;           // +0x48
    void HandleSimulationUpdate(float dt);
};
void __fastcall SetPlanetInput(void* strategy, void* planet);  // 0x00b3d240-ish
extern uint  gCachedFlag_169dd84;
void __cdecl matrix33_ctor(void* out, const void* up);
static void* inner_24(void* p) { return *(void**)((char*)p + 0x24); }
// ---- items of slice s00d1cdf0 end

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

// @ 0x00d1c090
void SP::cGameEditModeStrategy::OnKeyUp()
{
    void* m = GameInputManager();
    void** vt = *(void***)m;
    ((VFnV)vt[0x50 / 4])(m);
}

// @ 0x00d1c0a0
void SP::cGameEditModeStrategy::FUN_00d1c0a0(f32 a, f32 b, int c)
{
    void* m = GameInputManager();
    ((VFnVFFi)VFN(m, 0x5c))(m, a, b, c);
}

// @ 0x00d1c0d0
void SP::cGameEditModeStrategy::FUN_00d1c0d0(int a, f32 b, f32 c, int d)
{
    void* m = GameInputManager();
    ((VFnViFFi)VFN(m, 0x60))(m, a, b, c, d);
}

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

// @ 0x00d1c2e0
u8 SP::cGameEditModeStrategy::FUN_00d1c2e0(int key, int state)
{
    if (state == 1 && key == 0x45) {
        cPlanetModel_s00d1_c010* model = (cPlanetModel_s00d1_c010*)PlanetModel();
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

// @ 0x00d1cdf0
void cGameEditModeStrategy_s00d1_cdf0::HandleSimulationUpdate(float dt)
{
    float q2[3];
    int ms = (int)(dt * 1000.0f);
    void* nm = FUN_00b3d230();
    void* list = SP_GetGameDataVector(nm, gListSrcA, gListSrcB, gListSrcC, gListSrcD, 0x36be27e);
    void** begin = *(void***)((char*)list + 4);
    void** end   = *(void***)((char*)list + 8);
    if ((((char*)mpVecEnd_44 - (char*)mpVec_40) ^ ((char*)end - (char*)begin)) & ~3u) {
        for (void** it = begin; it != end; ++it) {
            void* obj = *it;
            if (obj && !(*(VFnI)VSLOT(obj, 0x2c))(obj)
                && !FUN_00dc6640(&mpVec_40, &ms)) {
                void* sp = (void*)((char*)obj + 0x34);
                if (sp) (*(VFn0)VSLOT(sp, 0xbc))(sp);
                void** e = mpVecEnd_44;
                if (e < mpVecCap_48) {
                    mpVecEnd_44 = e + 1;
                    if (e) {
                        *e = sp;
                        if (sp) (*(VFn0)VSLOT(sp, 0xbc))(sp);
                    }
                } else {
                    FUN_00bab900(e, &sp);
                }
                if (sp) (*(VFn0)VSLOT(sp, 0xc0))(sp);
            }
        }
    }
    void** it = mpVec_40;
    if (it != mpVecEnd_44) {
        void** nx = it + 1;
        do {
            void* o = *it;
            void* t = 0;
            if (o) t = (void*)(*(VFnR1)VSLOT(o, 0xb8))(o, (void*)0x17f243b);
            if (!o || !t || (*(VFnI)VSLOT(t, 0x2c))(t)) {
                if (nx < mpVecEnd_44) FUN_00c83c90(nx, mpVecEnd_44, it);
                mpVecEnd_44 = (void**)((char*)mpVecEnd_44 - 4);
                void* last = *mpVecEnd_44;
                if (last) (*(VFn0)VSLOT(last, 0xc0))(last);
            } else {
                ++it; ++nx;
            }
        } while (it != mpVecEnd_44);
    }
    if (gEditState_169dca4 == 1) {
        FUN_00b3d3b0();
        FUN_00b2ed10();
        FUN_00b3d3b0();
        FUN_00b2f140();
        FUN_00b3d440x();
        FUN_00b0c1(0);
        FUN_00b3d3c0();
        FUN_00b781d0();
        gEditState_169dca4 = 2;
    } else if (gEditState_169dca4 == 2) {
        gEditState_169dca4 = 3;
    } else if (gEditState_169dca4 == 3) {
        void* input = mp_24;
        void* planet = SP_PlanetModel();
        if (input && *(void**)((char*)planet + 0x24) != 0) {
            void* pm = (*(VFnR)VSLOT(*(void**)((char*)planet + 0x24), 8))(*(void**)((char*)planet + 0x24));
            if (*(int*)((char*)pm + 0xc) != 0)
                SetPlanetInput(input, (char*)pm + 8);
        }
        FUN_00b3d3b0();
        FUN_00b2ec80(0);
        void* m = FUN_00b5b820();
        FUN_00b3d3b0v(m);
        FUN_00b2f350(m);
        void* gm = SP_GetCurrentGameMode();
        FUN_00b3d440(gm);
        FUN_00b01db0(gm);
        FUN_00b3d440x();
        FUN_00b0b150();
        FUN_00b3d3c0();
        FUN_00b79aa0();
        gEditState_169dca4 = 0;
        FUN_00ba0770v(FUN_00b5b820());
    }
    int have = (int)FUN_00bc30b0();
    if (have != 0) {
        SP_PlanetModel();
        if (FUN_00b7ec40()) {
            float f34 = gDefVec_169dd88;
            float f30 = gDefVec_169dd8c;
            float f2c = gDefVec_169dd90;
            float q[4];
            q[0] = 0.0f; q[1] = f34; q[2] = 0.0f; q[3] = f30;
            float tmp = 0.0f;
            matrix33_ctor(&tmp, &gDefVec_169dd94);
            FUN_00bc40f0(q);
            float vec[3]; vec[0] = f34; vec[1] = f30; vec[2] = f2c;
            if ((gCachedFlag_169dd84 & 1) == 0) {
                gCachedFlag_169dd84 |= 1;
                gCached_169dd78 = f34; gCached_169dd7c = f30; gCached_169dd80 = f2c;
            }
            if ((f34 != gDefVec_169dd88 || f30 != gDefVec_169dd8c || f2c != gDefVec_169dd90)
                && (f34 != gCached_169dd78 || f30 != gCached_169dd7c || f2c != gCached_169dd80)) {
                gCached_169dd78 = f34; gCached_169dd7c = f30; gCached_169dd80 = f2c;
                void* b = FUN_00bc30b0();
                float half = *(float*)((char*)b + 0x24) * 0.5f;
                FUN_00bc2f00(half, &tmp);
            }
        }
    }
    void** app = (void**)FUN_00b3d240();
    (*(VFn1)VSLOT(app, 0x44))(app, (void*)1);
    FUN_00b76d20(q2, (void*)0x3f800000, (void*)7, 0, (void*)1);
    void* x = FUN_00b3d230();
    (*(VFn0)VSLOT(x, 0x2c))(x);
    (*(VFn1)VSLOT(mp_28, 4))(mp_28, 0);
    (*(VFn2)VSLOT(mp_24, 8))(mp_24, 0, 0);
    void* y = FUN_00b3d230();
    (*(VFn0)VSLOT(y, 0x30))(y);
    FUN_00b3d230();
    FUN_00b5e9a0(0);
}

// @ 0x00d1d2e0
uint FUN_00d1d2e0(int id, void* msg)
{
    if (id != 0x3d7106a)
        return 0;
    void* objA = (void*)(*(VFnR)VSLOT(FUN_00f48a80(), 0x18))(FUN_00f48a80());
    (void)objA;
    void* objB = FUN_00f48a80();
    (*(VFn1)VSLOT(objB, 0x10))(objB, 0);
    (*(VFn1)VSLOT(SP_App(), 0x28))(SP_App(), 0);
    void* x = FUN_00b3d320();
    *(void**)((char*)x + 0x24) = 0;
    SP_PlanetModel();
    FUN_00b8d8a0(0, 0, (void*)1);
    void* pm = SP_PlanetModel();
    void* inner = inner_24(pm);
    (*(VFn1)VSLOT(inner, 0x8c))(inner, FUN_0067dd50());
    gEditState_169dca4 = 1;
    if (sLastLoadedScenario != 0) {
        void* pk = SP_PlanetModelKey(SP_PlanetModel());
        if (pk) goto done;
    }
    SP_PlanetModel();
    FUN_00b8d8a0(0, 0, (void*)1);
    void* pm2 = SP_PlanetModel();
    void* inner2 = inner_24(pm2);
    (*(VFn1)VSLOT(inner2, 0x8c))(inner2, FUN_0067dd50());
    gEditState_169dca4 = 1;
done:
    void* mgr = FUN_00401090();
    void* sp = FUN_004df420();
    if (sp == 0) {
        void* buf = 0;
        FUN_004cea40(&buf, 1, 0);
        if (FUN_004dff50(0, 0xdada0591, 1, 0, 0) != 0)
            SP_SetAvatarSpecies(mgr, buf);
    }
    return 0;
}
