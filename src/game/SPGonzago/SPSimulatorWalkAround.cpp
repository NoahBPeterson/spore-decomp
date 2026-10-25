// src/game/SPGonzago/SPSimulatorWalkAround.cpp -- migrated from slice(s) s01016540 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSimulatorWalkAround.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPTimer.h"
#include "SP/cGameNounManager.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s01016540 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef signed   int   i32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long long u64;
void* __cdecl   SP_NounManager(int p);                  // 0x00b3d300 (ret 4)
void* __cdecl   SP_SimTicker();                         // 0x00b3d330
void   __cdecl  FUN_00572020(void* p, int a);           // 0x00572020 (ret 8)
void   __cdecl  copy_impl(void* first, void* last, void* dst); // 0x006782c0 (ret 0xc)
void*  __cdecl   FUN_00b3d3b0();                        // 0x00b3d3b0
void*  __cdecl   FUN_00b3d420_p();                     // 0x00b3d420 (0-arg getter)
void*  __cdecl   FUN_00401090_p();                     // 0x00401090 (0-arg getter)
void   __cdecl   FUN_00aea5d0(void* end, void* val);    // 0x00aea5d0 (ret 8)
struct Vec3 { float x, y, z; };
struct Mat3 {
    void Assign(const void* src);  // 0x41cb40 ret 4
};
struct SimTimer {                            // cSPTimer, at +0x20
    void  Stop();                            // 0x00bc3110
    void  Restart();                         // 0x00bc3130
    u8    IsRunning();                       // 0x00feba90
    u64   GetElapsed();                      // 0x00bc3190
};
struct cSPSimulatorWalkAround {
    u32   mFlags_0x0;                        // +0x00 (base vptr, unused here)
    u8    pad_04[0xc];
    bool  mIsWalkingAround;                  // +0x10
    void* mpAvatar;                          // +0x14  AutoRefCount<cSPCreatureAnimal>
    void* mpStrategy;                        // +0x18  AutoRefCount<cWalkAroundInputStrategy>
    i32   mBeamingState;                     // +0x1c
    SimTimer mBeamingTimer;                  // +0x20
    u8    pad_24[0x1c];                      // 0x24..0x3f
    float mRescueDelay;                      // +0x40
    void* mpX_44;                            // +0x44
    // eastl::vector<AutoRefCount<...>> at +0x48 (0x14 bytes)
    void** mHighLODPlantsBegin;              // +0x48
    void** mHighLODPlantsEnd;                // +0x4c
    void** mHighLODPlantsCap;                // +0x50
    u8    pad_54[8];                         // 0x54..0x5b
    void** mHighLODObstaclesBegin;           // +0x5c
    void** mHighLODObstaclesEnd;             // +0x60
    void** mHighLODObstaclesCap;             // +0x64
    u8    pad_68[8];                         // 0x68..0x6f

    // members
    void RemoveHighLODPlant(void* plant, char flag);   // 01016540 ret 8
    u8   ClearOldestPlant();                           // 01016630
    void SetHighLODPlant(void* plant);                 // 010166c0 ret 4
    void ShutdownForGame();                            // 010168c0
    void FUN_01016950();                               // 01016950
    void FUN_01016ad0();                               // 01016ad0
    void FUN_01016e50(void* a);                        // 01016e50 ret 4

    // external thiscall callees
    void  RemoveNoun0(void* noun);                     // 0x00b225d0 ret 4
    float FUN_00b7e4d0();                              // 0x00b7e4d0 (planet-model getter)
    void* GetPlayerInventory();                        // 0x00a1ad60
    void  AnimStop();                                  // 0x00b72640
    void  LoadStateMachine();                          // 0x00fe1a20
    void  ClearDirty();                                // 0x00b78860
    void  ShowCameraControls(int a);                   // 0x01065c30 ret 4
};
struct cGameNounManager {
    void RemoveNoun(void* noun);                       // 0x00b225d0 ret 4
};
struct ObstacleData {
    void* mpVtbl_00;                                   // +0x00
    u8  pad_04[0x30];                                  // 0x04..0x33
    u32 mFlags_34;                                     // +0x34 (bit2 used)
    u8  pad_38[0xc];                                   // 0x38..0x43
    float mFloat_44;                                   // +0x44
    u8  pad_48[0xc];                                   // 0x48..0x53
    u32 mFlag_54;                                      // +0x54
    u8  pad_58[0x24];                                  // 0x58..0x7b
    void* mpKey_7c;                                    // +0x7c
    void FUN_00b73de0(int a);                          // 0x00b73de0 ret 4
    void FUN_00b73e70_desc(void* out);                 // 0x00b73e70 ret 4
};
struct Plant {
    void* mpVtbl;                                      // +0x00
    u8  pad_04[0x30];
    u32 mFlags_34;                                     // +0x34
    u8  pad_38[0xc];
    float mFloat_44;                                   // +0x44
    u8  mFlag_54;                                      // +0x54
    u8  pad_55[0x27];
    void* mpKey_7c;                                    // +0x7c
    void* GetDesc();                                   // 0x00b73e70 ret 4 (thiscall)
    void FUN_00b73de0(int a);                          // 0x00b73de0 ret 4
};
struct PlantDesc {
    u16 a;            // +0x00
    u16 b;            // +0x02
    float x;          // +0x04
    float y;          // +0x08
    float z;          // +0x0c
    float w;          // +0x10
    Mat3  m;          // +0x14 (0x24 bytes)
};
struct NewPlant {
    void* mpVtbl_0;                                    // +0x00
    u8  pad_04[0x30];                                  // 0x04..0x33
    ObstacleData mData_34;                             // +0x34 (embedded)
    float mFloat_44;                                   // +0x44
    void FUN_00c3e270(float f);                        // 0x00c3e270 ret 4
};
struct SpeciesMgr {
    void* FUN_00b2b430(Vec3 v, int a, void* profile, void* key, void* desc); // ret 0x1c
};
struct SpeciesProfile {
    u8 pad_00[0x90];
    float mField_90;                                   // +0x90
};
struct PlantSpeciesManager {
    SpeciesProfile* GetSpeciesFromID(void* key);       // 0x00b90410 ret 4
};
struct EditorSpeciesManager {
    SpeciesProfile* GetPlantProfile(void* key);        // 0x004df440 ret 4
};
// ---- items of slice s01016540 end

// @ 0x01016540
void cSPSimulatorWalkAround::RemoveHighLODPlant(void* plant, char flag)
{
    void** begin = mHighLODPlantsBegin;
    void** end   = mHighLODPlantsEnd;
    void** obst  = mHighLODObstaclesBegin;
    if (plant != 0)
        (**(void(__thiscall**)(void*))(*(void***)plant + 0))(plant);
    ((cGameNounManager*)SP_NounManager((int)plant))->RemoveNoun(plant);
    void** p = begin;
    void** o = obst;
    for (;;) {
        if (p == end)
            goto cleanup;
        if (*p == plant) {
            void** e = mHighLODPlantsEnd;
            if ((char*)p + 4 < (char*)e)
                copy_impl((char*)p + 4, e, p);
            mHighLODPlantsEnd = (void**)((char*)mHighLODPlantsEnd - 4);
            void* last = *(void**)((char*)mHighLODPlantsEnd);
            if (last != 0)
                (**(void(__thiscall**)(void*))(*(void***)last + 1))(last);
            ObstacleData* ob = (ObstacleData*)*o;
            if (!(**(u8(__thiscall**)(void*))(*(void***)ob + 0xb))(ob) && ob->mFlag_54 != 0) {
                ob->FUN_00b73de0(flag == 0);
                if (flag == 0)
                    ob->mFlags_34 |= 2;
                else
                    ob->mFlags_34 &= 0xfffffffd;
            }
            void** e2 = mHighLODObstaclesEnd;
            if ((char*)o + 4 < (char*)e2)
                copy_impl((char*)o + 4, e2, o);
            mHighLODObstaclesEnd = (void**)((char*)mHighLODObstaclesEnd - 4);
            void* last2 = *(void**)((char*)mHighLODObstaclesEnd);
            if (last2 != 0)
                (**(void(__thiscall**)(void*))(*(void***)last2 + 1))(last2);
            goto cleanup;
        }
        ++p;
        ++o;
    }
cleanup:
    if (plant != 0)
        (**(void(__thiscall**)(void*))(*(void***)plant + 1))(plant);
}

// @ 0x01016630
u8 cSPSimulatorWalkAround::ClearOldestPlant()
{
    void** e = mHighLODPlantsBegin;
    if (e == mHighLODPlantsEnd)
        return 0;
    if (mHighLODObstaclesBegin == mHighLODObstaclesEnd)
        return 0;
    void* plant = *e;
    ((cGameNounManager*)SP_NounManager((int)plant))->RemoveNoun(plant);
    void** p5 = mHighLODPlantsBegin;
    void** p6 = mHighLODPlantsEnd;
    if ((char*)p5 + 4 < (char*)p6)
        copy_impl((char*)p5 + 4, p6, p5);
    mHighLODPlantsEnd = (void**)((char*)mHighLODPlantsEnd - 4);
    void* q = *(void**)mHighLODPlantsEnd;
    if (q != 0)
        (**(void(__thiscall**)(void*))(*(void***)q + 1))(q);
    void** r5 = mHighLODObstaclesBegin;
    void** r6 = mHighLODObstaclesEnd;
    if ((char*)r5 + 4 < (char*)r6)
        copy_impl((char*)r5 + 4, r6, r5);
    mHighLODObstaclesEnd = (void**)((char*)mHighLODObstaclesEnd - 4);
    void* s = *(void**)mHighLODObstaclesEnd;
    if (s != 0)
        (**(void(__thiscall**)(void*))(*(void***)s + 1))(s);
    return 1;
}

// @ 0x010166c0
void cSPSimulatorWalkAround::SetHighLODPlant(void* plant)
{
    Plant* pa = (Plant*)plant;
    if (pa == 0)
        return;
    if ((u32)((char*)mHighLODPlantsEnd - (char*)mHighLODPlantsBegin) / 4 == 8)
        ClearOldestPlant();

    PlantDesc desc;
    PlantDesc* d = (PlantDesc*)pa->GetDesc();
    desc.a = d->a;
    desc.b = d->b;
    desc.x = d->x;
    desc.y = d->y;
    desc.z = d->z;
    desc.w = d->w;
    desc.m.Assign(&d->m);

    if ((pa->mFlags_34 >> 2 & 1) != 0) {
        SpeciesProfile* sp =
            ((PlantSpeciesManager*)FUN_00b3d420_p())->GetSpeciesFromID(&pa->mpKey_7c);
        desc.w = desc.w / sp->mField_90;
        desc.b = (u16)(desc.b + 1);
    }
    pa->FUN_00b73de0(1);

    SpeciesProfile* profile =
        ((EditorSpeciesManager*)FUN_00401090_p())->GetPlantProfile(&pa->mpKey_7c);
    if (profile == 0)
        return;

    Vec3 v = { desc.x, desc.y, desc.z };
    SpeciesMgr* mgr = (SpeciesMgr*)FUN_00b3d3b0();
    NewPlant* np = (NewPlant*)mgr->FUN_00b2b430(v, 0, profile, &pa->mpKey_7c, &desc);
    np->FUN_00c3e270(pa->mFloat_44);

    ObstacleData* data = &np->mData_34;
    void* r1 = (**(void*(__thiscall**)(ObstacleData*))(*(void***)data + 0x2c))(data);
    void* r2 = (**(void*(__thiscall**)(ObstacleData*, int))(*(void***)data + 0x2b))(data, 1);
    (**(void(__thiscall**)(void*, void*))(*(void***)r1 + 0x2d))(r1, r2);

    if (mHighLODPlantsEnd < mHighLODPlantsCap) {
        *mHighLODPlantsEnd = np;
        mHighLODPlantsEnd = mHighLODPlantsEnd + 1;
        (**(void(__thiscall**)(void*))(*(void***)np + 0))(np);
    } else {
        FUN_00aea5d0(mHighLODPlantsEnd, np);
    }
    (**(void(__thiscall**)(void*))(*(void***)np + 1))(np);

    if (mHighLODObstaclesEnd < mHighLODObstaclesCap) {
        *mHighLODObstaclesEnd = pa;
        mHighLODObstaclesEnd = mHighLODObstaclesEnd + 1;
        (**(void(__thiscall**)(void*))(*(void***)pa + 0))(pa);
    } else {
        FUN_00aea5d0(mHighLODObstaclesEnd, pa);
    }
    (**(void(__thiscall**)(void*))(*(void***)pa + 1))(pa);
}

// @ 0x010168c0
void cSPSimulatorWalkAround::ShutdownForGame()
{
    void* ticker = SP_SimTicker();
    (**(void(__thiscall**)(void*, void*))(*(void***)ticker + 0x15))(ticker, this);
    while (ClearOldestPlant())
        ;
    void* p = mpX_44;
    if (p != 0) {
        FUN_00572020(p, 1);
        mpX_44 = 0;
    }
    void* a = mpAvatar;
    if (a != 0) {
        (**(void(__thiscall**)(void*, int))(*(void***)a + 0x32))(a, 1);
        a = mpAvatar;
        if (a != 0) {
            mpAvatar = 0;
            (**(void(__thiscall**)(void*))(*(void***)a + 1))(a);
        }
    }
    void* b = mpStrategy;
    if (b != 0) {
        (**(void(__thiscall**)(void*))(*(void***)b + 3))(b);
        void* c = mpStrategy;
        if (c != 0) {
            void* sub = (char*)c + 0x3c;
            mpStrategy = 0;
            (**(void(__thiscall**)(void*))(*(void***)sub + 2))(sub);
        }
    }
}
