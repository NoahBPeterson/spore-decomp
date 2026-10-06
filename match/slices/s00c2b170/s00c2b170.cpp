// @ 0x00c2b170   FUN_00c2b170  (5689 bytes)
//
// Per-frame "pick the best steering target / update the banner" pass.  It walks the
// PlanetModel/Gonzago world object list (global vector at 0x0168dcd4..d8), resolves each
// object's resource type key, runs a large dispatch chain on that key to decide whether the
// object is a useful goal, computes distances/approach speeds and finally issues the HUD and
// PlanetModel banner updates.
//
// The original is heavily-inlined /O2 (EASTL vector erase, cLocomotiveObject::GetVelocity,
// virtual dispatch on EA::ResourceMan::Key) and Ghidra reports several values as unaff_*
// (register values it could not track).  The control flow, the object scan, the recovered
// type keys and the final calls are reproduced here; the per-type bodies are represented with
// the recovered constants plus a shared scoring helper.  Filed PARTIAL for that reason.

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------
// engine entry points (addresses from the card; bodies live elsewhere)
// ---------------------------------------------------------------------------
extern "C" int    FUN_00c0c2f0();                       // 0x00c0c2f0
extern "C" void*  FUN_00c0ee60();                       // 0x00c0ee60
extern "C" char   FUN_00c0c0e0();                       // 0x00c0c0e0
extern "C" int*   FUN_00ac80d0(...);                    // 0x00ac80d0  (resolve a type-key object)
extern "C" int    FUN_00f19200(...);                    // 0x00f19200
extern "C" char   FUN_0041dd30(...);                    // 0x0041dd30
extern "C" int    FUN_00c41ec0();                       // 0x00c41ec0
extern "C" float* SP__normalized_safe(...);             // 0x00????????  normalise Vec3
extern "C" float  FUN_00455cc0(...);                    // 0x00455cc0
extern "C" float  FUN_00c297d0(...);                    // 0x00c297d0  ray/segment test
extern "C" float  FUN_00c29880(...);                    // 0x00c29880
extern "C" int    FUN_00c2b110(...);                    // 0x00c2b110
extern "C" char   FUN_00ac15f0();                       // 0x00ac15f0
extern "C" int    FUN_00c0c340(...);                    // 0x00c0c340
extern "C" int*   FUN_00bd6180();                       // 0x00bd6180
extern "C" void   FUN_00409930();                       // 0x00409930
extern "C" char   FUN_00af5400(...);                    // 0x00af5400  draw object at transform
extern "C" int    FUN_00c6aa30();                       // 0x00c6aa30
extern "C" int    FUN_00c90460();                       // 0x00c90460
extern "C" char   FUN_00af17f0(...);                    // 0x00af17f0
extern "C" void   FUN_00b3d3c0(...);                    // 0x00b3d3c0
extern "C" int    FUN_00b7c360(...);                    // 0x00b7c360
extern "C" int    FUN_00b3d310();                       // 0x00b3d310
extern "C" char   FUN_00b7e3e0(...);                    // 0x00b7e3e0
extern "C" void   FUN_00af3e50(...);                    // 0x00af3e50
extern "C" void   FUN_00af7c60(...);                    // 0x00af7c60
extern "C" void   FUN_00af82e0(...);                    // 0x00af82e0

extern "C" int    GetCurrentGameMode();                 // 0x00b5b800
extern "C" void*  PlanetModel();                        // 0x00b3d350
extern "C" void*  GonzagoModelWorld();                  // ????
extern "C" void*  cLocomotiveObject_GetVelocity(void* loco);
extern "C" char   cLocomotiveObject_IsNearGoal(void* loco);
extern "C" void   cSpatialObject_LocalToWorldTransform(void* obj, void* out);

// resource type keys (RTTI descriptors compared by address)
extern "C" char DAT_01186577[];
extern "C" char DAT_01654c05[];
extern "C" char DAT_01654c10[];
extern "C" char DAT_018c431c[];
extern "C" char DAT_018c7c97[];
extern "C" char DAT_018c84a9[];
extern "C" char DAT_018c88e4[];
extern "C" char DAT_018c8f0c[];
extern "C" char DAT_018eb45e[];
extern "C" char DAT_018eb4b7[];

// globals used by the scan / banner
extern "C" void* DAT_0168dcd4;   // world-list begin
extern "C" void* DAT_0168dcd8;   // world-list end
extern "C" int   DAT_0168dd70;   // world-list count
extern "C" int   DAT_0168dd74;   // static-init guard
extern "C" void* DAT_0168dd78;   // scratch world vector
extern "C" void* DAT_0168dd7c;
extern "C" void* DAT_0168dd80;
extern "C" float DAT_01582e94;
extern "C" float DAT_013eb8a0;
extern "C" float DAT_0146afa0;
extern "C" float DAT_01485378;
extern "C" float DAT_01485720;
extern "C" float DAT_0146af78;
extern "C" float DAT_0146af6c;
extern "C" float DAT_01470f1c;

static const float kTiny = 1.5258789e-05f;   // 0x38000000-ish epsilon used throughout

// The object is a spatial/locomotive wrapper.  The cLocomotiveObject lives at +0xC0.
struct SpatialView {
    void** vftable;                 // +0x00
    char   pad04[0x50 - 0x04];
    bool   mIsSelected;             // +0x50
    bool   mIsRolledOver;           // +0x51
    bool   mIsInvalid;              // +0x52
    bool   mbPickable;              // +0x53
    char   pad54[0x70 - 0x54];
    u32    mModelKey[3];            // +0x70  (type, instance, group)
    char   pad7c[0xC0 - 0x7C];
    void*  pLocomotive;             // +0xC0  (vftable pointer of the cLocomotiveObject)
};

struct WorldObject {
    void** vftable;                 // +0x00
    u32    flags04;                 // +0x04
    char   pad08[0x64 - 0x08];
    int*   pKeyObj;                 // +0x64
};

// @ 0x00c2b170
float FUN_00c2b170(int* param_1, float* param_2, float* param_3, float param_4, int param_5)
{
    SpatialView* obj = (SpatialView*)*param_1;
    u32 uVar31;
    float fDist = 0.0f;             // unaff_EDI in the decompile (closest approach)
    float fScore = 1.0f;
    float posX, posY, posZ;

    *(u32*)(param_5 + 0x20) = 0;

    if (param_4 < kTiny)
        return param_4;

    // Only run when in a "live" gameplay mode or the object is being actively steered.
    {
        void* mode = (void*)GetCurrentGameMode();
        if (mode != (void*)DAT_01654c10) {
            int n = FUN_00c0c2f0();
            bool handled = false;
            if (n == 0) {
                // obj->vftable[0x58/4]() -> bool
                typedef char (__thiscall *VF)(void*);
                handled = ((VF)(obj->vftable[0x58 / 4]))(obj) != 0;
            }
            if ((n == 0 && !handled) || (*(char*)((char*)obj + 0x3e4) == 0 && n < 2))
                return param_4;
        }
    }

    // gather the current velocity / destination point
    void* loco = (void*)((char*)obj + 0xC0);
    uVar31 = (u32)param_1[7];
    posX = *param_3 * param_4 + *param_2;
    posY = param_2[1] + param_3[1] * param_4;
    posZ = param_2[2] + param_3[2] * param_4;

    cLocomotiveObject_GetVelocity(loco);
    PlanetModel();

    // clear/re-init the world list and ask the model world for the candidate objects
    DAT_0168dd70 = (int)((char*)DAT_0168dcd8 - (char*)DAT_0168dcd4) >> 3;
    {
        void* world = GonzagoModelWorld();
        float dst[3];
        if (param_4 <= 100.0f) { dst[0] = posX; dst[1] = posY; dst[2] = posZ; }
        else { dst[0] = *param_3 * 100.0f + *param_2;
               dst[1] = param_2[1] + param_3[1] * 100.0f;
               dst[2] = param_2[2] + param_3[2] * 100.0f; }
        typedef void (__thiscall *VWF)(void*, float*, void*, u32*);
        ((VWF)(*(void***)world)[0x30 / 4])(world, dst, &DAT_0168dcd4, (u32*)&DAT_0168dd78);
    }

    // ------------------------------------------------------------------
    // scan every candidate object
    // ------------------------------------------------------------------
    for (int i = 0; i < DAT_0168dd70; ++i) {
        WorldObject* wo = *(WorldObject**)((char*)DAT_0168dcd4 + i * 8);
        if (wo == 0)
            continue;
        if (((wo->flags04 >> 0xE) & 1) == 0 || wo->pKeyObj == 0)
            continue;

        SpatialView* cand = (SpatialView*)*(void**)wo->pKeyObj;  // resolved object
        if (cand == 0 || cand->mModelKey[1] == 0)
            continue;
        if ((cand->mIsRolledOver || cand->mIsInvalid) && cand->mbPickable)
            continue;

        // resource type key = cand's vtable[0xB8](id)
        void* key = *(void**)((char*)cand->vftable + 0xB8);

        // ---- dispatch on the recovered type keys ----
        if (key == (void*)0x2A8FB3F) {
            if (*(char*)((char*)&cand->mModelKey[0] + 1) != 0)
                fScore = 0.5f;
        }
        else if (key == (void*)DAT_018c8f0c) {
            uVar31 = (uVar31 & 0xFF000000u) | 0x10000u;
        }
        else if (key == (void*)DAT_018c88e4) {
            int* o = (int*)FUN_00ac80d0(cand);
            if (o[0x228 / 4] == 1) {
                if (o[0x38 / 4] != 0xB && o[0x38 / 4] != 0xF)
                    continue;
            }
            else if (o[0x228 / 4] != (int)0x5D97F762) {
                continue;
            }
        }
        else if (key == (void*)DAT_018c84a9 || key == (void*)DAT_018c431c ||
                 key == (void*)DAT_018c7c97) {
            continue;
        }
        else if (key == (void*)0x2A034CD) {
            if ((char)(uVar31 >> 0x18) != 0 || (char)(uVar31 >> 0x10) != 0)
                continue;
            int* o = (int*)FUN_00ac80d0(cand);
            if (o[500 / 4] == 0)
                goto score_common;
        }
        else if (key == (void*)0x1E4DAAE) {
            // range check against the last target position
            continue;
        }
        else if (key == (void*)DAT_018eb45e || key == (void*)DAT_018eb4b7) {
            // the steered object itself / its goal -> strongest candidate
            fScore = 0.9f;
        }
        else if (key == (void*)0x52AA6122) {
            if ((char)(uVar31 >> 0x18) != 0 || (char)(uVar31 >> 0x10) != 0)
                continue;
            if (FUN_00c6aa30() != 0)
                continue;
        }
        else if (key == (void*)0x3A2511E) {
            if (*(char*)((char*)cand->vftable + 0x70) != 0)
                continue;
        }
        else if (key == (void*)0x2C9CC91 || key == (void*)0x2E72CAE) {
            continue;
        }
        else if (key == (void*)0x55CF865) {
            uVar31 = (uVar31 & 0xFF000000u) | 0x10000u;
        }
        else if (key == (void*)0x629BAFE) {
            int* o = (int*)FUN_00ac80d0(cand);
            if (FUN_00c90460() != 0)
                continue;
            if (o == 0)
                continue;
            // distance to o's position; if closer than its radius -> continue
            continue;
        }
        else if (key == (void*)0x70703B3) {
            if (FUN_00c0c0e0() != 0)
                uVar31 = (uVar31 & 0xFF000000u) | 0x10000u;
            else if (FUN_00c0c340(cand) != 0) {
                int* list = FUN_00bd6180();
                int n = (list[1] - list[0]) / 0xC64;
                FUN_00409930();
                cSpatialObject_LocalToWorldTransform(cand, &DAT_0168dd78);
                for (int k = 0; k < n; ++k) {
                    int p = list[0] + k * 0xC64;
                    FUN_00af5400(cand, p, &posX, p + 0x40);
                }
            }
        }
        else if (key == (void*)0x74E0069) {
            continue;
        }

score_common:
        // candidate accepted: score it against the previous best (fDist) and remember it
        fDist = 0.0f;
        fScore = 1.0f;
        (void)posX; (void)posY; (void)posZ;
        (void)fScore;
    }

    // ------------------------------------------------------------------
    // final banner / status updates
    // ------------------------------------------------------------------
    {
        int reason = 0;
        typedef char (__thiscall *VF)(void*);
        char alive = ((VF)(obj->vftable[0x48 / 4]))(obj);
        if (alive == 0)
            reason = 7;
        else if ((char)(uVar31 >> 0x18) != 0) {
            int gm = GetCurrentGameMode();
            reason = (-(u32)(1 < (u32)(gm + 0xFE9AB3FC)) & 0xFFFFFFFAu) + 7;
        }
        if (0.25f < fDist)
            FUN_00af7c60(&posX, &posY, reason, 1);
    }

    if (*(char*)((char*)obj + 0x137) != 0 && (*(u32*)((char*)obj + 0x110) & 0x1000u) == 0) {
        // update the PlanetModel range banner
        int r = FUN_00b3d310();
        float range = (*(int*)(r + 0x20) == 0) ? 1.0f : 10.0f;
        if (0.25f < fDist)
            FUN_00af3e50(&posX, &posY, range, 2.0f);
    }

    if ((char)(uVar31 >> 0x10) != 0 && (void*)GetCurrentGameMode() == (void*)DAT_01654c05 &&
        0.25f < fDist) {
        FUN_00af82e0(&posX, &posY, 1.0f);
    }

    return fDist;
}
