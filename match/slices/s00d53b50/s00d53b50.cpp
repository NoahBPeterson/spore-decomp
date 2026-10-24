// Slice s00d53b50: pick / place a nearby noun on a ring around the avatar (0x00d53b50, 1.9 KB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Place(target, outPos): every slot of the list at +0x20/+0x24 has an angle (+4); the slot's
// direction (the avatar's up-vector rotated by that angle about the avatar's position axis) is
// scored by |1 - dot(dir, direction to target)| into +8, the list is sorted by that score
// (eastl::sort with FUN_00d52c90), the first usable slot (angle inside the ring window while in
// the planet mode, farther from the avatar than the target) takes the target noun and the
// resulting point is projected onto the planet surface. Names are Claude-coined.
#include "types.h"
#include <math.h>

typedef unsigned int uint;

#define PV(n) virtual void pv##n();

struct Vec3 { float x, y, z; };
typedef Vec3 Vector3;

// ---------------------------------------------------------------------------- stubs
struct NounSub {                                     // polymorphic member at Noun+0xc0
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10();
    virtual const Vec3* GetPosition();               // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void GetDirection(Vec3* out);            // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                       // +0x74
};
struct Noun {
    virtual void AddRef();                           // +0
    virtual void Release();                          // +4
    char pad[0xc0 - 4];
    NounSub mSub;                                    // +0xc0
};
struct Entry {
    Noun* mpNoun;                                    // +0 (AutoRefCount<Noun>)
    float mAngle;                                    // +4
    float mScore;                                    // +8
};
struct NounMgr { Noun* GetAvatar(); };               // 0x00b1fdb0
NounMgr* NounManager();                              // 0x00b3d300
const void* GetCurrentGameMode();                    // 0x00b5b800
extern char gPlanetMode;                             // 0x01654c10
extern const float kRingRadius;                      // 0x01583d24
extern const float kOffsetBase;                      // 0x01582e04

struct PlanetModelT { Vec3* Project(Vec3* out, const Vec3* in); };   // 0x00b816f0 (ret 8)
PlanetModelT* PlanetModel();                         // 0x00b3d350
void FUN_00d99e20(const Vec3* pos, Vec3* res);       // cdecl
void FUN_00c0b9d0(void* pArg);                       // cdecl

typedef char (__cdecl* Cmp)(Entry*, Entry*);
extern "C" char __cdecl F52c90(Entry*, Entry*);      // 0x00d52c90
void introsort(Entry** first, Entry** last, int depth, Cmp pred);    // 0x00d53940 (cdecl)
void insertion_sort(Entry** first, Entry** last, Cmp pred);          // 0x00b909f0 (cdecl)

static inline int Log2(int n) { int k = 0; while (n) { n >>= 1; ++k; } return k; }

static __forceinline void SortEntries(Entry** first, Entry** last, Cmp cmp)
{
    if (first != last) {
        int lg = Log2(last - first);
        introsort(first, last, lg * 2 - 2, cmp);
        if (last - first > 28) {
            insertion_sort(first, first + 28, cmp);
            for (Entry** p = first + 28; p != last; ++p) {       // unguarded insertion sort
                Entry* val = *p;
                float key = val->mScore;
                Entry** q = p;
                Entry** r = p;
                while (true) {
                    --r;
                    if ((*r)->mScore <= key) break;
                    *q = *r;
                    --q;
                }
                *q = val;
            }
        } else {
            insertion_sort(first, last, cmp);
        }
    }
}

// Rotate v about the unit axis n by angle (quaternion form).
static inline void RotateAxis(Vec3* u, const Vec3& n, float angle, const Vec3& v)
{
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    float qx = s * n.x;
    float qy = n.y * s;
    float qz = n.z * s;
    u->x = (((qy * qx) - (c * qz)) * v.y + ((c * qy) + (qz * qx)) * v.z) * 2.0f
           + (1.0f - (qy * qy + qz * qz) * 2.0f) * v.x;
    u->y = (((qz * qy) - (c * qx)) * v.z + ((c * qz) + (qy * qx)) * v.x) * 2.0f
           + (1.0f - (qz * qz + qx * qx) * 2.0f) * v.y;
    u->z = (((qz * qx) - (c * qy)) * v.x + ((c * qx) + (qz * qy)) * v.y) * 2.0f
           + (1.0f - (qy * qy + qx * qx) * 2.0f) * v.z;
}

class cRingPlacer {
public:
    char pad00[0x20];
    Entry** mpBegin;                                 // +0x20
    Entry** mpEnd;                                   // +0x24

    Entry* Place(Noun* target, Vec3* outPos);
};

// @ 0x00d53b50
Entry* cRingPlacer::Place(Noun* target, Vec3* outPos)
{
    NounSub* av = (NounSub*)((char*)NounManager()->GetAvatar() + 0xc0);
    const Vec3* p = av->GetPosition();
    float px = p->x;
    float invLen = 1.0f / sqrtf((px * px + p->y * p->y) + p->z * p->z + 1e-8f);
    Vec3 n;
    n.x = px * invLen;
    n.y = p->y * invLen;
    n.z = p->z * invLen;
    Vec3 v;
    av->GetDirection(&v);

    const Vec3* ap = av->GetPosition();
    NounSub* tsub = &target->mSub;
    const Vec3* tp = tsub->GetPosition();
    float dy = tp->y - ap->y;
    float dz = tp->z - ap->z;
    float dx = tp->x - ap->x;
    float distSq = (dz * dz + dy * dy) + dx * dx;
    float invD = 1.0f / sqrtf(distSq + 1e-8f);
    Vec3 t;
    t.x = invD * dx;
    t.y = dy * invD;
    t.z = dz * invD;
    float dnx = t.x, dny = t.y, dnz = t.z;

    Entry* found = 0;
    Entry** end = mpEnd;
    for (Entry** it = mpBegin; it != end; ++it) {
        Entry* e = *it;
        RotateAxis(&t, n, e->mAngle, v);
        e->mScore = fabsf(1.0f - ((t.x * dnx + t.z * dnz) + t.y * dny));
        if (e->mpNoun == target) found = e;
    }

    SortEntries(mpBegin, mpEnd, F52c90);

    bool planet = (GetCurrentGameMode() == &gPlanetMode);
    Entry** cursor = mpBegin;
    Entry* chosen = 0;
    float ring = kRingRadius;
    for (; cursor != end; ++cursor) {
        chosen = *cursor;
        if (planet) {
            float a = chosen->mAngle;
            if (ring * 0.5f > a) continue;
            if (a > ring * 1.5f) continue;
        }
        Noun* cur = chosen->mpNoun;
        if (cur && cur != target) {
            const Vec3* a1 = av->GetPosition();
            const Vec3* t1 = cur->mSub.GetPosition();
            float ey = t1->y - a1->y;
            float ez = t1->z - a1->z;
            float ex = t1->x - a1->x;
            float thr = distSq + 1.0f;
            if (!(((ez * ez + ey * ey) + ex * ex) > thr)) continue;
        }
        if (found) {
            Noun* t = found->mpNoun;
            if (t) { found->mpNoun = 0; t->Release(); }
        }
        break;
    }
    if (cursor == end) return 0;

    Noun* old = chosen->mpNoun;
    if (old != target) {
        target->AddRef();
        chosen->mpNoun = target;
        if (old) old->Release();
    }
    RotateAxis(&t, n, chosen->mAngle, v);
    float k1 = kOffsetBase + 1.0f;
    float rt = tsub->GetRadius();
    float ra = av->GetRadius();
    float r = (ra + rt) + k1;
    Vec3 off;
    off.x = t.x * r;
    off.y = t.y * r;
    off.z = t.z * r;
    const Vec3* pa = av->GetPosition();
    t.x = off.x + pa->x;
    t.z = pa->z + off.z;
    t.y = pa->y + off.y;
    Vec3* proj = PlanetModel()->Project(&off, &t);
    *outPos = *proj;
    FUN_00d99e20(tsub->GetPosition(), outPos);
    return chosen;
}

// ---------------------------------------------------------------------------------------------
// SP::cBehaviorSpaceTurret helpers (0x00d54730..0x00d54c10). The turret keeps an airborne-weapon
// record (a 0x2c-byte block: a pointer, a flag word, a pointer, an AutoRefCount and seven
// values), an air-raid timer (0x0169ebc0) and an AutoRefCount<IVisualEffect> (0x0169ebe0).
namespace SP {

struct RefCounted
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
    virtual void AddRef();                                  // +0x18
};

struct WeaponSource                                         // the game-data template (0x24 bytes)
{
    void*        mpObject;                                  // +0x00
    RefCounted*  mpRef;                                     // +0x04
    uint32_t     mValues[7];                                // +0x08
};

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

struct SPObject
{
    PV(0) PV(1)
    virtual void* QueryInterface(uint32_t nID);             // +0x08
};

bool __stdcall CanJoin(void* pObject, int nUnused);         // 0x00d54730

struct cSPTimer
{
    void Stop();                                            // 0x00bc3110
    void Restart();                                         // 0x00bc3130
    bool IsRunning();                                       // 0x00feba90
    unsigned long long GetElapsedTime();                    // 0x00bc3190
};

struct EffectParams;
struct IVisualEffect
{
    PV(0)
    virtual void Release();                                 // +0x04
    virtual void Start(int bImmediate);                     // +0x08
    virtual void Stop(int bImmediate);                      // +0x0c
    PV(4) PV(5)
    virtual void SetParams(const EffectParams* pParams);    // +0x18
};

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

extern cSPTimer       sAirRaidTimer;                        // 0x0169ebc0
extern AutoRef<IVisualEffect> spAirRaidEffect;              // 0x0169ebe0 (AutoRefCount)

void StopAirRaidEffect();                                   // 0x00d54760

} // namespace SP

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

// ---------------------------------------------------------------------------------------------
// The turret's own update helpers share a few engine types: the property system (a hash-keyed
// property set with typed values), the space-combat tuning singleton, the visual-effect manager
// and a small matrix used to place the air-raid siren effect.
namespace SP {

typedef int64_t int64;
typedef uint64_t uint64;

struct Property
{
    uint16_t mPad00[9];                                     // +0x00
    uint16_t mType;                                         // +0x12 (property type id)
    int*     GetInt();                                      // 0x0041e990
    float*   GetFloat();                                    // 0x0041ea70 (GetPropertyAsFloat)
};

struct PropertySet
{
    PV(0)
    virtual void Release();                                 // +0x04
    PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual bool GetProperty(uint32_t nID, Property** ppOut);   // +0x24
};

struct PropertyManager
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual bool FindPropertySet(uint32_t nID, PropertySet** ppOut);   // +0x30
};
PropertyManager* GetPropertyManager();                      // 0x0067de30

struct Matrix33
{
    float m[9];
    void Assign(const Matrix33& src);                       // 0x0041cb40 (cSPMatrix3::Assign)
};

struct EffectParams                                         // what SetParams takes
{
    uint16_t mFlags;                                        // +0x00
    uint16_t mCount;                                        // +0x02
    Vector3  mPosition;                                     // +0x04
    float    mScale;                                        // +0x10
    Matrix33 mMatrix;                                       // +0x14
};

struct IEffectsManager
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual IVisualEffect* CreateEffect(uint32_t nID, void* pOwner, IVisualEffect** ppOut);   // +0x2c
};
IEffectsManager* EffectsManagerPtr();                       // 0x0067ddd0

struct cSPSpaceCombatTuning
{
    unsigned long long GetAirRaidSirenTimeMS();             // 0x01029af0
};
cSPSpaceCombatTuning* GetSpaceCombatTuning();               // 0x01029940

struct TurretTransform
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vector3* GetTranslation();                // +0x2c
};

struct WeaponEffectSlot
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void Stop(int bImmediate);                      // +0x50
};

struct cTurret
{
    PV(0)
    virtual void* QueryInterface(uint32_t nID);             // +0x08
    char              pad0c[0x120 - 4];
    TurretTransform   mTransform;                           // +0x120
    char              pad124[0x588 - 0x124];
    WeaponEffectSlot  mEffect;                              // +0x588
    void FaceAtTarget(int nTarget);                         // 0x00bce480
};

struct SlotEntry
{
    uint32_t mPad00;                                        // +0x00
    void*    mpItem;                                        // +0x04
};
struct SlotBucket { SlotEntry mEntries[128]; };
struct SlotVector                                           // spstl::slot_vector_base (128 entries per bucket)
{
    SlotBucket** mpBuckets;                                 // +0x00
    SlotBucket** mpBucketsEnd;                              // +0x04
    uint32_t     mPad08[3];
    int          mTail;                                     // +0x14
    int          mCount;                                    // +0x18
};
struct SlotIter
{
    SlotVector* mpVector;                                   // +0x00
    uint32_t    mIndex;                                     // +0x04
    void increment();                                       // 0x00abe9b0
};

struct cBehaviorSpaceTurret
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

bool __cdecl UpdateAirRaidSiren(cBehaviorSpaceTurret* pTurret);   // 0x00d54940
void __cdecl ClearAllTargets(SlotVector* pVec);                   // 0x00d54c10
int  __cdecl AddPosseMember(cBehaviorSpaceTurret* pTurret, void* pCreature);   // 0x00d54330

extern Vector3 sAirRaidSirenOffset;                         // 0x0169ec18
extern Matrix33 sAirRaidSirenMatrix;                        // 0x0169ebf4

} // namespace SP

// @ 0x00d547e0
void SP::cBehaviorSpaceTurret::UpdateWeaponData()
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

// @ 0x00d54940
bool __cdecl SP::UpdateAirRaidSiren(SP::cBehaviorSpaceTurret* pTurret)
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

static int SlotEnd(SP::SlotVector* pVec)
{
    return (int)(pVec->mpBucketsEnd - pVec->mpBuckets) * 0x80 + pVec->mTail - 0x7f;
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
        SP::cTurret* pTurret = pItem
            ? (SP::cTurret*)((SP::SPObject*)pItem)->QueryInterface(0x436f315) : 0;
        pTurret->mEffect.Stop(0);
        pTurret->FaceAtTarget(0);
        it.increment();
    }
}

// @ 0x00d54330
int __cdecl SP::AddPosseMember(SP::cBehaviorSpaceTurret* pTurret, void* pCreature)
{
    // A creature joins the avatar's posse (capped at three) unless it is an enemy or already a
    // member; joining drops the creature's UI selection, herd membership and target.
    const void* pMode = GetCurrentGameMode();
    bool bEnemy = false;
    if (pMode != &gPlanetMode)
        bEnemy = true;
    if (!NounManager()->GetAvatar())
        return 0;
    if (pTurret->mpTarget == pCreature)
        return 0;
    (void)pCreature;
    FUN_00c0b9d0(0);
    if (pCreature) {
        SP::cTurret* pNew = (SP::cTurret*)((SP::SPObject*)pCreature)->QueryInterface(0x436f315);
        if (pNew)
            pNew->FaceAtTarget(0);
    }
    return 1;
}


