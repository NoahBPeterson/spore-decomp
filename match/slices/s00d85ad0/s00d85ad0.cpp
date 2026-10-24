// Slice s00d85ad0 -- SP creature behaviour-tree callbacks: eat/evolve/death and the
// SIT_ITEM_ON_HEAD / RECEIVE_ITEM / DIG_UP_OBJECT activate/tick/deactivate group (retail).
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//
// Every entry point is a __cdecl behaviour-tree callback.  The first argument is the creature
// (cSPCreatureBase); the generic callback slots follow, and the last argument is the per-behaviour
// state block owned by the tree node.
#include "types.h"
#include <math.h>

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- shared constants (.rdata/.data)
extern const float kOne;          // 0x01485720  1.0
extern const float kTwo;          // 0x01470f1c  2.0
extern const float kThree;        // 0x013eb95c  3.0
extern const float kFive;         // 0x01486110  5.0
extern const float kTen;          // 0x01473c70  10.0
extern const float kFifteen;      // 0x014007f4  15.0
extern const float kSixty;        // 0x013ebc4c  60.0
extern const float kFifty;        // 0x013f1cac  50.0
extern const float kPointNine;    // 0x013ec4b4  0.9
extern const float kHalf;         // 0x01471064  0.5
extern const float kFloatMax;     // 0x0147c030  FLT_MAX
extern const float kZero;         // 0x01485378  0.0
extern const float kPropDefault;  // 0x014853bc  default death time
extern const float kEffect14;     // 0x0169f03c
extern const float kEffect18;     // 0x0169f040
extern const float kEffect1c;     // 0x0169f044
extern const float kSpec04;       // 0x0169f0d4
extern const float kSpec08;       // 0x0169f0d8
extern const float kSpec0c;       // 0x0169f0dc
extern const float kRadiusScale;  // 0x01582e7c
extern const float kEvolveSpeed;  // 0x015d9c6c
extern const char  gModeCreatureA;  // 0x01654c10  (creature-mode sentinel)
extern const char  gModeCreatureB;  // 0x01654c01
extern const char  gModeCreatureC;  // 0x01654c02
extern const char  gSpecMatrix;     // 0x0169f0b0  (Matrix33 source)
extern void*       gPropertyList;   // 0x01581288
extern void*       gTribeFactor;    // 0x01582e54

// ---------------------------------------------------------------- generic ref-counted object view
class cInteractableObject;

class cObj {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    virtual void vf08(int a);                     // +0x08
    PV(3) PV(4) PV(5)
    virtual void vf18(void* p);                   // +0x18
    PV(7)
    virtual void vf20(void* p);                   // +0x20
    PV(9) PV(10)
    virtual const Vec3* GetPosition();            // +0x2c
    PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
    PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual float GetRadius();                    // +0x74
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45)
    virtual cObj* Query(uint32_t id);             // +0xb8
    virtual void AddRefBundle();                  // +0xbc
    virtual void ReleaseBundle();                 // +0xc0
};

// A noun: its +0x2c slot is a "is dead / finished" predicate, not a position getter.
class cNoun {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool IsFinished();                    // +0x2c
};

// Spatial / locomotive sub-object embedded at creature +0xc0.
class cLoco {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();            // +0x2c
    PV(12) PV(13) PV(14) PV(15)
    virtual void vf40(float f);                   // +0x40
    PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28)
    virtual float GetRadius();                    // +0x74
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41)
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
    PV(54)
    virtual void PlayEffectSpec(void* spec);      // +0xdc
    PV(56) PV(57) PV(58) PV(59) PV(60) PV(61)
    virtual bool vfF8();                          // +0xf8
    float __thiscall FUN_00c887c0();              // 0x00c887c0, ret 0
};

// Behaviour tree stored at creature +0xb4c; both entry points are invoked on this + 8.
class BehaviorTreeHead {
public:
    cObj* __thiscall Play(unsigned id, int flags);      // 0x00bc96a0, ret 8
    void  __thiscall ClearAll(unsigned a, unsigned mask);  // 0x00bc98f0, ret 8
};
struct nSPBehaviorTree {
    uint32_t pad00[2];                            // +0x00..+0x07
    BehaviorTreeHead mHead;                       // +0x08
};

// Record handed back by Play(): +0x0c is a kind tag, +0x10 an interpreted value, +0x14/+0x18
// two animation ids.
class cAnimNode {
public:
    uint32_t pad00[3];                            // +0x00
    int      mKind;                               // +0x0c
    int      m10;                                 // +0x10
    int      mAnim14;                             // +0x14
    int      mAnim18;                             // +0x18
    uint32_t pad1c[4];                            // +0x1c..+0x2b
    cObj*    mpBundle2c;                          // +0x2c
};

// Object at creature +0xb54 (death handler); +0x80 gets the 1.0 "dead" marker.
class cB54 {
public:
    uint32_t pad00[0x80 / 4];                     // +0x00..+0x7f
    float    mf80;                                // +0x80
};

class Citizen;

class cGameNounManager {
public:
    uint32_t pad00[0x54 / 4];                     // +0x000
    Citizen* mpAvatar;                            // +0x054
    uint32_t pad58[(0x70 - 0x58) / 4];            // +0x058
    void*    mpPlayer;                            // +0x070
    void* __thiscall GetAvatar();                 // 0x00b1fdb0, ret 0
    void* __thiscall GetPlayerTribe();            // 0x00bfc5f0, ret 0
    void  __thiscall RemoveNoun(void* noun);      // 0x00b225d0, ret 4
};

// Object at creature +0xb20 (creature settings); +0x590 "already eaten" float and the +0x504
// position used when there is no model.
class cCreatureSettings {
public:
    uint32_t pad00[0x504 / 4];                    // +0x000
    Vec3     mPos504;                             // +0x504
    uint32_t pad510[(0x590 - 0x510) / 4];         // +0x510..+0x58f
    float    mf590;                               // +0x590
    uint32_t pad594[(0x73c - 0x594) / 4];         // +0x594..+0x73b
    cObj**   mpBegin73c;                          // +0x73c
    cObj**   mpEnd740;                            // +0x740
};

// Candidate object scanned by EatFood (creature/corpse-like noun).
class cFoodTarget {
public:
    uint32_t pad00[2];                            // +0x00..+0x07
    int      mType08;                             // +0x08  0x1b = edible corpse
    uint32_t pad0c[0x100 / 4];                    // +0x0c..+0x10b
    float    mf10c;                               // +0x10c  freshness / value
    uint32_t pad110[8];                           // +0x110..+0x12f
    void*    mpProps130;                          // +0x130
};

// ---------------------------------------------------------------- driven creature
class Citizen {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    PV(14) PV(15) PV(16) PV(17) PV(18)
    virtual int   vf4c();                         // +0x4c
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
    virtual float vf80(int a);                    // +0x80
    virtual void  vf84(void* obj, int a, int b);  // +0x84
    PV(34)
    virtual void  vf8c();                         // +0x8c
    uint8_t  pad04[0xc0 - 4];                     // +0x04..+0xbf (vptr first)
    cLoco    mLoco;                               // +0xc0
    uint32_t padC4[(0x110 - 0xc4) / 4];           // +0xc4..+0x10f
    uint32_t mFlags110;                           // +0x110
    uint8_t  pad114[0x12f - 0x114];               // +0x114..+0x12e
    uint8_t  mb12f;                               // +0x12f
    uint8_t  pad130[1];                           // +0x130
    uint8_t  mb131;                               // +0x131
    uint8_t  pad132[0x137 - 0x132];               // +0x132..+0x136
    uint8_t  mb137;                               // +0x137
    uint8_t  pad138[0xb20 - 0x138];               // +0x138..+0xb1f
    cCreatureSettings* mpSettings;                // +0xb20
    uint8_t  padB24[0xb4c - 0xb24];               // +0xb24..+0xb4b
    nSPBehaviorTree*   mpBehavior;                // +0xb4c
    uint8_t  padB50[0xb54 - 0xb50];               // +0xb50..+0xb53
    cB54*    mpB54;                               // +0xb54
    union {
        volatile uint32_t mFlagsB58;              // +0xb58..+0xb5b
        struct {
            uint16_t mB58lo;                      // +0xb58
            uint8_t  mbB5a;                       // +0xb5a
            uint8_t  mB58hi;                      // +0xb5b
        } mB58;
    };
    uint8_t  padB5c[0xb5e - 0xb5c];               // +0xb5c..+0xb5d
    uint8_t  mbB5e;                               // +0xb5e
    uint8_t  padB5f[0xb7c - 0xb5f];               // +0xb5f..+0xb7b
    float    mfB7c;                               // +0xb7c
    uint8_t  padB80[0xbbc - 0xb80];               // +0xb80..+0xbbb
    float    mfBbc;                               // +0xbbc
    uint8_t  padBC0[0x1004 - 0xbc0];              // +0xbc0..+0x1003
    Vec3     mVec1004;                            // +0x1004
    uint8_t  pad1010[0x1674 - 0x1010];            // +0x1010..+0x1673
    void*    mpPlayer;                            // +0x1674

    float __thiscall GetFood();                   // 0x00c0b9c0, ret 0
    void  __thiscall SetFood(float f);            // 0x00c0b9d0, ret 4
    bool  __thiscall Flag388();                   // 0x00c0c0e0, ret 0
    void* __thiscall GetPlayer();                 // 0x00c04590, ret 0
    void* __thiscall GetGameData();               // 0x00c04750, ret 0
    void* __thiscall GetFoodPos();                // 0x00c0bc00, ret 0
    void  __thiscall FUN_00c0bbe0();              // 0x00c0bbe0, ret 0
    void  __thiscall FUN_00c0d240();              // 0x00c0d240, ret 0
    void  __thiscall FUN_00c14750(int a);         // 0x00c14750, ret 4
    void  __thiscall FUN_00c15bd0(int a, int b, int c);  // 0x00c15bd0, ret 0xc
    bool  __thiscall FUN_00c13c60(void* obj, int a, int b);  // 0x00c13c60, ret 0xc
    bool  __thiscall FUN_00c0f5f0();              // 0x00c0f5f0, ret 0
    int   __thiscall FUN_00c0f8f0(void* obj);     // 0x00c0f8f0, ret 4
    int   __thiscall FUN_00c0f4f0();              // 0x00c0f4f0, ret 0
    void  __thiscall FUN_00c19940(int a);         // 0x00c19940, ret 4
    void  __thiscall SetStealthed(int a, int b);  // 0x00c1aed0, ret 8
    int   __thiscall InterruptAnimation(unsigned id, int a, int b);  // 0x00c12310, ret 0xc
    int   __thiscall PlayAnimation(unsigned id, int a, int b);       // 0x00c12190, ret 0xc
    void* __thiscall GetTargetAsCreature();       // 0x00c0ee70, ret 0
    void  __thiscall MoveToPointAtSpeed(int mode, const Vec3* p, float f1, float f2);  // 0x00c1c1d0
    void  __thiscall MoveToPointAndFacingAtSpeed(int mode, const Vec3* p, const Vec3* dir,
                                                 float f1, float f2);  // 0x00c1c5c0, ret 0x14
    void* __thiscall SpecQuery(int a);            // 0x00c1d290, ret 4
};

// ---------------------------------------------------------------- other globals / helpers
void* __cdecl GetCurrentGameMode();                       // 0x00b5b800
void* __cdecl NounManager();                              // 0x00b3d300
void* __cdecl PlanetModel();                              // 0x00b3d350
void* __cdecl FUN_00b3d310();                             // 0x00b3d310
void  __cdecl FUN_00b453a0();                             // 0x00b453a0 (reads ecx + stack slot)
void  __cdecl FUN_00b57bf0(void* bundleA, void* bundleB, float f);  // 0x00b57bf0
void  __cdecl FUN_00b54300(void* bundleA, void* obj);     // 0x00b54300
void  __cdecl FUN_00b530e0(void* obj, int a);             // 0x00b530e0
cObj* __cdecl FUN_00d998d0(cAnimNode* node, unsigned id); // 0x00d998d0
cObj* __cdecl FUN_00d7cf70(void* holder);                 // 0x00d7cf70, ret 4
cObj* __cdecl FUN_00d7cf90(void* holder);                 // 0x00d7cf90, ret 4
void  __cdecl FUN_00d2e8a0(float value);                  // 0x00d2e8a0
void  __cdecl FUN_00f47380(void* p);                      // 0x00f47380 operator delete[]
float __cdecl FUN_004e1c70(void* props, unsigned id, float def);  // 0x004e1c70
bool  __cdecl FUN_0064f350(void* props, unsigned id, int unused);  // 0x0064f350
bool  __fastcall FUN_00c8e870(void* p);            // 0x00c8e870

class cPlanetModel {
public:
    Vec3* __thiscall MakeRandomWorldPosition(Vec3* out, const Vec3* pos, float near, float range);
};
class cMatrix3 {
public:
    void __thiscall Assign(const void* src);      // 0x0041cb40, ret 4
};

class cCreatureModeStrategy {
public:
    uint32_t pad00[0xb4 / 4];                     // +0x000..+0x0b3
    cObj*    mpB4;                                // +0x0b4
    void __thiscall SignalCreatureEvent(unsigned id);  // 0x00d3cdc0
};
cCreatureModeStrategy* __cdecl FUN_00d38840();    // 0x00d38840

// ---------------------------------------------------------------- behaviour state blocks
struct StateDeath {                                // 0x00d85c00
    float    mf0;                                  // +0x00  time/death duration
    float    mf4;                                  // +0x04
    float    mf8;                                  // +0x08
    float    mfc;                                  // +0x0c
    int      mEffect10;                            // +0x10  effect/anim key
    uint8_t  mb14;                                 // +0x14
    uint8_t  mb15;                                 // +0x15
    uint8_t  mb16;                                 // +0x16  corpse flag
    uint8_t  mb17;                                 // +0x17  eaten-by-avatar flag
};

struct StateSit {                                  // 0x00d86130
    uint32_t pad00[4];                             // +0x00..+0x0f
    float    mf10;                                 // +0x10
    uint32_t pad14[3];                             // +0x14..+0x1f
    cNoun*   mp20;                                 // +0x20
};

struct StateEvolve {                               // 0x00d85f20
    int      m0;                                   // +0x00
    int      m4;                                   // +0x04
    int      m8;                                   // +0x08
    float    mf0c;                                 // +0x0c  evolve duration
    float    mf10;                                 // +0x10
    Vec3     mPos;                                 // +0x14
    cObj*    m20;                                  // +0x20
};

struct StateSitHead {                              // 0x00d86240
    int      m0;                                   // +0x00
    int      m4;                                   // +0x04
    uint8_t  mb08;                                 // +0x08
    uint8_t  pad09[3];                             // +0x09..+0x0b
    int      m0c;                                  // +0x0c
    uint8_t  mb10;                                 // +0x10
    uint8_t  mb11;                                 // +0x11
    uint8_t  mb12;                                 // +0x12
};

struct StateItemOnHead {                           // 0x00d86410 / 0x00d865c0
    int      m0;                                   // +0x00
    int      m4;                                   // +0x04
    int      m8;                                   // +0x08
    cObj*    mp0c;                                 // +0x0c
    cObj*    mp10;                                 // +0x10
    uint8_t  mb14;                                 // +0x14
};

struct StateReceive {                              // 0x00d86690 / 0x00d86850
    cObj*    mp0;                                  // +0x00
    int      m4;                                   // +0x04
    cObj*    mp8;                                  // +0x08
    int      m0c;                                  // +0x0c
};

struct StateReact {                                // 0x00d86810
    cObj*    mp0;                                  // +0x00
};

struct StateDig {                                  // 0x00d86940
    int      m0;                                   // +0x00
    uint32_t pad04;                                // +0x04
    cInteractableObject* mp8;                      // +0x08
};

// Ref-holding wrappers used by the item behaviours (out-of-line assign operators).
struct RefHolder {
    cObj* mp;
    void  __thiscall Assign(cObj* p);             // 0x00c70110, ret 4
};
struct AutoRef {
    cObj* mp;
    AutoRef& __thiscall operator=(cObj* p);       // 0x00b5f950, ret 4
};

// Interactive ornament query target.
class cOrnament {
public:
    uint32_t pad00[(0x108 - 0) / 4];              // +0x000
    cObj*    mp108;                                // +0x108
    uint32_t pad10c[(0x16c - 0x10c) / 4];         // +0x10c
    int      mState16c;                            // +0x16c
};

class cInteractiveOrnament {
public:
    uint32_t pad00[(0x238 - 0) / 4];              // +0x000
    uint32_t mFlags238;                            // +0x238
    void __thiscall SetLifetime(float lifetime, int flag);  // 0x00c40830, ret 8
};

// A spatial bundle target: +0xb8 query, +0x16c interaction state.
class cInteractableObject {
public:
    virtual void AddRef();                        // +0x00
    virtual void Release();                       // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22)
    PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31) PV(32) PV(33) PV(34)
    PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45)
    virtual cOrnament* Query(uint32_t id);        // +0xb8
    virtual void AddRefBundle();                  // +0xbc
    virtual void ReleaseBundle();                 // +0xc0
    uint8_t  pad04[0x70 - 4];                     // +0x04..+0x6f
    uint8_t  mb70;                                // +0x70
    uint8_t  pad71[0x108 - 0x71];                 // +0x71..+0x107
    cObj*    mp108;                               // +0x108
    uint8_t  pad10c[0x16c - 0x10c];               // +0x10c..+0x16b
    int      mState16c;                            // +0x16c
};

// ---------------------------------------------------------------- stack effect specs
struct Mat33 { float m[9]; };

struct EffectSpecSmall {                          // 0x00d85e40: 0x38 bytes
    short    m00;                                  // +0x00
    short    m02;                                  // +0x02
    float    mf04;                                 // +0x04
    float    mf08;                                 // +0x08
    float    mf0c;                                 // +0x0c
    float    mf10;                                 // +0x10
    Mat33    mMat;                                 // +0x14
};

struct EffectSpec {                                // 0x00d86240: 0x78 bytes
    void*    mpData;                               // +0x00
    void*    mpEnd;                                // +0x04
    void*    mpCap;                                // +0x08
    uint32_t m0c;                                  // +0x0c
    float    mf10;                                 // +0x10
    float    mf14;                                 // +0x14
    float    mf18;                                 // +0x18
    float    mf1c;                                 // +0x1c
    float    mf20;                                 // +0x20
    uint32_t m24;                                  // +0x24
    int      m28;                                  // +0x28
    uint8_t  pad2c[0x50 - 0x2c];                   // +0x2c..+0x4f
    uint8_t  mb50;                                 // +0x50
    uint8_t  pad51[3];                             // +0x51..+0x53
    float    mf54;                                 // +0x54
    float    mf58;                                 // +0x58
    float    mf5c;                                 // +0x5c
    float    mf60;                                 // +0x60
    float    mf64;                                 // +0x64
    uint32_t m68;                                  // +0x68
    float    mf6c;                                 // +0x6c
    float    mf70;                                 // +0x70
    int      m74;                                  // +0x74
};

// Query interface of the strategy field at +0xb4 (variant lookup with an out pointer).
class cB4Obj {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool Query(uint32_t id, void** out);  // +0x24
};

// Variant payload returned through that out pointer.
struct Variant {
    uint32_t m0;                                   // +0x00  value or pointer
    uint8_t  mFlags10;                             // +0x10  bit 0x30 = by reference
    uint8_t  pad11;                                // +0x11
    uint16_t mType12;                              // +0x12  0x0d/0x10 = numeric
};

class cPlayerNear {
public:
    uint8_t pad00[0x34];                           // +0x00..+0x33
    cLoco   mBundle;                               // +0x34
};
class cPlayerData {
public:
    uint8_t pad00[0x160];                          // +0x000..+0x15f
    cPlayerNear* mpNear160;                        // +0x160
    const Vec3* __thiscall GetPosition();          // 0x00c6acc0, ret 0
};

class cGlobalMgr {
public:
    void __thiscall FUN_00b453a0(void* loco);      // 0x00b453a0, ret 4
};

// ===========================================================================
// @ 0x00d85ad0
// SP::EatFood
// ===========================================================================
namespace SP {

void __cdecl EatFood(Citizen* c, float amount, unsigned id, int flag)
{
    if (c == 0)
        return;
    c->SetFood(c->GetFood() + amount);
    if (((unsigned char)(c->mFlagsB58 >> 9) & 1) == 0)
        return;
    if (GetCurrentGameMode() != &gModeCreatureA) {
        cCreatureModeStrategy* strategy = FUN_00d38840();
        strategy->SignalCreatureEvent(0xd35dd8c3);
    }
    if (flag == 0)
        return;
    cFoodTarget* best = 0;
    cObj** it = c->mpSettings->mpBegin73c;
    cObj** end = c->mpSettings->mpEnd740;
    while (it != end) {
        cFoodTarget* t = (cFoodTarget*)*it;
        if (t->mType08 == 0x1b) {
            bool hasA = FUN_0064f350(t->mpProps130, 0x23705bcc, 0);
            bool hasB = FUN_0064f350(t->mpProps130, 0x3d9ae5b3, 0);
            bool ok;
            if (id == 0x333b8596)
                ok = hasA;
            else if (id == 0xd33b8593)
                ok = hasB;
            else
                ok = true;
            if (ok && (best == 0 || t->mf10c > best->mf10c))
                best = t;
        }
        ++it;
    }
    if (best != 0)
        FUN_00d2e8a0(best->mf10c);
}

// ===========================================================================
// @ 0x00d85c00
// SP::DEATH_Activate
// ===========================================================================
bool __cdecl DEATH_Activate(Citizen* c, void*, void*, void*, void*, StateDeath* st)
{
    st->mb16 = c->mbB5e;
    st->mb17 = 0;
    c->vf8c();
    c->mfB7c = kOne;
    c->mpB54->mf80 = kOne;
    void* mode = GetCurrentGameMode();
    if (GetCurrentGameMode() == &gModeCreatureC) {
        void* tribe = ((cGameNounManager*)NounManager())->GetPlayerTribe();
        if (tribe == 0)
            st->mf0 = kFifteen;
        else if (FUN_00c8e870(tribe) && c->vf4c() == -1)
            st->mf0 = FUN_004e1c70(gPropertyList, 0x7c399e92, kSixty);
        else
            st->mf0 = FUN_004e1c70(gPropertyList, 0xdef7dd75, kPropDefault);
    } else if (mode == &gModeCreatureB) {
        st->mf0 = kSixty;
    } else if (mode == &gModeCreatureA) {
        char* data = (char*)c->GetGameData();
        if (data != 0 && data[2] != 0) {
            st->mf0 = kFloatMax;
            st->mb17 = 1;
        } else {
            st->mf0 = kFifteen;
        }
    } else {
        st->mf0 = kFifteen;
    }
    st->mf4 = kThree;
    st->mf8 = kThree;
    st->mfc = kOne;
    st->mb14 = 0;
    st->mb15 = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0x400, 0);
    int kind = 2;
    if (node != 0)
        kind = node->mKind;
    if (kind == 5)
        st->mEffect10 = 0x54ac179;
    else if (kind == 0x11)
        st->mEffect10 = 0x60db981;
    else if (kind == 0x12)
        st->mEffect10 = 0x779e183;
    else
        st->mEffect10 = 0xf14faa46;
    if (st->mb16 == 0 && st->mb17 == 0) {
        if ((unsigned char)(c->mFlagsB58 >> 9) & 1)
            c->GetFood();
        if (c->mLoco.FUN_00c887c0() > kFifty)
            st->mEffect10 = 0x92aa59ce;
        if (c->Flag388()) {
            char* data = (char*)c->GetPlayer();
            int n = *(int*)(data + 0xf4) - 1;
            float f = (float)n;
            if (f < 0.0f)
                f = 0.0f;
            *(int*)(data + 0xf4) = (int)f;
        }
    } else {
        st->mEffect10 = 0x5807346 - (c->Flag388() ? 1 : 0);
    }
    return true;
}

// ===========================================================================
// @ 0x00d85e40
// creature "reset effect + animation" helper
// ===========================================================================
bool __cdecl FUN_00d85e40(Citizen* c)
{
    cObj* fx = (cObj*)c->SpecQuery(0xf6ceaad6);
    if (fx != 0) {
        EffectSpecSmall spec;
        spec.m00 = 0;
        spec.m02 = 0;
        spec.mf04 = kSpec04;
        spec.mf08 = kSpec08;
        spec.mf0c = kSpec0c;
        spec.mf10 = kOne;
        ((cMatrix3*)&spec.mMat)->Assign(&gSpecMatrix);
        fx->vf20(&spec);
        spec.mf10 = c->mLoco.GetRadius() * kRadiusScale;
        spec.m02++;
        fx->vf18(&spec);
        fx->vf08(0);
    }
    c->InterruptAnimation(0x65d31ac, -1, 0);
    c->mFlagsB58 |= 4;
    return true;
}

// ===========================================================================
// @ 0x00d85f20
// SP::EVOLVE_Activate
// ===========================================================================
bool __cdecl EVOLVE_Activate(Citizen* c, void*, void*, void*, void*, StateEvolve* st)
{
    if (st != 0)
        st->m20 = 0;
    bool instant = (c->mB58.mbB5a & 1) != 0;
    st->m8 = 0x37048f6;
    cCreatureModeStrategy* strategy = FUN_00d38840();
    Variant* info = 0;
    float speed;
    if (strategy->mpB4 != 0 && ((cB4Obj*)strategy->mpB4)->Query(0xc4f054b6, (void**)&info)) {
        if (info->mType12 == 0xd || info->mType12 == 0x10) {
            if ((info->mFlags10 & 0x30) != 0)
                speed = *(float*)info->m0;
            else
                speed = *(float*)&info->m0;
        } else {
            speed = kEvolveSpeed;
        }
    } else {
        speed = kSixty;
    }
    st->mf0c = speed;
    st->mf10 = 0;
    st->mPos = *c->mLoco.GetPosition();
    st->m4 = 0;
    if (instant) {
        st->m0 = 2;
        c->mb131 = 1;
        c->mb12f = 0;
        Citizen* avatar = (Citizen*)((cGameNounManager*)NounManager())->GetAvatar();
        if (avatar != 0 && avatar->GetTargetAsCreature() == c)
            avatar->vf84(0, 0, 0);
    } else {
        float near = kFive;
        float range = kTen;
        st->m0 = 0;
        cPlayerData* player = (cPlayerData*)c->GetPlayer();
        if (player->mpNear160 != 0) {
            near = player->mpNear160->mBundle.GetRadius();
            range = c->mLoco.GetRadius() * kTwo + player->mpNear160->mBundle.GetRadius();
        }
        Vec3 out;
        Vec3* r = ((cPlanetModel*)PlanetModel())->MakeRandomWorldPosition(
                      &out, player->GetPosition(), near, range);
        st->mPos = *r;
        c->MoveToPointAtSpeed(2, &st->mPos, kOne, kTwo);
    }
    c->FUN_00c14750(0);
    c->mFlagsB58 |= 4;
    return true;
}

}  // namespace SP

// ===========================================================================
// @ 0x00d86130
// sit/stop tick: snap to the food position and detach the seat noun
// ===========================================================================
void __cdecl FUN_00d86130(Citizen* c, void*, void*, void*, void*, StateSit* st)
{
    Vec3* food = (Vec3*)c->GetFoodPos();
    if (*(int*)&c->mVec1004.x == *(int*)&food->x &&
        *(int*)&c->mVec1004.y == *(int*)&food->y &&
        *(int*)&c->mVec1004.z == *(int*)&food->z) {
        *(int*)&c->mVec1004.x = 0;
        if (st->mf10 != kZero) {
            c->mLoco.vf40(st->mf10);
            c->FUN_00c0bbe0();
        }
    } else {
        c->mLoco.vf40(c->vf80(0));
        c->FUN_00c0bbe0();
    }
    ((cGlobalMgr*)FUN_00b3d310())->FUN_00b453a0(&c->mLoco);
    c->mb131 = 0;
    c->mb12f = 1;
    c->FUN_00c14750(0);
    c->mFlagsB58 &= 0xfffefffb;
    if (st->mp20 != 0) {
        if (!st->mp20->IsFinished())
            ((cGameNounManager*)NounManager())->RemoveNoun(st->mp20);
    }
    if (st->mp20 != 0)
        st->mp20->Release();
}

// ===========================================================================
// @ 0x00d86240
// sit-on-head tick: animation selection + effect spec
// ===========================================================================
bool __cdecl FUN_00d86240(Citizen* c, void*, void*, void*, void*, void*, void*, StateSitHead* st)
{
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0x1000, 0);
    if (node == 0)
        return false;
    st->mb10 = FUN_00d998d0(node, 0x3a25119) != 0;
    st->m0c = 0;
    st->mb08 = node->mKind == 1;
    st->mb12 = 0;
    st->mb11 = node->mKind == 2;
    if (st->mb08) {
        st->m0 = node->mAnim14;
        st->m4 = node->mAnim18;
        c->InterruptAnimation(st->m0, -1, 0);
        c->PlayAnimation(st->m4, 1, -1);
    } else if (st->mb11) {
        st->m0c = c->InterruptAnimation(0x63bfcaa, -1, 0);
    } else if (st->mb10) {
        st->m0c = c->InterruptAnimation(0x61c2bfe, -1, 0);
    } else if (c->mb137 == 0 && (c->mFlags110 & 0x1000) == 0) {
        st->mb12 = 1;
    } else {
        st->m0c = c->InterruptAnimation(0x2481e14, -1, 0);
    }
    c->SetStealthed(0, 0);
    EffectSpec spec;
    spec.mf14 = kEffect14;
    spec.mf18 = kEffect18;
    spec.mf1c = kEffect1c;
    spec.mf20 = kOne;
    *(volatile float*)&spec.mf60 = kTwo;
    spec.mf64 = kPointNine;
    spec.mpData = 0;
    spec.mpEnd = 0;
    spec.mpCap = 0;
    spec.m28 = 0;
    spec.mb50 = 0;
    spec.mf54 = 0;
    spec.mf58 = 0;
    spec.mf5c = 0;
    spec.mf60 = 0;
    spec.mf6c = kFloatMax;
    spec.mf70 = 0;
    spec.m74 = 0;
    c->mLoco.PlayEffectSpec(&spec);
    if (spec.mpData != 0 && *(int*)((char*)spec.mpData - 4) != 0)
        FUN_00f47380(spec.mpData);
    return true;
}

// ===========================================================================
// @ 0x00d86410
// SP::SIT_ITEM_ON_HEAD_Tick
// ===========================================================================
bool __cdecl FUN_00d86410(Citizen* c, void*, void*, void*, void*, StateItemOnHead* st)
{
    if (st != 0) {
        st->mp0c = 0;
        st->mp10 = 0;
    }
    st->m0 = 0;
    st->m4 = -1;
    st->m8 = -1;
    st->mb14 = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x40000);
    if (node == 0 || node->mKind != 4)
        return false;
    if (!c->FUN_00c0f4f0()) {
        c->mpBehavior->mHead.ClearAll(0, 0x40000);
        return false;
    }
    ((RefHolder*)&st->mp0c)->Assign(FUN_00d998d0(node, 0x1186577));
    ((AutoRef*)&st->mp10)->operator=(FUN_00d998d0(node, 0x2c9cc8e));
    if (st->mp0c != 0 && c->FUN_00c0f8f0(st->mp0c) != -1)
        return false;
    if (c->FUN_00c0f5f0()) {
        c->FUN_00c15bd0(0, 0, 0);
        if (c->FUN_00c0f5f0())
            return false;
    }
    if (c->mpSettings->mf590 == 0.0f)
        st->mb14 = 1;
    if (st->mp0c != 0) {
        if (!c->FUN_00c13c60(st->mp0c, 0, 0))
            return false;
        cInteractableObject* obj = (cInteractableObject*)FUN_00d7cf70(&st->mp0c);
        if (obj != 0 && obj->mState16c != 2)
            return false;
        cInteractableObject* p = (cInteractableObject*)FUN_00d7cf90(&st->mp0c);
        if (p != 0) {
            if (p->mp108 != 0 && p->mp108 != (cObj*)c && ((unsigned char)(c->mFlagsB58 >> 9) & 1) == 0)
                return false;
            ((AutoRef*)&p->mp108)->operator=((cObj*)c);
        }
    } else {
        if (st->mp10 != 0 && ((cInteractableObject*)st->mp10)->mState16c != 0)
            return false;
    }
    if (!c->mLoco.vfF8())
        c->FUN_00c14750(1);
    c->vf84(0, 0, 0);
    return true;
}

// ===========================================================================
// @ 0x00d865c0
// SP::SIT_ITEM_ON_HEAD_Deactivate
// ===========================================================================
void __cdecl FUN_00d865c0(Citizen* c, void*, void*, void*, void*, StateItemOnHead* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st->mp0c != 0) {
        if (st->m0 == 2 || st->m0 == 0) {
            if (st->mp0c != 0) {
                cOrnament* o = (cOrnament*)st->mp0c->Query(0x398420d);
                if (o != 0) {
                    if (o->mp108 == (cObj*)c) {
                        if (cObj* old = o->mp108) {
                            o->mp108 = 0;
                            old->Release();
                        }
                    }
                }
            }
        }
    }
    cObj* p = st->mp0c;
    if (p != 0) {
        st->mp0c = 0;
        p->ReleaseBundle();
    }
    p = st->mp10;
    if (p != 0) {
        st->mp10 = 0;
        p->Release();
    }
    c->FUN_00c14750(0);
    if (st->mp10 != 0)
        st->mp10->Release();
    if (st->mp0c != 0)
        st->mp0c->ReleaseBundle();
}

// ===========================================================================
// @ 0x00d86690
// SP::RECEIVE_ITEM_Tick
// ===========================================================================
bool __cdecl FUN_00d86690(Citizen* c, void*, void*, void*, void*, StateReceive* st)
{
    if (st != 0)
        st->mp0 = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x40000);
    cObj* p = FUN_00d998d0(node, 0x1186577);
    cObj* old = st->mp0;
    if (p != old) {
        if (p != 0)
            p->AddRefBundle();
        st->mp0 = p;
        if (old != 0)
            old->ReleaseBundle();
    }
    st->m4 = node->m10;
    Vec3 pos = *st->mp0->GetPosition();
    float r = st->mp0->GetRadius();
    const Vec3* cp = c->mLoco.GetPosition();
    float dx = pos.x - cp->x;
    float dy = pos.y - cp->y;
    float dz = pos.z - cp->z;
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    Vec3 dir;
    dir.x = dx * inv;
    dir.y = dy * inv;
    dir.z = dz * inv;
    c->MoveToPointAndFacingAtSpeed(2, &pos, &dir, r, r + kFive);
    return true;
}

// ===========================================================================
// @ 0x00d86810
// SP::REACT_TO_AVATAR_Deactivate
// ===========================================================================
namespace SP {

void __cdecl REACT_TO_AVATAR_Deactivate(Citizen* c, void*, void*, void*, void*, StateReact* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st != 0 && st->mp0 != 0)
        st->mp0->ReleaseBundle();
}

}  // namespace SP

// ===========================================================================
// @ 0x00d86850
// receive-item activate: attach the item to the creature
// ===========================================================================
bool __cdecl FUN_00d86850(Citizen* c, void*, void*, void*, void*, StateReceive* st)
{
    if (st != 0)
        st->mp8 = 0;
    st->mp0 = 0;
    st->m4 = -1;
    st->m0c = 0;
    cAnimNode* node = (cAnimNode*)c->mpBehavior->mHead.Play(0, 0x40000);
    if (node == 0 || node->mKind != 5)
        return false;
    ((RefHolder*)&st->mp8)->Assign(FUN_00d998d0(node, 0x1186577));
    if (st->mp8 == 0)
        return false;
    c->FUN_00c19940(0);
    if (st->mp8 == 0)
        return false;
    cInteractableObject* obj = (cInteractableObject*)st->mp8->Query(0x398420d);
    if (obj == 0)
        return false;
    if (obj->mp108 != 0 && obj->mp108 != (cObj*)c && ((unsigned char)(c->mFlagsB58 >> 9) & 1) == 0)
        return false;
    cLoco* loco = &c->mLoco;
    FUN_00b57bf0(loco, (char*)obj + 0x34, kFloatMax);
    ((AutoRef*)&obj->mp108)->operator=((cObj*)c);
    return true;
}

// ===========================================================================
// @ 0x00d86940
// SP::DIG_UP_OBJECT_Deactivate
// ===========================================================================
void __cdecl FUN_00d86940(Citizen* c, void*, void*, void*, void*, StateDig* st)
{
    c->mpBehavior->mHead.ClearAll(0, 0x40000);
    if (st->m0 == 2) {
        FUN_00b530e0(st->mp8, 0);
        st->mp8->mb70 = 0;
        if (st->mp8 != 0) {
            cInteractiveOrnament* o = (cInteractiveOrnament*)st->mp8->Query(0x3a25119);
            if (o != 0)
                o->SetLifetime(kHalf, 1);
        }
    } else {
        FUN_00b54300(&c->mLoco, st->mp8);
    }
    c->FUN_00c14750(0);
    if (st->mp8 != 0) {
        cInteractableObject* o = (cInteractableObject*)st->mp8->Query(0x398420d);
        if (o != 0) {
            if (o->mp108 == (cObj*)c) {
                if (cObj* old = o->mp108) {
                    o->mp108 = 0;
                    old->Release();
                }
            }
        }
    }
    cInteractableObject* p = st->mp8;
    if (p != 0) {
        st->mp8 = 0;
        p->ReleaseBundle();
    }
    if (st->mp8 != 0)
        st->mp8->ReleaseBundle();
}


