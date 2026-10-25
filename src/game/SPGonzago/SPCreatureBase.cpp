// src/game/SPGonzago/SPCreatureBase.cpp -- migrated from slice(s) s00c22010, s00c1f580, s00c1c9f0, s00c18b40, s00c17350, s00c15310, s00c13340, s00c0eae0, s00c0acd0, s01335000, s00c1d640, s00c1aad0, s00c19b60, s00c104d0, s00c0fa70, s00c0ddb0, s00c0ce80, s00c0bd70 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// s00c19b60's items define the slices' own placement new(size_t, void*); s00c0acd0 adds <algorithm>, which reaches
// <new> through <memory>/<xmemory> (C2084).  Same hand guard as SPGraphicsModelManager.cpp (rewrite.py placement_new_guard).
#define __PLACEMENT_NEW_INLINE
#include "game/types.h"
#include "SP/cCreatureLocomotion.h"

// unnamed retail callees and globals (address in the comment)
extern float  gF_150c8b8, gF_150c8b4, gF_150c8cc, gF_1485720, gF_146a32c, gF_146a330;
extern void*  g_16c7aa4;
extern int    g_15716d8[];
#include <math.h>
#include "SP/cSPCreatureBase.h"
#include "SP/cSPTimer.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"
#include <stddef.h>
#include <algorithm>
#include "SP/cGameData.h"
#include "SP/cSpatialObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cBehaviorTreeData.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cInteractionTarget.h"
#define __PLACEMENT_NEW_INLINE   // the slices' own placement new/delete win over <new>'s (rewrite.py)
#include <new>
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cInteractionAgent.h"
#include "SP/cSpeciesArchetype.h"
#include "SP/cVarListSerializer.h"
inline void operator delete(void*, void*) {}   // placement delete (<new>'s is skipped, rewrite.py)

// ---- items of slice s00c0bd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl SP_GetCurrentGameMode();                 // 0xb5b800
void* __cdecl FUN_00401090();                          // 0x401090
void* __cdecl FUN_004df420();                          // 0x4df420
void  __cdecl FUN_00ef1930(void*, float);              // 0xef1930
int   __cdecl FUN_00ebfd50(int, int);                  // 0xebfd50
bool  __cdecl FUN_00c0b1c0(void*, void*, int);         // 0xc0b1c0
bool  __cdecl FUN_00c0b220(void*, void*);              // 0xc0b220
extern float  gF_150c8b8, gF_150c8b4, gF_150c8cc, gF_1485720, gF_146a32c, gF_146a330;
extern void*  g_16c7aa4;
extern int    g_15716d8[];
struct C {
  // simple accessors
  bool __thiscall Pred70(int x);
  bool __thiscall Preda0(int x);
  float __thiscall GetA();
  float __thiscall GetB();
  float __thiscall Get574();
  bool __thiscall Flag388();
  bool __thiscall Flag389();
  uint32_t __thiscall FlagF();
  void __thiscall SetE84(void* p);
  float __thiscall Speed1(char b);
  int  __thiscall FindIndex(int key);
  void __thiscall CallFind13();
  void __thiscall CallFind27();
  void __thiscall IsDefaultSpecies_();
  C*   __thiscall CopyRec(void* src);
  C*   __thiscall QuatHalf(float a);
  int  __thiscall RelationIndex(int idx, char b);
  __declspec(noinline) int __thiscall Cdb0();
  void __thiscall C200(float f);
  int  __thiscall C0bd70(int x);
  void __thiscall C0bee0(int a, int b);
  void __thiscall C0bf10(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k,char l);
  void __thiscall C0c250_();
  void __thiscall C0c630(char b,int* p3,int* p4,int* p5);
  void __thiscall C0c4b0(float a);
  void __thiscall C0ccc0(float f);
};
struct CCommunityStub { void __thiscall func60h(int,int); };
// ---- items of slice s00c0bd70 end

// ---- items of slice s00c0ce80 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct F_a02bf0 { void  __thiscall f(int, int); };        // 0x00a02bf0
struct F_a062a0 { void  __thiscall f(int, int); };        // 0x00a062a0
struct F_a06250 { void  __thiscall f(int); };             // 0x00a06250
struct F_a05270 { void  __thiscall Release(); };          // 0x00a05270
struct F_c88670 { void  __thiscall f(float*); };           // 0x00c88670
#define G32(a)  (*(uint32_t*)(a))
#define GF(a)   (*(float*)(a))
struct CCB {
    float __thiscall ce80(int, int);
    void  __thiscall cf50();
    float __thiscall cfa0(int, char);
    void  __thiscall cff0(int);
    int   __thiscall d050(float);
    void  __thiscall d0c0(uint32_t, char);
    void  __thiscall d1e0(int);
    void  __thiscall d200(int, int);
    void  __thiscall d240();
    float* __thiscall d310(float*);
    void  __thiscall d340(int);
    void  __thiscall UpdateHunger(float);
    int   __thiscall d560(int, float, float);
    void  __thiscall d660(float*);
    void  __thiscall d860(float*);
    void  __thiscall d950(char);
    void  __thiscall d970(float*);
    void  __thiscall d9b0();
    int   __thiscall dac0();
    int   __thiscall db10();
    int   __thiscall db60();
    void  __thiscall dd40(float*);
    void  __thiscall dd70(float*, float);
};
// ---- items of slice s00c0ce80 end

// ---- items of slice s00c0ddb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_009ff6f0(void*, void*);   // 0x009ff6f0
void* __cdecl FUN_0067cb20();                // 0x0067cb20
void  __cdecl FUN_011e07ef(void*);           // 0x011e07ef
struct F_58     { void  __thiscall f(float*); };      // 0x00c886d0 cCommunity::func58h
struct F_a02b40 { char  __thiscall f(int); };         // 0x00a02b40
struct F_c04750 { void* __thiscall f(); };            // 0x00c04750
struct F_d9b0   { void  __thiscall f(); };            // 0x00c0d9b0 (slice 117)
struct F_sw     { void __thiscall Ctor(int, int); unsigned long long __thiscall GetElapsedTime(); }; // 0x168db70
struct CCM {
    void  __thiscall ddb0(float*);
    char  __thiscall de30();
    void  __thiscall de60(int, int);
    char  __thiscall dee0(int, int*, char);
    void* __thiscall dfb0(int);
    void* __thiscall dfd0(int);
    char  __thiscall e000(int, int);
    void* __thiscall e040();
    bool  __thiscall e070(int);
    bool  __thiscall e0c0(int);
    char  __thiscall e120(int);
    char  __thiscall e170(int);
    char  __thiscall e2c0(int);
    void* __thiscall e370();
    float __thiscall e3a0();
    char  __thiscall e3d0();
    char  __thiscall e420();
    float __thiscall e480();
    float __thiscall e4f0();
    void* __thiscall e580();
    void  __thiscall e5f0(float);
    void  __thiscall e640(int);
    int   __thiscall e660();
    int   __thiscall e680(int);
    int   __thiscall e6a0();
    char  __thiscall e8d0(int, int);
};
// ---- items of slice s00c0ddb0 end

// ---- items of slice s00c0fa70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl FUN_0093aa70(void*, void*, int, int);  // 0x0093aa70 WriteUint32
void  __cdecl FUN_0093a780(void*, void*, int, int);  // 0x0093a780 ReadInt32
void  __cdecl FUN_0093ac80(void*);                   // 0x0093ac80 ReadBool
void  __cdecl FUN_0093a9a0(void*, void*, int);       // 0x0093a9a0 operator<<
void  __cdecl FUN_00c0b030(void*, void*);            // 0x00c0b030
void  __cdecl FUN_00bca810(int, int, void*, float, void*, int); // 0x00bca810
void* __cdecl FUN_0067de30();                        // 0x0067de30 SP::PropertyManager
void* __cdecl FUN_00f473a0(int, const char*, int, int, int, int); // 0x00f473a0 operator_new
void  __cdecl FUN_00c10050(uint32_t, int, int, int, char); // 0x00c10050
void  __cdecl FUN_00c10230(int, int, int, int);      // 0x00c10230
struct F_a047d0 { void  __thiscall f(int); };        // 0x00a047d0
struct F_f9b0   { char* __thiscall f(int, void*); }; // 0x00c0f9b0
// One binding slot of the cAnimatable binding array (0x24 bytes).
struct AnimBinding {
    uint32_t id;        // +0x00
    int32_t  maskBit;   // +0x04  bit index into the lookup mask (0 = empty slot)
    uint32_t f08;       // +0x08
    uint32_t f0c;       // +0x0c
    uint32_t f10;       // +0x10
    float    weight;    // +0x14
    char     flags;     // +0x18
    int32_t  handle;    // +0x1c
    void*    target;    // +0x20
};
struct CAN {
    char         _pad0[0xb48];
    void*        playCtx;    // +0xb48  animation play context (thiscall receiver)
    char         _pad2[8];
    void*        animCtx;    // +0xb54  animation subsystem context
    char         _pad1[0xe40 - 0xb58];
    AnimBinding* bindBegin;  // +0xe40
    AnimBinding* bindEnd;    // +0xe44
    void* __thiscall fa70(uint32_t, uint32_t*);
    void  __thiscall fae0(int);
    void  __thiscall fb40(int);
    void  __thiscall fb80(int, int);
    __declspec(noinline) void* __thiscall fe30(void*);
};
// Binding-cleanup receiver reached through CAN::animCtx at +0x184.
struct CANCtx {
    char  _pad0[0x17c];
    void* remapTable;   // +0x17c
    char  _pad1[4];
    void* bindingDst;   // +0x184  -> F_a01f10 receiver
};
// Play context at CAN+0xb48: starts a named animation.
struct AnimPlayCtx {
    void __thiscall Play(int, int, void*, float, void*, int);   // 0x00bca810
};
// One animation-remap descriptor (0x2bc bytes) with a duration/weight at +0x10c.
struct AnimSlotSrc {
    char  _pad0[0x10c];
    float weight;       // +0x10c
};
// Pointer chain walked by FUN_00c10050 from its object argument.
struct AnimParamObj {   // the caller's animation-object argument
    char  _pad0[0xfbc];
    void* sub;          // +0xfbc
};
struct AnimFbcObj {     // *(AnimParamObj+0xfbc)
    char  _pad0[0x2c0];
    void* sub;          // +0x2c0
};
struct Anim2c0Obj {     // *(AnimFbcObj+0x2c0)
    char  _pad0[8];
    void* sub;          // +0x08
};
struct Anim08Obj {      // *(Anim2c0Obj+0x08)
    char  _pad0[0x64];
    void* finder;       // +0x64  object with the +0xc lookup method
};
// ---- items of slice s00c0fa70 end

// ---- items of slice s00c104d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kPi;     // 0x0157174c
extern float gTwoPi;        // 0x0168d960 (dynamic-initialized)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};
inline Quaternion AxisAngle(const Vector3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quaternion(axis.x * s, axis.y * s, axis.z * s, c);
}
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
inline float SmoothStep(float v)
{
    v = Clamp(v, 0.0f, 1.0f);
    return (3.0f - v * 2.0f) * v * v;
}
inline Vector3 NormalizeSafe(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.LengthSq() + 1e-8f);
    return v * inv;
}
inline Vector3 Reject(const Vector3& v, const Vector3& n)
{
    float d = v.Dot(n);
    return v - n * d;
}
Vector3 RotateVector(const Vector3& v, const Quaternion& q);                  // 0x0059aed0
float SignedAngle(const Vector3& a, const Vector3& b, const Vector3& axis);   // 0x0069b760
struct cPlanetModel {
    static cPlanetModel* Get();                       // 0x00b3d350
    Vector3 SurfaceNormal(const Vector3& position);   // 0x00b7e3b0
};
static inline float WrapAngleMod(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        return x - gTwoPi;
    if (x < -kPi)
        return x + gTwoPi;
    return x;
}
// ---- items of slice s00c104d0 end

// ---- items of slice s00c19b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_CooldownThreshold;                         // 0x015716d4
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0
struct Vector3_s00c1_9b60 { float x, y, z; };
struct RefObj {
    virtual int AddRef();       // 0x00
    virtual int Release();      // 0x04
};
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p);                                                  // 0x00572660 (ret 4)
    __forceinline AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    __forceinline ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
typedef AutoRefCount<RefObj> ObjRef;
struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
    ObjRef    mValue;
};
struct ListAnchor {
    ListNode* mpNext;
    ListNode* mpPrev;
};
struct CBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsProtected();                 // 0x2c
    uint8_t pad[0x4];
    void FUN_00c19940(int a);                   // 0x00c19940 (ret 4)
    uint8_t pad8[0xe84 - 8];
    uint8_t* mpOverride;                        // +0xe84
};
struct CLoco {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3_s00c1_9b60* GetVector();         // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsLocomotive();                // 0x58
    void FUN_00c41d60(const Vector3_s00c1_9b60* v);        // 0x00c41d60 (ret 4)
    void FUN_00c446d0(const Vector3_s00c1_9b60* v, int a); // 0x00c446d0 (ret 8)
};
struct CTypeObj { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                  virtual void v10(); virtual void v14(); virtual void v18();
                  virtual int GetType(); };     // 0x1c
struct CAgent {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual CTypeObj* GetTypeObj();             // 0x20
};
struct CManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void Post(uint32_t id, void* data, const Vector3_s00c1_9b60* v);   // 0x60
};
CManager* FUN_00b3d240();                                    // 0x00b3d240 (cdecl)
struct StateObj { uint8_t pad[0x2c]; int mState; };
StateObj* FUN_00b3d4d0();                                    // 0x00b3d4d0 (cdecl)
void* StarManager();                                         // 0x00b3d2a0 (cdecl)
bool FUN_00ba6650(uint32_t id);                              // 0x00ba6650 (cdecl)
uint32_t GetCurrentGameMode();                               // 0x00b5b800 (cdecl)
int FUN_00ac80d0(CBase* b, uint32_t id);                     // 0x00ac80d0 (cdecl)
void Vector3_Normalize(Vector3_s00c1_9b60* out, const Vector3_s00c1_9b60* in);     // 0x00436ce0 (cdecl)
RefObj* FUN_00c11690(uint32_t id, CBase* b, void* attacker); // 0x00c11690 (cdecl)
float FUN_00c0db80(float damage, CBase* b);                  // 0x00c0db80 (cdecl)
float FUN_00c161f0(float damage, CBase* b);                  // 0x00c161f0 (cdecl)
float FUN_00c16340(float damage, CBase* b);                  // 0x00c16340 (cdecl)
float FUN_00c0dcb0(float damage, CBase* b);                  // 0x00c0dcb0 (cdecl)
struct Profile {
    uint8_t  pad[0x648];
    int      mCount648;
    uint8_t  pad64c[0x660 - 0x64c];
    uint32_t mCount660;
    uint32_t mCount664;
    uint32_t mCount668;
};
class cCreatureCombatant {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64();

    uint32_t pad04;             // (the vptr is 8 bytes wide: cGonzagoTimer alignment)
    uint32_t mFlags8;           // +0x08 (bit 9 tested)
    uint8_t  pad0c[0x578 - 0xc];
    Profile* mpProfile;         // +0x578
    uint8_t  pad57c[0x8dc - 0x57c];
    uint8_t* mpOverride;        // +0x8dc (byte +0x388)
    uint8_t  pad8e0[0x9d8 - 0x8e0];
    uint32_t mCooldown;         // +0x9d8
    ListAnchor mEffects;        // +0x9dc

    int  GetDamageState();                                                        // 0x008e7f80
    void TakeHit(float damage, uint32_t pid, int type, const Vector3_s00c1_9b60& dir, void* attacker);  // 0x00bfcdd0

    CBase*  Base()  { return (CBase*)((char*)this - 0x5a8); }
    CLoco*  Loco()  { return (CLoco*)((char*)this - 0x4e8); }
    CAgent* Agent() { return (CAgent*)((char*)this - 0x550); }

    void TakeDamage(float damage, uint32_t attackerPID, int damageType, const Vector3_s00c1_9b60& dir, void* attacker);   // 0x00c1a3c0
};
static __forceinline bool GetBit(uint32_t v, int n) { return ((v >> n) & 1) != 0; }
static __forceinline void PushEffect(ListAnchor* list, RefObj* obj)
{
    ObjRef tmp(obj);
    ListNode* n = (ListNode*)operator new(sizeof(ListNode), "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    ::new ((void*)&n->mValue) ObjRef(tmp);
    n->mpNext = (ListNode*)list;
    n->mpPrev = list->mpPrev;
    list->mpPrev->mpNext = n;
    list->mpPrev = n;
}
// ---- items of slice s00c19b60 end

// ---- items of slice s00c1aad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kLeapMargin;                                     // 0x01582fd8 (3.0)
extern const float kLeapSpeedDefault;                               // 0x01582fc0 (10.0)
struct Vector3_s00c1_aad0 { float x, y, z; };
void operator_delete__(void* p);                                    // 0x00f47380 (cdecl)
extern const Vector3_s00c1_aad0 kZeroVec;                                      // 0x0168d910
struct cLocomotionRequest {
    char* mpBegin;
    uint32_t pad[0x73 / 4];
    cLocomotionRequest();                                           // 0x00ac9850
    cLocomotionRequest(const Vector3_s00c1_aad0* pos, float a, float b);       // 0x00ad29d0 (ret 0xc)
    __forceinline ~cLocomotionRequest()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};
class Body {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const Vector3_s00c1_aad0* GetPos();                                // 0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22();
    virtual const Vector3_s00c1_aad0* GetForward(Vector3_s00c1_aad0* out);                // 0x5c
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual const float* GetBounds(float* out);                     // 0x6c (6 floats: min, max)
    virtual void s28();
    virtual float GetRadius();                                      // 0x74
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void s50(); virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void Submit(const cLocomotionRequest& req);             // 0xdc
    const Vector3_s00c1_aad0* GetVelocity();                                   // 0x00d20610 (lea eax,[ecx+0x1c8])
    void FUN_00c446d0(const Vector3_s00c1_aad0* v, bool flag);                 // 0x00c446d0 (ret 8)
};
struct SpeciesData {
    char pad0[0x548];
    float mLeapRangeAir;       // +0x548
    char pad54c[4];
    float mLeapRange;          // +0x550
    char pad554[0x610 - 0x554];
    uint32_t m610;             // +0x610
    char pad614[8];
    uint32_t m61c;             // +0x61c
    char pad620[0x698 - 0x620];
    uint32_t m698;             // +0x698
};
class PlanetModel {
public:
    float FUN_00b7e490();                                           // 0x00b7e490 (float in st0)
    float GetRadiusAt(const Vector3_s00c1_aad0* pos);                          // 0x00b7ef70 (ret 4)
    float FUN_00b82310(Vector3_s00c1_aad0* p);                                 // 0x00b82310 (ret 4)
};
PlanetModel* GetPlanetModel();                                      // 0x00b3d350
Vector3_s00c1_aad0* normalized_safe(Vector3_s00c1_aad0* out, const Vector3_s00c1_aad0* in);          // 0x00449c20 (cdecl, sret-style: out first, returns out)
class IQueryTarget {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void* Query(uint32_t id);                               // 0x5c
};
class cSPCreatureBase {
public:
    uint32_t vptr;
    char pad04[0xbc];
    Body mBody;                      // +0xc0
    char padc4[0x110 - 0xc4];
    uint32_t mFlags;                 // +0x110
    char pad114[0x137 - 0x114];
    bool mbLeaping;                  // +0x137
    char pad138[0x2b0 - 0x138];
    int mState;                      // +0x2b0
    char pad2b4[0xb20 - 0x2b4];
    SpeciesData* mpSpecies;          // +0xb20
    char padb24[0xbb0 - 0xb24];
    bool mbBB0;                      // +0xbb0
    char padbb1[0xe7c - 0xbb1];
    IQueryTarget* mpTargetHolder;    // +0xe7c

    float FUN_00c0ce80(int a, int b);                               // 0x00c0ce80 (ret 8)
    void FUN_00c15dc0(float f);                                     // 0x00c15dc0 (ret 4)
    void FUN_00c18b40(int arg);                                     // 0x00c18b40 (ret 4)
    void InterruptAnimation(uint32_t id, int a, int b);             // 0x00c12310 (ret 0xc)
    void FUN_00c1b020(int arg);
};
struct TargetCreature {
    char pad[0xc0];
    Body mBody;
};
// ---- items of slice s00c1aad0 end

// ---- items of slice s00c1d640 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gChargeScale;                                              // 0x01572058 (10.0)
extern float gBoundScale;                                               // 0x01572054 (1.5)
typedef unsigned int uint;
struct UIntVector {
    uint* mpBegin;
    uint* mpEnd;
    uint* mpCapacity;
    uint mAllocator[2];
    void DoInsertValue(uint* position, const uint& value);              // 0x004558a0 (ret 8)
    void push_back(const uint& v)
    {
        if (mpEnd < mpCapacity) {
            uint* p = mpEnd++;
            if (p)
                *p = v;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
    ~UIntVector()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};
struct AbilityMask {
    uint w[3];
    bool test(uint id) const
    {
        if (id >= 0x58)
            return false;
        return (w[id >> 5] & (1u << (id & 0x1f))) != 0;
    }
};
struct Ability {
    char pad0[8];
    uint id;                    // +0x08
    int mKind;                  // +0x0c
    char pad10[0x2c];
    float f3c;                  // +0x3c
    char pad40[0x44];
    float f84;                  // +0x84
    char pad88[0x14];
    float f9c;                  // +0x9c
    char pada0[8];
    float fa8;                  // +0xa8
    char padac[0x48];
    float ff4;                  // +0xf4
    char padf8[8];
    float f100_pad;
    float f104;                 // +0x104  (cost)
    char pad108[0xc];
    unsigned char mbBusy;       // +0x114
    char pad115[0xb];
    int m120;                   // +0x120
    float GetBound(bool upper); // 0x004d3d70 (ret 4)
};
struct Entry { float f0; float f4; float f8; float fc; };               // 16-byte per-ability state
struct TypeObj {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual uint GetType();                                      // slot 8 (+0x20)
};
struct TypeHolder {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual TypeObj* Get();                                             // slot 3 (+0xc)
};
struct Body_s00c1_d640 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const void* GetPos();                                       // slot 11 (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void s27(); virtual void s28();
    virtual float GetRadius();                                          // slot 29 (+0x74)
    const void* GetBodyPos();                                           // 0x00c42de0
};
float DistanceBetweenBodies(const void* posA, float radiusA, const void* posB, float radiusB, bool clamp0);  // 0x00d99a60
struct Creature {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual Creature* Query(uint id);                                   // slot 23 (+0x5c)
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33();
    virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38();
    virtual void s39(); virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
    virtual uint GetAbilityCount();                                     // slot 44 (+0xb0)
    virtual Ability* GetAbility(uint index);                            // slot 45 (+0xb4)
    char pad04[0xbc];
    Body_s00c1_d640 mBody;                                                         // +0xc0 (secondary base with vptr)
    char padc4[0xa94];
    uint mFlags;                                                        // +0xb58
    char padb5c[0x54];
    unsigned char mbNoBonus;                                            // +0xbb0
    char padbb1[0x77];
    Entry* mpEntries;                                                   // +0xc28
    char padc2c[0x22c];
    float mEnergy;                                                      // +0xe58
    char pade5c[0x20];
    TypeHolder* mpTypeHolder;                                           // +0xe7c
    char pade80[0xc];
    uint mActiveAbility;                                                // +0xe8c
    char pade90[0x7e0];
    uint mCooldownCount;                                                // +0x1670

    bool IsUpper() const { return (mFlags >> 9) & 1; }
    float F00c0ce80(int a, int b);                                      // 0x00c0ce80 (ret 8)
    uint ChooseAbility(AbilityMask* mask, Creature* target, float dist, bool flag);   // 0x00c1de20
};
float GetScale(int zero, Creature* c);                                  // 0x00d38a30 (cdecl)
const uint kCombatantTypeId = 0x018eb45e;
// ---- items of slice s00c1d640 end

// ---- items of slice s01335000 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0133_5000; 
}
typedef eastl::string8_s0133_5000 string8_s0133_5000;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0133_5000&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
bool Read_00572810(ISerializerReadStream* pStream, void* pData);  // 0x00572810
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);  // 0x00ac8750
}
namespace Simulator {
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);  // 0x00ac87c0
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);  // 0x00ae3430
}
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);  // 0x00ae3470
}
namespace Simulator {
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);  // 0x00aff840
}
namespace Simulator {
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);  // 0x00b02540
}
namespace Simulator {
bool Read_00c143c0(ISerializerReadStream* pStream, void* pData);  // 0x00c143c0
}
namespace Simulator {
bool Read_00c1b8c0(ISerializerReadStream* pStream, void* pData);  // 0x00c1b8c0
}
namespace Simulator {
bool Read_00c21260(ISerializerReadStream* pStream, void* pData);  // 0x00c21260
}
namespace Simulator {
bool Read_00c7e9f0(ISerializerReadStream* pStream, void* pData);  // 0x00c7e9f0
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);  // 0x00572840
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);  // 0x00ac8780
}
namespace Simulator {
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac87f0
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);  // 0x00ac88f0
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3450
}
namespace Simulator {
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);  // 0x00ae3490
}
namespace Simulator {
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);  // 0x00aff870
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);  // 0x00bca960
}
namespace Simulator {
bool Write_00c0fba0(ISerializerWriteStream* pStream, void* pData);  // 0x00c0fba0
}
namespace Simulator {
bool Write_00c143e0(ISerializerWriteStream* pStream, void* pData);  // 0x00c143e0
}
namespace Simulator {
bool Write_00c15f60(ISerializerWriteStream* pStream, void* pData);  // 0x00c15f60
}
namespace Simulator {
bool Write_00cd44e0(ISerializerWriteStream* pStream, void* pData);  // 0x00cd44e0
}
namespace Simulator {
void ReadText_00692fd0(const string8_s0133_5000& text, void* pData);  // 0x00692fd0
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0133_5000& text, void* pData);  // 0x00692ff0
}
namespace Simulator {
void ReadText_00693090(const string8_s0133_5000& text, void* pData);  // 0x00693090
}
namespace Simulator {
void ReadText_006930b0(const string8_s0133_5000& text, void* pData);  // 0x006930b0
}
namespace Simulator {
void ReadText_00693150(const string8_s0133_5000& text, void* pData);  // 0x00693150
}
namespace Simulator {
void ReadText_00694c80(const string8_s0133_5000& text, void* pData);  // 0x00694c80
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0133_5000& text, void* pData);  // 0x00c2e4e0
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);  // 0x00692fb0
}
namespace Simulator {
void WriteText_00694c10(char* pBuffer, void* pData);  // 0x00694c10
}
namespace Simulator {
void WriteText_00694ec0(char* pBuffer, void* pData);  // 0x00694ec0
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);  // 0x00694ee0
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);  // 0x00694f00
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);  // 0x00694fa0
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);  // 0x00694fc0
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);  // 0x00695080
}
namespace Simulator {
bool Validate_00ae3310();  // 0x00ae3310
}
namespace Simulator {
bool Validate_00b1fbf0();  // 0x00b1fbf0
}
namespace Simulator {
bool Validate_00b6f550();  // 0x00b6f550
}
namespace Simulator {
bool Validate_00c0fc10();  // 0x00c0fc10
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);  // 0x0057cde0
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);  // 0x0057ce00
}
namespace Simulator {
bool ToXml_00595a70(void* pData, const char* pName, int depth);  // 0x00595a70
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);  // 0x00675ca0
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);  // 0x00ac8050
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);  // 0x00acbb80
}
namespace Simulator {
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);  // 0x00acbbc0
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);  // 0x00ae5720
}
namespace Simulator {
bool ToXml_00c19b60(void* pData, const char* pName, int depth);  // 0x00c19b60
}
namespace Simulator {
bool ToXml_00ca8710(void* pData, const char* pName, int depth);  // 0x00ca8710
}
namespace Simulator {
struct AttrStorage { char data[sizeof(Attribute)]; };
}
namespace Simulator {
AttrStorage cCreatureBase_sAttributes[35];   // 0x01571798
}
// ---- items of slice s01335000 end

// ---- items of slice s00c0acd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_146a32c;         // FLT_MAX
extern float g_150c8e4, g_150c8e8, g_150c8ec, g_150c8f0;
extern float g_150c8f4, g_150c8f8, g_150c8fc;
extern float g_150c888, g_150c88c;
extern float g_1687a00, g_1687a04, g_1687a0c, g_1687a10, g_1687a14;
extern float g_1687a2c, g_1687a30, g_169e288;
extern int   g_168d900;
extern int   g_168d9bc, g_168da00, g_168da44, g_168da88, g_168dacc, g_168db10;
extern "C" float __fastcall FUN_00bfc490(void*);
typedef unsigned char uchar;
typedef unsigned long long uint64;
extern uchar g_168db6c;
struct AllocRec { char pad[0x40]; };
extern AllocRec g_168d998;
namespace EA {
namespace Random {
class RandomLinearCongruential_s00c0_acd0 {
 public:
  unsigned int RandomUint32Uniform(unsigned int);  // 0x00a68fb0 (EA::Random::RandomLinearCongruential::RandomUint32Uniform)
  float RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
#define GRAND ((EA::Random::RandomLinearCongruential_s00c0_acd0*)0x1601760)
bool __cdecl SP_GetPropertyAsUint32Array(unsigned int prop, unsigned int arg,
                                         int* count, int** data);
int  __cdecl SP_GetCurrentGameMode_s00c0_acd0();
struct AgentOrderManager {
  void __thiscall Tick(float);
  void __thiscall Activate(int, int, void*, float, void*, void*);
};
struct ModifiersCtorHelper {
  void* __thiscall Exist(AllocRec*);
};
void* __cdecl operator new(size_t, const char*, int, int, int, int);
bool __cdecl WriteUint32(void* stream, const void* data, int count, int flags);
bool __cdecl WriteUint64(void* stream, const void* data, int count, int flags);
bool __cdecl ReadUint64(void* stream, void* data, int count, int flags);
bool __cdecl ReadInt32(void* stream, void* data, int count, int flags);
bool __cdecl ReadBool(void* stream, void* data);
void __cdecl StreamWriteBool(void* stream, const void* data, int count);
namespace Simulator {
struct SpeciesData_s00c0_acd0 {
  char pad0[0x58c];
  float mAge;                               // +0x58c
  char pad1[0x608 - 0x590];
  unsigned int m608;
  unsigned int m60c;
};
}
namespace Simulator {
struct cCreatureBase {
  char pad000[0xbd];
  bool mb_bd;                               // +0xbd

  char pad0be[0x110 - 0xbe];
  unsigned int mFlags;                      // +0x110

  char pad114[0x135 - 0x114];
  bool mb_135;                              // +0x135
  char pad136[1];
  bool mb_137;                              // +0x137

  char pad138[0x2b0 - 0x138];
  int mState;                               // +0x2b0

  char pad2b4[0xb20 - 0x2b4];
  SpeciesData_s00c0_acd0* mpSpecies;                   // +0xb20
  char padb24[4];
  float mPosX;                              // +0xb28
  float mPosY;                              // +0xb2c
  float mPosZ;                              // +0xb30
  int m_b34;                                // +0xb34

  char padb38[0xb48 - 0xb38];
  AgentOrderManager* mpOrders;              // +0xb48

  char padb4c[0xb54 - 0xb4c];
  void* mpAnimCreature;                     // +0xb54
  unsigned int mGeneralFlags;               // +0xb58
  char padb5c[0xb5e - 0xb5c];
  bool mbDead;                              // +0xb5e
  char padb5f[1];
  bool mbUpdateInteractionEffect;           // +0xb60
  char padb61[0xb63 - 0xb61];
  bool mb_b63;                              // +0xb63
  char padb64[0xb67 - 0xb64];
  bool mbCasted;                            // +0xb67
  char padb68[0xb70 - 0xb68];
  int mAnimTargetCounter;                   // +0xb70

  char padb74[0xb80 - 0xb74];
  float m_b80;                              // +0xb80
  char padb84[0xb88 - 0xb84];
  int m_b88;                                // +0xb88
  int m_b8c;                                // +0xb8c

  char padb90[0xbb8 - 0xb90];
  float m_bB8;                              // +0xbb8
  float m_bBC;                              // +0xbbc

  char padbc0[0xcc4 - 0xbc0];
  unsigned int mLastInteractionEffect;      // +0xcc4

  char padcc8[0xe84 - 0xcc8];
  void* mp_e84;                             // +0xe84

  char pade88[0xeac - 0xe88];
  int m_eac;                                // +0xeac

  char padeb0[0xf80 - 0xeb0];
  int m_f80;                                // +0xf80

  char padf84[0x1624 - 0xf84];
  void* mp_1624;                            // +0x1624

  char pad1628[0x1670 - 0x1628];
  unsigned int m_1670;                      // +0x1670
  void* mp_1674;                            // +0x1674

  char pad1678[0x1698 - 0x1678];
  void* mp_1698;                            // +0x1698
  float m_169c;                             // +0x169c

  void Update(unsigned int);
  void SetLastInteractionEffect(unsigned int);
  bool ForgetUpdateInteractionEffect();
  void func90h();
  bool IsHungry() const;
  bool IsTired() const;
  bool IsSick() const;
  bool CanBeAttacked(void*) const;
  bool ShouldFlee(void*) const;
  bool ShouldFight(void*) const;
  bool IsIdle(void*) const;
  float GetSpeedScalar() const;
  bool NeedsFood() const;
  void InitOrders();
  int  QueryInterface(unsigned int);
  void SetTimeFromGlobal();
  bool HasAnyCooldown() const;
  bool HasOtherCooldown() const;
  bool IsBusy(void*) const;
  bool IsAttacking(void*) const;
  bool IsStunned(void*) const;
  bool IsDoingAction(void*) const;
  int  CompareTimer(cCreatureBase*);
  int  Query(unsigned int);
  bool CheckTargetA(void*);
  bool CheckTargetB(void*);
  bool CheckTargetC(void*);
  bool CheckTargetD(void*);
  int  TimerDelta(cCreatureBase*);
  void ClampHunger(float);
  void SetHunger(float);
  void ResetHunger();
  void TickCooldowns();
};
}
typedef Simulator::cCreatureBase CB;
typedef Simulator::SpeciesData_s00c0_acd0 SpeciesData_s00c0_acd0;
struct TuningObj {
  void* __thiscall GetAt(unsigned int);
};
struct F_abf740 { int __thiscall f(unsigned int); };
struct F_cee250 { int __thiscall f(unsigned int); };
struct F_c41d00 { int __thiscall f(unsigned int); };
struct F_ac0320 { int __thiscall f(unsigned int); };
struct F_b18460 { int __thiscall f(unsigned int); };
struct F_bfc380 { int __thiscall f(unsigned int); };
struct F_c7d050 { int __thiscall f(unsigned int); };
struct F_c884f0 { int __thiscall f(unsigned int); };
struct F_c35d20 { bool __thiscall f(); };
struct F_c35d40 { bool __thiscall f(); };
struct F_ba3f90 { int __thiscall f(void*, CB*, unsigned int); };
struct F_b48770 { void __thiscall f(CB*, int); };
int  __fastcall FUN_00b3d4c0(CB*);
void* __fastcall FUN_00b3d310(CB*);
bool __fastcall FUN_00c0bb90(CB*);
// ---- items of slice s00c0acd0 end

// ---- items of slice s00c0eae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int intptr_t;
#define nullptr 0
float sqrtf(float fValue);
#define __builtin_sqrtf sqrtf
struct Vec3 {
    float mX;
    float mY;
    float mZ;
};
class IRefCounted {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void v08();
    virtual void* Query(const void* pType);   // 0x0c
    virtual void v10();
    virtual uint32_t GetPoliticalID();        // 0x14
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
    virtual void v58(int a, int b, int c, int d);
    virtual void* QueryTarget(const void* pType);   // 0x5c
};
class cSpatialObject {
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
    virtual Vec3* GetPosition();          // 0x2c
    virtual Vec3* GetDirection();         // 0x30
    virtual bool IsVisible();             // 0x58
};
class cGameData : public IRefCounted {
public:
    uint8_t mPad60[0x1c];
};
class cCombatant : public cGameData {
public:
    uint8_t mPad7c[0x20];
};
class AnimatedCreature {
public:
    uint8_t mPad00[0x88];           // 0x00
    uint32_t mFlags;                // 0x88
    uint8_t mPad8c[0xc8];           // 0x8c
    uint32_t mState;                // 0x154
    Vec3 mOrientation;              // 0x158
    Vec3 mPosition;                 // 0x164
    uint8_t mPad170[0x10];
};
struct cCombatantSlot {
    int mKey;                       // 0x00
    int mSecondaryKey;              // 0x04
    uint8_t mPad08[0x18];           // 0x08
    cCombatant* mpCombatant;        // 0x20
};
class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(int nRange);
};
RandomLinearCongruential RandomGet();
void CreatureUpdateTransform(const Vec3* pPosition, int bFlag);
Vec3* RotateVectorAround(Vec3* pOut, const Vec3* pVector, const Vec3* pAxis);
bool IsVectorValid(const Vec3* pVector);
void* GetCurrentGameMode_s00c0_eae0();
extern uint8_t gGameModeTribe;
extern uint8_t gGameModeCity;
void CreatureAddRelation(cCombatant* pTarget);
uint32_t GetOwnPoliticalID(cSpatialObject* pObject);
void CreaturePlayAttackAnimation();
bool IsAnimationQueuedOrCurrent(void* pCreature);
void HideCreature(bool bHide);
void CreatureMoveStep(const Vec3* pDelta, int bFlag);
bool TraceTerrain(const Vec3* pFrom, const Vec3* pDirection, void* pWorld, float* pOut, int a, int b);
class Simulator_cCreatureBase : public cSpatialObject {
public:
    uint8_t mPad04[0xbc];           // 0x04
    uint8_t mLocomotiveFlags;       // 0xc0
    uint8_t mPadC1[0x76];           // 0xc1
    uint8_t mOrientationValid;      // 0x137
    uint8_t mPad138[0x9d8];         // 0x138
    uint32_t mFlags;                // 0xb10
    uint8_t mPadB14[0x04];          // 0xb14
    cCombatant* mpCombatantTarget;  // 0xb18
    int mIntentionTowardsTarget;    // 0xb1c
    void* mpSteeringModel;          // 0xb20
    uint8_t mPadB24[0x30];          // 0xb24
    AnimatedCreature* mpAnimatedCreature;   // 0xb54
    uint32_t mSteeringFlags;        // 0xb58
    uint8_t mTargetFlag;            // 0xb5c
    uint8_t mPadB5D[0x2ff];         // 0xb5d
    IRefCounted* mpSenseObject;     // 0xe5c
    uint8_t mPadE60[0x03];          // 0xe60
    uint8_t mPathValid;             // 0xe63
    uint32_t mSteeringTimer;        // 0xe64
    uint8_t mPadE68[0x14];          // 0xe68
    IRefCounted* mpSteeringTarget;  // 0xe7c
    uint8_t mPadE80[0x1c0];         // 0xe80
    cCombatantSlot* mpSlotsBegin;   // 0xe40
    cCombatantSlot* mpSlotsEnd;     // 0xe44

    void SteerTowards(const Vec3* pTarget, int nDelta);        // 0x00c0eae0
    void SetCreatureTarget(cCombatant* pTarget, bool bFlag, int nIntention);  // 0x00c0ed60
    void* GetTargetAsCreature();                                // 0x00c0ee70
    void ApplyCombatTarget();                                   // 0x00c0ee90
    void UpdateSteering(int nDelta, float fAmount);              // 0x00c0eec0
    void Hide();                                                // 0x00c0f280
    void Show();                                                // 0x00c0f2b0
    bool TraceTo(const Vec3* pFrom, const Vec3* pTo, Vec3* pOut);  // 0x00c0f2e0
    void ResetCombatants();                                     // 0x00c0f490
    bool IsSlotEmpty(uint32_t nIndex);                          // 0x00c0f510
    int CountValid();                                           // 0x00c0f570
    bool IsFull();                                              // 0x00c0f5f0
    uint32_t FindFirstEmpty();                                  // 0x00c0f620
    uint32_t FindRandomEmpty();                                 // 0x00c0f6b0
    uint32_t FindFirstValid();                                  // 0x00c0f780
    uint32_t FindNextValid(int nAfter);                         // 0x00c0f810
    cCombatant* GetAt(uint32_t nIndex);                         // 0x00c0f8a0
    uint32_t FindByCombatant(int nCombatant);                   // 0x00c0f8f0
    uint32_t FindByKey(int nKey);                               // 0x00c0f960
    cCombatantSlot* FindSlotByKey(int nKey, uint32_t* pIndex);  // 0x00c0f9b0
    cCombatantSlot* FindSlotByCombatant(int nCombatant, uint32_t* pIndex);  // 0x00c0fa10
};
// ---- items of slice s00c0eae0 end

// ---- items of slice s00c13340 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float   gFallbackRange;  // 0x01582f60
extern float   gEps146a330;     // 0x0146a330 (1.5e-5)
extern float   gZero1485378;    // 0x01485378 (0.0f cmp)
extern float   gOne1485720;     // 0x01485720 (1.0f)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Vector3_s00c1_3340 {
    float x, y, z;
    Vector3_s00c1_3340() {}
    Vector3_s00c1_3340(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s00c1_3340(const Vector3_s00c1_3340& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3_s00c1_3340& operator=(const Vector3_s00c1_3340& v) { x = v.x; y = v.y; z = v.z; return *this; }
    float Dot(const Vector3_s00c1_3340& b) const { return x * b.x + y * b.y + z * b.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    Vector3_s00c1_3340 operator+(const Vector3_s00c1_3340& b) const { return Vector3_s00c1_3340(x + b.x, y + b.y, z + b.z); }
    Vector3_s00c1_3340 operator-(const Vector3_s00c1_3340& b) const { return Vector3_s00c1_3340(x - b.x, y - b.y, z - b.z); }
    Vector3_s00c1_3340 operator*(float s) const { return Vector3_s00c1_3340(x * s, y * s, z * s); }
};
inline Vector3_s00c1_3340 operator*(float s, const Vector3_s00c1_3340& v) { return Vector3_s00c1_3340(v.x * s, v.y * s, v.z * s); }
struct IEffect {
    PV                                        // 0x00
    virtual void Release();                   // 0x04
    PV                                        // 0x08
    virtual void Stop(int flag);              // 0x0c
    PV8 PV8 PV4 PV                            // 0x10..0x60 (21 slots)
    virtual void Detach();                    // 0x64
};
struct IRefObj {
    PV8 PV8 PV8 PV8 PV8 PV4 PV2 PV             // 0x00..0xb8 (47 slots)
    virtual void AddRef();                    // 0xbc
    virtual void SubRef();                    // 0xc0
};
struct ICombatant {
    PV2                                       // 0x00
    virtual void* ToSpatialObject();          // 0x08
    virtual void* ToGameData();               // 0x0c
    PV8 PV8 PV8 PV4 PV                         // 0x10..0x80 (29 slots)
    virtual void SetCreatureTarget(void* a, void* b, void* c);  // 0x84
};
struct ILoco {
    PV8 PV2 PV                                // 0x00..0x28 (11 slots)
    virtual Vector3_s00c1_3340* Get2c();                 // 0x2c (returns a Vector3 pointer)
    PV8 PV2 PV                                // 0x30..0x58 (11 slots)
    virtual void* Get5c(void* a, void* b, float c);  // 0x5c
    PV2                                       // 0x60..0x64 (2 slots)
    virtual void* Get68();                    // 0x68 (extents pointer)
    PV                                        // 0x6c
    virtual float GetScalar70();              // 0x70
};
struct IProp {
    PV8 PV8 PV8 PV8 PV8                           // 0x00..0x9c (40 slots)
    virtual void Set(void* v);                    // 0xa0
    PV2 PV2                                        // 0xa4..0xa8
    virtual int  Get();                            // 0xac
    PV2 PV2                                        // 0xb0..0xb4
    virtual void* Find(int keyword);               // 0xb8
};
struct PropData {
    void*    mpVtbl;                              // +0x00
    uint8_t  pad04[0x4c];
    uint32_t mFlags50;                            // +0x50
};
struct IKeyed {
    PV8                                             // 0x00..0x1c (slots 0..7)
    virtual void* Slot20(int key);                  // 0x20
};
struct KeyedData {
    void*   mpVtbl;                                 // +0x00
    uint8_t pad04[0x24];
    int     mKey28;                                 // +0x28
};
struct IModelWorld {
    virtual void Slot00();                        // 0x00
    virtual void Release();                       // 0x04
};
struct IStream {
    PV8                                        // 0x00..0x1c (8 slots)
    virtual void* GetWriter_20();              // 0x20
    PV                                          // 0x24
    virtual void  Slot28(int key, void* out, int b);  // 0x28
};
struct IWriterS {
    PV2 PV4                                    // 0x00..0x14 (6 slots)
    virtual void* GetStream_18();              // 0x18
};
void*       FUN_00b5b800();                                        // 0x00b5b800 SP::GetCurrentGameMode
void*       FUN_00ae66f0(void* creature);                          // 0x00ae66f0 CastCreature
void*       FUN_00d38840();                                        // 0x00d38840 cCreatureModeStrategy::Instance
float       FUN_004e1c70(int a, int key, float def);               // 0x004e1c70 SP::GetPropertyT<float>
void        FUN_00ad7ec0(void* dst, void* src);                   // 0x00ad7ec0 PtrField::assign
void        FUN_00c0e000(void* obj, void* a, void* b);             // 0x00c0e000 set
void*       FUN_00b3d520();                                        // 0x00b3d520 SP::GonzagoModelWorld
void*       FUN_00b3d310(void* a, int b);                          // 0x00b3d310
void        FUN_00b5a260(void* a);                                 // 0x00b5a260
void*       FUN_009cab60(void* mw, void* prop);                    // 0x009cab60
void        FUN_00c0de60(void* self, void* elem, void* offsets);   // 0x00c0de60 SetGraspedEffectOffsets
void*       FUN_00b3d300(int noun);                                // 0x00b3d300 SP::NounManager
void*__fastcall FUN_00b21000(void* nm, void* edx);                  // 0x00b21000 (thiscall, 1 arg)
int         FUN_0064f350(int a, int key, int b);                   // 0x0064f350 parser/state
void        FUN_00d7d220(void* a, void* b);                        // 0x00d7d220
int         FUN_00c11f50(void* self, int index, int a, void* b, void* c);  // 0x00c11f50 CreateBodyEffect
void        FUN_00a01f10(void* obj, void* edx, int a, int b);     // 0x00a01f10 anim_qb::Foo
int         FUN_00c0c5b0(void* self, int a, int* out);             // 0x00c0c5b0
void        FUN_00c10210(int a, int b, int c, int d);              // 0x00c10210
void        FUN_0093ac80(void* stream, void* out);            // 0x0093ac80 ReadBool
struct Rec34 {
    uint32_t mp00;      // +0x00 (cleared with no release)
    uint8_t  pad04[0x20];
    IEffect* mpThird;   // +0x24
    IEffect* mpFirst;   // +0x28
    IEffect* mpSecond;  // +0x2c
    uint8_t  pad30[4];  // +0x30
};
struct DestructOwner {
    uint32_t pad00[0x301];            // +0x0000 .. +0x0c04
    uint32_t mC04;                    // +0x0c04
    uint32_t mC08;                    // +0x0c08
    uint32_t mC0C;                    // +0x0c0c
    uint8_t  padC10[0x2a4];           // +0x0c10 .. +0x0eb4
    Rec34    mRecs[4];                // +0x0eb4
};
struct CAnim {
    PV2 PV                                      // 0x00..0x04
    virtual void* Slot08(int a, int b);         // 0x08
    virtual void  Slot0c(int a, int b);         // 0x0c
    PV2 PV2                                      // 0x10..0x14
    virtual void  Slot18(int a);                // 0x18
    virtual void  Slot1c(int a, float v);       // 0x1c
    virtual void  Slot20(int a, int v);         // 0x20
    virtual void  Slot24(int a, float v);       // 0x24
    virtual void  Slot28(int a, void* p);       // 0x28
    PV4                                          // 0x2c..0x38
    virtual void  Slot3c(int a, bool b);        // 0x3c
    virtual void  Slot40(int a, int v);         // 0x40
    PV                                          // 0x44
    virtual void  Slot48(int a, void* cb);      // 0x48
    virtual void  Slot4c(int a, int flags, int b);  // 0x4c
    uint8_t  pad4[0x160];    // +0x04 .. +0x164
    Vector3_s00c1_3340  mLocalOffset;   // +0x164
    uint8_t  pad170[0xc];
    void*    mpModelWorld;   // +0x17c
    uint8_t  pad180[4];
    void*    mpP184;         // +0x184
};
struct CitRec {
    int32_t  mId;            // +0x00
    uint8_t  pad04[0x1c];
    IRefObj* mpPtr;          // +0x20
};
struct CAnimator {
    uint8_t  pad00[0x548];
    float    mF548;          // +0x548 hover height
    float    mF54C;          // +0x54c hover height (unscaled)
    uint8_t  pad550[0x40];
    float    mF590;          // +0x590
    uint8_t  pad594[0x88];
    int32_t  mI61c;          // +0x61c
    uint8_t  pad620[0x78];
    int32_t  mI698;          // +0x698
    uint8_t  pad69c[4];
    int32_t  mI6a0;          // +0x6a0
};
struct CCreature {
    uint8_t   pad00[0x110];
    uint32_t  mFlags110;         // +0x110 (0x1000 = hover enabled)
    uint8_t   pad114[0x23];
    uint8_t   mb137;             // +0x137
    uint8_t   pad138[0x178];
    uint32_t  mAnim3;            // +0x2b0 (mode = 3)
    uint8_t   pad2B4[0x80];
    uint32_t  mB34;              // +0x334
    uint8_t   pad338[0x7e8];
    void*     mpAnimator;        // +0xb20
    uint8_t   padB24[0x30];
    void*     mpAnimating;       // +0xb54
    uint32_t  mFlagsB58;         // +0xb58
    uint8_t   padB5C[0x2e4];
    CitRec*   mpRecsBegin;       // +0xe40
    CitRec*   mpRecsEnd;         // +0xe44
    uint8_t   padE48[0x1b];
    uint8_t   mbE63;             // +0xe63
    uint32_t  mE64;              // +0xe64
    uint8_t   padE68[0x14];      // +0xe68 .. +0xe7c
    ICombatant* mpCombatantTarget;  // +0xe7c
    uint8_t   padE80[0x34];
    Rec34     mAttacks[4];       // +0xeb4
};
// ---- items of slice s00c13340 end

// ---- items of slice s00c15310 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gF_15826c;        // 0x15826c
extern float gF_158270;        // 0x158270
extern float gF_169e280;       // 0x169e280
extern float gF_169e284;       // 0x169e284
extern float gF_146a32c;       // 0x146a32c (float sentinel, ~3.4e38)
extern float gF_168d910[];     // 0x168d910
typedef unsigned int   u32;
typedef int            s32;
typedef unsigned char  u8;
typedef unsigned int   SIZE_T;
struct Vec3_s00c1_5310 { float x, y, z; };
struct RefCnt {
  virtual void  AddRef();               // 0x00
  virtual void  Release();              // 0x04
  virtual void  pad08();
  virtual void  pad0c();
  virtual void  pad10();
  virtual void  pad14();
  virtual void  pad18();
  virtual void  pad1c();
  virtual void  pad20();
  virtual void  pad24();
  virtual void  pad28();
  virtual void  pad2c();
  virtual void  pad30();
  virtual void  pad34();
  virtual void  pad38();
  virtual void  pad3c();
  virtual void  pad40();
  virtual void  pad44();
  virtual void  pad48();
  virtual void  pad4c();
  virtual void  pad50();
  virtual void  pad54();
  virtual void  pad58();
  virtual void  pad5c();
  virtual void  pad60();
  virtual void  pad64();
  virtual void  pad68();
  virtual void  pad6c();
  virtual void  pad70();
  virtual void  pad74();
  virtual void  pad78();
  virtual void  pad7c();
  virtual void  pad80();
  virtual void  pad84();
  virtual void  pad88();
  virtual void  pad8c();
  virtual void  pad90();
  virtual void  pad94();
  virtual void  pad98();
  virtual void  pad9c();
  virtual void  pada0();
  virtual void  padA4();
  virtual void  padA8();
  virtual void  padAc();
  virtual void  padB0();
  virtual void  padB4();
  virtual void  padB8();
  virtual void  padBc();
};
struct SpatSub {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
virtual void  pad18();
virtual void  pad1c();
virtual void  pad20();
virtual void  pad24();
virtual void  pad28();
virtual void  pad2c();
virtual void  pad30();
virtual void  pad34();
virtual void  pad38();
virtual void  pad3c();
virtual void  pad40();
virtual void  pad44();
virtual void  pad48();
virtual void  pad4c();
virtual void  pad50();
virtual void  pad54();
virtual void  pad58();
  virtual Vec3_s00c1_5310* GetBounds(Vec3_s00c1_5310* out);              // 0x5c
  virtual void  pad60();
virtual void  pad64();
virtual void  pad68();
  virtual Vec3_s00c1_5310* GetBox(Vec3_s00c1_5310* out);                 // 0x6c
  virtual void  pad70();
  virtual float GetRadius();                       // 0x74
};
struct cCreatureAbility {
  u8   pad000[0x9c];
  float mF_9c;                                     // 0x9c
};
struct cAbilityState {
  u32   mU32_00;                                   // 0x00
  float mF_04;                                     // 0x04
  u32   mU32_08;                                   // 0x08
  u32   mU32_0c;                                   // 0x0c
};
struct BaseVtbl {
  virtual void* Slot0c(u32);                       // 0x0c
  virtual void  Slot18(void*);                     // 0x18
  virtual void  Slot1c(void*);                     // 0x1c
  virtual void* Slot20();                          // 0x20
  virtual void* Slot24(u32 propId, void* out);     // 0x24
  virtual u32   Slot2c(void* p);                   // 0x2c
  virtual void  Slot60();                          // 0x60
  virtual void  Slot64();                          // 0x64
  virtual Vec3_s00c1_5310* Slot6c(Vec3_s00c1_5310* out);                 // 0x6c
  virtual void  Slot70();
  virtual float Slot74();                          // 0x74
  virtual void  Slotb0();                          // 0xb0
  virtual u32   Slotb0_count();                    // 0xb0
  virtual u32   Slotb4(u32);                       // 0xb4
  virtual void* Slotb8(u32);                       // 0xb8
  virtual void  Slotbc();                          // 0xbc
  virtual void  Slotc0();                          // 0xc0
};
struct cSPCreatureBase_s00c1_5310 {
  BaseVtbl* mpVtbl;                                // 0x000
  u8        pad004[0xc0 - 0x04];
  SpatSub   mSpatial;                              // 0x0c0
  u8        pad0c4[0x1e4 - 0xc4];
  float     mF_1e4;                                // 0x1e4
  u8        pad1e8[0x4cc - 0x1e8];
  RefCnt*   mpRefA_4cc;                            // 0x4cc
  u8        pad4d0[0xb54 - 0x4d0];
  void*     mpAnimWorld_b54;                       // 0xb54 (anim world)
  u32       mFlags_b58;                            // 0xb58 (bit 9 tested)
  u8        padB5c[0xbf8 - 0xb5c];
  // mRechargingAbilityBits: a 3-word bitset at 0xbf8
  u32       mRechargeBits_bf8[3];                  // 0xbf8
  u32       mAbilityDirty_c04[3];                  // 0xc04
  u8        padC10[0xc28 - 0xc10];
  void*     mpAbilityStates_c28;                   // 0xc28 (vector block ptr)
  u8        padC2c[0xe40 - 0xc2c];
  u8*       mNeighborBegin_e40;                    // 0xe40
  u8*       mNeighborEnd_e44;                      // 0xe44
  u8        padE48[0xe58 - 0xe48];
  float     mWaveF_e58;                            // 0xe58
  u8        padE5c[0xeb0 - 0xe5c];
  // Slot 0 of the 4x0x34-byte body-effect slot block at 0xeb0. Slot 1 begins
  // at 0xee4 (aliasing mFlags_ee4 below), slots 2..3 follow it.
  u8        mBodyBlock_eb0[0x34];                   // 0xeb0
  u32       mFlags_ee4;                            // 0xee4

  void __thiscall func64h(s32 a2, float a3);       // 0xc15310
  float FUN_00c15920();                            // 0xc15920
  float FUN_00c15970();                            // 0xc15970
  void  FUN_00c15470(s32 a2, RefCnt* a3, u8 a4);   // 0xc15470
  u8    FUN_00c159c0(u32 a2, u32 a3, u8 a4);       // 0xc159c0
  void* FUN_00c15bd0(u32 a2, u8 a3, u32 a4);       // 0xc15bd0
  u8    FUN_00c15d50(u32 a2, u32 a3, u32 a4);      // 0xc15d50
  void  FUN_00c15dc0(float a2);                    // 0xc15dc0
};
void __cdecl FUN_00c14f70(cSPCreatureBase_s00c1_5310*, u32, u32, u32);      // 0xc14f70
void* __cdecl EffectsManager();                                  // 0x67ddd0
struct BodyEffectVtbl {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
  virtual void  SetMatrix(void* m);                // 0x18
virtual void  pad1c();
virtual void  pad20();
virtual void  pad24();
  virtual void  pad28();
  virtual void  Slot2c();                          // 0x2c
};
struct BodyEffect {
  BodyEffectVtbl* mpVtbl;                          // 0x00
  float           mF_04;                           // 0x04
  u8              pad08[0x2c - 0x08];
  void*           mpMatrix_2c;                     // 0x2c
};
struct ObjVtbl {
virtual void  Slot00();
virtual void  Slot04();
virtual void  Slot08();
virtual void* Slot0c(u32);
virtual void  Slot10();
virtual void  Slot14();
virtual void  Slot18();
virtual void  Slot1c();
virtual void* Slot20();
virtual void  Slot24();
virtual void  Slot28();
virtual u8    Slot2c();
virtual void  Slot30();
virtual void  Slot34();
virtual void  Slot38();
virtual void  Slot3c();
virtual void  Slot40();
virtual void  Slot44();
virtual void  Slot48();
virtual void  Slot4c();
virtual void  Slot50();
virtual void  Slot54();
virtual void  Slot58();
  virtual Vec3_s00c1_5310* Slot5c(Vec3_s00c1_5310* out);                 // 0x5c
virtual void  Slot60();
virtual void  Slot64();
  virtual Vec3_s00c1_5310* Slot6c(Vec3_s00c1_5310* out);                 // 0x6c
  virtual void  Slot70();
  virtual float Slot74();                          // 0x74
virtual void  Slot78();
virtual void  Slot7c();
virtual void  Slot80();
virtual void  Slot84();
virtual void  Slot88();
virtual void  Slot8c();
virtual void  Slot90();
virtual void  Slot94();
virtual void  Slot98();
virtual void  Slot9c();
virtual void  SlotA0();
virtual void  SlotA4();
virtual void  SlotA8();
virtual void  SlotAc();
virtual void  SlotB0();
virtual void  SlotB4();
virtual void* SlotB8(u32);
virtual void  SlotBc();
  virtual void  SlotC0();
};
void*  __cdecl FUN_00b3d310();                        // 0xb3d310
int    __fastcall FUN_00c06000_tc(void* thisptr, int dummy); // 0xc06000 (ecx=this)
u8     __fastcall FUN_00c15150_tc(void* thisobj, int dummy, void* a1, u32 a2); // 0xc15150
void   __cdecl FUN_00c0f490(void*);                   // 0xc0f490
void   __cdecl FUN_00c0ca00(Vec3_s00c1_5310*, Vec3_s00c1_5310*, float, void*, void*); // 0xc0ca00
void   __cdecl FUN_00c12640(float);                   // 0xc12640
void*  __cdecl FUN_0099c1a0(Vec3_s00c1_5310* out, void* quat, Vec3_s00c1_5310* in);  // 0x99c1a0
void*  __cdecl FUN_0069b440(void* out, void* facing, void* up); // 0x69b440
struct EffectsMgr {
  virtual void  pad0();
  virtual void  pad1();
  virtual void  pad2();
  virtual void  pad3();
  virtual void  pad4();
  virtual void  pad5();
  virtual void  pad6();
  virtual void  pad7();
  virtual void  pad8();
  virtual void  pad9();
  virtual void  padA();
  virtual u8    Slot2c(u32 a, u32 b, void** out);      // 0x2c
};
struct cSPCreatureBaseVtbl {
virtual void  pad00();
virtual void  pad04();
virtual void  pad08();
virtual void  pad0c();
virtual void  pad10();
virtual void  pad14();
virtual void  pad18();
virtual void  pad1c();
virtual void  pad20();
virtual void  pad24();
virtual void  pad28();
virtual void  pad2c();
virtual void  pad30();
virtual void  pad34();
virtual void  pad38();
virtual void  pad3c();
virtual void  pad40();
virtual void  pad44();
virtual void  pad48();
virtual void  pad4c();
virtual void  pad50();
virtual void  pad54();
virtual void  pad58();
virtual void  pad5c();
virtual void  pad60();
virtual void  pad64();
virtual void  pad68();
virtual void  pad6c();
virtual void  pad70();
virtual void  pad74();
virtual void  pad78();
virtual void  pad7c();
virtual void  pad80();
virtual void  pad84();
virtual void  pad88();
virtual void  pad8c();
virtual void  pad90();
virtual void  pad94();
virtual void  pad98();
virtual void  pad9c();
virtual void  padA0();
virtual void  padA4();
virtual void  padA8();
virtual void  padAc();
  virtual u32   GetAbilitiesCount();                    // 0xb0 (this slice)
  virtual cCreatureAbility* GetAbility(u32);            // 0xb4
  virtual void* Slotb8(u32);                            // 0xb8
};
struct SimCreature {
  cSPCreatureBaseVtbl* mpVtbl;                          // 0x000
};
struct AbilityObj {
  u8  pad00[0x88];
  u32 mpEffect_88;      // 0x88 (parent effect object)
  u32 mEffectId_8c;     // 0x8c (effect resource id passed to EffectsMgr)
};
struct BodyEntry {
  u8      mB_00;                          // 0x00
  u8      mB_01;                          // 0x01
  u8      pad02[0x04 - 0x02];
  u32     mU32_04;                        // 0x04
  float   mF_08;                          // 0x08
  float   mF_0c;                          // 0x0c
  float   mF_10;                          // 0x10
  float   mF_14;                          // 0x14
  float   mF_18;                          // 0x18
  float   mF_1c;                          // 0x1c
  u32     mU32_20;                        // 0x20
  float   mF_24;                          // 0x24
  RefCnt* mpTarget_28;                    // 0x28
  BodyEffect* mpEffect_2c;                // 0x2c
  u8      pad30[0x34 - 0x30];
};
// ---- items of slice s00c15310 end

// ---- items of slice s00c17350 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cEffectSlot {
    virtual void v00();                // slot +0x00
    virtual void v04();                // slot +0x04
    virtual void v08();                // slot +0x08
    virtual void v0c();                // slot +0x0c
    virtual bool IsActive();           // slot +0x10
};
struct cEffectEntry {
    uint8_t      mPad000[0x8c];        // +0x000
    cEffectSlot* mEffect;              // +0x08c
};
struct cBodyAnim {
    // 0x009cab60  resolve the effect entry for a key
    cEffectEntry* FindEffect(uint32_t key);
};
struct cCreatureBody {
    uint8_t     mPad000[0x17c];        // +0x000
    cBodyAnim*  mAnim;                 // +0x17c
};
struct cSPCreatureBase_s00c1_7350 {
    uint8_t        mPad0000[0xb20];    // +0x0000
    void*          mCreature;          // +0x0b20
    uint8_t        mPad0b24[0xb54 - 0xb24]; // +0x0b24
    cCreatureBody* mBody;              // +0x0b54

    uint32_t MakeBodyEffect(uint32_t part, uint32_t a, uint32_t b);  // 0x00c14f70
    void     BodyEffectNotify(uint32_t a, uint32_t b);               // 0x00c15150

    // 0x00c17580
    uint32_t GetBodyPartIndex(uint32_t kind, uint32_t index);  // 0x00c17580 (cSPCreatureBase::GetBodyPartIndex)
    // 0x00c17c80
    uint32_t CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b);
    // 0x00c17cc0
    uint32_t CreateBodyEffectChecked(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                     uint32_t b);
    // 0x00c17d60
    uint32_t CreateBodyEffectChecked2(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                      uint32_t b);
};
uint32_t QueryCreatureBodyParts(cSPCreatureBase_s00c1_7350* self, uint32_t kind, uint32_t* out, uint32_t max);
// ---- items of slice s00c17350 end

// ---- items of slice s00c18b40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kRealZero;      // 0x01485378  _HK_REAL_ZERO
extern const float kSqrtEpsilon;   // 0x013ec4b8
extern const float kThree;         // 0x013eb95c
extern float  gZeroVecX;           // 0x0168d910
extern float  gZeroVecY;           // 0x0168d914
extern float  gZeroVecZ;           // 0x0168d918
extern bool   gB_1572050;          // 0x01572050
extern bool   gB_1572051;          // 0x01572051
extern bool   gB_169e381;          // 0x0169e381
extern float  gF_169e384;          // 0x0169e384
extern float  gF_169e388;          // 0x0169e388
extern float  gF_169e38c;          // 0x0169e38c
extern float  gF_169e390;          // 0x0169e390
extern float  gF_169e3b4;          // 0x0169e3b4
extern float  gF_169e3b8;          // 0x0169e3b8
extern float  gF_169e3bc;          // 0x0169e3bc
extern const char* gBodyPartsString; // 0x015716e8
extern int gAbilityStatesAllocator;  // 0x013ebb38 (eastl allocator)
extern const float kLeapRadiusScale; // 0x01582fd8
extern const float kDefaultSpeedCap; // 0x01582fc0
extern const float kCe80Boost;       // 0x0150c900
extern const float kHalf;            // 0x01471064
extern const float kClampLow;        // 0x013eb8c8
extern const float kPlenEpsilon;     // 0x01488874
typedef unsigned int   uint32;
struct Vector3_s00c1_8b40 { float x, y, z; };
struct InventoryItem;
bool   Vector3Equal(const Vector3_s00c1_8b40* a, const Vector3_s00c1_8b40* b);                  // 0x004232c0 (cdecl)
Vector3_s00c1_8b40* normalized_safe(Vector3_s00c1_8b40* out, const Vector3_s00c1_8b40* in);                // 0x00449c20 (cdecl)
void*  operator_new(uint32 size, const char* name, int a, int b,
                    const char* file, int line);                          // 0x00f473a0 (cdecl)
void*  FUN_00ac2130(void* begin, void* end, void* dst);                   // 0x00ac2130 (cdecl, copy range)
int    EvaluateContextTargetQuery(void* out, int max, void* abilities,
                                  void* ctx, int a, int b);               // 0x009b2340 (cdecl)
class cPlanetModel_s00c1_8b40 {
public:
    float FUN_00b7e490();                                             // 0x00b7e490
    float GetRadiusAt(const Vector3_s00c1_8b40* p);                              // 0x00b7ef70
    float FUN_00b82310(const Vector3_s00c1_8b40* p);                             // 0x00b82310
};
class cLoco {
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
    virtual const Vector3_s00c1_8b40* GetPos();                                  // 0x2c
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
virtual void v5c0();
    virtual const Vector3_s00c1_8b40* GetForward(Vector3_s00c1_8b40* out);                  // 0x5c
virtual void v60();
virtual void v64();
virtual void v68();
    virtual const float* GetBounds(float* out);                       // 0x6c
    virtual void v70();
    virtual float GetRadius();                                        // 0x74
virtual void v78();
virtual void v7c();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
virtual void vc0();
virtual void vc4();
    virtual float GetF_0xc8();                                        // 0xc8
virtual void vcc();
virtual void vd0();
virtual void vd4();
virtual void vd8();
    virtual void Submit(const void* req);                             // 0xdc

    const Vector3_s00c1_8b40* GetVelocity();                                     // 0x00d20610
    void FUN_00c446d0(const Vector3_s00c1_8b40* v, int flag);                    // 0x00c446d0 (ret 8)
};
struct AnimatingCreature {
    char  pad000[0x170];
    uint32 mField170;         // +0x170
    char  pad174[0x17c - 0x174];
    void** mpAbilityList;     // +0x17c
};
struct BodyPartQuery {
    int         flag;         // +0x0
    const char* mpName;       // +0x4
    int         a;            // +0x8
    int         b;            // +0xc
};
struct AbilityState {
    bool  applied;         // +0x0
    bool  inRange;         // +0x1
    char  pad02[2];
    float chargeLevel;     // +0x4
    double refresh;        // +0x8
};
struct Ability_s00c1_8b40 {
    char  pad00[0x104];
    float mCost;           // +0x104
};
struct SpeciesProfile {
    char  pad00[0x548];
    float jumpingAbility;      // +0x548
    char  pad54c[4];
    float flappingAbility;     // +0x550
    char  pad554[0x610 - 0x554];
    uint32 sprintLevel;        // +0x610
    char  pad614[8];
    uint32 preferredSocialType; // +0x61c
    char  pad620[0x698 - 0x620];
    uint32 mCount698;          // +0x698
    char  pad69c[4];
    uint32 mCount6a0;          // +0x6a0
};
struct LocomotionRequest {
    char* mpBegin;
    char  pad[0x6c];
    LocomotionRequest();                                              // 0x00ac9850
};
class cSPCreatureBase_s00c1_8b40 {
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
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
    virtual uint32 GetAbilityCount();                                 // 0xb0
    virtual Ability_s00c1_8b40* GetAbility(uint32 index);                        // 0xb4

    char  pad04[0xc0 - 4];
    cLoco mBody;                                                      // 0xc0
    char  padc0[0x110 - 0xc4];
    uint32 mFlags;                                                    // 0x110
    char  pad114[0x137 - 0x114];
    bool  mbLeaping;                                                  // 0x137
    char  pad138[0x2b0 - 0x138];
    int   mState;                                                     // 0x2b0
    char  pad2b4[0xb20 - 0x2b4];
    SpeciesProfile* mpProfile;                                        // 0xb20
    char  padb24[0xb54 - 0xb24];
    AnimatingCreature* mpAnimCreature;                                // 0xb54
    uint32 mGeneralFlags;                                             // 0xb58
    char  padb5c[0xbb0 - 0xb5c];
    bool  mbFieldBB0;                                                 // 0xbb0
    char  padbb1[0xbec - 0xbb1];
    uint32 mInUseAbilityBits[3];                                      // 0xbec
    uint32 mRechargingAbilityBits[3];                                 // 0xbf8
    char  padc04[0xc28 - 0xc04];
    AbilityState* mpAbilityStates;                                    // 0xc28
    char  padc2c[0xe40 - 0xc2c];
    InventoryItem* mpItemBegin;                                       // 0xe40
    InventoryItem* mpItemEnd;                                         // 0xe44
    char  pade48[0xe8c - 0xe48];
    uint32 mCurrentAttackIdx;                                         // 0xe8c

    int  FindIndex(int key);                                          // 0x00c0c080 (ret 4)
    void FUN_00c15dc0(float f);                                       // 0x00c15dc0 (ret 4, ApplyWave)
    void FUN_00c15bd0(int index, int a, int b);                       // 0x00c15bd0 (ret 0xc)
    float FUN_00c0ce80(int a, int b);                                 // 0x00c0ce80 (ret 8)

    int  FUN_00c18b40(int arg);                                       // 0x00c18b40 (ret 4)
    bool TryJumpToTarget(const Vector3_s00c1_8b40* a1, const Vector3_s00c1_8b40* a2,
                         int a3, float a4, bool a5);                  // 0x00c190e0 (ret 0x14)
    uint32 FUN_00c196a0(uint32 index, bool a2, bool a3);              // 0x00c196a0 (ret 0xc)
    void FUN_00c197a0(uint32 index);                                  // 0x00c197a0 (ret 4)
    void FUN_00c19940(bool a);                                        // 0x00c19940 (ret 4)
    void InterruptAnimation(uint32 id, int a, int b);                 // 0x00c12310 (ret 0xc)
    bool GetBodyPartPositionAndOrientation(Vector3_s00c1_8b40& out, void* quat,
                                           uint32 part, bool flag) const; // 0x00c11b50 (ret 0x10)
};
struct CreatureSubView {
    char pad[0x5a8];
    Vector3_s00c1_8b40* FUN_00c19870(Vector3_s00c1_8b40* out, int part);                    // 0x00c19870 (ret 8)
};
struct InventoryItem {
    char pad[0x20];
    void* mpObject;                                                   // +0x20
};
class InventoryObject {
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
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
    virtual void* Query(uint32 id);                                   // 0xb8
    char padbc[0x110 - 0xbc];
    int mKind;                                                        // 0x110
};
struct Vector003c {
    void* mpBegin;                                                    // +0x0
    void* mpEnd;                                                      // +0x4
    void* mpCapacity;                                                 // +0x8
    void reserve(uint32 count);                                       // 0x00c199e0 (ret 4)
};
// ---- items of slice s00c18b40 end

// ---- items of slice s00c1c9f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef int            i32;
typedef float          f32;
typedef double         f64;
double pow(double, double);
extern f32 DAT_013f9428;   // 0x013f9428
extern f32 DAT_013ec480;   // 0x013ec480
extern f32 DAT_013f7344;   // 0x013f7344
extern f64 DAT_01447a10;   // 0x01447a10
extern const f32 _HK_REAL_ZERO;  // 0x01485378
class cVObj {
public:
    virtual void  v00();
    virtual void  v04();                 // +0x04: Release
    virtual void  v08(i32);              // +0x08
    virtual void  v0c(i32);              // +0x0c
    virtual bool  v10();                 // +0x10
    virtual void  v14();                 // +0x14
    virtual void  v18(void*);            // +0x18
    virtual void  v1c();                 // +0x1c
    virtual void  v20();                 // +0x20
    virtual void  v24();                 // +0x24
    virtual void  v28();                 // +0x28
    virtual void  v2c(i32);              // +0x2c
    virtual i32   v30();                 // +0x30
    virtual void  v34();                 // +0x34
    virtual i32   v38(i32);              // +0x38
    virtual void  v3c();                 // +0x3c
    virtual void  v40(i32, i32);         // +0x40
    virtual void  v44();                 // +0x44
    virtual void  v48();                 // +0x48
    virtual void  v4c();                 // +0x4c
    virtual void  v50();                 // +0x50
    virtual void  v54();                 // +0x54
    virtual void  v58();                 // +0x58
    virtual void  v5c();                 // +0x5c
    virtual void  v60();                 // +0x60
    virtual void  v64();                 // +0x64
    virtual void  v68();                 // +0x68
    virtual void  v6c();                 // +0x6c
    virtual void  v70();                 // +0x70
    virtual void  v74();                 // +0x74
    virtual void  v78();                 // +0x78
    virtual void  v7c();                 // +0x7c
    virtual void  v80();                 // +0x80
    virtual void  v84();                 // +0x84
    virtual void  v88();                 // +0x88
    virtual void  v8c();                 // +0x8c
    virtual void  v90();                 // +0x90
    virtual void  v94();                 // +0x94
    virtual void  v98();                 // +0x98
    virtual void  v9c(i32);              // +0x9c
    virtual void  vA0();                 // +0xa0
    virtual void  vA4();                 // +0xa4
    virtual void  vA8();                 // +0xa8
    virtual void  vAc();                 // +0xac
    virtual i32   vB0();                 // +0xb0
    virtual i32   vB4(i32);              // +0xb4
    virtual void  vB8();                 // +0xb8
    virtual void  vBc();                 // +0xbc
    virtual void  vC0();                 // +0xc0
    virtual void  vC4();                 // +0xc4
    virtual void  vC8();                 // +0xc8
    virtual void  vCc();                 // +0xcc
    virtual void  vD0();                 // +0xd0
    virtual void  vD4();                 // +0xd4
    virtual void  vD8();                 // +0xd8
    virtual void  vDc();                 // +0xdc
    virtual void  vE0();                 // +0xe0
    virtual void  vE4();                 // +0xe4
    virtual void  vE8();                 // +0xe8
    virtual void  vEc();                 // +0xec

    // non-virtual helpers that are called directly on embedded sub objects
    void FUN_00c41d60(void* pArg);       // 0x00c41d60
    void FUN_00bfcae0();                 // 0x00bfcae0
};
class cOrderMgr {                        // at +0xb48
public:
    void FUN_00bc9fe0();                 // 0x00bc9fe0
};
class cSpeciesProfile {                  // at +0xb20
public:
    u8  mPad_000[0x53c];
    u32 mnSequence;                      // +0x53c
    u8  mPad_540[0x644 - 0x540];
    f32 mf_644;                          // +0x644
};
class cEffect {                          // at +0xb54
public:
    u8  mPad_000[0x80];
    f32 mf_80;                           // +0x80
};
class cDetach {                          // at +0xe7c
public:
    virtual void  d00();
    virtual void  d04();
    virtual void  d08();
    virtual void  d0c();
    virtual void  d10();
    virtual void  d14();
    virtual void  d18();
    virtual void  d1c();
    virtual void  d20();
    virtual void  d24();
    virtual void  d28();
    virtual void  d2c();
    virtual void  d30();
    virtual void  d34();
    virtual void  d38();
    virtual void  d3c();
    virtual void  d40();
    virtual void  d44();
    virtual void  d48();
    virtual void  d4c();
    virtual void  d50();
    virtual void  d54();
    virtual void  d58();
    virtual void  d5c();
    virtual void  d60();
    virtual void  d64();                 // +0x64
};
class cPHTable {
public:
    void* FUN_00b76460(u32* pKey);       // 0x00b76460
    void  FreeBuckets(cVObj** ppBuckets, u32 nCount);   // 0x00a24480
    cVObj** mppBuckets;                  // +0x00
    u32     mnBucketCount;               // +0x04
    u32     mnSize;                      // +0x08
    u32     mnElementCount;              // +0x0c
};
struct cRBNode {
    cRBNode* mpLeft;                     // +0x00
    cRBNode* mpParent;                   // +0x04
    cRBNode* mpRight;                    // +0x08
    u8       mbColor;                    // +0x0c
    u8       mPad_0d[3];
};
struct cRBTree {
    u32      mUnk_00;                    // +0x00
    cRBNode  mAnchor;                    // +0x04
    u32      mnSize;                     // +0x14
};
template<class T>
class cVec {
public:
    void FUN_00c53690(i32 n);            // 0x00c53690
    void FUN_00c19d10(T* pEnd, const T* pSrc); // 0x00c19d10
    void clear() { mpEnd = mpBegin; }
    void push_back(const T& v) {
        if (mpEnd < mpCapacity) {
            if (mpEnd != 0)
                *mpEnd = v;
            ++mpEnd;
        } else {
            FUN_00c19d10(mpEnd, &v);
        }
    }
    T* mpBegin;                          // +0x00
    T* mpEnd;                            // +0x04
    T* mpCapacity;                       // +0x08
};
class cVec2 {
public:
    void clear() { mpEnd = mpBegin; }
    void* mpBegin;                       // +0x00
    void* mpEnd;                         // +0x04
};
struct cAbilityState_s00c1_c9f0 {
    u8  mbActive;                        // +0x00
    u8  mbEnabled;                       // +0x01
    u16 mwFlags;                         // +0x02
    f32 mfWeight;                        // +0x04
    u32 mGroupId;                        // +0x08
    u32 mInstanceId;                     // +0x0c
};
void* __cdecl FUN_00b76460(u32* pKey);                    // 0x00b76460
class cSPCreatureBase_s00c1_c9f0 : public cVObj {
public:
    // ---- slice targets ----
    void   FUN_00c1c9f0(char a);
    bool   FUN_00c1cc80(char a);
    void   FUN_00c1cdd0(i32 a);
    void   FUN_00c1cf20();
    cVObj* FUN_00c1d120(u32 a, u32 b);
    cVObj* FUN_00c1d290(u32 a);
    cVObj* FUN_00c1d400(u32 a, u32 b);
    cVObj* FUN_00c1d430(u32 a);
    cVObj* FUN_00c1d460(u32 a, u32 b);
    i32    FUN_00c1d5e0(char a, u32 b, u32 c);

    // ---- helpers called on this ----
    void  SetStealthed(i32 a, i32 b);                     // 0x00c1aed0
    void  SetSprinting(i32 a);                           // 0x00c1ad10
    void  InterruptAnimation(u32 id, i32 a, i32 b);      // 0x00c12310
    f32   FUN_00c0bb20();                                // 0x00c0bb20
    i32   FUN_00c0c080(i32 a);                           // 0x00c0c080
    void  FUN_00c0d9b0();                                // 0x00c0d9b0
    void  FUN_00c15dc0(f32 a);                           // 0x00c15dc0
    void  FUN_00c17350(u32 a, i32 b);                    // 0x00c17350
    void  FUN_00c19940(i32 a);                           // 0x00c19940
    void  FUN_00c151b0();                                // 0x00c151b0
    cVObj* FUN_00c14e70(u32 a);                          // 0x00c14e70

    // ---- fields (offsets are exact) ----
    u8   mPad_004[0xbc];                 // 0x004 .. 0x0bf
    cVObj mSub_0c0;                      // +0x0c0
    u8   mPad_0c4[0x4c];                 // 0x0c4 .. 0x10f
    u32  mdw_110;                        // +0x110
    u8   mPad_114[0x214];                // 0x114 .. 0x327
    u8   mb_328;                         // +0x328
    u8   mPad_329[0x27f];                // 0x329 .. 0x5a7
    cVObj mSub_5a8;                      // +0x5a8
    u8   mPad_5ac[0x574];                // 0x5ac .. 0xb1f
    cSpeciesProfile* mp_b20;             // +0x0b20
    u32  mdw_b24;                        // +0x0b24
    u8   mPad_b28[0x20];                 // 0x0b28 .. 0xb47
    cOrderMgr* mp_b48;                   // +0x0b48
    cVObj*     mp_b4c;                   // +0x0b4c
    u8   mPad_b50[4];                    // 0xb50 .. 0xb53
    cEffect*   mp_b54;                   // +0x0b54
    u32  mdw_b58;                        // +0x0b58
    u8   mb_b5c;                         // +0x0b5c
    u8   mPad_b5d[1];                    // 0xb5d
    u8   mb_b5e;                         // +0x0b5e
    u8   mb_b5f;                         // +0x0b5f
    u8   mPad_b60[3];                    // 0xb60 .. 0xb62
    u8   mb_b63;                         // +0x0b63
    u8   mPad_b64[0x10];                 // 0xb64 .. 0xb73
    f32  mf_b74;                         // +0x0b74
    f32  mf_b78;                         // +0x0b78
    f32  mf_b7c;                         // +0x0b7c
    f32  mf_b80;                         // +0x0b80
    f32  mf_b84;                         // +0x0b84
    u8   mPad_b88[0x29];                 // 0xb88 .. 0xbb0
    u8   mb_bb1;                         // +0x0bb1
    u8   mPad_bb2[2];                    // 0xbb2 .. 0xbb3
    cVObj* mp_bb4;                       // +0x0bb4
    u8   mPad_bb8[4];                    // 0xbb8 .. 0xbbb
    f32  mf_bbc;                         // +0x0bbc
    u8   mPad_bc0[0x2c];                 // 0xbc0 .. 0xbeb
    u32  mdw_bec;                        // +0x0bec
    u32  mdw_bf0;                        // +0x0bf0
    u32  mdw_bf4;                        // +0x0bf4
    u32  mdw_bf8;                        // +0x0bf8
    u32  mdw_bfc;                        // +0x0bfc
    u32  mdw_c00;                        // +0x0c00
    u32  mdw_c04;                        // +0x0c04
    u32  mdw_c08;                        // +0x0c08
    u32  mdw_c0c;                        // +0x0c0c
    u8   mPad_c10[0x18];                 // 0xc10 .. 0xc27
    cVec<cAbilityState_s00c1_c9f0> mAbilities;      // +0x0c28
    u8   mPad_c34[0x94];                 // 0xc34 .. 0xcc7
    cPHTable mTable_cc8;                 // +0x0cc8
    u8   mPad_cd8[0x90];                 // 0xcd8 .. 0xd67
    cPHTable mTable_d68;                 // +0x0d68
    u8   mPad_d78[0x90];                 // 0xd78 .. 0xe07
    cRBTree  mTree_e08;                  // +0x0e08
    u8   mPad_e20[4];                    // 0xe20 .. 0xe23
    cVec2 mVec_e24;                      // +0x0e24
    u8   mPad_e2c[0x2c];                 // 0xe2c .. 0xe57
    f32  mf_e58;                         // +0x0e58
    f32  mf_e5c;                         // +0x0e5c
    u8   mPad_e60[0x1c];                 // 0xe60 .. 0xe7b
    cDetach* mp_e7c;                     // +0x0e7c
    u8   mPad_e80[0xc];                  // 0xe80 .. 0xe8b
    u32  mdw_e8c;                        // +0x0e8c
    u32  mdw_e90;                        // +0x0e90
    f32  mf_e94;                         // +0x0e94
    cVec2 mVec_e98;                      // +0x0e98
    u8   mPad_ea0[0xc];                  // 0xea0 .. 0xeab
    cVObj* mp_eac;                       // +0x0eac
};
// ---- items of slice s00c1c9f0 end

// ---- items of slice s00c1f580 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void          __cdecl FUN_00c0d3a0(void* p);           // 0x00c0d3a0
extern "C" void*         __cdecl FUN_00c0ff80(void* a, void* b, void* c); // 0x00c0ff80
extern "C" void          __cdecl FUN_00572020(void* p, int flag); // 0x00572020
extern "C" void          __cdecl FUN_00c29b00(void* p);           // 0x00c29b00
extern wchar_t gEmptyString16[];        // 0x01667bac (eastl's empty 16-bit string)
extern float   gField13f1cac;           // 0x013f1cac
extern float   gHKRealOne;              // 0x01485720
extern float   gField13ec5b4;           // 0x013ec5b4
extern float   gVecBe0;                 // 0x0168d910
extern float   gVecBe4;                 // 0x0168d914
extern float   gVecBe8;                 // 0x0168d918
extern int     gField15716d4;           // 0x015716d4
extern int     gField15716d8;           // 0x015716d8
extern int     gField15716dc;           // 0x015716dc
extern int     gField15716e0;           // 0x015716e0
extern int     gField15716e4;           // 0x015716e4
struct Vector3_s00c1_f580 {
    float x;
    float y;
    float z;
};
class cReleaseable {
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
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    virtual void vc0();
};
struct cCurvePoint {
    int          mIndex;      // +0x00
    int          mField04;    // +0x04
    int          mField08;    // +0x08
    int          mField0c;    // +0x0c
    int          mField10;    // +0x10
    int          mField14;    // +0x14   (deliberately not initialized)
    union {
        unsigned char mByte18;   // +0x18  low byte: "initialised" flag
        float         mField18;  // +0x18  full slot: sampled curve limit
    };
    int          mField1c;    // +0x1c
    cReleaseable* mpRef20;    // +0x20

    cCurvePoint()
        : mIndex(-1), mField04(0), mField08(0), mField0c(0), mField10(0),
          mByte18(0), mField1c(0), mpRef20(0) {
    }
    ~cCurvePoint() {
        if (mpRef20 != 0) {
            mpRef20->vc0();
        }
    }
};
class cCurvePointVector {
public:
    cCurvePoint* mpBegin;    // +0x00
    cCurvePoint* mpEnd;      // +0x04
    cCurvePoint* mpCapacity; // +0x08
    void*        mpFixed;    // +0x0c

    void  PushBackDefault();                                          // 0x00c1f650
    void  InsertValue(cCurvePoint* pos, const cCurvePoint* value);    // 0x00c1b990
    cCurvePoint* erase(cCurvePoint* first, cCurvePoint* last);        // 0x00ac4570
    void* FUN_00c144b0(void* a, void* b);                             // 0x00c144b0
    void  fn(void* a, void* b, void* c, int count);                   // 0x00b96360
};
class cCurveHolder : public cCurvePointVector {
public:
    int     mField10;    // +0x10
    Vector3_s00c1_f580 mPoint14;    // +0x14
    char    mPad20[0x38];// +0x20
    int     mField58;    // +0x58
    int     mField5c;    // +0x5c
    void  FUN_00c199e0(int value);   // 0x00c199e0
};
class cSampleRef {
public:
    char  mPad00[0x0c];
    float mField0c;      // +0x0c
};
class cVector3Vector {
public:
    Vector3_s00c1_f580* mpBegin;    // +0x00
    Vector3_s00c1_f580* mpEnd;      // +0x04
    Vector3_s00c1_f580* mpCapacity; // +0x08

    void DoInsertValue(Vector3_s00c1_f580* position, const Vector3_s00c1_f580* value);  // 0x004b5ad0

    void push_back(const Vector3_s00c1_f580& value) {
        Vector3_s00c1_f580* slot = mpEnd;
        if (slot < mpCapacity) {
            mpEnd = slot + 1;
            if (slot != 0) {
                *slot = value;
            }
        } else {
            DoInsertValue(slot, &value);
        }
    }
};
extern cVector3Vector gVec168e81c;      // 0x0168e81c
struct cRange {
    float mMin;   // +0x00
    float mMax;   // +0x04

    cRange() {}
    cRange(float min, float max) : mMin(min), mMax(max) {}
};
class cCreatureDataBlock {
public:
    int          mPad00[2];      // +0x00
    uint         mCount08;       // +0x08
    void*        mpField0c;      // +0x0c
    cRange       mRange10;       // +0x10
    int          mField18;       // +0x18
    char         mPad1c[0x18];   // +0x1c
    int          mpField34;      // +0x34
    char         mPad38[0x14];   // +0x38
    char         mBuffer4c[0x30]; // +0x4c
    char         mPad7c[4];      // +0x7c

    cCreatureDataBlock* FUN_00c1f580(void* param2, void* param3);   // 0x00c1f580
    void FUN_00b5d220(uint n);                                  // 0x00b5d220
    void FUN_00c142a0(void* a1, void* a2, void* a3, void* a4, void* a5,
                      void* a6, void* a7);                      // 0x00c142a0
};
class cGameData_s00c1_f580 {
public:
    cGameData_s00c1_f580();
    // The primary vtable; slot 0x00..0xbc.  Slot 0xbc is the one the retail
    // teardown calls through "this".
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
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    void* mpSecondaryVtbl;   // +0x04
};
class cPropertyBag {
public:
    int FUN_00c14350();     // 0x00c14350
};
extern "C" uint          __cdecl FNVHash(const char* name, uint start, int flag); // 0x00932e80
extern "C" float         __cdecl SP_GetPropertyT_float(uint hashA, int zero, uint hashB, float fallback); // 0x00bcea30
extern "C" cPropertyBag* __cdecl FUN_00b3d310_s00c1_f580();                  // 0x00b3d310
class cBehaviorTreeData {
public:
    // Class-specific allocation: the retail constructor passes the size, an
    // allocation name and four zeroed debug/alignment parameters.
    static void* operator new(size_t size,
                              const char* name = "Simulator/cBehaviorTreeData",
                              int flags = 0, unsigned align = 0,
                              const char* file = 0, int line = 0);
    cBehaviorTreeData();          // 0x00bcb2a0
    virtual void bt0();
    void FUN_00bcb3d0();          // 0x00bcb3d0
};
class cFieldB48 {
public:
    void FUN_00bc9fe0();   // 0x00bc9fe0
};
class cBundle34 {
public:
    cBundle34();
    virtual void b00();
    void FUN_00cee7e0();    // 0x00cee7e0
    char mPad04[0x20];      // +0x04 -> 0x24
};
class cMotion58 {
public:
    cMotion58();
    virtual void m00();
    void FUN_00abf710();    // 0x00abf710
    char mPad04[0x64];      // +0x04 -> 0x68
};
class cSampleC0 {
public:
    cSampleC0();
    virtual void sc00();
    cCurveHolder* FUN_00c41ec0();     // 0x00c41ec0
    cSampleRef*   FUN_00c421f0();     // 0x00c421f0
    void FUN_00c421b0(int value);  // 0x00c421b0

    char  mPad04[0x4c];      // +0x04
    int   mFlags50;          // +0x50   (bit 0x200 = "armed")
    int   mField54;          // +0x54
    char  mPad58[0x7c];      // +0x58
    void* mpVtblD4;          // +0xd4   (secondary vtable slot)
    int   mFieldD8;          // +0xd8
    int   mFieldDc;          // +0xdc
    char  mPadE0[0x104];     // +0xe0
    float mField1e4;         // +0x1e4
    int   mField1e8;         // +0x1e8
    int   mField1ec;         // +0x1ec
    int   mField1f0;         // +0x1f0
    char  mPad1f4[0x2dc];    // +0x1f4 -> 0x4d0
};
class cInteractionTarget {
public:
    cInteractionTarget();
    virtual void it00();
    void FUN_00ac0450();    // 0x00ac0450
    char mPad04[0x14];      // +0x04 -> 0x18
};
class cCombatant_s00c1_f580 {
public:
    cCombatant_s00c1_f580();
    virtual void cb00();

    char  mPad04[0x28];      // +0x04
    float mHealth2c;         // +0x2c   (creature health)
    int   mField30;          // +0x30
    int   mField34;          // +0x34
    float mCombat38;         // +0x38   (combat strength)
    char  mPad3c[0x8c];      // +0x3c -> 0xc8
};
class cGonzagoTimer {
public:
    cGonzagoTimer();
    virtual void gt00();
    void FUN_00bc3170();     // 0x00bc3170

    char  mPad04[0x1c];      // +0x04
    float mField20;          // +0x20
    int   mField24;          // +0x24
    float mField28;          // +0x28
    float mField2c;          // +0x2c   (100.0f)
};
class cField670 {
public:
    cField670();
    virtual void f670();

    char          mPad04[0x49c];   // +0x04
    unsigned char mByte4a0;        // +0x4a0
    char          mPad4a1[7];      // +0x4a1
    unsigned char mByte4a8;        // +0x4a8
    char          mPad4a9[7];      // +0x4a9
    int           mField4b0;       // +0x4b0
    int           mField4b4;       // +0x4b4
    int           mField4b8;       // +0x4b8
    int           mField4bc;       // +0x4bc
    int           mField4c0;       // +0x4c0
    int           mField4c4;       // +0x4c4
    wchar_t*      mpStr4c8;        // +0x4c8   (empty wide string)
    wchar_t*      mpStr4cc;        // +0x4cc
    wchar_t*      mpStr4d0;        // +0x4d0
    int           mField4d4;       // +0x4d4
    cFieldB48*    mpField4d8;      // +0x4d8
    cBehaviorTreeData* mpTree4dc;  // +0x4dc
    cReleaseable* mpField4e0;      // +0x4e0
    int           mField4e4;       // +0x4e4
    int           mField4e8;       // +0x4e8
    unsigned char mBytes4ec[8];    // +0x4ec
    unsigned char mByte4f4;        // +0x4f4
    unsigned char mBytes4f5[3];    // +0x4f5
    unsigned char mByte4f8;        // +0x4f8
    unsigned char mByte4f9;        // +0x4f9
    char          mPad4fa[2];      // +0x4fa
    void*         mpField4fc;      // +0x4fc
    int           mField500;       // +0x500
    int           mField504;       // +0x504
    char          mPad508[4];      // +0x508
    float         mField50c;       // +0x50c
    float         mField510;       // +0x510
    float         mField514;       // +0x514
    int           mField518;       // +0x518
    int           mField51c;       // +0x51c -> 0x520
};
class cSPCreatureBase_s00c1_f580 : public cGameData_s00c1_f580 {
public:
    cSPCreatureBase_s00c1_f580();
    ~cSPCreatureBase_s00c1_f580();

    void  FUN_00c1fe80();                       // 0x00c1fe80
    void  FUN_00c19940(int value);              // 0x00c19940
    void  FUN_00c13340();                       // 0x00c13340
    float ce80(int a, int b);                   // 0x00c0ce80  (?ce80@CCB@@QAEMHH@Z)
    void  cff0(int value);                       // 0x00c0cff0  (?cff0@CCB@@QAEXH@Z)

    char               mPad08[0x2c];   // +0x08
    cBundle34          mBundle34;      // +0x34
    cMotion58          mMotion58;      // +0x58
    cSampleC0          mSampleC0;      // +0xc0
    cInteractionTarget mTarget590;     // +0x590
    cCombatant_s00c1_f580         mCombatant5a8;  // +0x5a8
    cField670          mField670;      // +0x670
    cGonzagoTimer      mTimerB90;      // +0xb90
    cCurvePointVector  mCurvesBc0;     // +0xbc0
    char               mPadBd0[0x10];  // +0xbd0
    float              mFieldBe0;      // +0xbe0
    float              mFieldBe4;      // +0xbe4
    float              mFieldBe8;      // +0xbe8
    int                mFieldBec;      // +0xbec
    int                mFieldBf0;      // +0xbf0
    int                mFieldBf4;      // +0xbf4
    int                mFieldBf8;      // +0xbf8
    int                mFieldBfc;      // +0xbfc
    int                mFieldC00;      // +0xc00
    int                mFieldC04;      // +0xc04
    int                mFieldC08;      // +0xc08
    int                mFieldC0c;      // +0xc0c
    char               mPadC10[0x18];  // +0xc10
    uint*              mpFixedBegin;   // +0xc28
    uint*              mpFixedEnd;     // +0xc2c
    uint*              mpFixedCapacity;// +0xc30
    char               mPadC34[8];     // +0xc34
    int                mFieldC3c;      // +0xc3c
    char               mFixedBuffer[0x80]; // +0xc40
    void*              mpFieldCc0;     // +0xcc0
    void*              mpFieldCc4;     // +0xcc4
    cCreatureDataBlock mBlockCc8;      // +0xcc8
    cCreatureDataBlock mBlockD68;      // +0xd68
    void*              mpFieldE08;     // +0xe08
    void*              mpFieldE0c;     // +0xe0c
    void*              mpFieldE10;     // +0xe10
    int                mFieldE14;      // +0xe14
    int                mFieldE18;      // +0xe18
    int                mFieldE1c;      // +0xe1c
    char               mPadE20[4];     // +0xe20
    int                mFieldE24;      // +0xe24
    int                mFieldE28;      // +0xe28
    int                mFieldE2c;      // +0xe2c
    char               mPadE30[8];     // +0xe30
    unsigned char      mByteE38;       // +0xe38
    char               mPadE39[3];     // +0xe39
    int                mFieldE3c;      // +0xe3c
    cCurvePointVector  mCurvesE40;     // +0xe40
    char               mPadE4c[8];     // +0xe4c
    int                mFieldE54;      // +0xe54
    float              mFieldE58;      // +0xe58
    float              mFieldE5c;      // +0xe5c
    unsigned char      mBytesE60[4];   // +0xe60
    int                mFieldE64;      // +0xe64
    unsigned char      mByteE68;       // +0xe68
    char               mPadE69[3];     // +0xe69
    int                mFieldE6c;      // +0xe6c
    int                mFieldE70;      // +0xe70
    int                mFieldE74;      // +0xe74
    unsigned char      mByteE78;       // +0xe78
    char               mPadE79[3];     // +0xe79
    cReleaseable*      mpFieldE7c;     // +0xe7c
    int                mFieldE80;      // +0xe80
    int                mFieldE84;      // +0xe84
    int                mFieldE88;      // +0xe88
    int                mFieldE8c;      // +0xe8c
    int                mFieldE90;      // +0xe90
    float              mFieldE94;      // +0xe94
    int                mFieldE98;      // +0xe98
    int                mFieldE9c;      // +0xe9c
    int                mFieldEa0;      // +0xea0
    char               mPadEa4[8];     // +0xea4
    int                mFieldEac;      // +0xeac
    char               mPadEb0[4];     // +0xeb0
    int                mFieldEb4;      // +0xeb4
    char               mPadEb8[0x20];  // +0xeb8
    int                mFieldEd8;      // +0xed8
    int                mFieldEdc;      // +0xedc
    int                mFieldEe0;      // +0xee0
    char               mPadEe4[4];     // +0xee4
    int                mFieldEe8;      // +0xee8
    char               mPadEec[0x20];  // +0xeec
    int                mFieldF0c;      // +0xf0c
    int                mFieldF10;      // +0xf10
    int                mFieldF14;      // +0xf14
    char               mPadF18[4];     // +0xf18
    int                mFieldF1c;      // +0xf1c
    char               mPadF20[0x20];  // +0xf20
    int                mFieldF40;      // +0xf40
    int                mFieldF44;      // +0xf44
    int                mFieldF48;      // +0xf48
    char               mPadF4c[4];     // +0xf4c
    int                mFieldF50;      // +0xf50
    char               mPadF54[0x20];  // +0xf54
    int                mFieldF74;      // +0xf74
    int                mFieldF78;      // +0xf78
    int                mFieldF7c;      // +0xf7c
    int                mFieldF80;      // +0xf80
    void*              mpFieldF84;     // +0xf84
    void*              mpFieldF88;     // +0xf88
    int                mFieldF8c;      // +0xf8c
    unsigned char      mByteF90;       // +0xf90
    char               mPadF91[3];     // +0xf91
    int                mFieldF94;      // +0xf94
    int                mFieldF98;      // +0xf98
    int                mFieldF9c;      // +0xf9c
    int                mFieldFa0;      // +0xfa0
    int                mFieldFa4;      // +0xfa4
    float              mFieldFa8;      // +0xfa8
    float              mFieldFac;      // +0xfac
    float              mFieldFb0;      // +0xfb0
    float              mFieldFb4;      // +0xfb4
    int                mFieldFb8;      // +0xfb8
};
class cCreaturePart {
public:
    void FUN_00c1ffb0(char enable);   // 0x00c1ffb0

    char    mPad00[0xd4];  // +0x00
    Vector3_s00c1_f580 mAnchorD4;     // +0xd4   (first point appended to the anchor vector)
    Vector3_s00c1_f580 mAnchorE0;     // +0xe0   (second point)
    char    mPadEc[0xb0];  // +0xec
    int     mField19c;     // +0x19c   (state bits, bit 2 = "disabled")
    char    mPad1a0[0x88c];// +0x1a0
    Vector3_s00c1_f580* mpCurveBeginA2c; // +0xa2c   (creature's +0xbc0)
    Vector3_s00c1_f580* mpCurveEndA30;   // +0xa30   (creature's +0xbc4)
    char    mPadA34[0x3d4];   // +0xa34
    int     mFieldE08;     // +0xe08   (creature's +0xf9c)
};
class cCreatureFactory {
public:
    void* FUN_00c14e70(void* arg);                  // 0x00c14e70
    void  FUN_00c17350(void* arg, int zero);        // 0x00c17350
    void* FUN_00c1d120(void* a, void* b);           // 0x00c1d120
    void* FUN_00c201a0(char flag, void* a, void* b); // 0x00c201a0
    void  FUN_00c20210(void* a, void* b);           // 0x00c20210
};
class cFactoryObject {
public:
    virtual void o00();
    virtual void o04();
    virtual void o08(void* arg);
    virtual void o0c();
    virtual bool o10();
};
// ---- items of slice s00c1f580 end

// ---- items of slice s00c22010 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVN(n) virtual void pv##n();
class cSpeciesProfile_s00c2_2010;
class cSPCreatureBase_s00c2_2010;
class cInteractionTarget_s00c2_2010;
class cBehaviorStimuliOwner;
class cInteractionAgent;
class cSpeciesProfile_s00c2_2010 {
public:
    uint8_t  mPad000[0x504];    // +0x000
    float    mf0504;            // +0x504
    float    mf0508;            // +0x508
    float    mf050C;            // +0x50c
    uint8_t  mPad510[0x53c - 0x510];
    uint32_t mn053C;            // +0x53c
    uint8_t  mPad540[0x56c - 0x540];
    float    mf056C;            // +0x56c
    uint8_t  mPad570[0x590 - 0x570];
    float    mf0590;            // +0x590
    float    mf0594;            // +0x594
    uint8_t  mPad598[0x634 - 0x598];
    int      mn0634;            // +0x634

    void*    FUN_004d9050(void* pAnim);   // 0x004d9050
    void*    FUN_004d9030(void* pAnim);   // 0x004d9030
    void*    FUN_004d5500(const void* pKey);  // 0x004df550  (species manager method)
};
struct ResourceKey { uint32_t mA; uint32_t mB; uint32_t mC; };
class cSpeciesManager {
public:
    cSpeciesProfile_s00c2_2010* GetProfile(const ResourceKey& key);     // 0x004df550
    cSpeciesProfile_s00c2_2010* GetAvatarProfile();                     // 0x004df420
    void* GetSpeciesArchetype(void* pKey, int nSomething);   // 0x004e0050
    char  GetReplacementKey(const ResourceKey& key, uint32_t nMode, ResourceKey* pOut);  // 0x004df7d0
};
class cLocoWrapper {
public:
    void FUN_00b48770(void* pCreature, int nFlag);   // 0x00b48770
};
class cObj0xA8C {
public:
    uint8_t  mPad0[0x5fc];      // +0x000
    uint32_t mn05FC;            // +0x5fc
};
class cSpeciesArchetype {
public:
    uint8_t mPad0[0x388];       // +0x000
    uint8_t mb0388;             // +0x388
};
class cAnimatingCreature {
public:
    uint8_t mPad0[0x17c];       // +0x000
    void*   mp017C;             // +0x17c
};
class cBehaviorStimuliOwner {
public:
    uint8_t  mPad000[0x88];            // +0x000
    uint8_t  mEntries[0x1d0 - 0x88];   // +0x088
    int      mn01D0;            // +0x1d0
    int      mn01D4;            // +0x1d4
    int      mn01D8;            // +0x1d8
    uint32_t mn01DC;            // +0x1dc

    int GetStimulusId() const { return *(const int*)((const char*)mEntries + mn01DC * 0xac); }
};
class cInteractionTarget_s00c2_2010 {
public:
    uint8_t mPad000[0x34];         // +0x000
    uint8_t mSub34[0x12c - 0x34];  // +0x034 (sub-object passed to FUN_00c15d50)
    int     mnType12C;             // +0x12c
    int     mn0130;                // +0x130
    float   mf0134;                // +0x134
    int     GetAttackState();      // 0x00c35b60
};
class cSub58 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12)
    virtual void vIdx13();       // 0x34
    uint8_t mPad04[0x40 - 4];    // +0x04 .. +0x3f
};
class cGameData_s00c2_2010 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void* vIdx12();      // 0x30
    virtual void  vIdx13(int);   // 0x34
    virtual void  vIdx14(int);   // 0x38
    PVN(15) PVN(16) PVN(17) PVN(18) PVN(19)
    virtual void  vIdx20();      // 0x50
    PVN(21) PVN(22) PVN(23) PVN(24) PVN(25) PVN(26) PVN(27) PVN(28) PVN(29)
    PVN(30) PVN(31)
    virtual float vIdx32(int);   // 0x80
    PVN(33) PVN(34) PVN(35) PVN(36) PVN(37) PVN(38) PVN(39) PVN(40) PVN(41) PVN(42)
    virtual void  vIdx43(int);   // 0xac
    PVN(44)
    virtual void* vIdx45(int);   // 0xb4
    PVN(46)
    PVN(47) PVN(48) PVN(49) PVN(50) PVN(51) PVN(52) PVN(53)
    virtual int   vIdx54();      // 0xd8
    PVN(55) PVN(56) PVN(57) PVN(58) PVN(59)
    virtual void  vIdx60(int);   // 0xf0
    uint8_t mPad00[0x30];        // +0x04 .. +0x33
};
class cInteractionAgent {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11)
    virtual void  ia30(void* pArg);            // 0x30
    PVN(13)
    virtual float GetBundleCapacity(uint32_t nToolType);  // 0x38

    void*  mpListBegin;          // +0x04
    void*  mpListEnd;            // +0x08
    uint8_t mPad0c[0x18 - 0x0c]; // +0x0c
    void*  mp0x18;               // +0x18
    uint8_t mPad1c[0x20 - 0x1c];
    float  mf0x20;               // +0x20
    cSub58 mSub58;               // +0x24
    uint8_t mPad64[0x89 - 0x64]; // +0x64
    uint8_t mb0x89;              // +0x89
    uint8_t mPad8a[0x8c - 0x8a]; // +0x8a

    float FUN_00c22530();                 // 0x00c22530
    void  FUN_010829f0(void* pArg);       // 0x010829f0
    void  FUN_00c22f60(void* pArg);       // 0x00c22f60
};
class cLocomotiveObject {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15)
    virtual void lo40(float fScale);    // 0x40
    PVN(17) PVN(18) PVN(19)
    virtual char lo50();                // 0x50
    PVN(21)
    virtual char lo58();                // 0x58

    uint8_t mPad04[0x6c - 0x04]; // +0x04
    uint8_t mb0x6c;              // +0x6c
    uint8_t mPad6d[0x75 - 0x6d]; // +0x6d
    uint8_t mb0x75;              // +0x75
    uint8_t mPad76[0x4e8 - 0x76];// +0x76

    void FUN_00c226c0(char nFlag);   // 0x00c226c0
};
class cCombatant_s00c2_2010 {
public:
    PVN(0) PVN(1) PVN(2) PVN(3) PVN(4) PVN(5) PVN(6) PVN(7) PVN(8) PVN(9)
    PVN(10) PVN(11) PVN(12) PVN(13) PVN(14) PVN(15) PVN(16) PVN(17) PVN(18)
    PVN(19) PVN(20) PVN(21)
    virtual float GetMaxHealth();        // 0x58

    uint8_t mPad04[0x34 - 0x04]; // +0x04
    void*   mp0x34;              // +0x34
    float   mf0x38;              // +0x38
    uint8_t mPad3c[0x40 - 0x3c]; // +0x3c

    float GetHealthRatio();              // 0x00bfc490
    void  PartialRepair(float fAmount);  // 0x00bfd1a0
    void  SetHealth(float fValue);       // 0x00f924e0
    int   FUN_00c22010();                // 0x00c22010
};
class cSPCreatureBase_s00c2_2010 : public cGameData_s00c2_2010, public cInteractionAgent,
                        public cLocomotiveObject, public cCombatant_s00c2_2010 {
public:
    // own members, from +0x5e8
    uint8_t  mPad5e8[0xa8c - 0x5e8];
    cObj0xA8C* mp0xA8C;          // +0xa8c
    uint8_t  mPadA90[0xb20 - 0xa90];
    cSpeciesProfile_s00c2_2010* mpSpeciesProfile;  // +0xb20
    uint32_t mn0xB24;            // +0xb24
    ResourceKey mKey0xB28;       // +0xb28
    int      mn0xB34;            // +0xb34 (age)
    uint8_t  mPadB38[0xb48 - 0xb38];
    void*    mp0xB48;            // +0xb48  (object with FUN_00bc9fe0)
    cBehaviorStimuliOwner* mpB4C;// +0xb4c
    uint8_t  mPadB50[0xb54 - 0xb50];
    cAnimatingCreature* mp0xB54; // +0xb54
    uint8_t  mPadB58[0xb67 - 0xb58];
    uint8_t  mb0xB67;            // +0xb67
    uint8_t  mPadB68[0xbbc - 0xb68];
    float    mf0xBBC;            // +0xbbc
    uint8_t  mPadBC0[0xe70 - 0xbc0];
    int      mn0xE70;            // +0xe70
    int      mn0xE74;            // +0xe74
    uint8_t  mPadE78[0xe80 - 0xe78];
    void*    mp0xE80;            // +0xe80
    cSpeciesArchetype* mp0xE84;  // +0xe84
    uint8_t  mPadE88[0xfc4 - 0xe88];
    int      mn0xFC4;            // +0xfc4
    uint8_t  mPadFC8[0xff8 - 0xfc8];
    int      mn0xFF8;            // +0xff8
    uint8_t  mPadFFC[0x1004 - 0xffc];
    float    mf0x1004;           // +0x1004
    float    mf0x1008;           // +0x1008
    float    mf0x100C;           // +0x100c
    uint8_t  mPad1010[0x1014 - 0x1010];
    void*    mp0x1014;           // +0x1014
    uint8_t  mPad1018[0x102c - 0x1018];
    int      mn0x102C;           // +0x102c

    // ---- helper calls (thiscall) ----
    void  FUN_00c21bf0(int a, int b);            // 0x00c21bf0  CheckCreatureModel
    char  FUN_00c0c2d0();                        // 0x00c0c2d0  IsDefaultSpecies_
    float FUN_00c0b9c0();                        // 0x00c0b9c0
    void  FUN_00c0b9d0(float fValue);            // 0x00c0b9d0
    char  FUN_00c0bab0();                        // 0x00c0bab0
    char  FUN_00c0ba30();                        // 0x00c0ba30
    int   FUN_00c0c080(int nId);                 // 0x00c0c080  FindIndex
    char  FUN_00b183f0(void* pArg);              // 0x00b183f0
    void  FUN_00c1d640(const char* pVox, int a, int b);  // 0x00c1d640
    void  FUN_00c15d50(void* pArg, int a, int b);        // 0x00c15d50
    void  FUN_00c42350();                        // 0x00c42350
    char  FUN_00c0e0c0(int nType);                       // 0x00c0e0c0
    void  FUN_00c14aa0(void* pStream);                   // 0x00c14aa0
    void  FUN_00c0bc20Write(void* pStream);              // 0x00c0bc20  cSPCreatureBase::Write

    // ---- sliced members ----
    void  FUN_00c22210(int nAge);                        // 0x00c22210
    void  FUN_00c22240();                                // 0x00c22240
    void  FUN_00c222f0(cSpeciesProfile_s00c2_2010* pNew);           // 0x00c222f0
    bool  FUN_00c22470(void* pArg);                      // 0x00c22470
    float GetBaseMaxHitPoints();                         // 0x00c22720
    char  FUN_00c22750();                                // 0x00c22750
    void  FUN_00c227c0();                                // 0x00c227c0
    void  FUN_00c227f0(int x, int y, int z);            // 0x00c227f0
    int   FUN_00c22830(int nValue);                      // 0x00c22830
    void  FUN_00c22870();                                // 0x00c22870
    void  FUN_00c228c0Write(void* pStream);              // 0x00c228c0
    void  FUN_00c22930Read(void* pStream);               // 0x00c22930
    char  FUN_00c229a0();                                // 0x00c229a0
    void  FUN_00c22a30();                                // 0x00c22a30
    char  FUN_00c22a80(cInteractionTarget_s00c2_2010* pTarget);     // 0x00c22a80
    void  FUN_00c22ae0();                                // 0x00c22ae0
    char  FUN_00c22ca0(int nType);                       // 0x00c22ca0
    void  FUN_00c22cb0(uint32_t nVox);                   // 0x00c22cb0
    int   FUN_00c22dd0();                                // 0x00c22dd0
    void  FUN_00c22ee0(void* pObj);                      // 0x00c22ee0
};
class cObj0xB48 {
public:
    void FUN_00bc9fe0();     // 0x00bc9fe0
};
// ---- items of slice s00c22010 end

// @ 0x00c0b000
bool __fastcall FUN_00c0b000(CB* self)
{
  return *(float*)((char*)self + 0xf4) > 0.0f &&
         *(int*)((char*)self + 0xf8) != -1;
}

// @ 0x00c0b030
int* __cdecl FUN_00c0b030(int* stream, char* data)
{
  void* inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  uint64 v = *(uint64*)(data + 8);
  void* s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  WriteUint64(s, &v, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  float u = *(float*)(data + 4);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  WriteUint32(s, &u, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  bool b = *data != 0;
  StreamWriteBool(s, &b, 1);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  b = data[1] != 0;
  StreamWriteBool(s, &b, 1);
  return stream;
}

// @ 0x00c0b100
int* __cdecl FUN_00c0b100(int* stream, char* data)
{
  void* inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  void* s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadUint64(s, data + 8, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadInt32(s, data + 4, 1, 0);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadBool(s, data);

  inner = (*(void* (__thiscall**)(void*))(*(void***)stream)[0x20 / 4])(stream);
  s = (*(void* (__thiscall**)(void*))(*(void***)inner)[0x18 / 4])(inner);
  ReadBool(s, data + 1);
  return stream;
}

// @ 0x00c0b190
bool __cdecl FUN_00c0b190(CB* self, int* info)
{
  if (self == 0) return false;
  if (((self->mGeneralFlags >> 9) & 1) != 0 && info[2] == 0x3d) return false;
  return info[0x120 / 4] != -1;
}

// @ 0x00c0b1c0
bool __cdecl FUN_00c0b1c0(unsigned int arg, unsigned int* out, unsigned int prop)
{
  int count = 0;
  int* data = 0;
  if (!SP_GetPropertyAsUint32Array(prop, arg, &count, &data) || count <= 0)
    return false;
  *out = data[GRAND->RandomUint32Uniform((unsigned int)count)];
  return true;
}

// @ 0x00c0b220
bool __stdcall FUN_00c0b220(unsigned int arg, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode_s00c0_acd0();
  if (mode < 0x1654c00) return false;
  if (mode >= 0x1654c07 && mode != 0x1654c10) return false;
  int index = mode - 0x1654c00;
  if (mode == 0x1654c10) index = 6;
  return FUN_00c0b1c0(arg, out, ((int*)g_168d900)[index]);
}

// @ 0x00c0b270
bool __stdcall FUN_00c0b270(unsigned int arg, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode_s00c0_acd0();
  unsigned int index = (unsigned int)(mode - 0x1654c00);
  if (index > 6) return false;
  int count = 0;
  int* data = 0;
  if (!SP_GetPropertyAsUint32Array(((int*)g_168d900)[index], arg, &count, &data) ||
      count <= 0)
    return false;
  *out = GRAND->RandomUint32Uniform((unsigned int)count);
  return true;
}

// @ 0x00c0b2f0
bool __stdcall FUN_00c0b2f0(unsigned int arg, unsigned int index, unsigned int* out)
{
  int mode = SP_GetCurrentGameMode_s00c0_acd0();
  unsigned int idx = (unsigned int)(mode - 0x1654c00);
  if (idx > 6) return false;
  int count = 0;
  int* data = 0;
  if (!SP_GetPropertyAsUint32Array(((int*)g_168d900)[idx], arg, &count, &data) ||
      count <= 0 || index >= (unsigned int)count)
    return false;
  *out = data[index];
  return true;
}

// @ 0x00c0b380
void* __cdecl FUN_00c0b380(CB* self, TuningObj* tuning)
{
  void* result = tuning->GetAt(0);
  switch (*(int*)((char*)tuning + 8)) {
  case 0x1e: return (void*)0x4bc047d;
  case 0x1f: return (void*)0x4bc0481;
  case 0x20: return (void*)0x5b6db0a;
  case 0x21:
    result = (void*)0x4bc0485;
    if (*(float*)((char*)self->mpSpecies + 0x58c) > 0.0f &&
        GRAND->RandomUint32Uniform(100) < 0x32)
      result = (void*)0x4c074c7;
    break;
  }
  return result;
}

// @ 0x00c0b410
bool __cdecl FUN_00c0b410()
{
  return g_169e288 >= GRAND->RandomDoubleUniform();
}

// @ 0x00c0b440
float __cdecl FUN_00c0b440(unsigned int which)
{
  float value = 1.0f;
  switch (which & ((int)which < 0 ? 0xffffffffu : 0u)) {
  case 0: return g_150c8e4;
  case 1: return g_150c8e8;
  case 2: return g_150c8ec;
  case 3: return g_150c8f0;
  case 4: return g_150c8f4;
  case 5: return g_150c8f8;
  case 6: value = g_150c8fc; break;
  }
  return value;
}

// @ 0x00c0b510
void __cdecl SP_AddSetAnimationTargetModifierA(CB* self, void* target, void* owner, void* extra)
{
  if (target == 0) return;
  int local[8];
  local[0] = (int)target;
  local[1] = 0;
  local[2] = (int)extra;
  local[3] = ++self->mAnimTargetCounter;
  self->mpOrders->Activate(3, 0, self, g_146a32c, local, owner);
}

// @ 0x00c0b570
void __cdecl SP_AddSetAnimationTargetModifierB(CB* self, void* target, float* position)
{
  if (target == 0) return;
  int local[8];
  local[0] = (int)target;
  local[1] = 0;
  local[2] = -1;
  local[3] = ++self->mAnimTargetCounter;
  ((float*)&local[4])[0] = position[0];
  ((float*)&local[4])[1] = position[1];
  ((float*)&local[4])[2] = position[2];
  self->mpOrders->Activate(3, 0, self, g_146a32c, local, 0);
}

// @ 0x00c0b5e0
void __cdecl FUN_00c0b5e0(CB* self)
{
  if (g_168db6c == 0) {
    g_168db6c = 1;
    g_168d9bc = 0;
    g_168da00 = 1;
    g_168da44 = 2;
    g_168da88 = 3;
    g_168dacc = 4;
    g_168db10 = 5;
  }
  void* p = operator new(0x230, "Simulator/cModifiers", 0, 0, 0, 0);
  self->mpOrders = p != 0
      ? (AgentOrderManager*)((ModifiersCtorHelper*)p)->Exist(&g_168d998)
      : 0;
}

// @ 0x00c0b670
int __thiscall CB::Query(unsigned int id)
{
  CB* self = this;
  if (id == 0xce9f6639) return (int)self;
  int r = ((F_abf740*)((char*)self + 0x58))->f(id);
  if (r != 0) return r;
  r = ((F_cee250*)((char*)self + 0x34))->f(id);
  if (r != 0) return r;
  r = ((F_c41d00*)((char*)self + 0xc0))->f(id);
  if (r != 0) return r;
  r = ((F_ac0320*)((char*)self + 0x590))->f(id);
  if (r != 0) return r;
  r = ((F_b18460*)self)->f(id);
  if (r != 0) return r;
  r = ((F_bfc380*)((char*)self + 0x5a8))->f(id);
  if (r != 0) return r;
  r = ((F_c7d050*)((char*)self + 0x670))->f(id);
  if (r != 0) return r;
  return ((F_c884f0*)((char*)self + 0xc0))->f(id);
}

// @ 0x00c0b710
void __fastcall FUN_00c0b710(CB* self)
{
  self->m_b8c = (int)(g_1687a30 * 1000.0f);
}

// @ 0x00c0b780
bool __fastcall FUN_00c0b780(CB* self)
{
  return self->mpSpecies->m608 > 0;
}

// @ 0x00c0b7a0
bool __fastcall FUN_00c0b7a0(CB* self)
{
  return self->mpSpecies->m60c > 0;
}

// @ 0x00c0b7c0
bool __thiscall CB::CheckTargetA(void* target)
{
  CB* self = this;
  if (self->mpSpecies->m60c > 0 && ((F_c35d20*)target)->f())
    return true;
  if (self->mpSpecies->m608 > 0 && ((F_c35d40*)target)->f())
    return true;
  return false;
}

// @ 0x00c0b810
bool __thiscall CB::CheckTargetB(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base == 0) return false;
  int r = ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg);
  return r == 2 || r == 5 || r == 3 || r == 4;
}

// @ 0x00c0b860
bool __thiscall CB::CheckTargetC(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base == 0) return false;
  int r = ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg);
  return r == 2 || r == 5;
}

// @ 0x00c0b8a0
bool __thiscall CB::CheckTargetD(void* argp)
{
  CB* self = this;
  unsigned int arg = (unsigned int)(size_t)argp;
  int base = FUN_00b3d4c0(self);
  if (base == 0) return false;
  return ((F_ba3f90*)base)->f((char*)self + 0xb28, self, arg) == 1;
}

// @ 0x00c0b8e0
int __thiscall CB::TimerDelta(CB* other)
{
  CB* self = this;
  return self->m_b88 - other->m_b88;
}

// @ 0x00c0b910
void __thiscall Simulator::cCreatureBase::SetLastInteractionEffect(unsigned int value)
{
  if (this->mLastInteractionEffect != value) {
    this->mLastInteractionEffect = value;
    this->mbUpdateInteractionEffect = true;
  }
}

// @ 0x00c0b930
bool __thiscall Simulator::cCreatureBase::ForgetUpdateInteractionEffect()
{
  bool old = this->mbUpdateInteractionEffect;
  this->mbUpdateInteractionEffect = false;
  return old;
}

// @ 0x00c0b950
void __fastcall FUN_00c0b950(CB* self)
{
  self->m_bBC = g_1687a00;
}

// @ 0x00c0b9a0
void __thiscall Simulator::cCreatureBase::func90h()
{
  this->mbDead = false;
  this->m_bBC = g_1687a00;
}

// @ 0x00c0b9d0
void __thiscall CB::ClampHunger(float value)
{
  value = std::min(std::max(value, g_1687a04), g_1687a00);
  this->m_bBC = value;
}

// @ 0x00c0ba10
void __fastcall FUN_00c0ba10(CB* self)
{
  self->m_bB8 = -g_1687a2c;
}

// @ 0x00c0ba30
bool __fastcall FUN_00c0ba30(CB* self)
{
  if (g_1687a0c > self->m_bBC) return true;
  if (FUN_00bfc490((char*)self + 0x5a8) * 100.0f < g_1687a0c) {
    return true;
  }
  return false;
}

// @ 0x00c0ba70
bool __fastcall FUN_00c0ba70(CB* self)
{
  if (g_1687a10 > self->m_bBC) return true;
  if (FUN_00bfc490((char*)self + 0x5a8) * 100.0f < g_1687a10) {
    return true;
  }
  return false;
}

// @ 0x00c0bab0
bool __fastcall FUN_00c0bab0(CB* self)
{
  if (g_1687a14 > self->m_bBC) return false;
  if (g_1687a14 > FUN_00bfc490((char*)self + 0x5a8) * 100.0f) return false;
  return true;
}

// @ 0x00c0bb20
float __fastcall FUN_00c0bb20(CB* self)
{
  float value;
  if (self->mp_e84 != 0)
    value = *(float*)((char*)self->mp_e84 + 0x368);
  else
    value = *(float*)((char*)self->mpSpecies + 0x570);
  if (self->m_b34 == 1) {
    if ((self->mGeneralFlags & 1) == 1)
      value = g_150c88c * value;
  } else {
    value = g_150c888 * value;
  }
  return value;
}

// @ 0x00c0bb90
bool __fastcall FUN_00c0bb90(CB* self)
{
  return FUN_00bfc490((char*)self + 0x5a8) * g_1687a00 < g_1687a10;
}

// @ 0x00c0bbe0
void __fastcall FUN_00c0bbe0(CB* self)
{
  void* base = FUN_00b3d310(self);
  ((F_b48770*)base)->f(self, 1);
}

// @ 0x00c0bc00
char* __fastcall FUN_00c0bc00(CB* self)
{
  if (self->mpSpecies != 0)
    return (char*)self->mpSpecies + 0x504;
  return (char*)self + 0xb28;
}

// @ 0x00c0be70
bool __cdecl FUN_00c0be70(int x)
{
  return x == 0x25b3bc0 || x == 0x772ff58 || x == 0x7995fdc || x == 0x7982fb2 || x == 0x7b5063e;
}

// @ 0x00c0bee0
void __thiscall C::C0bee0(int a, int b)
{
  ((CCommunityStub*)this)->func60h(a, b);
  *(uint8_t*)((char*)this + 0xa9d) = 1;
}

// @ 0x00c0c010
float __thiscall C::GetA()
{
  void* p = *(void**)((char*)this + 0xe84);
  if (p) { float f = *(float*)((char*)p + 0x350); if (f >= 0.0f) return f; }
  return gF_150c8b8;
}

// @ 0x00c0c040
float __thiscall C::GetB()
{
  void* p = *(void**)((char*)this + 0xe84);
  if (p) { float f = *(float*)((char*)p + 0x354); if (f >= 0.0f) return f; }
  return gF_150c8b4;
}

// @ 0x00c0c080
int __thiscall C::FindIndex(int key)
{
  uint32_t n = (*(uint32_t(__thiscall*)(void*))((*(void***)this)[0xb0/4]))(this);
  for (uint32_t i = 0; i < n; ++i) {
    void* e = (*(void*(__thiscall*)(void*, uint32_t))((*(void***)this)[0xb4/4]))(this, i);
    if (*(int*)((char*)e + 8) == key) return (int)i;
  }
  return -1;
}

// @ 0x00c0c0d0
float __thiscall C::Get574()
{ return *(float*)((char*)*(void**)((char*)this + 0xa60) + 0x574); }

// @ 0x00c0c0e0
bool __thiscall C::Flag388()
{
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x388) != 0;
}

// @ 0x00c0c100
bool __thiscall C::Flag389()
{
  void* p = *(void**)((char*)this + 0xe84);
  return p != 0 && *(char*)((char*)p + 0x389) != 0;
}

// @ 0x00c0c140
void __thiscall C::CallFind13()
{ if (FindIndex(0xd) == -1) FindIndex(0x52); }

// @ 0x00c0c160
void __thiscall C::CallFind27()
{ if (FindIndex(0x27) == -1) FindIndex(0x50); }

// @ 0x00c0c180
void __thiscall C::SetE84(void* p)
{
  *(void**)((char*)this + 0xe84) = p;
  if (p) *(void**)((char*)this + 0xe80) = *(void**)((char*)p + 0x10);
}

// @ 0x00c0c1c0
float __thiscall C::Speed1(char b)
{
  float v = 1.0f;
  if (*(int*)((char*)this + 0xb34) != 1 && b == 0) v = gF_150c8cc;
  return v;
}

// @ 0x00c0c200
void __thiscall C::C200(float f)
{
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10 && *(int*)((char*)g_16c7aa4 + 0xcc) == 2) {
    if (this) FUN_00ef1930((char*)this + 0x5a8, f);
    else FUN_00ef1930(0, f);
  }
}

// @ 0x00c0c2d0
void __thiscall C::IsDefaultSpecies_()
{
  FUN_00401090();
  void* p = FUN_004df420();
  *(void**)((char*)this + 0); // no-op to keep this used
}

// @ 0x00c0c310
uint32_t __thiscall C::FlagF()
{ return (*(uint32_t*)((char*)this + 0xb58) >> 0xf) & 1; }

// @ 0x00c0c3e0
C* __thiscall C::CopyRec(void* srcv)
{
  uint32_t* s = (uint32_t*)srcv;
  uint32_t* d = (uint32_t*)this;
  d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3]; d[4]=s[4];
  *(float*)(d+5) = *(float*)(s+5);
  *(uint8_t*)(d+6) = *(uint8_t*)(s+6);
  d[7]=s[7];
  void* o = (void*)s[8];
  d[8]=(uint32_t)o;
  if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
  return this;
}

// @ 0x00c0c440
void* __cdecl FUN_00c0c440(uint32_t* first, uint32_t* last, uint32_t* dst)
{
  while (first != last) {
    if (dst) {
      dst[0]=first[0]; dst[1]=first[1]; dst[2]=first[2]; dst[3]=first[3];
      dst[4]=first[4]; dst[5]=first[5];
      *(uint8_t*)(dst+6) = *(uint8_t*)(first+6);
      dst[7]=first[7];
      void* o = (void*)first[8];
      dst[8]=(uint32_t)o;
      if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
    }
    first += 9; dst += 9;
  }
  return dst;
}

// @ 0x00c0c4b0
C* __thiscall C::QuatHalf(float a)
{
  float* q = (float*)this;
  float x=q[0], y=q[1], z=q[2], w=q[3];
  float c = cosf(a * 0.5f);
  float s = sinf(a * 0.5f);
  q[0] = x*c + w*0.0f - z*s + y*0.0f;
  q[1] = y*c + w*s + z*0.0f - x*0.0f;
  q[2] = z*c - y*0.0f + x*s + w*0.0f;
  q[3] = w*c - x*0.0f - y*s - z*0.0f;
  return this;
}

// @ 0x00c0c5b0
bool __cdecl C5b0(int obj, int b, int* out)
{
  if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
    int r = FUN_00ebfd50(obj, b);
    *out = r;
    return r != b;
  }
  void* p = *(void**)((char*)obj + 0xe84);
  if (p && *(char*)((char*)p + 0x388) != 0) {
    void* mgr = *(void**)0x168d900;
    if (FUN_00c0b1c0((void*)b, (void*)out, *(int*)((char*)mgr + 0x1c))) return true;
  }
  return FUN_00c0b220((void*)b, (void*)out);
}

// @ 0x00c0ce30
int __thiscall C::RelationIndex(int idx, char b)
{
  if (*(int*)((char*)this + 0xb20) == 0) return 0;
  if (idx == 0) return 0;
  int v = Cdb0() + g_15716d8[idx];
  if (b == 0) v += *(int*)((char*)this + 0xfa0);
  if (v < 0) return 0;
  return v < 6 ? v : 5;
}

// @ 0x00c0cf50
void __thiscall CCB::cf50()
{
    G32((char*)this + 0xfa8) = 0;
    GF((char*)this + 0xfac) = ce80(1, 1);
    GF((char*)this + 0xfb0) = ce80(2, 1);
    GF((char*)this + 0xfb4) = ce80(3, 1);
    G32((char*)this + 0x2a4) = G32((char*)this + 0xfb0);
}

// @ 0x00c0cfa0
float __thiscall CCB::cfa0(int index, char flag)
{
    if (*(char*)((char*)this + 0xbb0) != 0)
        return ce80(2, 1) + GF(0x150c900);
    if (flag != 0)
        return GF((char*)this + 0xfa8 + index * 4);
    return ce80(index, 0);
}

// @ 0x00c0cff0
void __thiscall CCB::cff0(int param)
{
    G32((char*)this + 0xf98) = param;
    float v;
    if (*(char*)((char*)this + 0xbb0) != 0)
        v = ce80(2, 1) + GF(0x150c900);
    else
        v = ce80(param, 0);
    GF((char*)this + 0x2a0) = v;
}

// @ 0x00c0d050
int __thiscall CCB::d050(float param)
{
    int iVar1 = 0;
    do {
        if (iVar1 != 1) {
            float f;
            if (*(char*)((char*)this + 0xbb0) == 0) f = ce80(iVar1, 0);
            else f = ce80(2, 1) + GF(0x150c900);
            if (f >= param) return iVar1;
        }
        ++iVar1;
        if (iVar1 > 3) return 3;
    } while (true);
}

// @ 0x00c0d0c0
void __thiscall CCB::d0c0(uint32_t param_2, char param_3)
{
    bool bVar3;
    if (param_2 < 8) {
        uint32_t bit = 1u << (param_2 & 0x1f);
        bVar3 = (G32((char*)this + 0xfa4) & bit) != 0;
        if (param_3 == 0) G32((char*)this + 0xfa4) &= ~bit;
        else G32((char*)this + 0xfa4) |= bit;
    } else bVar3 = false;
    if (param_3 == bVar3) return;
    int iVar1 = (param_3 == 0 || bVar3) ? -1 : 1;
    int* pfa0 = (int*)((char*)this + 0xfa0);
    switch (param_2) {
    case 0: *pfa0 += iVar1; break;
    case 1: case 2: case 3: *pfa0 -= iVar1; break;
    case 4: iVar1 = -iVar1 * 2; *pfa0 += iVar1; break;
    case 5: *pfa0 += (*(int*)((char*)*(void**)((char*)this + 0xb20) + 0x5d0)) * iVar1; break;
    case 6: iVar1 = -iVar1 * 4; *pfa0 += iVar1; break;
    case 7: *pfa0 += iVar1 * 2; break;
    }
    float v;
    if (*(char*)((char*)this + 0xbb0) == 0) v = ce80(G32((char*)this + 0xf98), 0);
    else v = ce80(2, 1) + GF(0x150c900);
    GF((char*)this + 0x2a0) = v;
}

// @ 0x00c0d1e0
void __thiscall CCB::d1e0(int param)
{
    void* p = *(void**)((char*)this + 0xb54);
    if (p != 0) ((F_a02bf0*)p)->f(param, 1);
}

// @ 0x00c0d200
void __thiscall CCB::d200(int param_2, int param_3)
{
    if (*(int*)((char*)this + 0xb54) != 0) {
        void* eax = *(void**)((char*)param_2 + 0xb54);
        if (eax != 0) {
            void* ths = *(void**)((char*)this + 0xb54);
            if (param_3 != -1) ((F_a062a0*)ths)->f((int)eax, param_3);
            else ((F_a06250*)ths)->f((int)eax);
        }
    }
}

// @ 0x00c0d240
void __thiscall CCB::d240()
{
    void* p = *(void**)((char*)this + 0xb54);
    if (p != 0) {
        float local_14 = *(float*)((char*)p + 0x3c) * GF(0x1473c70);
        float r = (*(float(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x74 / 4]))((char*)this + 0xc0);
        float af[2]; af[0] = r;
        float* pf = &local_14;
        if (local_14 <= r) pf = af;
        float neg = -(*pf);
        *(uint32_t*)((char*)p + 0x154) = 1;
        void* q = *(void**)((char*)this + 0xb54);
        *(uint32_t*)((char*)q + 0x164) = 0;
        *(float*)((char*)q + 0x168) = neg;
        *(uint32_t*)((char*)q + 0x16c) = 0;
        void* r2 = *(void**)((char*)this + 0xb54);
        if (*(int*)((char*)r2 + 0x15c) != 0) {
            void* contained = *(void**)((char*)r2 + 0x15c);
            *(uint32_t*)((char*)r2 + 0x15c) = 0;
            ((F_a05270*)contained)->Release();
        }
    }
    *(uint8_t*)((char*)this + 0xb66) = 0;
}

// @ 0x00c0d340
void __thiscall CCB::d340(int param_2)
{
    void* iVar2 = *(void**)((char*)param_2 + 0x34);
    *(uint32_t*)((char*)param_2 + 0x130) = 0;
    float* u = (float*)(*(float*(__thiscall**)(void*))((*(void***)((char*)this + 0x8c))[0x2c / 4]))((char*)this + 0x8c);
    void* self2 = (char*)param_2 + 0x34;
    (*(void(__thiscall**)(void*, void*))(*(void**)((char*)iVar2 + 0x38)))(self2, u);
    void* piVar3 = *(void**)((char*)this + 0x18);
    void* piVar1 = (char*)this - 0x34;
    if (piVar1 != piVar3) {
        if (piVar1) (*(void(__thiscall**)(void*))((*(void***)piVar1)[0]))(piVar1);
        *(void**)((char*)this + 0x18) = piVar1;
        if (piVar3) (*(void(__thiscall**)(void*))((*(void***)piVar3)[1]))(piVar3);
    }
}

// @ 0x00c0dd40
void __thiscall CCB::dd40(float* param_2)
{
    ((F_c88670*)this)->f(param_2);
    char* eax = *(char**)((char*)this + 0xa94);
    if (eax != 0) {
        *(int*)(eax + 4) = *(int*)param_2;
        *(int*)(eax + 8) = *(int*)((char*)param_2 + 4);
        *(int*)(eax + 0xc) = *(int*)((char*)param_2 + 8);
    }
}

// @ 0x00c0ddb0
void __thiscall CCM::ddb0(float* param_2)
{
    ((F_58*)this)->f(param_2);
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        *(int*)(p + 0x10) = *(int*)((char*)param_2 + 4);
        GF(p + 0x14) = -param_2[0];
        *(int*)(p + 0x18) = *(int*)((char*)param_2 + 0xc);
        GF(p + 0x1c) = -param_2[2];
    }
}

// @ 0x00c0e040
void* __thiscall CCM::e040()
{
    char* c = *(char**)((char*)this + 0xb54);
    uint32_t local_4 = 0;
    if (c == 0) return (void*)local_4;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    return (void*)local_4;
}

// @ 0x00c0e070
bool __thiscall CCM::e070(int param_2)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0 && *(int*)(c + 0x184) != 0) {
        char* r = (char*)FUN_009ff6f0(*(void**)(c + 0x184), (void*)param_2);
        if (r != 0) return *(int*)(r + 0xc0) != 0;
        return 0;
    }
    return 1;
}

// @ 0x00c0e0c0
bool __thiscall CCM::e0c0(int param_2)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c == 0) return 0;
    uint32_t local_4 = 0;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    if ((int)local_4 == param_2) return 1;
    if (!((F_a02b40*)c)->f(param_2)) return 0;
    return 1;
}

// @ 0x00c0e120
char __thiscall CCM::e120(int param_2)
{
    char* p = *(char**)(*(char**)((char*)this + 0xb54) + 0x184);
    int* pu = (int*)(p + 0xf4c);
    for (int i = 0; i < 0x10; ++i) {
        int v = *pu;
        if (v != -1 && *(int*)(v * 0xf0 + (int)p + 0xe0) == param_2) return 1;
        ++pu;
    }
    return 0;
}

// @ 0x00c0e370
void* __thiscall CCM::e370()
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c == 0) return 0;
    uint32_t local_4 = 0;
    void* vt = *(void**)c;
    ((void(__thiscall*)(void*, int, int, void*, int))(*(void**)((char*)vt + 0x58)))(
        c, 0, 0, &local_4, 0);
    return (void*)local_4;
}

// @ 0x00c0e3a0
float __thiscall CCM::e3a0()
{
    char* c = *(char**)((char*)this + 0xb54);
    float local_4 = 0.0f;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, void*, int, int))(*(void**)((char*)vt + 0x58)))(
            c, 0, &local_4, 0, 0);
    }
    return local_4;
}

// @ 0x00c0e3d0
char __thiscall CCM::e3d0()
{
    char* c = *(char**)((char*)this + 0xa94);
    if (c != 0) {
        uint32_t local_4 = 0;
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
        if (local_4 != 0) {
            void* lm = FUN_0067cb20();
            char* r = (char*)((void*(__thiscall*)(void*, uint32_t))(*(void**)((char*)*(void**)lm + 0x40)))(
                lm, local_4);
            if (r != 0) return *(char*)(r + 0x1d);
        }
    }
    return 1;
}

// @ 0x00c0e420
char __thiscall CCM::e420()
{
    void* lm = FUN_0067cb20();
    char* c = *(char**)((char*)this + 0xb54);
    uint32_t local_4 = 0;
    if (c != 0) {
        void* vt = *(void**)c;
        ((void(__thiscall*)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
    }
    char* r = (char*)((void*(__thiscall*)(void*, uint32_t))(*(void**)((char*)*(void**)lm + 0x40)))(
        lm, local_4);
    if (r != 0 && *(char*)(r + 0x1c) != 0) return 1;
    return 0;
}

// @ 0x00c0e480
double SP::cSPCreatureBase::GetTime()
{
    if ((G32(0x168db88) & 1) == 0) {
        G32(0x168db88) |= 1;
        ((F_sw*)0x168db70)->Ctor(4, 1);
        FUN_011e07ef((void*)0x13c3580);
    }
    unsigned long long u = ((F_sw*)0x168db70)->GetElapsedTime();
    double d = (double)(long long)u;
    return (float)(d * *(double*)0x13f6560);
}

// @ 0x00c0e4f0
float __thiscall CCM::e4f0()
{
    if (SP_GetCurrentGameMode() == (void*)0x1654c10
        && *(int*)(G32(0x16c7aa4) + 0xcc) == 2
        && this != 0) {
        int r = (*(int(__thiscall**)(void*, int))((*(void***)this)[0xc / 4]))(this, 0xd0036e08);
        if (r != 0 && ((G32((char*)this + 0xb58) >> 9) & 1) == 0) {
            int* q = (int*)((F_c04750*)(void*)r)->f();
            if (q != 0) return GF((char*)q + 0x484);
        }
    }
    char* e = *(char**)((char*)this + 0xe84);
    if (e != 0) {
        float v = GF(e + 0x34c);
        if (v >= 0.0f) return v;
    }
    return GF(0x150c8bc);
}

// @ 0x00c0e5f0
void __thiscall CCM::e5f0(float param_2)
{
    char* p = *(char**)((char*)this + 0xa94);
    if (p != 0) {
        GF(p + 0x3c) = param_2;
        SP_GetCurrentGameMode();
    }
    if (param_2 != GF((char*)this + 0x64)) {
        GF((char*)this + 0x64) = param_2;
        GF((char*)this + 0x7c) = param_2;
        ((F_d9b0*)((char*)this - 0xc0))->f();
    }
}

// @ 0x00c0e640
void __thiscall CCM::e640(int param_2)
{
    char* p = *(char**)((char*)this + 0xb54);
    if (p != 0) *(int*)(p + 0x170) = param_2;
}

// @ 0x00c0e660
int __thiscall CCM::e660()
{
    char* b = *(char**)((char*)this + 0xb20);
    return (*(int*)(b + 0x6d8) - *(int*)(b + 0x6d4)) >> 2;
}

// @ 0x00c0e680
int __thiscall CCM::e680(int param_2)
{
    if (param_2 == -1) return 0;
    char* b = *(char**)((char*)this + 0xb20);
    return *(int*)(*(int*)(b + 0x6d4) + param_2 * 4);
}

// @ 0x00c0eae0
void Simulator_cCreatureBase::SteerTowards(const Vec3* pTarget, int nDelta)
{
    (void)nDelta;
    Vec3* pPosition = GetPosition();
    Vec3 direction;
    direction.mX = pTarget->mX - pPosition->mX;
    direction.mY = pTarget->mY - pPosition->mY;
    direction.mZ = pTarget->mZ - pPosition->mZ;

    float fDistance = direction.mX * direction.mX + direction.mY * direction.mY +
                      direction.mZ * direction.mZ;
    fDistance = (float)__builtin_sqrtf(fDistance);

    if (fDistance <= 0.0001f) {
        Vec3 local;
        local.mX = -1.0f;
        local.mY = 0.0f;
        local.mZ = 0.0f;
        Vec3* pRotated = RotateVectorAround(&local, &local, &mpAnimatedCreature->mOrientation);
        if (!IsVectorValid(&local))
            (void)pRotated;
    } else {
        float fInv = 1.0f / fDistance;
        direction.mX *= fInv;
        direction.mY *= fInv;
        direction.mZ *= fInv;
    }

    if (mpAnimatedCreature != nullptr) {
        CreatureUpdateTransform(&direction, 1);
    }
}

// @ 0x00c0ed60
void Simulator_cCreatureBase::SetCreatureTarget(cCombatant* pTarget, bool bFlag, int nIntention)
{
    mTargetFlag = bFlag ? 1 : 0;
    mIntentionTowardsTarget = nIntention;

    if (mpCombatantTarget == pTarget)
        return;

    if (pTarget == nullptr) {
        if (mpCombatantTarget != nullptr) {
            IRefCounted* pOld = mpCombatantTarget;
            mpCombatantTarget = nullptr;
            pOld->Release();
        }
        if (mpAnimatedCreature != nullptr && mpAnimatedCreature->mState == 0)
            IsAnimationQueuedOrCurrent(this);
    } else {
        cCombatant* pOld = mpCombatantTarget;
        if (pTarget != pOld) {
            pTarget->AddRef();
            mpCombatantTarget = pTarget;
            if (pOld != nullptr)
                pOld->Release();
        }
    }

    if (IsVisible() && mpCombatantTarget != nullptr) {
        uint32_t nTargetPolitical = mpCombatantTarget->GetPoliticalID();
        if (nTargetPolitical != GetOwnPoliticalID(this) && GetCurrentGameMode_s00c0_eae0() == &gGameModeTribe) {
            CreatureAddRelation(pTarget);
            CreaturePlayAttackAnimation();
        }
    }
}

// @ 0x00c0ee70
void* Simulator_cCreatureBase::GetTargetAsCreature()
{
    if (mpCombatantTarget != nullptr)
        return mpCombatantTarget->QueryTarget((const void*)0xce9f6639);
    return nullptr;
}

// @ 0x00c0ee90
void Simulator_cCreatureBase::ApplyCombatTarget()
{
    if (mpSteeringTarget == nullptr)
        return;
    IRefCounted* pTarget = (IRefCounted*)mpSteeringTarget->Query(nullptr);
    if (pTarget == nullptr)
        return;
    if (GetCurrentGameMode_s00c0_eae0() == &gGameModeCity)
        mpSteeringTarget = pTarget;
}

// @ 0x00c0eec0
void Simulator_cCreatureBase::UpdateSteering(int nDelta, float fAmount)
{
    mSteeringTimer += nDelta;

    if (fAmount == 0.0f) {
        mSteeringTimer = 0;
        mPathValid = 0;
        return;
    }

    if (mSteeringTimer > 1000u) {
        mSteeringTimer = 0;
        mPathValid = 0;
    }

    Vec3 offset;
    offset.mX = 0.0f;
    offset.mY = 0.0f;
    offset.mZ = 0.0f;

    float fScale = 1.0f;
    if ((mSteeringFlags >> 9 & 1) != 0 && mpSteeringModel != nullptr && mOrientationValid != 0) {
        Vec3* pDirection = GetDirection();
        if (pDirection->mX * pDirection->mX + pDirection->mY * pDirection->mY +
                pDirection->mZ * pDirection->mZ == 0.0f) {
            offset.mX = 0.0f;
            offset.mY = 1.0f;
        }
    }

    float fSpeed = *(float*)((uint8_t*)mpSteeringModel + 0x548);
    if (mOrientationValid == 0) {
        Vec3 velocity;
        Vec3* pDirection = GetDirection();
        float fLen = pDirection->mX * pDirection->mX + pDirection->mY * pDirection->mY +
                     pDirection->mZ * pDirection->mZ;
        float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
        velocity.mX = pDirection->mX * fInv;
        velocity.mY = pDirection->mY * fInv;
        velocity.mZ = pDirection->mZ * fInv;
        float fDot = velocity.mX * offset.mX + velocity.mY * offset.mY + velocity.mZ * offset.mZ;
        if (fDot < 0.0f)
            fSpeed += fDot;
    }

    Vec3* pForward = GetDirection();
    float fLen = pForward->mX * pForward->mX + pForward->mY * pForward->mY +
                 pForward->mZ * pForward->mZ;
    float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
    float fAmountScaled = (float)mSteeringTimer;
    offset.mX += pForward->mX * fInv * fSpeed * fAmountScaled * 0.001f * fScale;
    offset.mY += pForward->mY * fInv * fSpeed * fAmountScaled * 0.001f * fScale;
    offset.mZ += pForward->mZ * fInv * fSpeed * fAmountScaled * 0.001f * fScale;

    CreatureMoveStep(&offset, 0);
}

// @ 0x00c0f280
void Simulator_cCreatureBase::Hide()
{
    if (mpAnimatedCreature != nullptr) {
        mpAnimatedCreature->mFlags &= ~1u;
        *(uint8_t*)((uint8_t*)mpAnimatedCreature + 0x64) = 0;
        HideCreature(true);
    }
}

// @ 0x00c0f2b0
void Simulator_cCreatureBase::Show()
{
    if (mpAnimatedCreature != nullptr) {
        mpAnimatedCreature->mFlags |= 1u;
        *(uint8_t*)((uint8_t*)mpAnimatedCreature + 0x64) = 1;
    }
}

// @ 0x00c0f2e0
bool Simulator_cCreatureBase::TraceTo(const Vec3* pFrom, const Vec3* pTo, Vec3* pOut)
{
    Vec3 direction;
    direction.mX = pTo->mX - pFrom->mX;
    direction.mY = pTo->mY - pFrom->mY;
    direction.mZ = pTo->mZ - pFrom->mZ;

    float fLen = direction.mX * direction.mX + direction.mY * direction.mY +
                 direction.mZ * direction.mZ;
    float fInv = 1.0f / (float)__builtin_sqrtf(fLen + 1e-08f);
    direction.mX *= fInv;
    direction.mY *= fInv;
    direction.mZ *= fInv;

    Vec3 hit;
    hit.mX = 0.0f;
    hit.mY = 0.0f;
    hit.mZ = 0.0f;

    if (!TraceTerrain(pFrom, &direction, nullptr, &hit.mX, 0, 0))
        return false;

    *pOut = hit;

    float fToHit = (pFrom->mX - pOut->mX) * (pFrom->mX - pOut->mX) +
                   (pFrom->mY - pOut->mY) * (pFrom->mY - pOut->mY) +
                   (pFrom->mZ - pOut->mZ) * (pFrom->mZ - pOut->mZ);
    float fToEnd = (pFrom->mX - pTo->mX) * (pFrom->mX - pTo->mX) +
                   (pFrom->mY - pTo->mY) * (pFrom->mY - pTo->mY) +
                   (pFrom->mZ - pTo->mZ) * (pFrom->mZ - pTo->mZ);
    return __builtin_sqrtf(fToHit) <= __builtin_sqrtf(fToEnd);
}

// @ 0x00c0f490
void Simulator_cCreatureBase::ResetCombatants()
{
    mIntentionTowardsTarget = 0;

    if (mpSenseObject != nullptr) {
        mpSenseObject->Query(nullptr);
        IRefCounted* pOld = mpSenseObject;
        mpSenseObject = nullptr;
        pOld->Release();
    }
    if (mpSteeringTarget != nullptr) {
        mpSteeringTarget->Query(nullptr);
        IRefCounted* pOld = mpSteeringTarget;
        mpSteeringTarget = nullptr;
        pOld->Release();
    }
    if (mpCombatantTarget != nullptr) {
        IRefCounted* pOld = mpCombatantTarget;
        mpCombatantTarget = nullptr;
        pOld->Release();
    }
}

// @ 0x00c0f510
bool Simulator_cCreatureBase::IsSlotEmpty(uint32_t nIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    if (nCount <= nIndex)
        return true;
    if (mpSlotsBegin[nIndex].mpCombatant == nullptr && mpSlotsBegin[nIndex].mSecondaryKey == 0)
        return true;
    return false;
}

// @ 0x00c0f570
int Simulator_cCreatureBase::CountValid()
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    int nValid = 0;
    for (int i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            ++nValid;
    }
    return nValid;
}

// @ 0x00c0f5f0
bool Simulator_cCreatureBase::IsFull()
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    return CountValid() == nCount;
}

// @ 0x00c0f620
uint32_t Simulator_cCreatureBase::FindFirstEmpty()
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant == nullptr && mpSlotsBegin[i].mSecondaryKey == 0)
            return i;
    }
    return 0xffffffff;
}

// @ 0x00c0f6b0
uint32_t Simulator_cCreatureBase::FindRandomEmpty()
{
    int nValid = CountValid();
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    int nEmpty = nCount - nValid;
    uint32_t nPick = RandomGet().RandomUint32Uniform(nEmpty);
    int nSeen = 0;
    for (int i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant == nullptr && mpSlotsBegin[i].mSecondaryKey == 0) {
            if (nSeen == (int)nPick)
                return (uint32_t)i;
            ++nSeen;
        }
    }
    return 0xffffffff;
}

// @ 0x00c0f780
uint32_t Simulator_cCreatureBase::FindFirstValid()
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            return i;
    }
    return 0xffffffff;
}

// @ 0x00c0f810
uint32_t Simulator_cCreatureBase::FindNextValid(int nAfter)
{
    int nCount = (int)(mpSlotsEnd - mpSlotsBegin);
    for (int i = nAfter + 1; i < nCount; ++i) {
        if (mpSlotsBegin[i].mpCombatant != nullptr || mpSlotsBegin[i].mSecondaryKey != 0)
            return (uint32_t)i;
    }
    return 0xffffffff;
}

// @ 0x00c0f8a0
cCombatant* Simulator_cCreatureBase::GetAt(uint32_t nIndex)
{
    if (nIndex < (uint32_t)(mpSlotsEnd - mpSlotsBegin))
        return mpSlotsBegin[nIndex].mpCombatant;
    return nullptr;
}

// @ 0x00c0f8f0
uint32_t Simulator_cCreatureBase::FindByCombatant(int nCombatant)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (nCombatant == 0)
            return 0xffffffff;
        if ((int)(intptr_t)mpSlotsBegin[i].mpCombatant == nCombatant)
            return i;
    }
    return 0xffffffff;
}

// @ 0x00c0f960
uint32_t Simulator_cCreatureBase::FindByKey(int nKey)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mKey == nKey)
            return i;
    }
    return 0xffffffff;
}

// @ 0x00c0f9b0
cCombatantSlot* Simulator_cCreatureBase::FindSlotByKey(int nKey, uint32_t* pIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if (mpSlotsBegin[i].mKey == nKey) {
            if (pIndex != nullptr)
                *pIndex = i;
            return &mpSlotsBegin[i];
        }
    }
    return nullptr;
}

// @ 0x00c0fa10
cCombatantSlot* Simulator_cCreatureBase::FindSlotByCombatant(int nCombatant, uint32_t* pIndex)
{
    uint32_t nCount = (uint32_t)(mpSlotsEnd - mpSlotsBegin);
    for (uint32_t i = 0; i < nCount; ++i) {
        if ((int)(intptr_t)mpSlotsBegin[i].mpCombatant == nCombatant) {
            if (pIndex != nullptr)
                *pIndex = i;
            return &mpSlotsBegin[i];
        }
    }
    return nullptr;
}

// @ 0x00c0fa70
void* __thiscall CAN::fa70(uint32_t mask, uint32_t* pIndex)
{
    int n = (int)((char*)this->bindEnd - (char*)this->bindBegin);
    unsigned count = (unsigned)(n / 0x24);
    if (count == 0) return 0;
    AnimBinding* e = this->bindBegin;
    unsigned i = 0;
    do {
        int b = e->maskBit;
        if (b != 0 && (mask & (1u << b)) != 0) {
            if (pIndex != 0) *pIndex = i;
            return e;
        }
        ++i;
        ++e;
    } while (i < count);
    return 0;
}

// @ 0x00c0fb80
void __thiscall CAN::fb80(int, int)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c != 0) ((F_a047d0*)c)->f(1);
}

// @ 0x00c0fba0
void __cdecl FUN_00c0fba0(int* self, int* vec)
{
    int count = (vec[1] - vec[0]) >> 4;
    int* o = (int*)(*(void*(__thiscall**)(int*))((*(int**)self)[0x20 / 4]))(self);
    void* s = (*(void*(__thiscall**)(void*))((*(void***)o)[0x18 / 4]))(o);
    FUN_0093aa70(s, &count, 1, 0);
    int* p = (int*)vec[0];
    int* end = (int*)vec[1];
    while (p != end) {
        FUN_00c0b030(self, p);
        p += 4;
    }
    (*(void(__thiscall**)(int*))((*(int**)self)[0x1c / 4]))(self);
}

// @ 0x00c0fc10
char __cdecl FUN_00c0fc10(int param_1, int* param_2)
{
    AnimBinding* p = (AnimBinding*)param_2[0];
    AnimBinding* end = (AnimBinding*)param_2[1];
    while (p != end) {
        if (p != 0) {
            void* q = p->target;
            void (__thiscall *fn)(void*, int) =
                (void (__thiscall *)(void*, int))(*(int**)q)[0x1c / 4];
            fn(q, param_1);
        }
        ++p;
    }
    return 1;
}

// @ 0x00c0fc40
int* __cdecl FUN_00c0fc40(int* first, int* last)
{
    if (first != last) {
        int* prev;
        do {
            prev = first;
            ++first;
            if (first == last) return last;
        } while (*prev != *first);
        int* dst = prev;
        int* cur = dst;
        while (++cur != last) {
            int* v = (int*)*cur;
            if ((int*)*dst != v) {
                int* old = (int*)dst[1];
                ++dst;
                if (v != old) {
                    if (v != 0) (*(void(__thiscall**)(void*))((*(void***)v)[0xbc / 4]))((void*)v);
                    *dst = (int)v;
                    if (old != 0) (*(void(__thiscall**)(void*))((*(void***)old)[0xc0 / 4]))((void*)old);
                }
            }
        }
        return dst + 1;
    }
    return last;
}

// @ 0x00c0fcf0
int* __cdecl FUN_00c0fcf0(int* iface, int param_2)
{
    int count = 0;
    int* o = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
    void* s = (*(void*(__thiscall**)(void*))((*(void***)o)[0x18 / 4]))(o);
    FUN_0093a780(s, &count, 1, 0);
    if (count > 0) {
        for (int i = 0; i < count; ++i) {
            char b = 0;
            int* o2 = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
            void* s2 = (*(void*(__thiscall**)(void*, void*))((*(void***)o2)[0x18 / 4]))(o2, &b);
            FUN_0093ac80(s2);
            if (i < 0x58) {
                uint32_t* pu = (uint32_t*)(param_2 + (i >> 5) * 4);
                if (b == 0) *pu &= ~(1u << (i & 0x1f));
                else *pu |= 1u << (i & 0x1f);
            }
        }
    }
    return iface;
}

// @ 0x00c0fda0
int* __cdecl FUN_00c0fda0(int* iface, int param_2)
{
    int n = 0x58;
    int* o = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
    void* s = (*(void*(__thiscall**)(void*))((*(void***)o)[0x18 / 4]))(o);
    FUN_0093aa70(s, &n, 1, 0);
    uint32_t bit = 1;
    for (int i = 0; i < 0x58; ++i) {
        char b = ((*(uint32_t*)(param_2 + (i >> 5) * 4) & bit) != 0);
        int* o2 = (int*)(*(void*(__thiscall**)(int*))((*(int**)iface)[0x20 / 4]))(iface);
        void* s2 = (*(void*(__thiscall**)(void*))((*(void***)o2)[0x18 / 4]))(o2);
        FUN_0093a9a0(s2, &b, 1);
        bit = (bit << 1) | (bit >> 31);
    }
    return iface;
}

// @ 0x00c0fe30
void* __thiscall CAN::fe30(void* src)
{
    AnimBinding* d = (AnimBinding*)this;
    AnimBinding* s = (AnimBinding*)src;
    d->id = s->id;
    d->maskBit = s->maskBit;
    d->f08 = s->f08;
    d->f0c = s->f0c;
    d->f10 = s->f10;
    d->weight = s->weight;
    d->flags = s->flags;
    d->handle = s->handle;
    void* old = d->target;
    void* nw = s->target;
    if (nw != old) {
        if (nw != 0) ((void (__thiscall *)(void*))(*(int**)nw)[0xbc / 4])(nw);
        d->target = nw;
        if (old != 0) ((void (__thiscall *)(void*))(*(int**)old)[0xc0 / 4])(old);
    }
    return this;
}

// @ 0x00c0fea0
void __cdecl FUN_00c0fea0(int* src, int* dst)
{
    int local[9];
    for (int i = 0; i < 9; ++i) local[i] = src[i];
    void* p = (void*)src[8];
    if (p != 0) (*(void(__thiscall**)(void*))((*(void***)p)[0xbc / 4]))(p);
    ((CAN*)src)->fe30(dst);
    ((CAN*)dst)->fe30(local);
    if (p != 0) (*(void(__thiscall**)(void*))((*(void***)p)[0xc0 / 4]))(p);
}

// @ 0x00c0ffc0
void* __cdecl FUN_00c0ffc0(int param_1, int param_2, int* param_3)
{
    if (param_2 == param_1) return param_3;
    int* dst;
    do {
        param_2 -= 0x24;
        param_3 -= 9;
        dst = param_3;
        dst[0] = *(int*)(param_2 + 0x00);
        dst[1] = *(int*)(param_2 + 0x04);
        dst[2] = *(int*)(param_2 + 0x08);
        dst[3] = *(int*)(param_2 + 0x0c);
        dst[4] = *(int*)(param_2 + 0x10);
        dst[5] = *(int*)(param_2 + 0x14);
        *(char*)(dst + 6) = *(char*)(param_2 + 0x18);
        dst[7] = *(int*)(param_2 + 0x1c);
        int* piVar1 = *(int**)(param_2 + 0x20);
        int* piVar2 = (int*)dst[8];
        if (piVar1 != piVar2) {
            if (piVar1 != 0) (*(void(__thiscall**)(void*))((*(void***)piVar1)[0xbc / 4]))((void*)piVar1);
            dst[8] = (int)piVar1;
            if (piVar2 != 0) (*(void(__thiscall**)(void*))((*(void***)piVar2)[0xc0 / 4]))((void*)piVar2);
        }
    } while (param_2 != param_1);
    return dst;
}

// @ 0x00c10050
void __cdecl FUN_00c10050(uint32_t param_1, int param_2, int param_3, int param_4, char param_5)
{
    if (param_3 == 0) return;
    AnimFbcObj* a = (AnimFbcObj*)((AnimParamObj*)param_3)->sub;
    if (a == 0) return;
    Anim2c0Obj* b = (Anim2c0Obj*)a->sub;
    if (b == 0) return;
    Anim08Obj* c = (Anim08Obj*)b->sub;
    if (c == 0) return;
    void* finder = c->finder;
    CAN* ctx;
    if (finder == 0) ctx = 0;
    else ctx = (CAN*)((int (__thiscall *)(void*, int))(*(int**)finder)[0xc / 4])(finder, 0xce9f6639);

    uint32_t local_40[16];
    local_40[0] = 0; local_40[1] = 1;
    local_40[2] = 0; local_40[3] = 2;
    local_40[4] = 0; local_40[5] = 3;
    local_40[6] = 0; local_40[7] = 4;
    uint32_t uVar7 = 0;
    if (param_1 != 0xffffffff) {
        uint32_t uVar4 = param_1;
        do {
            local_40[uVar7 * 2] = uVar4 & 0xff;
            ++uVar7;
            if (uVar7 >= 4) break;
            uint32_t t = uVar4 >> 8;
            uVar4 = uVar4 >> 8;
            if ((char)t == -1) break;
        } while (1);
    }
    uint32_t uVar6 = 0;
    int* piVar3 = (int*)FUN_009ff6f0((void*)param_3, (void*)param_4);
    if (piVar3 != 0 && *piVar3 != 0) {
        int iVar5 = *(int*)(*piVar3 + 8);
        if (iVar5 != 0 && uVar7 != 0) {
            if (*(uint32_t*)(iVar5 + 0x18) < 2) {
                if (*(int*)(iVar5 + 0x14) == 2) {
                    CANCtx* cc = (CANCtx*)ctx->animCtx;
                    int remap = (int)cc->remapTable;
                    int arr = *(int*)(remap + 0x2e4);
                    AnimSlotSrc* elem = (AnimSlotSrc*)*(void**)(arr + local_40[0] * 700);
                    if (0.0f < elem->weight) uVar6 = 1;
                } else {
                    uVar6 = 0;
                }
            } else {
                void* c2 = ctx->animCtx;
                char* extra = 0;
                uint32_t rr = ((uint32_t (__thiscall *)(void*, int, uint32_t*, uint32_t, void*))
                               (*(int**)c2)[0x68 / 4])(c2, param_4, local_40, uVar7, &extra);
                if (rr < *(uint32_t*)(*(int*)(*piVar3 + 8) + 0x14)) uVar6 = rr;
            }
        }
    }
    void* c3 = ctx->animCtx;
    ((void (__thiscall *)(void*, int, uint32_t))(*(int**)c3)[0x3c / 4])(c3, param_4, uVar6);
    if (param_5 == 0 && param_2 != -1) {
        uint32_t val = (uint32_t)param_2;
        for (int i = 0; i < 4; ++i) {
            uint32_t local = 0;
            char* e = ((F_f9b0*)ctx)->f((int)(val & 0xff), &local);
            if (e != 0 && *(int*)(e + 4) != 0) {
                local_40[6] = local;
                local_40[7] = (uint32_t)param_4;
                local_40[8] = 0;
                ((AnimPlayCtx*)ctx->playCtx)->Play(5, 0, (void*)ctx, GF(0x146a32c), &local_40[6], 0);
            }
            uint32_t t = val >> 8;
            val = val >> 8;
            if ((char)t == -1) break;
        }
    }
}

// @ 0x00c10210
void __cdecl FUN_00c10210(int a1, int a2, int a3, int a4)
{
    FUN_00c10050((uint32_t)a1, a2, a3, a4, 1);
}

// @ 0x00c10230
void __cdecl FUN_00c10230(int a1, int a2, int a3, int a4)
{
    FUN_00c10050((uint32_t)a1, a2, a3, a4, 0);
}

// @ 0x00c10250
void __cdecl FUN_00c10250(int param_1, int param_2, uint32_t param_3, int param_4)
{
    CAN* self = (CAN*)param_1;
    if (*(int*)(param_4 + 0x24) != 0) {
        uint32_t u = 0xffffffff;
        char* p = (char*)self->fa70(*(uint32_t*)(param_4 + 0x24), 0);
        if (p != 0) u = *(uint32_t*)p;
        if (u != param_3 && u != 0xffffffff) param_3 = u;
    }
    char* c = *(char**)(param_1 + 0xb54);
    int iVar1 = *(int*)(c + 0x17c);
    uint32_t cnt = (uint32_t)((*(int*)(iVar1 + 0x2e8) - *(int*)(iVar1 + 0x2e4)) / 700);
    if (cnt <= param_3) param_3 = 0xffffffff;
    uint32_t u2 = 0xffffffff;
    if (*(int*)(param_4 + 0x20) != 0) {
        char* p2 = (char*)self->fa70(*(uint32_t*)(param_4 + 0x20), 0);
        if (p2 != 0 && *(uint32_t*)p2 != 0xffffffff) u2 = *(uint32_t*)p2 | 0xffffff00;
    }
    param_3 |= 0xffffff00;
    char* c2 = *(char**)(param_1 + 0xb54);
    void* vt = *(void**)c2;
    (*(void(__thiscall**)(void*, int, void*))((char*)vt + 0x48))(c2, param_2, (void*)FUN_00c10230);
    (*(void(__thiscall**)(void*, int, uint32_t, uint32_t))((char*)vt + 0x4c))(c2, param_2, param_3, u2);
}

// @ 0x00c10330
void __cdecl FUN_00c10330(int param_1, int param_2, int param_3, uint32_t param_4, int param_5, uint32_t param_6)
{
    uint32_t uVar8 = 0xffffffff;
    uint32_t local_4 = 4;
    uint32_t* pu = &local_4;
    if (param_4 < 5) pu = &param_4;
    uint32_t uVar5 = 0;
    if (*pu != 0) {
        char bVar6 = 0;
        do {
            int iVar1 = (int)(uVar5 * 4);
            char bVar2 = bVar6 & 0x1f;
            char bVar3 = bVar6 & 0x1f;
            ++uVar5;
            bVar6 = (char)(bVar6 + 8);
            uVar8 = ((uint32_t)*(uint8_t*)(param_3 + iVar1) << bVar3) | (~(0xffu << bVar2) & uVar8);
        } while (uVar5 < *pu);
    }
    uint32_t uVar7 = 0xffffffff;
    uVar5 = 0;
    if (param_6 != 0) {
        char bVar6 = 0;
        do {
            int iVar1 = (int)(uVar5 * 4);
            char bVar2 = bVar6 & 0x1f;
            char bVar3 = bVar6 & 0x1f;
            ++uVar5;
            bVar6 = (char)(bVar6 + 8);
            uVar7 = ((uint32_t)*(uint8_t*)(param_5 + iVar1) << bVar3) | (~(0xffu << bVar2) & uVar7);
        } while (uVar5 < param_6);
    }
    char* c = *(char**)(param_1 + 0xb54);
    void* vt = *(void**)c;
    (*(void(__thiscall**)(void*, int, void*))((char*)vt + 0x48))(c, param_2, (void*)FUN_00c10230);
    (*(void(__thiscall**)(void*, int, uint32_t, uint32_t))((char*)vt + 0x4c))(c, param_2, uVar8, uVar7);
}

// @ 0x00c103f0
void __cdecl FUN_00c103f0(void)
{
    void* a = FUN_00f473a0(0x20, "Simulator/cAnimationRemapping", 0, 0, 0, 0);
    G32(0x168d900) = (uint32_t)(uintptr_t)a;
    if (a != 0) {
        for (int i = 0; i < 8; ++i) *(int*)((char*)a + i * 4) = 0;
    } else {
        G32(0x168d900) = 0;
    }
    int* pm = (int*)FUN_0067de30();
    intptr_t base = (intptr_t)G32(0x168d900);
    uint32_t uVar5 = 0;
    int iVar3 = 0;
    do {
        if (G32(0x1572008 + uVar5) != 0) {
            int* piVar1 = *(int**)(base + iVar3);
            int* puVar4 = (int*)(base + iVar3);
            if (piVar1 != 0) {
                *puVar4 = 0;
                (*(void(__thiscall**)(void*))((*(void***)piVar1)[1]))((void*)piVar1);
            }
            (*(void(__thiscall**)(void*, int, int, void*))((char*)*(void**)pm + 0x2c))(
                pm, (int)G32(0x1572008 + uVar5), (int)G32(0x157200c + uVar5), puVar4);
        }
        uVar5 += 8;
        iVar3 += 4;
    } while (uVar5 < 0x38);
    intptr_t base2 = (intptr_t)G32(0x168d900);
    int* piVar1 = *(int**)(base2 + 0x1c);
    int* puVar4 = (int*)(base2 + 0x1c);
    if (piVar1 != 0) {
        *puVar4 = 0;
        (*(void(__thiscall**)(void*))((*(void***)piVar1)[1]))((void*)piVar1);
    }
    (*(void(__thiscall**)(void*, uint32_t, uint32_t, void*))((char*)*(void**)pm + 0x2c))(
        pm, 0x3bd27948u, 0x623d3400u, puVar4);
}

// @ 0x00c104d0
void FUN_00c104d0(Vector3* out, const Vector3& up, const Vector3& fwd, const Vector3& target, const Vector3& goal, float t)
{
    Vector3 u = up;
    float inv = 1.0f / sqrtf(u.LengthSq());
    Vector3 n = u * inv;
    Vector3 d = target - u;
    Vector3 dp = Reject(d, n);
    Vector3 fp = Reject(fwd, n);
    Vector3 dpN = NormalizeSafe(dp);
    float cosA = NormalizeSafe(fp).Dot(dpN);

    Vector3 side = NormalizeSafe(dp.Cross(n));
    float angle = WrapAngleMod(SignedAngle(dp, d, side));

    Vector3 surfUp = cPlanetModel::Get()->SurfaceNormal(up);
    Vector3 fpSide = NormalizeSafe(fp.Cross(n));
    float baseAngle = WrapAngleMod(SignedAngle(fp, Reject(fp, surfUp), fpSide));

    if (cosA < 0.5f) {
        float turn = WrapAngleMod(SignedAngle(fp, dpN, n));
        if (turn > 0.0f)
            turn = 1.0471976f;
        else
            turn = -1.0471976f;
        Vector3 r = RotateVector(fp, AxisAngle(n, turn));
        float w = SmoothStep((cosA + 1.0f) * 0.6666667f);
        float iw = 1.0f - w;
        dp = Vector3(r.x * w + fp.x * iw, r.y * w + fp.y * iw, r.z * w + fp.z * iw);
        dpN = NormalizeSafe(dp);
        angle = iw * baseAngle + w * angle;
    }

    float len = sqrtf(dp.LengthSq());
    if (len < 1.0f) {
        float w = SmoothStep(len);
        float iw = 1.0f - w;
        float k = iw * 3.0f;
        dp = Vector3(dpN.x * w + fp.x * k, dpN.y * w + fp.y * k, dpN.z * w + fp.z * k);
        angle = iw * baseAngle + w * angle;
    }

    Vector3 axis = NormalizeSafe(dp.Cross(n));
    Vector3 r = RotateVector(dp, AxisAngle(axis, angle));
    float f = (float)exp((double)(t * -3.0103f));
    float g = 1.0f - f;
    Vector3 p = up + r;
    out->x = goal.x * f + p.x * g;
    out->y = goal.y * f + p.y * g;
    out->z = goal.z * f + p.z * g;
}

// @ 0x00c13340
void __fastcall FUN_00c13340(DestructOwner* self, void* edx)
{
    (void)edx;
    Rec34* rec = self->mRecs;
    for (int i = 4; i != 0; --i, ++rec) {
        IEffect* p;
        p = rec->mpFirst;
        rec->mp00 = 0;
        if (p) {
            p->Stop(0);
            p = rec->mpFirst;
            if (p) {
                rec->mpFirst = 0;
                p->Release();
            }
        }
        p = rec->mpSecond;
        if (p) {
            p->Stop(0);
            p = rec->mpSecond;
            if (p) {
                rec->mpSecond = 0;
                p->Release();
            }
        }
        p = rec->mpThird;
        if (p) {
            rec->mpThird = 0;
            p->Detach();
        }
    }
    self->mC04 = 0;
    self->mC08 = 0;
    self->mC0C = 0;
}

// @ 0x00c13c60
uint8_t __fastcall FUN_00c13c60(CCreature* self, void* edx, int* target, uint8_t p3, uint8_t p4)
{
    (void)edx;
    uint8_t result = 0;
    void* gameMode = FUN_00b5b800();
    uint8_t isStrategy = (gameMode == (void*)0x01654c10);
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;

    if (count <= 0)
        return result;
    if (self->mB34 != 1 && !isStrategy)
        return result;
    if (!target)
        return result;
    uint32_t flags = *(uint32_t*)((char*)target + 0x50);
    if ((flags & 0x200) == 0)
        return result;
    if (!p3 && (int8_t)flags < 0)
        return result;
    if (*(uint8_t*)((char*)target + 0x70) == 0)
        return result;
    if (!p3 && (flags & 0x100) != 0)
        return result;
    if (p4) {
        CAnimator* anim = (CAnimator*)self->mpAnimator;
        if (!(anim->mF590 > gZero1485378))
            return result;
    }

    if (!isStrategy) {
        float ratio = ((ILoco*)target)->GetScalar70();
        ILoco* loco = (ILoco*)((char*)self + 0xc0);
        float denom = loco->GetScalar70() + gEps146a330;
        ratio = ratio / denom;
        void* creature = FUN_00ae66f0(target);
        float limit = gFallbackRange;
        if (creature) {
            void* strat = FUN_00d38840();
            limit = FUN_004e1c70(*(int*)((char*)strat + 0xb4), (int)0xd7e2f8aa, 0.5f);
        }
        if (ratio > limit)
            return result;
    }
    result = 1;
    return result;
}

// @ 0x00c13db0
uint8_t __fastcall FUN_00c13db0(CCreature* self, void* edx, int a, int b)
{
    (void)edx;
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;
    if (a >= count)
        return 0;
    if (b >= count)
        return 0;

    CitRec* begin = self->mpRecsBegin;
    CitRec* recA = &begin[a];
    CitRec* recB = &begin[b];

    IRefObj* held = recA->mpPtr;
    if (held)
        held->AddRef();

    FUN_00ad7ec0(&recA->mpPtr, &recB->mpPtr);
    FUN_00ad7ec0(&recB->mpPtr, &held);

    if (recA->mpPtr)
        FUN_00c0e000(self, recA->mpPtr, (void*)recA->mId);
    if (recB->mpPtr)
        FUN_00c0e000(self, recB->mpPtr, (void*)recB->mId);
    if (held)
        held->SubRef();
    return 1;
}

// @ 0x00c13eb0
void __fastcall FUN_00c13eb0(CCreature* self, void* edx)
{
    (void)edx;
    if (!self->mpAnimator)
        return;
    int count = (int)(self->mpRecsEnd - self->mpRecsBegin) / 0x24;
    if (count <= 0)
        return;

    CitRec* rec = self->mpRecsBegin;
    for (int i = 0; i < count; ++i, ++rec) {
        IProp* prop = (IProp*)rec->mpPtr;
        if (!prop)
            continue;

        if (prop->Get() == 0) {
            void* world = FUN_00b3d520();
            if (world)
                ((IModelWorld*)world)->Slot00();
            ((PropData*)prop)->mFlags50 |= 8;
            prop->Set(world);
            int key = (int)prop->Find(0x116dd1b);
            void* a = FUN_00b3d310(prop, key);
            FUN_00b5a260(a);
            if (world)
                ((IModelWorld*)world)->Release();
        }

        int id = rec->mId;
        if (id == -1)
            continue;
        if (!FUN_00c11f50(self, id, 0, prop, prop))
            continue;

        void* offsets = 0;
        CAnim* anim = (CAnim*)self->mpAnimating;
        if (anim) {
            offsets = FUN_009cab60(anim->mpModelWorld, prop);
        }
        CAnim* anim2 = (CAnim*)self->mpAnimating;
        void* mw2 = anim2->mpModelWorld;
        void* array = *(void**)((char*)mw2 + 0x2e4);
        void* elem = *(void**)((char*)array + id * 0x2bc);
        FUN_00c0de60(self, elem, offsets);

        IKeyed* sub = (IKeyed*)prop->Find(0x017f243b);
        if (sub) {
            void* noun = sub->Slot20(((KeyedData*)sub)->mKey28);
            void* nm = FUN_00b3d300((int)noun);
            void* hit = FUN_00b21000(nm, 0);
            if (hit && FUN_0064f350(*(int*)((char*)hit + 0xc), (int)0x670f1af, 0)) {
                float* f = (float*)offsets;
                f[6] = 0.0f;
                f[7] = gOne1485720;
                f[8] = 0.0f;
                f[9] = 0.0f;
            }
        }
        FUN_00d7d220(prop, self);
    }
}

// @ 0x00c14070
void __fastcall FUN_00c14070(CCreature* self, void* edx, uint32_t* prop)
{
    (void)edx;
    CAnim* anim = (CAnim*)self->mpAnimating;
    if (!anim || !prop)
        return;

    if (prop[7]) {
        FUN_00a01f10(anim->mpP184, 0, (int)prop[7], 0);
        prop[7] = 0;
    }

    int key = (int)prop[2];
    FUN_00c0c5b0(self, key, &key);

    uint32_t handle = (uint32_t)anim->Slot08(key, 0);
    prop[7] = handle;
    anim->Slot0c((int)handle, 2);
    anim->Slot18((int)handle);
    anim->Slot1c((int)handle, 3.0f);
    anim->Slot20((int)handle, 1);
    anim->Slot24((int)handle, -1.0f);
    anim->Slot3c((int)handle, (uint8_t)prop[6] == 0);
    anim->Slot40((int)handle, (int)prop[2]);
    uint32_t flags = *prop | 0xffffff00;
    anim->Slot48((int)handle, (void*)&FUN_00c10210);
    anim->Slot4c((int)handle, (int)flags, 0);
}

// @ 0x00c141b0
void*__cdecl FUN_00c141b0(IStream* stream, int* rec)
{
    IRefObj** slot = (IRefObj**)((char*)rec + 0x20);
    IRefObj* old = *slot;
    if (old) {
        *slot = 0;
        old->SubRef();
    }

    stream->Slot28(0x01186577, slot, 0);

    IWriterS* w;
    void* s;
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, rec, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 8, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 4, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    s = w->GetStream_18();
    FUN_0093a780(s, (char*)rec + 0x10, 1, 0);
    w = (IWriterS*)stream->GetWriter_20();
    FUN_0093ac80(w->GetStream_18(), (char*)rec + 0x18);
    return stream;
}

// @ 0x00c15310
void __thiscall cSPCreatureBase_s00c1_5310::func64h(s32 a2, float a3)
{
  (void)a2;
  // Refresh ability-recharge timers.
  u32 n = 0;
  u32* pBits = this->mRechargeBits_bf8;
  do {
    if (pBits[0] != 0) {
      SimCreature* pSim = (SimCreature*)this;
      u32 count = pSim->mpVtbl->GetAbilitiesCount();
      u32 words[3];
      words[0] = pBits[0];
      words[1] = pBits[1];
      words[2] = pBits[2];
      u32 idx = 0;
      // first: check recharging words for set bits
      for (;;) {
        if (words[idx] != 0)
          break;
        idx++;
        if (idx >= 3) goto checkDirty;
      }
      while (idx < count) {
        if (idx < 0x58) {
          u32 bit = 1u << (idx & 0x1f);
          u32 wi = idx >> 5;
          if ((words[wi] & bit) == 0) { idx++; continue; }
          cAbilityState* pStates = (cAbilityState*)this->mpAbilityStates_c28;
          u32 clearMask = ~bit;
          words[wi] &= clearMask;
          if (pStates[idx].mF_04 >= 1.0f) {
            pStates[idx].mF_04 = 1.0f;
            this->mRechargeBits_bf8[wi] &= clearMask;
          } else {
            cCreatureAbility* pAb = ((SimCreature*)this)->mpVtbl->GetAbility(idx);
            u32 delta = (u32)((1.0f / pAb->mF_9c) * (float)count);
            pStates[idx].mF_04 = (float)delta + pStates[idx].mF_04;
          }
        }
        idx++;
      }
    }
    n++;
    pBits++;
  } while (n < 3);

checkDirty:
  n = 0;
  u32* pDirty = this->mAbilityDirty_c04;
  do {
    if (pDirty[0] != 0) {
      FUN_00c12640(a3);
      return;
    }
    n++;
    pDirty++;
  } while (n < 3);
}

// @ 0x00c15470
void cSPCreatureBase_s00c1_5310::FUN_00c15470(s32 a2, RefCnt* a3, u8 a4)
{
  u32 count = ((SimCreature*)this)->mpVtbl->GetAbilitiesCount();
  if ((u32)a2 >= count)
    return;
  BodyEntry* pBase = (BodyEntry*)this->mBodyBlock_eb0;
  u32 idx = 0;
  BodyEntry* e = pBase;
  for (; idx < 4; idx++) {
    if (e->mU32_04 == 0)
      break;
    e = (BodyEntry*)((u8*)e + 0x34);
  }
  if (idx == 4) {
    FUN_00c0f490(pBase);
    this->mAbilityDirty_c04[0] |= 2;
    e = pBase;
  } else {
    this->mAbilityDirty_c04[idx >> 5] |= (1u << (idx & 0x1f));
  }
  if (pBase == 0)
    return;
  void* pAbilityRaw = ((SimCreature*)this)->mpVtbl->GetAbility(a2);
  AbilityObj* pAbility = (AbilityObj*)pAbilityRaw;
  u32 pBoneless = (u32)(SIZE_T)pAbility;
  e->mU32_04 = 1;
  e->mU32_20 = a2;
  RefCnt* pOld = e->mpTarget_28;
  if (pOld != a3) {
    if (a3 != 0)
      ((ObjVtbl*)a3)->Slot60();
    e->mpTarget_28 = a3;
    if (pOld != 0)
      ((ObjVtbl*)pOld)->Slot64();
  }
  e->mB_00 = a4;
  u8* pSpat = (u8*)&this->mSpatial;
  e->mF_24 = 0.0f;
  Vec3_s00c1_5310 box[2];
  Vec3_s00c1_5310* pb = this->mSpatial.GetBox(box);
  float midX = (pb[1].x + pb[0].x) * 0.5f;
  float midY = (pb[1].y + pb[0].y) * 0.5f;
  float midZ = (pb[1].z + pb[0].z) * 0.5f;
  if (a2 == -1) {
    e->mF_24 = -this->mSpatial.GetRadius();
  } else {
    void* pAnimWorld = this->mpAnimWorld_b54;
    u32 pArr = *(u32*)((u8*)pAnimWorld + 0x17c);
    Vec3_s00c1_5310 t;
    FUN_0099c1a0(&t, (void*)(pArr + 0x3c), (Vec3_s00c1_5310*)(*(u32*)(pArr + 0x2e4) + a2 * 700 + 0x10));
    midX = t.x + *(float*)(pArr + 0x18);
    midY = t.y + *(float*)(pArr + 0x1c);
    midZ = t.z + *(float*)(pArr + 0x20);
    FUN_00c15150_tc(this, 0, (void*)(pAbility->mpEffect_88 + (u32)(SIZE_T)e), 0);
    FUN_00c14f70(this, (u32)(SIZE_T)pAbility, pAbility->mpEffect_88,
                 pAbility->mpEffect_88 + (u32)(SIZE_T)e);
  }
  e->mF_08 = midX;
  e->mF_0c = midY;
  e->mF_10 = midZ;
  e->mB_01 = 1;
  if (a3 == 0) {
    e->mF_14 = 1.0f;
    e->mF_18 = 1.0f;
    e->mF_1c = 1.0f;
  } else {
    Vec3_s00c1_5310 b2[2];
    Vec3_s00c1_5310* pb2 = this->mSpatial.GetBox(b2);
    float c0 = (pb2[1].x + pb2[0].x) * 0.5f;
    float c1 = (pb2[1].y + pb2[0].y) * 0.5f;
    float c2 = (pb2[1].z + pb2[0].z) * 0.5f;
    Vec3_s00c1_5310 c = { c0, c1, c2 };
    FUN_00c0ca00(&c, &c, 0.0f, &e->mF_14, gF_168d910);
  }
  EffectsMgr* mgr = (EffectsMgr*)(void*)EffectsManager();
  BodyEffect* pEff = e->mpEffect_2c;
  BodyEffect** ppEff = &e->mpEffect_2c;
  if (pEff != 0) {
    *ppEff = 0;
    ((ObjVtbl*)pEff)->Slot04();
  }
  u8 ok = mgr->Slot2c(pAbility->mEffectId_8c, 0, (void**)ppEff);
  (void)pSpat; (void)pBoneless;
  if (ok != 0) {
    Vec3_s00c1_5310 fwd = { e->mF_14, e->mF_18, e->mF_1c };
    float len2 = fwd.x * fwd.x + fwd.y * fwd.y + fwd.z * fwd.z;
    float inv = 1.0f / len2;
    Vec3_s00c1_5310 norm = { fwd.x * inv, fwd.y * inv, fwd.z * inv };
    Vec3_s00c1_5310 up = { midX, midY, midZ };
    Vec3_s00c1_5310 out;
    FUN_0069b440(&out, &norm, &up);
    ((ObjVtbl*)(*ppEff))->Slot18();
    ((ObjVtbl*)(*ppEff))->Slot08();
  }
}

// @ 0x00c15920
float cSPCreatureBase_s00c1_5310::FUN_00c15920()
{
  s32 saved = (s32)(u32)(this->mpRefA_4cc);
  s32 cur = FUN_00c06000_tc(FUN_00b3d310(), 0);
  if (saved == cur && ((this->mFlags_ee4 >> 5) & 1) == 0)
    return this->mF_1e4 * gF_15826c + gF_169e280;
  return gF_146a32c;
}

// @ 0x00c15970
float cSPCreatureBase_s00c1_5310::FUN_00c15970()
{
  s32 saved = (s32)(u32)(this->mpRefA_4cc);
  s32 cur = FUN_00c06000_tc(FUN_00b3d310(), 0);
  if (saved == cur && ((this->mFlags_ee4 >> 5) & 1) == 0)
    return this->mF_1e4 * gF_158270 + gF_169e284;
  return gF_146a32c;
}

// @ 0x00c17580
uint32_t cSPCreatureBase_s00c1_7350::GetBodyPartIndex(uint32_t kind, uint32_t index)
{
    uint32_t result = 0xffffffff;
    uint32_t parts[255];
    uint32_t count = QueryCreatureBodyParts(this, kind, parts, 255);
    if (index < count) {
        result = parts[index];
    }
    return result;
}

// @ 0x00c17c80
uint32_t cSPCreatureBase_s00c1_7350::CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b)
{
    uint32_t part;
    if (QueryCreatureBodyParts(this, kind, &part, 1) != 0) {
        return MakeBodyEffect(part, a, b);
    }
    return 0;
}

// @ 0x00c18b40
int cSPCreatureBase_s00c1_8b40::FUN_00c18b40(int arg)
{
    SpeciesProfile* prof = mpProfile;
    if (prof->sprintLevel == 0)
        return 0;

    bool bLeap = mbLeaping;
    float range;
    if (bLeap) {
        range = prof->jumpingAbility;
    } else {
        if (mFlags & 0x1000)
            return 0;
        range = prof->flappingAbility;
    }
    if (range <= kRealZero)
        return 0;

    bool isAvatar = ((mGeneralFlags >> 9) & 1) != 0;

    const Vector3_s00c1_8b40* pos = mBody.GetPos();
    Vector3_s00c1_8b40 res = { gZeroVecX, gZeroVecY, gZeroVecZ };

    float inv = 1.0f / sqrtf(pos->x*pos->x + pos->y*pos->y + pos->z*pos->z
                             + kSqrtEpsilon);
    Vector3_s00c1_8b40 fwd = { pos->x*inv, pos->y*inv, pos->z*inv };

    Vector3_s00c1_8b40 face;
    mBody.GetForward(&face);

    const Vector3_s00c1_8b40* vel = mBody.GetVelocity();
    float speed = sqrtf(vel->x*vel->x + vel->y*vel->y + vel->z*vel->z);

    float dot = (fwd.x*vel->y + fwd.y*vel->z) + range*vel->x;
    float q  = range * dot;
    float projX = vel->x - q;
    float t  = fwd.y * dot;
    float projZ = vel->z - t;
    float u  = fwd.x * dot;
    float projY = vel->y - u;
    float projLen = sqrtf(projY*projY + (projZ*projZ + projX*projX));

    float radius = mBody.GetF_0xc8();

    if (gB_1572051 && isAvatar && gB_169e381 &&
        Vector3Equal(vel, (const Vector3_s00c1_8b40*)&gZeroVecX)) {
        res.x = gF_169e388 * gF_169e384;
        res.y = gF_169e38c * gF_169e384;
        res.z = gF_169e390 * gF_169e384;
    }

    if (bLeap) {
        Vector3_s00c1_8b40 r;
        r.z = fwd.z*range + vel->z;
        r.y = fwd.y*range + vel->y;
        r.x = fwd.x*range + vel->x;
        float len = sqrtf(r.z*r.z + r.y*r.y + r.x*r.x);
        float lim = (speed > range) ? speed : range;
        if (len > lim) {
            float s = lim / len;
            r.x *= s;
            r.y *= s;
            r.z *= s;
        }
        r.x -= vel->x;
        r.y -= vel->y;
        r.z -= vel->z;
        res = r;
    } else {
        Vector3_s00c1_8b40 dir = fwd;
        if (radius > projLen) {
            Vector3_s00c1_8b40 a = { face.x + fwd.x*kThree,
                          face.y + fwd.y*kThree,
                          face.z + fwd.z*kThree };
            normalized_safe(&dir, &a);
        }
        res.x = dir.x * range;
        res.y = dir.y * range;
        res.z = dir.z * range;
        if (gB_1572050 && speed > kRealZero &&
            (projX*fwd.x + projY*fwd.y + projZ*fwd.z) < kRealZero) {
            res.x -= projX;
            res.y -= projY;
            res.z -= projZ;
        }
    }

    mBody.FUN_00c446d0(&res, 0);

    if (isAvatar) {
        LocomotionRequest req;
        mBody.Submit(&req);
        if (req.mpBegin && ((int*)req.mpBegin)[-1] != 0)
            operator_delete__(req.mpBegin);
    }

    FUN_00c15dc0((float)arg);

    if (!bLeap) {
        if (prof->mCount698 == 0)
            InterruptAnimation(0x5485a4cu, -1, 0);
        else
            InterruptAnimation(0x77300ffu, -1, 0);
        return 1;
    }

    uint32 id;
    if (prof->preferredSocialType == 0) {
        id = (prof->mCount6a0 == 0) ? 0x25b3bc0u : 0x7995fdcu;
    } else if (prof->mCount6a0 != 0) {
        id = 0x7995fdcu;
    } else {
        id = (prof->mCount698 != 0) ? 0x77300f2u : 0x5261d56u;
    }
    InterruptAnimation(id, -1, 0);

    mState = 3;
    mbLeaping = false;
    if (isAvatar) {
        gF_169e3b4 = pos->x;
        gF_169e3b8 = pos->y;
        gF_169e3bc = pos->z;
    }
    return 1;
}

// @ 0x00c190e0
bool cSPCreatureBase_s00c1_8b40::TryJumpToTarget(const Vector3_s00c1_8b40* a1, const Vector3_s00c1_8b40* a2, int a3, float a4, bool a5)
{
    SpeciesProfile* prof = mpProfile;
    if (!a5 && prof->sprintLevel == 0)
        return false;

    float r1 = mBody.GetRadius();
    float r2 = mBody.GetRadius();
    float maxSq = a4*a4 + (kLeapRadiusScale*kLeapRadiusScale + r2*r1);

    const Vector3_s00c1_8b40* pos = mBody.GetPos();
    float dx = pos->x - a2->x;
    float dy = pos->y - a2->y;
    float dz = pos->z - a2->z;
    if (dx*dx + dy*dy + dz*dz < maxSq)
        return false;

    bool bLeap = mbLeaping;
    float range;
    if (bLeap) {
        range = prof->jumpingAbility;
    } else {
        range = (mFlags & 0x1000) ? 0.0f : prof->flappingAbility;
    }
    if (a5) {
        if (range <= 0.0f)
            range = 5.0f;
    } else {
        if (range <= 0.0f)
            return false;
    }

    bool flagB = (prof->preferredSocialType != 0) || (prof->flappingAbility > 0.0f);

    cPlanetModel_s00c1_8b40* pm = (cPlanetModel_s00c1_8b40*)GetPlanetModel();
    float f7 = pm->FUN_00b7e490();

    const Vector3_s00c1_8b40* p2 = mBody.GetPos();
    Vector3_s00c1_8b40 face;
    mBody.GetForward(&face);

    float inv = 1.0f / sqrtf(p2->x*p2->x + p2->y*p2->y + p2->z*p2->z
                             + kSqrtEpsilon);
    float fx = p2->x * inv;
    float fy = p2->y * inv;
    float fz = p2->z * inv;

    const Vector3_s00c1_8b40* vel = mBody.GetVelocity();
    float dist = sqrtf(p2->x*p2->x + (p2->y*p2->y + p2->z*p2->z));
    pm->GetRadiusAt(p2);

    float dot = vel->x*fx + fy*vel->y + fz*vel->z;
    float px = vel->x - fx*dot;
    float pz = vel->z - fz*dot;
    float py = vel->y - fy*dot;
    float plen = sqrtf(py*py + (pz*pz + px*px));

    float speedLim = kDefaultSpeedCap;
    if (!flagB) {
        float g;
        if (!mbFieldBB0)
            g = FUN_00c0ce80(2, 0);
        else
            g = FUN_00c0ce80(2, 1) + kCe80Boost;
        speedLim = (g <= plen) ? plen : g;
    }

    float ratio;
    if (plen <= kPlenEpsilon) {
        ratio = 1.0f;
    } else {
        Vector3_s00c1_8b40 proj = { px, py, pz };
        Vector3_s00c1_8b40 dir;
        normalized_safe(&dir, &proj);
        ratio = dir.x*face.x + dir.y*face.y + dir.z*face.z;
    }
    float r = ratio + kHalf;
    if (r <= kClampLow)
        r = kClampLow;
    if (r >= 1.0f)
        r = 1.0f;

    float a = pm->FUN_00b82310(a1);
    float ax = a1->x - p2->x;
    float ay = a1->y - p2->y;
    float az = a1->z - p2->z;
    float d2 = az*az + ay*ay + ax*ax;
    float dd = sqrtf(d2);
    float invd = 1.0f / sqrtf(d2 + kSqrtEpsilon);
    float scale = dd / speedLim;
    float t = (a - dist) / scale - (scale * range) * kHalf;
    if (t > 0.0f)
        t = 0.0f;
    float v = t;

    Vector3_s00c1_8b40 out;
    out.x = fx*v + (invd*ax)*speedLim - vel->x;
    out.y = fy*v + (invd*ay)*speedLim - vel->y;
    out.z = fz*v + (invd*az)*speedLim - vel->z;

    mBody.FUN_00c446d0(&out, 0);
    FUN_00c15dc0((float)a3);

    if (bLeap) {
        uint32 id = (prof->mCount698 == 0) ? 0x5261d56u : 0x77300f2u;
        InterruptAnimation(id, -1, 0);
        mState = 3;
        mbLeaping = false;
        return true;
    }
    uint32 id = (prof->mCount698 == 0) ? 0x5485a4cu : 0x77300ffu;
    InterruptAnimation(id, -1, 0);
    {
        LocomotionRequest req;
        mBody.Submit(&req);
        if (req.mpBegin && ((int*)req.mpBegin)[-1] != 0)
            operator_delete__(req.mpBegin);
    }
    return true;
}

// @ 0x00c196a0
uint32 cSPCreatureBase_s00c1_8b40::FUN_00c196a0(uint32 index, bool a2, bool a3)
{
    uint32 result = 0xffffffffu;
    uint32* mask = a2 ? mRechargingAbilityBits : mInUseAbilityBits;
    if (index < 0x58) {
        bool inUse = (mask[index >> 5] & (1u << (index & 0x1f))) != 0;
        if (inUse)
            goto done;
    }
    if (mCurrentAttackIdx != 0xffffffffu)
        goto done;
    if (index >= GetAbilityCount())
        goto done;
    {
        AbilityState* st = &mpAbilityStates[index];
        Ability_s00c1_8b40* ab = GetAbility(index);
        if (st->chargeLevel < 1.0f)
            goto done;
        if (index < 0x58)
            mask[index >> 5] |= 1u << (index & 0x1f);
        if (a2 || a3) {
            st->chargeLevel = 0.0f;
            FUN_00c15dc0(ab->mCost);
        }
        st->applied = false;
        mpAnimCreature->mField170 = 0;
        result = index;
    }
done:
    return result;
}

// @ 0x00c197a0
void cSPCreatureBase_s00c1_8b40::FUN_00c197a0(uint32 index)
{
    if (index >= 0x58)
        return;
    uint32 bit = 1u << (index & 0x1f);
    uint32 word = index >> 5;
    bool inUse = (mInUseAbilityBits[word] & bit) != 0;
    if (!inUse)
        return;
    if (index >= GetAbilityCount())
        return;
    mInUseAbilityBits[word] &= ~bit;
    mRechargingAbilityBits[word] |= bit;
    AbilityState* st = &mpAbilityStates[index];
    Ability_s00c1_8b40* ab = GetAbility(index);
    st->chargeLevel = 0.0f;
    int i = FindIndex(0x27);
    if (i == -1)
        i = FindIndex(0x50);
    if ((int)index == i)
        return;
    int j = FindIndex(0xd);
    if (j == -1)
        j = FindIndex(0x52);
    if ((int)index == j)
        return;
    FUN_00c15dc0(ab->mCost);
}

// @ 0x00c19870
Vector3_s00c1_8b40* CreatureSubView::FUN_00c19870(Vector3_s00c1_8b40* out, int part)
{
    int buf[0xff];
    BodyPartQuery query;
    int p = part;
    if (part == -1) {
        p = -1;
        cSPCreatureBase_s00c1_8b40* base = (cSPCreatureBase_s00c1_8b40*)((char*)this - 0x5a8);
        if (base != 0) {
            AnimatingCreature* anim = base->mpAnimCreature;
            if (anim != 0 && anim->mpAbilityList != 0) {
                query.flag = 1;
                query.mpName = gBodyPartsString;
                query.a = 0;
                query.b = 0;
                uint32 n = (uint32)EvaluateContextTargetQuery(buf, 0xff,
                                            *anim->mpAbilityList, &query, 0, 0);
                if (n > 0)
                    p = buf[0];
            }
        }
    }
    out->x = gZeroVecX;
    out->y = gZeroVecY;
    out->z = gZeroVecZ;
    ((cSPCreatureBase_s00c1_8b40*)((char*)this - 0x5a8))->GetBodyPartPositionAndOrientation(
        *out, &query, (uint32)p, true);
    return out;
}

// @ 0x00c19940
void cSPCreatureBase_s00c1_8b40::FUN_00c19940(bool a)
{
    int count = (int)(mpItemEnd - mpItemBegin);
    if (count == 0)
        return;
    InventoryItem* it = mpItemBegin;
    int i = 0;
    do {
        if (a != 0) {
            if (i >= (int)(mpItemEnd - mpItemBegin))
                goto docall;
            if (it->mpObject == 0)
                goto docall;
            InventoryObject* o = (InventoryObject*)it->mpObject;
            if (o->Query(0x398420d) == 0)
                goto docall;
            if (o->mKind != 3)
                goto docall;
            goto next;
        }
    docall:
        FUN_00c15bd0(i, 0, 0);
    next:
        ++i;
        ++it;
    } while (i < count);
}

// @ 0x00c199e0
void Vector003c::reserve(uint32 count)
{
    uint32 cur = (uint32)(((char*)mpCapacity - (char*)mpBegin) / 0x3c);
    if (count <= cur)
        return;
    char* p;
    if (count != 0) {
        p = (char*)operator_new(count * 0x3c, "Simulator", 0, 0,
               (const char*)&gAbilityStatesAllocator, 0xd1);
    } else {
        p = 0;
    }
    FUN_00ac2130(mpBegin, mpEnd, p);
    if (mpBegin && ((int*)mpBegin)[-1])
        operator_delete__(mpBegin);
    uint32 n = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x3c);
    mpBegin = p;
    mpEnd = p + n * 0x3c;
    mpCapacity = p + count * 0x3c;
}

// @ 0x00c1a3c0
void cCreatureCombatant::TakeDamage(float damage, uint32_t attackerPID, int damageType, const Vector3_s00c1_9b60& dir, void* attacker)
{
    Vector3_s00c1_9b60 tmp;
    CBase* base = Base();
    if (base->IsProtected())
        return;
    if (GetBit(mFlags8, 9) && GetCurrentGameMode() == 0x1654c05)
        return;

    CLoco* loco = Loco();
    if (loco->IsLocomotive()) {
        int s = FUN_00b3d4d0()->mState;
        if (s == 1 || s == 2)
            return;
    }

    if (GetCurrentGameMode() == 0x1654c05) {
        StarManager();
        if (FUN_00ba6650(attackerPID) && (base->mpOverride == 0 || base->mpOverride[0x388] == 0))
            damage = 10000.0f;
    }

    if (GetCurrentGameMode() == 0x1654c10 && damageType != 7) {
        bool fired = false;
        if (mpProfile->mCount668 > 0) {
            float r = FUN_00c0db80(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0xf7a8a2b1, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount648 > 0) {
            float r = FUN_00c161f0(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0x924bae45, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount664 > 0) {
            float r = FUN_00c16340(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0xb9716d18, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount660 > 0) {
            float r = FUN_00c0dcb0(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0x4c1b2351, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (fired)
            mCooldown = 0;
    }

    TakeHit(damage, attackerPID, damageType, dir, attacker);

    if (GetDamageState() == 2) {
        mFlags8 &= 0xffffefff;
        if (GetCurrentGameMode() == 0x1654c10)
            base->FUN_00c19940(0);
        CAgent* agent = Agent();
        bool skip = false;
        if (agent->GetTypeObj() != 0 && agent->GetTypeObj()->GetType() == 0x3cdbbe9)
            skip = true;
        if (skip || (damageType != 0 && damageType != 1)) {
            if (GetCurrentGameMode() != 0x1654c01 && GetCurrentGameMode() != 0x1654c02 &&
                FUN_00ac80d0(base, 0x18eb45e) == 0 && GetCurrentGameMode() != 0x1654c04)
                ((void (__thiscall*)(CBase*, int))(*(void***)base)[0xc8 / 4])(base, 0);
        } else if (damageType == 0) {
            tmp.x = -dir.x; tmp.y = -dir.y; tmp.z = -dir.z;
            FUN_00b3d240()->Post(0x1b55d9a, (void*)loco->GetVector(), &tmp);
        } else {
            tmp.x = -dir.x; tmp.y = -dir.y; tmp.z = -dir.z;
            FUN_00b3d240()->Post(0x1b55d9b, (void*)loco->GetVector(), &tmp);
            return;
        }
    }
    if (damageType != 0)
        return;
    if ((mpOverride == 0 || mpOverride[0x388] == 0) && GetCurrentGameMode() != 0x1654c10) {
        Vector3_Normalize(&tmp, loco->GetVector());
        const float k2 = 2.0f;
        const float tx = tmp.x * k2, ty = tmp.y * k2, tz = tmp.z * k2;
        tmp.x = (tx + dir.x) * 4.0f; tmp.y = (ty + dir.y) * 4.0f; tmp.z = (tz + dir.z) * 4.0f;
        loco->FUN_00c41d60(&tmp);
        tmp.x = tx + dir.x; tmp.y = ty + dir.y; tmp.z = tz + dir.z;
        loco->FUN_00c446d0(&tmp, 0);
        *(int*)((char*)this - 0x2f8) = 3;
    }
}

// @ 0x00c1b020
void cSPCreatureBase::FUN_00c1b020(int arg)
{
    if (mpTargetHolder) {
        TargetCreature* other = (TargetCreature*)mpTargetHolder->Query(0xce9f6639);
        if (other) {
            Body* me = &mBody;
            Body* ob = &other->mBody;
            const Vector3_s00c1_aad0* myPos = me->GetPos();
            const Vector3_s00c1_aad0* otherPos = ob->GetPos();
            Vector3_s00c1_aad0 d;
            d.z = otherPos->z - myPos->z;
            d.y = otherPos->y - myPos->y;
            d.x = otherPos->x - myPos->x;
            float inv = 1.0f / sqrtf((d.z * d.z + d.y * d.y) + d.x * d.x + 1e-8f);
            d.x = inv * d.x;
            d.y = d.y * inv;
            d.z = d.z * inv;
            Vector3_s00c1_aad0 fwdTmp;
            if (!(d.x == kZeroVec.x && d.y == kZeroVec.y && d.z == kZeroVec.z)) {
                const Vector3_s00c1_aad0* fwd = me->GetForward(&fwdTmp);
                if ((fwd->y * d.y + fwd->z * d.z) + fwd->x * d.x > 0.7f) {
                    float boundsTmp[6];
                    const float* bb = ob->GetBounds(boundsTmp);
                    Vector3_s00c1_aad0 center;
                    center.x = (bb[3] + bb[0]) * 0.5f;
                    center.y = (bb[4] + bb[1]) * 0.5f;
                    center.z = (bb[5] + bb[2]) * 0.5f;
                    float otherRadius = ob->GetRadius();
                    ob->GetVelocity();
                    SpeciesData* sp = mpSpecies;
                    if (sp->m610 != 0) {
                        float thr = (me->GetRadius() * me->GetRadius() + otherRadius * otherRadius) +
                                    kLeapMargin * kLeapMargin;
                        const Vector3_s00c1_aad0* p = me->GetPos();
                        float dz = p->z - center.z;
                        float dy = p->y - center.y;
                        float dx = p->x - center.x;
                        if (!(thr > (dz * dz + dy * dy) + dx * dx)) {
                            bool bLeaping = mbLeaping;
                            float range;
                            if (bLeaping) {
                                range = sp->mLeapRangeAir;
                            } else {
                                if (mFlags & 0x1000)
                                    goto L_submit;
                                range = sp->mLeapRange;
                            }
                            if (range > 0.0f) {
                                bool bBig;
                                if (sp->m61c > 0u || sp->mLeapRange > 0.0f)
                                    bBig = true;
                                else
                                    bBig = false;
                                PlanetModel* pm = GetPlanetModel();
                                float g = pm->FUN_00b7e490();
                                const Vector3_s00c1_aad0* pos = me->GetPos();
                                Vector3_s00c1_aad0 fwd2;
                                me->GetForward(&fwd2);
                                float pinv = 1.0f / sqrtf((pos->x * pos->x + pos->y * pos->y) + pos->z * pos->z + 1e-8f);
                                Vector3_s00c1_aad0 up;
                                up.x = pos->x * pinv;
                                up.y = pinv * pos->y;
                                up.z = pinv * pos->z;
                                const Vector3_s00c1_aad0* vel = ob->GetVelocity();
                                float posLen = sqrtf((pos->z * pos->z + pos->y * pos->y) + pos->x * pos->x);
                                pm->GetRadiusAt(pos);
                                float vup = (vel->x * up.x + vel->y * up.y) + vel->z * up.z;
                                Vector3_s00c1_aad0 t;
                                t.x = vel->x - up.x * vup;
                                t.y = vel->y - up.y * vup;
                                t.z = vel->z - up.z * vup;
                                Vector3_s00c1_aad0 t2;
                                t2.x = t.x;
                                t2.y = t.y;
                                t2.z = t.z;
                                float speed = sqrtf((t.x * t.x + t.z * t.z) + t.y * t.y);
                                float cap = kLeapSpeedDefault;
                                if (!bBig) {
                                    float v;
                                    if (mbBB0)
                                        v = FUN_00c0ce80(2, 1) + 10.0f;
                                    else
                                        v = FUN_00c0ce80(2, 0);
                                    const float* pc = &speed;
                                    if (v > speed)
                                        pc = &v;
                                    cap = *pc;
                                }
                                float dotv;
                                if (speed > 0.1f) {
                                    Vector3_s00c1_aad0* n = normalized_safe(&t, &t2);
                                    dotv = (n->y * fwd2.y + n->z * fwd2.z) + n->x * fwd2.x;
                                } else {
                                    dotv = 1.0f;
                                }
                                float w = dotv + 0.5f;
                                float lo = 0.3f, hi = 1.0f;
                                __asm {
                                    movss xmm0, w
                                    maxss xmm0, lo
                                    minss xmm0, hi
                                    movss w, xmm0
                                }
                                float groundR = pm->FUN_00b82310(&center);
                                Vector3_s00c1_aad0 e;
                                e.x = center.x - pos->x;
                                e.z = center.z - pos->z;
                                e.y = center.y - pos->y;
                                float e2 = (e.x * e.x + e.z * e.z) + e.y * e.y;
                                float tt = sqrtf(e2) / cap;
                                float einv = 1.0f / sqrtf(e2 + 1e-8f);
                                float vz = (groundR - posLen) / tt - (tt * g) * 0.5f;
                                const float* pv = &range;
                                if (!(vz > range))
                                    pv = &vz;
                                float vzc = *pv;
                                Vector3_s00c1_aad0 acc;
                                acc.x = (up.x * vzc + (einv * e.x) * cap) - vel->x;
                                acc.y = (up.y * vzc + (e.y * einv) * cap) - vel->y;
                                acc.z = (up.z * vzc + (e.z * einv) * cap) - vel->z;
                                me->FUN_00c446d0(&acc, false);
                                FUN_00c15dc0((float)arg);
                                if (bLeaping) {
                                    if (sp->m698 > 0u)
                                        InterruptAnimation(0x77300f2, -1, 0);
                                    else
                                        InterruptAnimation(0x5261d56, -1, 0);
                                    mState = 3;
                                    mbLeaping = false;
                                } else {
                                    if (sp->m698 > 0u)
                                        InterruptAnimation(0x77300ff, -1, 0);
                                    else
                                        InterruptAnimation(0x5485a4c, -1, 0);
                                    me->Submit(cLocomotionRequest());
                                }
                            }
                        }
                    }
                L_submit:
                    me->Submit(cLocomotionRequest(ob->GetPos(), 1.0f, 2.0f));
                    return;
                }
            }
        }
    }
    FUN_00c18b40(arg);
}

// @ 0x00c1cdd0
void cSPCreatureBase_s00c1_c9f0::FUN_00c1cdd0(i32 a)
{
    if (mp_b54 == 0)
        return;

    i32 idx = FUN_00c0c080(0x0d);
    if (idx == -1)
        idx = FUN_00c0c080(0x52);

    i32 r = vB4(idx);

    if (r != 0 && mb_bb1 != 0) {
        f32 t = (f32)((f64)(u32)a * DAT_013f9428) * *(f32*)((char*)r + 0x104);
        FUN_00c15dc0(t);
        if (mf_e58 == _HK_REAL_ZERO)
            SetStealthed(0, 0);
    }

    if (mb_b5e == 0 && (mdw_b58 & 0x800) == 0) {
        f32 p = (f32)pow(DAT_01447a10, (f64)(u32)a * DAT_013f9428);
        f32 target = (mb_bb1 != 0) ? DAT_013ec480 : 1.0f;
        f32 nv = (1.0f - p) * target + mf_b7c * p;
        mf_b7c = nv;
        if (nv > DAT_013f7344)
            mf_b7c = 1.0f;
        mp_b54->mf_80 = mf_b7c;
    }
}

// @ 0x00c1de20
uint Creature::ChooseAbility(AbilityMask* mask, Creature* target, float dist, bool flag)
{
    uint best = (uint)-1;
    if (mActiveAbility != (uint)-1)
        return best;

    if (mask) {
        mask->w[2] &= 0xfffffdff;
        mask->w[0] &= 0xdfffffff;
    }
    float scale = GetScale(0, this);

    Creature* tc = target ? target->Query(0xd0036e08) : 0;
    bool nearTarget = false;
    if (tc) {
        TypeObj* owner;
        TypeHolder* holder = tc->mpTypeHolder;
        if (holder && (owner = holder->Get()) != 0 && owner->GetType() == kCombatantTypeId) {
        } else {
            owner = 0;
        }
        if ((void*)owner == (void*)this) {
            Body_s00c1_d640* tb = &tc->mBody;
            Body_s00c1_d640* mb = &mBody;
            float d = DistanceBetweenBodies(mb->GetPos(), mb->GetRadius(), tb->GetBodyPos(), tb->GetRadius(), true);
            if (dist < 5.0f || d < 5.0f)
                nearTarget = true;
        }
    }

    uint count = GetAbilityCount();
    float bestScore = 0.0f;
    bool bestReady = false;
    Ability* bestAbility = 0;
    float bestMargin = dist;
    UIntVector cands;
    cands.mpBegin = 0; cands.mpEnd = 0; cands.mpCapacity = 0;
    for (uint i = 0; i < count; ++i) {
        Entry* e = &mpEntries[i];
        Ability* a = GetAbility(i);
        if (mask && !mask->test(a->id))
            continue;
        if (tc) {
            if (!((tc->IsUpper() && a->id == 0x3d) || a->m120 == -1)) {
                if (tc->mCooldownCount > 0)
                    continue;
            }
        }
        if (a->mKind != 1 || a->mbBusy || !(mEnergy >= a->f104))
            continue;

        float lo = (a->ff4 + a->fa8) * scale;
        float hi = a->GetBound(IsUpper()) * scale;
        bool inRange = lo >= dist && dist >= hi;
        bool noBound = lo < 10.0f && a->GetBound(IsUpper()) == 0.0f;
        float score = (a->f84 + a->f3c) / a->f9c;
        bool ready = e->f4 >= 1.0f;
        uint id = a->id;
        switch (id) {
        case 0x1f:
            if (inRange && ready) score = gChargeScale * score;
            break;
        case 0x48:
            if (inRange && ready) score = 90.0f;
            break;
        case 0x4b:
            if (inRange && ready) score = 100.0f;
            else score = 0.0f;
            break;
        }
        if (!noBound && id != 0x1f)
            score = gBoundScale * score;

        float penalty = 0.0f;
        float margin = dist;
        if (!inRange) {
            float gap = 0.0f;
            float w = 1.0f;
            if (dist > lo) {
                gap = dist - lo;
                margin = lo;
            } else if (hi > dist) {
                gap = hi - dist;
                margin = hi;
                w = 0.5f;
            }
            float norm = mbNoBonus ? F00c0ce80(2, 1) + 10.0f : F00c0ce80(2, 0);
            penalty = gap / norm * w;
        }

        if ((noBound && !flag) || (inRange && ready) || (!nearTarget && !flag)) {
            score = score - penalty * score * 0.1f;
            if (score > bestScore || !bestAbility) {
                bestMargin = margin;
                bestScore = score;
                best = i;
                bestReady = ready;
                bestAbility = a;
            }
            cands.push_back(i);
        }
    }

    if (bestMargin == dist && !bestReady) {
        float top = 0.0f;
        int n = (int)(cands.mpEnd - cands.mpBegin);
        for (int j = 0; j < n; ++j) {
            uint idx = cands.mpBegin[j];
            Entry* e = &mpEntries[idx];
            Ability* a = GetAbility(idx);
            float lo = (a->ff4 + a->fa8) * scale;
            float hi = a->GetBound(IsUpper()) * scale;
            bool inRange = lo >= dist && dist >= hi;
            bool ready = e->f4 >= 1.0f;
            if (inRange && ready) {
                float extra = bestAbility ? bestAbility->f104 : 0.0f;
                if (mEnergy > a->f104 + extra) {
                    float s = (a->f84 + a->f3c) / a->f9c;
                    if (s > top) {
                        top = s;
                        best = idx;
                    }
                }
            }
        }
    }
    return best;
}

// @ 0x00c1f650
void cCurvePointVector::PushBackDefault()
{
    cCurvePoint* p = mpEnd;

    if (p < mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            new (p) cCurvePoint;
        }
        return;
    }

    cCurvePoint value;
    InsertValue(p, &value);
}

// @ 0x00c1f8d0
cSPCreatureBase_s00c1_f580::cSPCreatureBase_s00c1_f580()
: mBundle34()
    , mMotion58()
    , mSampleC0()
    , mTarget590()
    , mCombatant5a8()
    , mField670()
    , mTimerB90()
{
    // ---- behaviour-tree / path state (inside cField670) ------------------
    mField670.mByte4a0 = 0;                 // +0xb10
    mField670.mByte4a8 = 0;                 // +0xb18
    mField670.mField4b0 = 0;                // +0xb20
    mField670.mField4b4 = 0;                // +0xb24
    mField670.mField4b8 = 0;                // +0xb28
    mField670.mField4bc = 0;                // +0xb2c
    mField670.mField4c0 = 0;                // +0xb30
    mField670.mField4c4 = 1;                // +0xb34
    mField670.mpStr4c8 = gEmptyString16;         // +0xb38  (empty wide string)
    mField670.mpStr4cc = gEmptyString16;         // +0xb3c
    mField670.mpStr4d0 = gEmptyString16 + 1;     // +0xb40  (its terminator)
    mField670.mpField4d8 = 0;               // +0xb48
    mField670.mpTree4dc  = 0;               // +0xb4c
    mField670.mpField4e0 = 0;               // +0xb50
    mField670.mField4e4 = 0;                // +0xb54
    mField670.mField4e8 = 0;                // +0xb58
    mField670.mBytes4ec[0] = 0;             // +0xb5c  (four zeroed bools)
    mField670.mBytes4ec[1] = 0;
    mField670.mBytes4ec[2] = 0;
    mField670.mBytes4ec[3] = 0;
    mField670.mBytes4ec[4] = 0;
    mField670.mBytes4ec[5] = 0;
    mField670.mBytes4ec[6] = 0;
    mField670.mBytes4ec[7] = 0;             // +0xb63
    mField670.mByte4f4 = 1;                 // +0xb64
    mField670.mBytes4f5[0] = 0;             // +0xb65
    mField670.mBytes4f5[1] = 0;
    mField670.mBytes4f5[2] = 0;             // +0xb67
    mField670.mByte4f8 = 1;                 // +0xb68
    mField670.mByte4f9 = 0;                 // +0xb69
    mField670.mpField4fc = 0;               // +0xb6c
    mField670.mField500 = 0;                // +0xb70
    mField670.mField504 = 0;                // +0xb74
    mField670.mField50c = gHKRealOne;       // +0xb7c  (standard speed = 1)
    mField670.mField510 = 0.0f;             // +0xb80  (turn rate)
    mField670.mField514 = gField13f1cac;    // +0xb84
    mField670.mField518 = 5;                // +0xb88

    // ---- goal / timer block ----------------------------------------------
    mTimerB90.mField20 = 0.0f;              // +0xbb0
    mTimerB90.mField24 = 0;                 // +0xbb4
    mTimerB90.mField28 = 0.0f;              // +0xbb8
    mTimerB90.mField2c = 100.0f;            // +0xbbc  (v2 = (100,0,0))

    mFieldBe0 = gVecBe0;                    // +0xbe0  (goal.facing)
    mFieldBe4 = gVecBe4;                    // +0xbe4  (movementMode)
    mFieldBe8 = gVecBe8;                    // +0xbe8  (acceptableStopDistance)
    mFieldBec = 0;                          // +0xbec
    mFieldBf0 = 0;                          // +0xbf0
    mFieldBf4 = 0;                          // +0xbf4
    mFieldBf8 = 0;                          // +0xbf8
    mFieldBfc = 0;                          // +0xbfc
    mFieldC00 = 0;                          // +0xc00
    mFieldC04 = 0;                          // +0xc04
    mFieldC08 = 0;                          // +0xc08
    mFieldC0c = 0;                          // +0xc0c

    // ---- neighbour vector with an in-place buffer ------------------------
    mpFixedBegin    = (uint*)mFixedBuffer;                  // +0xc28
    mpFixedEnd      = (uint*)mFixedBuffer;                  // +0xc2c
    mpFixedCapacity = (uint*)(mFixedBuffer + 0x80);         // +0xc30
    mFieldC3c = 0;                                          // +0xc3c

    // ---- the two pooled data blocks --------------------------------------
    mpFieldCc0 = 0;                         // +0xcc0
    mpFieldCc4 = 0;                         // +0xcc4

    char scratch;                           // address-only, as in the image
    mBlockCc8.FUN_00c1f580(&scratch, &scratch);     // +0xcc8
    mBlockD68.FUN_00c1f580(&scratch, &scratch);     // +0xd68

    // ---- reference lists -------------------------------------------------
    mFieldE14 = 0;                          // +0xe14
    mFieldE18 = 0;                          // +0xe18
    mFieldE1c = 0;                          // +0xe1c
    mpFieldE0c = (void*)&mpFieldE0c;         // +0xe0c  (self-referential list head)
    mpFieldE10 = (void*)&mpFieldE0c;         // +0xe10
    mFieldE24 = 0;                          // +0xe24
    mFieldE28 = 0;                          // +0xe28
    mFieldE2c = 0;                          // +0xe2c
    mByteE38  = 0;                          // +0xe38
    mFieldE3c = -1;                         // +0xe3c
    mCurvesE40.mpBegin    = 0;              // +0xe40
    mCurvesE40.mpEnd      = 0;              // +0xe44
    mCurvesE40.mpCapacity = 0;              // +0xe48
    mFieldE54 = 0;                          // +0xe54
    mFieldE58 = gField13ec5b4;              // +0xe58
    mFieldE5c = gField13ec5b4;              // +0xe5c
    mBytesE60[0] = 0;                       // +0xe60
    mBytesE60[1] = 0;
    mBytesE60[2] = 0;
    mBytesE60[3] = 0;
    mFieldE64 = 0;                          // +0xe64
    mByteE68  = 0;                          // +0xe68
    mFieldE6c = 0;                          // +0xe6c
    mFieldE70 = -1;                         // +0xe70
    mFieldE74 = -1;                         // +0xe74
    mByteE78  = 0;                          // +0xe78
    mpFieldE7c = 0;                         // +0xe7c
    mFieldE80 = 0;                          // +0xe80
    mFieldE84 = 0;                          // +0xe84
    mFieldE88 = 0;                          // +0xe88
    mFieldE8c = -1;                         // +0xe8c
    mFieldE90 = -1;                         // +0xe90
    mFieldE94 = 0.0f;                       // +0xe94
    mFieldE98 = 0;                          // +0xe98
    mFieldE9c = 0;                          // +0xe9c
    mFieldEa0 = 0;                          // +0xea0
    mFieldEac = 0;                          // +0xeac
    mFieldEd8 = 0;                          // +0xed8
    mFieldEdc = 0;                          // +0xedc
    mFieldEe0 = 0;                          // +0xee0
    mFieldEe8 = 0;                          // +0xee8
    mFieldEb4 = 0;                          // +0xeb4
    mFieldF0c = 0;                          // +0xf0c
    mFieldF10 = 0;                          // +0xf10
    mFieldF14 = 0;                          // +0xf14
    mFieldF1c = 0;                          // +0xf1c
    mFieldF40 = 0;                          // +0xf40
    mFieldF44 = 0;                          // +0xf44
    mFieldF48 = 0;                          // +0xf48
    mFieldF50 = 0;                          // +0xf50
    mFieldF74 = 0;                          // +0xf74
    mFieldF78 = 0;                          // +0xf78
    mFieldF7c = 0;                          // +0xf7c
    mFieldF80 = gField15716d4;              // +0xf80
    mpFieldF84 = (void*)&mpFieldF84;         // +0xf84  (self-referential list head)
    mpFieldF88 = (void*)&mpFieldF84;         // +0xf88
    mFieldF8c = 0;                          // +0xf8c
    mByteF90  = 1;                          // +0xf90
    mFieldF94 = 0;                          // +0xf94
    mFieldF98 = 0;                          // +0xf98
    mFieldF9c = 0;                          // +0xf9c
    mFieldFa0 = 0;                          // +0xfa0
    mFieldFa4 = 0;                          // +0xfa4

    mSampleC0.mField1f0 = 0;                // +0x2b0
    mSampleC0.mField54  = 1;                // +0x114

    // ---- health / combat numbers out of the property bag -----------------
    uint hashHealth = FNVHash("StandardCreatureHealth", 0x811c9dc5, 1);
    uint hashCombat = FNVHash("Combat", 0x811c9dc5, 1);
    float property = SP_GetPropertyT_float(hashCombat, 0, hashHealth, 100.0f);
    mCombatant5a8.mHealth2c = property;     // +0x5d4
    mCombatant5a8.mCombat38 = property;     // +0x5e0

    gField15716d8 = 0;                      // +0x15716d8
    gField15716dc = -1;                     // +0x15716dc
    gField15716e0 = 0;                      // +0x15716e0
    gField15716e4 = 1;                      // +0x15716e4

    mFieldFa8 = 0.0f;                       // +0xfa8

    mFieldFac = ce80(1, 1);                 // +0xfac
    mFieldFb0 = ce80(2, 1);                 // +0xfb0
    mFieldFb4 = ce80(3, 1);                 // +0xfb4
    mSampleC0.mField1e4 = mFieldFb0;        // +0x2a4  (copy of the middle value)

    mField670.mField51c = 0;                // +0xb8c
    mTimerB90.FUN_00bc3170();

    cPropertyBag* bag = FUN_00b3d310_s00c1_f580();
    mSampleC0.FUN_00c421b0(bag->FUN_00c14350());

    mField670.mpTree4dc = new cBehaviorTreeData;    // +0xb4c

    FUN_00c0b5e0((CB*)this);

    mSampleC0.mFlags50 |= 0x200;            // +0x110
    mField670.mField4e8 &= 0xffff778f;      // +0xb58
}

// @ 0x00c1fe80
void cSPCreatureBase_s00c1_f580::FUN_00c1fe80()
{
    mMotion58.FUN_00abf710();
    mTarget590.FUN_00ac0450();
    mBundle34.FUN_00cee7e0();

    vbc();                                  // [this]+0xbc

    FUN_00c0d3a0(this);

    if (mField670.mpTree4dc != 0) {
        mField670.mpTree4dc->FUN_00bcb3d0();
    }
    if (mField670.mpField4d8 != 0) {
        mField670.mpField4d8->FUN_00bc9fe0();
    }

    mCurvesBc0.erase(mCurvesBc0.mpBegin, mCurvesBc0.mpEnd);

    if (mField670.mpField4e0 != 0) {
        cReleaseable* released = mField670.mpField4e0;
        mField670.mpField4e0 = 0;
        released->v04();
    }

    mField670.mField4e8 = 0;

    if (mField670.mpField4fc != 0) {
        FUN_00572020(mField670.mpField4fc, 0);
        mField670.mpField4fc = 0;
    }

    mFieldE3c = -1;
    FUN_00c13340();

    if (mpFieldE7c != 0) {
        cReleaseable* released = mpFieldE7c;
        mpFieldE7c = 0;
        released->v64();
    }

    mField670.mField504 = 0;
    FUN_00c19940(0);

    // The second curve vector is re-based: the tail is relocated and the end
    // pointer advanced by exactly the number of live elements.
    cCurvePoint* curveBegin = mCurvesE40.mpBegin;
    cCurvePoint* curveEnd   = mCurvesE40.mpEnd;
    void* relocated = FUN_00c0ff80(curveEnd, curveEnd, curveBegin);
    mCurvesE40.FUN_00c144b0(relocated, mCurvesE40.mpEnd);

    uint elements = (uint)((char*)curveEnd - (char*)curveBegin) / 0x24;
    mCurvesE40.mpEnd = (cCurvePoint*)((char*)mCurvesE40.mpEnd + elements * 0x24);

    FUN_00c29b00(this);
}

// @ 0x00c1ffb0
void cCreaturePart::FUN_00c1ffb0(char enable)
{
    cSampleC0* samples = (cSampleC0*)((char*)this - 0xd4);
    cSPCreatureBase_s00c1_f580* owner = (cSPCreatureBase_s00c1_f580*)((char*)this - 0x194);

    if (enable != 0) {
        if (mpCurveBeginA2c == mpCurveEndA30) {
            return;
        }

        mField19c &= 0xfffffffb;

        cCurveHolder* holder = samples->FUN_00c41ec0();
        cSampleRef*   ref    = samples->FUN_00c421f0();
        float         limit  = ref->mField0c;

        holder->mPoint14 = *mpCurveBeginA2c;
        if (holder->mField5c == 0) {
            holder->mField5c = 1;
        }

        holder->erase(holder->mpBegin, holder->mpEnd);

        float count = (float)(int)((uint)((char*)mpCurveEndA30
                                         - (char*)mpCurveBeginA2c) / 0x24 - 1);
        float clamped = (count > 0.0f) ? count : 0.0f;
        holder->FUN_00c199e0((int)clamped);

        holder->fn(holder->mpEnd, (void*)((char*)mpCurveBeginA2c + 0x3c),
                   mpCurveEndA30, (int)clamped);

        if (holder->mpBegin != holder->mpEnd) {
            const float kOne = gHKRealOne;
            float value = (kOne > limit) ? kOne : limit;
            holder->mpEnd[-2].mField18 = value;
        }

        owner->cff0(mFieldE08);
        return;
    }

    // Switch the part off: record the disabled state and remember its anchors.
    mField19c = 8;
    gVec168e81c.push_back(mAnchorD4);
    gVec168e81c.push_back(mAnchorE0);
}

// @ 0x00c201a0
void* cCreatureFactory::FUN_00c201a0(char flag, void* param2, void* param3)
{
    cFactoryObject* created;

    if (flag != 0) {
        cFactoryObject* found = (cFactoryObject*)FUN_00c14e70(param3);
        if (found != 0 && found->o10()) {
            return 0;
        }

        FUN_00c17350(param3, 0);

        created = (cFactoryObject*)FUN_00c1d120(param2, param3);
        if (created != 0) {
            created->o08(0);
        }
        return created;
    } else {
        FUN_00c17350(param3, 0);
    }
    return 0;
}

// @ 0x00c20210
void cCreatureFactory::FUN_00c20210(void* param1, void* param2)
{
    FUN_00c201a0((char)param1, param2, param2);
}

// @ 0x00c22210
void cSPCreatureBase_s00c2_2010::FUN_00c22210(int nAge)
{
    mn0xB34 = nAge;
    FUN_00c21bf0(1, 1);
    this->mSub58.vIdx13();
}

// @ 0x00c22240
void cSPCreatureBase_s00c2_2010::FUN_00c22240()
{
    float fMax = this->GetMaxHealth();
    float fRatio = this->mf0x38 / fMax;
    mn0xB34 = 1;
    FUN_00c21bf0(1, 1);
    this->mSub58.vIdx13();
    float fScale = this->vIdx32(0);
    this->lo40(fScale);
    ((cLocoWrapper*)FUN_00b3d310())->FUN_00b48770(this, 1);
    float f = this->GetMaxHealth() * fRatio;
    this->SetHealth(f);
    this->mb0x89 = 1;
    ((cObj0xB48*)mp0xB48)->FUN_00bc9fe0();
}

// @ 0x00c22470
bool cSPCreatureBase_s00c2_2010::FUN_00c22470(void* pArg)
{
    if (mb0xB67 != 0 && mb0x75 == 0)
        return true;

    cSpeciesProfile_s00c2_2010* p1 = ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28);
    if (FUN_00b183f0(pArg) == 0)
        return false;

    bool b;
    if (mKey0xB28.mA == 0) {
        b = (mb0x75 == 0);
    } else {
        cSpeciesProfile_s00c2_2010* p2 = ((cSpeciesManager*)FUN_00401090())->GetProfile(mKey0xB28);
        if (p1 != p2) {
            FUN_00c222f0(p2);
            b = (mpSpeciesProfile != 0);
        } else {
            mpSpeciesProfile = p2;
            FUN_00c21bf0(1, 1);
            b = (mpSpeciesProfile != 0);
        }
    }
    if (b && mp0xE80 != 0)
        mp0xE84 = (cSpeciesArchetype*)((cSpeciesManager*)FUN_00401090())
                      ->GetSpeciesArchetype(mp0xE80, 0);
    return b;
}

// @ 0x01335000
namespace Simulator {
void InitCreatureBaseAttributes()
{
    {
        Attribute a("mbTeleport", 0x02415ec6, 0xb5d,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[0] = a;
    }
    {
        Attribute a("mbDead", 0x02415ebc, 0xb5e,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[1] = a;
    }
    {
        Attribute a("mbUpdateInteractionEffect", 0x02415ebd, 0xb60,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[2] = a;
    }
    {
        Attribute a("mbUpdateMotiveEffect", 0x02415ebe, 0xb61,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[3] = a;
    }
    {
        Attribute a("mbIsDiseased", 0x0303fb98, 0xb62,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[4] = a;
    }
    {
        Attribute a("mLastInteractionEffect", 0x021d1baa, 0xcc4,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[5] = a;
    }
    {
        Attribute a("mLastMotiveState", 0x021d1bab, 0xcc0,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[6] = a;
    }
    {
        Attribute a("mSpeciesKey", 0x03f64a78, 0xb28,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cCreatureBase_sAttributes[7] = a;
    }
    {
        Attribute a("mProfileSeq", 0x02415ec8, 0xb24,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[8] = a;
    }
    {
        Attribute a("mAge", 0x52773f6f, 0xb34,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[9] = a;
    }
    {
        Attribute a("mbCasted", 0x024cd902, 0xb67,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[10] = a;
    }
    {
        Attribute a("mpWhoIsInteractingWithMe", 0xb2774021, 0xb50,
                  Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[11] = a;
    }
    {
        Attribute a("mbStealthed", 0x06948b64, 0xbb1,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[12] = a;
    }
    {
        Attribute a("mCurrentLoudness", 0xd277405a, 0xb80,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[13] = a;
    }
    {
        Attribute a("mFoodValue", 0x021d1ba5, 0xb84,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[14] = a;
    }
    {
        Attribute a("mbHasBeenEaten", 0x72774074, 0xb5f,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[15] = a;
    }
    {
        Attribute a("mStrengthRating", 0x021d1bac, 0xb88,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[16] = a;
    }
    {
        Attribute a("mSpeedState", 0x02415eca, 0xf98,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cCreatureBase_sAttributes[17] = a;
    }
    {
        Attribute a("mCreatureName", 0x03d97b19, 0xb38,
                  Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
                  Validate_00b1fbf0, ToXml_00acbbc0);
        *(Attribute*)&cCreatureBase_sAttributes[18] = a;
    }
    {
        Attribute a("mCurrentAttackIdx", 0x021d239f, 0xe8c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[19] = a;
    }
    {
        Attribute a("mCurrentAttackAnimId", 0x0547c1bf, 0xe90,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[20] = a;
    }
    {
        Attribute a("mbColorIsIdentity", 0x042a2b0e, 0xb65,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cCreatureBase_sAttributes[21] = a;
    }
    {
        Attribute a("mHunger", 0x05501f64, 0xbbc,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[22] = a;
    }
    {
        Attribute a("mHungerDelta", 0x05501f65, 0xbb8,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[23] = a;
    }
    {
        Attribute a("mHungerDelayTimer", 0x04653b60, 0xb90,
                  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00ae3310, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[24] = a;
    }
    {
        Attribute a("mArchetype", 0x33ace6b5, 0xe80,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[25] = a;
    }
    {
        Attribute a("mGeneralFlags", 0x051b38ff, 0xb58,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cCreatureBase_sAttributes[26] = a;
    }
    {
        Attribute a("mNoAttackTimer", 0x5242896a, 0xb78,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cCreatureBase_sAttributes[27] = a;
    }
    {
        Attribute a("DEPRECATED_mRechargingAbilityBits", 0x0528933e, 0xc18,
                  Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
                  Validate_00b1fbf0, ToXml_00595a70);
        *(Attribute*)&cCreatureBase_sAttributes[28] = a;
    }
    {
        Attribute a("DEPRECATED_mInUseAbilityBits", 0x0535a140, 0xc10,
                  Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0,
                  Validate_00b1fbf0, ToXml_00595a70);
        *(Attribute*)&cCreatureBase_sAttributes[29] = a;
    }
    {
        Attribute a("mRechargingAbilityBits", 0x076c8f4d, 0xbf8,
                  Read_00c143c0, Write_00c143e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[30] = a;
    }
    {
        Attribute a("mInUseAbilityBits", 0x076c8f46, 0xbec,
                  Read_00c143c0, Write_00c143e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ac8050);
        *(Attribute*)&cCreatureBase_sAttributes[31] = a;
    }
    {
        Attribute a("mIntentionTowardsTarget", 0x05675535, 0xb74,
                  Read_00c7e9f0, Write_00cd44e0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, (ToXmlFunction_t)Validate_00b1fbf0);  // same stub in both slots
        *(Attribute*)&cCreatureBase_sAttributes[32] = a;
    }
    {
        Attribute a("mAbilityStates", 0x0521e608, 0xc28,
                  Read_00c1b8c0, Write_00c0fba0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00ca8710);
        *(Attribute*)&cCreatureBase_sAttributes[33] = a;
    }
    {
        Attribute a("mItemInventory", 0x05ef360e, 0xe40,
                  Read_00c21260, Write_00c15f60, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c0fc10, ToXml_00c19b60);
        *(Attribute*)&cCreatureBase_sAttributes[34] = a;
    }
}
}  // namespace Simulator
