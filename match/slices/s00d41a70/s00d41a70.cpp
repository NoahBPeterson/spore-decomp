// `anonymous namespace'::SetGlobalAudioProperties(cSPCreatureBase*), 0x00d41a70
//
// ~2.8 KB per-frame helper of the creature game (/O2 /arch:SSE /fp:fast, no EH frame). It measures the
// squared distance from the avatar to the nearest creature of two kinds (an interaction list filtered
// by a predicate), handles the "mate call" sound bookkeeping, measures the nearest object of a
// second filtered list, and then pushes ~19 global audio parameters through the audio system
// (BeginMessage(0x3cdd1a9) / SetParam(0x34753a7, name) / SetParamFloat(0x34753aa, value) / Send).
//
//   void __cdecl SetGlobalAudioProperties(cSPCreatureBase* avatar)

#include "types.h"

#include <math.h>

// memmove is the statically linked CRT one here (0x011e0744), not the msvcr90 import.
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);

struct Vector3 { float x, y, z; };
inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

namespace SP {

// --- audio system ----------------------------------------------------------------------------
class IAudioSystem {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34();
    /* 38h */ virtual void BeginMessage(uint32_t msg);
    /* 3ch */ virtual void SetParamFloat(uint32_t key, float value);
    /* 40h */ virtual void SetParam(uint32_t key, uint32_t value);
    virtual void _v44(); virtual void _v48(); virtual void _v4c(); virtual void _v50();
    virtual void _v54();
    /* 58h */ virtual void SendMessage();
};
}  // namespace SP
namespace EA { namespace Audio { SP::IAudioSystem* GetSystemAT(); } }   // 0x00a206f0

// --- creatures -------------------------------------------------------------------------------
class cSpatialObject {   // subobject at +0xc0 of a creature
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    /* 2ch */ virtual const Vector3& GetPosition();
};

struct cIdleAnimInfo { uint32_t pad00[3]; uint32_t mID; };            // +0x0c
struct cAnimState    { uint32_t pad00[3]; int mState; };              // +0x0c

struct cAnimOwner {   // object at +8 of the avatar's +0xb4c
    cIdleAnimInfo* GetIdle(int kind, int flags);                      // 0x00bc96a0 (ICF name: PlayIdleAnimation)
};
struct cAvatarAnim {   // the avatar's +0xb4c
    uint32_t pad00[2];
    cAnimOwner mOwner;                                                // +0x08
    uint32_t pad0c[(0x1d8 - 0xc) / 4];
    uint32_t mMode;                                                   // +0x1d8
};

struct cSpecies { float GetScale(); };                                 // 0x004d46b0 (SpeciesDB::GetScale)
struct cSpeciesData { uint32_t pad[0x598 / 4]; float mValue598; };     // the avatar's +0xb20

struct cTimer5a8 { float Get(); };                                     // 0x00bfc490

class cCreatureMain {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64(); virtual void _v68(); virtual void _v6c();
    virtual void _v70(); virtual void _v74(); virtual void _v78(); virtual void _v7c();
    virtual void _v80(); virtual void _v84(); virtual void _v88(); virtual void _v8c();
    virtual void _v90(); virtual void _v94(); virtual void _v98(); virtual void _v9c();
    virtual void _va0(); virtual void _va4(); virtual void _va8(); virtual void _vac();
    virtual void _vb0();
    /* b4h */ virtual cAnimState* GetAnimState(uint32_t id);
    virtual void _vb8(); virtual void _vbc();
    virtual void _vc0(); virtual void _vc4(); virtual void _vc8(); virtual void _vcc();
    virtual void _vd0(); virtual void _vd4();
    /* d8h */ virtual int GetValueD8();

    uint32_t padMain[(0xc0 - 4) / 4];
};

class cCreature : public cCreatureMain, public cSpatialObject {   // cSpatialObject at +0xc0
public:
    cTimer5a8* Timer() { return (cTimer5a8*)((char*)this + 0x5a8); }

    struct cCreatureInfo* GetInfo();                                   // 0x00c04590
    bool IsKindB(cCreature* other);                                    // 0x00c0b8a0
    int  GetValueB750();                                               // 0x00c0b750
    float GetValueB9c0();                                              // 0x00c0b9c0
    int  GetValue2c70();                                               // 0x00c02c70
    bool GetFlagB770();                                                // 0x00c0b770
    bool GetFlagC130();                                                // 0x00c0c130
    void StartIndependentSound(const char* name, const Vector3* pos, void* handles);  // 0x00c1db40

    uint32_t padA[(0xb20 - 0xc4) / 4];
    cSpeciesData* mpSpecies;                                           // +0xb20
    uint32_t padB24[(0xb4c - 0xb24) / 4];
    cAvatarAnim* mpAnim;                                               // +0xb4c
    uint32_t padB50[2];
    uint32_t mFlags;                                                   // +0xb58
    uint32_t padB5c[(0x1124 - 0xb5c) / 4];
    struct cEntry** mpNearBegin;                                       // +0x1124
    struct cEntry** mpNearEnd;                                         // +0x1128
    uint32_t pad112c[(0x140c - 0x112c) / 4];
    struct cEntry** mpObjBegin;                                        // +0x140c
    struct cEntry** mpObjEnd;                                          // +0x1410
};
struct cCreatureInfo { uint32_t pad[0x15c / 4]; int mKind; };         // +0x15c

class cObject {   // what a cEntry of the object list points to
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    /* 0ch */ virtual struct cObjectTarget* Cast(uint32_t typeID);
};
class cObjectTargetMain {
public:
    virtual void _v00();
    uint32_t padMain[(0x34 - 4) / 4];
};
struct cObjectTarget : public cObjectTargetMain, public cSpatialObject {   // cSpatialObject at +0x34
    bool IsAudible();                                                  // 0x00c6aa50
};

struct cEntry { uint32_t pad00[2]; void* mpObject; };                  // +0x08

cCreature* CreatureCast(void* p);                                      // 0x00d99500 (cdecl)

// --- filtered iterators over the two entry lists ---------------------------------------------
struct NearPred { bool operator()(cEntry* e) const; };                 // 0x00c02600
struct ObjPred  { bool operator()(cEntry* e) const; };                 // 0x00c03520

struct NearIterator {
    cEntry** mpCur;
    cEntry** mpEnd;
    NearPred mPred;
    NearIterator& Advance();                                           // 0x00b3d850 (operator++)
    NearIterator(cEntry** b, cEntry** e) : mpCur(b), mpEnd(e)
    {
        if (mpCur != mpEnd && !mPred(*mpCur))
            Advance();
    }
    void operator++()
    {
        do { ++mpCur; } while (mpCur != mpEnd && !mPred(*mpCur));
    }
    cEntry* operator*() const { return *mpCur; }
};

struct ObjIterator {
    cEntry** mpCur;
    cEntry** mpEnd;
    ObjPred mPred;
    ObjIterator(cEntry** b, cEntry** e) : mpCur(b), mpEnd(e)
    {
        if (mpCur != mpEnd && !mPred(*mpCur))
            ++*this;
    }
    void operator++()
    {
        do { ++mpCur; } while (mpCur != mpEnd && !mPred(*mpCur));
    }
};

// --- game -------------------------------------------------------------------------------------
struct cHerd { void* GetLeader(); };                                    // 0x00c6acc0
cHerd* GetDesiredAvatarHerd(int);                                       // 0x00d40b40
double GetTime();                                                       // 0x00c0e480

class cCreatureModeStrategy {
public:
    uint32_t pad00[0x24 / 4];
    uint32_t mCount24;                                                  // +0x24
    Vector3 CalcVisiblePosition(void* target, float distance);          // 0x00d3b0c0
    static cCreatureModeStrategy* spInstance;                           // 0x0169e294
};

struct UIntVector {   // eastl::vector<uint32_t>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void erase(uint32_t* first, uint32_t* last)
    {
        memmove(first, last, (char*)mpEnd - (char*)last);
        mpEnd = mpEnd - (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
};

using namespace SP;

extern UIntVector g_MatecallSounds;      // 0x0169e2a8
extern double     g_MatecallTime;        // 0x0169e2c0
extern int        g_MatecallState;       // 0x0169e2c8
struct AudioTuning { float mScale; float pad04[2]; float mLimit0c; float mLimit10; };
extern AudioTuning g_AudioTuning;        // 0x01687a00

static __forceinline void SetGlobalParam(uint32_t name, float value)
{
    IAudioSystem* audio = EA::Audio::GetSystemAT();
    if (audio) {
        audio->BeginMessage(0x3cdd1a9);
        audio->SetParam(0x34753a7, name);
        audio->SetParamFloat(0x34753aa, value);
        audio->SendMessage();
    }
}

template <class A, class B>
static __forceinline float DistanceSquared(A* from, B* to)
{
    const Vector3& a = from->GetPosition();
    const Vector3& b = to->GetPosition();
    Vector3 d = b - a;
    return d.z * d.z + d.y * d.y + d.x * d.x;
}

namespace {

// @ 0x00d41a70
void SetGlobalAudioProperties(cCreature* avatar)
{
    cCreatureModeStrategy* strategy = cCreatureModeStrategy::spInstance;
    if (!strategy)
        return;

    float nearestB = 3.402823466e+38F;
    float nearestA = 3.402823466e+38F;
    {   // (the block scopes give the original's frame: both iterators and `pos` share one slot,
        //  and nothing address-taken is live at the end, so the last SendMessage is a tail call)
    for (NearIterator it(avatar->mpNearBegin, avatar->mpNearEnd); it.mpCur != it.mpEnd; ++it) {
        cCreature* creature = CreatureCast((*it)->mpObject);
        if (creature) {
            if (creature->GetInfo()->mKind == 1) {
                float d = DistanceSquared(creature, avatar);
                if (d < nearestA)
                    nearestA = d;
            }
            if (avatar->IsKindB(creature)) {
                float d = DistanceSquared(creature, avatar);
                if (d < nearestB)
                    nearestB = d;
            }
        }
    }
    }

    bool flag6 = (avatar->mFlags >> 6) & 1;
    bool idleState = false;
    if (avatar->mpAnim->mMode == 0xd2f1ed12) {
        cIdleAnimInfo* idle = avatar->mpAnim->mOwner.GetIdle(0x20, 0);
        if (idle)
            idleState = avatar->GetAnimState(idle->mID)->mState == 1;
    }
    bool zero598 = true;
    if (avatar->mpSpecies->mValue598 != 0.0f)
        zero598 = false;
    float valueB750 = (float)avatar->GetValueB750() * 0.33333334f;
    void* leader = GetDesiredAvatarHerd(0)->GetLeader();

    cAvatarAnim* anim = avatar->mpAnim;
    if (anim) {
        if (anim->mMode == 0x2d852ed) {
            g_MatecallTime = GetTime();
        } else if (g_MatecallSounds.mpBegin != g_MatecallSounds.mpEnd
                   && (float)(GetTime() - g_MatecallTime) > 5.0f) {
            for (uint32_t i = 0, n = g_MatecallSounds.size(); i < n; ++i) {
                uint32_t sound = g_MatecallSounds.mpBegin[i];
                IAudioSystem* audio = EA::Audio::GetSystemAT();
                if (audio) {
                    audio->BeginMessage(0x347536b);
                    audio->SetParam(0x3475385, sound);
                    audio->SetParam(0x34753a0, 0);
                    audio->SendMessage();
                }
            }
            g_MatecallSounds.clear();
            switch (g_MatecallState) {
            case 1: {
                Vector3 pos = cCreatureModeStrategy::spInstance->CalcVisiblePosition(leader, 30.0f);
                avatar->StartIndependentSound("soc_matecall_2_stop", &pos, &g_MatecallSounds);
                g_MatecallTime = GetTime();
                g_MatecallState = 2;
                break;
            }
            case 2:
                g_MatecallState = 0;
                break;
            }
        }
    }

    float nearestObj = 3.402823466e+38F;
    {
    for (ObjIterator it(avatar->mpObjBegin, avatar->mpObjEnd); it.mpCur != it.mpEnd; ++it) {
        cObject* object = (cObject*)(*it.mpCur)->mpObject;
        if (object) {
            cObjectTarget* target = object->Cast(0x1b92b27);
            if (target && target->IsAudible()) {
                float d = DistanceSquared(target, avatar);
                if (d < nearestObj)
                    nearestObj = d;
            }
        }
    }
    }

    float timer = avatar->Timer()->Get();
    SetGlobalParam(0x1a7b91f7, timer);
    SetGlobalParam(0x5f301f0c, timer * g_AudioTuning.mScale < g_AudioTuning.mLimit0c ? 1.0f : 0.0f);
    SetGlobalParam(0x81d19469, timer * g_AudioTuning.mScale < g_AudioTuning.mLimit10 ? 1.0f : 0.0f);
    SetGlobalParam(0x304f73f0, avatar->GetValueB9c0() * 0.01f);
    SetGlobalParam(0xaba89849, sqrtf(nearestB));
    SetGlobalParam(0xe356f907, sqrtf(nearestA));
    SetGlobalParam(0xee7fb4b4, (float)avatar->GetValueD8());
    SetGlobalParam(0x75a853ba, sqrtf(nearestObj));
    SetGlobalParam(0x6ff2604a, (float)(avatar->GetValue2c70() > 0));
    SetGlobalParam(0xc6182545, (float)!avatar->GetFlagB770());
    SetGlobalParam(0xe1a7e909, (float)avatar->GetFlagC130());
    SetGlobalParam(0x8208c446, (float)strategy->mCount24);
    SetGlobalParam(0x1ca50e46, (float)idleState);
    SetGlobalParam(0x4c6d557b, ((cSpecies*)avatar->mpSpecies)->GetScale() * 0.1f);
    SetGlobalParam(0x8ac976a3, (float)flag6);
    SetGlobalParam(0x6e44f8c0, (float)zero598);
    SetGlobalParam(0x8b24520a, valueB750);
}

}  // namespace

// Taking the address keeps the internal-linkage function emitted out of line (its callers live in
// this TU in the original; here there are none).
void (*g_pSetGlobalAudioProperties)(cCreature*) = &SetGlobalAudioProperties;
