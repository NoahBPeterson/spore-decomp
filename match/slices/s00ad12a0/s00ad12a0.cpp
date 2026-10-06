// Slice s00ad12a0 — tribe casting manager update: tracks the tribes near the camera and
// populates them with creatures from the creature pool.
// PDB candidate (caller-scored, unconfirmed): SP::cPlayer::SetSelectionGroup — the body does not fit it;
// the debug string names it "Casting Manager".
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no EH frame although locals have destructors).
#include "types.h"
#include <math.h>

inline void* operator new(unsigned int, void* p) throw() { return p; }
void __cdecl operator_delete__(void* p);                  // 0xf47380 (operator delete[])
extern "C" int __cdecl atexit(void (__cdecl*)(void));

// ---- math -------------------------------------------------------------
// EA SSE asm helper (truncating float->int, result in eax).
#pragma warning(disable: 4035)
__forceinline int TruncToInt(float f) { __asm cvttss2si eax, f }
#pragma warning(default: 4035)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline bool operator!=(const Vector3& a, const Vector3& b) { return a.x != b.x || a.y != b.y || a.z != b.z; }
struct Quaternion { float x, y, z, w; };
struct Matrix3 { Vector3 row[3]; };

extern Vector3 g_ZeroVector;                              // 0x167a390 (Vector3::ZERO)
extern Matrix3 g_IdentityMatrix3;                         // 0x167a464 (Matrix3::IDENTITY)

namespace SP { Matrix3 __cdecl Matrix3FromQuaternion(const Quaternion& q); }                 // 0x59c190
namespace rw { Quaternion __cdecl QuaternionFromMatrix33(const Matrix3& m, float tolerance); } // 0x472b80

struct cTransform {                       // 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;

    cTransform() : mFlags(0), mModificationCount(0), mTranslation(g_ZeroVector), mScale(1.0f), mRotation(g_IdentityMatrix3) {}
    cTransform& operator=(const cTransform& o);           // 0x537dc0
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; ++mModificationCount; }
    void SetTranslation(const Vector3& v) { mTranslation = v; mFlags |= 4; ++mModificationCount; }
};

struct RandomLCG { uint32_t mnSeed; uint32_t RandomUint32Uniform(uint32_t n); };  // 0xa68fb0
extern RandomLCG g_MathRandom;                            // 0x1601760

// ---- EASTL pieces ---------------------------------------------------------
struct IRefCounted {
    virtual int AddRef();                                 // +0x00
    virtual int Release();                                // +0x04
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x)
    {
        T* const pObject = x.mpObject;
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    // Assigning a live (already dereferenced) object: the original skips the null test on AddRef.
    void AssignLive(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
};

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
    void deallocate(void* p)
    {
        if (((uint32_t*)p)[-1])
            operator_delete__(p);
    }
};

template <class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}
template <class T> T* __cdecl copy_ptrs(T* first, T* last, T* dest);                // 0x6782c0 (eastl::copy)

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector()
    {
        destruct(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](unsigned i) { return mpBegin[i]; }
    T& back() { return *(mpEnd - 1); }

    void reserve(unsigned n);
    T* erase(T* first, T* last);                    // out-of-line instance
    void DoInsertValue(T* pos, const T& value);
    SpVector& operator=(const SpVector& x);

    T* EraseInline(T* first, T* last)
    {
        T* const pNewEnd = copy_ptrs(last, mpEnd, first);
        destruct(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void push_back()
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
    }
    void pop_back()
    {
        --mpEnd;
        mpEnd->~T();
    }
};

struct eastl_string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    eastl_string() { mpBegin = mpEnd = g_EmptyString; mpCapacity = g_EmptyString + 1; }
    ~eastl_string()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator_delete__(mpBegin);
    }
    eastl_string& sprintf(const char* fmt, ...);    // 0x472fe0
    static char g_EmptyString[];                    // 0x1667bac
};

// ---- game objects -----------------------------------------------------------
struct cSpatial {                       // interface subobject
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
};
struct cSpatialSetter {                 // creature subobject at +0xc0
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void SetPosition(const Vector3& p);      // +0x38
    virtual void SetOrientation(const Quaternion& q);// +0x3c
};

struct cTribeTool {
    uint32_t pad00[13];
    cSpatial mSpatial;                               // +0x34
};

struct cCreatureData { uint32_t pad[383]; uint32_t mFlags; };   // +0x5fc

struct cCreature;
struct cTribe : IRefCounted {
    virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual SpVector<cCreature*>* GetCreatures();    // +0x90
    virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual SpVector<cTribeTool*>* GetTools();       // +0xbc

    uint32_t pad04[71];
    cSpatial mSpatial;                               // +0x120

    bool IsActive();                                 // 0xc8e800
    void SetPopulating(int b);                       // 0xc8fc50
    int GetAdultPopulation();                        // 0xc8f370
    cCreature* GetChieftain();                       // 0xc8fd30
    void PromoteChieftain(cCreature* c);             // 0xc8fd50
    void AddCreature(cCreature* c);                  // 0xc96e80
};

struct cCreature {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84();
    virtual void SetIdleTime(float t);               // +0x88
    virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4();
    virtual void Spawn(int a, cTribe* tribe, int b, const Vector3& pos);   // +0xe8

    uint32_t pad04[47];
    cSpatialSetter mSpatial;                         // +0xc0
    uint32_t padc4[658];
    cCreatureData* mpData;                           // +0xb4c

    bool IsIdle();                                   // 0xc24560
    int GetAge();                                    // 0xc0b760
};

struct cPoolObject {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cCreature* Cast(uint32_t typeID);        // +0x0c
};
struct cPoolEntry { uint32_t mKey; bool mbInUse; uint8_t pad[3]; cPoolObject* mpObject; };   // 12 bytes
struct cCreaturePool { uint32_t pad00[2]; SpVector<cPoolEntry> mEntries; };                // +0x08
struct cPoolManager { cCreaturePool* GetPool(const void* const* key); };                    // 0xad0ca0

struct cTransformListener {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void Transform(const cTransform& in, cTransform& out, const cTransform& ref);   // +0x10
};

template <class T> struct cGameDataList { uint32_t pad00; SpVector<AutoRefCount<T> > mItems; };   // +0x04

typedef void (__cdecl *GameDataFn)();
void __cdecl FUN_00cd7d10();
void __cdecl FUN_00d3d420();
void __cdecl FUN_00accb30();
void __cdecl FUN_00accbb0();
void __cdecl FUN_00b1e500();
extern const char g_CitizenTypeTag;                  // 0x18eb4b7
extern const char g_TribeTypeTag;                    // 0x18c6d19
struct cGameNounManager {
    void* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, const void* tag);   // 0xb21340
};
namespace SP { cGameNounManager* __cdecl NounManager(); }   // 0xb3d300

struct cSpaceRelationshipTuning { uint32_t pad00[19]; bool mbEnabled; };   // +0x4c
namespace SP { cSpaceRelationshipTuning* __cdecl GetSpaceRelationshipTuning(); }   // 0x10407c0
struct cGameModeInfo { const void* GetLocation(); };      // 0xa42730
cGameModeInfo* __cdecl GetGameModeInfo();                 // 0xb3d320
extern const char g_LocationTribe;                        // 0x1654c05
extern const char g_GameModeTribe;                        // 0x1654c04
namespace SP { const void* __cdecl GetCurrentGameMode(); }   // 0xb5b800

struct VarMap {
    void SetVar(const char* name, float value);           // 0x7f25c0
    void PushScope(const char* name);                     // 0x7f20d0
    float GetVar(const char* name);                       // 0x7f2590
};
extern VarMap g_VarMap;                                   // 0x167a3d0
extern float g_HuntingProbability;                        // 0x167a364
extern float g_EatingProbability;                         // 0x167a368
extern float g_RestProbability;                           // 0x167a36c
extern float g_FishingProbability;                        // 0x167a370
extern float g_MatingProbability;                         // 0x167a374
extern int g_NewBehaviorCap;                              // 0x167a388
extern int g_NewBehaviorCount;                            // 0x167a38c
extern unsigned g_MaxActiveTribes;                        // 0x1565d08

struct cViewer { void GetCameraLocationInfo(Vector3* pos, Vector3* dir, int a, int b); };   // 0x7c3d30
struct IGameModeMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual cViewer* GetViewer();                         // +0x1c
};
struct IApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual IGameModeMgr* GetGameModeManager();           // +0x50
};
namespace SP { IApp* __cdecl App(); }                     // 0x67dd10

struct cTerrainCameraController { const Vector3& GetAnchorDirection0(); };   // 0xb10200
cTerrainCameraController* __cdecl GetTerrainCameraController();              // 0xb3d280
struct cPlanetModel {
    Vector3 SnapToSurface(const Vector3& p);                                       // 0xb81630
    Vector3 Intersect(const Vector3& pos, const Vector3& dir);                     // 0xb82060
    Vector3 MakeRandomWorldPosition(const Vector3& center, float minR, float maxR); // 0xb81780
};
namespace SP { cPlanetModel* __cdecl PlanetModel(); }     // 0xb3d350

struct DistanceCompare { Vector3 mPos; };
void __cdecl partial_sort(AutoRefCount<cTribe>* first, AutoRefCount<cTribe>* middle,
                          AutoRefCount<cTribe>* last, DistanceCompare compare);   // 0xdc2ee0

// out-of-line template instances
template <> AutoRefCount<cTribe>* SpVector<AutoRefCount<cTribe> >::erase(AutoRefCount<cTribe>* first, AutoRefCount<cTribe>* last);   // 0xe25bd0
template <> void SpVector<AutoRefCount<cTribe> >::reserve(unsigned n);                     // 0xd01790
template <> void SpVector<AutoRefCount<cTribe> >::DoInsertValue(AutoRefCount<cTribe>* pos, const AutoRefCount<cTribe>& v);   // 0xaea5d0
template <> AutoRefCount<cTribe>* __cdecl copy_ptrs(AutoRefCount<cTribe>* first, AutoRefCount<cTribe>* last, AutoRefCount<cTribe>* dest);   // 0x6782c0

struct cTribeEntry {                 // 0x18
    AutoRefCount<cTribe> mpTribe;
    SpVector<AutoRefCount<IRefCounted> > mMembers;
};
template <> SpVector<AutoRefCount<IRefCounted> >& SpVector<AutoRefCount<IRefCounted> >::operator=(const SpVector<AutoRefCount<IRefCounted> >& x);   // 0x1008600
template <> void SpVector<cTribeEntry>::DoInsertValue(cTribeEntry* pos, const cTribeEntry& v);   // 0xacf0b0

struct cCastingManager {
    uint32_t pad00[34];
    cPoolManager mPools;                 // +0x88
    uint32_t pad8c[7];
    SpVector<cTribeEntry> mTribes;       // +0xa8
    uint32_t padbc[41];
    cTransformListener* mpListenerVtbl;  // +0x160 (object with a vtable)

    void AcquireFromPool(cCreaturePool* pool, int index);   // 0xac8a80
    void Update();
};

void cCastingManager::Update()
{
    // ---- citizen idle statistics (tribe stage only) ---------------------------
    if (SP::GetSpaceRelationshipTuning()->mbEnabled && GetGameModeInfo()->GetLocation() == &g_LocationTribe) {
        cGameDataList<cCreature>* citizens = (cGameDataList<cCreature>*)SP::NounManager()->GetGameDataVector(
            FUN_00cd7d10, FUN_00d3d420, FUN_00accb30, FUN_00b1e500, &g_CitizenTypeTag);
        int idle = 0;
        unsigned count = citizens->mItems.size();
        for (unsigned i = 0; i < count; ++i) {
            if (citizens->mItems[i]->IsIdle())
                ++idle;
            else
                citizens->mItems[i]->SetIdleTime(0.2f);
        }
        if (idle) {
            g_VarMap.SetVar("idle_citizens", (float)idle);
            g_VarMap.SetVar("total_citizens", (float)citizens->mItems.size());
            g_VarMap.PushScope("tribe");
            g_HuntingProbability = g_VarMap.GetVar("hunting_probability");
            g_EatingProbability = g_VarMap.GetVar("eating_probability");
            g_RestProbability = g_VarMap.GetVar("rest_probability");
            g_FishingProbability = g_VarMap.GetVar("fishing_probability");
            g_MatingProbability = g_VarMap.GetVar("mating_probability");
            g_NewBehaviorCap = TruncToInt(g_VarMap.GetVar("new_behavior_cap"));
            g_NewBehaviorCount = 0;
        }
    }

    // ---- pick the active tribes nearest to the camera ---------------------------
    SpVector<AutoRefCount<cTribe> >& tribes = ((cGameDataList<cTribe>*)SP::NounManager()->GetGameDataVector(
        FUN_00cd7d10, FUN_00d3d420, FUN_00accbb0, FUN_00b1e500, &g_TribeTypeTag))->mItems;
    static SpVector<AutoRefCount<cTribe> > sActiveTribes;
    sActiveTribes.erase(sActiveTribes.mpBegin, sActiveTribes.mpEnd);

    if (tribes.mpBegin != tribes.mpEnd) {
        Vector3 camPos;
        Vector3 camDir;
        SP::App()->GetGameModeManager()->GetViewer()->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
        cTerrainCameraController* controller = GetTerrainCameraController();
        if (controller) {
            if (controller->GetAnchorDirection0() != g_ZeroVector)
                camPos = SP::PlanetModel()->SnapToSurface(camPos);
        } else {
            Vector3 hit = SP::PlanetModel()->Intersect(camPos, camDir);
            if (hit != g_ZeroVector)
                camPos = hit;
        }

        sActiveTribes.reserve(tribes.size());
        for (unsigned i = 0; i < tribes.size(); ++i) {
            if (tribes[i]->IsActive())
                sActiveTribes.push_back(tribes[i]);
        }

        unsigned keep = g_MaxActiveTribes;
        if (keep > sActiveTribes.size())
            keep = sActiveTribes.size();
        DistanceCompare compare;
        compare.mPos = camPos;
        partial_sort(sActiveTribes.mpBegin, sActiveTribes.mpBegin + keep, sActiveTribes.mpEnd, compare);
        sActiveTribes.EraseInline(sActiveTribes.mpBegin + keep, sActiveTribes.mpEnd);
    }

    // ---- release entries of tribes that are no longer active ----------------------
    for (unsigned i = 0; i < mTribes.size();) {
        cTribeEntry& entry = mTribes[i];
        unsigned n = sActiveTribes.size();
        unsigned j;
        for (j = 0; j < n; ++j)
            if (entry.mpTribe.mpObject == sActiveTribes[j].mpObject)
                break;
        if (j == n && entry.mMembers.empty()) {
            entry.mpTribe->SetPopulating(0);
            entry.mpTribe = mTribes.back().mpTribe;
            entry.mMembers = mTribes.back().mMembers;
            mTribes.pop_back();
        } else {
            ++i;
        }
    }

    // ---- populate newly active tribes ----------------------------------------------
    for (unsigned i = 0; i < sActiveTribes.size(); ++i) {
        cTribe* tribe = sActiveTribes[i].mpObject;
        SpVector<cTribeTool*>* tools = tribe->GetTools();
        unsigned j;
        for (j = 0; j < mTribes.size(); ++j)
            if (mTribes[j].mpTribe.mpObject == tribe)
                break;
        if (j != mTribes.size())
            continue;

        cTransform spawn;
        cTransform placed;
        spawn.SetRotation(SP::Matrix3FromQuaternion(tribe->mSpatial.GetOrientation()));

        Vector3 pos;
        if (tools->size() != 0) {
            tribe->mSpatial.GetPosition();
            pos = (*tools)[g_MathRandom.RandomUint32Uniform(tools->size())]->mSpatial.GetPosition();
        } else {
            pos = SP::PlanetModel()->MakeRandomWorldPosition(tribe->mSpatial.GetPosition(), 20.0f, 30.0f);
        }
        spawn.SetTranslation(pos);
        placed = spawn;

        int adults = tribe->GetAdultPopulation();
        mTribes.push_back();
        cTribeEntry& entry = mTribes.back();
        entry.mpTribe.AssignLive(tribe);
        entry.mpTribe->SetPopulating(1);
        if (adults > 20) {
            eastl_string msg;
            msg.sprintf("Casting Manager - attempting to populate tribe with %d members - tell Jason S!", adults);
            adults = 12;
        }

        SpVector<cCreature*>* creatures = entry.mpTribe->GetCreatures();
        int have = (int)creatures->size();
        if (have < adults) {
            int toSpawn = adults - have;
            const void* key = &g_CitizenTypeTag;
            do {
                cCreaturePool* pool = mPools.GetPool(&key);
                int nEntries = (int)pool->mEntries.size();
                for (int k = 0; k < nEntries; ++k) {
                    if (!pool->mEntries[k].mbInUse) {
                        AcquireFromPool(pool, k);
                        cPoolObject* obj = pool->mEntries[k].mpObject;
                        cCreature* creature;
                        if (obj && (creature = obj->Cast(0x4f176642)) != 0) {
                            mpListenerVtbl->Transform(spawn, placed, spawn);
                            creature->Spawn(0, tribe, 1, placed.mTranslation);
                            creature->mSpatial.SetPosition(placed.mTranslation);
                            Quaternion q = rw::QuaternionFromMatrix33(placed.mRotation, 0.0f);
                            creature->mSpatial.SetOrientation(q);
                            if (tribe->GetChieftain() == 0 && creature->GetAge() == 1)
                                tribe->PromoteChieftain(creature);
                            if (SP::GetSpaceRelationshipTuning()->mbEnabled && GetGameModeInfo()->GetLocation() == &g_LocationTribe)
                                creature->mpData->mFlags |= 0x100;
                            else if (SP::GetCurrentGameMode() == &g_GameModeTribe)
                                creature->mpData->mFlags |= 0x200;
                            tribe->AddCreature(creature);

                            unsigned nTools = tools->size();
                            if (nTools != 0) {
                                float dx = pos.x - spawn.mTranslation.x;
                                float dy = pos.y - spawn.mTranslation.y;
                                float dz = pos.z - spawn.mTranslation.z;
                                if (sqrtf(dx * dx + dy * dy + dz * dz) > 15.0f) {
                                    Vector3 next((*tools)[g_MathRandom.RandomUint32Uniform(nTools)]->mSpatial.GetPosition());
                                    spawn.SetTranslation(next);
                                    placed = spawn;
                                    pos = spawn.mTranslation;
                                }
                            }
                        }
                        break;
                    }
                }
            } while (--toSpawn);
        }
    }

    sActiveTribes.EraseInline(sActiveTribes.mpBegin, sActiveTribes.mpEnd);
}
