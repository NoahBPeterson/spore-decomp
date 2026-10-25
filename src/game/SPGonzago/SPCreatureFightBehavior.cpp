// src/game/SPGonzago/SPCreatureFightBehavior.cpp -- migrated from slice(s) s00d697a0, s00d67d30, s00d67140, s00d661a0, s00d65250 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureFightBehavior.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCombatant.h"
#include "SP/cSPCreatureBase.h"
#include <math.h>
#include "SP/cLocomotiveObject.h"
#include "SP/cSPTimer.h"

// ---- items of slice s00d65250 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RecordArray {
  uint32_t* mpData;           // +0x00
  int FindNext(int index);
};
typedef int (__thiscall* FnIi)(void*, int);
char   FUN_00c0c0e0();                                 // 0x00c0c0e0
// ---- items of slice s00d65250 end

// ---- items of slice s00d661a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(asin)
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct SlotBody {
    uint32_t mBitmap;     // +0x00  bitmap of used sub-slots
    uint32_t mCount;      // +0x04  number of sub-slots
    uint32_t m0c;         // +0x08
    uint32_t m10;         // +0x0c
    int      mRefCount;   // +0x10
};
}
namespace SP {
struct cTribeFightSlots {
    union {
        struct {
            uint32_t mIndex  : 30;   // +0x00  bits 0..29: slot index of the owner
            uint32_t mFlag30 : 1;    // +0x00  bit 30
            uint32_t mUsed   : 1;    // +0x00  bit 31: set while the slot is taken
        };
        uint32_t mFlags;             // +0x00  the whole flag word
    };
    SlotBody mBody;                  // +0x04
};
}
namespace SP {
class cResizableObjectPoolT {
public:
    cTribeFightSlots* mpData;        // +0x00  (0x1583f5c)
    cTribeFightSlots* mpEnd;         // +0x04  (0x1583f60)
    uint32_t          pad08[3];      // +0x08
    int               mFreeIndex;    // +0x14
    int               mLastIndex;    // +0x18

    void GetObject(uint32_t id);     // 0xd66d60
    int  NextFree(int idx);          // 0xd660a0
};
}
namespace SP {
extern cResizableObjectPoolT sTribeFightSlotsPool;
}
namespace SP {
struct PtrRange { void** mpBegin; void** mpEnd; };  // returned by FUN_00c420d0
}
namespace SP {
class Loco {
public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual Vec3* GetPosition();                       // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
    virtual bool IsMoving();                           // +0x58
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
    virtual float GetRadius();                         // +0x74

    PtrRange* GetNeighbourRange();                     // 0xc420d0
};
}
namespace SP {
class cSPCreatureBase_s00d6_61a0;
}
namespace SP {
struct NeighbourEntry {
    float            mDistance;    // +0x00
    uint32_t         m04;          // +0x04
    cSPCreatureBase_s00d6_61a0* mpCreature;   // +0x08
};
}
namespace SP {
struct AbilityMask {
    uint32_t mBits[3];                              // +0x00
    bool IsValid(NeighbourEntry* e);                // SP::IsValidNeighbourEntry 0xc02600
};
}
namespace SP {
struct NeighbourIter {
    NeighbourEntry** mpCur;                         // +0x00
    void SkipInvalid();                             // 0xb3d850
};
}
namespace SP {
struct FightGroup {
    char        pad00[0x1a4];       // +0x00
    int         m1a4;               // +0x1a4
    bool        m1a8;               // +0x1a8
};
}
namespace SP {
struct Behav {
    char        pad00[0x1d8];       // +0x00
    int         m1d8;               // +0x1d8
    char        pad1dc[0x600 - 0x1dc];
    FightGroup* mpGroup;            // +0x600
    void SetTargetFromGroup();      // 0xbcb430
};
}
namespace SP {
struct CreatureStateFlags {
    uint32_t mBits0  : 8;   // +0x00  bits 0..7
    uint32_t mFlag8  : 1;   // +0x00  bit 8
    uint32_t mRest   : 23;
};
}
namespace SP {
struct TargetObj { char pad[0x578]; };   // opaque sub-object living at creature+0x5a8
}
namespace SP {
class cSPCreatureBase_s00d6_61a0 {
public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
    virtual uint32_t GetTypeId();                      // +0x20
virtual void s09();
virtual void s10();
    virtual bool IsDead();                             // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
    virtual int GetSpatialId();                        // +0x4c
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74  (0xd66250)
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
    virtual void* GetAbility(int idx);                 // +0xb4
    virtual cSPCreatureBase_s00d6_61a0* GetByTypeHash(uint32_t hash);  // +0xb8
    virtual void s47();
    virtual bool CanReach(void* o, float a, float b);  // +0xc0

    char      pad004[0xc0 - 4];
    Loco      mLoco;                                   // +0xc0
    char      pad0c4[0x135 - 0xc4];
    uint8_t   mb135;                                   // +0x135
    char      pad136[0x5a8 - 0x136];
    TargetObj mTargetObj;                              // +0x5a8
    int       mB20;                                    // +0xb20
    char      padb24[0xb4c - 0xb24];
    Behav*    mpBehav;                                 // +0xb4c
    char      padb50[0xb58 - 0xb50];
    CreatureStateFlags mStateFlags;                    // +0xb58
    char      padb5c[0xb5e - 0xb5c];
    uint8_t   mB5E;                                    // +0xb5e
    char      padb5f[0x1124 - 0xb5f];
    NeighbourEntry** mNeighbourBegin;                  // +0x1124
    NeighbourEntry** mNeighbourEnd;                    // +0x1128

    int  GetTribe();                                   // 0xc22f50
    void* GetCombatTarget();                           // 0xc0ee60
    cSPCreatureBase_s00d6_61a0* GetCombatTargetCreature();        // 0xc0ee90
    bool IsTribal();                                   // 0xc232c0
    bool CanBeFightTarget();                           // 0xc0b770
    int  GetFightState();                              // 0xc0c2f0
    struct SpeciesTraits* GetTraits();                 // 0xc0c1a0
    bool Flag388();                                    // 0xc0c0e0
    bool IsInRange(cSPCreatureBase_s00d6_61a0* other);            // 0xc02eb0
    int  GetFightValue(cSPCreatureBase_s00d6_61a0* other);        // 0xc0b8e0
    int  CheckRange(AbilityMask* mask, float range, int a, int b, int c,
                    int d, int e);                     // 0xc12410
};
}
namespace SP {
typedef cSPCreatureBase_s00d6_61a0 cSPCreatureCitizen;
}
namespace SP {
class cCombatant_s00d6_61a0 {
public:
virtual void s00();
virtual void s01();
    virtual Loco* GetSpatial();                        // +0x08
    virtual cSPCreatureBase_s00d6_61a0* GetCreature();            // +0x0c
    int GetDamageState();                              // 0x8e7f80
};
}
namespace SP {
struct RBNode { RBNode* mpLeft; RBNode* mpRight; RBNode* mpParent; uint8_t mColor; };
}
namespace SP {
struct CooldownMap { int mCompare; RBNode mAnchor; int mSize; };   // 0x18 bytes
}
namespace SP {
struct SpeciesTraits { char pad[0x3f0]; int m3f0; short m3f4; };
}
namespace SP {
struct FightMem {
    int      mTarget;               // +0x00
    float    mEvalTimer;            // +0x04
    float    mMoveTimer;            // +0x08
    float    mNoActivityTimer;      // +0x0c
    float    mMaxRange;             // +0x10
    float    mAbilityTimer;         // +0x14
    int      mState;                // +0x18
    float    mDistance;             // +0x1c
    int      m20;                   // +0x20
    short    mStandardAttackCounter;// +0x24
    char     pad26[2];
    cSPCreatureBase_s00d6_61a0* mpCreature;    // +0x28
    int      m2c;                   // +0x2c
    int      mAttackAnim;           // +0x30
    int      m34;                   // +0x34
    int      mFrustrationAnim;      // +0x38
    int      m3c;                   // +0x3c
    float    m40;                   // +0x40
    bool     m44;                   // +0x44
    char     pad45[0x48 - 0x45];
    void*    mp48;                  // +0x48
    short    m4c;                   // +0x4c
    bool     m4e;                   // +0x4e
    bool     mbAttackOnSight;       // +0x4f
    float    m50;                   // +0x50
    float    m54;                   // +0x54
    float    m58;                   // +0x58
    float    m5c;                   // +0x5c
    int      m60;                   // +0x60
    CooldownMap mCooldowns;         // +0x64
    bool     m44b;                  // +0x7c

    FightMem* Init(cSPCreatureBase_s00d6_61a0* c);   // 0xd66e70
    void Release();                       // 0xd670e0
};
}
namespace SP {
extern unsigned char DAT_01582df5;  // byte passed to the range query
}
namespace SP {
extern float DAT_0147bc0c;          // FLT_MAX
}
namespace SP {
extern float DAT_01485544;          // 0.75f
}
namespace SP {
void   FUN_00d65500(int arg);
}
namespace SP {
float  FUN_00d38a30(int which, cSPCreatureBase_s00d6_61a0* c);
}
namespace SP {
cSPCreatureBase_s00d6_61a0* FUN_00d99500(void* obj);
}
namespace SP {
void*  FUN_00ae3390(void* p);
}
namespace SP {
float  DistanceBetweenBodies(const Vec3* a, float rA, const Vec3* b, float rB, bool clamp);
}
// ---- items of slice s00d661a0 end

// ---- items of slice s00d67140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_00d66250(void* out, void* obj, float value);
extern "C" void* FUN_00bc9b00();
extern "C" void* FUN_00bca620(void* self, int key, void* fn, void* pair);
extern "C" int   FUN_00d99470(void* p);
extern "C" void* FUN_00d99a10(void* p);
extern "C" int   FUN_008e7f80(void* self);
extern "C" void* SP_GetAnimalFromStimulus(void* s);
extern "C" void* SP_GetCreatureFromStimulus(void* s);
extern "C" void* SP_GetSpeciesProfile(void* creature);
extern "C" void* SP_cCreatureModeStrategy_Instance(int key, void* out);
extern "C" int   FUN_00d995c0();
typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;
struct VT {
    virtual void  q00();
    virtual void  q01();                  // +0x04
    virtual void* q02();                  // +0x08
    virtual void* q03(int id);            // +0x0c
    virtual void  q04();
    virtual void  q05();
    virtual void  q06();
    virtual void  q07();
    virtual void* q08();                  // +0x20
    virtual void  q09();
    virtual void  q10();
    virtual void* q11();                  // +0x2c
    virtual void  q12();
    virtual void  q13();
    virtual void  q14();
    virtual void  q15();
    virtual void  q16();
    virtual void  q17();
    virtual void  q18();
    virtual void  q19();
    virtual void  q20();
    virtual void  q21();
    virtual bool  q22();                  // +0x58
    virtual void* q23(int id);            // +0x5c
    virtual void  q24();
    virtual void  q25();                  // +0x64
    virtual void  q26();
    virtual void  q27();
    virtual void  q28();
    virtual float q29();                  // +0x74
    virtual void  q30();
    virtual void  q31();
    virtual void  q32();
    virtual void  q33(void* a, int b, int c);   // +0x84
    virtual void  q34();
    virtual void  q35();
    virtual void  q36();
    virtual void  q37();
    virtual void  q38();
    virtual void  q39();
    virtual void  q40();
    virtual void  q41();
    virtual void  q42();
    virtual void  q43();
    virtual void  q44();
    virtual void  q45();
    virtual void  q46();
    virtual void  q47();                  // +0xbc
    virtual void  q48();                  // +0xc0
    virtual void  q49();
    virtual void  q50();
    virtual void  q51();
    virtual void  q52();
    virtual void  q53();
    virtual void  q54();
    virtual void  q55();
    virtual void  q56();
    virtual void  q57();
    virtual void  q58();
    virtual void  q59();                  // +0xec
    virtual void  q60();
    virtual void  q61();
    virtual bool  q62();                  // +0xf8
    virtual void  q63();
};
struct SlotPayload {
    U32   mNounID;    // +0x00
    U32   mType;      // +0x04
    U32   mToken;     // +0x08
    U32   mTimerBits; // +0x0c  (float timer stored as its bit pattern)
    U32   mCount;     // +0x10
};
struct Slot {
    U32         mFlags;     // +0x00
    SlotPayload mPayload;   // +0x04
    // sizeof == 0x18
};
struct SlotPool {
    Slot* mpBegin;          // +0x00
    Slot* mpEnd;            // +0x04
    Slot* mpCapacity;       // +0x08
    U32   mPad0C;           // +0x0c
    U32   mPad10;           // +0x10
    U32   mMinFreeIndex;    // +0x14
    U32   mFreeListHead;    // +0x18

    Slot* begin()  { return mpBegin; }
    Slot* end()    { return mpEnd; }
    U32   count()  { return (U32)(mpEnd - mpBegin); }

    void  reserve(U32 newCapacity);
    void  insert_impl(Slot* position, Slot* value);
    U32   alloc(const SlotPayload* value);
};
extern SlotPool gTribeFightSlotsPool;
struct TreeObject {
    U32   mUnk00;      // +0x00
    void* mLeft;       // +0x04
    void* mRight;      // +0x08
    void* mRoot;       // +0x0c
    U8    mByte10;     // +0x10
    U8    mPad11[3];
    U32   mCount;      // +0x14
};
struct Stimuli {
    void  Play(int a, int b);
    void  ClearAll(int a, int b);
};
struct B4CObj;
struct FightAction {
    U32        mSlot;       // +0x00
    float      mF04;        // +0x04
    float      mF08;        // +0x08
    float      mF0C;        // +0x0c
    float      mF10;        // +0x10
    float      mF14;        // +0x14
    U32        mField18;    // +0x18
    float      mF1C;        // +0x1c
    void*      mpField20;   // +0x20
    U16        mW24;        // +0x24
    U8         mPad26[2];
    void*      mpCreature;  // +0x28
    U32        mField2C;    // +0x2c
    void*      mpField30;   // +0x30
    void*      mpField34;   // +0x34
    U32        mField38;    // +0x38
    U32        mField3C;    // +0x3c
    float      mF40;        // +0x40
    U8         mByte44;     // +0x44
    U8         mPad45[3];
    void*      mpField48;   // +0x48
    U16        mW4C;        // +0x4c
    U8         mByte4E;     // +0x4e
    U8         mByte4F;     // +0x4f
    float      mF50;        // +0x50
    float      mF54;        // +0x54
    float      mF58;        // +0x58
    float      mF5C;        // +0x5c
    U32        mField60;    // +0x60
    TreeObject mTree64;     // +0x64 (root at +0x70)
};
struct FightGroup_s00d6_7140 {
    U32   mPad00[4];        // +0x00
    U32   mField10;         // +0x10
    U8    mPad14[0x1a4 - 0x14];
    U32   mSlot1A4;         // +0x1a4
    U8    mByte1A8;         // +0x1a8
    U8    mPad1A9[3];
    U32   mVec1AC[3];       // +0x1ac .. +0x1b4
    U8    mPad1B8[0x1d8 - 0x1b8];
    U32   mField1D8;        // +0x1d8
};
struct B4CObj {
    U32       mPad00[2];        // +0x00
    Stimuli   mStimuli;         // +0x08
    U8        mPad0C[0x1d8 - 0x0c];
    U32       mField1D8;        // +0x1d8
    U8        mPad1DC[0x600 - 0x1dc];
    FightGroup_s00d6_7140* mpGroup;        // +0x600
};
struct Combatant : VT { };      // embedded combatant view (+0x5a8)
struct SubSys : VT { };         // creature subsystem (+0xc0)
struct Creature : VT {
    U8      mPad04[0xc0 - 0x04];
    SubSys  mSubSys;            // +0xc0
    U8      mPadC4[0x5a8 - 0xc4];
    Combatant mCombatant;       // +0x5a8
    U8      mPad5AC[0x5b4 - 0x5ac];
    TreeObject mTree;           // +0x5b4
    U8      mPad5CC[0xb4c - 0x5cc];
    B4CObj* mpB4C;              // +0xb4c
    U8      mPadB50[0xb58 - 0xb50];
    U32     mFlagsB58;          // +0xb58
    U8      mPadB5C[2];
    U8      mFlagB5E;           // +0xb5e
    U8      mPadB5F[0xe8c - 0xb5f];
    U32     mFieldE8C;          // +0xe8c
    U32     mFieldE90;          // +0xe90
    float   mFieldE94;          // +0xe94
    void*   mpFieldE98;         // +0xe98
    void*   mpFieldE9C;         // +0xe9c
    U8      mPadEA0[0x1124 - 0xea0];
    U8      mField1124[0x10];   // +0x1124

    void  ResetFightAction();   // helper used by several callees
};
struct HasB4C {
    U8       mPad00[0xb4c];
    B4CObj*  mpB4C;         // +0xb4c
};
struct EntryWithPtr {       // a neighbour entry: pointer at +0x08
    void* mpField00;
    void* mpField08;
};
struct Arg7Object {         // activation context object
    void* mpField04;
    void* mpField08;
};
struct FieldHolder {        // object owning a dword at +0x3f8
    U8  mPad00[0x3f8];
    U32 mField3F8;
};
extern "C" void* FUN_00bcb0b0(void* self, int key, U32 b, U32 c, const char* name);
extern "C" U32   FUN_00b5b800();
struct FnD66E70    { void* __thiscall f(Creature* creature); };
struct FnD670E0    { void __thiscall f(); };
struct FnC14750    { void __thiscall f(int a); };
struct FnC0EE60    { void* __thiscall f(); };
struct FnC19940    { void __thiscall f(int a); };
struct FnC232B0    { char __thiscall f(); };
struct FnC0C0E0    { char __thiscall f(); };
struct FnGetTarget { void* __thiscall f(); };
struct FnB41A40    { void __thiscall f(void* collection, void* ctx); };
struct FnIsValid   { char __thiscall f(void* entry); };
struct FnD39360    { void __thiscall f(); };
struct FnBC9B50    { char __thiscall f(); };
struct FnBCB480    { void __thiscall f(void* a, void* b, int c, int d); };
struct FnBC97F0    { void __thiscall f(int a, int b, float c, void* d); };
struct FnSpotPlay   { void* __thiscall f(int a, int b); };
struct FnInterrupt  { int __thiscall f(int id, int a, int b); };
struct FnPlay2      { void* __thiscall f(int a, int b); };
SlotPayload* FUN_00d66320(U32 slot);
SlotPayload* FUN_00d67660();
int FUN_00d678d0(FightAction* self, U8 param);
struct FindKey {
    void* mpObject;
    void* mpCreature;
};
// ---- items of slice s00d67140 end

// ---- items of slice s00d67d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
static inline Vec3 operator-(const Vec3& a, const Vec3& b) { Vec3 r = { a.x - b.x, a.y - b.y, a.z - b.z }; return r; }
}
namespace SP {
static inline Vec3 operator+(const Vec3& a, const Vec3& b) { Vec3 r = { a.x + b.x, a.y + b.y, a.z + b.z }; return r; }
}
namespace SP {
static inline Vec3 operator*(const Vec3& a, float s) { Vec3 r = { s * a.x, s * a.y, s * a.z }; return r; }
}
namespace SP {
static inline Vec3 operator-(const Vec3& a) { Vec3 r = { -a.x, -a.y, -a.z }; return r; }
}
namespace SP {
static inline float Dot(const Vec3& a, const Vec3& b) { return a.y * b.y + a.z * b.z + b.x * a.x; }
}
namespace SP {
static inline float DistSq(const Vec3& a, const Vec3& b)
{
    Vec3 d = a - b;
    return d.z * d.z + d.y * d.y + d.x * d.x;
}
}
namespace SP {
static inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
}
namespace SP {
static inline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }
}
namespace SP {
Vec3  normalized_safe(const Vec3& v);                  // 0x449c20 (sret)
}
namespace SP {
Vec3  Vector3_Normalize(const Vec3& v);                // 0x436ce0 (sret)
}
namespace SP {
float Length(const Vec3& v);                           // 0x4885d0
}
namespace SP {
bool  operator!=(const Vec3& a, const Vec3& b);        // 0x41dd30
}
namespace SP {
extern Vec3 kZeroVec;                                  // 0x169ecbc
}
namespace SP {
struct LocoState {
    char     pad00[0x5c];
    int      mHasPath;                                 // +0x5c
    char     pad60[0x70 - 0x60];
    uint32_t mMoveFlags;                               // +0x70
    const Vec3* GetGoal();                             // 0xc423c0
};
}
namespace SP {
class cLocomotiveObject_s00d6_7d30 { public:
    const Vec3& GetVelocity();                         // 0xd20610
};
}
namespace SP {
struct Loco_s00d6_7d30 {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual const Vec3* GetPosition();                 // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
    virtual bool IsMoving();                           // +0x58
    virtual const Vec3* GetFacing(Vec3* out);          // +0x5c
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual float Slot70();                            // +0x70
    virtual float GetRadius();                         // +0x74
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
virtual void s45();
virtual void s46();
virtual void s47();
virtual void s48();
virtual void s49();
virtual void s50();
virtual void s51();
virtual void s52();
virtual void s53();
virtual void s54();
virtual void s55();
virtual void s56();
virtual void s57();
virtual void s58();
virtual void s59();
virtual void s60();
virtual void s61();
    virtual bool SlotF8();                             // +0xf8
    LocoState* GetState();                             // 0xc41ec0
    bool IsNearGoal();                                 // 0xc42e20
};
}
namespace SP {
typedef Loco_s00d6_7d30 Spatial;
}
namespace SP {
struct Handle { char pad[0x24]; int m24; };
}
namespace SP {
struct TargetObj_s00d6_7d30 {
virtual void s00();
virtual void s01();
    virtual Spatial* GetOwner();                       // +0x08
    virtual Handle*  GetHandle();                      // +0x0c
};
}
namespace SP {
struct Ability {
    char  pad00[0x7c];
    int   m7c;                                         // +0x7c
    char  pad80[0x9c - 0x80];
    float mCooldown;                                   // +0x9c
    float mA0;                                         // +0xa0
    char  padA4[0xa8 - 0xa4];
    float mRange;                                      // +0xa8
    char  padAC[0xf4 - 0xac];
    float mF4;                                         // +0xf4
    int   mF8;                                         // +0xf8
    float GetBound(bool b);                            // TuningObj::GetBound 0x4d3d70
};
}
namespace SP {
class cSPCreatureBase_s00d6_7d30;
}
namespace SP {
struct GroupMember { bool mActive; cSPCreatureBase_s00d6_7d30* mpCreature; int m8; };
}
namespace SP {
struct FightGroup_s00d6_7d30 {
    char        pad00[0x14];
    int         mLeaderIdx;                            // +0x14
    uint32_t    mCount;                                // +0x18
    char        pad1c[4];
    GroupMember mMembers[(0x1a4 - 0x20) / 12];         // +0x20
    int         m1a4;                                  // +0x1a4
    char        pad1a8[4];
    Vec3        mLeaderPos;                            // +0x1ac
    bool        FUN_00a75010();
};
}
namespace SP {
struct IdleRes;
}
namespace SP {
struct BehStim {
    IdleRes* PlayIdleAnimation(uint32_t a, uint32_t b);           // 0xbc96a0
    void SetStimulus(int a, uint32_t b, float c, void* who);      // 0xbc97f0
};
}
namespace SP {
struct Behav_s00d6_7d30 {
    char      pad00[8];
    BehStim   mStim;                                   // +0x08
    char      pad09[0x600 - 9];
    FightGroup_s00d6_7d30* mpGroup;                               // +0x600
};
}
namespace SP {
struct Herd {
    char  pad[0x164];
    cSPCreatureBase_s00d6_7d30* mpLeader;                         // +0x164
    struct ListNode { ListNode* next; ListNode* prev; } mList;     // +0x168
    bool HasMembers() { return mList.next != &mList; }
};
}
namespace SP {
class cSPTimer_s00d6_7d30 { public: uint64_t GetElapsedTime(); };       // 0xbc3190
}
namespace SP {
struct Sim { char pad[0x4c8]; bool mUseOtherTargeting; };     // FUN_00c04750 result
}
namespace SP {
struct TargetQuery { virtual void s0(); virtual void s1(); virtual void s2(); virtual void* Get(const void* id); };
}
namespace SP {
struct TargetSrc { TargetQuery* FUN_00c7d930(); };
}
namespace SP {
struct SimSingleton {
    static SimSingleton* Get();                        // 0xc03260
    void* FindTarget(void* who, float a, float b);     // 0xf30cc0
};
}
namespace SP {
struct KeyPair { int a, b; };
}
namespace SP {
struct HandleSet { KeyPair insert(const int& key); }; // 0xa18440
}
namespace SP {
struct Tuning { char pad[0x58c]; float m58c; };
}
namespace SP {
struct AttackEntry { int m0; float mReadiness; int m8, mc; };
}
namespace SP {
class cSPCreatureBase_s00d6_7d30 { public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
    virtual uint32_t GetTypeId();                      // +0x20
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
    virtual void s32();
    virtual void SetTarget(void* o, int a, int b);     // +0x84
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
    virtual Ability* GetAbility(int idx);              // +0xb4
virtual void s46();
virtual void s47();
    virtual bool CanReach(void* o, float a, float b);  // +0xc0

    char      pad004[0xc0 - 4];
    Loco_s00d6_7d30      mLoco;                                   // +0xc0
    char      pad0c4[0x330 - 0xc4];
    uint8_t   mFlags330;                               // +0x330
    char      pad331[0x5a8 - 0x331];
    char      mTargetable[0x5b4 - 0x5a8];              // +0x5a8
    HandleSet mSeenHandles;                            // +0x5b4
    char      pad5b5[0x670 - 0x5b5];
    TargetSrc mTargetSrc;                              // +0x670
    char      pad671[0xb20 - 0x671];
    Tuning*   mpTuning;                                // +0xb20
    char      padb24[0xb4c - 0xb24];
    Behav_s00d6_7d30*    mpBehav;                                 // +0xb4c
    char      padb50[0xb58 - 0xb50];
    uint32_t  mStateFlags;                             // +0xb58
    uint8_t   mbFlagB5C;                               // +0xb5c
    char      padb5d[0xc28 - 0xb5d];
    AttackEntry* mpAttacks;                            // +0xc28
    char      padc2c[0xe8c - 0xc2c];
    int       mActiveTarget;                           // +0xe8c
    char      pade90[0xfc0 - 0xe90];
    cSPTimer_s00d6_7d30  mTimer;                                  // +0xfc0

    TargetObj_s00d6_7d30* GetTargetObj();                         // 0xc0ee60
    int   GetTargetAsCreature();                       // 0xc0ee70
    cSPCreatureBase_s00d6_7d30* GetTargetCreature();              // 0xc0ee90
    Sim*  FUN_00c04750();
    Herd* FUN_00c04590();
    bool  FUN_00c0c0e0();
    bool  FUN_00c0b780();
    bool  AnimationFinished(int id);                   // 0xc12400
    bool  AnimationFinished2(int id);                  // 0xc123f0
    int   InterruptAnimation(int id, int a, int b);    // 0xc12310
    int   PlayAnimation(int id, int a, int b);         // 0xc12190
    bool  FUN_00c0e0c0(int id);
    void  FUN_00c14750(int a);
    void  Attack(int idx, int* outAnim);               // 0xc1e460
    void  MoveToPointAtSpeed(int mode, const Vec3& p, float s0, float s1);                        // 0xc1c1d0
    void  MoveToPointAndFacingAtSpeed(int mode, const Vec3& p, const Vec3& f, float s0, float s1); // 0xc1c5c0
    void  TryJumpToTarget(int a, const Vec3& p, const Vec3& vel, float r, int b);                // 0xc190e0
};
}
namespace SP {
struct CooldownNode { CooldownNode* mpNodeRight; CooldownNode* mpNodeLeft; CooldownNode* mpNodeParent; int mColor; int first; float second; };
}
namespace SP {
CooldownNode* RBTreeIncrement(const CooldownNode* p);  // eastl::RBTreeIncrement 0x921580
}
namespace SP {
struct CooldownIter {
    CooldownNode* mpNode;
    CooldownIter(CooldownNode* p) : mpNode(p) {}
    CooldownIter(const CooldownIter& x) : mpNode(x.mpNode) {}
    CooldownIter& operator++() { mpNode = RBTreeIncrement(mpNode); return *this; }
    bool operator!=(const CooldownIter& x) const { return mpNode != x.mpNode; }
};
}
namespace SP {
struct CooldownMap_s00d6_7d30 {
    int          mCompare;                             // +0x00
    CooldownNode mAnchor;                              // +0x04 (only right/left/parent/color used)
    CooldownIter begin() { return CooldownIter(mAnchor.mpNodeLeft); }
    CooldownIter end()   { return CooldownIter(&mAnchor); }
    CooldownIter erase(CooldownIter it);               // 0x8dae70
    float& operator[](const int& key);                 // 0xc8c550
};
}
namespace SP {
struct FightMem_s00d6_7d30 {
    float    m00;
    float    mEvalTimer;                               // +0x04
    float    mMoveTimer;                               // +0x08
    float    mNoActivityTimer;                         // +0x0c
    float    m10;                                      // +0x10
    float    m14;                                      // +0x14
    int      mState;                                   // +0x18
    float    mDistance;                                // +0x1c
    int      m20;
    short    mStandardAttackCounter;                   // +0x24
    char     pad26[0x2c - 0x26];
    int      mFirstHitAnim;                            // +0x2c
    int      mAttackAnim;                              // +0x30
    int      mFrustrationAnim;                         // +0x34
    int      m38;
    int      m3c;                                      // +0x3c
    float    m40;                                      // +0x40
    bool     m44;                                      // +0x44
    char     pad45[0x4e - 0x45];
    bool     m4e;                                      // +0x4e
    bool     mbAttackOnSight;                          // +0x4f
    float    m50;                                      // +0x50
    float    m54;                                      // +0x54
    float    mFrustrationTimer;                        // +0x58
    float    mAbilityTimer;                            // +0x5c
    int      mAbilityIdx;                              // +0x60
    CooldownMap_s00d6_7d30 mCooldowns;                            // +0x64
    bool FUN_00d678d0(bool b);
};
}
namespace SP {
struct PropertyList;
}
namespace SP {
class cCreatureModeStrategy { public: char pad[0xb4]; PropertyList* mpProps; };
}
namespace SP {
extern cCreatureModeStrategy* g_CreatureModeStrategy;  // 0x169e294
}
namespace SP {
float GetPropertyT_float(PropertyList* p, uint32_t hash, float def);  // SP::GetPropertyT<float> 0x4e1c70
}
namespace SP {
struct PlanetModelT { Vec3 ProjectToSurface(const Vec3* p); };       // 0xb81630
}
namespace SP {
PlanetModelT* PlanetModel();                           // 0xb3d350
}
namespace SP {
struct RandomLinearCongruential { double RandomDoubleUniform(); };
}
namespace SP {
extern RandomLinearCongruential sMathRandom;          // 0x1601760
}
namespace SP {
extern char g_CreatureGameMode;                        // 0x1654c10
}
namespace SP {
extern int  DAT_01582ee8;
}
namespace SP {
extern char DAT_013f94d4[];
}
namespace SP {
void* GetCurrentGameMode();                            // 0xb5b800
}
namespace SP {
const uint32_t kTypeCreatureAnimal = 0x18eb4b7;
}
namespace SP {
const uint32_t kTypeA = 0x18ebadc;
}
namespace SP {
const uint32_t kTypeB = 0x18c6de8;
}
namespace SP {
struct CastObj { char pad[0xb1c]; int mb1c; };
}
namespace SP {
cSPCreatureBase_s00d6_7d30* FUN_00d99470_s00d6_7d30(int creature);
}
namespace SP {
int        FUN_00d99500(cSPCreatureBase_s00d6_7d30* c);
}
namespace SP {
float      FUN_00d99ac0(Loco_s00d6_7d30* me, Spatial* other, int a);
}
namespace SP {
bool       FUN_00d659e0(FightMem_s00d6_7d30* m, cSPCreatureBase_s00d6_7d30* c, int flags, TargetObj_s00d6_7d30* t, cSPCreatureBase_s00d6_7d30* tc);
}
namespace SP {
bool       FUN_00d65c40(FightMem_s00d6_7d30* m, cSPCreatureBase_s00d6_7d30* c, TargetObj_s00d6_7d30* t);
}
namespace SP {
float      FUN_00f264b0(cSPCreatureBase_s00d6_7d30* c);
}
namespace SP {
int        FUN_00d998f0(const void* p);
}
namespace SP {
int        FUN_00d66710(FightMem_s00d6_7d30* m, cSPCreatureBase_s00d6_7d30* c, TargetObj_s00d6_7d30* t, int* prevIdx, float* maxR, float* minR);
}
namespace SP {
float      FUN_00d65530(float base, bool b);
}
namespace SP {
cSPCreatureBase_s00d6_7d30* FUN_00d66600(cSPCreatureBase_s00d6_7d30* c, int tgt);
}
namespace SP {
cSPCreatureBase_s00d6_7d30* FUN_00d655d0(cSPCreatureBase_s00d6_7d30* c, int tgt, float a, float b);
}
namespace SP {
cSPCreatureBase_s00d6_7d30* FUN_00d66400(cSPCreatureBase_s00d6_7d30* c, void* animal, float a, float b);
}
namespace SP {
void*      FUN_00ac80d0(const void* o, uint32_t type);
}
namespace SP {
void*      FUN_00ae6740(TargetQuery* q);
}
namespace SP {
void*      FUN_00d99a10(IdleRes* idle);
}
namespace SP {
float      FUN_00d38a30(int which, cSPCreatureBase_s00d6_7d30* c);
}
namespace SP {
Vec3       FUN_00d65580(cSPCreatureBase_s00d6_7d30* c, const Vec3& p);
}
namespace SP {
bool       GetFightSlots(cSPCreatureBase_s00d6_7d30* c, FightMem_s00d6_7d30* m, int arg);       // 0xd66370
}
namespace SP {
bool       FUN_00d65fe0(FightMem_s00d6_7d30* m, cSPCreatureBase_s00d6_7d30* c, TargetObj_s00d6_7d30* t, float minR, float maxR);
}
namespace SP {
cLocomotiveObject_s00d6_7d30* FUN_00b33e40(Spatial* s);
}
namespace SP {
cLocomotiveObject_s00d6_7d30* FUN_00bfc6c0(TargetObj_s00d6_7d30* t);
}
namespace SP {
static __forceinline bool IsCreatureGame() { return GetCurrentGameMode() == &g_CreatureGameMode; }
}
// ---- items of slice s00d67d30 end

// ---- items of slice s00d697a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct LocoState_s00d6_97a0 {
    uint32_t pad00[0x5c / 4];
    int      mHasPath;      // +0x5c
    uint32_t pad60[(0x70 - 0x60) / 4];
    uint32_t mMoveFlags;    // +0x70
    Vec3* GetPos();         // FUN_00c423c0
};
}
namespace SP {
struct Loco_s00d6_97a0 {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual Vec3* GetPosition();                       // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
    virtual bool IsMovingFast();                       // +0x58
    virtual Vec3* GetFacing(Vec3* out);                // +0x5c
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
    LocoState_s00d6_97a0* GetState();                             // FUN_00c41ec0
};
}
namespace SP {
struct IdleRes_s00d6_97a0 { uint32_t pad[3]; int mId; };
}
namespace SP {
struct BehStim_s00d6_97a0 {
    IdleRes_s00d6_97a0* PlayIdleAnimation(uint32_t a, uint32_t b);
    void ClearAll(uint32_t a, uint32_t b);
};
}
namespace SP {
struct Big { uint32_t pad[0x1a4 / 4]; int m1a4; void FUN_00bc9b10(); };
}
namespace SP {
struct Behav_s00d6_97a0 {
    uint32_t pad0[2];
    uint32_t pad1[(0x1c8 - 8) / 4];
    uint32_t mFlags;                                   // +0x1c8
    uint32_t pad2[(0x600 - 0x1cc) / 4];
    Big*     mBig;                                     // +0x600
};
}
namespace SP {
struct Obj {
virtual void s00();
virtual void s01();
    virtual Obj* GetOwner();                           // +0x08
    virtual int  GetHandle();                          // +0x0c
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual Vec3* GetPosition();                       // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                         // +0x74
    uint32_t pad04[2];
    int      m0c;
    uint32_t pad10[(0x7c - 0x10) / 4];
    int      m7c;
    uint32_t pad80[(0xa8 - 0x80) / 4];
    float    mA8;
    uint32_t padac[(0xf4 - 0xac) / 4];
    float    mF4;
    uint32_t padf8[(0x130 - 0xf8) / 4];
    int      m130;
    bool  FUN_00c0b000();
    float GetBound(int);                               // TuningObj::GetBound
    void  FUN_00aca360();
    void  FUN_00acd2d0();
};
}
namespace SP {
struct CitSub { int FUN_00bca0c0(int a, int b, int c, int d); };
}
namespace SP {
struct Citizen {
    uint32_t pad[0xb48 / 4];
    CitSub*  mSub;                                     // +0xb48
    int GetTribe();
};
}
namespace SP {
struct StratMgr {
    int  FUN_00bc2240(int hash, Vec3 pos);
    void FUN_00bc23d0(int handle, Vec3 pos);
    void FUN_00bc2180(int handle);
};
}
namespace SP {
struct TribeStrategy { uint32_t pad[0x1c8 / 4]; StratMgr* mMgr; };
}
namespace SP {
struct RefSlot { void* mp; void Assign(int v); };       // FUN_00ae6690
}
namespace SP {
struct FightState {
    int      mTarget;      // +0x00
    int      mId;          // +0x04
    int      mSlot;        // +0x08
    int      mStratHandle; // +0x0c
    float    mTimer0;      // +0x10
    float    mTimer1;      // +0x14
    float    mTimer2;      // +0x18
    float    mAttackTimer; // +0x1c
    float    mAttackReset; // +0x20
    bool     mB24;         // +0x24
    bool     mB25;         // +0x25
    bool     mNoRetarget;  // +0x26
    int      mEventAnim;   // +0x28
    int      mAnim;        // +0x2c
    int      mHintArg;     // +0x30
    RefSlot  mRef;         // +0x34
};
}
namespace SP {
class cSPCreatureBase_s00d6_97a0 { public:
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
    virtual void s32();
    virtual void SetTarget(Obj* o, int a, int b);      // +0x84
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
virtual void s44();
    virtual Obj* GetObjectById(int id);                // +0xb4
virtual void s46();
virtual void s47();
    virtual bool CanReach(Obj* o, float a, float b);   // +0xc0

    uint32_t pad04[(0xc0 - 4) / 4];
    Loco_s00d6_97a0     mLoco;                                    // +0xc0
    uint32_t padc4[(0xb4c - 0xc4) / 4];
    Behav_s00d6_97a0*   mBehav;                                   // +0xb4c
    uint32_t padb50[(0xb5c - 0xb50) / 4];
    uint8_t  mFlag5c;                                  // +0xb5c
    uint8_t  padb5d[3];
    uint32_t padb60[(0xb80 - 0xb60) / 4];
    float    mTurnRate;                                // +0xb80
    uint32_t padb84[(0xc28 - 0xb84) / 4];
    char*    mNeighbors;                               // +0xc28
    uint32_t padc2c[(0xe8c - 0xc2c) / 4];
    int      mActiveTarget;                            // +0xe8c

    Obj* GetTargetObj();                               // FUN_00c0ee60
    int  GetTargetAsCreature();  // 0x00c0ee70 (SP::cSPCreatureBase::GetTargetAsCreature)
    int  GetMode();                                    // FUN_00c22dc0
    bool AnimationFinished(int id);                    // 0xc12400
    bool AnimationFinished2(int id);                   // 0xc123f0
    bool WaitForAnimEventOrEnd(int id, int* out, int a, int b, int c);  // 0x00c14ef0 (SP::cSPCreatureBase::WaitForAnimEventOrEnd)
    void FUN_00c26c80();
    bool FUN_00c26c90(int a, int b);                   // thiscall, ret 8
    int  InterruptAnimation(int id, int a, int b);  // 0x00c12310 (SP::cSPCreatureBase::InterruptAnimation)
    int  PlayAnimation(int id, int a, int b);  // 0x00c12190 (SP::cSPCreatureBase::PlayAnimation)
    bool FUN_00c0c130();
    float FUN_00c0c070();
    bool FUN_00c0d560(int tgt, float a, float b);
    void FUN_00c073a0(int a);
    void FUN_00c14750(int a);
    int  FUN_00c23750();
    int  FUN_00c22a70();
    bool FUN_00c0e0c0(int id);
    int  FUN_00c12410(uint32_t* mask, float range, int a, int b, int c, int d, int e);
    void Attack(int tgt, int a);  // 0x00c1e460 (SP::cSPCreatureBase::Attack)
    void MoveToPointAtSpeed(int a, const Vec3* p, float s0, float s1);  // 0x00c1c1d0 (SP::cSPCreatureBase::MoveToPointAtSpeed)
};
}
namespace SP {
Citizen* FUN_00d994c0(int creature);
}
namespace SP {
void*    FUN_00d998d0(IdleRes_s00d6_97a0* idle, int hash);
}
namespace SP {
bool     FUN_00da6270(cSPCreatureBase_s00d6_97a0* c, int id);
}
namespace SP {
float    FUN_004df2d0(const void* tuning);
}
namespace SP {
float    FUN_00d38a30(int which, cSPCreatureBase_s00d6_97a0* c);
}
namespace SP {
Obj*     CheckForNewTarget(cSPCreatureBase_s00d6_97a0* c, Obj* o, int hint);
}
namespace SP {
Obj*     FUN_00b3d480(int handle);
}
namespace SP {
void     FUN_00d66e10(cSPCreatureBase_s00d6_97a0* c, int slot);
}
namespace SP {
void     FindGroup(cSPCreatureBase_s00d6_97a0* c);
}
namespace SP {
void     FUN_00da8370(cSPCreatureBase_s00d6_97a0* c, int id, int handle);
}
namespace SP {
TribeStrategy* Instance();                             // cTribeModeStrategy::Instance
}
namespace SP {
bool     FUN_0064f350(int p, uint32_t hash, int z);
}
namespace SP {
Obj*     FUN_00c9cec0(int which);
}
namespace SP {
Vec3*    normalized_safe(Vec3* out, const Vec3* in);
}
namespace SP {
char     Vector3Equal(const Vec3* a, const Vec3* b);
}
namespace SP {
void     FUN_00d99e20(Vec3* pos, Vec3* res);
}
namespace SP {
bool     GetFightSlots(cSPCreatureBase_s00d6_97a0* c, int* slot, int arg);
}
namespace SP {
float    GetPropertyT_float(int props, uint32_t hash, float def);   // 0x004e1c70 SP::GetPropertyT<float>
}
namespace SP {
extern float DAT_0157206c;
}
namespace SP {
extern float DAT_01582ea8;
}
namespace SP {
extern int   DAT_01581288;
}
namespace SP {
extern char  DAT_01581254[];
}
namespace SP {
extern char  DAT_0158124c[];
}
namespace SP {
extern char  DAT_01581244[];
}
namespace SP {
extern Vec3  DAT_0169ecbc;
}
namespace SP {
static inline const float& MaxRef(const float& a, const float& b) { return (a > b) ? a : b; }
}
namespace SP {
static inline const float& MinRef(const float& a, const float& b) { return (a > b) ? b : a; }
}
// ---- items of slice s00d697a0 end

// @ 0x00d65c40
uint32_t FIGHT_Tick(int self, void* creature, int* param3)
{
  if (*(int*)(self + 0x38) != 0) {
    char done = (char)((FnIi)(*(void***)((uint8_t*)creature + 0xc0))[0x48 / 4])
                    ((uint8_t*)creature + 0xc0, *(int*)(self + 0x38));
    if (done != 0) {
      ((FnIi)(*(void***)((uint8_t*)creature + 0))[0x40 / 4])
          (creature, 0x035ee245);
      *(int*)(self + 0x38) = 0;
    }
    return 1;
  }

  if (*(int*)(self + 0x3c) == 0) {
    char can = FUN_00c0c0e0();
    if (can != 0) {
      (void)param3;
      *(int*)(self + 0x40) = 0;
    }
  } else {
    char done = (char)((FnIi)(*(void***)((uint8_t*)creature + 0xc0))[0x48 / 4])
                    ((uint8_t*)creature + 0xc0, *(int*)(self + 0x3c));
    if (done == 0)
      return 1;
    *(int*)(self + 0x3c) = 0;
  }

  if (*(int*)(self + 0x34) == 0) {
    (void)param3;
  }

  if (*(char*)(self + 0x44) != 0 && FUN_00c0c0e0() == 0 &&
      *(int*)(self + 0x18) != 0) {
    return 0;
  }
  return 0;
}

// @ 0x00d660a0
int RecordArray::FindNext(int index)
{
  uint32_t* p = mpData + index * 6;
  uint32_t value = *p;
  if ((value >> 30) & 1)
    return 0x3fffffff;

  for (;;) {
    value = p[6];
    p += 6;
    ++index;
    if ((value >> 31) == 0)
      return index;
    if ((value >> 30) & 1)
      return 0x3fffffff;
  }
}

// @ 0x00d66320
namespace SP {
SlotBody* GetFightSlotBody(uint32_t id)
{
    uint32_t count = (uint32_t)(sTribeFightSlotsPool.mpEnd - sTribeFightSlotsPool.mpData);
    id &= 0xbfffffff;
    if (id < count) {
        bool used = sTribeFightSlotsPool.mpData[id].mUsed;
        if (!used)
            return &sTribeFightSlotsPool.mpData[id].mBody;
    }
    return 0;
}
}  // namespace SP

// @ 0x00d66370
namespace SP {
bool GetFightSlots(cSPCreatureBase_s00d6_61a0* /*c*/, int* pSlot, uint32_t id)
{
    SlotBody* b = GetFightSlotBody(id);
    if ((uint32_t)*pSlot < b->mCount && (b->mBitmap & (1u << *pSlot)) != 0)
        return true;
    *pSlot = -1;
    for (uint32_t i = 0; i < b->mCount; ++i) {
        uint32_t bit = 1u << i;
        if ((b->mBitmap & bit) == 0) {
            *pSlot = i;
            b->mBitmap |= bit;
            return true;
        }
    }
    return false;
}
}  // namespace SP

// @ 0x00d66400
namespace SP {
NeighbourEntry* FindNeighbourEntry(cSPCreatureBase_s00d6_61a0* c, cSPCreatureBase_s00d6_61a0* exclude)
{
    if (!exclude)
        return 0;
    if (c->GetFightState() != 2)
        return 0;

    Loco* myLoco = &c->mLoco;
    Vec3* myPos = myLoco->GetPosition();
    float myRadius = myLoco->GetRadius();

    AbilityMask mask;
    mask.mBits[0] = 0xffffffff;
    mask.mBits[1] = 0xffffffff;
    mask.mBits[2] = 0x00ffffff;

    float dist = DistanceBetweenBodies(myPos, myRadius, exclude->mLoco.GetPosition(),
                                       exclude->mLoco.GetRadius(), true);
    if (c->CheckRange(&mask, dist, 0, 0, DAT_01582df5, 0, 0) != -1)
        return 0;

    NeighbourEntry* best = 0;
    NeighbourEntry** end = c->mNeighbourEnd;
    NeighbourIter it;
    it.mpCur = c->mNeighbourBegin;
    if (it.mpCur != end && !mask.IsValid(*it.mpCur))
        it.SkipInvalid();
    if (it.mpCur == end)
        return best;

    for (;;) {
        NeighbourEntry* e = *it.mpCur;
        cSPCreatureBase_s00d6_61a0* cand = e->mpCreature;
        if (cand && cand->GetTypeId() == 0x18eb4b7 && cand != exclude && cand->mB5E == 0
            && cand->CanBeFightTarget() && cand->GetCombatTarget() == (void*)&c->mTargetObj) {
            float d = DistanceBetweenBodies(myPos, myRadius, cand->mLoco.GetPosition(),
                                            cand->mLoco.GetRadius(), true);
            if (dist > d) {
                dist = d;
                best = e;
            }
        }
        do {
            ++it.mpCur;
            if (it.mpCur == end)
                return best;
        } while (!mask.IsValid(*it.mpCur));
    }
}
}  // namespace SP

// @ 0x00d66600
namespace SP {
cSPCreatureBase_s00d6_61a0* FindNeighbourCreature(cSPCreatureBase_s00d6_61a0* c, cSPCreatureBase_s00d6_61a0* tgt)
{
    if (!tgt)
        return 0;
    if (c->GetCombatTargetCreature() == tgt)
        return 0;
    if (c->mpBehav->m1d8 != 0x02d852e6)
        return 0;

    NeighbourEntry** end = tgt->mNeighbourEnd;
    AbilityMask mask;
    mask.mBits[0] = 0xffffffff;
    mask.mBits[1] = 0xffffffff;
    mask.mBits[2] = 0x00ffffff;
    NeighbourIter it;
    it.mpCur = tgt->mNeighbourBegin;
    if (it.mpCur == end)
        return 0;
    if (!mask.IsValid(*it.mpCur))
        it.SkipInvalid();
    if (it.mpCur == end)
        return 0;

    for (;;) {
        NeighbourEntry* e = *it.mpCur;
        if (e->mDistance > FUN_00d38a30(5, tgt))
            return 0;
        cSPCreatureBase_s00d6_61a0* cand = e->mpCreature;
        if (cand) {
            cSPCreatureBase_s00d6_61a0* o = cand->GetByTypeHash(0xd0036e08);
            if (o && o != c && cand->mB5E == 0 && tgt->IsInRange(o) && c->GetFightValue(o) > 0)
                return o;
        }
        do {
            ++it.mpCur;
            if (it.mpCur == end)
                return 0;
        } while (!mask.IsValid(*it.mpCur));
    }
}
}  // namespace SP

// @ 0x00d669c0
namespace SP {
TargetObj* CheckForNewTarget(cSPCreatureCitizen* me, cCombatant_s00d6_61a0* target, int tribe)
{
    bool fighting = (target->GetDamageState() == 2);
    bool moving = me->mLoco.IsMoving();
    if (!moving && me->GetFightState() < 2 && !fighting)
        return 0;

    Loco* myLoco = &me->mLoco;
    Loco* tgtSpatial = target->GetSpatial();
    Vec3* myPos = myLoco->GetPosition();
    float myRadius = myLoco->GetRadius();

    float maxDist = DAT_0147bc0c;
    if (!fighting) {
        float d = DistanceBetweenBodies(myPos, myRadius, tgtSpatial->GetPosition(),
                                        tgtSpatial->GetRadius(), true);
        AbilityMask mask;
        mask.mBits[0] = 0xffffffff;
        mask.mBits[1] = 0xffffffff;
        mask.mBits[2] = 0x00ffffff;
        if (me->CheckRange(&mask, d, 0, 0, DAT_01582df5, 0, 0) != -1)
            return 0;
        maxDist = d * DAT_01485544;
    }

    TargetObj* best = 0;
    int myTribe = me->GetTribe();
    PtrRange* range = myLoco->GetNeighbourRange();
    void** it = range->mpBegin;
    void** end = range->mpEnd;

    cSPCreatureBase_s00d6_61a0* animal = target->GetCreature();
    if (animal && animal->GetTypeId() != 0x18eb4b7)
        animal = 0;
    cSPCreatureBase_s00d6_61a0* citizen = target->GetCreature();
    if (citizen && citizen->GetTypeId() != 0x18eb45e)
        citizen = 0;

    if (animal) {
        for (; it != end; ++it) {
            cSPCreatureBase_s00d6_61a0* c = 0;
            if (*it)
                c = ((cSPCreatureBase_s00d6_61a0*)*it)->GetByTypeHash(0x4f176642);
            if (c) {
                if (!c->IsDead() && c->mb135 && c->mB5E == 0 && c->GetTribe() == tribe
                    && c->CanBeFightTarget()) {
                    float d = DistanceBetweenBodies(myPos, myRadius, c->mLoco.GetPosition(),
                                                    c->mLoco.GetRadius(), true);
                    if (maxDist > d) {
                        maxDist = d;
                        best = &c->mTargetObj;
                    }
                }
            }
        }
        return best;
    }

    if (citizen) {
        int wanted = citizen->mB20;
        int myId = me->GetSpatialId();
        for (; it != end; ++it) {
            void* o = 0;
            if (*it)
                o = ((cSPCreatureBase_s00d6_61a0*)*it)->GetByTypeHash(0xd0036e08);
            cSPCreatureBase_s00d6_61a0* c = FUN_00d99500(o);
            if (c && c->mB20 == wanted && c->GetSpatialId() != myId
                && c->mpBehav->m1d8 == 0x02d852e6) {
                cSPCreatureCitizen* cit = (cSPCreatureCitizen*)FUN_00ae3390(c->GetCombatTarget());
                if (cit && cit->IsTribal() && cit->GetTribe() == myTribe) {
                    float d = DistanceBetweenBodies(myPos, myRadius, c->mLoco.GetPosition(),
                                                    c->mLoco.GetRadius(), true);
                    if (maxDist > d) {
                        maxDist = d;
                        best = &c->mTargetObj;
                    }
                }
            }
        }
    }
    return best;
}
}  // namespace SP

// @ 0x00d66d60
namespace SP {
void cResizableObjectPoolT::GetObject(uint32_t id)
{
    id &= 0xbfffffff;
    cTribeFightSlots* s = mpData + id;
    s->mIndex = mLastIndex;
    s->mUsed = 1;
    mLastIndex = id;
    if (mFreeIndex == (int)id)
        mFreeIndex = NextFree((int)id);
}
}  // namespace SP

// @ 0x00d66db0
namespace SP {
void ReleaseFightSlot(uint32_t id)
{
    SlotBody* b = GetFightSlotBody(id);
    if (b) {
        if (--b->mRefCount == 0)
            sTribeFightSlotsPool.GetObject(id);
    }
}
}  // namespace SP

// @ 0x00d66e10
namespace SP {
void FUN_00d66e10(cSPCreatureBase_s00d6_61a0* c, uint32_t slot)
{
    FightGroup* g = c->mpBehav->mpGroup;
    if (g) {
        SlotBody* b = GetFightSlotBody(g->m1a4);
        if (slot < b->mCount)
            b->mBitmap &= ~(1u << slot);
        ReleaseFightSlot(g->m1a4);
    }
    c->mpBehav->SetTargetFromGroup();
}
}  // namespace SP

// @ 0x00d670e0
namespace SP {
void FightMem::Release()
{
    cSPCreatureBase_s00d6_61a0* c = mpCreature;
    FightGroup* g = c->mpBehav->mpGroup;
    if (g) {
        if (g->m1a8 && mState == 1)
            FUN_00d65500(0);
        FUN_00d66e10(c, mTarget);
        mTarget = -1;
    }
    mMaxRange = mAbilityTimer;
    mState = 0;
    mMoveTimer = 0.0f;
    mNoActivityTimer = 0.0f;
}
}  // namespace SP

// @ 0x00d67660
SlotPayload* FUN_00d67660()
{
    SlotPayload value;
    value.mNounID    = 0;
    value.mType      = 0;
    value.mToken     = 0;
    value.mTimerBits = 0;
    value.mCount     = 0;

    U32 index = gTribeFightSlotsPool.alloc(&value);
    U32 token = index | 0x40000000;
    U32 i = token & 0xbfffffff;

    SlotPayload* result;
    if (i < gTribeFightSlotsPool.count() &&
        (int)gTribeFightSlotsPool.mpBegin[i].mFlags >= 0) {
        result = &gTribeFightSlotsPool.mpBegin[i].mPayload;
    } else {
        result = 0;
    }

    result->mToken = token;
    result->mCount = 0;
    result->mNounID = 0;
    result->mType = 0x1f;
    *(float*)&result->mTimerBits = 1.0f;
    return result;
}

// @ 0x00d67700
void FindGroup(Creature* creature)
{
    void* manager = FUN_00bc9b00();
    void* objA = ((FnC0EE60*)creature)->f();

    FindKey key;
    key.mpObject = objA;
    key.mpCreature = creature;

    void* group = FUN_00bca620(manager, 0x60995fc, (void*)&FUN_00d995c0, &key);
    if (group != 0) {
        if (((FnBC9B50*)group)->f() == 0) {
            return;
        }
    }

    group = FUN_00bcb0b0(manager, 0x60995fc, 0x20, 0xce9f6639, "Fight");

    SlotPayload* slot = FUN_00d67660();
    ((FightGroup_s00d6_7140*)group)->mSlot1A4 = slot->mToken;
    ((FightGroup_s00d6_7140*)group)->mByte1A8 = 0;

    void* objB = ((VT*)objA)->q02();
    U32* vec = (U32*)((VT*)objB)->q11();
    ((FightGroup_s00d6_7140*)group)->mVec1AC[0] = vec[0];
    ((FightGroup_s00d6_7140*)group)->mVec1AC[1] = vec[1];
    ((FightGroup_s00d6_7140*)group)->mVec1AC[2] = vec[2];

    float f = creature->mSubSys.q29();
    void* r = ((VT*)objA)->q02();
    FUN_00d66250(slot, r, f);

    ((FnBCB480*)creature->mpB4C)->f(group, creature, 0, 0);
}

// @ 0x00d678d0
int FUN_00d678d0(FightAction* self, U8 param)
{
    Creature* creature = (Creature*)self->mpCreature;
    ((FnD670E0*)self)->f();
    FindGroup(creature);

    FightGroup_s00d6_7140* group = creature->mpB4C->mpGroup;
    if (group == 0) {
        return 0;
    }

    U32 v = self->mField2C;
    if (v < group->mField10 && group->mByte1A8 != 0) {
        SlotPayload* sp = FUN_00d66320(group->mSlot1A4);
        param = (U8)(param | (sp->mNounID < (1u << ((v - 1) & 0x1f))));
    }

    if (group->mField10 > v && param == 0) {
        return 0;
    }

    {
        Creature* target = (Creature*)((FnGetTarget*)creature)->f();

        self->mF10 = self->mF14;
        self->mField18 = 1;
        self->mF04 = 0.0f;
        self->mF08 = 0.0f;
        self->mF0C = 0.0f;

        U8 ch = 0;
        if (target != 0 && ((target->mFlagsB58 >> 9) & 1) != 0) {
            ch = 1;
        }
        group->mByte1A8 = ch;

        if (self->mpField48 != 0 &&
            group->mField10 <= ((FieldHolder*)self->mpField48)->mField3F8) {
            self->mByte4E = 1;
        }

        if (ch != 0) {
            U32 local[3];
            local[0] = 0;
            local[1] = 0;
            local[2] = 1;
            void* strat = SP_cCreatureModeStrategy_Instance(0xd3353637, local);
            ((FnD39360*)strat)->f();
        }
    }
    return 1;
}

// @ 0x00d679e0
char FIGHT_Activate(Creature* c, int a2, int a3, int a4, U32 bits, FightAction* fa, void* arg7)
{
    (void)a2; (void)a3; (void)a4;

    if (fa != 0) {
        ((FnD66E70*)fa)->f(c);
    }
    if ((bits & 0x20) != 0) {
        fa->mByte4F = 1;
    }

    void* combatant = 0;
    void* foundCreature = 0;
    int   haveFound = 0;

    if (((c->mFlagsB58 >> 8) & 1) != 0) {
        void* played = ((FnSpotPlay*)&c->mpB4C->mStimuli)->f(0x10, 0);
        if (played != 0) {
            if (FUN_00b5b800() != 0x1654c10) {
                void* animal = SP_GetAnimalFromStimulus(played);
                if (animal != 0 && ((Creature*)animal)->mFlagB5E == 0) {
                    combatant = (void*)&((Creature*)animal)->mCombatant;
                    foundCreature = animal;
                    haveFound = 1;
                }
            } else {
                void* y = FUN_00d99a10(played);
                if (y != 0 && FUN_008e7f80(y) != 2) {
                    combatant = y;
                    foundCreature = SP_GetCreatureFromStimulus(y);
                    haveFound = 1;
                }
            }
        }
    }

    if (haveFound) {
        if (foundCreature != 0 && FUN_00d99470(foundCreature) == 0) {
            return 0;
        }
    } else {
        void* esi = 0;
        if (arg7 != 0) {
            void* q = ((Arg7Object*)arg7)->mpField08;
            combatant = ((Arg7Object*)arg7)->mpField04;
            if (q != 0) {
                esi = ((VT*)q)->q03(0x1186577);
            }
        } else {
            combatant = 0;
        }

        void* old = fa->mpField20;
        if (esi != old) {
            if (esi != 0) {
                ((VT*)esi)->q47();
            }
            fa->mpField20 = esi;
            if (old != 0) {
                ((VT*)old)->q48();
            }
        }

        if (combatant == 0) {
            return 0;
        }
        {
            void* x = ((VT*)combatant)->q23(0xce9f6639);
            if (x != 0 && FUN_00d99470(x) == 0) {
                return 0;
            }
        }
    }

    c->q33(combatant, 1, 0);

    if (((bits >> 2) & 1) != 0 && ((bits >> 4) & 1) == 0) {
        ((FnInterrupt*)c)->f(0x2481df9, -1, 0);

        U32 local[3];
        local[0] = 0;
        local[1] = 0;
        local[2] = 0;
        ((FnB41A40*)local)->f(c->mField1124, fa);

        void** p = (void**)local[0];
        void** e = (void**)local[1];
        for (;;) {
            if (p == e) {
                break;
            }
            void* entry = *p;
            void* obj = ((EntryWithPtr*)entry)->mpField08;
            if (obj != 0 && ((VT*)obj)->q08() == (void*)0x18eb45e) {
                void* sp1 = SP_GetSpeciesProfile(obj);
                void* sp2 = SP_GetSpeciesProfile(c);
                if (sp1 == sp2) {
                    void* r = ((VT*)combatant)->q03(0);
                    B4CObj* stim = ((HasB4C*)obj)->mpB4C;
                    ((FnBC97F0*)&stim->mStimuli)->f(0x800000, 0, 10.0f, r);
                }
            }
            for (;;) {
                p++;
                if (p == e) {
                    goto loop_done;
                }
                if (((FnIsValid*)(local + 2))->f(*p)) {
                    break;
                }
            }
        }
    loop_done: ;
    } else {
        if (!c->mSubSys.q62()) {
            ((FnInterrupt*)c)->f(0x39e477b, -1, 0);
        } else {
            ((FnC14750*)c)->f(0);
        }
    }

    U8 flag = 0;
    if (c->mpB4C->mField1D8 != 0x2d852e6) {
        void* played = ((FnPlay2*)&c->mpB4C->mStimuli)->f(0x400, 0);
        if (played != 0) {
            if (!((FnC0C0E0*)c)->f()) {
                fa->mField38 = (U32)((FnInterrupt*)c)->f(0x35ee23c, -1, 0);
            }
            flag = 1;
        }
    }

    fa->mF58 = 0.0f;

    U8 arg = (flag != 0 || ((c->mFlagsB58 >> 8) & 1) != 0) ? 1 : 0;
    FUN_00d678d0(fa, arg);

    fa->mByte44 = 1;
    c->mSubSys.q59();
    c->mFlagsB58 |= 0x2000;
    ((FnC19940*)c)->f(0);

    if (combatant != 0) {
        void* x = ((VT*)combatant)->q23(0x4f176642);
        if (x != 0 && ((FnC232B0*)x)->f()) {
            void* r = ((VT*)c)->q03(0xee3f516e);
            B4CObj* stim = ((HasB4C*)x)->mpB4C;
            ((FnBC97F0*)&stim->mStimuli)->f(0, 0x80, 10.0f, r);
        }
    }
    return 1;
}

// @ 0x00d67d30
namespace SP {
bool FIGHT_Tick(cSPCreatureBase_s00d6_7d30* self, int, int, uint32_t flags, uint32_t flags2, FightMem_s00d6_7d30* mem, int, float dt)
{
    TargetObj_s00d6_7d30* target = self->GetTargetObj();
    cSPCreatureBase_s00d6_7d30* targetCreature = FUN_00d99470_s00d6_7d30(self->GetTargetAsCreature());
    int targetCitizen = FUN_00d99500(targetCreature);

    Spatial* targetOwner = 0;
    float dist = 0.0f;
    if (target) {
        targetOwner = target->GetOwner();
        if (targetOwner)
            dist = FUN_00d99ac0(self ? &self->mLoco : 0, targetOwner, 1);
    }

    int* attackAnim = &mem->mAttackAnim;
    float* pDist = &mem->mDistance;
    *pDist = dist;
    if ((*attackAnim == 0 || self->AnimationFinished(*attackAnim))
        && FUN_00d659e0(mem, self, flags2, target, targetCreature))
        return false;

    if (IsCreatureGame()) {
        if (*pDist > FUN_00f264b0(self)) {
            mem->mFrustrationTimer = dt + mem->mFrustrationTimer;
            if (mem->mFrustrationTimer > 5.0f && mem->mFrustrationAnim == 0)
                mem->mFrustrationAnim = self->InterruptAnimation(0x3238f953, -1, 0);
        } else {
            mem->mFrustrationTimer = 0.0f;
        }

        if (target)
            mem->mFirstHitAnim = targetCitizen ? DAT_01582ee8 : 0x20;

        if (mem->mbAttackOnSight) {
            self->mbFlagB5C = 1;
            self->SetTarget(target, 1, 0);
            bool targetValid = FUN_00d998f0(target) != 0;
            int prevIdx = -1;
            float maxR = 0.0f, minR = 0.0f;
            int idx = FUN_00d66710(mem, self, target, &prevIdx, &maxR, &minR);
            if (targetValid && maxR >= *pDist && *pDist >= minR) {
                Loco_s00d6_7d30* loco = &self->mLoco;
                const Vec3* myPos = loco->GetPosition();
                const Vec3* tgtPos = targetOwner->GetPosition();
                Vec3 toTarget = normalized_safe(*tgtPos - *myPos);
                Vec3 facingBuf;
                const Vec3* facing = loco->GetFacing(&facingBuf);
                if (Dot(*facing, toTarget) > 0.85f && idx != -1)
                    self->Attack(idx, attackAnim);
                return true;
            }
            void* newTarget;
            if (!self->FUN_00c04750()->mUseOtherTargeting) {
                newTarget = SimSingleton::Get()->FindTarget(self->mTargetable, 0.0f, 0.0f);
            } else {
                TargetQuery* q = self->mTargetSrc.FUN_00c7d930();
                newTarget = q ? q->Get(DAT_013f94d4) : 0;
            }
            self->SetTarget(newTarget, 1, 0);
            return true;
        }
    }

    FightGroup_s00d6_7d30* group = self->mpBehav->mpGroup;
    mem->mEvalTimer = mem->mEvalTimer - dt;
    mem->mMoveTimer = mem->mMoveTimer - dt;
    mem->mNoActivityTimer = mem->mNoActivityTimer - dt;

    if (self->FUN_00c0c0e0() && mem->m3c == 0 && self->mTimer.GetElapsedTime() < 3000)
        mem->m40 = mem->m40 + dt;

    {
        int at = self->mActiveTarget;
        Ability* ab;
        if (at == -1 || (ab = self->GetAbility(at)) == 0 || !(ab->mF4 > 0.0f) || ab->mF8 == -1)
            self->mbFlagB5C = 1;
    }

    if (FUN_00d65c40(mem, self, target))
        return true;

    uint32_t mustSee = flags & 8;
    if (!mustSee && targetCreature && targetCreature->GetTypeId() == kTypeCreatureAnimal) {
        const Vec3* tp = targetCreature->mLoco.GetPosition();
        const Vec3* mp = self->mLoco.GetPosition();
        if (DistSq(*mp, *tp) < 400.0f)
            targetCreature->mpBehav->mStim.SetStimulus(0, 0x100, 30.0f, self);
    }

    if (mem->mEvalTimer < 0.0f) {
        mem->mEvalTimer = FUN_00d65530(1.0f, self->FUN_00c0c0e0());
        void* newTarget = 0;
        if (!IsCreatureGame()) {
            cSPCreatureBase_s00d6_7d30* found;
            if (targetCitizen) {
                if (flags2 & 4)
                    found = FUN_00d66600(self, targetCitizen);
                else {
                    if (self->mLoco.IsMoving() || (flags & 0x1000) || !mustSee)
                        goto noRetarget;
                    found = FUN_00d655d0(self, targetCitizen, mem->m50, mem->m54);
                }
            } else {
                found = FUN_00d66400(self, FUN_00ac80d0(targetCreature, kTypeCreatureAnimal), mem->m50, mem->m54);
            }
            if (!found)
                goto noRetarget;
            newTarget = found->mTargetable;
        } else {
            if (((self->mStateFlags >> 9) & 1) || ((self->mStateFlags >> 8) & 1) || !(self->mFlags330 & 0x21))
                goto noRetarget;
            int h = target->GetHandle()->m24;
            self->mSeenHandles.insert(h);
            if (self->FUN_00c04750()->mUseOtherTargeting)
                newTarget = FUN_00ae6740(self->mTargetSrc.FUN_00c7d930());
            else
                newTarget = SimSingleton::Get()->FindTarget(self->mTargetable, 0.0f, 0.0f);
            if (!newTarget || newTarget == target)
                goto noRetarget;
        }
        if (newTarget) {
            self->SetTarget(newTarget, 1, 0);
            mem->FUN_00d678d0(false);
            return true;
        }
    }
noRetarget:

    if (group) {
        IdleRes* idle = self->mpBehav->mStim.PlayIdleAnimation(0x400, 0);
        if (idle) {
            TargetObj_s00d6_7d30* o = (TargetObj_s00d6_7d30*)FUN_00d998f0(FUN_00d99a10(idle));
            if (o && o == group->mMembers[group->mLeaderIdx].mpCreature->GetTargetObj())
                group->mLeaderPos = *o->GetOwner()->GetPosition();
        }
    }

    switch (mem->mState) {
    case 0: {
        if (mem->mMoveTimer < 0.0f) {
            bool targeted = false;
            IdleRes* idle = self->mpBehav->mStim.PlayIdleAnimation(0x400, 0);
            if (idle) {
                int o = FUN_00d998f0(FUN_00d99a10(idle));
                if (o) {
                    self->SetTarget((void*)o, 0, 0);
                    targeted = true;
                }
            }
            if (!mem->FUN_00d678d0(targeted))
                mem->mMoveTimer = FUN_00d65530(1.0f, self->FUN_00c0c0e0());
        }
        return true;
    }
    case 1:
        break;
    default:
        return true;
    }

    // state 1: engaged
    if (!group || group->FUN_00a75010())
        return false;

    bool specialTarget = false;
    if (!targetCreature && targetOwner) {
        void* h = target->GetHandle();
        if (h) {
            if (FUN_00ac80d0(h, kTypeA))
                specialTarget = true;
            else {
                CastObj* c = (CastObj*)FUN_00ac80d0(h, kTypeB);
                if (c) {
                    if (c->mb1c == 2)
                        specialTarget = true;
                    else if (c->mb1c == 1)
                        specialTarget = true;
                }
            }
        }
    }

    int prevIdx = -1;
    float maxR = 0.0f, minR = 0.0f;
    int idx = FUN_00d66710(mem, self, target, &prevIdx, &maxR, &minR);

    if (IsCreatureGame()) {
        if (mem->mAbilityIdx != idx) {
            mem->mAbilityIdx = idx;
            mem->mAbilityTimer = 0.0f;
            Ability* ab = self->GetAbility(idx);
            if (ab)
                mem->mAbilityTimer = (1.0f - self->mpAttacks[idx].mReadiness) * ab->mCooldown + 5.0f;
        }
        if (mem->mAbilityIdx != -1) {
            mem->mAbilityTimer = mem->mAbilityTimer - dt;
            if (mem->mAbilityTimer < 0.0f) {
                mem->mAbilityIdx = -1;
                mem->mAbilityTimer = 0.0f;
                mem->mCooldowns[idx] = 30.0f;
            }
        }
        for (CooldownIter it = mem->mCooldowns.begin(); it != mem->mCooldowns.end(); ) {
            it.mpNode->second = it.mpNode->second - dt;
            if (0.0f < it.mpNode->second)
                ++it;
            else
                it = mem->mCooldowns.erase(it);
        }
    }

    Spatial* owner = targetOwner;
    Vec3 targetPos = PlanetModel()->ProjectToSurface(owner->GetPosition());
    Loco_s00d6_7d30* loco = &self->mLoco;
    float radii = owner->GetRadius();
    radii = loco->GetRadius() + radii;

    if (self->mActiveTarget != -1) {
        // an ability is being used: stay in its range
        if (loco->GetState()->mHasPath != 0)
            return true;
        Ability* ab = self->GetAbility(self->mActiveTarget);
        float scale = FUN_00d38a30(0, self);
        bool b = (self->mStateFlags >> 9) & 1;
        float bound = ab->GetBound(b) * scale;
        if (IsCreatureGame() && bound > *pDist) {
            // too close: back off to the edge of the range
            Vec3 away = Vector3_Normalize(*loco->GetPosition() - targetPos);
            float over = bound - *pDist;
            Vec3 off = { over * away.x, away.y * over, away.z * over };
            Vec3 dest = *loco->GetPosition() + off;
            self->MoveToPointAndFacingAtSpeed(2, dest, normalized_safe(targetPos - *loco->GetPosition()), 1.0f, 2.0f);
            return true;
        }
        float ownerR = owner->GetRadius();
        float myR = loco->GetRadius();
        float sumR = myR + ownerR;
        float speed = (ab ? ab->mRange * scale : 0.0f) + sumR;
        float speedMax = speed + myR;
        Vec3 goal = FUN_00d65580(self, targetPos);
        float dsq = DistSq(goal, targetPos);
        if (dsq > 1.5258789e-05f) {
            float d = sqrtf(dsq);
            speed = speed + d;
            speedMax = d + speedMax;
        }
        self->MoveToPointAndFacingAtSpeed(2, goal, normalized_safe(targetPos - *loco->GetPosition()), speed, speedMax);
        cLocomotiveObject_s00d6_7d30* ol = FUN_00b33e40(owner);
        if (!ol)
            return true;
        if (Length(ol->GetVelocity()) > 0.01f)
            loco->GetState()->mMoveFlags |= 1;
        return true;
    }

    bool mutualTarget;
    if (targetCreature && targetCreature->GetTargetCreature() == self && targetCreature->mActiveTarget != -1)
        mutualTarget = true;
    else
        mutualTarget = false;

    bool engaged = self->mActiveTarget != -1;
    if (!engaged && targetCreature && targetCreature->mLoco.IsMoving()) {
        for (uint32_t i = 0; i < group->mCount; ++i) {
            GroupMember& m = group->mMembers[i];
            if (m.mActive && m.mpCreature && m.mpCreature->mActiveTarget != -1) {
                engaged = true;
                break;
            }
        }
    }
    if (mutualTarget || engaged)
        mem->m10 = mem->m14;

    bool canAct;
    if (self->FUN_00c04590()->mpLeader == self
        && self->FUN_00c04590()->HasMembers()
        && !self->mpBehav->mStim.PlayIdleAnimation(0x400, 0))
        canAct = false;
    else
        canAct = true;

    if (mem->mMoveTimer < 0.0f && !mutualTarget && !engaged && idx != -1
        && self->mpAttacks[idx].mReadiness >= 1.0f && canAct) {
        // ready to attack
        bool slotted = GetFightSlots(self, mem, group->m1a4);
        if (FUN_00d65fe0(mem, self, target, minR, maxR))
            return false;
        bool targetValid = FUN_00d998f0(target) != 0;
        Vec3 toTarget = normalized_safe(targetPos - *loco->GetPosition());
        Vec3 up = normalized_safe(*loco->GetPosition());
        float d = up.x * toTarget.x + toTarget.y * up.y + toTarget.z * up.z;
        Vec3 flat = { toTarget.x - d * up.x, toTarget.y - d * up.y, toTarget.z - d * up.z };
        if (flat != kZeroVec)
            toTarget = normalized_safe(flat);

        Vec3 facingBuf;
        if (targetValid && maxR >= *pDist && *pDist >= minR
            && Dot(*loco->GetFacing(&facingBuf), toTarget) > 0.85f) {
            if (IsCreatureGame()) {
                mem->mAbilityIdx = -1;
                mem->mAbilityTimer = 0.0f;
            }
            self->Attack(idx, attackAnim);
            mem->m4e = false;
            mem->m44 = false;
            if (idx == prevIdx)
                mem->mStandardAttackCounter = 0;
            else
                ++mem->mStandardAttackCounter;
            mem->m10 = mem->m14;
            bool b = self->FUN_00c0c0e0();
            mem->mMoveTimer = FUN_00d65530(self->GetAbility(idx)->mA0, b);
            mem->mNoActivityTimer = 0.0f;
            return true;
        }

        float scale = FUN_00d38a30(0, self);
        Ability* ab = self->GetAbility(idx);
        float maxRange = (ab->mF4 + ab->mRange) * scale;
        bool b = (self->mStateFlags >> 9) & 1;
        float bound = ab->GetBound(b) * scale;
        bool moved;
        if (IsCreatureGame() && bound > *pDist) {
            // too close: back off to a quarter of the way into the range
            Vec3 away = Vector3_Normalize(*loco->GetPosition() - targetPos);
            float over = ((maxRange - bound) * 0.25f + bound) - *pDist;
            Vec3 off = { over * away.x, over * away.y, over * away.z };
            Vec3 dest = *loco->GetPosition() + off;
            self->MoveToPointAndFacingAtSpeed(2, dest, normalized_safe(targetPos - *loco->GetPosition()), 1.0f, 2.0f);
            moved = loco->SlotF8();
        } else {
            float jumpChance = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0x4f7cf2c, 0.25f);
            if (!self->FUN_00c0c0e0() && self->mpTuning->m58c > 1.5258789e-05f
                && (((self->mStateFlags >> 8) & 1) || self->FUN_00c0b780())
                && jumpChance > sMathRandom.RandomDoubleUniform()
                && targetCreature && self->CanReach(targetCreature, mem->m54, 0.0f)) {
                Loco_s00d6_7d30* tl = &targetCreature->mLoco;
                self->TryJumpToTarget(0, targetPos, ((cLocomotiveObject_s00d6_7d30*)tl)->GetVelocity(), tl->GetRadius(), 0);
                return true;
            }

            float approach = maxRange;
            if (self->GetAbility(idx)->m7c == 1)
                approach = Min(approach, Max(*pDist, minR));
            approach = approach + radii;
            float approachMax = loco->GetRadius() + approach;

            LocoState* st = loco->GetState();
            bool needMove = true;
            if (st->mHasPath != 0 && !(*pDist < 40.0f)) {
                const Vec3* g = loco->GetState()->GetGoal();
                float gd = DistSq(*g, targetPos);
                float r = owner->Slot70();
                if (!(gd > owner->Slot70() * r))
                    needMove = false;
            }
            if (needMove) {
                if (slotted) {
                    self->MoveToPointAtSpeed(2, targetPos, approach, approachMax);
                    loco->GetState()->mMoveFlags |= 4;
                } else {
                    Vec3 goal = FUN_00d65580(self, targetPos);
                    float dsq = DistSq(targetPos, goal);
                    if (dsq > 1.5258789e-05f) {
                        float d2 = sqrtf(dsq);
                        approach = approach + d2;
                        approachMax = d2 + approachMax;
                    }
                    self->MoveToPointAndFacingAtSpeed(2, goal, normalized_safe(goal - *loco->GetPosition()), approach, approachMax);
                }
            }
            cLocomotiveObject_s00d6_7d30* tl = FUN_00bfc6c0(self->GetTargetObj());
            if (tl && Length(tl->GetVelocity()) > 0.01f)
                loco->GetState()->mMoveFlags |= 1;
            moved = loco->SlotF8();
        }
        if (!moved)
            self->FUN_00c14750(0);
        return true;
    }

    // not ready to attack: circle / approach
    bool slotted = GetFightSlots(self, mem, group->m1a4);
    float closeDist = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0x8b034ce0, 1.0f);
    if (!specialTarget
        && !(targetCreature && targetCreature->GetTargetCreature() == self)
        && (mem->mNoActivityTimer < 0.0f || *pDist > closeDist)) {
        float extra = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0xf290181f, 1.0f);
        float timerBase = GetPropertyT_float(g_CreatureModeStrategy->mpProps, 0x2140064f, 1.0f);
        float keep = extra + radii + minR;
        mem->mNoActivityTimer = FUN_00d65530(timerBase, self->FUN_00c0c0e0());
        if (slotted) {
            self->MoveToPointAtSpeed(2, targetPos, keep, keep + 0.2f);
            loco->GetState()->mMoveFlags |= 4;
        } else {
            Vec3 dir = normalized_safe(targetPos - *loco->GetPosition());
            Vec3 off = -dir * keep;
            const Vec3* op = owner->GetPosition();
            Vec3 dest = { off.x + op->x, op->y + off.y, op->z + off.z };
            dest = FUN_00d65580(self, dest);
            self->MoveToPointAtSpeed(2, dest, loco->GetRadius() * 0.5f, loco->GetRadius());
        }
        if (!loco->SlotF8())
            self->FUN_00c14750(0);
    }
    if (!self->AnimationFinished2(0))
        return true;
    int anim = 0x26ede51;
    if (!loco->IsNearGoal())
        anim = 0x39e477b;
    if (self->FUN_00c0e0c0(anim))
        return true;
    self->PlayAnimation(anim, 1, -1);
    return true;
}
}  // namespace SP

// @ 0x00d697a0
namespace SP {
bool TRIBE_FIGHT_Tick(cSPCreatureBase_s00d6_97a0* self, int, int, int, int, FightState* st, int, float dt)
{
    Obj* targetObj = self->GetTargetObj();
    int mode = self->GetMode();

    if (!targetObj) {
        if (st->mNoRetarget) return false;
        return FUN_00da6270(self, st->mId);
    }

    Obj* myObj = targetObj->GetOwner();
    int tgtCreature = self->GetTargetAsCreature();
    Citizen* citizen = FUN_00d994c0(tgtCreature);
    BehStim_s00d6_97a0* stim = (BehStim_s00d6_97a0*)((char*)self->mBehav + 8);
    IdleRes_s00d6_97a0* idle = stim->PlayIdleAnimation(0, 0x400000);

    bool checkCitizen = true;
    if (idle != 0 && citizen) {
        void* r = FUN_00d998d0(idle, 0x4f396a66);
        if (r && (int)r == citizen->GetTribe()) {
            ((BehStim_s00d6_97a0*)((char*)self->mBehav + 8))->ClearAll(0, 0x400000);
            return FUN_00da6270(self, st->mId);
        }
    } else if (idle != 0) {
        checkCitizen = false;
    }
    if (checkCitizen && citizen && citizen->mSub->FUN_00bca0c0(0, 2, 0, 0) != -1)
        return false;

    if (st->mAnim) {
        if (!self->AnimationFinished(st->mAnim)) return true;
        if (st->mNoRetarget) return false;
        return FUN_00da6270(self, st->mId);
    }

    if (!self->FUN_00c26c90(0x6000e, 1)) return true;

    if (st->mEventAnim) {
        int tmp = 0;
        if (!self->WaitForAnimEventOrEnd(0x7d7502fc, &tmp, -1, 0, 1)) return true;
        self->FUN_00c26c80();
        st->mEventAnim = 0;
    }

    st->mTimer0 = st->mTimer0 - dt;
    st->mTimer1 = st->mTimer1 - dt;
    st->mTimer2 = st->mTimer2 - dt;
    st->mAttackTimer = st->mAttackTimer - dt;

    if (!self->mLoco.IsMovingFast() && st->mAttackTimer < 0.0f) {
        st->mAnim = self->InterruptAnimation(0x5b93649, -1, 0);
        ((BehStim_s00d6_97a0*)((char*)self->mBehav + 8))->ClearAll(0x400, 0);
        return true;
    }

    if (!st->mB24) {
        st->mB24 = (FUN_00d998f0(targetObj) == 0);
        if (st->mB24) {
            st->mTimer0 = FUN_004df2d0(DAT_01581254) + 2.0f;
            st->mTimer2 = 0.0f;
        }
    }

    {
        Obj* ao;
        if (self->mActiveTarget == -1
            || !(ao = self->GetObjectById(self->mActiveTarget))
            || !ao->FUN_00c0b000())
            self->mFlag5c = 1;
    }

    if (!self->FUN_00c0c130())
        self->mTurnRate = self->FUN_00c0c070() * DAT_01582ea8;

    Vec3* pos  = self->mLoco.GetPosition();
    Vec3* tpos = myObj->GetPosition();
    float objRadius = myObj->GetRadius();
    float sum = self->mLoco.GetRadius() + objRadius;
    float dx = tpos->x - pos->x;
    float dy = tpos->y - pos->y;
    float dz = tpos->z - pos->z;
    float dist = (float)(sqrt((double)(dz * dz + dy * dy + dx * dx)) - sum);
    if (!(dist >= 0.0f)) dist = 0.0f;

    float scale1 = FUN_00d38a30(1, self);
    float scale2 = FUN_00d38a30(2, self);

    bool inRange;
    if (!st->mB24 && !self->mLoco.IsMovingFast()
        && (tgtCreature == 0
            || (!self->FUN_00c0d560(tgtCreature, scale1, dist)
                && !self->CanReach((Obj*)tgtCreature, scale2, dist))))
        inRange = false;
    else
        inRange = true;

    st->mRef.Assign(FUN_00d998f0(st->mRef.mp));

    if (st->mRef.mp == 0) {
        if (mode == 9) return FUN_00da6270(self, st->mId);
        if (self->mActiveTarget == -1 && (st->mTimer2 <= 0.0f || !inRange)) {
            st->mTimer2 = FUN_004df2d0(DAT_01581254) + 1.0f;
            if (!st->mNoRetarget) {
                Obj* newT = CheckForNewTarget(self, targetObj, st->mHintArg);
                if (newT) {
                    if (self->mLoco.IsMovingFast()) {
                        FUN_00b3d480(targetObj->GetHandle())->FUN_00aca360();
                        FUN_00b3d480(newT->GetHandle())->FUN_00acd2d0();
                    }
                    self->SetTarget(newT, 1, 1);
                    st->mB24 = false;
                    st->mTimer0 = 0.0f;
                    st->mTimer1 = 0.0f;
                    FUN_00d66e10(self, st->mSlot);
                    FindGroup(self);
                    FUN_00da8370(self, st->mId, newT->GetHandle());
                }
            }
        }
    }

    if (st->mB24) {
        if (0.0f <= st->mTimer0) return true;
        return FUN_00da6270(self, st->mId);
    }

    if (self->mLoco.IsMovingFast()) {
        if (self->FUN_00c23750()) {
            Vec3 p = *self->mLoco.GetPosition();
            if (st->mStratHandle == 0) {
                st->mStratHandle = Instance()->mMgr->FUN_00bc2240(0xad1a17d, p);
            } else {
                Instance()->mMgr->FUN_00bc23d0(st->mStratHandle, p);
            }
        } else if (st->mStratHandle) {
            Instance()->mMgr->FUN_00bc2180(st->mStratHandle);
            st->mStratHandle = 0;
        }
    }

    Big* big = self->mBehav->mBig;
    big->FUN_00bc9b10();

    if ((uint64_t)self->mBehav->mFlags & 0x10000000ULL) {
        IdleRes_s00d6_97a0* res = ((BehStim_s00d6_97a0*)((char*)self->mBehav + 8))->PlayIdleAnimation(0x10000000, 0);
        int id = res->mId;
        Obj* o = self->GetObjectById(id);
        if (o && o->m0c == 1
            && *(float*)(self->mNeighbors + id * 16 + 4) >= 1.0f) {
            st->mTarget = id;
            st->mTimer0 = -1.0f;
            st->mTimer1 = -1.0f;
            self->FUN_00c073a0(-1);
            self->FUN_00c14750(0);
        }
        ((BehStim_s00d6_97a0*)((char*)self->mBehav + 8))->ClearAll(0x10000000, 0);
    }

    Loco_s00d6_97a0* loco = &self->mLoco;

    if (self->mActiveTarget != -1) {
        Obj* o = self->GetObjectById(self->mActiveTarget);
        if (loco->GetState()->mHasPath == 0 && o && !o->FUN_00c0b000()) {
            float scale0 = FUN_00d38a30(0, self);
            float a = (o->mF4 + o->mA8) * scale0;
            float b = o->GetBound(0);
            float total = MaxRef(a, b) + sum;
            float speed = total * 0.98f;
            if (speed < dist) {
                Vec3* p = myObj->GetPosition();
                self->MoveToPointAtSpeed(2, p, speed, total);
                loco->GetState()->mMoveFlags |= 3;
            }
        }
        goto done;
    }

    if (mode == 3 && self->FUN_00c22a70() != 3 && self->AnimationFinished2(0x2c39370)) {
        st->mEventAnim = self->InterruptAnimation(0x56d43de, -1, 0);
        return true;
    }
    if (st->mB25 == 1 && !self->FUN_00c0e0c0(0x67378dd))
        self->PlayAnimation(0x67378dd, 1, -1);

    {
        uint32_t mask[3];
        mask[0] = 0; mask[1] = 0; mask[2] = 0;
        uint32_t i = 0;
        do {
            mask[i] = ~mask[i];
            i = i + 1;
        } while (i < 3);
        mask[2] &= 0xffffff;
        int tid = st->mTarget;
        if (((1 << (mode & 31)) & 0xa0e) != 0) {
            mask[0] &= 0xbfffffff;
            mask[1] &= 0xfffffffd;
        }
        if (tid == -1) {
            bool found = false;
            if (mode == 3) {
                uint32_t m2[3];
                m2[0] = 0; m2[1] = 0x800; m2[2] = 0;
                tid = self->FUN_00c12410(m2, dist, 1, 0, 0, 1, 0);
                Obj* o = self->GetObjectById(tid);
                if (o && ((o->mF4 + o->mA8) - sum) * 0.25f < dist && tid != -1)
                    found = true;
            }
            if (!found) {
                tid = self->FUN_00c12410(mask, dist, 0, 0, 0, 0, 0);
                if (tid == -1)
                    tid = self->FUN_00c12410(mask, dist, 1, 0, 0, 1, 0);
            }
        }

        Obj* tobj = 0;
        float scaleA = FUN_00d38a30(0, self);
        float rngInner = 0.0f;
        float approach = 0.0f;
        float rngOuter = 0.0f;
        bool canMelee = true;
        if (tid != -1) {
            tobj = self->GetObjectById(tid);
            rngOuter = (tobj->mF4 + tobj->mA8) * scaleA;
            rngInner = tobj->GetBound(0);
            rngOuter = MaxRef(rngOuter, rngInner);
            float x3 = rngOuter * 0.98f + sum;
            float y = (dist + rngInner) + sum;
            approach = MinRef(x3, y);
            canMelee = FUN_0064f350(tobj->m130, 0xffa5839d, 0);
        }
        if (mode == 3) {
            Obj* t = *(Obj**)((char*)FUN_00c9cec0(3) + 0x24);
            float A = (t->mF4 + t->mA8) * scaleA;
            rngInner = t->GetBound(0);
            approach = A * 0.98f + sum;
            rngOuter = A;
            canMelee = false;
        }

        if (0.0f <= st->mTimer0 || tid == -1
            || *(float*)(self->mNeighbors + tid * 16 + 4) < 1.0f) {
            // not ready to attack: keep positioning
            if (st->mTimer1 < 0.0f) {
                st->mTimer1 = FUN_004df2d0(DAT_0158124c);
                if (mode == 3) {
                    self->MoveToPointAtSpeed(2, tpos, approach, rngOuter);
                    loco->GetState()->mMoveFlags |= 1;
                } else if (!GetFightSlots(self, &st->mSlot, big->m1a4)) {
                    float prop = GetPropertyT_float(DAT_01581288, 0x5753ef17, 5.0f);
                    if (dist <= prop) {
                        loco->GetState()->mMoveFlags |= 1;
                    } else {
                        self->MoveToPointAtSpeed(2, tpos, prop + sum, prop + sum);
                        loco->GetState()->mMoveFlags |= 1;
                    }
                } else if (1.5258789e-05f < dist) {
                    self->MoveToPointAtSpeed(2, tpos, approach, approach + 0.2f);
                    loco->GetState()->mMoveFlags |= 4;
                    loco->GetState()->mMoveFlags |= 1;
                } else {
                    float x = rngOuter * 0.98f + sum;
                    Vec3 d;
                    d.x = pos->x - tpos->x;
                    d.y = pos->y - tpos->y;
                    d.z = pos->z - tpos->z;
                    Vec3 tmp;
                    Vec3* n = normalized_safe(&tmp, &d);
                    Vec3 res;
                    res.x = tpos->x + x * n->x;
                    res.y = tpos->y + n->y * x;
                    res.z = tpos->z + n->z * x;
                    FUN_00d99e20(pos, &res);
                    self->MoveToPointAtSpeed(2, &res, 0.2f, dt);
                    loco->GetState()->mMoveFlags |= 1;
                }
            }
            goto done;
        }

        // ready: aim and attack
        Vec3 d;
        d.x = tpos->x - pos->x;
        d.y = tpos->y - pos->y;
        d.z = tpos->z - pos->z;
        Vec3 u;
        normalized_safe(&u, &d);
        Vec3 p;
        normalized_safe(&p, pos);
        float dot = (p.x * u.x + u.y * p.y) + u.z * p.z;
        Vec3 w;
        w.x = u.x - p.x * dot;
        w.y = u.y - dot * p.y;
        w.z = u.z - dot * p.z;
        if (Vector3Equal(&w, &DAT_0169ecbc)) {
            w = u;
        } else {
            Vec3 t2;
            Vec3* nn = normalized_safe(&t2, &w);
            w = *nn;
        }
        Vec3 facingTmp;
        Vec3* facing = loco->GetFacing(&facingTmp);
        bool aligned = 0.9f < (facing->z * w.z + facing->y * w.y) + w.x * facing->x;
        bool slotWait;
        if (canMelee == true && st->mSlot == -1) slotWait = true;
        else slotWait = false;

        if (dist <= rngOuter && rngInner <= dist && aligned && !slotWait) {
            st->mAttackTimer = st->mAttackReset;
            self->Attack(tid, 0);
            st->mTarget = -1;
            st->mTimer0 = FUN_004df2d0(DAT_01581244);
            st->mB25 = true;
            goto done;
        }

        float lx = tpos->x - pos->x;
        float lz = tpos->z - pos->z;
        float ly = tpos->y - pos->y;
        float rr = rngOuter + sum;
        if (aligned && !((lx * lx + lz * lz) + ly * ly > rr * rr) && !slotWait)
            goto done;

        LocoState_s00d6_97a0* ls = loco->GetState();
        if (ls->mHasPath != 0) {
            Vec3* cp = ls->GetPos();
            float ex = cp->x - tpos->x;
            float ey = cp->y - tpos->y;
            float ez = cp->z - tpos->z;
            float rad = myObj->GetRadius();
            if ((ex * ex + ez * ez) + ey * ey <= rad * rad)
                goto done;
        }

        if (mode == 3 || tobj->m7c == 1 || tobj->m7c == 3) {
            self->MoveToPointAtSpeed(2, tpos, approach, approach + DAT_0157206c);
            loco->GetState()->mMoveFlags |= 2;
        } else if (GetFightSlots(self, &st->mSlot, big->m1a4)) {
            if (!tobj->FUN_00c0b000()) {
                self->MoveToPointAtSpeed(2, tpos, approach, approach + 0.2f);
                loco->GetState()->mMoveFlags |= 4;
                loco->GetState()->mMoveFlags |= 1;
                goto done;
            }
            self->MoveToPointAtSpeed(2, tpos, sum, sum + 0.2f);
            loco->GetState()->mMoveFlags |= 2;
        } else {
            float prop = GetPropertyT_float(DAT_01581288, 0x5753ef17, 5.0f);
            if (prop < dist) {
                self->MoveToPointAtSpeed(2, tpos, prop + sum, prop + sum);
                loco->GetState()->mMoveFlags |= 1;
                goto done;
            }
            if (dist < prop * 0.25f
                && (tgtCreature == 0 || tgtCreature != self->GetTargetAsCreature())) {
                float x = prop + sum;
                Vec3 d3;
                d3.x = pos->x - tpos->x;
                d3.y = pos->y - tpos->y;
                d3.z = pos->z - tpos->z;
                Vec3 tmp;
                Vec3* n = normalized_safe(&tmp, &d3);
                Vec3 res;
                res.x = tpos->x + n->x * x;
                res.y = tpos->y + n->y * x;
                res.z = tpos->z + n->z * x;
                FUN_00d99e20(pos, &res);
                self->MoveToPointAtSpeed(2, &res, 0.2f, dt);
                loco->GetState()->mMoveFlags |= 1;
                goto done;
            }
        }
        loco->GetState()->mMoveFlags |= 1;
    }
done:
    if (!st->mB25 && loco->GetState()->mHasPath != 0) {
        st->mB25 = true;
        self->InterruptAnimation(0x4cffb, -1, 0);
    }
    return true;
}
}  // namespace SP
