// src/game/SPGonzago/_at_00dc0000.cpp -- migrated from slice(s) s00dc48e0, s00dc3940, s00dc2720, s00dc18e0, s00dc0040 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00dc0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"

// unnamed retail callees and globals (address in the comment)
extern "C" float __cdecl sqrtf(float);
extern float g_one;      // 0x01485720  (1.0f)
extern float g_9d5f8;    // 0x0159d5f8
extern float g_9d604;    // 0x0159d604
extern float g_9d608;    // 0x0159d608
extern float g_9d60c;    // 0x0159d60c
extern float g_9d610;    // 0x0159d610
extern float g_9d614;    // 0x0159d614
extern float g_9d628;    // 0x0159d628
extern float g_9d630;    // 0x0159d630
extern float g_9d634;    // 0x0159d634
extern float g_9d638;    // 0x0159d638
extern float g_9d63c;    // 0x0159d63c
extern float g_473c70;   // 0x01473c70
extern float g_47c308;   // 0x0147c308
extern float g_3ec4d0;   // 0x013ec4d0
extern float g_3eb1bc;   // 0x013eb1bc
extern float g_3eecd8;   // 0x013eecd8
extern float g_fA18;     // 0x0169fa18
extern float g_fA1c;     // 0x0169fa1c
extern float g_fA20;     // 0x0169fa20
extern float g_fA24;     // 0x0169fa24
extern float g_fA28;     // 0x0169fa28
extern float g_fA2c;     // 0x0169fa2c
extern "C" void* SPGetUFOSimulator();                        // 0x00ffbe50
extern "C" void* GetBestUFOTarget(void*, unsigned, int);     // 0x0102bc90
extern "C" void* PlanetModel(void*, void*, float, float);    // 0x00b3d350
extern "C" float RandomSigned(float);                        // 0x00572a60
#include <intrin.h>
#include "SP/cPlanetModel.h"
#include <math.h>
#include "nSPBehaviorTree/behavior_stimuli.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cCombatant.h"
#include "SP/cCommunity.h"
#include "SP/cGameNounManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cLocomotiveObject.h"

// ---- items of slice s00dc0040 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
struct Vec3 { float x, y, z; };
extern "C" float __cdecl sqrtf(float);
extern float g_one;      // 0x01485720  (1.0f)
extern float g_9d5f8;    // 0x0159d5f8
extern float g_9d604;    // 0x0159d604
extern float g_9d608;    // 0x0159d608
extern float g_9d60c;    // 0x0159d60c
extern float g_9d610;    // 0x0159d610
extern float g_9d614;    // 0x0159d614
extern float g_9d628;    // 0x0159d628
extern float g_9d630;    // 0x0159d630
extern float g_9d634;    // 0x0159d634
extern float g_9d638;    // 0x0159d638
extern float g_9d63c;    // 0x0159d63c
extern float g_473c70;   // 0x01473c70
extern float g_47c308;   // 0x0147c308
extern float g_3ec4d0;   // 0x013ec4d0
extern float g_3eb1bc;   // 0x013eb1bc
extern float g_3eecd8;   // 0x013eecd8
extern float g_fA18;     // 0x0169fa18
extern float g_fA1c;     // 0x0169fa1c
extern float g_fA20;     // 0x0169fa20
extern float g_fA24;     // 0x0169fa24
extern float g_fA28;     // 0x0169fa28
extern float g_fA2c;     // 0x0169fa2c
extern struct RRngObj g_rng;   // 0x01601760 (the RNG object itself)
struct Sub {                             // view on the outer object (this in ecx)
    void  Be70(void* p);                 // 0x00c3be70
    void  Daa0(float f);                 // 0x00c3daa0
    char* B00();                         // 0x00c38b00  -> returns an object*
    void  B10();                         // 0x00c38b10
    char* B80();                         // 0x00c38b80  -> returns an object*
    char* B7720();                       // 0x00c37720  -> returns an object*
    void  Bf0(int, int, float, int);     // 0x00bc97f0  (this = *(+0x6c8) + 8)
    bool  C8990(int a);                  // 0x00c38990
    float C7120();                       // 0x00c37120  (this = the target object)
};
struct Planet { float* MakeRandomWorldPosition(); };   // 0x00b81780 (thiscall, 0 args)
struct Sub2 { float F10(); };                          // 0x0104be30 (thiscall, 0 args)
struct RRngObj {                         // 0x01601760 (RNG instance, direct object)
    unsigned RandomUint32Uniform(unsigned n);  // 0x00a68fb0
    double   RandomDoubleUniform();            // 0x009360d0
};
struct Sim { void* GetPlayerInventory(); };    // 0x00a1ad60 (this = UFO simulator)
extern "C" void* SPGetUFOSimulator();                        // 0x00ffbe50
extern "C" void* GetBestUFOTarget(void*, unsigned, int);     // 0x0102bc90
extern "C" void* PlanetModel(void*, void*, float, float);    // 0x00b3d350
extern "C" float RandomSigned(float);                        // 0x00572a60
// ---- items of slice s00dc0040 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern struct RRngObj g_rng;   // 0x01601760 (the RNG object itself)

// ---- items of slice s00dc18e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cPlanetModel_s00dc_18e0 {
 public:
  float GetRadiusAt(const void* pos);                          // 0x00b7ef70: thiscall, ret 4
};
}
namespace SP {
cPlanetModel_s00dc_18e0* PlanetModel();                                   // 0x00b3d350: cdecl, no args
}
namespace SP {
int    GetBestUFOTarget_s00dc_18e0(void* self, unsigned int flag, int zero);  // 0x0102bc90: cdecl, 3 args
}
namespace SP {
int    Fun_102c460(void* self);                                // 0x0102c460: cdecl, 1 arg
}
namespace SP {
int    Fun_cc15b0(int a, int b);                               // 0x00cc15b0: cdecl, 2 args
}
namespace SP {
int    Fun_b67740(void* a);                                    // 0x00b67740: cdecl, 1 arg
}
namespace SP {
float* Fun_59aed0(void* out, const void* a, const void* b);    // 0x0059aed0: cdecl, 3 args
}
namespace SP {
float* Fun_b0fd00(void* out, const void* a, const void* b, float t);  // 0x00b0fd00 RotateTowards: cdecl, 4 args
}
namespace SP {
void   QuaternionFromFacingAndUp(void* out, const void* facing, const void* up);  // 0x0069b600: cdecl
}
namespace SP {
float* Fun_5b2500(const void* a, const void* b, const void* c, float t);          // 0x005b2500 Slerp: cdecl
}
namespace SP {
void   Fun_dc00a0(float* out, int arg, void* self);            // 0x00dc00a0: cdecl, 3 args
}
namespace SP {
float  Fun_c37120();                                           // 0x00c37120: cdecl, no args
}
namespace SP {
typedef void  (__thiscall* FnV0)(void*);
}
namespace SP {
typedef void* (__thiscall* FnP0)(void*);
}
namespace SP {
typedef void* (__thiscall* FnPP)(void*, void*);
}
namespace SP {
typedef void* (__thiscall* FnPStr)(void*, unsigned int);
}
namespace SP {
typedef int   (__thiscall* FnIArg)(void*, unsigned int);
}
namespace SP {
typedef float (__thiscall* FnF0)(void*);
}
namespace SP {
typedef void  (__thiscall* FnV1)(void*, int);
}
namespace SP {
inline void** VT(void* o) { return *reinterpret_cast<void***>(o); }
}
namespace SP {
struct Sub508 { void* vtbl; };
}
namespace SP {
struct HeldBody {
  char    pad0[0x34];
  struct { void* vtbl; } sub34;               // +0x34
  char    pad38[0x718 - 0x38];
  float   pos[3];                             // +0x718
  float   r724[3];                            // +0x724
  float   orient[4];                          // +0x730
};
}
namespace SP {
class cSpace {
 public:
  bool __cdecl Update(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8);
  bool __cdecl UpdateTarget(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8);

  void* Fun_c38b00();                                          // 0x00c38b00: thiscall, returns [this+0x7a8]
  void* Fun_c38b80();                                          // 0x00c38b80: thiscall, returns [this+0x7ac]
  void  Fun_c3dae0(const void* arg);                           // 0x00c3dae0: thiscall, ret 4
  void  Fun_c3daa0(float arg);                                 // 0x00c3daa0: thiscall float, ret 4
  void  Fun_c3be70(const void* arg);                           // 0x00c3be70: thiscall, ret 4

  char        pad0[0x34];                     // +0x00
  void*       subObj34;                       // +0x34  helper object pointer
  char        pad38[0x508 - 0x38];            // +0x38
  Sub508      sub508;                         // +0x508
  char        pad50c[0x624 - 0x50c];          // +0x50c
  unsigned char flag624;                      // +0x624
  char        pad625[0x68c - 0x625];          // +0x625
  void*       heldObject;                     // +0x68c
  char        pad690[0x691 - 0x690];          // +0x690
  unsigned char flag691;                      // +0x691
  char        pad692[0x694 - 0x692];          // +0x692
  float       heldOffset[3];                  // +0x694
  char        pad6a0[0x6b0 - 0x6a0];          // +0x6a0
  unsigned int idx6b0;                        // +0x6b0
  char        pad6b4[0x714 - 0x6b4];          // +0x6b4
  int         i714;                           // +0x714
  float       pos[3];                         // +0x718
  char        pad724[0x730 - 0x724];          // +0x724
  float       orient[4];                      // +0x730
};
}
// ---- items of slice s00dc18e0 end

// ---- items of slice s00dc2720 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sin(double);
extern "C" double cos(double);
extern const float g_ringBasis[7];                            // 0x0169fa08 .. 0x0169fa20
extern const float kRingRadiusNear;                           // 0x0159d59c 20.0
extern const float kRingRadiusB;                              // 0x0159d594 25.0
extern const float kRingRadiusC;                              // 0x0159d598 25.0
extern const float kRingRadiusD;                              // 0x0159d590 25.0
extern const float kRingRadiusE;                              // 0x0159d5e0 25.0
extern const float kRingWeightA;                              // 0x013eb1bc -1.0
extern const float kRingWeightB;                              // 0x0159d5ec -1.0
extern const float kRingWeightC;                              // 0x0159d5e4 -1.0
extern const float kRingField6b4;                             // 0x0159d618 3.5
extern const float kRingField6b8;                             // 0x0159d61c 2.5
#pragma warning(disable: 4100)
namespace SP {
struct Vec3_s00dc_2720 { float x, y, z; };
}
namespace SP {
class cSpatialObject_s00dc_2720;
}
namespace SP {
class cSpatialSub;
}
namespace SP {
class cCombatant_s00dc_2720;
}
namespace SP {
class cCommunity_s00dc_2720;
}
namespace SP {
class RefCounted {
public:
    virtual void AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};
}
namespace SP {
class cCombatant_s00dc_2720 : public RefCounted {
public:
    virtual void v02();
    virtual cSpatialObject_s00dc_2720* GetOwnerNoun();                   // +0x0c
};
}
namespace SP {
class cLocomotion {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual const Vec3_s00dc_2720* GetPosition();                        // +0x2c  0x00c0d6b0
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
    virtual const Vec3_s00dc_2720* GetFacing(Vec3_s00dc_2720* out);                 // +0x5c
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v2a();
virtual void v2b();
virtual void v2c();
virtual void v2d();
virtual void v2e();
virtual void v2f();
virtual void v30();
virtual void v31();
    virtual bool TestGround();                                // +0x48
virtual void v33();
virtual void v34();
virtual void v35();
    virtual bool IsFlying();                                  // +0x58
};
}
namespace SP {
struct cBehaviorTreeData_s00dc_2720 {
    uint32_t pad00[0x1d8 / 4];
    uint32_t mTreeId;                                         // +0x1d8  behaviour-tree fourcc
};
}
namespace SP {
class cSpatialSub {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
    virtual const Vec3_s00dc_2720* GetPosition();                        // +0x2c
};
}
namespace SP {
class cGroup {
public:
virtual void v00();
virtual void v01();
virtual void v02();
    virtual cSpatialObject_s00dc_2720* FindMember(uint32_t key);         // +0x0c
};
}
namespace SP {
class cSpatialObject_s00dc_2720 : public RefCounted {
public:
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual int  GetTypeHash();                               // +0x20  0x00c0...
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
    virtual int  GetRingKey();                                // +0x60
    virtual void v19();
    uint8_t  pad04[0xc0 - 0x04];
    cLocomotion mLoco;                                        // +0xc0 locomotion sub-object
    uint8_t  padc4[0x120 - 0xc4];
    cSpatialSub mSpatial120;                                  // +0x120 spatial sub-object
    uint8_t  pad124[0x135 - 0x124];
    bool     mbValid135;                                      // +0x135 the leader is usable
    uint8_t  pad136[0x5a8 - 0x136];
    cCombatant_s00dc_2720 mCombatant5a8;                                 // +0x5a8 combatant sub-object
    uint8_t  pad5ac[0x624 - 0x5ac];
    bool     mbDirty624;                                      // +0x624 behaviour state changed
    uint8_t  pad625[0x68c - 0x625];
    int      mFamily68c;                                      // +0x68c family / house id
    bool     mbFlag690;                                       // +0x690
    uint8_t  pad691[0x694 - 0x691];
    Vec3_s00dc_2720     mBasis694;                                       // +0x694 ring direction
    uint8_t  pad6a0[0x6b0 - 0x6a0];
    int      mRingIndex6b0;                                   // +0x6b0 index within the ring
    float    mField6b4;                                       // +0x6b4
    float    mField6b8;                                       // +0x6b8
    uint8_t  pad6bc[0x6c8 - 0x6bc];
    void*    mpEnv;                                           // +0x6c8 behaviour environment / tree
    uint8_t  pad6cc[0x714 - 0x6cc];
    int      mState714;                                       // +0x714 tuning / model state
    uint8_t  pad718[0x74c - 0x718];
    bool     mbEnabled74c;                                    // +0x74c behaviour switched on
    uint8_t  pad74d[0xb20 - 0x74d];
    void*    mpSpecies;                                       // +0xb20 species profile
    uint8_t  padb24[0xb34 - 0xb24];
    int      mRankB34;                                        // +0xb34 (== 1 for a follower)
    uint8_t  padb38[0xb4c - 0xb38];
    cBehaviorTreeData_s00dc_2720* mpGameData;                            // +0xb4c behaviour-tree data
    uint8_t  padb50[0xb5e - 0xb50];
    bool     mbDeadB5e;                                       // +0xb5e dead / despawned
    uint8_t  padb5f[4];
    // ---- predicates / lookups (plain members, direct calls in the original) ----
    bool          IsBaby();                                   // 0x00c0b770
    bool          IsEpic();                                   // 0x00c0c0e0
    cCombatant_s00dc_2720*   GetCombatantTarget();                       // 0x00c0ee60
    cGroup*       GetTargetGroup();                           // 0x00c38b00
    // ---- posse-member interface (0x00c3daa0 / 0x00c3be70) ----
    void SetTargetDistance(float distance);                   // 0x00c3daa0
    void SetTargetPosition(const Vec3_s00dc_2720& position);             // 0x00c3be70
};
}
namespace EA {
template <class T>
class AutoRefCount_s00dc_2720 {
public:
    T* mpObj;                                                 // +0x00
    AutoRefCount_s00dc_2720() : mpObj(0) {}
    explicit AutoRefCount_s00dc_2720(T* p) : mpObj(p) { if (mpObj) mpObj->AddRef(); }
    AutoRefCount_s00dc_2720(const AutoRefCount_s00dc_2720& o) : mpObj(o.mpObj) { if (mpObj) mpObj->AddRef(); }
    ~AutoRefCount_s00dc_2720() { if (mpObj) mpObj->Release(); }
    AutoRefCount_s00dc_2720& operator=(const AutoRefCount_s00dc_2720& o) {
        if (mpObj != o.mpObj) {
            T* p = o.mpObj;
            if (p) p->AddRef();
            T* old = mpObj;
            mpObj = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* Get() const { return mpObj; }
};  // namespace EA
}
namespace eastl {
template <class T>
class vector_s00dc_2720 {
public:
    T* mpBegin;                                               // +0x00
    T* mpEnd;                                                 // +0x04
    T* mpCapacity;                                            // +0x08
    vector_s00dc_2720() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    vector_s00dc_2720(T* begin, T* end, T* capacity)
        : mpBegin(begin), mpEnd(end), mpCapacity(capacity) {}
    void push_back(const T& value) {
        if (mpEnd < mpCapacity) {
            *mpEnd = value;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, value);  // 0x00621fc0 (eastl::vector::DoInsertValue)
        }
    }
    void DoInsertValue(T* position, const T& value);          // 0x00aea5d0
    ~vector_s00dc_2720();                                                // 0x00ad92d0
};
}
namespace SP {
class cCommunity_s00dc_2720 {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
virtual void v1b();
virtual void v1c();
virtual void v1d();
virtual void v1e();
virtual void v1f();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
    virtual eastl::vector_s00dc_2720<EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> >* GetMembers();   // +0x90
    cSpatialObject_s00dc_2720* GetLeader();                              // 0x00c00650
};  // namespace SP
}
using SP::Vec3_s00dc_2720;
using SP::cSpatialObject_s00dc_2720;
using SP::cSpatialSub;
using SP::cLocomotion;
using SP::cCombatant_s00dc_2720;
using SP::cGroup;
using SP::cCommunity_s00dc_2720;
extern const Vec3_s00dc_2720  g_originThread;                            // 0x0169f444 (x/y/z)
class cGameNounManager_s00dc_2720 {
public:
    cSpatialObject_s00dc_2720* GetAvatar();                              // 0x00b1fdb0
    cCommunity_s00dc_2720*     GetPlayerTribe();                         // 0x00bfc5f0
    void* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);   // 0x00b21340
};
cGameNounManager_s00dc_2720* NounManager();                              // 0x00b3d300
void operator_delete_array(void* p);                          // 0x00f47380
enum {
    kCreatureAnimalNoun = 0x18eb45e,   // cCreatureAnimal::NOUN_ID
    kUFOFollowTree      = 0x3704748,   // behaviour-tree id already driving the candidate
    kGroupMemberKey     = 0xee9b2232,  // fourcc used by cGroup::FindMember
};
struct RingStateOut {
    float mWeight;                                            // +0x00
    float mRadius;                                            // +0x04
    float mSpacing;                                           // +0x08
    int   mField0C;                                           // +0x0c
    bool  mbFlag10;                                           // +0x10
    Vec3_s00dc_2720  mOrigin;                                            // +0x14
};
struct GameDataVector {
    uint32_t mPad;                                            // +0x00
    EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>* mpBegin;                // +0x04
    EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>* mpEnd;                  // +0x08
};
// ---- items of slice s00dc2720 end

// ---- items of slice s00dc3940 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float k3940_10;                      // 0x013eb1bc
extern const float k4890_3;                       // 0x013eb95c
extern const float k3940_6b4;                     // 0x0159d5b4
extern const float k3940_6b8;                     // 0x0159d5b8
extern const float k3940_out0;                    // 0x0169f444
extern const float k3940_out1;                    // 0x0169f448
extern const float k3940_out2;                    // 0x0169f44c
extern const float k3940_basis[9];                // 0x0169fa0c
extern const float k3c20_basis[9];                // 0x0169fa18
extern const float k3c20_scale;                   // 0x0169fa08
extern const float k3940_angles[5];               // 0x016dc0d4
extern const float k3940_vecs[15];                // 0x016dba24
extern const float k3940_randmul;                 // 0x0147c320
extern const float k3940_randlo;                  // 0x0147c318
extern const float k3940_randhi;                  // 0x01423748
extern const int   k3eb0_lim_a;                   // 0x0159d580
extern const float k3e10_lim_b;                   // 0x01485378
extern const int   k3eb0_lim_c;                   // 0x0159d584
extern const int   k43a0_lim_d;                   // 0x0159d588
extern const float k3f10_near;                    // 0x01469358
extern const float k4460_r;                       // 0x0159d5dc
extern const float k3c20_n;                       // 0x0159d58c
extern const float k40a0_max;                     // 0x0147c300
extern const int   k43a0_tool;                    // 0x0169f754
extern char  g_1601760;                           // 0x01601760 sMathRandom
#define VFN(p, off)     (((void**)*(void**)(p))[(off) / 4])
#define VC0(p, off)     ((int(__thiscall*)(void*))VFN(p, off))(p)
#define VC0V(p, off)    ((void(__thiscall*)(void*))VFN(p, off))(p)
#define VC1(p, off, a)  ((int(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))
#define VCV(p, off, a)  ((void(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))
#define D(p, off) (*(int*)((char*)(p) + (off)))
#define F(p, off) (*(float*)((char*)(p) + (off)))
#define B(p, off) (*(unsigned char*)((char*)(p) + (off)))
struct Vec3f { float x, y, z; };
struct NounVec {
    int** mpBegin;
    int** mpEnd;
    int** mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    void* operator[](int i) const { return (void*)mpBegin[i]; }
};
struct IntVec { uint32_t pad; NounVec mData; };
struct cGameNounManager {
    IntVec* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, uint32_t id);
    IntVec* GetSomething();                       // 0x00ad49b0
};
cGameNounManager* NounManager_s00dc_3940();                  // 0x00b3d300
struct BehaviorStimuli {
    void ClearAll(int a, int b);                  // 0x00bc98f0
    int PlayIdleAnimation(int a, int b);          // 0x00bc96a0
};
struct Stim {
    char pad[8];
    void* p8;                                     // +0x08
    void GetAny();                                // 0x00d997e0
};
struct PFIndex { int GetFileCount(); };           // 0x008e7f80
struct Damage508 { char IsReady(); };             // 0x00bfc600
struct CmdObj {
    void Cmd(int id);                             // 0x00ca80e0
    void SetParam(float v);                       // 0x00c9ee70
    void SetTarget(int a);                        // 0x00ca33b0
    void Finish();                                // 0x00c9ee50
};
struct CheckObj {
    int  IsActive();                              // 0x00c9fee0
    void DoAction();                              // 0x00cacbe0
};
struct FilterObj {
    char Accept(int a);                           // 0x00c004c0
};
struct GroundObj {
    void SetPosition(float* pos);                 // 0x00c3be70
};
void F_00cd7d10();                                 // 0x00cd7d10
void F_00d3d420();                                 // 0x00d3d420
void F_00ad48b0();                                 // 0x00ad48b0
void F_00b1e500();                                 // 0x00b1e500
void F_00ad4930();                                 // 0x00ad4930
void F_00acdff0();                                 // 0x00acdff0
void F_00dc3250();                                 // 0x00dc3250
float* FUN_0059aed0(float* out, const float* m, const float* q);   // 0x0059aed0
void*  FUN_00401010();                                             // 0x00401010
void*  SP_SpaceGameGet();                                          // 0x01002bd0
int    FUN_00c38b00(void* self);                                   // 0x00c38b00
int    FUN_00c38b80(void* self);                                   // 0x00c38b80
void*  FUN_010212a0();                                             // 0x010212a0
char   FUN_01029a10(void* self, int target);                       // 0x01029a10
void   FUN_00c37130(void* self, int a);                            // 0x00c37130
void   FUN_00c3b630(void* self, void* a);                          // 0x00c3b630
void   FUN_00dc3170(int a, int b, float x, float y, float z);      // 0x00dc3170
void   FUN_00b93c60(void* self, int count, void* src);             // 0x00b93c60
struct PlanetModel_s00dc_3940 {
    void ToGround(Vec3f* out);                                     // 0x00b81720
    Vec3f* MakeRandomWorldPosition(Vec3f* out, const Vec3f* p, float a, float b); // 0x00b81780
};
PlanetModel_s00dc_3940* SP_PlanetModel();                                     // 0x00b3d350
struct RandLCG {
    double RandomDoubleUniform();                 // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t n);     // 0x00a68fb0
};
struct SpaceGame { void* GetAvatar(); };                           // 0x00b1fdb0
struct Avatar { void Notify(int id); };                            // 0x00ff8300
struct Empire { char IsHostileToPlayer(); };                       // 0x00c309e0
struct StarManager { Empire* GetEmpireByID(int id); };             // 0x00ba9370
StarManager* SP_StarManager();                                     // 0x00b3d2a0
// ---- items of slice s00dc3940 end

// ---- items of slice s00dc48e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t DAT_015a2560;   // 0x015a2560
extern uint8_t DAT_015a25e8;   // 0x015a25e8
extern uint8_t DAT_01654c10;   // 0x01654c10
extern uint8_t DAT_0169fa30;   // 0x0169fa30
extern uint8_t DAT_0169fa31;   // 0x0169fa31
extern float   DAT_01470f1c;   // 0x01470f1c
extern void* SP_GetCivModeStrategy();            // 0xcf74c0
extern void* GetTriggerMgr();                    // 0xb3d4d0
extern void* SP_GetCurrentGameMode();            // 0xb5b800
extern void  SP_GridHasValidIndex(void* p);      // 0xbc8fa0
#pragma pack(push,1)
#pragma pack(pop)
struct Obj;
typedef void          (__thiscall *VfnRaw)(void);
typedef void          (__thiscall *Vfn0)(void*);
typedef void          (__thiscall *VfnI)(void*, int);
enum VtSlot {
    kVt00 = 0x00 / 4, kVt04 = 0x04 / 4, kVt08 = 0x08 / 4, kVt0C = 0x0c / 4,
    kVt10 = 0x10 / 4, kVt2C = 0x2c / 4, kVt50 = 0x50 / 4, kVt5C = 0x5c / 4,
    kVt60 = 0x60 / 4, kVt64 = 0x64 / 4, kVt6C = 0x6c / 4, kVtB8 = 0xb8 / 4,
    kVtC0 = 0xc0 / 4, kVtE8 = 0xe8 / 4, kVtEC = 0xec / 4
};
struct Vtbl { VfnRaw mSlots[0xf0 / 4]; };
struct Sub_s00dc_48e0 {
    Vtbl* mpVtbl;                 // +0x00
    char  IsNearGoal();           // 0xc42e20  SP::cLocomotiveObject::IsNearGoal
    char  Cbfc600();              // 0xbfc600
    float Cbfc400();              // 0xbfc400
    void* Cc41ec0();              // 0xc41ec0
    void* Cc421f0();              // 0xc421f0
};
struct BehaviorTreeStim {
    void  ClearAll(int a, int b); // 0xbc98f0
    int   Play(int a, int b);     // 0xbc96a0
    void* GetAny();               // 0xd997e0
};
struct BehaviorTree {
    uint8_t         mPad00[8];                                    // +0x000
    BehaviorTreeStim mStimA;                                      // +0x008
    uint8_t         mPadA[0x1d0 - 0x008 - sizeof(BehaviorTreeStim)];
    BehaviorTreeStim mStimB;                                      // +0x1d0
    void Cb660(void* p);                                          // 0xbcb660
};
struct CivMode     { char   IsCivTriggerActive(); };              // 0xcf7a90
struct TriggerMgr {
    uint8_t mPad00[0x28];         // +0x00
    uint8_t mByte28;              // +0x28
    uint8_t mPad29[0x2c - 0x29];
    int     mState2c;             // +0x2c
};
struct StateObj  { uint8_t mPad00[0x4b8]; int mState; };   // +0x4b8
struct OrderInfo { uint8_t mPad00[0x10];  int mKind;  };   // +0x10
struct Obj {
    Vtbl*  mpVtbl;                          // +0x000
    uint8_t mPad004[0x34 - 0x04];           // +0x004
    Sub_s00dc_48e0    mSub34;                          // +0x034
    uint8_t mPad038[0x50 - 0x38];           // +0x038
    int    mField50;                        // +0x050
    uint8_t mPad054[0x5c - 0x54];           // +0x054
    int    mField5c;                        // +0x05C
    uint8_t mPad060[0x108 - 0x60];          // +0x060
    Sub_s00dc_48e0    mSub108;                         // +0x108
    uint8_t mPad10c[0x120 - 0x10c];         // +0x10C
    Sub_s00dc_48e0    mSub120;                         // +0x120
    uint8_t mPad124[0x224 - 0x124];         // +0x124
    float  mF224;                           // +0x224
    uint8_t mPad228[0x2a4 - 0x228];         // +0x228
    uint8_t mByte2a4;                       // +0x2A4
    uint8_t mPad2a5[0x508 - 0x2a5];         // +0x2A5
    Sub_s00dc_48e0    mSub508;                         // +0x508
    uint8_t mPad50c[0xaf0 - 0x50c];         // +0x50C
    Obj*   mpBehaviorTree;                  // +0xAF0
    uint8_t mPadaf4[0xb1c - 0xaf4];         // +0xAF4
    int    mStateB1c;                       // +0xB1C
    uint8_t mPadb20[0xb7c - 0xb20];         // +0xB20
    Obj*   mpObjB7c;                        // +0xB7C
    uint8_t mPadb80[0xb8c - 0xb80];         // +0xB80
    Obj**  mpVecBeginB8c;                   // +0xB8C
    Obj**  mpVecEndB90;                     // +0xB90

    void*  Ca71d0();                        // 0xca71d0
    void   Ca7250(char* msg);               // 0xca7250
    void   Caa900();                        // 0xcaa900
    void*  C9f1c0();                        // 0xc9f1c0
    void   C6c0200();                       // 0x6c0200
    char   C9e960(float* p);                // 0xc9e960  SP::cVehicle::CanOccupyTerrain
    void*  C9fee0();                        // 0xc9fee0
    float* C9e880();                        // 0xc9e880
    void   C9fb40(float x, float y, float z, float a, float b); // 0xc9fb40
    void   Cabe70();                        // 0xcabe70
    float  C9eb80();                        // 0xc9eb80
    float* Cbd9480(float* out);             // 0xbd9480
    int    GetFileCount();                  // 0x8e7f80
};
// ---- items of slice s00dc48e0 end

// @ 0x00dc0040
void FUN_00dc0040(char* self)
{
    byte z = 0;
    float one = g_one;
    *(float*)(self + 0x6b4) = one;
    *(float*)(self + 0x6b8) = one;
    *(byte*)(self + 0x690) = z;
    *(byte*)(self + 0x691) = z;
    _ReadWriteBarrier();
    void* p = *(void**)(self + 0x68c);
    if (p != 0) {
        *(void**)(self + 0x68c) = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    ((Sub*)self)->Be70(self + 0x718);
}

// @ 0x00dc01c0
void FUN_00dc01c0(char* self)
{
    float one = g_one;
    *(float*)(self + 0x6b4) = one;
    *(float*)(self + 0x6b8) = one;
    *(byte*)(self + 0x690) = 0;
    *(byte*)(self + 0x691) = 0;
    _ReadWriteBarrier();
    void* p = *(void**)(self + 0x68c);
    if (p != 0) {
        *(void**)(self + 0x68c) = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    ((Sub*)self)->Be70(self + 0x718);
    (*(void (__thiscall**)(char*, int))((char*)*(void**)(self + 0x508) + 0x50))(self + 0x508, 0);
}

// @ 0x00dc0230
bool FUN_00dc0230(char* self)
{
    if (*(char*)(self + 0x74c) != 0 && *(char*)(*(int*)(self + 0x68c) + 0x74c) != 0) {
        char* a = self + 0x34;
        char* b = (char*)*(int*)(self + 0x68c) + 0x34;
        float* pa = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        float ax = pa[0], ay = pa[1], az = pa[2];
        float* pb = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)b + 0x2c))(b);
        float x1 = pb[0] - ax * 2.0f;
        float y1 = pb[1] - ay * 2.0f;
        float z1 = pb[2] - az * 2.0f;
        float* pa2 = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        Vec3 v;
        v.x = pa2[0] + x1;
        v.y = pa2[1] + y1;
        v.z = pa2[2] + z1;
        ((Sub*)self)->Be70(&v);
        ((Sub*)self)->Daa0(((Sub*)*(void**)(self + 0x68c))->C7120());
        *(byte*)(self + 0x624) = 1;
    }
    if (*(char*)(*(int*)(self + 0x68c) + 0x74c) == 0) {
        char* a = self + 0x34;
        float loc[3];
        float* pv = (float*)(*(void* (__thiscall**)(char*, float*))((char*)*(void**)a + 0x5c))(a, loc);
        float x1 = pv[0] * 100.0f;
        float y1 = pv[1] * 100.0f;
        float z1 = pv[2] * 100.0f;
        float* pa = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
        Vec3 v;
        v.x = pa[0] + x1;
        v.y = pa[1] + y1;
        v.z = pa[2] + z1;
        ((Sub*)self)->Be70(&v);
        ((Sub*)self)->Daa0(((Sub*)*(void**)(self + 0x68c))->C7120());
        *(byte*)(self + 0x624) = 1;
    }
    return true;
}

// @ 0x00dc0410
bool FUN_00dc0410(char* self)
{
    char* inv = (char*)((Sim*)SPGetUFOSimulator())->GetPlayerInventory();
    if (((Sub*)inv)->C8990(1)) return false;
    if (*(void**)(self + 0x68c) == inv) return false;
    void* old = *(void**)(self + 0x68c);
    if (inv != old) {
        if (inv != 0) (*(void (__thiscall**)(void*))(*(void**)inv))(inv);
        *(void**)(self + 0x68c) = inv;
        if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    *(int*)(self + 0x6b0) = (int)g_rng.RandomUint32Uniform(2);
    double f = g_rng.RandomDoubleUniform() * 50.0;
    if (f > 50.0) f = 50.0;
    else if (f < 0.0) f = 0.0;
    float v = (float)f - 25.0f;
    *(float*)(self + 0x694) = g_fA24 * v + g_fA18 * g_47c308;
    *(float*)(self + 0x698) = g_fA28 * v + g_fA1c * g_47c308;
    *(float*)(self + 0x69c) = g_fA2c * v + g_fA20 * g_47c308;
    *(float*)(self + 0x6ac) = RandomSigned(g_473c70);
    return true;
}

// @ 0x00dc0550
bool FUN_00dc0550(char* self)
{
    void* best = GetBestUFOTarget(self, 0, 1);
    if (best == 0) return false;
    void* info = (*(void* (__thiscall**)(void*, unsigned))((char*)*(void**)best + 0x5c))(best, 0xb033b403);
    if (info == 0) return false;
    if (*(void**)(self + 0x68c) == info) return false;
    void* old = *(void**)(self + 0x68c);
    if (info != old) {
        (*(void (__thiscall**)(void*))(*(void**)info))(info);
        *(void**)(self + 0x68c) = info;
        if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    *(int*)(self + 0x6b0) = (int)g_rng.RandomUint32Uniform(2);
    double f = g_rng.RandomDoubleUniform() * 50.0;
    if (f > 50.0) f = 50.0;
    else if (f < 0.0) f = 0.0;
    float v = (float)f - 25.0f;
    *(float*)(self + 0x694) = g_fA24 * v + g_fA18 * g_47c308;
    *(float*)(self + 0x698) = g_fA28 * v + g_fA1c * g_47c308;
    *(float*)(self + 0x69c) = g_fA2c * v + g_fA20 * g_47c308;
    *(float*)(self + 0x6ac) = RandomSigned(g_473c70);
    return true;
}

// @ 0x00dc06a0
bool FUN_00dc06a0(char* self)
{
    char* o = ((Sub*)self)->B00();
    if (o == 0) return false;
    void* info = (*(void* (__thiscall**)(char*, unsigned))((char*)*(void**)o + 0xc))(o, 0xb033b403);
    if (info == 0) return false;
    if ((*(char (__thiscall**)(void*))((char*)*(void**)info + 0x2c))(info) != 0) {
        ((Sub*)self)->B10();
        return false;
    }
    if ((*(char (__thiscall**)(void*))((char*)*(void**)info + 0x2c))(info) != 0) return false;
    void* old = *(void**)(self + 0x68c);
    if (info != old) {
        (*(void (__thiscall**)(void*))(*(void**)info))(info);
        *(void**)(self + 0x68c) = info;
        if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    return true;
}

// @ 0x00dc0720
bool FUN_00dc0720(char* self)
{
    void* p = *(void**)(self + 0x68c);
    if (p != 0) {
        *(void**)(self + 0x68c) = 0;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    return false;
}

// @ 0x00dc0750
bool FUN_00dc0750(char* self, void* a2, void* a3, void* a4, void* a5, void* a6, void* src)
{
    if (src != 0) {
        char* q = *(char**)((char*)src + 4);
        void* info;
        if (q != 0) info = (*(void* (__thiscall**)(char*, unsigned))((char*)*(void**)q + 0x5c))(q, 0xb033b403);
        else info = 0;
        void* old = *(void**)(self + 0x68c);
        if (info != old) {
            if (info != 0) (*(void (__thiscall**)(void*))(*(void**)info))(info);
            *(void**)(self + 0x68c) = info;
            if (old != 0) (*(void (__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        ((Sub*)((char*)*(void**)(self + 0x6c8) + 8))->Bf0(4, 0, g_9d5f8, 0);
    }
    return true;
}

// @ 0x00dc07d0
bool FUN_00dc07d0(char* self, void* a2, void* a3, void* a4, void* a5, Vec3* out)
{
    out->x = g_9d604;
    out->y = g_9d608;
    char* a = self + 0x34;
    float* pa = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)a + 0x2c))(a);
    Vec3 neg;
    neg.x = pa[0] * g_3eb1bc;
    neg.y = pa[1] * g_3eb1bc;
    neg.z = pa[2] * g_3eb1bc;
    Vec3 loc;
    char* m = (char*)PlanetModel(&loc, &neg, g_3eecd8, g_3ec4d0);
    float* r = ((Planet*)m)->MakeRandomWorldPosition();
    loc = *(Vec3*)r;
    ((Sub*)self)->Be70(&loc);
    ((Sub*)self)->Daa0(g_9d614);
    if (*(int*)(self + 0x714) == 5) {
        *(float*)(self + 0x6b4) = g_9d630;
        *(float*)(self + 0x6b8) = g_9d634;
    }
    *(float*)(self + 0x6b4) = g_9d60c;
    bool one = true;
    *(float*)(self + 0x6b8) = g_9d610;
    *(bool*)(self + 0x624) = one;
    return one;
}

// @ 0x00dc08f0
bool FUN_00dc08f0(char* self, void* a2, void* a3, void* a4, void* a5, Vec3* out)
{
    char* o = ((Sub*)self)->B80();
    if (o != 0) {
        char* info = (char*)(*(void* (__thiscall**)(char*, void*))((char*)*(void**)o + 0xc))(o, (void*)0x1186577);
        if (info != 0) {
            float* p = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)info + 0x2c))(info);
            *out = *(Vec3*)p;
            void* r = (*(void* (__thiscall**)(char*))((char*)*(void**)info + 0x2c))(info);
            ((Sub*)self)->Be70(r);
        }
    }
    ((Sub*)self)->Daa0(g_9d628);
    *(float*)(self + 0x6b4) = g_9d638;
    float vb = g_9d63c;
    bool one = true;
    *(bool*)(self + 0x624) = one;
    *(float*)(self + 0x6b8) = vb;
    return one;
}

// @ 0x00dc0980
bool FUN_00dc0980(char* self, void* a2, void* a3, void* a4, void* a5, void* a6, Vec3* pos)
{
    char* o = ((Sub*)self)->B80();
    if (o == 0) return false;
    char* infoF = (char*)(*(void* (__thiscall**)(char*, unsigned))((char*)*(void**)o + 0xc))(o, 0x11c0ba3);
    char* infoH = (char*)(*(void* (__thiscall**)(char*, void*))((char*)*(void**)o + 0xc))(o, (void*)0x1186577);
    char* infoX = (char*)(*(void* (__thiscall**)(char*, void*))((char*)*(void**)o + 0xc))(o, (void*)0x13f94d4);
    if ((*(char (__thiscall**)(char*))((char*)*(void**)o + 0x2c))(o) != 0) return false;
    if (infoF == 0) return false;
    if (infoH == 0) return false;
    if (infoX == 0) return false;
    if (*(char*)(self + 0x74c) == 0) return true;
    unsigned t = (*(unsigned (__thiscall**)(char*))((char*)*(void**)infoF + 0x24))(infoF);
    if (t != 0x114242e6) {
        float* ph = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)infoH + 0x2c))(infoH);
        float dx = ph[0] - pos->x;
        float dy = ph[1] - pos->y;
        float dz = ph[2] - pos->z;
        if (sqrtf(dx*dx + dy*dy + dz*dz) >= g_473c70) {
            pos->x = ph[0];
            pos->y = ph[1];
            pos->z = ph[2];
            void* r = (*(void* (__thiscall**)(char*))((char*)*(void**)infoH + 0x2c))(infoH);
            ((Sub*)self)->Be70(r);
            return true;
        }
    }
    char* u = ((Sub*)self)->B7720();
    if (u != 0) {
        float f = ((Sub2*)u)->F10();
        float* ps = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)(self + 0x34) + 0x2c))(self + 0x34);
        float* pm = (float*)(*(void* (__thiscall**)(char*))((char*)*(void**)infoX + 0x2c))(infoX);
        float dx = pm[0] - ps[0];
        float dy = pm[1] - ps[1];
        float dz = pm[2] - ps[2];
        if (sqrtf(dx*dx + dy*dy + dz*dz) < f) {
            (*(void (__thiscall**)(char*, char*))((char*)*(void**)(self + 0x508) + 0x50))(self + 0x508, infoX);
        }
    }
    return true;
}

// @ 0x00dc18e0
namespace SP {
bool __cdecl cSpace::UpdateTarget(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8)
{
  (void)p2; (void)p3; (void)p5; (void)p7;

  void* held = heldObject;
  if (held == 0)
    return false;

  float local[3];
  Fun_dc00a0(local, p4, this);

  HeldBody* body = static_cast<HeldBody*>(held);
  void* heldSub = &body->sub34;
  void** heldVt = *reinterpret_cast<void***>(heldSub);
  const float kPositionScale = *reinterpret_cast<const float*>(0x014007f4);
  float scalar = reinterpret_cast<FnF0>(heldVt[0x34 / 4])(heldSub);

  local[0] = (local[0] + heldOffset[0] * kPositionScale) * scalar;
  local[1] = (local[1] + heldOffset[1] * kPositionScale) * scalar;
  local[2] = (local[2] + heldOffset[2] * kPositionScale) * scalar;

  void* basis = reinterpret_cast<FnP0>(heldVt[0x30 / 4])(heldSub);
  float rotated[3];
  Fun_59aed0(rotated, local, basis);

  float candidate[3];
  candidate[0] = pos[0] + rotated[0];
  candidate[1] = pos[1] + rotated[1];
  candidate[2] = pos[2] + rotated[2];

  const float kUnsetX = *reinterpret_cast<const float*>(0x0169f444);
  const float kUnsetY = *reinterpret_cast<const float*>(0x0169f448);
  const float kUnsetZ = *reinterpret_cast<const float*>(0x0169f44c);
  const float kOne = *reinterpret_cast<const float*>(0x01485720);
  const bool targetUnset = p6[0] == kUnsetX && p6[1] == kUnsetY && p6[2] == kUnsetZ;

  if (targetUnset) {
    const float dx = candidate[0] - pos[0];
    const float dy = candidate[1] - pos[1];
    const float dz = candidate[2] - pos[2];
    const float distance = (float)sqrt((double)(dz * dz + dy * dy) + (double)(dx * dx));

    if (distance > *reinterpret_cast<const float*>(0x01486110)) {
      const float blend = Fun_c37120();
      Fun_c3be70(candidate);
      Fun_c3daa0(blend);
      flag624 = 1;
      return true;
    }

    flag691 = 1;
    p6[0] = candidate[0];
    p6[1] = candidate[1];
    p6[2] = candidate[2];
  } else {
    flag691 = 1;

    float rate = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f0)) * p8;
    if (rate > kOne)
      rate = kOne;

    const float dirLength = (float)sqrt((double)(candidate[2] * candidate[2] +
                                                candidate[1] * candidate[1]) +
                                        (double)(candidate[0] * candidate[0]));
    float dir[3];
    dir[0] = candidate[0] / dirLength;
    dir[1] = candidate[1] / dirLength;
    dir[2] = candidate[2] / dirLength;

    const float targetLength = (float)sqrt((double)(p6[2] * p6[2] +
                                                    p6[1] * p6[1]) +
                                           (double)(p6[0] * p6[0]));
    const float invTargetLength = kOne / targetLength;
    float normal[3];
    normal[0] = p6[0] * invTargetLength;
    normal[1] = p6[1] * invTargetLength;
    normal[2] = p6[2] * invTargetLength;

    float steer[3];
    Fun_b0fd00(steer, normal, dir, rate);
    p6[0] = steer[0] * targetLength;
    p6[1] = steer[1] * targetLength;
    p6[2] = steer[2] * targetLength;
  }

  void* finalHeld = heldObject;
  HeldBody* finalBody = static_cast<HeldBody*>(finalHeld);
  void* finalSub = &finalBody->sub34;
  void** finalVt = *reinterpret_cast<void***>(finalSub);
  void* extra = reinterpret_cast<FnP0>(finalVt[0x2c / 4])(finalSub);
  const float* extraVec = static_cast<const float*>(extra);
  float combined[3];
  combined[0] = extraVec[0] + p6[0];
  combined[1] = extraVec[1] + p6[1];
  combined[2] = extraVec[2] + p6[2];

  float facing[3];
  Fun_b0fd00(facing, pos, combined, *reinterpret_cast<const float*>(0x013ec4b4));
  Fun_c3dae0(facing);

  float orientRate = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f4)) * p8;
  if (orientRate > kOne)
    orientRate = kOne;

  float slerpResult[4];
  float* quat = Fun_5b2500(slerpResult, orient, finalBody->orient, orientRate);
  orient[0] = quat[0];
  orient[1] = quat[1];
  orient[2] = quat[2];
  orient[3] = quat[3];
  return true;
}
}  // namespace SP

// @ 0x00dc1d70
namespace SP {
bool __cdecl cSpace::Update(int p2, unsigned int p3, int p4, int p5, float* p6, float p7, float p8)
{
  (void)p2; (void)p4; (void)p5;
  const float kEbp = 0.0f;  // unaff_EBP: no visible origin in the Ghidra output.
  const float S0 = *reinterpret_cast<const float*>(0x0169f444);
  const float S1 = *reinterpret_cast<const float*>(0x0169f448);
  const float S2 = *reinterpret_cast<const float*>(0x0169f44c);

  // Early out when no held object.
  if (heldObject == 0) {
    return false;
  }
  if (p6[4] != -1.0f) {
    p6[4] = p6[4] - p8;
    if (p6[4] <= 0.0f) {
      void* c = heldObject;
      if (c != 0) {
        heldObject = 0;
        reinterpret_cast<FnV0>(VT(c)[1])(c);
      }
      void* sub = &sub508;
      reinterpret_cast<FnV0>(VT(sub)[0x38 / 4])(sub);
      return false;
    }
  }

  // Retarget test: if the target is farther than the threshold, drop it.
  if (heldObject != Fun_c38b00()) {
    void* u = Fun_c38b00();
    if (u != 0) {
      void* o = reinterpret_cast<FnPStr>(VT(u)[0xc / 4])(u, 0x01186577);
      if (o != 0) {
        float* pa = static_cast<float*>(reinterpret_cast<FnP0>(VT(o)[0x2c / 4])(o));
        void* m34 = subObj34;
        float* pb = static_cast<float*>(reinterpret_cast<FnP0>(VT(m34)[0x2c / 4])(m34));
        double dd = (double)(pb[1] - pa[1]) * (pb[1] - pa[1]) +
                    ((double)(pb[2] - pa[2]) * (pb[2] - pa[2]) + (double)(pb[0] - pa[0]) * (pb[0] - pa[0]));
        if (*reinterpret_cast<const float*>(0x0159d5c4) < (float)sqrt(dd)) {
          void* c = heldObject;
          if (c != 0) {
            heldObject = 0;
            reinterpret_cast<FnV0>(VT(c)[1])(c);
          }
          void* sub = &sub508;
          reinterpret_cast<FnV0>(VT(sub)[0x38 / 4])(sub);
          int t = Fun_b67740(Fun_c38b00());
          if (t != 0) {
            void* sub2 = reinterpret_cast<char*>(t) + 0x508;
            reinterpret_cast<FnV0>(VT(sub2)[0x38 / 4])(sub2);
          }
          return false;
        }
      }
    }
  }

  // Blend toward the target.
  float W[3] = {0.0f, 0.0f, 0.0f};  // W[0] is uStack_7c; W[1] and W[2] are filled from the stage-2 result.
  float fStack_84, fStack_88, uStack_80, fStack_64, fStack_60, fStack_5c;
  bool bEq = (heldObject == Fun_c38b00());
  fStack_84 = 1.0f;
  if (bEq) {
    uStack_80 = *reinterpret_cast<const float*>(0x0159d5cc);
    fStack_84 = *reinterpret_cast<const float*>(0x0159d5c8);
  } else {
    uStack_80 = 1.0f;
  }
  unsigned int idx = idx6b0 % 5;
  const float* row = reinterpret_cast<const float*>(0x016dba24) + idx * 3;
  double ang = (double)(*reinterpret_cast<const float*>(0x0169fa04) * fStack_84 * p8) * 0.5;
  float sn = (float)sin(ang);
  float cs = (float)cos(ang);
  float rv[3] = {row[0] * sn, row[1] * sn, row[2] * sn};
  float buf24[4];
  float* pv = Fun_59aed0(buf24, heldOffset, rv);
  heldOffset[0] = pv[0];
  heldOffset[1] = pv[1];
  heldOffset[2] = pv[2];

  // Length of the held object's position vector, minus planet radius and 1.0.
  HeldBody* hb = static_cast<HeldBody*>(heldObject);
  fStack_88 = (float)sqrt((double)(hb->pos[0] * hb->pos[0] + hb->pos[1] * hb->pos[1]) +
                          (double)(hb->pos[2] * hb->pos[2]));
  cPlanetModel_s00dc_18e0* pl = PlanetModel();
  float rad = pl->GetRadiusAt(hb->pos);
  fStack_84 = (float)((double)fStack_88 - rad - 1.0);
  void* O = hb->sub34.vtbl;
  float t34 = reinterpret_cast<FnF0>(VT(O)[0x34 / 4])(O);
  float cand = t34 * *reinterpret_cast<const float*>(0x0159d5bc) * uStack_80;
  fStack_88 = cand;
  if (!(cand <= fStack_84)) {
    fStack_88 = fStack_84;
  }

  float V1[3] = {heldOffset[0] * fStack_88, heldOffset[1] * fStack_88, heldOffset[2] * fStack_88};
  void* O2 = hb->sub34.vtbl;
  void* u30 = reinterpret_cast<FnP0>(VT(O2)[0x30 / 4])(O2);
  float* v2 = Fun_59aed0(buf24, V1, u30);
  W[1] = v2[0];
  W[2] = v2[1];

  void* O3 = hb->sub34.vtbl;
  float buf18[6];
  float* v6c = static_cast<float*>(reinterpret_cast<FnPP>(VT(O3)[0x6c / 4])(O3, buf18));
  float V3x = (v6c[0] + v6c[3]) * 0.5f;
  float V3y = (v6c[4] + v6c[1]) * 0.5f;
  float V3z = (v6c[5] + v6c[2]) * 0.5f;

  // Steering test: take the main branch if the target changed, or if the held object is within range.
  float dx = hb->pos[0] - pos[0];
  float dy = hb->pos[1] - pos[1];
  float dz = hb->pos[2] - pos[2];
  float dist = (float)sqrt((double)(dz * dz + dy * dy) + (double)(dx * dx));
  bool take = (p6[0] != S0) || (p6[1] != S1) || (p6[2] != S2) || (dist <= kEbp + 3.0f);

  if (take) {
    flag691 = 1;
    if (p6[0] == S0 && p6[1] == S1 && p6[2] == S2) {
      p6[0] = W[0];
      p6[1] = W[1];
      p6[2] = W[2];
    } else {
      float f60 = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f0)) * p7;
      float rate1 = (f60 <= 1.0f) ? f60 : 1.0f;
      fStack_64 = (float)sqrt((double)(W[0] * W[0] + (W[1] * W[1] + W[2] * W[2])));
      float inv = 1.0f / fStack_64;
      float f84 = p6[2];
      W[0] = inv * W[0];
      float f88 = p6[1];
      W[1] = W[1] * inv;
      W[2] = W[2] * inv;
      float f58 = p6[0];
      fStack_5c = 1.0f / (float)sqrt((double)(f58 * f58 + (f88 * f88 + f84 * f84)));
      float N[3] = {f58 * fStack_5c, f88 * fStack_5c, f84 * fStack_5c};
      float buf54[4];
      float* r = Fun_b0fd00(buf54, N, W, rate1);
      float len = fStack_64;
      p6[0] = len * r[0];
      p6[1] = len * r[1];
      p6[2] = len * r[2];
    }

    float k2 = *reinterpret_cast<const float*>(0x0159fe28) * p7;
    float rate2 = (k2 <= 1.0f) ? k2 : 1.0f;
    float N2[3] = {V3x + p6[0], V3y + p6[1], V3z + p6[2]};
    float buf28[4];
    Fun_b0fd00(buf28, pos, N2, rate2);
    Fun_c3dae0(buf28);

    float k3 = (p6[3] + *reinterpret_cast<const float*>(0x0159d5f4)) * p7;
    float rate3 = (k3 <= 1.0f) ? k3 : 1.0f;
    void* O4 = hb->sub34.vtbl;
    void* u2 = reinterpret_cast<FnP0>(VT(O4)[0x30 / 4])(O4);
    float buf54b[4];
    float* b = Fun_59aed0(buf54b, row, u2);

    float f58b = p6[0];
    float f88b = p6[1];
    float f84b = p6[2];
    float c0 = (f88b * -1.0f) * b[2] - (f84b * -1.0f) * b[1];
    float c1 = b[1] * (f58b * -1.0f) - (f88b * -1.0f) * b[0];
    float c2 = (f84b * -1.0f) * b[0] - b[2] * (f58b * -1.0f);
    float f34 = 1.0f / (float)sqrt((double)(c0 * c0 + (c2 * c2 + c1 * c1)) + 1e-08);
    float F[3] = {f34 * c0, c2 * f34, c1 * f34};
    float fa = 1.0f / (float)sqrt((double)(f58b * f58b + (f88b * f88b + f84b * f84b)) + 1e-08);
    float N3[3] = {fa * f58b, fa * f88b, fa * f84b};
    float Q[4];
    QuaternionFromFacingAndUp(Q, F, N3);
    float* pq = Fun_5b2500(N3, orient, Q, rate3);
    float q0 = pq[0], q1 = pq[1], q2 = pq[2], q3 = pq[3];
    orient[0] = q0;
    orient[1] = q1;
    orient[2] = q2;
    orient[3] = q3;
    const float* vv = hb->r724;
    if (*reinterpret_cast<const float*>(0x0159fe24) <
        (float)sqrt((double)(vv[0] * vv[0] + vv[1] * vv[1]) + (double)(vv[2] * vv[2]))) {
      flag691 = 0;
      p6[0] = S0;
      p6[1] = S1;
      p6[2] = S2;
    }
  } else {
    W[2] = V3z + W[2];
    W[1] = V3y + W[1];
    W[0] = V3x + W[0];
    Fun_c3daa0((float)sqrt((double)(W[0] * W[0] + (W[1] * W[1] + W[2] * W[2]))));
    Fun_c3be70(W);
    flag624 = 1;
  }

  // Target selection and final dispatch.
  int target = GetBestUFOTarget_s00dc_18e0(this, (p3 >> 12) & 1u, 0);
  if (i714 == 2 && target == 0) {
    target = Fun_102c460(this);
  }
  unsigned char* u80b = reinterpret_cast<unsigned char*>(&uStack_80);
  if (u80b[3] != 0 && target == 0) {
    void* p = reinterpret_cast<cSpace*>(heldObject)->Fun_c38b80();
    if (p != 0) {
      int r = reinterpret_cast<FnIArg>(VT(p)[0xc / 4])(p, 0xee9b2232u);
      if (r != 0) {
        target = Fun_cc15b0(r, 0);
      }
    }
  }
  void* sub = &sub508;
  reinterpret_cast<FnV1>(VT(sub)[0x50 / 4])(sub, target);
  return true;
}
}  // namespace SP

// @ 0x00dc32d0
bool FUN_00dc32d0(cSpatialObject_s00dc_2720* self, void* a2, void* a3, void* a4, void* a5, RingStateOut* out)
{
    out->mRadius = 0.0f;
    out->mWeight = kRingWeightA;
    out->mField0C = 0;
    out->mbFlag10 = false;
    out->mOrigin = g_originThread;

    switch (self->mState714) {
    case 1:
        out->mRadius = kRingRadiusNear;
        out->mWeight = kRingWeightA;
        break;
    case 2:
    case 11:
        out->mRadius = kRingRadiusB;
        out->mWeight = kRingWeightA;
        break;
    case 3:
        out->mRadius = kRingRadiusE;
        out->mWeight = kRingWeightC;
        break;
    case 6: {
        cGroup* group = self->GetTargetGroup();
        out->mWeight = (group != 0 && group->FindMember(kGroupMemberKey) != 0)
                     ? kRingWeightA : kRingWeightB;
        out->mRadius = kRingRadiusD;
        break;
    }
    case 8:
        out->mRadius = kRingRadiusC;
        out->mWeight = kRingWeightA;
        break;
    default:
        break;
    }

    // ---- gather the entries of the same family and state -----------------
    eastl::vector_s00dc_2720<EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720> > entries;
    GameDataVector* gameData = (GameDataVector*)NounManager()->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ad48b0, (void*)0x00b1e500,
        (void*)0x018ebadc);
    for (EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>* it = gameData->mpBegin; it != gameData->mpEnd; ++it) {
        cSpatialObject_s00dc_2720* entry = it->Get();
        if (entry->mFamily68c != self->mFamily68c)
            continue;
        if (entry->mState714 != self->mState714)
            continue;
        entries.push_back(EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>(entry));
    }

    // ---- spread them over the ring --------------------------------------
    if (entries.mpBegin != entries.mpEnd) {
        int count = (int)(entries.mpEnd - entries.mpBegin);
        float step = 1.0f / (float)count;
        int index = 0;
        for (EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>* it = entries.mpBegin; it != entries.mpEnd; ++it, ++index) {
            cSpatialObject_s00dc_2720* entry = it->Get();
            entry->mRingIndex6b0 = index;

            float angle = ((float)entry->mRingIndex6b0 * step) * g_ringBasis[0];
            angle *= 0.5f;
            float sn = (float)sin((double)angle);
            float cs = (float)cos((double)angle);

            float u = sn * g_ringBasis[1];                    // 0x0169fa0c
            float v = sn * g_ringBasis[2];                    // 0x0169fa10
            float w = sn * g_ringBasis[3];                    // 0x0169fa14
            float kA = g_ringBasis[4];                        // 0x0169fa18
            float kB = g_ringBasis[5];                        // 0x0169fa1c
            float kC = g_ringBasis[6];                        // 0x0169fa20

            entry->mBasis694.x = 2.0f * ((v * u - cs * w) * kB + (cs * v + w * u) * kC)
                               + (1.0f - 2.0f * (v * v + w * w)) * kA;
            entry->mBasis694.y = 2.0f * ((w * v - cs * u) * kC + (cs * w + v * u) * kA)
                               + (1.0f - 2.0f * (u * u + w * w)) * kB;
            entry->mBasis694.z = 2.0f * ((cs * u + w * v) * kB + (w * u - cs * v) * kA)
                               + (1.0f - 2.0f * (u * u + v * v)) * kC;
        }
    }

    out->mSpacing = 0.0f;
    self->mField6b4 = kRingField6b4;
    self->mbDirty624 = 1;
    self->mbFlag690 = 1;
    self->mField6b8 = kRingField6b8;

    for (EA::AutoRefCount_s00dc_2720<cSpatialObject_s00dc_2720>* it = entries.mpBegin; it != entries.mpEnd; ++it) {
        if (it->Get() != 0)
            it->Get()->Release();
    }
    if (entries.mpBegin != 0) {
        if (*((int*)entries.mpBegin - 1) != 0)
            operator_delete_array(entries.mpBegin);
    }
    return true;
}

// @ 0x00dc3940
char __cdecl FUN_00dc3940(void* owner, int, int, int, void* self, float* out)
{
    F(self, 0x10) = k3940_10;
    cGameNounManager* nm = NounManager_s00dc_3940();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                   (void*)&F_00ad48b0, (void*)&F_00b1e500, 0x18ebadc);
    NounVec& v = vec->mData;
    int** p = v.mpBegin;
    int** end = v.mpEnd;
    int i = 0;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (D(o, 0x68c) != D(self, 0x68c) || D(o, 0x714) != D(self, 0x714))
            continue;
        D(o, 0x6b0) = i;
        unsigned u = (unsigned)D(o, 0x6b0) % 5u;
        ++i;
        float a = k3940_angles[u] * 0.5f;
        float s = (float)sin((double)a);
        float c = (float)cos((double)a);
        float q[4];
        q[0] = k3940_vecs[u * 3 + 0] * s;
        q[1] = k3940_vecs[u * 3 + 1] * s;
        q[2] = k3940_vecs[u * 3 + 2] * s;
        q[3] = c;
        Vec3f tmp;
        float* r = FUN_0059aed0(&tmp.x, k3940_basis, q);
        F(o, 0x694) = r[0];
        F(o, 0x698) = r[1];
        F(o, 0x69c) = r[2];
    }
    out[0] = k3940_out0;
    out[1] = k3940_out1;
    out[2] = k3940_out2;
    double r = ((RandLCG*)&g_1601760)->RandomDoubleUniform() * k3940_randmul;
    r -= k3940_randhi;
    if (k3940_randhi <= r)
        r = k3940_randhi;
    else if (r < k3940_randlo)
        r = k3940_randlo;
    out[3] = (float)r;
    F(owner, 0x6b4) = k3940_6b4;
    F(owner, 0x6b8) = k3940_6b8;
    B(owner, 0x690) = 1;
    return 1;
}

// @ 0x00dc3af0
char __cdecl FUN_00dc3af0(void* self, int, int, int, int, float* v, int, float dt)
{
    if (((BehaviorStimuli*)((char*)D(self, 0x6c8) + 8))->PlayIdleAnimation(8, 0) == 0) {
        v[1] -= dt;
        if (0.0f < v[1])
            return 1;
        return 0;
    }
    if (((BehaviorStimuli*)((char*)D(self, 0x6c8) + 8))->PlayIdleAnimation(0x20, 0) == 0)
        return 1;
    v[0] -= dt;
    if (0.0f < v[0])
        return 1;
    void* o = FUN_00401010();
    if (((char(__thiscall*)(void*, void*, int))VFN(o, 0x1c))(
            o, (void*)((char*)self + 0x780), 0) == 0)
        return 1;
    void* av = ((SpaceGame*)SP_SpaceGameGet())->GetAvatar();
    ((Avatar*)av)->Notify(0x638207a);
    IntVec* vec = NounManager_s00dc_3940()->GetSomething();
    int** p = vec->mData.mpBegin;
    int** end = vec->mData.mpEnd;
    for (; p != end; ++p) {
        void* e = (void*)*p;
        if (D(e, 0x6c8) == 0)
            continue;
        BehaviorStimuli* bs = (BehaviorStimuli*)((char*)D(e, 0x6c8) + 8);
        if (bs->PlayIdleAnimation(8, 0) == 0)
            continue;
        if (VC0(e, 0x4c) != VC0(self, 0x4c))
            continue;
        bs->ClearAll(8, 0);
        FUN_00c37130(e, 1);
    }
    return 1;
}

// @ 0x00dc3c20
char __cdecl FUN_00dc3c20(void* self, int, int, int, int, void* src)
{
    if (src == 0)
        return 1;
    void* t;
    if (D(src, 8) != 0)
        t = (void*)VC1((void*)D(src, 8), 0xc, 0xee9b2232);
    else
        t = 0;
    FUN_00c3b630(self, t);
    void* target = (void*)FUN_00c38b00(self);
    int count;
    void* anchor;
    if (target == 0) {
        anchor = 0;
    } else {
        anchor = (void*)VC1(target, 0xc, 0xee9b2232);
    }
    count = D(anchor, 0x224);
    float* pos = (float*)VC0((char*)anchor + 0x120, 0x2c);
    float inv = 1.0f / (float)sqrt((double)(pos[2] * pos[2] + (pos[1] * pos[1] + pos[0] * pos[0])));
    float nx = pos[0] * inv;
    float ny = pos[1] * inv;
    float nz = pos[2] * inv;
    cGameNounManager* nm = NounManager_s00dc_3940();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                   (void*)&F_00ad48b0, (void*)&F_00b1e500, 0x18ebadc);
    NounVec& v = vec->mData;
    int** p = v.mpBegin;
    int** end = v.mpEnd;
    int i = 0;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (FUN_00c38b00(o) != FUN_00c38b00(self))
            continue;
        D(o, 0x6b0) = i++;
        float a = ((float)D(o, 0x6b0) / (float)count) * k3c20_scale;
        a *= 0.5f;
        float s = (float)sin((double)a);
        float c = (float)cos((double)a);
        float q[4];
        q[0] = nx * s;
        q[1] = ny * s;
        q[2] = nz * s;
        q[3] = c;
        Vec3f tmp;
        float* r = FUN_0059aed0(&tmp.x, k3c20_basis, q);
        F(o, 0x6a0) = k3c20_n * r[0];
        F(o, 0x6a4) = k3c20_n * r[1];
        F(o, 0x6a8) = k3c20_n * r[2];
    }
    return 1;
}

// @ 0x00dc3e10
double __cdecl FUN_00dc3e10(int, int, int, int, Stim* stim, char* out)
{
    cGameNounManager* nm = NounManager_s00dc_3940();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                        (void*)&F_00acdff0, (void*)&F_00b1e500, 0x18c43e8);
    NounVec& v = vec->mData;
    int** p = v.mpBegin;
    int** end = v.mpEnd;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (D(o, 0x224) < k3eb0_lim_a &&
            (((FilterObj*)o)->Accept(0) || F(o, 0x220) > k3e10_lim_b)) {
            if (stim != 0)
                stim->GetAny();
            stim->p8 = o;
            *out = 1;
            return 1.0;
        }
    }
    return 0.0;
}

// @ 0x00dc3eb0
double __cdecl FUN_00dc3eb0()
{
    cGameNounManager* nm = NounManager_s00dc_3940();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                        (void*)&F_00ad4930, (void*)&F_00b1e500, 0x2dd8c42);
    NounVec& v = vec->mData;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        void* o = v[i];
        if (D(o, 0x658) == 4)
            return 0.0;
    }
    return 1.0;
}

// @ 0x00dc3f10
double __cdecl FUN_00dc3f10(void* self, int, int, int, Stim* stim, char* out)
{
    cGameNounManager* nm = NounManager_s00dc_3940();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                        (void*)&F_00ad4930, (void*)&F_00b1e500, 0x2dd8c42);
    NounVec& v = vec->mData;
    int count = v.size();
    void* found = 0;
    float best = k3f10_near;
    int i = 0;
    for (; i < count; ++i) {
        void* o = v[i];
        if (D(o, 0x658) != 4)
            continue;
        float* a = (float*)VC0((char*)self + 0x34, 0x2c);
        float* b = (float*)VC0((char*)o + 0x34, 0x2c);
        float dx = b[0] - a[0];
        float dy = b[1] - a[1];
        float dz = b[2] - a[2];
        float dist = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
        if (best < dist)
            continue;
        IntVec* v2 = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                           (void*)&F_00ad48b0, (void*)&F_00b1e500, 0x18ebadc);
        NounVec& v2d = v2->mData;
        int n2 = v2d.size();
        int j = 0;
        for (; j < n2; ++j) {
            void* other = v2d[j];
            if (other == self)
                continue;
            if (FUN_00c38b80(other) == (int)o)
                break;
        }
        if (j < n2)
            continue;
        found = o;
        best = dist;
    }
    if (found != 0) {
        if (stim != 0)
            stim->GetAny();
        stim->p8 = found;
        *out = 1;
        return 1.0;
    }
    return 0.0;
}

// @ 0x00dc40a0
double __cdecl FUN_00dc40a0(void* self, int, int, int, Stim* stim, char* out)
{
    if (FUN_00c38b80(self) != 0)
        return 0.0;
    cGameNounManager* nm = NounManager_s00dc_3940();
    IntVec* list = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                         (void*)&F_00acdff0, (void*)&F_00b1e500, 0x18c43e8);
    int n = (int)(list->mData.mpEnd - list->mData.mpBegin);
    void* buf[1];
    FUN_00b93c60(buf, n, (char*)list + 0x10);
    float* a = (float*)VC0((char*)self + 0x34, 0x2c);
    FUN_00dc3170((int)buf, 0, a[0], a[1], a[2]);
    void* pick = 0;
    void* active = FUN_010212a0();
    char hostile = FUN_01029a10((void*)VC1(self, 0x4c, (int)active), 0);
    int** p = list->mData.mpBegin;
    int** end = list->mData.mpEnd;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (hostile != 0) {
            float f = F(o, 0x74c);
            if (f == (float)VC0(self, 0x4c) && 100.0f <= F(o, 0x748))
                break;
        }
        if (D(o, 0x228) < k3eb0_lim_c) {
            pick = (char*)o + 0x120;
            break;
        }
    }
    float bestd = k40a0_max;
    if (pick != 0) {
        float* q = (float*)VC0(pick, 0x2c);
        float* b = (float*)VC0((char*)self + 0x34, 0x2c);
        float dx = b[0] - q[0];
        float dy = b[1] - q[1];
        float dz = b[2] - q[2];
        bestd = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
    }
    IntVec* v2 = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                       (void*)&F_00dc3250, (void*)&F_00b1e500, 0x4e3fab5);
    void* nearest = pick;
    p = v2->mData.mpBegin;
    end = v2->mData.mpEnd;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (D(o, 0x638) >= k43a0_lim_d)
            continue;
        char* sub = (char*)o + 0x34;
        float* q = (float*)VC0(sub, 0x2c);
        float* b = (float*)VC0((char*)self + 0x34, 0x2c);
        float dx = b[0] - q[0];
        float dy = b[1] - q[1];
        float dz = b[2] - q[2];
        float d = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
        if (d < bestd) {
            nearest = sub;
            bestd = d;
        }
    }
    if (nearest != 0) {
        if (stim != 0)
            stim->GetAny();
        stim->p8 = (void*)VC1(nearest, 0xb8, 0x17f243b);
        *out = 1;
    }
    return 0.0;
}

// @ 0x00dc43a0
double __cdecl FUN_00dc43a0(void* self, int, int, int, Stim* stim, char* out)
{
    Empire* e = SP_StarManager()->GetEmpireByID(VC0(self, 0x4c));
    if (e != 0 && e->IsHostileToPlayer()) {
        cGameNounManager* nm = NounManager_s00dc_3940();
        IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                       (void*)&F_00dc3250, (void*)&F_00b1e500, 0x4e3fab5);
        NounVec& v = vec->mData;
        int** p = v.mpBegin;
        int** end = v.mpEnd;
        for (; p != end; ++p) {
            void* o = (void*)*p;
            if (D(o, 0x64c) != k43a0_tool || D(o, 0x638) >= k43a0_lim_d)
                continue;
            if (stim != 0)
                stim->GetAny();
            stim->p8 = (void*)VC1(o, 0xc, 0x17f243b);
            *out = 1;
            return 1.0;
        }
    }
    return 0.0;
}

// @ 0x00dc4460
char __cdecl FUN_00dc4460(void* self)
{
    if (B(self, 0x74c) != 0) {
        PlanetModel_s00dc_3940* pm = SP_PlanetModel();
        Vec3f pos;
        pm->ToGround(&pos);
        if (D(self, 0x714) == 6) {
            cGameNounManager* nm = NounManager_s00dc_3940();
            IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                           (void*)&F_00acdff0, (void*)&F_00b1e500, 0x18c43e8);
            NounVec& v = vec->mData;
            if (v.mpBegin != v.mpEnd) {
                uint32_t idx = ((RandLCG*)&g_1601760)->RandomUint32Uniform((uint32_t)v.size());
                void* o = v[idx];
                Vec3f tmp;
                Vec3f* r = pm->MakeRandomWorldPosition(&tmp, (const Vec3f*)VC0((char*)o + 0x120, 0x2c), 0.0f, k4460_r);
                pos = *r;
            }
        }
        ((GroundObj*)self)->SetPosition(&pos.x);
        B(self, 0x624) = 1;
    }
    VCV((char*)self + 0x508, 0x50, 0);
    return 1;
}

// @ 0x00dc4670
double __cdecl FUN_00dc4670(void* self)
{
    return ((PFIndex*)((char*)self + 0x508))->GetFileCount() == 2 ? 1.0 : 0.0;
}

// @ 0x00dc4690
double __cdecl FUN_00dc4690(void* self)
{
    return ((Damage508*)((char*)self + 0x508))->IsReady() ? 1.0 : 0.0;
}

// @ 0x00dc46b0
double __cdecl FUN_00dc46b0(void* self)
{
    return (B(self, 0x2a4) & 2) != 0 ? 1.0 : 0.0;
}

// @ 0x00dc46d0
char __cdecl FUN_00dc46d0(void* self)
{
    ((BehaviorStimuli*)((char*)D(self, 0xaf0) + 8))->ClearAll(1, 0);
    VC0V((char*)self + 0x34, 0xec);
    VCV((char*)self + 0x508, 0x50, 0);
    return 0;
}

// @ 0x00dc4710
void __cdecl FUN_00dc4710(void* self)
{
    ((CmdObj*)self)->SetParam(0.0f);
}

// @ 0x00dc47b0
void __cdecl FUN_00dc47b0(void* self)
{
    ((CmdObj*)self)->Cmd(0x16);
    ((CmdObj*)self)->Cmd(0x17);
}

// @ 0x00dc47d0
void __cdecl FUN_00dc47d0(void* self)
{
    ((CmdObj*)self)->Cmd(0x13);
}

// @ 0x00dc47e0
char __cdecl FUN_00dc47e0(int, int, int, int, int, float* out)
{
    if (out != 0)
        *out = 0.0f;
    return 1;
}

// @ 0x00dc4800
double __cdecl FUN_00dc4800(void* self)
{
    return B(self, 0xbcc) != 0 ? 1.0 : 0.0;
}

// @ 0x00dc4820
void __cdecl FUN_00dc4820(void* self)
{
    VCV((char*)self + 0x508, 0x50, 0);
    ((void(__thiscall*)(void*, float, int))VFN((char*)self + 0x34, 0xc4))((char*)self + 0x34, 0.0f, 0);
    ((CmdObj*)self)->SetTarget(VC0((char*)self + 0x34, 0x2c));
    ((CmdObj*)self)->Finish();
}

// @ 0x00dc4870
char __cdecl FUN_00dc4870(int, int, int, int, int, float* out)
{
    if (out != 0)
        *out = 3.0f;
    return 1;
}

// @ 0x00dc4890
char __cdecl FUN_00dc4890(void* self, int, int, int, int, float* out, int, float delta)
{
    if (((CheckObj*)self)->IsActive() == 0)
        return 0;
    if ((D(self, 0x2a4) & 4) != 0) {
        ((CheckObj*)self)->DoAction();
        return 1;
    }
    if ((D(self, 0x2a4) & 8) == 0)
        return 0;
    float v = *out + delta;
    float lim = k4890_3;
    *out = v;
    if (lim > v)
        return 1;
    return 0;
}

// @ 0x00dc48e0
char FUN_00dc48e0(Obj* self)
{
    return self->mSub34.IsNearGoal() == 0;
}

// @ 0x00dc4900
char FUN_00dc4900(void* a0, void* a1, void* a2, void* a3, void* a4, int* pOut)
{
    if (pOut)
        *pOut = 1;
    return 1;
}

// @ 0x00dc4920
char FUN_00dc4920(Obj* self)
{
    return self->mSub508.Cbfc600() != 0;
}

// @ 0x00dc4940
char FUN_00dc4940(Obj* self)
{
    OrderInfo* info = (OrderInfo*)self->Ca71d0();
    if (info->mKind == 0xc) {
        ((VfnI)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, 0);
        ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
        return 1;
    }
    self->Ca7250((char*)"(51) MTP: bad orders");
    self->Caa900();
    return 0;
}

// @ 0x00dc4990
char FUN_00dc4990(Obj* self)
{
    CivMode* mode = (CivMode*)SP_GetCivModeStrategy();
    if (mode->IsCivTriggerActive())
        return 1;
    self->Caa900();
    return 0;
}

// @ 0x00dc49b0
float FUN_00dc49b0(Obj* self)
{
    StateObj* o = (StateObj*)self->C9f1c0();
    if (o->mState == 3)
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc49d0
void FUN_00dc49d0(Obj* self)
{
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
}

// @ 0x00dc49f0
char FUN_00dc49f0(Obj* self)
{
    self->C6c0200();
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
    return 1;
}

// @ 0x00dc4a10
char FUN_00dc4a10(void* a0, void* a1, void* a2, void* a3, void* a4, float* pOut)
{
    if (pOut)
        *pOut = DAT_01470f1c;
    return 1;
}

// @ 0x00dc4a30
void FUN_00dc4a30(Obj* self)
{
    BehaviorTree* bt = (BehaviorTree*)self->mpBehaviorTree;
    bt->mStimA.ClearAll(0x10000, 0);
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
}

// @ 0x00dc4ab0
float FUN_00dc4ab0(void* a0, void* a1, void* a2, uint32_t a3)
{
    if (a3 & 0x400)
        return 0.0f;
    return 1.0f;
}

// @ 0x00dc4ae0
char FUN_00dc4ae0(Obj* self)
{
    BehaviorTree* bt = (BehaviorTree*)self->mpBehaviorTree;
    return bt->mStimA.Play(0x8000, 0) != 0;
}

// @ 0x00dc4b00
float FUN_00dc4b00(void)
{
    TriggerMgr* t = (TriggerMgr*)GetTriggerMgr();
    if (t->mState2c == 2 && t->mByte28 == 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00dc4b20
char FUN_00dc4b20(Obj* self)
{
    ((Vfn0)self->mSub34.mpVtbl->mSlots[kVtEC])(&self->mSub34);
    ((VfnI)self->mSub508.mpVtbl->mSlots[kVt50])(&self->mSub508, 0);
    return 1;
}

// @ 0x00dc4b50
char FUN_00dc4b50(void)
{
    TriggerMgr* t = (TriggerMgr*)GetTriggerMgr();
    if (t->mState2c == 2 && t->mByte28 == 0)
        return 1;
    return 0;
}

// @ 0x00dc4b70
void FUN_00dc4b70(Obj* self)
{
    void* mode = SP_GetCurrentGameMode();
    if (mode != &DAT_01654c10) {
        if (DAT_0169fa31 == 0) {
            SP_GridHasValidIndex(&DAT_015a2560);
            DAT_0169fa31 = 1;
        }
        ((BehaviorTree*)self->mpBehaviorTree)->Cb660(&DAT_015a2560);
    } else {
        if (DAT_0169fa30 == 0) {
            SP_GridHasValidIndex(&DAT_015a25e8);
            DAT_0169fa30 = 1;
        }
        ((BehaviorTree*)self->mpBehaviorTree)->Cb660(&DAT_015a25e8);
    }
}
