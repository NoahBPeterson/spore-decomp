// src/game/SPGonzago/SPCreatureBase.cpp -- migrated from slice(s) s01335000, s00c1d640, s00c1aad0, s00c19b60, s00c104d0, s00c0fa70, s00c0ddb0, s00c0ce80, s00c0bd70 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCreatureBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern float  gF_150c8b8, gF_150c8b4, gF_150c8cc, gF_1485720, gF_146a32c, gF_146a330;
extern void*  g_16c7aa4;
extern int    g_15716d8[];
#include <math.h>
#include "SP/cSPCreatureBase.h"
#include "SP/cSPTimer.h"
#include "SP/cCombatant.h"
#include "SP/cLocomotiveObject.h"

// ---- items of slice s00c0bd70 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl SP_GetCurrentGameMode();                 // 0xb5b800
void* __cdecl FUN_00401090();                          // 0x401090
void* __cdecl FUN_004df420();                          // 0x4df420
void  __cdecl FUN_00ef1930(void*, float);              // 0xef1930
void  __cdecl FUN_00ebfd50();                          // 0xebfd50
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
  void __thiscall CopyRec(void* src);
  void __thiscall QuatHalf(float a);
  bool __thiscall C5b0(int a, int b, int* out);
  int  __thiscall RelationIndex(int idx, char b);
  int  __thiscall Cdb0();
  int  __thiscall C200(float f);
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
    char  __thiscall e070(int);
    char  __thiscall e0c0(int);
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
struct CAN {
    void* __thiscall fa70(uint32_t, uint32_t*);
    void  __thiscall fae0(int);
    void  __thiscall fb40(int);
    void  __thiscall fb80(int, int);
    void* __thiscall fe30(void*);
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
int __thiscall C::C200(float f)
{
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10 && *(int*)((char*)g_16c7aa4 + 0xcc) == 2) {
    if (this) FUN_00ef1930((char*)this + 0x5a8, f);
    else FUN_00ef1930(0, f);
  }
  return 0;
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
void __thiscall C::CopyRec(void* srcv)
{
  uint32_t* s = (uint32_t*)srcv;
  uint32_t* d = (uint32_t*)this;
  d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; d[3]=s[3]; d[4]=s[4]; d[5]=s[5];
  *(uint8_t*)(d+6) = *(uint8_t*)(s+6);
  d[7]=s[7];
  void* o = (void*)s[8];
  d[8]=(uint32_t)o;
  if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0xbc/4]))(o);
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
void __thiscall C::QuatHalf(float a)
{
  float* q = (float*)this;
  float x=q[0], y=q[1], z=q[2], w=q[3];
  float c = cosf(a * 0.5f);
  float s = sinf(a * 0.5f);
  q[0] = ((w*c + x*0.0f) - y*s) + z*0.0f;
  q[1] = ((x*c + z*s) + y*0.0f) - w*0.0f;
  q[2] = ((y*c - x*0.0f) + w*s) + z*0.0f;
  q[3] = ((z*c - w*0.0f) - x*s) - y*0.0f;
}









// @ 0x00c0c5b0
bool __thiscall C::C5b0(int a, int b, int* out)
{
  void* gm = SP_GetCurrentGameMode();
  if (gm == (void*)0x1654c10) {
    int r = 0; FUN_00ebfd50(); r = 0;
    *out = r;
    return r != b;
  }
  return false;
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
    if ((bool)param_3 == bVar3) return;
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
        float r = (*(float(__thiscall**)(void*))((*(void***)((char*)this + 0xc0))[0x74 / 4]))((char*)this + 0xc0);
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
            *(uint32_t*)((char*)r2 + 0x15c) = 0;
            ((F_a05270*)r2)->Release();
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
    (*(void(__thiscall**)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    return (void*)local_4;
}







// @ 0x00c0e070
char __thiscall CCM::e070(int param_2)
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
char __thiscall CCM::e0c0(int param_2)
{
    char* c = *(char**)((char*)this + 0xb54);
    if (c == 0) return 0;
    uint32_t local_4 = 0;
    void* vt = *(void**)c;
    (*(void(__thiscall**)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
        c, &local_4, 0, 0, 0);
    if ((int)local_4 == param_2) return 1;
    if (!((F_a02b40*)c)->f((int)local_4)) return 0;
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
    (*(void(__thiscall**)(void*, int, int, void*, int))(*(void**)((char*)vt + 0x58)))(
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
        (*(void(__thiscall**)(void*, void*, void*, int, int))(*(void**)((char*)vt + 0x58)))(
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
        (*(void(__thiscall**)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
        if (local_4 != 0) {
            void* lm = FUN_0067cb20();
            char* r = (char*)(*(void*(__thiscall**)(void*, uint32_t))(*(void**)((char*)lm + 0x40)))(
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
        (*(void(__thiscall**)(void*, void*, int, int, int))(*(void**)((char*)vt + 0x58)))(
            c, &local_4, 0, 0, 0);
    }
    char* r = (char*)(*(void*(__thiscall**)(void*, uint32_t))(*(void**)((char*)lm + 0x40)))(
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






// @ 0x00c0fa70
void* __thiscall CAN::fa70(uint32_t mask, uint32_t* pIndex)
{
    char* base = (char*)this;
    int count = (*(int*)(base + 0xe44) - *(int*)(base + 0xe40)) / 0x24;
    if (count == 0) return 0;
    char* e = *(char**)(base + 0xe40);
    int i = 0;
    do {
        int b = *(int*)(e + 4);
        if (b != 0 && (mask & (1u << (b & 0x1f))) != 0) {
            if (pIndex != 0) *pIndex = (uint32_t)i;
            return e;
        }
        ++i;
        e += 0x24;
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
    for (int i = param_2[0]; i != param_2[1]; i += 0x24) {
        if (i != 0) {
            int* q = *(int**)(i + 0x20);
            (*(void(__thiscall**)(void*, int))((*(int**)q)[0x1c / 4]))((void*)q, param_1);
        }
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
    char* s = (char*)src;
    char* d = (char*)this;
    *(int*)(d + 0x00) = *(int*)(s + 0x00);
    *(int*)(d + 0x04) = *(int*)(s + 0x04);
    *(int*)(d + 0x08) = *(int*)(s + 0x08);
    *(int*)(d + 0x0c) = *(int*)(s + 0x0c);
    *(int*)(d + 0x10) = *(int*)(s + 0x10);
    GF(d + 0x14) = GF(s + 0x14);
    *(char*)(d + 0x18) = *(char*)(s + 0x18);
    *(int*)(d + 0x1c) = *(int*)(s + 0x1c);
    void* old = *(void**)(d + 0x20);
    void* nw = *(void**)(s + 0x20);
    if (nw != old) {
        if (nw != 0) (*(void(__thiscall**)(void*))((*(void***)nw)[0xbc / 4]))(nw);
        *(void**)(d + 0x20) = nw;
        if (old != 0) (*(void(__thiscall**)(void*))((*(void***)old)[0xc0 / 4]))(old);
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
    int e1 = *(int*)(param_3 + 0xfbc);
    if (e1 == 0) return;
    int e2 = *(int*)(e1 + 0x2c0);
    if (e2 == 0) return;
    int e3 = *(int*)(e2 + 8);
    if (e3 == 0) return;
    int* pi = *(int**)(e3 + 0x64);
    int iVar2;
    if (pi == 0) iVar2 = 0;
    else iVar2 = (*(int(__thiscall**)(void*, int))((*(void***)pi)[0xc / 4]))((void*)pi, 0xce9f6639);

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
                    char* base = *(char**)((char*)iVar2 + 0xb54);
                    int v = *(int*)(base + 0x17c);
                    int arr = *(int*)(v + 0x2e4);
                    int elem = *(int*)(arr + local_40[0] * 700);
                    if (0.0f < GF(elem + 0x10c)) uVar6 = 1;
                } else {
                    uVar6 = 0;
                }
            } else {
                void* c = *(void**)((char*)iVar2 + 0xb54);
                void* vt = *(void**)c;
                char* extra = 0;
                uint32_t rr = (*(uint32_t(__thiscall**)(void*, int, uint32_t*, uint32_t, void*))((char*)vt + 0x68))(
                    c, param_4, local_40, uVar7, &extra);
                if (rr < *(uint32_t*)(*(int*)(*piVar3 + 8) + 0x14)) uVar6 = rr;
            }
        }
    }
    void* c2 = *(void**)((char*)iVar2 + 0xb54);
    (*(void(__thiscall**)(void*, int, uint32_t))((char*)*(void**)c2 + 0x3c))(c2, param_4, uVar6);
    if (param_5 == 0 && param_2 != -1) {
        uint32_t val = (uint32_t)param_2;
        for (int i = 0; i < 4; ++i) {
            uint32_t local = 0;
            char* e = ((F_f9b0*)iVar2)->f((int)(val & 0xff), &local);
            if (e != 0 && *(int*)(e + 4) != 0) {
                local_40[6] = local;
                local_40[7] = (uint32_t)param_4;
                local_40[8] = 0;
                FUN_00bca810(5, 0, (void*)iVar2, GF(0x146a32c), &local_40[6], 0);
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
