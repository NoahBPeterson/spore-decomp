// Slice s00c6d7c0: SP::cHerd::Update (0x00c6d7c0, 2290 bytes, thiscall, 1 stack arg).
// Per-frame herd upkeep: counts the adult guards, picks the "herd mom" creature (personality),
// keeps the egg layer valid, respawns animals while under the target size, updates/removes eggs,
// then ticks the feeding-ground selection.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), as in sibling s00c09fa0.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>

#pragma warning(disable: 4100)

typedef unsigned int u32;
typedef unsigned long long u64;

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

struct cSPTimer {
    bool IsRunning();         // 0x00feba90
    u64  GetElapsedTime();    // 0x00bc3190
    void Stop();              // 0x00bc3110
    void Restart();           // 0x00bc3130
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

struct cEgg {
    virtual int AddRef();
    virtual int Release();
    char pad04[0x34 - 0x4];
    char mSpatialStorage[4];   // +0x34
    char pad38[0x1f8 - 0x38];
    cSPTimer mTimer;           // +0x1f8
    void Update(int ms);       // 0x00c6b040
    ISpatial* Spatial() { return (ISpatial*)((char*)this + 0x34); }
};

struct cNest {
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

struct cGameNounManager {
    cSPCreatureAnimal* GetAvatar();         // 0x00b1fdb0
    void RemoveNoun(cEgg* egg);             // 0x00b225d0
};

struct cEditorSpeciesManager {
    cSpeciesProfile* GetAvatarProfile();    // 0x004df420
    struct cArchetype { char pad[0x364]; float mFactor; };
    cArchetype* GetSpeciesArchetype(u32 key, u32 generation);   // 0x004e0050
};

struct cAvatarHolder {
    cSPCreatureAnimal* FUN_00a1ad10();      // 0x00a1ad10
};

struct cGameMode { char pad[0x2c]; int mMode; };

struct cPlanetModel {
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
    char pad84[0x88 - 0x84];
    u32 mArchetype;                            // +0x88
    char pad8c[0xa4 - 0x8c];
    cSpeciesProfile* mpSpeciesProfile;         // +0xa4
    char pada8[0xf0 - 0xa8];
    u32 mGeneration;                           // +0xf0
    int mTargetHerdSize;                       // +0xf4
    char padf8[0x100 - 0xf8];
    u32 mEggStatus;                            // +0x100
    int mNumGuards;                            // +0x104
    char pad108[0x11c - 0x108];
    u32 mRespawnRate;                          // +0x11c
    char pad120[0x128 - 0x120];
    bool mbOkayToRespawn;                      // +0x128
    char pad129[0x15c - 0x129];
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

    void Update(int ms);
    const Vector3* GetPosition();              // 0x00c6acc0
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

} // namespace SP
