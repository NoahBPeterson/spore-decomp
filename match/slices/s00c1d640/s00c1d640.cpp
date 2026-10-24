// Slice s00c1d640 (gold7): creature body-part sound playback.  The batch targets
// are 0x00C1D640 (unnamed body-part sound + live-handle map) and 0x00C1DB40
// (SP::cSPCreatureBase::StartIndependentSound).  The older 0x00C1DE20
// ability-selection reconstruction below was already present in this slice
// directory and is preserved verbatim; its row and symbol stay in place.
// Optimized module: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
#include "types.h"
#include <math.h>
#include <string.h>

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Stubs (offsets / vtable slots recovered from 0x00c1de20)
// ---------------------------------------------------------------------------
void operator_delete__(void* p);                                          // 0x00f47380

// SP::SimpleVector<unsigned int> (begin, end, capacity, allocator)
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

// 88-bit set of ability ids
struct AbilityMask {
    uint w[3];
    bool test(uint id) const
    {
        if (id >= 0x58)
            return false;
        return (w[id >> 5] & (1u << (id & 0x1f))) != 0;
    }
};

// Ability tuning record (TuningObj)
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

// Sub-object (secondary base) at +0xc0 of a creature
struct Body {
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
    Body mBody;                                                         // +0xc0 (secondary base with vptr)
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
extern float gChargeScale;                                              // 0x01572058 (10.0)
extern float gBoundScale;                                               // 0x01572054 (1.5)

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
            Body* tb = &tc->mBody;
            Body* mb = &mBody;
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

#define OFFCHK(T, m, o) typedef char offchk_##T##_##m[((unsigned)(unsigned long)&((T*)0)->m == (o)) ? 1 : -1]
OFFCHK(Ability, id, 0x8); OFFCHK(Ability, mKind, 0xc); OFFCHK(Ability, f3c, 0x3c); OFFCHK(Ability, f84, 0x84);
OFFCHK(Ability, f9c, 0x9c); OFFCHK(Ability, fa8, 0xa8); OFFCHK(Ability, ff4, 0xf4); OFFCHK(Ability, f104, 0x104);
OFFCHK(Ability, mbBusy, 0x114); OFFCHK(Ability, m120, 0x120);
OFFCHK(Creature, mBody, 0xc0); OFFCHK(Creature, mFlags, 0xb58); OFFCHK(Creature, mbNoBonus, 0xbb0);
OFFCHK(Creature, mpEntries, 0xc28); OFFCHK(Creature, mEnergy, 0xe58); OFFCHK(Creature, mpTypeHolder, 0xe7c);
OFFCHK(Creature, mActiveAbility, 0xe8c); OFFCHK(Creature, mCooldownCount, 0x1670);

// ===========================================================================
// Slice targets 0x00C1D640 and 0x00C1DB40.
//
// The 0x00C1DE20 body above is an older reconstruction that was already present
// in this slice directory; it is kept verbatim so its row in nonmatching.txt and
// its symbols/slices entry remain valid.  The two functions below are the ones
// the gold7 batch actually assigns to s00c1d640: they play body-part sounds for
// a creature ("vcode_*"/"vsoc_*" names) and maintain a per-creature map of the
// live sound handles.
// ===========================================================================

struct Vec3 {
    float x, y, z;
};

struct Quat {
    float x, y, z, w;
};

// Per-part data object (cCreaturePartData).  Only the audio-relevant fields are
// modelled: the three radii used to compute the emitter sphere and the sound
// emitter id at +0x428.
struct PartData {
    char  mPad000[0x138];
    float mRadiusX;                 // +0x138
    float mRadiusY;                 // +0x13c
    float mRadiusZ;                 // +0x140
    char  mPad144[0x428 - 0x144];
    void* mpSound;                  // +0x428 (0 when the part is silent)
};

// One entry of the model's 0x2bc-byte body-part array.
struct BodyPart {
    PartData* mpData;               // +0x00
    char      mPad04[0x10 - 0x04];
    Vec3      mOffset;              // +0x10 (part-local emitter offset)
    char      mPad1c[0x2bc - 0x1c];
};

// Model attached to the animated creature (+0xB54 -> +0x17C).
struct CreatureModel {
    char  mPad000[0x18];
    Vec3  mPosition;                // +0x18
    char  mPad024[0x3c - 0x24];
    Quat  mRotation;                // +0x3c
    char  mPad04c[0x70 - 0x4c];
    float mScale;                   // +0x70
    char  mPad074[0x2e4 - 0x74];
    BodyPart* mpParts;              // +0x2e4
};

struct AnimCreature {
    char          mPad000[0x17c];
    CreatureModel* mpModel;         // +0x17c
};

// Nodes of the live-sound map (eastl::rbtree node base + pair payload).
struct SoundNode {
    SoundNode* mpLeft;              // +0x00
    SoundNode* mpRight;             // +0x04
    SoundNode* mpParent;            // +0x08
    uint       mColor;              // +0x0c
    uint       mKey;                // +0x10 (creature sound id)
    uint       mHandle;             // +0x14 (audio-system handle)
    int        mPart;               // +0x18 (body-part index)
};

struct SoundMapHead {
    SoundNode* mpLeft;              // +0x00
    SoundNode* mpRight;             // +0x04
    SoundNode* mpParent;            // +0x08 (root)
    uint       mColor;              // +0x0c
};

// SPVector<unsigned int> (begin, end, capacity).  The slice's first function
// also uses it for the per-creature list of sound ids at +0xe24.
struct UIntVec {
    uint* mpBegin;                  // +0x00
    uint* mpEnd;                    // +0x04
    uint* mpCapacity;               // +0x08
    void DoInsertValue(uint* position, const uint& value);   // 0x004558A0
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
};

// EA::Audio::GetSystemAT() result.  Only the slots used by these two functions
// are named; the other slots are padding.
class AudioSystem {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual uint s20();             // +0x20
    virtual uint s24();             // +0x24
    virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34();
    virtual void s38(uint key);                         // +0x38
    virtual void s3c(uint key, float value);           // +0x3c
    virtual void s40(uint key, uint value);            // +0x40
    virtual void s44(uint key, const char* name, uint arg); // +0x44
    virtual void s48(); virtual void s4c(); virtual void s50(); virtual void s54();
    virtual void s58();             // +0x58 (commit/play)
};

AudioSystem* GetSystemAT();                                     // 0x00A206F0 EA::Audio::GetSystemAT
uint QueryCreatureBodyParts(void* creature, int mode, int* parts, int maxParts); // 0x00C17420
void* SimAlloc(unsigned int size, const char* name, int a, int b,
               const char* file, int line);                     // 0x00F473A0 operator new
void RBTreeInsert(void* node, void* parent, void* head, int side); // 0x009216A0 eastl::RBTreeInsert
bool __fastcall Flag388(void* self);                            // 0x00C0C0E0 (thiscall; ecx = self)

extern float g_168d910;                                         // 0x0168D910
extern float g_168d914;                                         // 0x0168D914
extern float g_168d918;                                         // 0x0168D918

#define VSLOT(n) virtual void vs##n()
class cSPCreatureBase {
public:
    // Slots 0x00..0xD4 are not used here; they only preserve the primary
    // vtable offset of the sound-flag query at +0xD8.
    VSLOT(00); VSLOT(04); VSLOT(08); VSLOT(0c); VSLOT(10); VSLOT(14);
    VSLOT(18); VSLOT(1c); VSLOT(20); VSLOT(24); VSLOT(28); VSLOT(2c);
    VSLOT(30); VSLOT(34); VSLOT(38); VSLOT(3c); VSLOT(40); VSLOT(44);
    VSLOT(48); VSLOT(4c); VSLOT(50); VSLOT(54); VSLOT(58); VSLOT(5c);
    VSLOT(60); VSLOT(64); VSLOT(68); VSLOT(6c); VSLOT(70); VSLOT(74);
    VSLOT(78); VSLOT(7c); VSLOT(80); VSLOT(84); VSLOT(88); VSLOT(8c);
    VSLOT(90); VSLOT(94); VSLOT(98); VSLOT(9c); VSLOT(a0); VSLOT(a4);
    VSLOT(a8); VSLOT(ac); VSLOT(b0); VSLOT(b4); VSLOT(b8); VSLOT(bc);
    VSLOT(c0); VSLOT(c4); VSLOT(c8); VSLOT(cc); VSLOT(d0); VSLOT(d4);
    virtual uint vsD8();            // +0xD8

    char       mPad004[0xb34 - 0x04];
    int        mFieldB34;           // +0xb34
    char       mPadB38[0xb54 - 0xb38];
    AnimCreature* mpAnim;           // +0xb54
    uint       mFlagsB58;           // +0xb58
    char       mPadB5c[0xe0c - 0xb5c];
    SoundMapHead mSoundMap;         // +0xe0c
    uint       mSoundMapCount;      // +0xe1c
    char       mPadE20[0xe24 - 0xe20];
    UIntVec    mSoundIds;           // +0xe24
    char       mPadE30[0xf94 - 0xe30];
    uint       mSoundCounter;       // +0xf94

    uint FUN_00c1d640(const char* name, int mode, uint id);
    bool StartIndependentSound(const char* name, const Vec3* pos, UIntVec* out);
    uint CallVd8() { return vsD8(); }
    bool Flag388() { return ::Flag388(this); }
};

// Rotate v by quaternion q (right-handed, same expansion as the original
// inlined SSE code) and return the model-space offset.
static inline Vec3 RotateOffset(const Quat& q, const Vec3& v)
{
    float xx = q.x * q.x;
    float yy = q.y * q.y;
    float zz = q.z * q.z;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float yz = q.y * q.z;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    float wz = q.w * q.z;
    Vec3 r;
    r.x = (1.0f - 2.0f * (yy + zz)) * v.x
        + 2.0f * (xy - wz) * v.y
        + 2.0f * (xz + wy) * v.z;
    r.y = 2.0f * (xy + wz) * v.x
        + (1.0f - 2.0f * (xx + zz)) * v.y
        + 2.0f * (yz - wx) * v.z;
    r.z = 2.0f * (xz - wy) * v.x
        + 2.0f * (yz + wx) * v.y
        + (1.0f - 2.0f * (xx + yy)) * v.z;
    return r;
}

// @ 0x00c1d640
uint cSPCreatureBase::FUN_00c1d640(const char* name, int mode, uint id)
{
    AudioSystem* audio = GetSystemAT();
    if (!audio)
        return id;

    int parts[255];
    uint count = QueryCreatureBodyParts(this, mode, parts, 0xff);
    if (count == 0 || id != 0) {
        id = 0;
    } else {
        ++mSoundCounter;
        id = mSoundCounter;
        if (id != 0) {
            if (mSoundIds.mpEnd < mSoundIds.mpCapacity) {
                uint* p = mSoundIds.mpEnd++;
                if (p)
                    *p = id;
            } else {
                mSoundIds.DoInsertValue(mSoundIds.mpEnd, id);
            }
        }
    }

    for (uint i = 0; i < count; ++i) {
        BodyPart* part = &mpAnim->mpModel->mpParts[parts[i]];
        if (!part->mpData->mpSound)
            continue;

        AudioSystem* sys = GetSystemAT();
        uint handle = sys ? sys->s24() : 0;
        int partIndex = parts[i];

        SoundNode* root = mSoundMap.mpParent;
        SoundNode* parent = (SoundNode*)&mSoundMap;
        while (root) {
            parent = root;
            if (id < root->mKey)
                root = root->mpRight;
            else
                root = root->mpLeft;
        }
        int side = 0;
        if (parent != (SoundNode*)&mSoundMap && !(id < parent->mKey))
            side = 1;

        SoundNode* node = (SoundNode*)SimAlloc(
            0x1c, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        if (node) {
            node->mKey = id;
            node->mHandle = handle;
            node->mPart = partIndex;
        }
        RBTreeInsert(node, parent, &mSoundMap, side);
        ++mSoundMapCount;

        audio->s38(0x3475365);
        audio->s44(0x347537e, name, 0);
        audio->s40(0x3475385, handle);
        audio->s40(0x39f9e01, (uint)(uintptr_t)part->mpData->mpSound);

        Vec3 pos = RotateOffset(mpAnim->mpModel->mRotation, part->mOffset);
        pos.x += mpAnim->mpModel->mPosition.x;
        pos.y += mpAnim->mpModel->mPosition.y;
        pos.z += mpAnim->mpModel->mPosition.z;
        audio->s3c(0x3475391, pos.x);
        audio->s3c(0x3475395, pos.y);
        audio->s3c(0x3475398, pos.z);

        float scale = mpAnim->mpModel->mScale;
        float rx = part->mpData->mRadiusX * scale;
        float ry = part->mpData->mRadiusY * scale;
        float rz = part->mpData->mRadiusZ * scale;
        float radius = sqrtf(rx * rx + (rz * rz + ry * ry));
        audio->s3c(0x39f9e0f, radius + radius);

        audio->s40(0x39f9e08, CallVd8());
        audio->s40(0x44d6399, (mFlagsB58 >> 9) & 1);
        audio->s40(0x44d63a2, mFieldB34 == 1);
        audio->s40(0x48def6d, (uint)Flag388() & 0xff);
        audio->s40(0x3475381, 0);
        audio->s58();
    }
    return id;
}

// @ 0x00c1db40
bool cSPCreatureBase::StartIndependentSound(const char* name, const Vec3* pos, UIntVec* out)
{
    AudioSystem* audio = GetSystemAT();
    if (!audio)
        return false;

    int parts[255];
    uint count = QueryCreatureBodyParts(this, 2, parts, 0xff);

    // Clear the caller-supplied handle vector (the original emits a zero-length
    // memcpy for the element destructor pass, then resets end to begin).
    memcpy(out->mpBegin, out->mpEnd, 0);
    out->mpEnd = out->mpBegin;

    for (uint i = 0; i < count; ++i) {
        BodyPart* part = &mpAnim->mpModel->mpParts[parts[i]];
        if (!part->mpData->mpSound)
            continue;

        uint handle = audio->s20();
        out->push_back(handle);

        audio->s38(0x3475365);
        audio->s44(0x347537e, name, 0);
        audio->s40(0x3475385, handle);
        audio->s40(0x39f9e01, (uint)(uintptr_t)part->mpData->mpSound);

        if (pos->x == g_168d910 && pos->y == g_168d914 && pos->z == g_168d918) {
            audio->s40(0x3475389, 0);
        } else {
            audio->s40(0x3475389, 1);
            audio->s3c(0x3475391, pos->x);
            audio->s3c(0x3475395, pos->y);
            audio->s3c(0x3475398, pos->z);
        }

        float scale = mpAnim->mpModel->mScale;
        float rx = part->mpData->mRadiusX * scale;
        float ry = part->mpData->mRadiusY * scale;
        float rz = part->mpData->mRadiusZ * scale;
        float radius = sqrtf(rx * rx + (rz * rz + ry * ry));
        audio->s3c(0x39f9e0f, radius + radius);

        audio->s40(0x39f9e08, CallVd8());
        audio->s40(0x44d6399, 0);
        audio->s40(0x44d63a2, 1);
        audio->s40(0x48def6d, 0);
        audio->s40(0x3475381, 0);
        audio->s58();
    }
    return count != 0;
}

// Layout checks for the fields used above.
OFFCHK(BodyPart, mpData, 0x0); OFFCHK(BodyPart, mOffset, 0x10);
OFFCHK(PartData, mRadiusX, 0x138); OFFCHK(PartData, mRadiusY, 0x13c); OFFCHK(PartData, mRadiusZ, 0x140);
OFFCHK(PartData, mpSound, 0x428);
OFFCHK(CreatureModel, mPosition, 0x18); OFFCHK(CreatureModel, mRotation, 0x3c);
OFFCHK(CreatureModel, mScale, 0x70); OFFCHK(CreatureModel, mpParts, 0x2e4);
OFFCHK(AnimCreature, mpModel, 0x17c);
OFFCHK(SoundNode, mKey, 0x10); OFFCHK(SoundNode, mHandle, 0x14); OFFCHK(SoundNode, mPart, 0x18);
OFFCHK(SoundMapHead, mpParent, 0x8);
OFFCHK(UIntVec, mpBegin, 0x0); OFFCHK(UIntVec, mpEnd, 0x4); OFFCHK(UIntVec, mpCapacity, 0x8);
OFFCHK(cSPCreatureBase, mFieldB34, 0xb34); OFFCHK(cSPCreatureBase, mpAnim, 0xb54);
OFFCHK(cSPCreatureBase, mFlagsB58, 0xb58); OFFCHK(cSPCreatureBase, mSoundMap, 0xe0c);
OFFCHK(cSPCreatureBase, mSoundMapCount, 0xe1c); OFFCHK(cSPCreatureBase, mSoundIds, 0xe24);
OFFCHK(cSPCreatureBase, mSoundCounter, 0xf94);
