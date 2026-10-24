// Slice s00c6d7c0: SP::cHerd::Update (0x00c6d7c0, 2290 bytes, thiscall, 1 stack arg).
// Per-frame herd upkeep: counts the adult guards, picks the "herd mom" creature (personality),
// keeps the egg layer valid, respawns animals while under the target size, updates/removes eggs,
// then ticks the feeding-ground selection.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), as in sibling s00c09fa0.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>
#include <string.h>
#include <xmmintrin.h>

// float -> int via SSE cvtss2si: returns INT_MIN for NaN/out-of-range, matching
// the original. Read from a memory temporary to avoid a scratch xmm register.
__forceinline int FloatToIntSSE(const float& f)
{
    volatile float tmp = f;
    return _mm_cvtss_si32(_mm_load_ss((const float*)&tmp));
}

#pragma warning(disable: 4100)

typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;

// float -> int rounding up (the module's asm helper; cvtss2si + cmovb)
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

template <typename T> inline const T& MinRef(const T& a, const T& b) { return (a < b) ? a : b; }
template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

inline bool TestBit(u32 v, int n) { return (v >> n) & 1; }

__forceinline float DistSq(const Vector3* a, const Vector3* b)
{
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float dz = a->z - b->z;
    return dz * dz + dy * dy + dx * dx;
}

namespace SP {

class cSPTimer { public:
    bool IsRunning();         // 0x00feba90
    u64  GetElapsedTime();    // 0x00bc3190
    void Stop();              // 0x00bc3110
    void Restart();           // 0x00bc3130
    void Init();              // 0x00bc3170
};

// sub-object interface found at +0x34 (nests/eggs) and +0xc0 (animals)
struct ISpatial {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();   // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual bool Slot48();                  // +0x48
    virtual void v4c(); virtual void v50(); virtual void v54();
    virtual bool Slot58();                  // +0x58
};

struct cBehaviorInfo {
    char pad0[0x1d8];
    u32 mBehaviorID;        // +0x1d8
    char pad1dc[0x5fc - 0x1dc];
    u32 mFlags;             // +0x5fc
};

struct cSpeciesProfile;
class cSPCreatureAnimal;

// refcounted creature slot as stored in the herd vectors
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    void reset()
    {
        T* const pTemp = mpObject;
        if (pTemp) {
            mpObject = 0;
            pTemp->Release();
        }
    }
};

class cSPCreatureAnimal {
public:
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
    char pad04[0xc0 - 0x4];
    char mSpatialStorage[4];    // +0xc0: sub-object (accessed via Spatial())
    char pad0c4[0xb20 - 0xc4];
    cSpeciesProfile* mpSpeciesProfile;   // +0xb20
    char padb24[0xb4c - 0xb24];
    cBehaviorInfo* mpBehaviorInfo;       // +0xb4c
    char padb50[0xb58 - 0xb50];
    u32 mGeneralFlags;                   // +0xb58
    char padb5c[0x1628 - 0xb5c];
    cSPTimer mTimer;                     // +0x1628

    bool IsBaby();                                  // 0x00c0b770
    cSPCreatureAnimal* GetTargetAsCreature();       // 0x00c0ee70
    void ResetEggLayer(int n);                      // 0x00c02c20
    int  GetValue2c70();                            // 0x00c02c70
    ISpatial* Spatial() { return (ISpatial*)((char*)this + 0xc0); }
    bool GetFlag135() { return *((char*)this + 0x135) != 0; }
    bool GetFlagB5E() { return *((char*)this + 0xb5e) != 0; }
};

// Ceiling for the AutoRefCount<cSPCreatureAnimal>::operator= instance the original calls out of line
// (identical-code-folded with AutoRefCount<IWinText>::operator=, 0x00b5f950).
struct AnimalRefOut {
    cSPCreatureAnimal* mpObject;
    void Assign(cSPCreatureAnimal* p);   // 0x00b5f950
    AnimalRefOut& operator=(cSPCreatureAnimal* p) { Assign(p); return *this; }
    void reset();
};

inline void AnimalRefOut::reset()
{
    cSPCreatureAnimal* const pTemp = mpObject;
    if (pTemp) {
        mpObject = 0;
        pTemp->Release();
    }
}

class cEgg { public:
    virtual int AddRef();
    virtual int Release();
    char pad04[0x34 - 0x4];
    char mSpatialStorage[4];   // +0x34
    char pad38[0x1f8 - 0x38];
    cSPTimer mTimer;           // +0x1f8
    void Update(int ms);       // 0x00c6b040
    ISpatial* Spatial() { return (ISpatial*)((char*)this + 0x34); }
};

class cNest { public:
    char pad0[0x34];
    char mSpatialStorage[4];   // +0x34
    char pad38[0x84 - 0x38];
    u32 mFlags;                // +0x84
    ISpatial* Spatial() { return (ISpatial*)((char*)this + 0x34); }
};

struct cEggPtr {
    cEgg* mpObject;
    cEggPtr(cEgg* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    cEggPtr(const cEggPtr& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~cEggPtr() { if (mpObject) mpObject->Release(); }
};

class cGameNounManager { public:
    cSPCreatureAnimal* GetAvatar();         // 0x00b1fdb0
    void RemoveNoun(cEgg* egg);             // 0x00b225d0
};

struct cEditorSpeciesManager {
    cSpeciesProfile* GetAvatarProfile();    // 0x004df420
    cSpeciesProfile* GetProfile(const void* key);   // 0x004df550
    struct cArchetype { char pad[0x364]; float mFactor; };
    cArchetype* GetSpeciesArchetype(u32 key, u32 generation);   // 0x004e0050
};

struct cAvatarHolder {
    cSPCreatureAnimal* FUN_00a1ad10();      // 0x00a1ad10
};

struct cGameMode { char pad[0x2c]; int mMode; };

class cPlanetModel { public:
    Vector3* MakeRandomWorldPosition(Vector3* out, const Vector3* center, float minR, float maxR);   // 0x00b81780
};

struct RandomLCG {
    double RandomDoubleUniform();           // 0x009360d0
    u32 RandomUint32Uniform(u32 n);         // 0x00a68fb0
};

class cHerd;

} // namespace SP

extern "C" {
    SP::cGameNounManager*        __cdecl NounManager();           // 0x00b3d300
    SP::cEditorSpeciesManager*   __cdecl FUN_00401090();
    SP::cPlanetModel*            __cdecl PlanetModel();           // 0x00b3d350
    SP::cGameMode*               __cdecl FUN_00b3d4d0();
    SP::cAvatarHolder*           __cdecl FUN_00d51660();
    SP::cSPCreatureAnimal*       __cdecl FUN_00d99500(SP::cSPCreatureAnimal* c);   // creature cast
    bool __cdecl FUN_00c6af40(SP::cSPCreatureAnimal* a, SP::cHerd* herd);
    bool __cdecl FUN_00c699a0(SP::cSPCreatureAnimal* a, SP::cHerd* herd);
    void __cdecl SpawnHerdAnimals(const Vector3* pos, SP::cSpeciesProfile* species, int count, float babyFrac,
                                  SP::cHerd* herd);                                  // 0x00c09fa0
    void __cdecl FUN_00c099e0(const Vector3* pos, SP::cSpeciesProfile* species, int flag, SP::cHerd* herd,
                              int a, int b);                                         // 0x00c099e0
    float __cdecl RandomFloatRange(float lo, float hi);                              // 0x00572a10
    void* __cdecl GetCurrentGameMode();                                              // 0x00b5b800
    bool  __cdecl IsWorldLayoutFlagSet(int flag);                                    // 0x00685520
    void* __cdecl FUN_01021300();                                                    // 0x01021300
    int   __cdecl FUN_00c30f90();                                                    // 0x00c30f90
    bool  __cdecl ResourceKeyNE(const void* key, int val);                           // 0x005f78f0
}

namespace SP {

// Retail GetAnimal-by-index helper types
struct cEggVector {
    cEggPtr* mpBegin;
    cEggPtr* mpEnd;
    cEggPtr* mpCapacity;
    u32 mAllocator[2];
};
struct cVector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    u32 mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cAnimalVector {
    AutoRefCount<cSPCreatureAnimal>* mpBegin;
    AutoRefCount<cSPCreatureAnimal>* mpEnd;
    AutoRefCount<cSPCreatureAnimal>* mpCapacity;
    u32 mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
};

void __cdecl CopyEggs(cEggPtr* first, cEggPtr* last, cEggPtr* dest);   // 0x006782c0

struct cIntVector {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    u32 mAllocator[2];
    void PushN(int count, const int* val);   // 0x00c6e0c0
};
struct cByteVector {
    u8* mpBegin;
    u8* mpEnd;
    u8* mpCapacity;
    u32 mAllocator[2];
    void Insert(u8* end, int n, const u8* val);   // 0x005151b0
};

struct Vector2 {
    float x, y;
};

// RandomInRange<Vector2> — 0x004df2d0
float __cdecl RandomInRange(const Vector2* range);

// Species archetype blob (the per-species tuning record passed to UpdateFromArchetype).
struct cHerdArchetype {
    char pad0[0x2f0];
    float mTargetSizeMin;      // +0x2f0
    float mTargetSizeMax;      // +0x2f4
    float mBabyMin;            // +0x2f8
    float mBabyMax;            // +0x2fc
    char pad300[0x314 - 0x300];
    float mRespawnValue;       // +0x314
    Vector2 mSpeedRange;       // +0x318
    char pad320[0x338 - 0x320];
    float mSizeScale;          // +0x338
    char pad33c[0x344 - 0x33c];
    float mScaleValue;         // +0x344
    char pad348[0x35c - 0x348];
    float mCallTimerDefault;   // +0x35c
    float mBabyFrac;           // +0x360
    char pad364[0x36c - 0x364];
    int   mSizeTarget;         // +0x36c
    int   mMaxSize;            // +0x370
    float mScaleA;             // +0x374
    float mScaleB;             // +0x378
    char pad37c[0x38c - 0x37c];
    int   mPersonality;        // +0x38c
    char pad390[0x3d8 - 0x390];
    int   mRespawnSpecies;     // +0x3d8
    int   mMinCount;           // +0x3dc
    int   mMaxCount;           // +0x3e0
};

class cHerd {
public:
    virtual int AddRef();                      // +0x00
    virtual int Release();                     // +0x04
    char pad04[0x34 - 0x4];
    Vector3 mInitialPosition;                  // +0x34
    cAnimalVector mHerd;                       // +0x40
    cEggVector mEggs;                          // +0x54
    cVector3Vector mFeedingGrounds;            // +0x68
    char pad7c[0x80 - 0x7c];
    u32 mCurrentFeedingGrounds;                // +0x80
    u8  mbHasAvatarLink;                       // +0x84
    char pad85[0x88 - 0x85];
    u32 mArchetype;                            // +0x88
    char pad8c[0x90 - 0x8c];
    int   mArchetypeVariance;                  // +0x90
    float mMovementSpeed;                      // +0x94
    u8  mKey98[0xc];                           // +0x98 (species key passed to GetProfile)
    cSpeciesProfile* mpSpeciesProfile;         // +0xa4
    u8* mpKeyBegin;                            // +0xa8 (array of 0xc-stride species keys)
    u8* mpKeyEnd;                              // +0xac
    char pada8[0xf0 - 0xb0];
    u32 mGeneration;                           // +0xf0
    int mTargetHerdSize;                       // +0xf4
    int mEggGoal;                              // +0xf8
    char padf8[0x100 - 0xfc];
    u32 mEggStatus;                            // +0x100
    int mNumGuards;                            // +0x104
    float mCallTimer;                          // +0x108
    int mSizeTarget;                           // +0x10c
    u32 mMaxSize;                              // +0x110
    float mScaleMultiplierA;                   // +0x114
    float mScaleMultiplierB;                   // +0x118
    u32 mRespawnRate;                          // +0x11c
    char pad120[0x128 - 0x120];
    bool mbOkayToRespawn;                      // +0x128
    int mRespawnSpecies;                       // +0x12c (-1 = unset)
    char pad129[0x150 - 0x130];
    float mHerdSizeScale;                      // +0x150
    char pad154[0x158 - 0x154];
    float mScaleMultiplierC;                   // +0x158
    int mCreaturePersonality;                  // +0x15c
    cNest* mpNest;                             // +0x160
    AutoRefCount<cSPCreatureAnimal> mpHerdMom; // +0x164
    char pad168[0x190 - 0x168];
    bool mbExtinction;                         // +0x190
    char pad191;
    bool mbTransientHerd;                      // +0x192
    char pad193;
    AnimalRefOut mpEggLayer;                   // +0x194 (see AnimalRefOut)
    char pad198[0x1a0 - 0x198];
    cSPTimer mEggTimer;                        // +0x1a0
    char pad1a1[0x1c0 - 0x1a1];
    cSPTimer mRespawnTimer;                    // +0x1c0
    char pad1c1[0x1e0 - 0x1c1];
    cIntVector mEmotionVector;                 // +0x1e0 (eastl vector<int>)
    cByteVector mGenderVector;                 // +0x1f4 (eastl vector<u8>)

    void Update(int ms);
    const Vector3* GetPosition();              // 0x00c6acc0
    void FUN_00c6e4f0();                       // 0x00c6e4f0
    void UpdateFromArchetype(int pArchetype, char bForce);   // 0x00c6e200
    u8   vtableSlot40(u32 arg);                // 0x00b183f0
    u8   EnsureProfiles(u32 arg);              // 0x00c6e120
    void FUN_00c6ad60();                       // 0x00c6ad60
    void FUN_00c6b540();                       // 0x00c6b540
    __forceinline const Vector3* HomePos() { return mpNest ? mpNest->Spatial()->GetPosition() : &mInitialPosition; }
    float FUN_00c69f80();                      // 0x00c69f80 (baby fraction)
    void FUN_00c6cbf0();                       // 0x00c6cbf0
};

// shared RNG object
extern RandomLCG g_mathRandom;                 // 0x01601760
extern float g_minRadius;                      // 0x01470f1c
extern float g_maxRadius;                      // 0x0147b9f0
extern float g_adultFrac;                      // 0x01582f58
extern int   g_maxEggs;                        // 0x01582f34
extern int   gHerdRespawnDelay;                // 0x0150c8c4
extern int   gHerdSizeSmall;                   // 0x01582e58
extern int   gHerdSizeLarge;                   // 0x01582e5c
extern int   gAppNameTag;                      // 0x01654c05 (game-mode identity tag)
extern u8*   g_speciesKeyBegin;                // 0x015d96fc
extern u8*   g_speciesKeyEnd;                  // 0x015d9700

// @ 0x00c6d7c0
void cHerd::Update(int ms)
{
    cSPCreatureAnimal* guardCandidate;
    cSPCreatureAnimal* avatar = NounManager()->GetAvatar();
    mNumGuards = 0;
    mEggStatus = 0;
    guardCandidate = 0;
    int idx = 0;
    if (0 < mHerd.size()) {
        do {
            cSPCreatureAnimal* animal = mHerd.mpBegin[idx].mpObject;
            if (!animal->IsBaby()) {
                cSPCreatureAnimal* avatarTarget = 0;
                if (avatar)
                    avatarTarget = avatar->GetTargetAsCreature();
                bool bBusy;
                cBehaviorInfo* info = animal->mpBehaviorInfo;
                if (info && info->mBehaviorID == 0x2d852e6)
                    bBusy = true;
                else
                    bBusy = false;
                if (!animal->mTimer.IsRunning() && !TestBit(animal->mGeneralFlags, 9) &&
                    animal->GetTargetAsCreature() != avatar && animal != avatarTarget && !bBusy)
                    guardCandidate = animal;
                ++mNumGuards;
            } else if (mpHerdMom.mpObject == 0 && mArchetype != 0xc21f9669 && FUN_00c6af40(animal, this)) {
                mpHerdMom = animal;
                mpHerdMom.mpObject->mpBehaviorInfo->mFlags |= 0x400000;
            }
            ++idx;
        } while (idx < mHerd.size());
    }

    if (mNumGuards > 0) {
        float adultFrac = (mpSpeciesProfile == FUN_00401090()->GetAvatarProfile()) ? 0.0f : g_adultFrac;
        if (mArchetype != 0) {
            cEditorSpeciesManager::cArchetype* arch = FUN_00401090()->GetSpeciesArchetype(mArchetype, mGeneration);
            if (arch)
                adultFrac = arch->mFactor;
        }
        int wanted = CeilToInt((float)mTargetHerdSize * adultFrac);
        if (guardCandidate && mNumGuards > wanted && !TestBit(guardCandidate->mGeneralFlags, 9) &&
            !TestBit(guardCandidate->mGeneralFlags, 8))
            ((void (__thiscall*)(void*, int))(*(void***)guardCandidate)[0xe8 / 4])(guardCandidate, 1);

        if (!FUN_00d99500(mpHerdMom.mpObject) || !FUN_00c6af40(mpHerdMom.mpObject, this)) {
            const Vector3* home;
            cSPCreatureAnimal* mom = mpHerdMom.mpObject;
            if (mom && mom->GetFlag135() && mom->GetFlagB5E())
                home = mom->Spatial()->GetPosition();
            else
                home = HomePos();
            Vector3 homePos = *home;
            cSPCreatureAnimal* best = 0;
            float bestDist = 3.402823466e+38f;
            idx = 0;
            if (0 < mHerd.size()) {
                do {
                    cSPCreatureAnimal* c = FUN_00d99500(mHerd.mpBegin[idx].mpObject);
                    if (FUN_00c6af40(c, this) &&
                        (best == 0 || DistSq(c->Spatial()->GetPosition(), &homePos) < bestDist)) {
                        best = c;
                        bestDist = DistSq(c->Spatial()->GetPosition(), &homePos);
                    }
                    ++idx;
                } while (idx < mHerd.size());
            }
            mpHerdMom = best;
            if (mpHerdMom.mpObject)
                mpHerdMom.mpObject->mpBehaviorInfo->mFlags |= 0x400000;
        }
    } else {
        if (mpHerdMom.mpObject)
            mpHerdMom.mpObject->mpBehaviorInfo->mFlags &= 0xffbfffff;
        mpHerdMom.reset();
    }

    // egg layer validity
    cSPCreatureAnimal* layer = mpEggLayer.mpObject;
    if (!(FUN_00d99500(layer) && layer->IsBaby() && !layer->Spatial()->Slot58() &&
          layer->mpSpeciesProfile == mpSpeciesProfile && FUN_00d51660()->FUN_00a1ad10() != layer)) {
        if (mpEggLayer.mpObject) {
            mpEggLayer.mpObject->ResetEggLayer(0);
            mpEggLayer.reset();
        }
    }

    // respawn / egg laying
    if (mCreaturePersonality != 7 && mpSpeciesProfile != 0 && !mbTransientHerd && !mbExtinction) {
        int mode = FUN_00b3d4d0()->mMode;
        if (mode != 1 && mode != 2) {
            int x;
            {
                int y = g_maxEggs;
                x = mTargetHerdSize - mHerd.size();
                const int* p = (x < y) ? &x : &y;
                x = *p - (int)(mEggs.mpEnd - mEggs.mpBegin);
            }
            if (x > 0) {
                cSPTimer* t = &mEggTimer;
                if (t->IsRunning()) {
                    u64 el = t->GetElapsedTime();
                    if (el > (u64)mRespawnRate) {
                        t->Stop();
                        bool bDone = false;
                        if (mpEggLayer.mpObject && mpEggLayer.mpObject->GetValue2c70()) {
                            bDone = true;
                        } else {
                            AutoRefCount<cSPCreatureAnimal>* it = mHerd.mpBegin;
                            AutoRefCount<cSPCreatureAnimal>* end = mHerd.mpEnd;
                            float minD = 3.402823466e+38f;
                            for (; it != end; ++it) {
                                cSPCreatureAnimal* c = it->mpObject;
                                if (FUN_00c699a0(c, this)) {
                                    const Vector3* hp = HomePos();
                                    float d = DistSq(c->Spatial()->GetPosition(), hp);
                                    if (minD > d) {
                                        mpEggLayer = c;
                                        minD = d;
                                    }
                                }
                            }
                            if (mpEggLayer.mpObject) {
                                bDone = true;
                                mpEggLayer.mpObject->ResetEggLayer(x);
                            }
                        }
                        if (mbOkayToRespawn && !bDone) {
                            Vector3 tmp;
                            if (avatar && mpSpeciesProfile == avatar->mpSpeciesProfile) {
                                SpawnHerdAnimals(
                                    PlanetModel()->MakeRandomWorldPosition(&tmp, GetPosition(), g_minRadius, g_maxRadius),
                                    mpSpeciesProfile, x, FUN_00c69f80(), this);
                            } else {
                                int flag = (idx > 0 && g_mathRandom.RandomDoubleUniform() < (double)g_adultFrac) ? 0 : 1;
                                FUN_00c099e0(
                                    PlanetModel()->MakeRandomWorldPosition(&tmp, GetPosition(), g_minRadius, g_maxRadius),
                                    mpSpeciesProfile, flag, this, 0, 1);
                            }
                        }
                        goto afterSpawn;
                    }
                }
                if (!t->IsRunning())
                    t->Restart();
            }
        }
    }
afterSpawn:

    // eggs
    {
        cEggPtr* it = mEggs.mpBegin;
        if (it != mEggs.mpEnd) {
            cEggPtr* next = it + 1;
            do {
                cEggPtr egg(*it);
                cSPTimer* tm = &egg.mpObject->mTimer;
                bool bRemove = false;
                if (tm->IsRunning()) {
                    u64 el = tm->GetElapsedTime();
                    if (el > 0x2710)
                        bRemove = true;
                }
                if (!bRemove && mbExtinction && !egg.mpObject->Spatial()->Slot48())
                    bRemove = true;
                if (bRemove) {
                    NounManager()->RemoveNoun(egg.mpObject);
                    cEggPtr* e = mEggs.mpEnd;
                    if (next < e)
                        CopyEggs(next, e, it);
                    --mEggs.mpEnd;
                    mEggs.mpEnd->~cEggPtr();
                } else {
                    egg.mpObject->Update(ms);
                    ++it;
                    ++next;
                }
            } while (it != mEggs.mpEnd);
        }
    }

    if (mpNest)
        mpNest->mFlags |= 0x2000;
    FUN_00c6cbf0();

    u32 cur = mCurrentFeedingGrounds;
    if (cur != 0xffffffff && cur >= (u32)mFeedingGrounds.size())
        mCurrentFeedingGrounds = 0;

    cSPTimer* rt = &mRespawnTimer;
    if (rt->IsRunning()) {
        u64 el = rt->GetElapsedTime();
        if (el <= 0x12c)
            return;
    }
    rt->Restart();
    if (mFeedingGrounds.mpBegin != mFeedingGrounds.mpEnd)
        mCurrentFeedingGrounds = g_mathRandom.RandomUint32Uniform((u32)mFeedingGrounds.size());
}

// @ 0x00c6e200
void cHerd::UpdateFromArchetype(int pArchetype, char bForce)
{
    if (pArchetype == 0)
        return;
    cHerdArchetype* arch = (cHerdArchetype*)pArchetype;

    if (bForce || mTargetHerdSize == 0) {
        float roll = RandomFloatRange(arch->mTargetSizeMin, arch->mTargetSizeMax);
        mTargetHerdSize = FloatToIntSSE(roll);
    }
    if (bForce || mHerdSizeScale == 0.0f)
        mHerdSizeScale = arch->mSizeScale;
    if (bForce || mScaleMultiplierC == 0.0f)
        mScaleMultiplierC = arch->mScaleValue;
    if (bForce || mCallTimer == 0.0f)
        mCallTimer = arch->mCallTimerDefault;

    mMovementSpeed = RandomInRange(&arch->mSpeedRange);

    mRespawnSpecies = arch->mRespawnSpecies;
    if (mRespawnSpecies == -1)
        mRespawnSpecies = g_mathRandom.RandomUint32Uniform((u32)((g_speciesKeyEnd - g_speciesKeyBegin) / 0xc));

    mSizeTarget = arch->mSizeTarget;
    mMaxSize = arch->mMaxSize;
    mScaleMultiplierA = arch->mScaleA;
    mScaleMultiplierB = arch->mScaleB;

    if (bForce || mCallTimer > 0.0f) {
        const float* pa = &mCallTimer;
        if (mScaleMultiplierA <= mCallTimer)
            pa = &mScaleMultiplierA;
        mScaleMultiplierA = *pa;
        const float* pb = &mCallTimer;
        if (mScaleMultiplierB <= mCallTimer)
            pb = &mScaleMultiplierB;
        mScaleMultiplierB = *pb;
    }

    if (bForce || mCreaturePersonality == 0) {
        mCreaturePersonality = arch->mPersonality;
        FUN_00c6ad60();
    }

    mArchetypeVariance = (int)g_mathRandom.RandomUint32Uniform((arch->mMaxCount - arch->mMinCount) >> 2);
    mEggStatus = (u32)(int)((float)mTargetHerdSize * arch->mBabyFrac);

    float babyRoll = RandomFloatRange(arch->mBabyMin, arch->mBabyMax);
    int lo = FloatToIntSSE(babyRoll);
    int hi = mTargetHerdSize - 1;
    mEggGoal = lo;
    int floorVal = (hi < 0) ? 0 : hi;
    if (floorVal < mEggGoal)
        mEggGoal = floorVal;

    float respawnRoll = arch->mRespawnValue * 0.5f;
    mRespawnRate = (u32)FloatToIntSSE(respawnRoll);

    {
        u32 count = (u32)mSizeTarget;
        u8* begin = mGenderVector.mpBegin;
        u8* end = mGenderVector.mpEnd;
        if (count > (u32)(end - begin)) {
            u8 zero = 0;
            mGenderVector.Insert(end, (int)((end - begin) + count), &zero);
        } else {
            memcpy(begin + count, end, 0);
            mGenderVector.mpEnd = begin + count;
        }
    }

    int one = 1;
    mEmotionVector.PushN(mSizeTarget, &one);
}

// @ 0x00c6e4f0
void cHerd::FUN_00c6e4f0()
{
    if (mTargetHerdSize == 0) {
        bool bDo = false;
        cSpeciesProfile* sp = mpSpeciesProfile;
        if (sp != 0) {
            if (sp != FUN_00401090()->GetAvatarProfile())
                bDo = true;
        }
        if (GetCurrentGameMode() == (void*)0x01654c05 && IsWorldLayoutFlagSet(2)) {
            if (bDo && ResourceKeyNE((char*)sp + 0x504, FUN_00c30f90()))
                mTargetHerdSize = gHerdRespawnDelay;
        } else if (bDo) {
            mTargetHerdSize = gHerdRespawnDelay;
        }
    }

    if (mHerdSizeScale == 0.0f)
        mHerdSizeScale = 1.0f;
    if (mScaleMultiplierC == 0.0f)
        mScaleMultiplierC = 1.0f;

    if (mRespawnSpecies == -1)
        mRespawnSpecies = g_mathRandom.RandomUint32Uniform((u32)((g_speciesKeyEnd - g_speciesKeyBegin) / 0xc));

    if (mSizeTarget > 0 && mMaxSize == 0)
        mMaxSize = 1;

    {
        u32 count = (u32)mSizeTarget;
        u8* begin = mGenderVector.mpBegin;
        u8* end = mGenderVector.mpEnd;
        if (count > (u32)(end - begin)) {
            u8 zero = 0;
            mGenderVector.Insert(end, (int)((end - begin) + count), &zero);
        } else {
            memcpy(begin + count, end, 0);
            mGenderVector.mpEnd = begin + count;
        }
    }

    int one = 1;
    mEmotionVector.PushN(mSizeTarget, &one);
    mEggTimer.Init();
    mRespawnTimer.Init();

    if (mbHasAvatarLink && NounManager()->GetAvatar() == 0) {
        const Vector3* pos = mpNest ? mpNest->Spatial()->GetPosition() : (const Vector3*)((char*)this + 0x34);
        FUN_00c099e0(pos, mpSpeciesProfile, 1, this, 1, 0);
        FUN_00c6b540();
    }

    if (mRespawnRate == 0 && mCreaturePersonality != 2) {
        mRespawnRate = (mpSpeciesProfile == FUN_00401090()->GetAvatarProfile()) ? gHerdSizeSmall : gHerdSizeLarge;
    }
}

// @ 0x00c6e120
u8 cHerd::EnsureProfiles(u32 arg)
{
    u8 ret = 1;
    if (mpSpeciesProfile == 0) {
        ret = vtableSlot40(arg);
        cSpeciesProfile* profile = FUN_00401090()->GetProfile(mKey98);
        mpSpeciesProfile = profile;
        ret = (u8)(ret & (profile != 0));
    }

    int n = (int)((mpKeyEnd - mpKeyBegin) / 0xc);
    for (int i = 0; i < n; ++i)
        FUN_00401090()->GetProfile(mpKeyBegin + i * 0xc);

    u32 count = (u32)mSizeTarget;
    u8* begin = mGenderVector.mpBegin;
    u8* end = mGenderVector.mpEnd;
    if (count > (u32)(end - begin)) {
        u8 zero = 0;
        mGenderVector.Insert(end, (int)((end - begin) + count), &zero);
    } else {
        memcpy(begin + count, end, 0);
        mGenderVector.mpEnd = begin + count;
    }
    return ret;
}

} // namespace SP
