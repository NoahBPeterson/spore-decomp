// src/game/SPGonzago/SPCreatureAbility.cpp -- migrated from slice(s) s00d1f650, s00d1e930, s00d1df40 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureAbility.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCommunity.h"
#include "SP/cCity.h"
#include "SP/cSPCreatureBase.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern const float  gRealOne;          // 0x01485720 (_HK_REAL_ONE)
extern const unsigned char gByte1582df5; // 0x01582df5 (byte gate)
extern uint32_t     gTable169de64[6];  // 0x0169de64
#include <math.h>
#include <wchar.h>
#include "EA/Variant.h"
#include "SP/cSPCreatureCitizen.h"
#include "SP/cGameNounManager.h"
#include "SP/cLocalInputState.h"
#include "SP/cTribe.h"

// ---- items of slice s00d1df40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned int uintptr_t;
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct IVtbl {
    PV PV                                        // 0x00, 0x04
    virtual int   Slot8(int a);                  // 0x08
    virtual void* SlotC();                       // 0x0c
    PV8 PV4 PV2 PV                               // 0x10..0x48
    virtual int   Slot4c();                      // 0x4c
    PV16 PV8                                     // 0x50..0xac
    virtual int   SlotB0();                      // 0xb0  (count)
    virtual int   SlotB4(int i);                 // 0xb4  (element i)
    PV4 PV2 PV                                   // 0xb8..0xd0
    virtual char  SlotD4();                      // 0xd4
};
typedef int (__cdecl *Slot8Vfn)(int);
struct VtblTable { void* mSlots[0x100]; };
struct IVtblSlot8 {
    VtblTable* mpVtbl;                        // 0x00
};
struct NounMgr {
    void* GetPlayerTribe();                      // 0x00bfc5f0
    void* GetAvatar();                           // 0x00b1fdb0
    void* GetCurrentTerrainSphere();             // 0x00f67d90
};
struct Community {
    void* GetLeader();                           // 0x00c00650
};
struct Sphere {
    void FUN_00c77320(uint id);                  // 0x00c77320
};
struct AvatarProfile;
struct SpeciesMgr {
    AvatarProfile* GetAvatarProfile();           // 0x004df420
};
struct TuningObj {
    float GetBound(bool flag);                         // 0x004d3d70
};
struct Loco { uint32_t mDummy; };
struct cCreature {
    uint8_t  pad00[0xc0];
    Loco     mLoco;                                    // +0xc0
    uint8_t  padC4[0xb58 - (0xc0 + sizeof(Loco))];
    uint32_t mFlagsB58;                                // +0xb58
    uint8_t  padB5c[0xb5e - (0xb58 + 4)];
    uint8_t  mFlagB5e;                                 // +0xb5e
    void*    FUN_00c0bc00(void* a);                    // 0x00c0bc00
    void*    GetSocialGoal();                          // 0x00c0e6a0
};
struct Elem {
    uint8_t pad00[4];
    float   mValue;                                    // +0x04
    uint8_t pad08[8];
};
struct FlagSetObj {
    uint8_t  pad00[0xbf8];
    uint32_t mFlags[12];                               // +0xbf8
    Elem*    mpElems;                                  // +0xc28
};
struct BabyRec {
    int32_t  mId;                                      // +0x00 (object +0x168)
    uint8_t  pad04[0x70 - 4];
    uint32_t mTag;                                     // +0x70 (object +0x1d8)
    uint32_t mIndex;                                   // +0x74 (object +0x1dc)
    uint8_t  pad78[0xac - 0x78];
};
struct TrainData {
    uint8_t pad00[0x168];
    BabyRec mRecs[1];                                  // +0x168 (stride 0xac)
};
struct TrainObj {
    uint8_t  pad00[0x14];
    void*    mpAgent;                                  // +0x14
    uint8_t  pad18[0x6c - 0x18];
    uint32_t mFlags6c;                                 // +0x6c
};
struct AgentLink {
    uint8_t pad00[0xb4c];
    void*   mpData;                                    // +0xb4c
};
struct SocialData {
    uint8_t pad00[0x1d8];
    uint32_t mTag;                                     // +0x1d8
    uint8_t pad1dc[0x600 - 0x1dc];
    void*   mpInner;                                   // +0x600
};
struct InnerObj {
    uint8_t pad00[8];
    uint32_t mTag8;                                    // +0x08
    uint8_t pad0c[0x1e4 - 0xc];
    uint8_t mFlag1e4;                                  // +0x1e4
};
struct DataLink {
    uint8_t pad00[0xb4c];
    SocialData* mpData;                                // +0xb4c
};
struct OrderMgr {
    int FindSlot(int a, int b, int c, int d);          // 0x00bca0c0
};
struct OrderLink {
    uint8_t  pad00[0xb48];
    OrderMgr* mpOrder;                                 // +0xb48
};
struct SocialProbe {
    int FUN_00ba3f90(void* b, void* c);                // 0x00ba3f90
};
struct AvatarProfile {
    uint8_t   pad00[0x6d4];
    uint32_t* mpIds;                                   // +0x6d4
};
float __cdecl FUN_00d99ac0(void* loco, int sel);    // 0x00d99ac0
void* __cdecl SP_GetCurrentGameMode();              // 0x00b5b800
char  __cdecl FUN_00c0e8d0(void* a, int b);         // 0x00c0e8d0
void* __cdecl SP_NounManager();                     // 0x00b3d300
void* __cdecl FUN_00d51660();                       // 0x00d51660
void* __cdecl FUN_00c0bc00(void* a, void* b);       // 0x00c0bc00
void* __cdecl FUN_00b3d4c0(void* a);                // 0x00b3d4c0
void* __cdecl GetSetting9();                        // 0x00401090
extern const float  gRealOne;          // 0x01485720 (_HK_REAL_ONE)
extern const unsigned char gByte1582df5; // 0x01582df5 (byte gate)
extern uint32_t     gTable169de64[6];  // 0x0169de64
// ---- items of slice s00d1df40 end

// ---- items of slice s00d1e930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_147a2d8;                                      // 0x0147a2d8 FLT_MAX
extern float g_1473c70;                                      // 0x01473c70 10.0f
extern char  g_1582df5;                                      // 0x01582df5
struct cTerrainEditor {
    char  _p000[0x10fc];
    void* mpListA;                        // +0x10fc
    void* mpListB;                        // +0x1100
    bool  GetFlagValue(uint32_t id, int* outValue);      // 0x00c77380
    void  SetFlagValue(uint32_t id, uint32_t value);     // 0x00c79f00
    bool  HasFlagOrInsert(uint32_t id);                  // 0x00c77bf0
};
char g_1654c01;                           // 0x01654c01  game-mode tag
void* FUN_00f67d90();                     // 0x00f67d90 thiscall GetCurrentTerrainSphere
struct cAbilityEntry;
struct cCreatureBase;
struct cCreatureVtbl {
    void* mSlots[0xb0 / 4];                                  // +0x000
    int (__thiscall* fnB0)(cCreatureBase*);                  // +0x0b0  ability count
    cAbilityEntry* (__thiscall* fnB4)(cCreatureBase*, int);  // +0x0b4  ability entry
};
struct cSubC0Vtbl {
    void* mSlots[0x58 / 4];                                  // +0x000
    char (__thiscall* fn58)(void*);                          // +0x058
};
struct cCreatureList {
    cCreatureBase** mpBegin;                                 // +0x00
    cCreatureBase** mpEnd;                                   // +0x04
};
struct cGameNounManager {
    cCreatureList* GetItemID();                              // 0x00b1f9c0
};
struct cBehaviorStimuli {
    void  Set(unsigned int a, unsigned int b, float c, void* d);  // 0x00bc97f0
    void* Play(unsigned int a, unsigned int b);                   // 0x00bc96a0
};
struct Variant {
    int            mD00, mD04, mD08, mD0c;                   // +0x00
    unsigned short mFlags;                                   // +0x10
    unsigned short mTypeId;                                  // +0x12
    Variant& SetInt(const int& value);                       // 0x00671ba0
    void     Destruct(int freeFlag);                         // 0x0093db80
};
struct cCitizen {
    void* GiveOrder(void* a, void* b, void* c);              // 0x00c275b0
};
struct cUIHints {
    void FUN_0067c830(unsigned int id);                      // 0x0067c830
};
struct cAbilityEntry {
    char  _p000[0x08];
    int   mType;                                             // +0x08
    int   mMode;                                             // +0x0c
    char  _p010[0xa8 - 0x10];
    float mF0a8;                                             // +0x0a8
    char  _p0ac[0xf4 - 0xac];
    float mF0f4;                                             // +0x0f4
    char  _p0f8[0x104 - 0xf8];
    float mF104;                                             // +0x104
    char  _p108[0x115 - 0x108];
    char  mB115;                                             // +0x115
    float GetBound(int which);                               // 0x004d3d70
};
struct cCreatureBase {
    cCreatureVtbl* mpVtbl;                                   // +0x000
    char  _p004[0xc0 - 0x04];
    char  mSubC0;                                            // +0x0c0
    char  _pC1[0x110 - 0xc1];
    unsigned int mFlags110;                                  // +0x110
    char  _p114[0x137 - 0x114];
    char  mB137;                                             // +0x137
    char  _p138[0xb20 - 0x138];
    void* mPtrB20;                                           // +0xb20
    char  _pB24[0xb4c - 0xb24];
    void* mPtrB4c;                                           // +0xb4c
    char  _pB50[0xb58 - 0xb50];
    unsigned int mB58;                                       // +0xb58
    char  mB5c;                                              // +0xb5c
    char  _pB5d[0xe70 - 0xb5d];
    int   mE70;                                              // +0xe70
    int   mE74;                                              // +0xe74

    int   FUN_00c196a0(int a, int b, int c);                 // 0x00c196a0
    void  FUN_00c1b020(int a);                               // 0x00c1b020
    void  FUN_00c18370();                                    // 0x00c18370
    void  FUN_00c13650();                                    // 0x00c13650
    void  FUN_00c03c20(int a);                               // 0x00c03c20
    void  FUN_00c03190(unsigned int a, unsigned int b, float c, int d, int e, int f, int g); // 0x00c03190
    int   FUN_00c0c120();                                    // 0x00c0c120
    int   FUN_00c0c130();                                    // 0x00c0c130
    void  SetSprinting(int on);                              // 0x00c1ad10
    void  SetStealthed(int a, int b);                        // 0x00c1aed0
    void  Attack(int target, int flags);                     // 0x00c1e460
    void* FUN_00c0ee60();                                    // 0x00c0ee60
    void* GetTargetAsCreature();                             // 0x00c0ee70
    int   FUN_00c0e0c0(int a);                               // 0x00c0e0c0
};
void* FUN_00ac80d0(void* obj, void* type);                   // 0x00ac80d0
void* FUN_00d2e340();                                        // 0x00d2e340
float FUN_00d38a30(int a, void* b);                          // 0x00d38a30
void* FUN_00ad26d0(void* p);                                 // 0x00ad26d0
float FUN_00d99ac0(void* a, void* b, unsigned int c);        // 0x00d99ac0
void* FUN_0067cac0();                                        // 0x0067cac0
char g_1654c10;                                              // 0x01654c10 game-mode tag
// ---- items of slice s00d1e930 end

// ---- items of slice s00d1f650 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_gameModeTribe;     // 0x01654c01
extern char g_gameModeTribe2;    // 0x01654c02
extern const float g_kOne;       // 0x01485720
extern const float g_kTen;       // 0x01473c70
struct ModeState {
    char     pad00[0x6c];
    unsigned mBits6C;                          // 0x6c
};
struct ScriptState {
    char pad00[8];
    int  mValue8;                              // 0x08
};
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
struct cAbilityItem {
    char          pad00[0x51];
    unsigned char mByte51;                     // 0x51
};
struct cAbilityOwner {
    int GetFileCount();                        // 0x008e7f80
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
struct cGameNounManager_s00d1_f650 {
    void* GetPlayerTribe();                    // 0x00bfc5f0
};
struct cCommunity {
    void* GetLeader();                         // 0x00c00650
};
typedef unsigned     (__thiscall *CreatureTypeVfn)(void*);         // vftable slot 0x20
typedef AbilityInfo* (__thiscall *ResolveAbilityVfn)(void*, int);  // vftable slot 0xb4
typedef void         (__thiscall *TerrainCursorGetObjectsVfn)(void*, SpatialVec*);  // 0x00b30d70 result vftable slot 0x5c
typedef void*        (__thiscall *SpatialCastVfn)(void*, unsigned);                 // cSpatialObject vftable slot 0xb8
typedef int          (__thiscall *GetFieldVfn)(void*);                              // vftable slot 0xb0
extern AbilityInfo* g_abilityTable[];        // 0x0169de64
ModeState*   FUN_00d51660_s00d1_f650();                 // 0x00d51660
ScriptState* FUN_00d2e340_s00d1_f650();                 // 0x00d2e340
void*  FUN_00d9f530(void* a);                // 0x00d9f530 cdecl
float  FUN_00d1e7f0(void* a, void* b);       // 0x00d1e7f0 cdecl
void   FUN_00ad92d0(void* vec);              // 0x00ad92d0 eastl::vector<>::~vector
void*  FUN_00d1e830(int a);                  // 0x00d1e830 cdecl
void*  FUN_00d1e610();                       // 0x00d1e610 cdecl
int    FUN_00d1e5c0(void* a, void* b);       // 0x00d1e5c0 cdecl
void*  GetCurrentGameMode();                 // 0x00b5b800
void*  NounManager();                        // 0x00b3d300
void*  GetGameTerrainCursor();               // 0x00b30d70
unsigned char AbilityIsBeingTaughtToBaby(int a); // 0x00d1e6c0 cdecl
unsigned char FUN_00d1f400(void* p);         // 0x00d1f400 cdecl
int    FUN_00d1e530(void* a, void* b, void* c, void* d); // 0x00d1e530 cdecl
unsigned char FUN_00d1e8d0(void* a, void* b); // 0x00d1e8d0 cdecl
void*  CanSocial(void* a, void* b);          // 0x00d1e720 cdecl
// ---- items of slice s00d1f650 end

// @ 0x00d1e4b0
int __cdecl FUN_00d1e4b0(TuningObj* param_1, cCreature* param_2, IVtbl* param_3)
{
    if (gByte1582df5 != 1) {
        Loco* loco = param_2 ? &param_2->mLoco : 0;
        int sel = ((Slot8Vfn)((IVtblSlot8*)param_3)->mpVtbl->mSlots[2])(1);
        float v = FUN_00d99ac0(loco, sel);
        bool flag = ((param_2->mFlagsB58 >> 9) & 1u) != 0;
        float bound = param_1->GetBound(flag);
        if (v < bound)
            return 2;
    }
    return 0;
}

// @ 0x00d1e530
int __cdecl FUN_00d1e530(TuningObj* param_1, IVtbl* param_2, cCreature* param_3, IVtbl* param_4)
{
    if (param_4 == 0)
        return 3;
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        IVtbl* x = (IVtbl*)param_4->SlotC();
        int a = x->Slot4c();
        int b = param_2->Slot4c();
        if (a == b)
            return 0xc;
    }
    if (param_3 != 0) {
        if (param_3->mFlagB5e != 0)
            return 7;
        if (FUN_00c0e8d0(param_2, 6) != 0)
            return 0xc;
    }
    return FUN_00d1e4b0(param_1, param_3, param_4);
}

// @ 0x00d1e5c0
int __cdecl FUN_00d1e5c0(IVtbl* param_1, int param_2)
{
    int i = param_1->SlotB0() - 1;
    while (i >= 0) {
        if (param_1->SlotB4(i) == param_2)
            return i;
        --i;
    }
    return -1;
}

// @ 0x00d1e610
void* __cdecl FUN_00d1e610(void)
{
    switch ((uintptr_t)SP_GetCurrentGameMode()) {
    case 0x1654c01:
    case 0x1654c10:
        return ((NounMgr*)SP_NounManager())->GetAvatar();
    case 0x1654c02: {
        void* c = ((NounMgr*)SP_NounManager())->GetPlayerTribe();
        if (c)
            return ((Community*)c)->GetLeader();
        return 0;
    }
    default:
        return 0;
    }
}

// @ 0x00d1e670
void __cdecl FUN_00d1e670(void)
{
    Sphere* s = (Sphere*)((NounMgr*)SP_NounManager())->GetCurrentTerrainSphere();
    if (s) {
        s->FUN_00c77320(0x5ff7927);
        s->FUN_00c77320(0x5ff7928);
        s->FUN_00c77320(0x5ff7baf);
        s->FUN_00c77320(0x5ff7bb6);
    }
}

// @ 0x00d1e6c0
namespace SP {
bool AbilityIsBeingTaughtToBaby(int param_1)
{
    if (param_1 == -1)
        return false;
    TrainObj* o = (TrainObj*)FUN_00d51660();
    if (((o->mFlags6c >> 4) & 1u) == 0)
        return false;
    o = (TrainObj*)FUN_00d51660();
    AgentLink* a = (AgentLink*)o->mpAgent;
    if (a == 0)
        return false;
    TrainData* d = (TrainData*)a->mpData;
    if (d->mRecs[0].mTag != 0xb413edc5)
        return false;
    unsigned idx = d->mRecs[0].mIndex;
    return param_1 == d->mRecs[idx].mId;
}
}  // namespace SP

// @ 0x00d1e720
int __cdecl SP_CanSocial(cCreature* param_1, cCreature* param_2)
{
    if (param_2 == 0)
        return 4;
    void* r = param_2->FUN_00c0bc00(param_1);
    void* q = FUN_00b3d4c0(r);
    int res = ((SocialProbe*)q)->FUN_00ba3f90(param_2, param_1);
    if (res == 5 && ((OrderLink*)param_2)->mpOrder->FindSlot(2, 1, 0, 0) == -1)
        return 1;
    if (param_2->mFlagB5e != 0)
        return 1;
    if (param_2->GetSocialGoal() == 0 && ((IVtbl*)param_2)->SlotD4() != 0)
        return 6;
    if (((DataLink*)param_1)->mpData->mTag == 0x941bd4bf) {
        SocialData* p = ((DataLink*)param_2)->mpData;
        if (p->mTag != 0x341bd4be)
            return 5;
        InnerObj* in = (InnerObj*)p->mpInner;
        if (in && in->mTag8 == 0x14fcf96e && in->mFlag1e4 == 0)
            return 5;
        return 0;
    }
    return 0;
}

// @ 0x00d1e7f0
float __cdecl FUN_00d1e7f0(FlagSetObj* param_1, int param_2)
{
    int i = FUN_00d1e5c0((IVtbl*)param_1, param_2);
    int n = ((IVtbl*)param_1)->SlotB0();
    if (i >= 0 && i < n)
        return param_1->mpElems[i].mValue;
    return 0.0f;
}

// @ 0x00d1e830
void* __cdecl FUN_00d1e830(int param_1)
{
    if (param_1 == -1)
        return 0;
    IVtbl* p = (IVtbl*)FUN_00d1e610();
    if (p != 0) {
        int n = p->SlotB0();
        if (param_1 < n)
            return (void*)(uintptr_t)p->SlotB4(param_1);
        if (SP_GetCurrentGameMode() == (void*)0x1654c02) {
            int d = param_1 - n;
            if (d >= 6)
                return 0;
            return (void*)(uintptr_t)gTable169de64[d];
        }
    }
    if (SP_GetCurrentGameMode() != (void*)0x1654c01 && SP_GetCurrentGameMode() != (void*)0x1654c10)
        return 0;
    AvatarProfile* profile = ((SpeciesMgr*)GetSetting9())->GetAvatarProfile();
    return (void*)(uintptr_t)profile->mpIds[param_1];
}

// @ 0x00d1e8d0
bool __cdecl FUN_00d1e8d0(FlagSetObj* param_1, uint param_2)
{
    float f = param_1->mpElems[param_2].mValue;
    if (f == gRealOne)
        return false;
    if (param_2 >= 0x58)
        return false;
    uint mask = 1u << (param_2 & 0x1f);
    bool b = (param_1->mFlags[param_2 >> 5] & mask) != 0;
    if (b)
        return true;
    return false;
}

// @ 0x00d1e930
void __cdecl SP_UseAbility(cCreatureBase* self, int index)
{
    if (index == -1)
        return;

    cCreatureVtbl* vt = *(cCreatureVtbl**)self;
    int count = vt->fnB0(self);
    if (index >= count)
        return;

    cAbilityEntry* entry = vt->fnB4(self, index);
    int type = entry->mType;

    if (entry->mMode == 0)
        self->mE74 = index;
    else if (entry->mMode == 1)
        self->mE70 = index;

    if (((cSubC0Vtbl*)*(void**)((char*)self + 0xc0))->fn58((char*)self + 0xc0) != 0
        && entry->mB115 != 0) {
        void* x = FUN_00d51660();
        if (((*(unsigned int*)((char*)x + 0x6c) >> 4) & 1) != 0) {
            ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
                ->FUN_00c03190(0, 0x10, g_147a2d8, index, 0, 0, 0);
            return;
        }
    }

    switch (type) {
    // ---- 0x28 : interact / use ------------------------------------------
    case 0x28: {
        if (self->GetTargetAsCreature() == 0)
            break;
        self->FUN_00c196a0(index, 1, 0);
        return;
    }

    // ---- 0x27, 0x50 : sprint toggle -------------------------------------
    case 0x27:
    case 0x50: {
        if (self->FUN_00c0c120() != 0) {
            self->SetSprinting(0);
            cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
            for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
                (*it)->SetSprinting(0);
        } else {
            self->FUN_00c196a0(index, 0, 1);
            self->SetSprinting(1);
            cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
            for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
                (*it)->SetSprinting(1);
        }
        return;
    }

    // ---- 0x0d, 0x52 : stealth toggle ------------------------------------
    case 0x0d:
    case 0x52: {
        if (self->FUN_00c0c130() != 0) {
            self->SetStealthed(0, 0);
            cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
            for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
                (*it)->SetStealthed(0, 0);
            return;
        }
        if (self->FUN_00c196a0(index, 0, 1) != (unsigned int)index)
            break;
        self->SetStealthed(1, 0);
        cCreatureList* list = ((cGameNounManager*)SP_NounManager())->GetItemID();
        for (cCreatureBase** it = list->mpBegin; it != list->mpEnd; ++it)
            (*it)->SetStealthed(1, 0);
        return;
    }

    // ---- 0x10 : play visual effect --------------------------------------
    case 0x10: {
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
            ->FUN_00c03190(0x800, 0, g_147a2d8, 0, 0, 0, 0);
        cTerrainEditor* sphere =
            (cTerrainEditor*)((void*(__thiscall*)(void*))FUN_00f67d90)(SP_NounManager());
        sphere->HasFlagOrInsert(0x52da1fa);
        return;
    }

    // ---- 0x53 ------------------------------------------------------------
    case 0x53: {
        if (((self->mB58 >> 9) & 1) != 0) {
            self->FUN_00c18370();
            return;
        }
        if (self->mB137 != 0 || (self->mFlags110 & 0x1000) != 0)
            goto useAbility;
        break;
    }

    // ---- 0x11 ------------------------------------------------------------
    case 0x11: {
        if (self->mB137 == 0)
            break;
        if (SP_GetCurrentGameMode() == (void*)&g_1654c10
            && ((self->mB58 >> 9) & 1) != 0
            && *(unsigned int*)((char*)self->mPtrB20 + 0x610) > 2) {
            self->FUN_00c13650();
            return;
        }
        goto useAbility;
    }

    // ---- 0x12, 0x51 ------------------------------------------------------
    case 0x12:
    case 0x51: {
        void* x = FUN_00d2e340();
        if (*(int*)((char*)x + 8) <= 0)
            break;
        if (self->FUN_00c0e0c0(0x5485a4c) != 0)
            break;
        if (self->FUN_00c0e0c0(0x77300ff) != 0)
            break;
        if (type != 0x51)
            --*(int*)((char*)FUN_00d2e340() + 8);
        self->FUN_00c1b020((int)entry->mF104);
        return;
    }

    // ---- 0x1d : attack ---------------------------------------------------
    case 0x1d: {
        if (((self->mB58 >> 9) & 1) == 0)
            goto attack;
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))->FUN_00c03c20(index);
        return;
    }

    // ---- 0x22..0x25, 0x40, 0x4c..0x4f, 0x54..0x56 : play order -----------
    case 0x22: case 0x23: case 0x24: case 0x25:
    case 0x40: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
    case 0x54: case 0x55: case 0x56: {
        if (((self->mB58 >> 9) & 1) == 0)
            break;
        cCreatureBase* obj = (cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e);
        void* cb = self->mPtrB4c;
        if (*(int*)((char*)cb + 0x1d8) != 0x941bd4bf) {
            obj->FUN_00c03190(0x10000, 0, g_147a2d8, 0, 0,
                              (int)self->GetTargetAsCreature(), 0);
            return;
        }
        cBehaviorStimuli* stim = (cBehaviorStimuli*)((char*)cb + 8);
        stim->Set(0x10000000, 0, g_1473c70, 0);
        void* r = stim->Play(0x10000000, 0);
        *(int*)((char*)r + 0x10) = index;
        *(int*)((char*)r + 0x0c) = 0;
        return;
    }

    // ---- 0x1e..0x21, 0x3d, 0x3e, 0x41, 0x42, 0x48..0x4b : use on target --
    case 0x1e: case 0x1f: case 0x20: case 0x21:
    case 0x3d: case 0x3e: case 0x41: case 0x42:
    case 0x48: case 0x49: case 0x4a: case 0x4b: {
        cTerrainEditor* sphere =
            (cTerrainEditor*)((void*(__thiscall*)(void*))FUN_00f67d90)(SP_NounManager());
        sphere->HasFlagOrInsert(0x52da1fe);
        if (self->FUN_00c0ee60() == 0)
            break;
        cAbilityEntry* entry2 = vt->fnB4(self, index);
        float rangeFactor = FUN_00d38a30(0, self);
        void* z = FUN_00ad26d0(self->FUN_00c0ee60());
        float result = g_147a2d8;
        if (z != 0) {
            float bits = g_147a2d8;
            *(unsigned char*)&bits = (unsigned char)(entry2->mMode == 1);
            result = FUN_00d99ac0((void*)((char*)self + 0xc0), z, *(unsigned int*)&bits);
        }
        if (((self->mB58 >> 9) & 1) != 0
            && !(((entry2->mF0f4 + entry2->mF0a8) * rangeFactor) < result)) {
            if (!(result < entry2->GetBound((int)((self->mB58 >> 9) & 1)))) {
                if (((self->mB58 >> 9) & 1) != 0) {
                    ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
                        ->FUN_00c03c20(index);
                    return;
                }
                goto attack;
            }
        }
        if (g_1582df5 != 0)
            goto labAttack;
        if (entry2->GetBound((int)((self->mB58 >> 9) & 1)) > result)
            goto labAttack;
        if (result > (entry2->mF0f4 + entry2->mF0a8) * rangeFactor)
            goto labAttack;
        if (((self->mB58 >> 9) & 1) == 0)
            break;
        if (!(entry2->GetBound(1) > result))
            break;
        if (SP_GetCurrentGameMode() == (void*)&g_1654c01)
            ((cUIHints*)FUN_0067cac0())->FUN_0067c830(0xc30cd054);
        return;
    labAttack:
        if (entry2->mMode == 1)
            self->mB5c = 1;
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
            ->FUN_00c03190(0x20, 0, g_147a2d8, index, 0, 0, 0);
        return;
    }

    // ---- 0x31..0x33 ------------------------------------------------------
    case 0x31: case 0x32: case 0x33: {
        ((cCreatureBase*)FUN_00ac80d0(self, (void*)0x18eb45e))
            ->FUN_00c03190(0x8000, 0, g_147a2d8, index, 0, 0, 0);
        return;
    }

    // ---- 0x34..0x39 : give order to citizen ------------------------------
    case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39: {
        cCitizen* citizen = (cCitizen*)FUN_00ac80d0(self, (void*)0x18eb4b7);
        if (citizen == 0)
            break;
        Variant v;
        v.SetInt(index);
        citizen->GiveOrder((void*)0x16, 0, &v);
        if ((v.mFlags & 4) != 0)
            v.Destruct(0);
        return;
    }

    default:
        break;
    }

    return;

useAbility:
    self->FUN_00c1b020((int)entry->mF104);
    return;

attack:
    self->Attack(index, 0);
    return;
}

// @ 0x00d1f650
unsigned int F_d1f650(AbilityCreature* self, int abilityId)
{
    if (self->mpModelBC->mAnim.PlayIdleAnimation(0, 0x20000) != 0)
        return 1;

    if (((FUN_00d51660_s00d1_f650()->mBits6C >> 4) & 1) != 0 && ((self->mFlagsB58 >> 9) & 1) != 0)
        return AbilityIsBeingTaughtToBaby(abilityId) == 0;

    if (self->mByteB5E != 0)
        return 1;

    void** vt = self->mpVftable;
    if (((CreatureTypeVfn)vt[0x20 / 4])(self) == 0x18eb45e
        && (self->mpModelBC->mFlags1c8 & 0x1000) != 0)
        return 1;

    AbilityInfo* info = ((ResolveAbilityVfn)vt[0xb4 / 4])(self, abilityId);

    float range = info->mFloat104;
    if (range > 0.0f && range > self->mRangeE58)
        return 1;

    void* target = self->GetTargetAsCreature();
    void* other = self->FUN_00c0ee60();

    switch (info->mType) {
    case 0x11:
        if (self->mByte137 != 0)
            return 0;
        return 9;

    case 0x12:
        if (self->mByte137 == 1)
            return 1;
        if (FUN_00d2e340_s00d1_f650()->mValue8 == 0)
            return 1;
        if (self->FUN_00c0e0c0(0x5485a4c) != 0)
            return 1;
        if (self->FUN_00c0e0c0(0x77300ff) == 0)
            return 0;
        return 1;

    case 0x1e: case 0x1f: case 0x20: case 0x21:
    case 0x3d: case 0x3e: case 0x41: case 0x42: case 0x48: case 0x4a:
        {
            unsigned r = FUN_00d1e530(info, self, target, other);
            if (r != 0)
                return r;
        }
        // falls through to the shared tail of the plain "use" cases
    case 0xd: case 0x27: case 0x50: case 0x52:
        if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
            return 8;
        return 0;

    case 0x22: case 0x23: case 0x24: case 0x25:
    case 0x40: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
    case 0x54: case 0x55: case 0x56:
        {
            float r = info->mFloat104;
            if (r > 0.0f && r > self->mRangeE58)
                return 1;
            unsigned s = (unsigned)CanSocial(self, target);
            if (s != 0)
                return s;
        }
        return 0;

    case 0x31: case 0x32: case 0x33:
        if (GetCurrentGameMode() != (void*)&g_gameModeTribe)
            return 1;
        if (FUN_00d1f400(info) == 0)
            return 10;
        if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
            return 8;
        return 0;

    case 0x34: case 0x35: case 0x36: case 0x37: case 0x38: case 0x39:
        if (GetCurrentGameMode() != (void*)&g_gameModeTribe2)
            return 1;
        if (FUN_00d1f400(info) == 0)
            return 10;
        {
            AbilityCreature* leader = (AbilityCreature*)
                ((cCommunity*)((cGameNounManager_s00d1_f650*)NounManager())->GetPlayerTribe())->GetLeader();
            if (leader == 0 || leader->mByteB5E != 0
                || (leader->mpModelBC->mFlags1cc & 0x10000) != 0)
                return 0xb;
            if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
                return 0xf;
        }
        return 0;

    case 0x49:
        if (target == 0) {
            if (other != 0)
                return 7;
        } else if (((AbilityCreature*)target)->FUN_00c0c0e0() != 0) {
            return 7;
        }
        {
            unsigned r = FUN_00d1e530(info, self, target, other);
            if (r != 0)
                return r;
            if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
                return 8;
        }
        return 0;

    case 0x4b:
        if (target == 0 && other != 0)
            return 7;
        {
            unsigned r = FUN_00d1e530(info, self, target, other);
            if (r != 0)
                return r;
            if (FUN_00d1e8d0(self, (void*)abilityId) != 0)
                return 8;
        }
        return 0;

    case 0x51:
        if (self->mByte137 == 1)
            return 1;
        if ((self->mFlags110 & 0x1000) != 0)
            return 1;
        if (FUN_00d2e340_s00d1_f650()->mValue8 == 0)
            return 1;
        if (self->FUN_00c0e0c0(0x5485a4c) != 0)
            return 1;
        if (self->FUN_00c0e0c0(0x77300ff) != 0)
            return 1;
        if (info->mFloatAC > self->mRangeE58)
            return 1;
        return 0;

    case 0x53:
        if (self->mByte137 == 0 && (self->mFlags110 & 0x1000) == 0)
            return 9;
        if (!(info->mFloatAC > self->mRangeE58))
            return 0;
        return 9;
    }
    return 0;
}

// @ 0x00d1fb30
unsigned int F_d1fb30(unsigned int abilitySlot)
{
    if (abilitySlot > 5)
        return 1;

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** cvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)cvt[0x5c / 4])(terrain, &vec);

    AbilityInfo* ability = g_abilityTable[abilitySlot];
    unsigned     group = ability->mType - 5;
    if (group > 0x36) {
        FUN_00ad92d0(&vec);
        return 1;
    }

    switch (group) {
    case 0: case 1: case 2:                     // ability types 5/6/7 need tools 4/5/6
        {
            int  count = (int)(vec.mpEnd - vec.mpBegin);
            char any = 0;
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return 14;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                void*  found = ((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                CreatureModel* model = ((AbilityCreature*)found)->mpModelBC;
                if (model->mTypeId1d8 != 0xb46e8803u)
                    continue;
                cAbilityItem* item = (cAbilityItem*)FUN_00d9f530(
                    ((CreatureInner*)model->mpInner600)->mpField1a8);
                if (item->mByte51 == 0) {
                    FUN_00ad92d0(&vec);
                    return 15;
                }
                int      tool = ((AbilityCreature*)found)->FUN_00c22dc0();
                unsigned want;
                if (tool == 4)
                    want = 3;
                else if (tool == 5)
                    want = 4;
                else if (tool == 6)
                    want = 5;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                float r = FUN_00d1e7f0(found, ability);
                if (r <= 1.0f) {
                    FUN_00ad92d0(&vec);
                    return 0;
                }
                any = 1;
            }
            FUN_00ad92d0(&vec);
            return any ? 15 : 14;
        }

    case 38: case 53: case 54:                  // ability types 0x2b/0x3a/0x3b need tools 3/1/2
        {
            int  count = (int)(vec.mpEnd - vec.mpBegin);
            char any = 0;
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return 13;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                void*  found = ((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                void* other = ((AbilityCreature*)found)->FUN_00c0ee60();
                if (other == 0)
                    continue;
                if (((cAbilityOwner*)other)->GetFileCount() == 2)
                    continue;
                CreatureModel* model = ((AbilityCreature*)found)->mpModelBC;
                if (model->mTypeId1d8 != 0x5218bb3u)
                    continue;
                int      tool = ((AbilityCreature*)found)->FUN_00c22dc0();
                unsigned want;
                if (tool == 1)
                    want = 0;
                else if (tool == 2)
                    want = 1;
                else if (tool == 3)
                    want = 2;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                float r = FUN_00d1e7f0(found, ability);
                if (r <= 1.0f) {
                    FUN_00ad92d0(&vec);
                    return 0;
                }
                any = 1;
            }
            FUN_00ad92d0(&vec);
            return any ? 15 : 13;
        }

    default:                                    // every other ability type
        FUN_00ad92d0(&vec);
        return 1;
    }
}

// @ 0x00d1fe00
void F_d1fe00(unsigned int abilitySlot)
{
    if (abilitySlot > 5)
        return;

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** tvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)tvt[0x5c / 4])(terrain, &vec);

    AbilityInfo* ability = g_abilityTable[abilitySlot];
    unsigned     group = ability->mType - 5;
    if (group > 0x36) {
        FUN_00ad92d0(&vec);
        return;
    }

    switch (group) {
    case 0: case 1: case 2:                     // ability types 5/6/7 need tools 4/5/6
        {
            int count = (int)(vec.mpEnd - vec.mpBegin);
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                AbilityCreature* found = (AbilityCreature*)((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                if (found->mpModelBC->mTypeId1d8 != 0xb46e8803u)
                    continue;
                int      tool = found->FUN_00c22dc0();
                unsigned want;
                if (tool == 4)
                    want = 3;
                else if (tool == 5)
                    want = 4;
                else if (tool == 6)
                    want = 5;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                int idx = FUN_00d1e5c0(found, ability);
                if (idx == -1)
                    continue;
                if (found->mpAbilitySlots[idx].mFloat4 < g_kOne)
                    continue;
                cAnimHandle* h = found->mpModelBC->mAnim.FUN_00bc97f0(0x10000000, 0, g_kTen, 0);
                h->mFieldC = (unsigned)idx;
            }
            FUN_00ad92d0(&vec);
        }
        break;

    case 38: case 53: case 54:                  // ability types 0x2b/0x3a/0x3b need tools 3/1/2
        {
            int count = (int)(vec.mpEnd - vec.mpBegin);
            if (count <= 0) {
                FUN_00ad92d0(&vec);
                return;
            }
            for (int i = 0; i < count; i++) {
                void* so = vec.mpBegin[i];
                if (so == 0)
                    continue;
                void** svt = *(void***)so;
                AbilityCreature* found = (AbilityCreature*)((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
                if (found == 0)
                    continue;
                void* other = found->FUN_00c0ee60();
                if (other == 0)
                    continue;
                if (((cAbilityOwner*)other)->GetFileCount() == 2)
                    continue;
                if (found->mpModelBC->mTypeId1d8 != 0x5218bb3u)
                    continue;
                int      tool = found->FUN_00c22dc0();
                unsigned want;
                if (tool == 1)
                    want = 0;
                else if (tool == 2)
                    want = 1;
                else if (tool == 3)
                    want = 2;
                else
                    continue;
                if (abilitySlot != want)
                    continue;
                int idx = FUN_00d1e5c0(found, ability);
                if (idx == -1)
                    continue;
                if (found->mpAbilitySlots[idx].mFloat4 < g_kOne)
                    continue;
                cAnimHandle* h = found->mpModelBC->mAnim.FUN_00bc97f0(0x10000000, 0, g_kTen, 0);
                h->mFieldC = (unsigned)idx;
            }
            FUN_00ad92d0(&vec);
        }
        break;

    default:                                    // every other ability type does nothing
        FUN_00ad92d0(&vec);
        return;
    }
}

// @ 0x00d200a0
float F_d200a0(int range)
{
    float acc = 0.0f;

    void* ability = FUN_00d1e830(range);
    if (ability == 0)
        return acc;

    void* caster = FUN_00d1e610();
    if (caster == 0)
        return 0.0f;

    void** cvt = *(void***)caster;
    int    target = range - ((GetFieldVfn)cvt[0xb0 / 4])(caster);

    void*      buf[16];
    SpatialVec vec;
    vec.mpBegin = buf;
    vec.mpEnd   = buf;
    vec.mpCap   = buf + 16;

    void*  terrain = GetGameTerrainCursor();
    void** tvt = *(void***)terrain;
    ((TerrainCursorGetObjectsVfn)tvt[0x5c / 4])(terrain, &vec);

    int count = (int)(vec.mpEnd - vec.mpBegin);
    for (int i = 0; i < count; i++) {
        void* so = vec.mpBegin[i];
        if (so == 0)
            continue;
        void** svt = *(void***)so;
        AbilityCreature* found = (AbilityCreature*)((SpatialCastVfn)svt[0xb8 / 4])(so, 0x4f176642);
        if (found == 0)
            continue;
        int tool = found->FUN_00c22dc0() - 1;
        if ((unsigned)tool > 5)
            continue;
        if (target != tool)
            continue;
        float score = FUN_00d1e7f0(found, ability);
        acc = (acc > score) ? acc : score;
    }
    FUN_00ad92d0(&vec);
    return acc;
}
