// src/game/SPGonzago/SPCityCivAttackBehaviors.cpp -- migrated from slice(s) s00d79470, s00d56630, s00d557f0, s00d53b50, s00d54ce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityCivAttackBehaviors.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCombatant.h"
#include "SP/cInteraction.h"
#include "SP/cInteractionAgent.h"
#include "SP/cSPTimer.h"

// unnamed retail callees and globals (address in the comment)
extern float gsSpaceHelixStep;                                  // 0x0169ebf0
#include <math.h>
#include "SP/cTurret.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "cSPVector3.h"
#include "SP/cLocomotiveObject.h"
#include "SP/cPlanetModel.h"
#include "SP/cCity.h"
#include "SP/cActionCircle.h"
#include "SP/cInteractionTarget.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cSpatialObject.h"
#include "SP/cTribe.h"

// ---- items of slice s00d54ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gInteractionAgentTypeInfo;                         // 0x013f94d4
extern void* gsAirRaidEffect;                                   // 0x0169ebe0
class cCombatant {
public:
    int GetDamageState();                                       // 0x008e7f80
    bool IsHostileAlive();                                      // 0x00bfc600
};
class cSPTimer {
public:
    void Stop();                                                // 0x00bc3110
};
class cInteractionAgent {
public:
    void* mpVtable;                                             // 0x00
};
extern cSPTimer gsAirRaidTimer;                                 // 0x0169ebc0
struct cVector3Array {
    float* mpBegin;                                             // 0x00
    float* mpEnd;                                               // 0x04
    float* mpCapacity;                                          // 0x08

    void Clear() { mpEnd = mpBegin; }
};
void Vector3_Push(cVector3Array*, const float*);                // 0x004b5ad0
void Vector3Array_Reserve(uint32_t nCount);                     // 0x00473890
int  GetDetailLevelCount();                                     // 0x011e0810
struct cSlotEntry {
    void* mpObject;                                             // 0x00 AutoRefCount payload
    uint32_t mnFlags;                                           // 0x04
};
struct cSlotBlock {
    uint32_t mnHeader;                                          // 0x00
    cSlotEntry mEntries[128];                                   // 0x04
};
struct cSlotIterator {
    uint8_t* mpBase;                                            // 0x00 container address
    uint32_t mnIndex;                                           // 0x04

    void Increment();                                           // 0x00abe9b0
    bool operator!=(const cSlotIterator& other) const
    {
        return mpBase + mnIndex != other.mpBase + other.mnIndex;
    }
};
struct cAgentSlotVector {
    cSlotBlock** mpBlocks;                                      // 0x00
    cSlotBlock** mpEnd;                                         // 0x04
    uint32_t mnUnk08;                                           // 0x08
    uint32_t mnUnk0c;                                           // 0x0c
    uint32_t mnUnk10;                                           // 0x10
    uint32_t mnFreeChain;                                       // 0x14
    uint32_t mnIndex;                                           // 0x18

    uint32_t EndIndex() const
    {
        return ((int)((char*)mpEnd - (char*)mpBlocks) >> 2) * 128 - 127
               + mnFreeChain;
    }

    cSlotIterator Begin() const
    {
        cSlotIterator it;
        it.mpBase = (uint8_t*)this;
        it.mnIndex = mnIndex;
        if (it.mnIndex >= 0x3fffffff)
            it.mnIndex = EndIndex();
        return it;
    }

    cSlotIterator End() const
    {
        cSlotIterator it;
        it.mpBase = (uint8_t*)this;
        it.mnIndex = EndIndex();
        return it;
    }
};
struct cGonzagoTimerData {
    float mfElapsedTime;                                        // 0x00
    float mfDuration;                                           // 0x04
    uint32_t mnFlags;                                           // 0x08
    uint32_t mnUnk0c;                                           // 0x0c
    uint32_t mnUnk10;                                           // 0x10
    uint32_t mnUnk14;                                           // 0x14
    uint32_t mnUnk18;                                           // 0x18
    uint32_t mnUnk1c;                                           // 0x1c
    uint32_t mnUnk20;                                           // 0x20
    uint32_t mnUnk24;                                           // 0x24

    void Construct();                                           // 0x00b63890
    void Destruct();                                            // 0x00b638b0
};
struct cRBNodeBase {
    cRBNodeBase* mpNodeRight;                                   // 0x00
    cRBNodeBase* mpNodeLeft;                                    // 0x04
    cRBNodeBase* mpNodeParent;                                  // 0x08
    uint8_t mnColor;                                            // 0x0c
    uint8_t mPad0d[3];                                          // 0x0d
};
struct cTurretStateTree {
    uint32_t mnUnk00;                                           // 0x00
    cRBNodeBase mAnchor;                                        // 0x04
    uint32_t mnSize;                                            // 0x14
    uint32_t mnUnk18;                                           // 0x18

    void NukeSubtree(cRBNodeBase* pNode);                       // 0x00d54ac0
};
class cInteraction {
public:
    cInteraction();                                             // 0x00abf320
    ~cInteraction();                                            // 0x00abf190

    void* mpVtable;                                             // 0x00 vtbl_Simulator::cBehaviorSpaceTurret
    void* mpRefCountVtable;                                     // 0x04
    uint32_t mUnk08[9];                                         // 0x08
    cAgentSlotVector mAgentList;                                // 0x2c
};
class cBehaviorSpaceTurret : public cInteraction {
public:
    cBehaviorSpaceTurret();                                     // 0x00d54fa0
    ~cBehaviorSpaceTurret();                                    // 0x00d54e50
    int GetActiveTurretCount();                                 // 0x00d54ce0
    int CountAttackableTurrets();                               // 0x00d54d90

    uint32_t mUnk48[11];                                        // 0x48
    cTurretStateTree mStateTree;                                // 0x74
    cGonzagoTimerData mLifeTimer;                               // 0x90
    uint32_t mnUnkB8;                                           // 0xb8
    uint32_t mnUnkBc;                                           // 0xbc
    uint32_t mnUnkC0;                                           // 0xc0
    uint32_t mnUnkC4;                                           // 0xc4
    uint32_t mnSdrBeamLifetime;                                 // 0xc8
    uint32_t mnUnkCc;                                           // 0xcc
    uint32_t mnUnkD0;                                           // 0xd0
    uint32_t mnUnkD4;                                           // 0xd4
    uint8_t mbAirRaidDone;                                      // 0xd8
    uint8_t mUnkD9[7];                                          // 0xd9
    cGonzagoTimerData mAirRaidTimer;                            // 0xe0
};
// ---- items of slice s00d54ce0 end

// ---- items of slice s00d53b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
typedef Vec3 Vector3;
namespace SP {
struct RefCounted
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void AddRef();                                  // +0x18
};
}
namespace SP {
struct WeaponSource                                         // the game-data template (0x24 bytes)
{
    void*        mpObject;                                  // +0x00
    RefCounted*  mpRef;                                     // +0x04
    uint32_t     mValues[7];                                // +0x08
};
}
namespace SP {
struct WeaponData                                           // the turret's copy (0x2c bytes)
{
    void*        mpObject;                                  // +0x00
    uint32_t     mFlags;                                    // +0x04
    void*        mpTemplate;                                // +0x08
    RefCounted*  mpRef;                                     // +0x0c
    uint32_t     mValues[7];                                // +0x10

    WeaponData(const WeaponData& src);                      // 0x00d54780
    WeaponData(void* const* ppObject, const WeaponSource& src);     // 0x00d548e0
};
}
namespace SP {
struct SPObject
{
    PV(0) PV(1)
    virtual void* QueryInterface(uint32_t nID);             // +0x08
};
}
namespace SP {
bool __stdcall CanJoin(void* pObject, int nUnused);         // 0x00d54730
}
namespace SP {
struct cSPTimer_s00d5_3b50
{
    void Stop();                                            // 0x00bc3110
    void Restart();                                         // 0x00bc3130
    bool IsRunning();                                       // 0x00feba90
    unsigned long long GetElapsedTime();                    // 0x00bc3190
};
}
namespace SP {
struct EffectParams;
}
namespace SP {
struct IVisualEffect
{
    PV(0)
    virtual void Release();                                 // +0x04
    virtual void Start(int bImmediate);                     // +0x08
    virtual void Stop(int bImmediate);                      // +0x0c
    PV(4) PV(5)
    virtual void SetParams(const EffectParams* pParams);    // +0x18
};
}
namespace SP {
template <class T>
struct AutoRef {                                            // EA::RefCounted::AutoRefCount
    T* mpObject;                                            // +0x00
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    void reset() {
        if (mpObject) {
            T* pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
    }
};
}
namespace SP {
extern cSPTimer_s00d5_3b50       sAirRaidTimer;                        // 0x0169ebc0
}
namespace SP {
extern AutoRef<IVisualEffect> spAirRaidEffect;              // 0x0169ebe0 (AutoRefCount)
}
namespace SP {
void StopAirRaidEffect();                                   // 0x00d54760
}
namespace SP {
typedef int64_t int64;
}
namespace SP {
struct Property
{
    uint16_t mPad00[9];                                     // +0x00
    uint16_t mType;                                         // +0x12 (property type id)
    int*     GetInt();                                      // 0x0041e990
    float*   GetFloat();                                    // 0x0041ea70 (GetPropertyAsFloat)
};
}
namespace SP {
struct PropertySet
{
    PV(0)
    virtual void Release();                                 // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t nID, Property** ppOut);   // +0x24
};
}
namespace SP {
struct PropertyManager
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual bool FindPropertySet(uint32_t nID, PropertySet** ppOut);   // +0x30
};
}
namespace SP {
PropertyManager* GetPropertyManager();                      // 0x0067de30
}
namespace SP {
struct Matrix33
{
    float m[9];
    void Assign(const Matrix33& src);                       // 0x0041cb40 (cSPMatrix3::Assign)
};
}
namespace SP {
struct EffectParams                                         // what SetParams takes
{
    uint16_t mFlags;                                        // +0x00
    uint16_t mCount;                                        // +0x02
    Vector3  mPosition;                                     // +0x04
    float    mScale;                                        // +0x10
    Matrix33 mMatrix;                                       // +0x14
};
}
namespace SP {
struct IEffectsManager
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual IVisualEffect* CreateEffect(uint32_t nID, void* pOwner, IVisualEffect** ppOut);   // +0x2c
};
}
namespace SP {
IEffectsManager* EffectsManagerPtr();                       // 0x0067ddd0
}
namespace SP {
struct cSPSpaceCombatTuning
{
    unsigned long long GetAirRaidSirenTimeMS();             // 0x01029af0
};
}
namespace SP {
cSPSpaceCombatTuning* GetSpaceCombatTuning();               // 0x01029940
}
namespace SP {
struct TurretTransform
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vector3* GetTranslation();                // +0x2c
};
}
namespace SP {
struct WeaponEffectSlot
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void Stop(int bImmediate);                      // +0x50
};
}
namespace SP {
struct cTurret_s00d5_3b50
{
    PV(0)
    virtual void* QueryInterface(uint32_t nID);             // +0x08
    char              pad0c[0x120 - 4];
    TurretTransform   mTransform;                           // +0x120
    char              pad124[0x588 - 0x124];
    WeaponEffectSlot  mEffect;                              // +0x588
    void FaceAtTarget(int nTarget);                         // 0x00bce480
};
}
namespace SP {
struct SlotEntry
{
    uint32_t mPad00;                                        // +0x00
    void*    mpItem;                                        // +0x04
};
}
namespace SP {
struct SlotBucket { SlotEntry mEntries[128]; };
}
namespace SP {
struct SlotVector                                           // spstl::slot_vector_base (128 entries per bucket)
{
    SlotBucket** mpBuckets;                                 // +0x00
    SlotBucket** mpBucketsEnd;                              // +0x04
    uint32_t     mPad08[3];
    int          mTail;                                     // +0x14
    int          mCount;                                    // +0x18
};
}
namespace SP {
struct SlotIter
{
    SlotVector* mpVector;                                   // +0x00
    uint32_t    mIndex;                                     // +0x04
    void increment();                                       // 0x00abe9b0
};
}
namespace SP {
struct cBehaviorSpaceTurret_s00d5_3b50
{
    char     pad00[0xc0];
    void*    mpTarget;                                      // +0xc0
    uint32_t mPadC4;
    int      mSdrBeamLifetime;                              // +0xc8
    uint32_t mPadCC;
    uint64_t mWeaponTimerMS;                                // +0xd0
    char     padD8[0x120 - 0xd8];
    TurretTransform mTransform;                             // +0x120

    void UpdateWeaponData();                                // 0x00d547e0
    void UpdateAirRaidSiren();                              // 0x00d54940
};
}
namespace SP {
bool __cdecl UpdateAirRaidSiren(cBehaviorSpaceTurret_s00d5_3b50* pTurret);   // 0x00d54940
}
namespace SP {
void __cdecl ClearAllTargets(SlotVector* pVec);                   // 0x00d54c10
}
namespace SP {
extern Vector3 sAirRaidSirenOffset;                         // 0x0169ec18
}
namespace SP {
extern Matrix33 sAirRaidSirenMatrix;                        // 0x0169ebf4
}
static int SlotEnd(SP::SlotVector* pVec)
{
    return (int)(pVec->mpBucketsEnd - pVec->mpBuckets) * 0x80 + pVec->mTail - 0x7f;
}
// ---- items of slice s00d53b50 end

// ---- items of slice s00d557f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl sqrt(double);
extern float g_169ebf0;     // base angular step (radians)
#pragma intrinsic(cos, sin, sqrt)
inline void* operator new(unsigned int, void* p) throw() { return p; }
struct Vector3_s00d5_57f0 {
    float x, y, z;
    Vector3_s00d5_57f0() {}
    Vector3_s00d5_57f0(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s00d5_57f0(const Vector3_s00d5_57f0& o) : x(o.x), y(o.y), z(o.z) {}
};
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
};
template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    T* erase(T* first, T* last);
    void DoInsertValue(T* pos, const T& v);
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
    void clear() { erase(mpBegin, mpEnd); }
};
typedef SpVector<Vector3_s00d5_57f0> Vec3Vector;
template <> Vector3_s00d5_57f0* Vec3Vector::erase(Vector3_s00d5_57f0* first, Vector3_s00d5_57f0* last);          // 0x50f740
template <> void Vec3Vector::DoInsertValue(Vector3_s00d5_57f0* pos, const Vector3_s00d5_57f0& v);     // 0x4b5ad0
static __forceinline void AddStarRing(Vec3Vector& out, const Vector3_s00d5_57f0& p, const Vector3_s00d5_57f0& d,
                               float scale, float angle, const float& step)
{
    for (int i = 5; i != 0; --i) {
        float inv = 1.0f / (float)sqrt(p.x * p.x + (p.z * p.z + p.y * p.y));
        float s = (float)sin(angle * 0.5f);
        float c = (float)cos(angle * 0.5f);
        float qy = (p.y * inv) * s;
        float qz = (p.z * inv) * s;
        float qx = s * (inv * p.x);
        float rx = (((c * qy + qz * qx) * d.z + (qy * qx - c * qz) * d.y) * 2.0f +
                     (1.0f - (qz * qz + qy * qy) * 2.0f) * d.x) * scale + p.x;
        float ry = (((qz * qy - c * qx) * d.z + (c * qz + qy * qx) * d.x) * 2.0f +
                     (1.0f - (qz * qz + qx * qx) * 2.0f) * d.y) * scale + p.y;
        float rz = (((c * qx + qz * qy) * d.y + (qz * qx - c * qy) * d.x) * 2.0f +
                     (1.0f - (qx * qx + qy * qy) * 2.0f) * d.z) * scale + p.z;
        Vector3_s00d5_57f0 r(rx, ry, rz);
        out.push_back(r);
        angle = step + angle;
    }
}
struct Target {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void Release();          // vtable +0x14
};
struct cSpaceTurretStateInfo {
    int32_t  mState;                 // +0x00
    Target*  mpTarget;               // +0x04
    uint64_t mNextMissileTime;       // +0x08
    uint64_t mNextBeamTime;          // +0x10
    uint64_t mBeamCutoffTime;        // +0x18
    int32_t  mBehaviorIndex;         // +0x20
};
struct RBNodeBase {
    RBNodeBase* mpNodeRight;         // +0x00
    RBNodeBase* mpNodeLeft;          // +0x04
    RBNodeBase* mpNodeParent;        // +0x08
    uint32_t    mColor;              // +0x0c
};
struct StateNode : RBNodeBase {
    int32_t mKey;                    // +0x10
    int32_t mPad14;                  // +0x14
    cSpaceTurretStateInfo mValue;    // +0x18
};
struct StatePair {
    int32_t mKey;                    // +0x00
    int32_t mPad04;                  // +0x04
    cSpaceTurretStateInfo mValue;    // +0x08
    StatePair* Construct(const int* key, const cSpaceTurretStateInfo* src);   // 0x00d548e0
};
struct InsertTag { unsigned char mValue; InsertTag() : mValue(0) {} };
struct StateMap {
    uint32_t   mUnused;              // +0x00
    RBNodeBase mAnchor;              // +0x04
    uint32_t   mSize;                // +0x14

    void Insert(StateNode** out, StateNode* position, const StatePair* value,
                InsertTag unique);   // 0x00d54ed0
    cSpaceTurretStateInfo& GetOrInsert(const int& key);
};
struct cLocomotiveObject {
    Vector3_s00d5_57f0* GetVelocity();          // 0x00d20610
};
struct cInteractionAgent;
struct cInteraction_s00d5_57f0 {
    char mBase[0x74];
    bool AddAgent(cInteractionAgent* pAgent);   // 0x00abf640
};
extern Vector3_s00d5_57f0 g_169ebe4;           // 0x0169ebe4 reference direction constant
static __forceinline Vector3_s00d5_57f0* GetObjectDirection(void* obj)
{
    void** vtbl = *(void***)obj;
    return ((Vector3_s00d5_57f0* (__thiscall*)(void*))vtbl[0x2c / 4])(obj);
}
struct cPlanetModel {
    char pad[0x100];
    Vector3_s00d5_57f0* DirectionToSurfacePosition(Vector3_s00d5_57f0* out, const Vector3_s00d5_57f0* dir);        // 0x00b815a0
    Vector3_s00d5_57f0* MakeRandomWorldPosition(Vector3_s00d5_57f0* out, const Vector3_s00d5_57f0* dir, float a, float b); // 0x00b81780
};
cPlanetModel* PlanetModel();        // 0x00b3d350
struct Matrix3 { float m[9]; };
void __cdecl MatrixFromTwoVectors(Matrix3* out, const Vector3_s00d5_57f0* a, const Vector3_s00d5_57f0* b);  // 0x0069b1c0
struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t range);   // 0x00a68fb0
};
void FUN_00d55060(int count, Vec3Vector& out, Vector3_s00d5_57f0 p, Vector3_s00d5_57f0 d1, Vector3_s00d5_57f0 d2, float r);
void FUN_00d552c0(int count, Vec3Vector& out, Vector3_s00d5_57f0 p, Vector3_s00d5_57f0 d1, Vector3_s00d5_57f0 d2, float r);
void FUN_00d554f0(int count, Vec3Vector& out, Vector3_s00d5_57f0 p, Vector3_s00d5_57f0 d1, Vector3_s00d5_57f0 d2, float r);
struct cBehaviorSpaceTurret_s00d5_57f0 : cInteraction_s00d5_57f0 {
    StateMap mMap;                   // +0x74
    char mPad8c[0xb8 - (0x74 + sizeof(StateMap))];
    int32_t mF0b8;                   // +0xb8
    char mPadBc[0x74c - 0xb8 - 4];
    char mF74c;                      // +0x74c

    bool AddAgent(cInteractionAgent* pAgent);  // 0x00d565c0 (cBehaviorSpaceTurret::AddAgent)
};
// ---- items of slice s00d557f0 end

// ---- items of slice s00d56630 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s00d5_6630 { float x, y, z; };
struct IObj;
struct IAgent {
    virtual void     a00();
    virtual void     a04();
    virtual IObj*    a08();              // 0x08 (no stack argument)
    virtual IObj*    a0c();              // 0x0c
    virtual int      a10();              // 0x10
virtual void     a14();
virtual void a18();
virtual void a1c();
virtual void     a20();
virtual void a24();
virtual void a28();
virtual void a2c();
virtual void     a30();
virtual void a34();
virtual void a38();
virtual void a3c();
virtual void     a40();
virtual void a44();
virtual void a48();
virtual void a4c();
virtual void     a50();
virtual void a54();
virtual void a58();
    virtual void*    a5c(uint32_t id);   // 0x5c GetBehavior(id)
virtual void     a60();
virtual void a64();
virtual void a68();
virtual void a6c();
virtual void     a70();
virtual void a74();
virtual void a78();
virtual void a7c();
virtual void     a80();
virtual void a84();
virtual void a88();
virtual void a8c();
virtual void     a90();
virtual void a94();
virtual void a98();
virtual void a9c();
virtual void     aa0();
virtual void aa4();
virtual void aa8();
virtual void aac();
virtual void     ab0();
virtual void ab4();
    virtual void*    ab8(uint32_t id);   // 0xb8
};
struct ISpatial {
virtual void           v00();
virtual void v04();
virtual void v08();
virtual void           v0c();
virtual void v10();
virtual void v14();
virtual void           v18();
virtual void v1c();
virtual void v20();
virtual void           v24();
virtual void v28();
    virtual const Vector3_s00d5_6630& GetPosition();  // 0x2c
};
struct IObj {
    virtual void   v00();
    virtual IObj*  Cast4(uint32_t id);     // 0x04
    virtual IObj*  Cast8(uint32_t id);     // 0x08
    virtual IObj*  v0c();                  // 0x0c
    virtual int    v10();                  // 0x10
virtual void   v14();
virtual void v18();
virtual void v1c();
virtual void   v20();
virtual void v24();
virtual void v28();
    virtual const Vector3_s00d5_6630& GetPosition();  // 0x2c
};
struct IValid { virtual bool IsValid(); };     // 0x2c bool result
struct cCombatant_s00d5_6630 {
    int  GetDamageState();                 // 0x008e7f80
    bool IsDestroyed();                    // 0x00bfc600
    bool HasEntry(uint32_t id);            // 0x00bfcc40
};
struct cCombatantView {                    // cCombatant subobject at turret+0x588
virtual void   v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual int    GetTargetID();          // 0x10
virtual void   v14();
virtual void v18();
virtual void v1c();
virtual void   v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void   v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void   v40();
virtual void v44();
virtual void v48();
virtual void v4c();
    virtual void   SetTarget(void* target); // 0x50
    int  GetDamageState();                 // 0x008e7f80
    bool IsDestroyed();                    // 0x00bfc600
};
struct cTool {
    int GetRefireMs();                     // 0x0104bde0
};
struct cPointerList {                      // turret+0x2ac
    void** mpBegin;
    void** mpEnd;
};
struct cTurret {
    uint32_t pad00[0x34 / 4];
    ISpatial mSpatial;                     // 0x34
    uint32_t pad38[(0x2ac - 0x38) / 4];
    cPointerList mCandidateList;           // 0x2ac (0x00c420d0 returns &this)
    uint32_t pad2b4[(0x588 - 0x2b4) / 4];
    cCombatantView mCombatant;             // 0x588
    uint32_t pad58c[(0x688 - 0x58c) / 4];
    IObj*        mpField688;               // 0x688 (0x00bce5c0)
    uint32_t pad68c[(0x698 - 0x68c) / 4];
    cTool*       mpPrimaryTool;            // 0x698 (0x00bce3d0)

    cTurret* GetSomething() { return this; }
    cTool* GetPrimaryTool();
    IObj*  FUN_00bce5c0();
    cPointerList* GetCandidateList();      // 0x00c420d0 -> &mCandidateList
};
struct cCity {                             // cast target 0xee9b2232
    uint32_t pad00[0x324 / 4];
    ISpatial mSpatial;                     // 0x324
    Vector3_s00d5_6630* GetLocation(Vector3_s00d5_6630* out);    // 0x00bd9480
};
struct cPlanetModel_s00d5_6630 {
    Vector3_s00d5_6630* DirectionToSurfacePosition(uint32_t dirId, const Vector3_s00d5_6630* dir);  // 0x00b815a0
};
struct SlotVector_s00d5_6630;
struct SlotEntry_s00d5_6630 { uint32_t mNext; void* mpData; };
struct SlotIter_s00d5_6630 {
    SlotVector_s00d5_6630* mpOwner;
    uint32_t    mIndex;
    void increment();                      // 0x00abe9b0
};
static const uint32_t kSlotEmpty = 0x3fffffff;
int __cdecl SlotDistance(SlotIter_s00d5_6630 first, SlotIter_s00d5_6630 last);   // 0x00abea00
struct SlotBlock { SlotEntry_s00d5_6630 mEntries[128]; };
struct SlotVector_s00d5_6630 {
    SlotBlock** mpBegin;                   // +0x00
    SlotBlock** mpEnd;                     // +0x04
    void*       mpField08;                 // +0x08
    void*       mpField0c;                 // +0x0c
    void*       mpField10;                 // +0x10
    uint32_t    mEndSlot;                  // +0x14
    uint32_t    mBeginIndex;               // +0x18
    uint32_t    mFreeHead;                 // +0x1c

    SlotEntry_s00d5_6630* entry(uint32_t i) { return &mpBegin[i >> 7]->mEntries[i & 0x7f]; }
    uint32_t endIndex() { return (uint32_t)((mpEnd - mpBegin) * 128) + mEndSlot - 0x7f; }
    SlotIter_s00d5_6630 begin() { SlotIter_s00d5_6630 it; it.mpOwner = this; it.mIndex = mBeginIndex; return it; }
    SlotIter_s00d5_6630 end()   { SlotIter_s00d5_6630 it; it.mpOwner = this; it.mIndex = endIndex();  return it; }
    uint32_t key(SlotIter_s00d5_6630& it) { return (uint32_t)it.mpOwner + it.mIndex; }
    uint32_t size() {
        uint32_t end = endIndex();
        uint32_t first = mBeginIndex;
        if (first >= kSlotEmpty) first = end;
        typedef int(__cdecl* Distance5)(SlotVector_s00d5_6630*, uint32_t, SlotVector_s00d5_6630*, uint32_t, SlotVector_s00d5_6630*);
        return ((Distance5)SlotDistance)(this, first, this, end, this);
    }
};
struct cSpaceTurretStateInfo_s00d5_6630 {              // mStateMap value
    uint32_t pad00[2];
    uint64_t mNextFireTime;                 // +0x08
    uint64_t mNextBeamToggle;               // +0x10
    uint64_t mBeamEndTime;                  // +0x18
    int      mBeamOn;                       // +0x20
};
cPlanetModel_s00d5_6630* PlanetModel_s00d5_6630();                          // 0x00b3d350
Vector3_s00d5_6630* normalized_safe(Vector3_s00d5_6630* out, const Vector3_s00d5_6630* in);  // 0x00449c20
float Dot3(const Vector3_s00d5_6630& a, const Vector3_s00d5_6630& b);       // 0x00455cc0
void* FUN_00ae33b0(void* obj);                        // 0x00ae33b0 (OnAbduction)
bool  FUN_00c0c0e0(void* obj);                        // 0x00c0c0e0 (Flag388)
struct cTimer {
    uint32_t mData[8];
    void   Restart();                     // 0x00bc3130
    uint64_t GetElapsedTime();            // 0x00bc3190
};
struct cBehaviorSpaceTurret_s00d5_6630 {
    uint32_t pad00[3];
    SlotVector_s00d5_6630 mTargetList;               // 0x0c
    SlotVector_s00d5_6630 mAgentList;                // 0x2c
    uint32_t pad48[(0x74 - 0x48) / 4];
    cSpaceTurretStateInfo_s00d5_6630* GetState(IObj* agent);   // 0x00d56510 (mStateMap)
    uint32_t pad74[(0x90 - 0x78) / 4];
    cTimer   mLifeTimer;                  // 0x90
    uint64_t mNextFiringTime;             // 0xb0
    uint32_t padb8;
    Vector3_s00d5_6630  mCityCenter;                 // 0xbc
    int      mAaShotsPerTurret;           // 0xc8
    uint32_t padcc;
    uint64_t mSdrBeamLifetime;            // 0xd0
    bool     mbWasHostile;                // 0xd8
    uint32_t paddc;
    cTimer   mScanTimer;                  // 0xe0

    void UpdateWeaponData();              // 0x00d547e0
    void Init(int arg);                   // 0x00d56630
    void StopDefense();                   // 0x00d56870
};
// ---- items of slice s00d56630 end

// ---- items of slice s00d79470 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(inv * x, y * inv, z * inv);
    }
    float LengthSquared() const { return x * x + y * y + z * z; }
    cSPVector3& operator+=(const cSPVector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    bool operator==(const cSPVector3& v) const { return x == v.x && y == v.y && z == v.z; }
};
}
namespace SP {
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace SP {
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
}
namespace SP {
void InitEditorParamsInner(uint32_t* params);        // 0x00abedb0
}
// ---- items of slice s00d79470 end

// @ 0x00d54730
bool __stdcall SP::CanJoin(void* pObject, int nUnused)
{
    if (pObject && ((SP::SPObject*)pObject)->QueryInterface(0x436f315))
        return true;
    return false;
}

// @ 0x00d54760
void SP::StopAirRaidEffect()
{
    SP::sAirRaidTimer.Stop();
    if (SP::spAirRaidEffect.mpObject)
        SP::spAirRaidEffect.mpObject->Stop(0);
}

// @ 0x00d54780
SP::WeaponData::WeaponData(const SP::WeaponData& src)
{
    mpObject = src.mpObject;
    mpTemplate = src.mpTemplate;
    mpRef = src.mpRef;
    if (mpRef)
        mpRef->AddRef();
    mValues[0] = src.mValues[0];
    mValues[1] = src.mValues[1];
    mValues[2] = src.mValues[2];
    mValues[3] = src.mValues[3];
    mValues[4] = src.mValues[4];
    mValues[5] = src.mValues[5];
    mValues[6] = src.mValues[6];
}

// @ 0x00d547e0
void SP::cBehaviorSpaceTurret_s00d5_3b50::UpdateWeaponData()
{
    SP::AutoRef<SP::PropertySet> pSet;
    SP::PropertyManager* pMgr = SP::GetPropertyManager();
    pSet.reset();
    if (pMgr->FindPropertySet(0xa4c2f6bd, &pSet.mpObject)) {
        SP::Property* pProp;
        float f;
        if (pSet.mpObject && pSet.mpObject->GetProperty(0x244ea3d, &pProp) && pProp->mType == 9)
            mSdrBeamLifetime = *pProp->GetInt();
        if (pSet.mpObject && pSet.mpObject->GetProperty(0x24a0740, &pProp) && pProp->mType == 0xd)
            f = *pProp->GetFloat();
        float ms = f * 1000.0f;
        mWeaponTimerMS = (int64)ms;
    }
}

// @ 0x00d548e0
SP::WeaponData::WeaponData(void* const* ppObject, const SP::WeaponSource& src)
: mpObject(*ppObject)
{
    mpTemplate = src.mpObject;
    mpRef = src.mpRef;
    if (mpRef)
        mpRef->AddRef();
    mValues[0] = src.mValues[0];
    mValues[1] = src.mValues[1];
    mValues[2] = src.mValues[2];
    mValues[3] = src.mValues[3];
    mValues[4] = src.mValues[4];
    mValues[5] = src.mValues[5];
    mValues[6] = src.mValues[6];
}

// @ 0x00d54940
bool __cdecl SP::UpdateAirRaidSiren(SP::cBehaviorSpaceTurret_s00d5_3b50* pTurret)
{
    if (!SP::sAirRaidTimer.IsRunning()) {
        SP::sAirRaidTimer.Restart();
        if (!SP::spAirRaidEffect.mpObject) {
            SP::IEffectsManager* pMgr = SP::EffectsManagerPtr();
            SP::spAirRaidEffect.reset();
            pMgr->CreateEffect(0x9254cd2, 0, &SP::spAirRaidEffect.mpObject);
            if (!SP::spAirRaidEffect.mpObject)
                return false;
        }

        SP::spAirRaidEffect.mpObject->Start(0);

        SP::EffectParams params;
        params.mPosition.x = SP::sAirRaidSirenOffset.x;
        params.mPosition.y = SP::sAirRaidSirenOffset.y;
        params.mPosition.z = SP::sAirRaidSirenOffset.z;
        params.mFlags = 0;
        params.mCount = 0;
        params.mScale = 1.0f;
        params.mMatrix.Assign(SP::sAirRaidSirenMatrix);
        const Vector3* pPos = pTurret->mTransform.GetTranslation();
        params.mPosition = *pPos;
        params.mFlags |= 4;
        params.mCount += 1;
        SP::spAirRaidEffect.mpObject->SetParams(&params);
        return false;
    }

    unsigned long long nSirenTime = SP::GetSpaceCombatTuning()->GetAirRaidSirenTimeMS();
    if (SP::sAirRaidTimer.GetElapsedTime() < nSirenTime)
        return false;
    SP::sAirRaidTimer.Stop();
    if (SP::spAirRaidEffect.mpObject)
        SP::spAirRaidEffect.mpObject->Stop(0);
    return true;
}

// @ 0x00d54c10
void __cdecl SP::ClearAllTargets(SP::SlotVector* pVec)
{
    unsigned index = (unsigned)pVec->mCount;
    if ((unsigned)index >= 0x3fffffffu)
        index = SlotEnd(pVec);
    SP::SlotIter it;
    it.mpVector = pVec;
    it.mIndex = index;
    while ((char*)pVec + SlotEnd(pVec) != (char*)it.mpVector + it.mIndex) {
        void* pItem = pVec->mpBuckets[it.mIndex >> 7]->mEntries[it.mIndex & 0x7f].mpItem;
        SP::cTurret_s00d5_3b50* pTurret = pItem
            ? (SP::cTurret_s00d5_3b50*)((SP::SPObject*)pItem)->QueryInterface(0x436f315) : 0;
        pTurret->mEffect.Stop(0);
        pTurret->FaceAtTarget(0);
        it.increment();
    }
}

// @ 0x00d54ce0
int cBehaviorSpaceTurret::GetActiveTurretCount()
{
    int nCount = 0;
    for (cSlotIterator it = mAgentList.Begin(); it != mAgentList.End();
         it.Increment()) {
        cSlotEntry* pEntry =
            &((cAgentSlotVector*)it.mpBase)->mpBlocks[it.mnIndex >> 7]
                 ->mEntries[it.mnIndex & 0x7f];
        cInteractionAgent* pAgent = (cInteractionAgent*)pEntry->mpObject;
        cCombatant* pCombatant;
        if (pAgent != 0)
            pCombatant = ((cCombatant* (__thiscall*)(cInteractionAgent*, void*))
                              ((void**)pAgent->mpVtable)[0x08 / 4])(
                pAgent, &gInteractionAgentTypeInfo);
        else
            pCombatant = 0;
        if (pCombatant->GetDamageState() != 2)
            ++nCount;
    }
    return nCount;
}

// @ 0x00d54d90
int cBehaviorSpaceTurret::CountAttackableTurrets()
{
    int nCount = 0;
    for (cSlotIterator it = mAgentList.Begin(); it != mAgentList.End();
         it.Increment()) {
        cSlotEntry* pEntry =
            &((cAgentSlotVector*)it.mpBase)->mpBlocks[it.mnIndex >> 7]
                 ->mEntries[it.mnIndex & 0x7f];
        cInteractionAgent* pAgent = (cInteractionAgent*)pEntry->mpObject;
        cCombatant* pCombatant;
        if (pAgent != 0)
            pCombatant = ((cCombatant* (__thiscall*)(cInteractionAgent*, void*))
                              ((void**)pAgent->mpVtable)[0x08 / 4])(
                pAgent, &gInteractionAgentTypeInfo);
        else
            pCombatant = 0;
        if (pCombatant->GetDamageState() != 2) {
            if (pCombatant->IsHostileAlive())
                ++nCount;
        }
    }
    return nCount;
}

// @ 0x00d54e50
cBehaviorSpaceTurret::~cBehaviorSpaceTurret()
{
    mpVtable = (void*)0x147b900;
    mpRefCountVtable = (void*)0x147b8ec;
    if (mbAirRaidDone == 0) {
        gsAirRaidTimer.Stop();
        void* pEffect = gsAirRaidEffect;
        if (pEffect != 0) {
            void** ppVtable = *(void***)pEffect;
            ((void (__thiscall*)(void*, int))ppVtable[0x0c / 4])(pEffect, 0);
        }
    }
    mAirRaidTimer.Destruct();
    mLifeTimer.Destruct();
    cRBNodeBase* pRoot = mStateTree.mAnchor.mpNodeParent;
    cTurretStateTree* pTree = &mStateTree;
    pTree->NukeSubtree(pRoot);
}

// @ 0x00d54fa0
cBehaviorSpaceTurret::cBehaviorSpaceTurret()
{
    mpVtable = (void*)0x147b900;
    mpRefCountVtable = (void*)0x147b8ec;
    // eastl rbtree reset: anchor first cleared, then re-linked to itself.
    mStateTree.mAnchor.mpNodeLeft = 0;
    mStateTree.mAnchor.mpNodeParent = 0;
    mStateTree.mAnchor.mnColor = 0;
    mStateTree.mAnchor.mpNodeRight = &mStateTree.mAnchor;
    mStateTree.mAnchor.mpNodeLeft = &mStateTree.mAnchor;
    mStateTree.mAnchor.mpNodeParent = 0;
    mStateTree.mAnchor.mnColor = 0;
    mStateTree.mnSize = 0;
    mLifeTimer.Construct();
    mnUnkB8 = 0;
    mAirRaidTimer.Construct();
    mbAirRaidDone = 0;
    mnSdrBeamLifetime = 8;
}

// @ 0x00d55060
void SpaceTurret_SampleHelix(int nSamples, cVector3Array* pVertices, float fArg3, float fArg4, float fArg5, float fArg6, float fArg7, float fArg8, float fArg9, float fArg10, float fArg11, float fArg12)
{
    pVertices->Clear();
    Vector3Array_Reserve(nSamples);
    float fStep = gsSpaceHelixStep / (float)nSamples;
    for (int i = 0; i < nSamples; ++i) {
        float fHalf = (float)i * 0.5f;
        float fSin = (float)sin(fHalf);
        float fCos = (float)cos(fHalf);
        float v[3];
        v[0] = fArg6 * fSin + fArg3;
        v[1] = fArg7 * fSin + fArg4;
        v[2] = fArg8 * fCos + fArg5;
        Vector3_Push(pVertices, v);
        fHalf = fStep;
    }
}

// @ 0x00d552c0
void SpaceTurret_SampleGrid(int nSamples, cVector3Array* pVertices, float fArg3, float fArg4, float fArg5, float fArg6, float fArg7, float fArg8, float fArg9, float fArg10, float fArg11, float fArg12)
{
    int nCount = GetDetailLevelCount();
    if (nCount < 1)
        nCount = 1;
    pVertices->Clear();
    Vector3Array_Reserve((uint32_t)(nCount * nCount) / 2);
    float fStep = (fArg12 / (float)nCount) * 2.0f;
    for (int i = 0; i < nCount; ++i) {
        for (int j = 0; j < nCount; ++j) {
            if (((i & 1) == 0) && ((j & 1) == 0))
                continue;
            float v[3];
            v[0] = fArg3 + (float)j * fStep - fArg12;
            v[1] = fArg4;
            v[2] = fArg5 + (float)i * fStep - fArg12;
            Vector3_Push(pVertices, v);
        }
    }
}

// @ 0x00d554f0
void SpaceTurret_SampleCorners(uint32_t nCount, cVector3Array* pVertices, float fArg3, float fArg4, float fArg5, float fArg6, float fArg7, float fArg8, float fArg9, float fArg10, float fArg11, float fArg12)
{
    pVertices->Clear();
    float v[3];
    v[0] = fArg3;
    v[1] = fArg4;
    v[2] = fArg5;
    Vector3_Push(pVertices, v);
    if ((int)nCount < 4)
        return;
    v[0] = fArg3 + fArg9;
    v[1] = fArg4 + fArg10;
    v[2] = fArg5 + fArg11;
    Vector3_Push(pVertices, v);
    v[0] = fArg3 + fArg12;
    v[1] = fArg4 + fArg12;
    v[2] = fArg5 + fArg12;
    Vector3_Push(pVertices, v);
    v[0] = fArg6;
    v[1] = fArg7;
    v[2] = fArg8;
    Vector3_Push(pVertices, v);
}

// @ 0x00d557f0
void SetStarPattern(int count, Vec3Vector& out, Vector3_s00d5_57f0 p, Vector3_s00d5_57f0 d, float radius)
{
    out.clear();
    static float sStep = g_169ebf0 * 0.2f;

    int n = count;
    if (n >= 5) {
        AddStarRing(out, p, d, radius * 0.5f, 0.0f, sStep);
        n -= 5;
        if (n >= 5) {
            AddStarRing(out, p, d, radius, sStep * 0.5f, sStep);
            n -= 5;
        }
    }

    int m = n / 10;
    if (m != 0) {
        const Vector3_s00d5_57f0* v = out.mpBegin;
        float dx = v[0].x - v[5].x;
        float dy = v[0].y - v[5].y;
        float dz = v[0].z - v[5].z;
        float stepT = (float)sqrt(dx * dx + (dy * dy + dz * dz)) / (float)(m + 1);
        for (int j = 0; j < 5; ++j) {
            const Vector3_s00d5_57f0* base = out.mpBegin;
            Vector3_s00d5_57f0 a = base[j];
            Vector3_s00d5_57f0 b = base[j + 5];
            Vector3_s00d5_57f0 c = base[(j < 4) ? j + 1 : 0];
            if (m > 0) {
                Vector3_s00d5_57f0 d1(b.x - a.x, b.y - a.y, b.z - a.z);
                Vector3_s00d5_57f0 d2(b.x - c.x, b.y - c.y, b.z - c.z);
                float inv1 = 1.0f / (float)sqrt(d1.y * d1.y + (d1.z * d1.z + d1.x * d1.x));
                Vector3_s00d5_57f0 u1(inv1 * d1.x, d1.y * inv1, d1.z * inv1);
                float inv2 = 1.0f / (float)sqrt(d2.y * d2.y + (d2.z * d2.z + d2.x * d2.x));
                Vector3_s00d5_57f0 u2(inv2 * d2.x, d2.y * inv2, d2.z * inv2);
                float t = stepT;
                for (int k = m; k != 0; --k) {
                    Vector3_s00d5_57f0 q1(u1.x * t + a.x, u1.y * t + a.y, u1.z * t + a.z);
                    out.push_back(q1);
                    Vector3_s00d5_57f0 q2(u2.x * t + c.x, u2.y * t + c.y, u2.z * t + c.z);
                    out.push_back(q2);
                    t = t + stepT;
                }
            }
        }
    }
}

// @ 0x00d56070
void UpdateFirePattern(Vec3Vector& out, int count, cBehaviorSpaceTurret_s00d5_57f0* turret)
{
    out.clear();

    Vector3_s00d5_57f0 dir;
    if (turret->mF74c == 0) {
        cLocomotiveObject* loco = (cLocomotiveObject*)((char*)turret + 0x34);
        Vector3_s00d5_57f0* vel = loco->GetVelocity();
        float sq = vel->x * vel->x + vel->y * vel->y + vel->z * vel->z;
        if ((float)sqrt(sq) > 0.0f) {
            Vector3_s00d5_57f0 pos;
            Vector3_s00d5_57f0* dirRaw = GetObjectDirection(loco);
            Vector3_s00d5_57f0* surf = PlanetModel()->DirectionToSurfacePosition(&pos, dirRaw);
            Vector3_s00d5_57f0 v = *surf;
            Vector3_s00d5_57f0 rnd = *PlanetModel()->MakeRandomWorldPosition(&pos, &v, 0.0f, 20.0f);
            Vector3_s00d5_57f0* pdir = GetObjectDirection(loco);
            float sqSpeed = pdir->x * pdir->x + pdir->y * pdir->y + pdir->z * pdir->z;
            float speed = (float)sqrt(sqSpeed);
            float inv = 1.0f / (float)sqrt(rnd.x * rnd.x + rnd.z * rnd.z + rnd.y * rnd.y);
            dir.x = (inv * rnd.x) * speed;
            dir.y = (rnd.y * inv) * speed;
            dir.z = (rnd.z * inv) * speed;
        } else {
            dir = *GetObjectDirection(loco);
        }
    } else {
        dir = *GetObjectDirection((cLocomotiveObject*)((char*)turret + 0x34));
    }

    float inv = 1.0f / (float)sqrt(dir.x * dir.x + dir.z * dir.z + dir.y * dir.y);
    Vector3_s00d5_57f0 d;
    d.x = inv * dir.x;
    d.y = dir.y * inv;
    d.z = dir.z * inv;

    Matrix3 m;
    MatrixFromTwoVectors(&m, &g_169ebe4, &d);
    Vector3_s00d5_57f0 row0(m.m[0], m.m[1], m.m[2]);
    Vector3_s00d5_57f0 row1(m.m[3], m.m[4], m.m[5]);
    Vector3_s00d5_57f0 row2(m.m[6], m.m[7], m.m[8]);

    if (count == 0)
        return;

    RandomLinearCongruential* rng = (RandomLinearCongruential*)0x1601760;
    int half = count / 2;
    int n = rng->RandomUint32Uniform(half) + half;
    int kind = rng->RandomUint32Uniform(4);
    switch (kind) {
    case 0: FUN_00d552c0(n, out, dir, row1, row0, 40.0f); break;
    case 1: FUN_00d554f0(n, out, dir, row1, row0, 40.0f); break;
    case 2: SetStarPattern(n, out, dir, row1, 40.0f); break;
    default: FUN_00d55060(n, out, dir, row2, row1, 40.0f); break;
    }
}

// @ 0x00d56510
cSpaceTurretStateInfo& StateMap::GetOrInsert(const int& key)
{
    RBNodeBase* anchor = &mAnchor;
    RBNodeBase* pos = anchor;
    RBNodeBase* cur = mAnchor.mpNodeParent;
    while (cur) {
        if ((uint32_t)((StateNode*)cur)->mKey < (uint32_t)key) {
            cur = cur->mpNodeRight;
        } else {
            pos = cur;
            cur = cur->mpNodeLeft;
        }
    }

    if (pos == anchor || (uint32_t)key < (uint32_t)((StateNode*)pos)->mKey) {
        cSpaceTurretStateInfo src;
        src.mpTarget = 0;
        src.mNextMissileTime = 0;
        src.mNextBeamTime = 0;
        src.mBeamCutoffTime = 0;
        src.mBehaviorIndex = 0;

        StatePair pair;
        pair.Construct(&key, &src);
        StateNode* result = 0;
        Insert(&result, (StateNode*)pos, &pair, InsertTag());
        if (pair.mValue.mpTarget)
            pair.mValue.mpTarget->Release();
        pos = result;
    }
    return ((StateNode*)pos)->mValue;
}

// @ 0x00d565c0
bool cBehaviorSpaceTurret_s00d5_57f0::AddAgent(cInteractionAgent* pAgent)
{
    if (pAgent != 0) {
        mF0b8 = (mF0b8 == 0);
        cSpaceTurretStateInfo* info = &mMap.GetOrInsert(*(const int*)&pAgent);
        info->mState = 0;
        Target* t = info->mpTarget;
        if (t) {
            info->mpTarget = 0;
            t->Release();
        }
        info->mNextMissileTime = 0;
        info->mBehaviorIndex = mF0b8;
    }
    return cInteraction_s00d5_57f0::AddAgent(pAgent);
}

// @ 0x00d56630
void cBehaviorSpaceTurret_s00d5_6630::Init(int arg)
{
    mLifeTimer.Restart();
    mScanTimer.Restart();
    mNextFiringTime = mLifeTimer.GetElapsedTime();

    if (mTargetList.mBeginIndex != kSlotEmpty) {
        IObj* pFront = (IObj*)mTargetList.entry(mTargetList.mBeginIndex)->mpData;
        cCity* pCity = pFront ? (cCity*)pFront->Cast4(0xee9b2232) : 0;
        Vector3_s00d5_6630 v;
        Vector3_s00d5_6630* pPosition;
        if (pCity)
            pPosition = pCity->GetLocation(&v);
        else
            pPosition = PlanetModel_s00d5_6630()->DirectionToSurfacePosition(0x0169ebe4, &v);
        mCityCenter = *pPosition;
    }

    UpdateWeaponData();

    if (mAgentList.mBeginIndex != kSlotEmpty) {
        uint32_t first = mAgentList.mBeginIndex;
        if (first >= kSlotEmpty)
            first = mAgentList.endIndex();

        IObj* pAgent = (IObj*)mAgentList.entry(first)->mpData;
        cTurret* pTurret = pAgent ? (cTurret*)pAgent->Cast8(0x436f315) : 0;
        cTool* pTool = pTurret->GetPrimaryTool();

        uint32_t step = (uint32_t)pTool->GetRefireMs() / mAgentList.size();

        uint64_t seg = 0;
        SlotIter_s00d5_6630 it = mAgentList.begin();
        uint32_t lastKey = mAgentList.key(mAgentList.end());
        while (mAgentList.key(it) != lastKey) {
            IObj* agent = (IObj*)it.mpOwner->entry(it.mIndex)->mpData;
            GetState(agent)->mNextFireTime = seg;
            GetState(agent)->mNextBeamToggle = 0;
            GetState(agent)->mBeamEndTime = 0;
            seg += step;
            it.increment();
        }
    }
    (void)arg;
}

// @ 0x00d56870
void cBehaviorSpaceTurret_s00d5_6630::StopDefense()
{
    uint64_t elapsed = mScanTimer.GetElapsedTime();
    if (elapsed <= 1000)
        return;

    mScanTimer.Restart();

    SlotIter_s00d5_6630 it = mAgentList.begin();
    uint32_t lastKey = mAgentList.key(mAgentList.end());
    while (mAgentList.key(it) != lastKey) {
        IObj* pAgent = (IObj*)it.mpOwner->entry(it.mIndex)->mpData;
        cTurret* pTurret = pAgent ? (cTurret*)pAgent->Cast8(0x436f315) : 0;
        GetState(pAgent);
        cCombatantView* pCombatant = (cCombatantView*)((uint8_t*)pTurret + 0x588);
        int myTargetID = pCombatant->GetTargetID();

        if (pCombatant->GetDamageState() == 2 || pCombatant->IsDestroyed()) {
            pCombatant->SetTarget(0);
        } else {
            uint32_t bestPriority = 0;
            IObj* pBest = 0;

            cPointerList* pList = pTurret->GetCandidateList();
            for (void** pp = pList->mpBegin; pp != pList->mpEnd; ++pp) {
                IAgent* pCand = (IAgent*)*pp;
                if (pCand == 0)
                    continue;
                IObj* pOther = (IObj*)pCand->ab8(0x013f94d4);
                if (pOther == 0)
                    continue;
                if (((cCombatant_s00d5_6630*)pOther)->GetDamageState() == 2)
                    continue;
                if (((IValid*)pOther->v0c())->IsValid())
                    continue;
                if (pOther->v10() == myTargetID)
                    continue;

                uint32_t priority = 0;
                void* pBehavior = pCand->a5c(0x137e8e0);
                if (pBehavior != 0) {
                    cCombatant_s00d5_6630* pHost = (cCombatant_s00d5_6630*)((uint8_t*)pBehavior + 0x508);
                    if (pHost->GetDamageState() == 2)
                        continue;
                    if (pHost->HasEntry((uint32_t)myTargetID))
                        priority = 4;
                } else {
                    void* pPart = pCand->a5c(0x4f176642);
                    if (pPart != 0) {
                        if (((cCombatant_s00d5_6630*)((uint8_t*)pPart + 0x5a8))->HasEntry((uint32_t)myTargetID))
                            priority = 1;
                    } else {
                        void* pBio = FUN_00ae33b0(pCand);
                        if (pBio != 0 && FUN_00c0c0e0(pBio))
                            priority = 2;
                    }
                }

                if (priority > bestPriority) {
                    IObj* pSelf = pTurret->FUN_00bce5c0();
                    const Vector3_s00d5_6630& a = ((ISpatial*)((uint8_t*)pSelf + 0x120))->GetPosition();
                    const Vector3_s00d5_6630& b = pTurret->mSpatial.GetPosition();
                    Vector3_s00d5_6630 d1;
                    d1.x = b.x - a.x;
                    d1.y = b.y - a.y;
                    d1.z = b.z - a.z;
                    Vector3_s00d5_6630 n1;
                    normalized_safe(&n1, &d1);

                    IObj* pSelf2 = pTurret->FUN_00bce5c0();
                    const Vector3_s00d5_6630& a2 = ((ISpatial*)((uint8_t*)pSelf2 + 0x120))->GetPosition();
                    const Vector3_s00d5_6630& b2 = pCand->a08()->GetPosition();
                    Vector3_s00d5_6630 d2;
                    d2.x = b2.x - a2.x;
                    d2.y = b2.y - a2.y;
                    d2.z = b2.z - a2.z;
                    Vector3_s00d5_6630 n2;
                    normalized_safe(&n2, &d2);

                    if (Dot3(n1, n2) > 0.5f) {
                        bestPriority = priority;
                        pBest = pOther;
                    }
                }
            }
            pCombatant->SetTarget(pBest);
        }
        it.increment();
    }
}

// @ 0x00d7a020
namespace SP {
void InitEditorParams(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f)
{
    uint32_t params[6];
    params[0] = a;
    params[1] = b;
    params[2] = c;
    params[3] = d;
    params[4] = e;
    params[5] = f;
    InitEditorParamsInner(params);
}
}  // namespace SP
