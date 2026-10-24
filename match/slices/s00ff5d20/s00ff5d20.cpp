// Slice s00ff5d20 -- 0x00ff5d20 .. 0x00ff6a00 (15 functions).
//
// cSPSimPlanetHighLOD cinematic / UFO / artifact entry points plus the small
// trigger-list heap helpers (00ff6570 / 00ff69c0 / 00ff6a00).  6190/6290/62d0
// drop the cCity / glow-effect references the object holds; 6380/63e0 sweep
// the active planet record's zoo-marker resource keys.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;
typedef float          f32;

struct Vec3 { f32 x, y, z; };

// ---------------------------------------------------------------------------
// engine helpers reached by the retail code (address in the comment)
// ---------------------------------------------------------------------------
struct cPlanetModel;
struct cGameNounManager;
struct cTerraformingManager;
struct cTriggerMgr;
struct cMessageServer;
struct cEffectsManager;
struct cSPSimulatorSpaceGame;
struct cSPMissionManager;
struct cMoviePlayer;
struct cCity;

cPlanetModel*          __cdecl FUN_00b3d350();   // 0x00b3d350 SP::PlanetModel
cGameNounManager*      __cdecl FUN_00b3d300();   // 0x00b3d300 SP::NounManager
cTerraformingManager*  __cdecl FUN_00b3d430();   // 0x00b3d430 SP::TerraformingManager
cTriggerMgr*           __cdecl FUN_00b3d4d0();   // 0x00b3d4d0 SP::GetTriggerMgr
cMessageServer*        __cdecl FUN_0067dcc0();   // 0x0067dcc0 MessageServer
cEffectsManager*       __cdecl FUN_0067ddd0();   // 0x0067ddd0 EffectsManagerPtr
cSPSimulatorSpaceGame* __cdecl FUN_00ffbe50();   // 0x00ffbe50 SP::GetUFOSimulator
cSPMissionManager*     __cdecl FUN_00feb9f0();   // 0x00feb9f0 SP::GetMissionManager
cMoviePlayer*          __cdecl FUN_010666a0();   // 0x010666a0
void*                  __cdecl FUN_010212a0();   // 0x010212a0 active planet record
void*                  __cdecl FUN_01021370();   // 0x01021370 player home planet
struct cActivePlanet;
cActivePlanet*         __cdecl FUN_01021260();   // 0x01021260 active planet
u32                    __cdecl FUN_00932e80(const char*, u32, u32); // 0x00932e80 FNVHash
void                   __cdecl FUN_01043c60(void*, const void*);    // 0x01043c60
void                   __cdecl SetZooMarker(void*, const void*, const Vec3*, void*); // 0x01043fd0
Vec3*                  __cdecl Swarm_Normalize(Vec3*, void*);       // 0x006e6df0

extern const f32 g_f13eb1bc;   // 0x13eb1bc
extern const f32 g_f13ec480;   // 0x13ec480  0.2f
extern const f32 g_f1486110;   // 0x1486110  5.0f
extern const f32 g_f1494fb8;   // 0x1494fb8  130.0f
extern const f32 g_f16db418;   // 0x16db418
extern const f32 g_f16db41c;   // 0x16db41c
extern const f32 g_f16db420;   // 0x16db420

struct ResourceKey { u32 k0, k1, k2; };   // 12 bytes

// ---------------------------------------------------------------------------
// small engine object models (vtable slots are the ones the retail code uses)
// ---------------------------------------------------------------------------

// reference-counted object reached through raw vtable slots (0 = AddRef, 4 = Release, c = DecRef)
struct RefObj {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08(u32);
    virtual void* v0c(void*);
};

// city-hall sub-object embedded at cityHall+0x34 (and artifact+0x34)
struct cHallSub {
    virtual void  v00(); virtual void  v04(); virtual void  v08(); virtual void  v0c();
    virtual void  v10(); virtual void  v14(); virtual void  v18(); virtual void  v1c();
    virtual void  v20(); virtual void  v24(); virtual void  v28();
    virtual void* v2c();
    virtual void* v30();
    virtual f32   v34();
    virtual void  v38(Vec3*);
    virtual void  v3c(void*);
    virtual void  v40(); virtual void  v44(); virtual void  v48(); virtual void  v4c();
    virtual void  v50(); virtual void  v54(); virtual void  v58(); virtual void  v5c();
    virtual void  v60(); virtual void  v64(); virtual void  v68(); virtual void  v6c();
    virtual void  v70(); virtual void  v74(); virtual void  v78(); virtual void  v7c();
    virtual void  v80(); virtual void  v84(); virtual void  v88(); virtual void  v8c();
    virtual void  v90(); virtual void  v94(); virtual void  v98(); virtual void  v9c();
    virtual void  va0(); virtual void  va4(); virtual void  va8();
    virtual void* vac();
};

struct cHallSub2 {    // +0x34 sub-object of the player inventory (vtable slot +0x2c takes a float)
    virtual void  v00(); virtual void  v04(); virtual void  v08(); virtual void  v0c();
    virtual void  v10(); virtual void  v14(); virtual void  v18(); virtual void  v1c();
    virtual void  v20(); virtual void  v24(); virtual void  v28();
    virtual void* v2c(f32);
};

// the very same +0x34 sub-object is also reached with an integer payload in the
// cinematic path (slot +0x2c), so a second view of the slot is needed
struct cSub2cU {
    virtual void  v00(); virtual void  v04(); virtual void  v08(); virtual void  v0c();
    virtual void  v10(); virtual void  v14(); virtual void  v18(); virtual void  v1c();
    virtual void  v20(); virtual void  v24(); virtual void  v28();
    virtual void* v2c(u32);
};

struct cCityHall {
    u8        pad00[0x34];
    cHallSub  mSub;                    // +0x34
};

struct cGovernment {
    void FUN_01062e60(u32);            // 0x01062e60
    void FUN_01062e70(u32, void*);     // 0x01062e70
};

struct cCivilization {
    cGovernment* FUN_00bef8e0();       // 0x00bef8e0
};

struct cCity : RefObj {
    cCivilization* GetCivilization();             // 0x00bd9bf0
    cCityHall*     GetCityHall();                 // 0x00bd9b40
    void           FUN_00bd7f70(Vec3*, void*);    // 0x00bd7f70
};

struct cZooMarkerMgr {
    u8           pad00[0x2c];
    u32          mFlags2c;             // +0x2c
    u8           pad30[0xa0];
    ResourceKey* mBegin;               // +0xd0
    ResourceKey* mEnd;                 // +0xd4
};

struct cPlanetModel {
    void  GetRandomSurfacePoint(Vec3*);   // 0x00b84730
    void* FUN_00b81720(void*);            // 0x00b81720
    bool  FUN_00b7e3e0(Vec3*);            // 0x00b7e3e0
    bool  FUN_00b83870(Vec3*);            // 0x00b83870
    void* FUN_00b7f190(void*, void*);     // 0x00b7f190
};

struct cGameNounManager {
    void*  CreateNoun(void*);             // 0x00b20c60
    cCity* FUN_00b25c30();                // 0x00b25c30
};

struct cMoviePlayer { void FUN_01066dd0(); };   // 0x01066dd0

struct cTerraformingManager {
    u32  FUN_00bbc670(u32);               // 0x00bbc670
    void FUN_00bbf2b0(u32);               // 0x00bbf2b0
};

struct cTriggerMgr {
    void setModal(u32);                                   // 0x00ad7e40
    void FUN_00adde90(u32, void*, u32);                   // 0x00adde90
    void PostTrigger(const char*, u32, u32, u32, u32, u32);// 0x00ae0930
};

struct cMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(u32, u32, u32, u32);
};

struct cEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(u32); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(void*); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool v2c(u32, u32, void*);
};

struct cPlayerInventory {
    void FUN_00c37130(u32);               // 0x00c37130
    void FUN_00c3aa40(Vec3*, void*);      // 0x00c3aa40
    void FUN_00c3daa0(f32);               // 0x00c3daa0
    void FUN_00c7e2f0(u32);               // 0x00c7e2f0
    u8        pad000[0x34];
    cHallSub2 m34;                        // +0x34
    u8        pad038[0x5ec];
    u8        m624;                       // +0x624
    u8        pad625[0x8f];
    f32       m6b4;                       // +0x6b4
    f32       m6b8;                       // +0x6b8
};

struct cSPSimulatorSpaceGame {
    cPlayerInventory* GetPlayerInventory();   // 0x00a1ad60
};

struct cMissionList { void** mBegin; void** mEnd; };

struct cSPMission {
    u32   GetMissionID();                 // 0x01030e10
    void* GetTargetPlanet();              // 0x00970b30
    void  FUN_00c485e0();                 // 0x00c485e0
};

struct cSPMissionManager {
    cMissionList* GetMissionList();       // 0x00fedd50
};

struct cActivePlanet {
    void* FUN_008414c0();                 // 0x008414c0
    void  FUN_00c7e2f0(u32);              // 0x00c7e2f0
};

// inventory reached through its vtable slot +0x40 (used by StartUFOCelebration)
struct cInvInner {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(u32, void*);
};

struct Mat3 { f32 m[9]; };

struct TriggerCtx { u32 a, b, c; };   // 12-byte trigger payload

// 0x00434040 -- transform notification handed to the cinematic FX manager
struct XformMsg {
    void ctor();
    u16  mFlags;      // +0x00
    u16  mSequence;   // +0x02
    Vec3 mPos;        // +0x04  (its x slot is re-used as the 1.0 "w" tag)
    u16  mPad10;      // +0x10
    u16  mPad12;      // +0x12
    Mat3 mMat;        // +0x14
};
void __cdecl Matrix3FromQuaternion(f32*, void*);   // 0x0059c190

struct cVisualEffect : RefObj {
    virtual void v10(); virtual void v14();
    virtual void v18(void*);
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(u32, void*);
    virtual void v44(u32, void*, u32);
};

struct cSPPlanetaryArtifact {
    void Set(u8, void*, u16, u32);        // 0x00c74d30
    u8        pad000[0x34];
    cHallSub  mSub;                       // +0x34
    u8        pad038[0x1ec];
    u32       m224;                       // +0x224
    u8        pad228[0x418];
    u32       m640;                       // +0x640
    u8        pad644[0x1a];
    u8        m65e;                       // +0x65e
};

struct cArtifactParams {
    u32 k0;                               // +0x00
    f32 x4;                               // +0x04
    f32 y8;                               // +0x08
    f32 z_c;                              // +0x0c
    u16 w10;                              // +0x10
    u8  b12;                              // +0x12
    u8  pad13[5];
    u32 v18;                              // +0x18
    u8  pad1c[0xc];
    u8  flags28;                          // +0x28
};

struct cSub1e4   { void FUN_007d01d0(u32, u32); };  // 0x007d01d0
struct cField1b0 { void FUN_00ebdc20(void*, f32); };// 0x00ebdc20
struct cSPTimer  { u8 mBytes[0x20]; void Restart(); };// 0x00bc3130

// ---------------------------------------------------------------------------

struct cSPSimPlanetHighLOD {
    void FUN_00ff6190();                       // 0x00ff6190
    void FUN_00ff6290();                       // 0x00ff6290
    void FUN_00ff62d0();                       // 0x00ff62d0
    void FUN_00ff6200();                       // 0x00ff6200
    void FUN_00ff6450(Vec3*);                  // 0x00ff6450
    void FUN_00ff6520(void*, f32);             // 0x00ff6520
    cSPPlanetaryArtifact* SpawnArtifact(cArtifactParams*);   // 0x00ff5d20
    void StartCVG2SPG(u32, u8);                // 0x00ff5ee0
    void ShowUFOForTransition();               // 0x00ff60d0
    void StartUFOCelebration(cCity*);          // 0x00ff65f0

    u8             pad000[0x18];
    cVisualEffect* mp18;                       // +0x18
    cVisualEffect* mp1c;                       // +0x1c
    u8             pad020[0x10];
    cCity*         mpCity;                     // +0x30
    u8             pad034[0x124];
    u8             m158;                       // +0x158
    u8             pad159[3];
    Vec3           m15c;                       // +0x15c
    u32            m168;                       // +0x168
    u8             pad16c[4];
    cSPTimer       mTimer170;                  // +0x170
    f32            m190;                       // +0x190
    f32            m194;                       // +0x194
    f32            m198;                       // +0x198
    u8             pad19c[0x14];
    cField1b0*     mp1b0;                      // +0x1b0
    u8             pad1b4[0x30];
    cSub1e4        m1e4;                       // +0x1e4
};

// ---------------------------------------------------------------------------
// cinematic / artifact entry points
// ---------------------------------------------------------------------------

// @ 0x00ff5d20
cSPPlanetaryArtifact* cSPSimPlanetHighLOD::SpawnArtifact(cArtifactParams* pm)
{
    cPlanetModel* mdl = FUN_00b3d350();
    RefObj* noun = (RefObj*)FUN_00b3d300()->CreateNoun((void*)0x2dd8c42);
    if (noun == 0)
        return 0;
    cSPPlanetaryArtifact* art = (cSPPlanetaryArtifact*)noun->v0c((void*)0x2dd8c33);
    if (art != 0) {
        ResourceKey key;
        key.k0 = pm->k0;
        key.k1 = 0;
        key.k2 = 0;
        art->Set(pm->b12, &key, pm->w10, (pm->flags28 >> 1) & 1);
        art->m640 = pm->v18;
        Vec3 v = { g_f16db418, g_f16db41c, g_f16db420 };
        if (pm->x4 == g_f16db418 && pm->y8 == g_f16db41c && pm->z_c == g_f16db420) {
            for (u32 i = 0; i < 100; i++) {
                Vec3* p = (Vec3*)mdl->FUN_00b81720(&key);
                v = *p;
                if (mdl->FUN_00b7e3e0(&v))
                    continue;
                if (!mdl->FUN_00b83870(&v))
                    break;
            }
        } else {
            v.x = pm->x4;
            v.y = pm->y8;
            v.z = pm->z_c;
        }
        pm->x4  = v.x;
        pm->y8  = v.y;
        pm->z_c = v.z;
        cHallSub* sub = (cHallSub*)((char*)art + 0x34);
        sub->v38(&v);
        void* ori = mdl->FUN_00b7f190(&key, sub->v2c());
        sub->v3c(ori);
        if (mdl->FUN_00b7e3e0((Vec3*)sub->v2c()))
            art->m224 = 6;
        art->m65e = (pm->flags28 >> 5) & 1;
    }
    return art;
}

// @ 0x00ff5ee0
void cSPSimPlanetHighLOD::StartCVG2SPG(u32 param2, u8 flag)
{
    cCity* city = FUN_00b3d300()->FUN_00b25c30();
    if (city == 0)
        return;
    if (city != mpCity) {
        ((RefObj*)city)->v00();
        cCity* old = mpCity;
        mpCity = city;
        if (old)
            ((RefObj*)old)->v04();
    }
    cPlayerInventory* inv =
        ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    cCityHall* hall = mpCity->GetCityHall();
    if (inv != 0 && hall != 0) {
        cHallSub* sub = (cHallSub*)((char*)hall + 0x34);
        void* r = sub->vac();
        f32 f = sub->v34() * *(f32*)((char*)r + 0x84);
        Vec3 tmp;
        Vec3* n = Swarm_Normalize(&tmp, sub->v2c());
        Vec3* c = (Vec3*)sub->v2c();
        Vec3 off;
        off.x = c->x + n->x * f;
        off.y = c->y + n->y * f;
        off.z = c->z + n->z * f;
        inv->FUN_00c3aa40(&off, sub->v30());
        inv->FUN_00c3daa0(sqrtf(off.x * off.x + off.y * off.y + off.z * off.z) + g_f1486110);
    }
    m1e4.FUN_007d01d0(0x9c377c26, 0);
    u32 h1 = FUN_00932e80("cinematics_spg", 0x811c9dc5, 1);
    u32 h2 = FUN_00932e80("UFOCreateText", 0x811c9dc5, 1);
    TriggerCtx ctx;
    ctx.a = param2;
    ctx.b = 0;
    ctx.c = h1;
    FUN_00b3d4d0()->FUN_00adde90(h2, &ctx, 0);
    if (flag != 0)
        FUN_00b3d4d0()->PostTrigger("CVG2SPG", 1, 0, 0, 0, 0);
    else
        FUN_00b3d4d0()->PostTrigger("CVG2SPG_short", 1, 0, 0, 0, 0);
}

// @ 0x00ff65f0
void cSPSimPlanetHighLOD::StartUFOCelebration(cCity* param)
{
    if (param == 0)
        return;
    if (param != mpCity) {
        ((RefObj*)param)->v00();
        cCity* old = mpCity;
        mpCity = param;
        if (old)
            ((RefObj*)old)->v04();
    }
    if (mp18) {
        mp18->v0c((void*)1);
        if (mp18) {
            cVisualEffect* p = mp18;
            mp18 = 0;
            p->v04();
        }
    }
    if (mp1c) {
        mp1c->v0c((void*)1);
        if (mp1c) {
            cVisualEffect* p = mp1c;
            mp1c = 0;
            p->v04();
        }
    }
    void* home = FUN_01021370();
    cPlayerInventory* inv = 0;
    if (FUN_010212a0() == home)
        inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    cCityHall* hall = mpCity->GetCityHall();
    if (inv != 0 && hall != 0) {
        cHallSub* sub = (cHallSub*)((char*)hall + 0x34);
        void* r = sub->vac();
        f32 f = sub->v34() * *(f32*)((char*)r + 0x84);
        Vec3 tmp;
        Vec3* n = Swarm_Normalize(&tmp, sub->v2c());
        f32 sx = n->x * f;
        f32 sy = n->y * f;
        f32 sz = n->z * f;
        Vec3* c = (Vec3*)sub->v2c();
        Vec3 off;
        off.x = c->x + sx;
        off.y = c->y + sy;
        off.z = c->z + sz;
        inv->FUN_00c3aa40(&off, sub->v30());
        inv->FUN_00c3daa0(sqrtf(off.x * off.x + off.y * off.y + off.z * off.z) + g_f1486110);
    }
    cEffectsManager* em = FUN_0067ddd0();
    if (mp18) {
        cVisualEffect* p = mp18;
        mp18 = 0;
        p->v04();
    }
    if (em->v2c(0x60713c20, 0, &mp18)) {
        cCityHall* hall2 = mpCity->GetCityHall();
        if (hall2 != 0) {
            cHallSub* sub = (cHallSub*)((char*)hall2 + 0x34);
            XformMsg m1;
            m1.ctor();
            m1.mPos = *(Vec3*)sub->v2c();
            m1.mFlags |= 4;
            m1.mSequence++;
            Mat3 rot;
            Matrix3FromQuaternion(rot.m, sub->v30());
            m1.mMat = rot;
            m1.mFlags |= 2;
            m1.mSequence++;
            m1.mPos.x = 1.0f;                  // re-uses the +0x04 slot as the scale tag
            ((cInvInner*)inv)->v40(9, ((cSub2cU*)((char*)inv + 0x34))->v2c(1));
            mp18->v44(10, &m1, 1);
            mp18->v18(&m1);
            mp18->v08(0);
            cCivilization* civ = mpCity->GetCivilization();
            if (civ != 0) {
                cGovernment* gov = civ->FUN_00bef8e0();
                if (gov != 0)
                    gov->FUN_01062e60(1);
            }
            cEffectsManager* em2 = FUN_0067ddd0();
            if (mp1c) {
                cVisualEffect* p = mp1c;
                mp1c = 0;
                p->v04();
            }
            if (em2->v2c(0x5dd13c64, 0, &mp1c)) {
                XformMsg m2;
                m2.ctor();
                m2.mPos = *(Vec3*)((cHallSub*)((char*)inv + 0x34))->v2c();
                m2.mFlags |= 4;
                m2.mSequence++;
                Mat3 rot2;
                Matrix3FromQuaternion(rot2.m, sub->v30());
                m2.mMat = rot2;
                m2.mFlags |= 2;
                m2.mSequence++;
                mp1c->v18(&m2);
                mp1c->v08(0);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// heap helpers for the trigger list (signed int payloads)
// ---------------------------------------------------------------------------

// @ 0x00ff6570
void __cdecl FUN_00ff6570(int* a, int lo, int n, int i, int v)
{
    int j = i * 2 + 2;
    int c;
    while (j < n) {
        c = a[j];
        if (c < a[j - 1])
            c = a[--j];
        a[i] = c;
        i = j;
        j = j * 2 + 2;
    }
    if (j == n) {
        a[i] = a[j - 1];
        i = j - 1;
    }
    while (i > lo) {
        int p = (i - 1) >> 1;
        c = a[p];
        if (c >= v)
            break;
        a[i] = c;
        i = p;
    }
    a[i] = v;
}

// @ 0x00ff69c0
void __cdecl FUN_00ff69c0(u32* begin, u32* end)
{
    int count = (int)(end - begin);
    if (count >= 2)
        for (int i = (count - 2) >> 1; i >= 0; --i)
            FUN_00ff6570((int*)begin, i, count, i, (int)begin[i]);
}

// @ 0x00ff6a00
void __cdecl FUN_00ff6a00(u32* begin, u32* end)
{
    int count = (int)(end - begin);
    if (count > 1) {
        u32* p = end - 1;
        do {
            u32 v = *p;
            *p = *begin;
            FUN_00ff6570((int*)begin, 0, --count, 0, (int)v);
            --p;
        } while (count > 1);
    }
}

// ---------------------------------------------------------------------------
// zoo-marker sweeps
// ---------------------------------------------------------------------------

// @ 0x00ff6380
void __cdecl FUN_00ff6380()
{
    cPlanetModel*  pm  = FUN_00b3d350();
    cZooMarkerMgr* mgr = (cZooMarkerMgr*)FUN_010212a0();
    for (ResourceKey* it = mgr->mBegin; it != mgr->mEnd; ++it) {
        Vec3 pt;
        pm->GetRandomSurfacePoint(&pt);
        SetZooMarker(mgr, it, &pt, 0);
    }
}

// @ 0x00ff63e0
void __cdecl FUN_00ff63e0()
{
    FUN_00b3d350();
    cZooMarkerMgr* mgr = (cZooMarkerMgr*)FUN_010212a0();
    for (ResourceKey* it = mgr->mBegin; it != mgr->mEnd; ++it)
        FUN_01043c60(mgr, it);
    mgr->mFlags2c &= 0xfffff7ff;
    FUN_0067dcc0()->v18(0x490d429, 0, 0, 0);
    FUN_00b3d430()->FUN_00bbf2b0(0);
}

// ---------------------------------------------------------------------------
// small release / policy helpers
// ---------------------------------------------------------------------------

// @ 0x00ff6190
void cSPSimPlanetHighLOD::FUN_00ff6190()
{
    FUN_010666a0()->FUN_01066dd0();
    if (mpCity) {
        cCivilization* civ = mpCity->GetCivilization();
        if (civ) {
            cGovernment* gov = civ->FUN_00bef8e0();
            if (gov)
                gov->FUN_01062e60(0);
        }
    }
    cPlayerInventory* inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    if (inv)
        inv->FUN_00c37130(1);
    if (mpCity) {
        cCity* p = mpCity;
        mpCity = 0;
        p->v04();
    }
}

// @ 0x00ff6290
void cSPSimPlanetHighLOD::FUN_00ff6290()
{
    if (mpCity) {
        cCivilization* civ = mpCity->GetCivilization();
        if (civ) {
            cGovernment* gov = civ->FUN_00bef8e0();
            if (gov)
                gov->FUN_01062e60(0);
        }
    }
    if (mpCity) {
        cCity* p = mpCity;
        mpCity = 0;
        p->v04();
    }
}

// @ 0x00ff62d0
void cSPSimPlanetHighLOD::FUN_00ff62d0()
{
    if (mp18) {
        mp18->v0c((void*)1);
        if (mp18) {
            cVisualEffect* p = mp18;
            mp18 = 0;
            p->v04();
        }
    }
    if (mp1c) {
        mp1c->v0c((void*)1);
        if (mp1c) {
            cVisualEffect* p = mp1c;
            mp1c = 0;
            p->v04();
        }
    }
    FUN_00b3d4d0()->setModal(0);
    cPlayerInventory* inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    if (inv)
        inv->FUN_00c37130(1);
    FUN_010666a0()->FUN_01066dd0();
}

// @ 0x00ff6200
void cSPSimPlanetHighLOD::FUN_00ff6200()
{
    void* active = FUN_010212a0();
    cPlayerInventory* inv = 0;
    if (active == FUN_01021370()) {
        inv = ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
        FUN_010666a0()->FUN_01066dd0();
    }
    FUN_00b3d4d0()->setModal(0);
    if (inv) {
        inv->FUN_00c37130(1);
        if (mpCity) {
            cCivilization* civ = mpCity->GetCivilization();
            if (civ) {
                cGovernment* gov = civ->FUN_00bef8e0();
                if (gov) {
                    cHallSub2* sub = (cHallSub2*)((char*)inv + 0x34);
                    gov->FUN_01062e70(5, sub->v2c(g_f13eb1bc));
                }
            }
        }
    }
}

// @ 0x00ff6450
void cSPSimPlanetHighLOD::FUN_00ff6450(Vec3* v)
{
    m158 = 1;
    m15c = *v;
    mTimer170.Restart();
    m168 = FUN_00b3d430()->FUN_00bbc670(0);
    m198 = 0.0f;
    m194 = 0.0f;
    m190 = 0.0f;
    void* y = FUN_01021260()->FUN_008414c0();
    if (y != 0)
        ((cActivePlanet*)y)->FUN_00c7e2f0(0);
    cMissionList* list = FUN_00feb9f0()->GetMissionList();
    for (void** it = list->mBegin; it != list->mEnd; ++it) {
        cSPMission* m = (cSPMission*)*it;
        if (m->GetMissionID() == 0x311cc10f) {
            if ((void*)m->GetTargetPlanet() == (void*)FUN_01021260())
                m->FUN_00c485e0();
        }
    }
}

// @ 0x00ff6520
void cSPSimPlanetHighLOD::FUN_00ff6520(void* obj, f32 x)
{
    void* p = obj ? (void*)((char*)obj + 0x508) : 0;
    mp1b0->FUN_00ebdc20(p, x);
}

// @ 0x00ff60d0
void cSPSimPlanetHighLOD::ShowUFOForTransition()
{
    cPlayerInventory* inv =
        ((cSPSimulatorSpaceGame*)FUN_00ffbe50())->GetPlayerInventory();
    if (inv == 0)
        return;
    cCity* city = FUN_00b3d300()->FUN_00b25c30();
    cCityHall* hall = city ? city->GetCityHall() : 0;
    Vec3 v;
    u32  unk;
    city->FUN_00bd7f70(&v, &unk);
    inv->m624 = 1;
    cHallSub* sub = (cHallSub*)((char*)hall + 0x34);
    inv->FUN_00c3aa40(&v, sub->v30());
    inv->FUN_00c3daa0(sqrtf(v.z * v.z + v.x * v.x + v.y * v.y) + g_f1494fb8);
    inv->FUN_00c37130(1);
    f32 c = g_f13ec480;
    inv->m6b4 = c;
    inv->m6b8 = c;
}