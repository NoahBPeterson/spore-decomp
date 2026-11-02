// src/game/SPGonzago/_at_00d20000.cpp -- migrated from slice(s) s00d2dd20, s00d1f650 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00d20000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cLocalInputState.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cTribe.h"
#include "SP/cPlanetModel.h"
#include "cSPUILayout.h"
#include "SP/cSPUINewProgressBar.h"
#include "SP/cTerrainSphere.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern char g_gameModeTribe2;    // 0x01654c02

// ---- items of slice s00d1f650 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_gameModeTribe2;    // 0x01654c02
struct cAnimHandle {
    char     pad00[0xc];
    unsigned mFieldC;                          // +0x0c
};
struct CreatureAnim {
    void*        PlayIdleAnimation(int a, int b);                    // 0x00bc96a0
    cAnimHandle* FUN_00bc97f0(unsigned f, int a, float t, int b);    // 0x00bc97f0
};
struct CreatureInner {
    char  pad000[0x1a8];
    void* mpField1a8;                          // 0x1a8
};
struct CreatureModel {
    char           pad000[8];
    CreatureAnim   mAnim;                      // 0x08 (the animation state)
    char           pad009[0x1c8 - 0x09];
    unsigned       mFlags1c8;                  // 0x1c8
    unsigned       mFlags1cc;                  // 0x1cc
    unsigned       mTypeId1d8;                 // 0x1d8 (0xb46e8803 / 0x5218bb3 magic ids)
    char           pad1dc[0x600 - 0x1dc];
    CreatureInner* mpInner600;                 // 0x600
};
struct SpatialVec {
    void** mpBegin;                            // +0x00
    void** mpEnd;                              // +0x04
    void** mpCap;                              // +0x08
};
struct AbilityInfo {
    char     pad00[8];
    unsigned mType;                            // 0x08 (the 0xd..0x56 dispatch id)
    unsigned mFieldC;                          // 0x0c
    char     pad10[0xac - 0x10];
    float    mFloatAC;                         // 0xac
    char     padb0[0x104 - 0xb0];
    float    mFloat104;                        // 0x104
};
struct AbilitySlotRecord {
    char  pad00[4];
    float mFloat4;                             // +0x04
};
struct AbilityCreature {
    void**         mpVftable;                  // 0x000
    char           pad04[0x110 - 0x04];
    unsigned       mFlags110;                  // 0x110
    char           pad114[0x137 - 0x114];
    unsigned char  mByte137;                   // 0x137
    char           pad138[0xb4c - 0x138];
    CreatureModel* mpModelBC;                  // 0xb4c
    unsigned       mFlagsB58;                  // 0xb58
    char           padb5c[0xb5e - 0xb5c];
    unsigned char  mByteB5E;                   // 0xb5e (non-zero => ability not usable)
    char           padb5f[0xc28 - 0xb5f];
    AbilitySlotRecord* mpAbilitySlots;         // 0xc28 (the ability-slot records)
    char           padc2c[0xe58 - 0xc2c];
    float          mRangeE58;                  // 0xe58
    void*          GetTargetAsCreature();      // 0x00c0ee70
    void*          FUN_00c0ee60();             // 0x00c0ee60
    unsigned char  FUN_00c0e0c0(int id);       // 0x00c0e0c0
    unsigned char  FUN_00c0c0e0();             // 0x00c0c0e0
    int            FUN_00c22dc0();             // 0x00c22dc0
};
struct cGameNounManager {
    void* GetPlayerTribe();                    // 0x00bfc5f0
};
struct cTribe {
    int   GetToolOfType(int type);             // 0x00c8f6e0
};
typedef void         (__thiscall *TerrainCursorGetObjectsVfn)(void*, SpatialVec*);  // 0x00b30d70 result vftable slot 0x5c
typedef void*        (__thiscall *SpatialCastVfn)(void*, unsigned);                 // cSpatialObject vftable slot 0xb8
void   FUN_00ad92d0(void* vec);              // 0x00ad92d0 eastl::vector<>::~vector
void*  GetCurrentGameMode();                 // 0x00b5b800
void*  NounManager();                        // 0x00b3d300
void*  GetGameTerrainCursor();               // 0x00b30d70
// ---- items of slice s00d1f650 end

// ---- items of slice s00d2dd20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kTier0Height;     // 0x01582e38
extern float kTier1Height;     // 0x01582e3c
extern float kTier2Height;     // 0x01582e40
#pragma pack(push, 4)
#pragma pack(pop)
struct Vector3 { float x, y, z; };
class cAvatar;
class cTerrainSphere {
public:
    unsigned char mPad00[0x10f0];
    float         mHeight;      // +0x10f0
    float         mHeightMax;   // +0x10f4
};
class cGameNounManager_s00d2_dd20 {
public:
    cAvatar*        GetAvatar();                     // 0x00b1fdb0
    cTerrainSphere* GetCurrentTerrainSphere();       // 0x00f67d90
};
cGameNounManager_s00d2_dd20* NounManager_s00d2_dd20();                     // 0x00b3d300
class cAvatarMood {
public:
    double FUN_00bfc490();                           // 0x00bfc490  st0 result
    unsigned char mPad00[4];
};
struct AvatarFlagsB58 {
    unsigned int mFlag0  : 1;
    unsigned int mFlag1  : 1;
    unsigned int mFlag2  : 1;
    unsigned int mFlag3  : 1;
    unsigned int mFlag4  : 1;
    unsigned int mFlag5  : 1;
    unsigned int mFlag6  : 1;
    unsigned int mFlag7  : 1;
    unsigned int mFlag8  : 1;
    unsigned int mFlag9  : 1;
    unsigned int mFlag10 : 1;
    unsigned int mFlag11 : 1;
};
class cLocomotive {
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual const Vector3* GetPosition();            // +0x2c
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
    virtual bool FUN_0048();                         // +0x48
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
    virtual double FUN_0074();                       // +0x74  st0 result
};
class cSpeciesData {
public:
    unsigned char mPad00[0x61c];
    int           mMode;         // +0x61c
};
class cAvatar {
public:
virtual void v00();
virtual void v04();
virtual void v08();
    virtual cAvatar* FUN_000C(unsigned int id);                                  // 0x0c
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
virtual void v74();
virtual void v78();
virtual void v7c();
    virtual void v80();                                                              // 0x80
    virtual void FUN_0084(void* arg);                                                // 0x84
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void vA0();
virtual void vA4();
virtual void vA8();
virtual void vAC();
virtual void vB0();
virtual void vB4();
virtual void vB8();
virtual void vBC();
virtual void vC0();
virtual void vC4();
virtual void vC8();
virtual void vCC();
virtual void vD0();
virtual void vD4();
    virtual int  FUN_00D8();                                                         // 0xd8

    void*  FUN_00c04590();                            // 0x00c04590
    double FUN_00c0b9c0();                            // 0x00c0b9c0  st0 result
    void*  FUN_00c0ee60(unsigned char slot, int flag);   // 0x00c0ee60
    cAvatar* FUN_00c0ee70();                          // 0x00c0ee70  GetTargetAsCreature
    cAvatar* FUN_00c0ee90();                          // 0x00c0ee90  ApplyCombatTarget
    bool   FUN_00c0b770();                            // 0x00c0b770
    void   FUN_00c1d400(unsigned int id, unsigned int guid);  // 0x00c1d400
    void*  FUN_00c14e70(unsigned int guid);           // 0x00c14e70

    unsigned char  mPad04[0xc0 - 0x04];
    cLocomotive    mLocomotive;  // +0xc0
    unsigned char  mPadC4[0x137 - 0xc4];
    unsigned char  mField137;    // +0x137
    unsigned char  mPad138[0x5a8 - 0x138];
    cAvatarMood    mMood;        // +0x5a8
    unsigned char  mPad5ac[0x5e0 - 0x5ac];
    float          mMadTimer;    // +0x5e0
    unsigned char  mPad5e4[0xb20 - 0x5e4];
    cSpeciesData*  mpSpecies;    // +0xb20
    unsigned char  mPadB24[0xb28 - 0xb24];
    unsigned char  mCombatDataB28[0xb4c - 0xb28];  // +0xb28  handed to the mode helpers
    void*          mpOwnerB4c;   // +0xb4c  object whose +8 owns the avatar
    unsigned char  mPadB50[0xb58 - 0xb50];
    AvatarFlagsB58 mFlagsB58;    // +0xb58
    unsigned char  mSlotB5c;     // +0xb5c
    unsigned char  mFieldB5e;    // +0xb5e
};
class cSub128 {
public:
    void FUN_00d2d560(float value);              // 0x00d2d560
    void FUN_00d2d0b0(int tick);                 // 0x00d2d0b0
};
class cCreatureModeEventSink {
public:
    __declspec(noinline) void Update(float value);   // 0x00d2e2e0  (this file)

    unsigned char mPad00[0x128];
    cSub128       mSub;      // +0x128
};
// ---- items of slice s00d2dd20 end

// @ 0x00d201f0
unsigned char F_d201f0(AbilityInfo* ability)
{
    if (GetCurrentGameMode() != (void*)&g_gameModeTribe2)
        return 1;
    if (ability->mFieldC == 4)
        return 1;

    cTribe* tribe = (cTribe*)((cGameNounManager*)NounManager())->GetPlayerTribe();
    int tool;
    switch (ability->mType - 5) {
    case 0:  if (tribe->GetToolOfType(4) == 0) return 0; tool = 4; break;
    case 1:  if (tribe->GetToolOfType(5) == 0) return 0; tool = 5; break;
    case 2:  if (tribe->GetToolOfType(6) == 0) return 0; tool = 6; break;
    case 38: if (tribe->GetToolOfType(1) == 0) return 0; tool = 1; break;
    case 53: if (tribe->GetToolOfType(2) == 0) return 0; tool = 2; break;
    case 54: if (tribe->GetToolOfType(3) == 0) return 0; tool = 3; break;
    default: return 0;
    }

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** tvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)tvt[0x5c / 4])(terrain, &vec);

    int           count = (int)(vec.mpEnd - vec.mpBegin);
    unsigned char found = 0;
    for (int i = 0; i < count; i++) {
        void* so = vec.mpBegin[i];
        if (so == 0)
            continue;
        void** svt = *(void***)so;
        void*  obj = ((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
        if (obj == 0)
            continue;
        if (((AbilityCreature*)obj)->FUN_00c22dc0() == tool) {
            found = 1;
            break;
        }
    }
    FUN_00ad92d0(&vec);
    return found;
}

// @ 0x00d2e2e0
void cCreatureModeEventSink::Update(float value)
{
    mSub.FUN_00d2d560(value);
}

// @ 0x00d2e410
double GetTierBaseHeight(int tier)
{
    float base = NounManager_s00d2_dd20()->GetCurrentTerrainSphere()->mHeight;
    switch (tier) {
    case 1:
        base = base - kTier0Height;
        break;
    case 2:
        base = base - (kTier1Height + kTier0Height);
        break;
    case 3:
        base = base - ((kTier2Height + kTier1Height) + kTier0Height);
        break;
    }
    return base;
}
