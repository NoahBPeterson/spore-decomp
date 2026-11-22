// src/game/SPGonzago/SPCityCivAttackBehaviors.cpp -- migrated from slice(s) s00d56c30, s00d79470, s00d56630, s00d557f0, s00d53b50, s00d54ce0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityCivAttackBehaviors.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include <intrin.h>
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
#include "SP/cGameNounManager.h"
#include "SP/cPlanet.h"

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
    virtual void AddRef();           // vtable +0x18
};
struct cSpaceTurretStateInfo {
    int32_t  mState;                 // +0x00
    Target*  mpTarget;               // +0x04
    uint64_t mNextMissileTime;       // +0x08
    uint64_t mNextBeamTime;          // +0x10
    uint64_t mBeamCutoffTime;        // +0x18
    int32_t  mBehaviorIndex;         // +0x20

    cSpaceTurretStateInfo() {}
    cSpaceTurretStateInfo(const cSpaceTurretStateInfo& src)
        : mState(src.mState), mpTarget(src.mpTarget)
    {
        if (mpTarget)
            mpTarget->AddRef();
        mNextMissileTime = src.mNextMissileTime;
        mNextBeamTime = src.mNextBeamTime;
        mBeamCutoffTime = src.mBeamCutoffTime;
        mBehaviorIndex = src.mBehaviorIndex;
    }
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
    StatePair(const int& key, const cSpaceTurretStateInfo& src);             // 0x00d548e0
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

// ---- items of slice s00d56c30_action begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
typedef unsigned char u8;
typedef long long i64;
struct Vec3f {
    float x, y, z;

    Vec3f operator-(const Vec3f& other) const
    {
        Vec3f r;
        r.x = x - other.x;
        r.y = y - other.y;
        r.z = z - other.z;
        return r;
    }
};
struct Matrix3Rows {
    float mRows[9];
};
struct cSlotEntry_s00d5_6c30__action;
struct cSlotBlock_s00d5_6c30__action;
struct cSlotEntry_s00d5_6c30__action {
    void* mpObject;                                    // +0x00 AutoRefCount payload
    u32   mnFlags;                                     // +0x04
};
struct cSlotBlock_s00d5_6c30__action {
    u32        mnHeader;                               // +0x00
    cSlotEntry_s00d5_6c30__action mEntries[128];                          // +0x04
};
struct cSlotIterator_s00d5_6c30__action {
    u8* mpBase;                                        // +0x00 address of the owning vector
    u32 mnIndex;                                       // +0x04

    void Increment();                                  // 0x00abe9b0

    bool operator!=(const cSlotIterator_s00d5_6c30__action& other) const
    {
        return mpBase + mnIndex != other.mpBase + other.mnIndex;
    }

    bool operator==(const cSlotIterator_s00d5_6c30__action& other) const
    {
        return mpBase + mnIndex == other.mpBase + other.mnIndex;
    }
};
struct cSlotVector {
    cSlotBlock_s00d5_6c30__action** mpBlocks;                             // +0x00
    cSlotBlock_s00d5_6c30__action** mpEnd;                                // +0x04
    u32          mn08;                                 // +0x08
    u32          mn0c;                                 // +0x0c
    u32          mn10;                                 // +0x10
    u32          mnFreeChain;                          // +0x14
    u32          mnIndex;                              // +0x18
    u32          mnPad1c;                              // +0x1c

    u32 Size();                                        // 0x00abefd0
    cSlotIterator_s00d5_6c30__action* Begin(cSlotIterator_s00d5_6c30__action* pOut);         // 0x00abeaf0

    u32 EndIndex() const
    {
        return ((int)((char*)mpEnd - (char*)mpBlocks) >> 2) * 0x80 - 0x7f
               + mnFreeChain;
    }

    cSlotIterator_s00d5_6c30__action End() const
    {
        cSlotIterator_s00d5_6c30__action it;
        it.mpBase = (u8*)this;
        it.mnIndex = EndIndex();
        return it;
    }

    cSlotEntry_s00d5_6c30__action& At(const cSlotIterator_s00d5_6c30__action& it)
    {
        return mpBlocks[it.mnIndex >> 7]->mEntries[it.mnIndex & 0x7f];
    }
};
class cSpatialObject_s00d5_6c30__action {
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
    virtual Vec3f* GetPosition();                                 // +0x2c
    char mPad04[0x48];
};
struct XformMsg {
    XformMsg();                                                   // 0x00434040
    void SetPosition(const Vec3f* pPosition);                      // 0x00571d40

    char           mPad00[0x0c];                                  // +0x00
    unsigned short mFlags;                                        // +0x0c
    unsigned short mPad0e;                                        // +0x0e
    unsigned short mSeq;                                          // +0x10
    char           mPad12[0x0e];                                  // +0x12..+0x1f
    Matrix3Rows    mOrientation;                                  // +0x20
    char           mPad44[0x30];                                  // +0x44
};
class cVisualEffect {
public:
    virtual void e00();                                           // +0x00
    virtual void Release();                                       // +0x04
    virtual void e08(int nValue);                                 // +0x08
    virtual void e0c(int nValue);                                 // +0x0c
    virtual bool IsActive();                                      // +0x10
    virtual void e14();                                           // +0x14
    virtual void SetXform(XformMsg* pMsg);                        // +0x18
};
class cEffectRef {
public:
    cVisualEffect** AsPPTypeParam();                              // 0x00a16f40
    cVisualEffect*  mpObject;                                     // +0x00
};
class cEffectManager {
public:
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
    virtual bool CreateEffect(const void* pTypeId, int nFlags,
                              cVisualEffect** ppEffect);           // +0x2c
};
cEffectManager* EffectsManagerPtr_s00d5_6c30__action();                              // 0x0067ddd0
class cSpaceToolData {
public:
    int    GetCooldown();                                          // 0x0104bde0
    float  GetMinRange();                                          // 0x0104be20
    float  GetMaxRange();                                          // 0x0104be30
    float  GetField1e8();                                          // 0x00e21850
};
class cCombatant_s00d5_6c30__action {
public:
virtual void c00();
virtual void c01();
    virtual cSpatialObject_s00d5_6c30__action* GetSpatial();                          // +0x08
virtual void c03();
virtual void c04();
virtual void c05();
virtual void c06();
virtual void c07();
virtual void c08();
virtual void c09();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
    virtual void SetTarget(const Vec3f* pTarget);                  // +0x50

    int  GetDamageState();                                         // 0x008e7f80
    bool IsHostileAlive();                                         // 0x00bfc600

    char mPad04[0xf4];                                             // +0x04
};
class cTurret_s00d5_6c30__action {
public:
    virtual void t00();                                            // +0x00
virtual void t01();
virtual void t02();
virtual void t03();
virtual void t04();
virtual void t05();
virtual void t06();
virtual void t07();
virtual void t08();
virtual void t09();
virtual void t10();
virtual void t11();
virtual void t12();
virtual void t13();
virtual void t14();
virtual void t15();
virtual void t16();
virtual void t17();
virtual void t18();
    virtual void OnTargetSelected();                               // +0x4c

    cSpaceToolData* GetToolData694();                              // 0x00bce3f0
    cSpaceToolData* GetToolData698();                              // 0x00bce3d0
    cSpaceToolData* GetToolData69c();                              // 0x00bce3e0
    void FaceAtTarget(const Vec3f* pTarget);                       // 0x00bce480
    bool AcceptTarget(int nMode);                                  // 0x00c38990

    char           mPad04[0x30];                                   // +0x04..+0x33
    cSpatialObject_s00d5_6c30__action mSpatial;                                       // +0x34
    char           mPad80[0xa0];                                   // +0x80..+0x11f
    cSpatialObject_s00d5_6c30__action mBody;                                          // +0x120
    char           mPad16c[0x39c];                                 // +0x16c..+0x507
    Vec3f          mTargetPos;                                     // +0x508
    char           mPad514[0x74];                                  // +0x514..+0x587
    cCombatant_s00d5_6c30__action     mCombatant;                                     // +0x588
    cEffectRef     mAirRaidEffect;                                 // +0x680
    char           mPad684[0xc4];                                  // +0x684..+0x747
    float          mField748;                                      // +0x748
};
class cInteractionAgent_s00d5_6c30__action {
public:
    virtual void a00();                                            // +0x00
    virtual cTurret_s00d5_6c30__action* GetTargetInterface(const void* pTypeId);      // +0x04
    virtual cTurret_s00d5_6c30__action* GetTurretInterface(const void* pTypeId);      // +0x08
};
class cPlanet_s00d5_6c30__action {
public:
    int GetToolMode();                                             // 0x00c70e00
};
class cCivilization_s00d5_6c30__action;
class cGameNounManager_s00d5_6c30__action {
public:
    cCivilization_s00d5_6c30__action* GetPlayerCivilization();                        // 0x00b25fb0
};
class cSPToolManager {
public:
    void UseToolStart(cSpaceToolData* pTool, cCombatant_s00d5_6c30__action* pActor,
                      const Vec3f* pPosition, int nMode, int nFlags,
                      cSpatialObject_s00d5_6c30__action* pOwner, int nCount);          // 0x01050070
    void UseToolStop(cSpaceToolData* pTool);                        // 0x0104fa90
};
cSPToolManager* ToolManager();                                      // 0x00b3d390
class cSPTimer_s00d5_6c30__action {
public:
    i64 GetElapsedTime();                                           // 0x00bc3190
    char mPad00[0x20];                                              // +0x00..+0x1f
    i64  mNextEventTime;                                            // +0x20
};
struct cTurretState {
    char mPad00[8];                                                 // +0x00
    i64  mLastFireTime;                                             // +0x08
    i64  mNextFireTime;                                             // +0x10
    i64  mNextEffectTime;                                           // +0x18
    int  mnFlag;                                                    // +0x20
};
class cTurretStateTree_s00d5_6c30__action {
public:
    cTurretState* Find(cInteractionAgent_s00d5_6c30__action* const* ppAgent);          // 0x00d56510
    char mPad00[0x24];
};
struct cFireSlot {
    float x, y, z;
};
struct cFirePattern {
    cFireSlot* mpBegin;
    cFireSlot* mpEnd;
    cFireSlot* mpCapacity;
};
namespace SP {
void* GetCurrentGameMode();                                         // 0x00b5b800
}
namespace SP {
class cSPLivingUniverse {
public:
    static cPlanet_s00d5_6c30__action* GetActivePlanet();                              // 0x01021260
};
}
namespace SP {
cGameNounManager_s00d5_6c30__action* NounManager();                                    // 0x00b3d300
}
namespace SP {
void ClearAllTargets(cSlotVector* pAgents);                         // 0x00d54c10
}
namespace SP {
bool IsPlanetAttackableByPlayer(const void* pTarget);               // 0x01029950
}
namespace SP {
bool IsMissionOfTypeActiveAtPlanet(cPlanet_s00d5_6c30__action* pPlanet);               // 0x0102ae60
}
namespace SP {
bool FUN_01041cf0();                                                // 0x01041cf0
}
namespace SP {
bool UpdateAirRaidSiren(cCivilization_s00d5_6c30__action* pCiv, const void* pTarget);   // 0x00d54940
}
namespace SP {
cTurret_s00d5_6c30__action* ResolveTurret(cInteractionAgent_s00d5_6c30__action* pAgent);                   // 0x00d546f0
}
namespace SP {
cTurret_s00d5_6c30__action* ResolveSlotTurret(cSlotEntry_s00d5_6c30__action* pSlot);                       // 0x00d54710
}
namespace SP {
cTurret_s00d5_6c30__action* FindNearestCreature(Vec3f vProbe, bool bModeA, bool bModeB); // 0x00cc26a0
}
namespace SP {
void UpdateFirePattern(cFirePattern* pPattern, int nCount,
                       cTurret_s00d5_6c30__action* pTarget);                           // 0x00d56070
}
namespace SP {
void DestroyFirePattern(cFirePattern* pPattern);                    // 0x00540520
}
namespace SP {
Vec3f* Vec3_Normalize(Vec3f* pOut, const Vec3f* pIn);                // 0x00436ce0
}
namespace SP {
Vec3f* OrthogonalVector(Vec3f* pOut, const Vec3f* pIn);              // 0x006985b0
}
namespace SP {
float Dot3(const Vec3f* pA, const Vec3f* pB);                        // 0x00455cc0
}
namespace SP {
Matrix3Rows* Matrix3FromFacingAndUp(Matrix3Rows* pOut,
                                    const Vec3f* pFacing,
                                    const Vec3f* pUp);               // 0x0069b440
}
namespace SP {
class cInteraction_s00d5_6c30__action {
public:
    void*        mpVtbl;                                            // +0x00
    void*        mpVtbl04;                                          // +0x04
    u32          mn08;                                              // +0x08
    cSlotVector  mTargetList;                                       // +0x0c
    cSlotVector  mAgentList;                                        // +0x2c
};
}
namespace SP {
class cBehaviorSpaceTurret_s00d5_6c30__action : public cInteraction_s00d5_6c30__action {
public:
    int  Action();  // 0x00d56c30 (SP::cBehaviorSpaceTurret::Action)
    int  GetActiveTurretCount();                                    // 0x00d54ce0
    int  CountAttackableTurrets();                                  // 0x00d54d90
    void UpdateWeaponData();                                        // 0x00d547e0
    void FUN_00d56630();                                            // 0x00d56630
    void FUN_00d56870();                                            // 0x00d56870

    char            mPad4c[0x28];                                   // +0x4c..+0x73
    cTurretStateTree_s00d5_6c30__action mStateTree;                                    // +0x74
    cSPTimer_s00d5_6c30__action        mLifeTimer;                                     // +0x90
    u32             mnB8;                                           // +0xb8
    Vec3f           mCityCenter;                                    // +0xbc
    int             mnSdrBeamLifetime;                              // +0xc8
    u32             mnCc;                                           // +0xcc
    i64             mReattackDelay;                                 // +0xd0
    bool            mbAirRaidOn;                                    // +0xd8
    char            mPadD9[7];                                      // +0xd9..+0xdf
    cSPTimer_s00d5_6c30__action        mAirRaidTimer;                                  // +0xe0
};
}
namespace SP {
extern float gAirRaidHealthLimit;                                   // 0x013ec4d0
}
// ---- items of slice s00d56c30_action end

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
StatePair::StatePair(const int& key, const cSpaceTurretStateInfo& src)
    : mKey(key), mValue(src)
{
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

        StatePair pair(key, src);
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
        _ReadWriteBarrier();
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

// @ 0x00d56c30
namespace SP {
int cBehaviorSpaceTurret_s00d5_6c30__action::Action()
{
    if (GetCurrentGameMode() == (void*)0x1654c05) {
        if (cSPLivingUniverse::GetActivePlanet()->GetToolMode() == 4)
            return 1;
    }
    if (mAgentList.mnIndex == 0x3fffffff) {
        ClearAllTargets(&mAgentList);
        return 0;
    }
    if (GetActiveTurretCount() == 0) {
        ClearAllTargets(&mAgentList);
        return 0;
    }
    if (mTargetList.Size() == 0) {
        ClearAllTargets(&mAgentList);
        return 0;
    }

    cCivilization_s00d5_6c30__action* pCiv = NounManager()->GetPlayerCivilization();

    // The turret this behaviour currently watches is the head of the target list.
    cTurret_s00d5_6c30__action* pTarget = 0;
    {
        cInteractionAgent_s00d5_6c30__action* pAgent0 =
            (cInteractionAgent_s00d5_6c30__action*)mTargetList.mpBlocks[mTargetList.mnIndex >> 7]
                ->mEntries[mTargetList.mnIndex & 0x7f].mpObject;
        if (pAgent0 != 0) {
            pTarget = pAgent0->GetTargetInterface((void*)0xee9b2232);
            if (pTarget != 0)
                pTarget->OnTargetSelected();
        }
    }

    bool bAttack = false;
    if (IsPlanetAttackableByPlayer(pTarget))
        bAttack = true;
    bool bMission = false;
    if (IsMissionOfTypeActiveAtPlanet(cSPLivingUniverse::GetActivePlanet()))
        bMission = true;
    if (pTarget->mField748 >= gAirRaidHealthLimit)
        bMission = false;
    if (FUN_01041cf0())
        bAttack = true;

    if (!mbAirRaidOn) {
        if (bAttack)
            bAttack = UpdateAirRaidSiren(pCiv, pTarget);
        else
            StopAirRaidEffect();
    } else if (!bAttack) {
        StopAirRaidEffect();
    }
    bool bRaid = bAttack || bMission || FUN_01041cf0();

    if (!mbAirRaidOn && bRaid)
        FUN_00d56630();
    mbAirRaidOn = bRaid;

    if (!bRaid) {
        // Raid over: drop the effect on every turret that still owns one.
        FUN_00d56870();
        cSlotIterator_s00d5_6c30__action it;
        mAgentList.Begin(&it);
        while (it != mAgentList.End()) {
            cInteractionAgent_s00d5_6c30__action* pAgent = (cInteractionAgent_s00d5_6c30__action*)mAgentList.At(it).mpObject;
            if (pAgent != 0) {
                cTurret_s00d5_6c30__action* pTurret = pAgent->GetTurretInterface((void*)0x436f315);
                if (pTurret != 0 && pTurret->mAirRaidEffect.mpObject != 0)
                    pTurret->mAirRaidEffect.mpObject->e0c(0);
            }
            it.Increment();
        }
        return 1;
    }

    UpdateWeaponData();
    i64 tNow = mLifeTimer.GetElapsedTime();
    if (tNow > mLifeTimer.mNextEventTime) {
        cSlotIterator_s00d5_6c30__action fireIt;
        mAgentList.Begin(&fireIt);
        cTurret_s00d5_6c30__action* pShooter = ResolveSlotTurret(&mAgentList.At(fireIt));
        cSpaceToolData* pWeapon = pShooter->GetToolData69c();
        mLifeTimer.mNextEventTime = tNow + pWeapon->GetCooldown();

        cTurret_s00d5_6c30__action* pCreature = FindNearestCreature(
            *pTarget->mBody.GetPosition(), bAttack, bMission);
        if (pCreature != 0 && !pCreature->AcceptTarget(1)) {
            Vec3f creaturePos = *pCreature->mSpatial.GetPosition();
            Vec3f toCreature = creaturePos - mCityCenter;
            pWeapon->GetField1e8();
            pWeapon->GetMaxRange();
            Vec3f nToCreature;
            Vec3f nCenter;
            if (Dot3(Vec3_Normalize(&nToCreature, &toCreature),
                     Vec3_Normalize(&nCenter, &mCityCenter)) >= 0.0f) {
                int nShots = (GetActiveTurretCount() - CountAttackableTurrets())
                             * mnSdrBeamLifetime;
                cFirePattern pattern;
                pattern.mpBegin = 0;
                pattern.mpEnd = 0;
                pattern.mpCapacity = 0;
                UpdateFirePattern(&pattern, nShots, pCreature);
                int nSlots = (int)(pattern.mpEnd - pattern.mpBegin);
                cSlotIterator_s00d5_6c30__action it2;
                mAgentList.Begin(&it2);
                cFireSlot* pSlot = &pattern.mpBegin[nSlots - 1];
                for (; nSlots > 0; --nSlots, --pSlot) {
                    cInteractionAgent_s00d5_6c30__action* pAgent = (cInteractionAgent_s00d5_6c30__action*)mAgentList.At(it2).mpObject;
                    cTurret_s00d5_6c30__action* pTurret = ResolveTurret(pAgent);
                    if (pTurret->mCombatant.GetDamageState() != 2
                        && !pTurret->mCombatant.IsHostileAlive()) {
                        Vec3f position;
                        position.x = pSlot->x;
                        position.y = pSlot->y;
                        position.z = pSlot->z;
                        cSpaceToolData* pTool = pTurret->GetToolData69c();
                        ToolManager()->UseToolStart(
                            pTool, pTurret != 0 ? &pTurret->mCombatant : (cCombatant_s00d5_6c30__action*)0,
                            &position, -1, 0, &pCreature->mSpatial, 1);
                        ToolManager()->UseToolStop(pTool);
                    }
                    it2.Increment();
                    if (it2 == mAgentList.End())
                        mAgentList.Begin(&it2);
                }
                DestroyFirePattern(&pattern);
            }
        }
    }

    cSlotIterator_s00d5_6c30__action it;
    mAgentList.Begin(&it);
    while (it != mAgentList.End()) {
        cInteractionAgent_s00d5_6c30__action* pAgent = (cInteractionAgent_s00d5_6c30__action*)mAgentList.At(it).mpObject;
        cTurret_s00d5_6c30__action* pTurret = 0;
        if (pAgent != 0)
            pTurret = pAgent->GetTurretInterface((void*)0x436f315);
        cTurretState* pState = mStateTree.Find(&pAgent);
        cCombatant_s00d5_6c30__action* pCombatant = &pTurret->mCombatant;

        const Vec3f* pAim = 0;
        if (pCombatant->GetDamageState() != 2 && !pCombatant->IsHostileAlive()) {
            cSpaceToolData* pPrimary = pTurret->GetToolData698();
            cSpaceToolData* pSecondary = pTurret->GetToolData694();
            bool bFired = false;
            if (tNow > pState->mLastFireTime) {
                pState->mLastFireTime += pPrimary->GetCooldown();
                bFired = true;
            }
            if (pState->mNextEffectTime == 0) {
                pState->mNextEffectTime = tNow + mReattackDelay;
                pState->mNextFireTime = tNow + pSecondary->GetCooldown();
            }

            if (tNow > pState->mNextFireTime - 1000) {
                if (pState->mnFlag == 1 && pTurret->mAirRaidEffect.mpObject == 0) {
                    cEffectManager* pEffects = EffectsManagerPtr_s00d5_6c30__action();
                    if (pEffects->CreateEffect((void*)0xc19e6439, 0,
                                               pTurret->mAirRaidEffect.AsPPTypeParam())) {
                        XformMsg msg;
                        msg.mFlags |= 2;
                        msg.mSeq += 1;
                        Matrix3Rows orientation;
                        Vec3f nFacing;
                        Vec3f nUp;
                        Vec3_Normalize(&nFacing, pTurret->mSpatial.GetPosition());
                        OrthogonalVector(&nUp, &nFacing);
                        Vec3_Normalize(&nUp, &nUp);
                        Matrix3FromFacingAndUp(&orientation, &nFacing, &nUp);
                        msg.mOrientation = orientation;
                        msg.SetPosition(pTurret->mSpatial.GetPosition());
                        pTurret->mAirRaidEffect.mpObject->SetXform(&msg);
                        pTurret->mAirRaidEffect.mpObject->e08(0);
                    }
                }
            } else if (tNow > pState->mNextEffectTime) {
                cVisualEffect* pEffect = pTurret->mAirRaidEffect.mpObject;
                if (pEffect != 0 && pEffect->IsActive())
                    pEffect->e0c(0);
                cVisualEffect* pOld = pTurret->mAirRaidEffect.mpObject;
                if (pOld != 0) {
                    pTurret->mAirRaidEffect.mpObject = 0;
                    pOld->Release();
                }
            }

            if (tNow > pState->mNextFireTime) {
                pState->mNextEffectTime = tNow + mReattackDelay;
                pState->mNextFireTime = tNow + pSecondary->GetCooldown();
                pState->mnFlag = (pState->mnFlag == 0);
            }

            cTurret_s00d5_6c30__action* pCreature = FindNearestCreature(
                *pTarget->mBody.GetPosition(), bAttack, bMission);
            if (pCreature != 0 && !pCreature->AcceptTarget(1)) {
                Vec3f creaturePos = *pCreature->mSpatial.GetPosition();
                Vec3f toCreature = creaturePos - mCityCenter;
                Vec3f nToCreature;
                Vec3f nCenter;
                bool bFacing =
                    Dot3(Vec3_Normalize(&nToCreature, &toCreature),
                         Vec3_Normalize(&nCenter, &mCityCenter)) >= 0.0f;
                pTurret->FaceAtTarget(&pCreature->mTargetPos);

                Vec3f* pTurretPos = pCombatant->GetSpatial()->GetPosition();
                float dx = creaturePos.x - pTurretPos->x;
                float dy = creaturePos.y - pTurretPos->y;
                float dz = creaturePos.z - pTurretPos->z;
                float fDist = sqrtf(dz * dz + dy * dy + dx * dx);

                bool bAim;
                if (fDist <= pPrimary->GetMinRange()
                    || fDist >= pPrimary->GetMaxRange()) {
                    bAim = fDist < pSecondary->GetMaxRange()
                           && tNow < pState->mNextEffectTime && bFacing
                           && pState->mnFlag == 0;
                } else {
                    bAim = bFired && bFacing;
                }
                if (bAim)
                    pAim = &pCreature->mTargetPos;
            }
        }
        pCombatant->SetTarget(pAim);
        it.Increment();
    }
    return 1;
}
}  // namespace SP

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
