// Slice s00c163f0 -- Simulator::cCreatureBase::func6Ch (0x00c163f0, 3936 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Per-frame graphics/audio sync of a creature (ModAPI: "called by Update"), member names from
// ModAPI's cCreatureBase.h. With an animated model present it:
//  1. pushes flags / brain level / age / speed state into the animated creature;
//  2. re-attaches the effects of mEffectPool1 (dropping dead ones), of the model's own effect
//     pool (or calls their attach callbacks) and of mEffectPool2 to the model transform;
//  3. moves every looping 3D sound of field_E08 to its bone's world position (stopping and
//     erasing finished ones);
//  4. drives the locomotion sound (start/stop + speed/age/flag parameters);
//  5. re-attaches the effects of the field_F84 list, dropping dead ones.
#include <math.h>
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

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

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }

struct Quaternion { float x, y, z, w; };

// Rotates p by the unit quaternion q (p + 2 * (rotation-matrix minus identity) * p).
__forceinline Vector3 RotateVector(const Quaternion& q, const Vector3& p)
{
    float xw = q.x * q.w;
    float nyy = -(q.y * q.y);
    float yw = q.y * q.w;
    float zw = q.z * q.w;
    float nxx = -(q.x * q.x);
    float yx = q.y * q.x;
    float zx = q.z * q.x;
    float zy = q.z * q.y;
    float nzz = -(q.z * q.z);
    float rx = (((nzz + nyy) * p.x + (zx + yw) * p.z) + (yx - zw) * p.y) * 2.0f + p.x;
    float ry = (((yx + zw) * p.x + (zy - xw) * p.z) + (nzz + nxx) * p.y) * 2.0f + p.y;
    float rz = (((zx - yw) * p.x + (nyy + nxx) * p.z) + (zy + xw) * p.y) * 2.0f + p.z;
    return Vector3(rx, ry, rz);
}

struct Matrix3 {
    Vector3 row[3];
    void Assign(const Matrix3& m);   // 0x0041cb40 (out-of-line /Od copy of the row-wise copy)
};
Matrix3 Matrix3FromQuaternion(const Quaternion& q);   // 0x0059c190

extern Vector3 sZeroVector;      // 0x0168d988 (this TU's runtime-initialised copy)
extern Matrix3 sIdentityMatrix;  // 0x0168d964

// ModAPI Transform.
struct Transform {
    enum { kFlagScale = 1, kFlagRotation = 2, kFlagOffset = 4 };
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float mfScale;
    Matrix3 mRotation;

    // Default construction; the identity copy goes through the out-of-line Matrix3 copy.
    Transform() : mnFlags(0), mnTransformCount(0), mOffset(sZeroVector), mfScale(1.0f)
    {
        mRotation.Assign(sIdentityMatrix);
    }
    // The same construction with the identity copy inlined (row by row).
    struct InlineInit {};
    __forceinline Transform(InlineInit) : mnFlags(0), mnTransformCount(0), mOffset(sZeroVector), mfScale(1.0f)
    {
        mRotation.row[0] = sIdentityMatrix.row[0];
        mRotation.row[1] = sIdentityMatrix.row[1];
        mRotation.row[2] = sIdentityMatrix.row[2];
    }
    void SetOffset(const Vector3& v) { mOffset = v; mnFlags |= kFlagOffset; mnTransformCount += 1; }
    void SetRotation(const Matrix3& m) { mRotation = m; mnFlags |= kFlagRotation; mnTransformCount += 1; }
    // Copies another transform's scale (counted as a change, scale flag untouched).
    void CopyScale(const Transform& o) { ++mnTransformCount; mfScale = o.mfScale; }
};

namespace Swarm {
class IVisualEffect {
public:
    PV
    virtual int Release();                          // +0x04
    PV2
    virtual bool IsRunning();                       // +0x10
    PV
    virtual void SetTransform(const Transform& t);  // +0x18
    PV
    virtual void GetTransform(Transform& t);        // +0x20
};
}
using Swarm::IVisualEffect;

namespace EA { namespace Audio {
class ISystem {
public:
    PV8
    virtual uint32_t NewTrack();                    // +0x20
    PV
    virtual bool IsTrackPlaying(uint32_t track);    // +0x28
    virtual void StopTrack(uint32_t track);         // +0x2c
};
ISystem* GetSystemAT();   // 0x00a206f0
}}

void SetTrackPosition(uint32_t track, Vector3 pos);                          // 0x009fbc50
void StopTrack(uint32_t track, int fade);                                    // 0x00572020
void Start3dSoundByName(uint32_t soundId, uint32_t track, Vector3 pos);      // 0x00571f80
namespace SP { namespace EditorUtils {
void PlayEditorSound(uint32_t track, uint32_t paramId, float value, int flags);   // 0x00435f40
}}

__forceinline bool IsTrackPlaying(uint32_t track)
{
    EA::Audio::ISystem* sys = EA::Audio::GetSystemAT();
    return sys && sys->IsTrackPlaying(track);
}
__forceinline void StopTrack(uint32_t track)
{
    EA::Audio::ISystem* sys = EA::Audio::GetSystemAT();
    if (sys)
        sys->StopTrack(track);
}
__forceinline uint32_t NewTrack()
{
    EA::Audio::ISystem* sys = EA::Audio::GetSystemAT();
    return sys ? sys->NewTrack() : 0;
}

// --- EASTL containers (only what is used) --------------------------------------------------

template <class K, class V> struct hash_node {
    K first;
    V second;
    hash_node* mpNext;
};
template <class K, class V> struct hashtable_iterator {
    hash_node<K, V>* mpNode;
    hash_node<K, V>** mpBucket;
    hashtable_iterator() {}
    hashtable_iterator(hash_node<K, V>** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}

    void increment_bucket()
    {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment()
    {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    hashtable_iterator& operator++() { increment(); return *this; }
    bool operator!=(const hashtable_iterator& x) const { return mpNode != x.mpNode; }
};
template <class K, class V>
struct sp_fixed_hash_map {
    typedef hashtable_iterator<K, V> iterator;
    uint32_t mHashFunction;
    hash_node<K, V>** mpBucketArray;
    uint32_t mnBucketCount;
    uint32_t mnElementCount;
    iterator begin();                 // 0x00594410 (out-of-line instance)
    iterator erase(iterator it);      // 0x00d2c9f0
    __forceinline iterator inline_begin()
    {
        iterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    iterator end() { return iterator(mpBucketArray + mnBucketCount); }
    bool empty() const { return mnElementCount == 0; }
};
typedef sp_fixed_hash_map<uint32_t, IVisualEffect*> CreatureEffectPool;

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    uint32_t mColor;
};
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);                     // 0x00921580
void RBTreeErase(rbtree_node_base* pNode, rbtree_node_base* pAnchor);                 // 0x00921880
void EASTLFree(void* p);                                                              // 0x00f47380

struct SoundEntry {
    uint32_t mTrack;   // node +0x14
    int mBoneIndex;    // node +0x18
};
struct sound_node : rbtree_node_base {
    uint32_t mKey;     // +0x10
    SoundEntry mValue; // +0x14
};
struct SoundMap {   // eastl::map<int, SoundEntry>
    uint32_t mCompare;
    rbtree_node_base mAnchor;   // +0x4
    uint32_t mnSize;            // +0x14
    sound_node* begin() { return (sound_node*)mAnchor.mpNodeLeft; }
    sound_node* end() { return (sound_node*)&mAnchor; }
    bool empty() const { return mnSize == 0; }
    sound_node* erase(sound_node* position)
    {
        sound_node* const pErase = position;
        --mnSize;
        position = (sound_node*)RBTreeIncrement(position);
        RBTreeErase(pErase, &mAnchor);
        EASTLFree(pErase);
        return position;
    }
};

struct list_node_base {
    list_node_base* mpNext;
    list_node_base* mpPrev;
    void remove()
    {
        mpPrev->mpNext = mpNext;
        mpNext->mpPrev = mpPrev;
    }
};
struct effect_list_node : list_node_base {
    IVisualEffect* mpValue;   // intrusive_ptr<IVisualEffect>
    ~effect_list_node()
    {
        if (mpValue)
            mpValue->Release();
    }
};
struct EffectList {   // eastl::list<IVisualEffectPtr>
    list_node_base mNode;
    uint32_t mAllocator;
    list_node_base* begin() { return mNode.mpNext; }
    list_node_base* end() { return &mNode; }
    bool empty() const { return mNode.mpNext == &mNode; }
    void DoErase(list_node_base* pNode)
    {
        pNode->remove();
        ((effect_list_node*)pNode)->~effect_list_node();
        EASTLFree(pNode);
    }
    list_node_base* erase(list_node_base* position)
    {
        position = position->mpNext;
        DoErase(position->mpPrev);
        return position;
    }
};

// --- Animated model -------------------------------------------------------------------------

struct cBone {   // 700 bytes
    uint32_t pad0[4];
    Vector3 mPosition;   // +0x10
    uint8_t pad1c[700 - 0x1c];
};

// Element of the model's own effect pool.
struct cModelEffect {
    uint32_t pad0[0x23];
    IVisualEffect* mpEffect;                                               // +0x8c
    uint32_t pad90[5];
    void* mpCallbackData;                                                  // +0xa4
    void (*mpCallback)(void* data, const Vector3& pos, const Matrix3& rot); // +0xa8
};
typedef sp_fixed_hash_map<uint32_t, cModelEffect*> ModelEffectPool;

struct cAnimatedCreatureData {
    uint32_t pad0[6];
    Vector3 mPosition;          // +0x18
    uint32_t pad24[6];
    Quaternion mOrientation;    // +0x3c
    uint32_t pad4c[166];
    cBone* mpBones;             // +0x2e4
    uint8_t pad2e8[0x17a0 - 0x2e8];
    ModelEffectPool mEffects;   // +0x17a0
};

class AnimatedCreature {
public:
    uint32_t pad0[4];
    Quaternion mOrientation;           // +0x10
    uint8_t pad20[0x151 - 0x20];
    bool mbFlag151;                    // +0x151
    uint8_t pad152[0x17c - 0x152];
    cAnimatedCreatureData* mpData;     // +0x17c

    void SetBrainLevel(int level);     // 0x00a04c80
    void SetIsBaby(bool baby);         // 0x00a04ca0
    void SetSpeedState(int state);     // 0x00a04ad0
    const Vector3& GetPosition();      // 0x00a048a0
    int GetMode();                     // 0x00a02bd0
};

namespace Simulator {

class cLocomotiveObject {
public:
    PV8 PV2 PV
    virtual const Vector3& GetPosition();   // +0x2c
    const Vector3& GetVelocity();           // 0x00d20610
};

class cSpeciesProfile {
public:
    uint8_t pad0[0x574];
    float mf574;   // +0x574
    uint8_t pad578[0x58c - 0x578];
    float mf58C;   // +0x58c
};

class cCreatureBase {
public:
    PV8 PV8 PV8 PV8 PV8 PV8 PV4 PV2
    virtual int GetCurrentBrainLevel();   // +0xd8

    uint32_t pad4[(0xc0 - 0x4) / 4];
    cLocomotiveObject mLocomotion;        // +0xc0 (base subobject)
    uint8_t padc4[0x137 - 0xc4];
    bool field_137;                       // +0x137
    uint8_t pad138[0xb20 - 0x138];
    cSpeciesProfile* mpSpeciesProfile;    // +0xb20
    uint32_t padb24[4];
    int mAge;                             // +0xb34
    uint32_t padb38[7];
    AnimatedCreature* mpAnimatedCreature; // +0xb54
    uint32_t mGeneralFlags;               // +0xb58
    bool field_B5C;
    bool mbTeleport;
    bool mbDead;                          // +0xb5e
    bool mbHasBeenEaten;
    uint32_t padb60[2];
    bool field_B68;                       // +0xb68
    bool field_B69;                       // +0xb69
    uint8_t padb6a[2];
    uint32_t field_B6C;                   // +0xb6c (Audio::AudioTrack)
    uint8_t padb70[0xcc8 - 0xb70];
    CreatureEffectPool mEffectPool1;      // +0xcc8
    uint8_t padcd8[0xa0 - 0x10];
    CreatureEffectPool mEffectPool2;      // +0xd68
    uint8_t padd78[0xa0 - 0x10];
    SoundMap field_E08;                   // +0xe08
    uint8_t pade20[0xf84 - 0xe20];
    EffectList field_F84;                 // +0xf84
    bool field_F90;                       // +0xf90
    uint32_t field_F94;
    int mSpeedState;                      // +0xf98

    bool IsFlag9() const { return (mGeneralFlags >> 9) & 1; }
    Vector3 GetEffectOffset();            // 0x00c0d860
    void func6Ch(int deltaTime);
};

void cCreatureBase::func6Ch(int deltaTime)
{
    if (!mpAnimatedCreature)
        return;

    bool flagF90 = field_F90;
    mpAnimatedCreature->mbFlag151 = IsFlag9();
    AnimatedCreature* animated = mpAnimatedCreature;
    animated->SetBrainLevel(GetCurrentBrainLevel());
    mpAnimatedCreature->SetIsBaby(mAge == 1);
    mpAnimatedCreature->SetSpeedState(mSpeedState);

    if (!mEffectPool1.empty()) {
        Transform effectXf;
        Transform xf;
        xf.SetRotation(Matrix3FromQuaternion(mpAnimatedCreature->mOrientation));
        xf.SetOffset(mpAnimatedCreature->GetPosition());
        CreatureEffectPool::iterator it = mEffectPool1.begin();
        CreatureEffectPool::iterator itEnd = mEffectPool1.end();
        while (it != itEnd) {
            IVisualEffect* effect = it.mpNode->second;
            if (effect->IsRunning()) {
                effect->GetTransform(effectXf);
                xf.CopyScale(effectXf);
                effect->SetTransform(xf);
                ++it;
            } else {
                it = mEffectPool1.erase(it);
            }
        }
    }

    if (mpAnimatedCreature->GetMode() == 0) {
        Transform effectXf;
        Transform xf;
        xf.SetRotation(Matrix3FromQuaternion(mpAnimatedCreature->mOrientation));
        xf.SetOffset(mpAnimatedCreature->GetPosition());
        ModelEffectPool& pool = mpAnimatedCreature->mpData->mEffects;
        ModelEffectPool::iterator it = pool.begin();
        ModelEffectPool::iterator itEnd = pool.end();
        while (it != itEnd) {
            cModelEffect* modelEffect = it.mpNode->second;
            IVisualEffect* effect = modelEffect->mpEffect;
            if (effect && effect->IsRunning()) {
                effect->GetTransform(effectXf);
                xf.CopyScale(effectXf);
                effect->SetTransform(xf);
            } else if (modelEffect->mpCallbackData && modelEffect->mpCallback) {
                modelEffect->mpCallback(modelEffect->mpCallbackData, xf.mOffset, xf.mRotation);
            }
            ++it;
        }
    }

    if (!mEffectPool2.empty()) {
        Transform xf;
        xf.SetRotation(Matrix3FromQuaternion(mpAnimatedCreature->mOrientation));
        xf.SetOffset(GetEffectOffset());
        CreatureEffectPool::iterator it = mEffectPool2.inline_begin();
        CreatureEffectPool::iterator itEnd = mEffectPool2.end();
        while (it != itEnd) {
            IVisualEffect* effect = it.mpNode->second;
            Transform effectXf((Transform::InlineInit()));
            effect->GetTransform(effectXf);
            xf.CopyScale(effectXf);
            effect->SetTransform(xf);
            ++it;
        }
    }

    if (!field_E08.empty()) {
        for (sound_node* it = field_E08.begin(); it != field_E08.end();) {
            if (IsTrackPlaying(it->mValue.mTrack)) {
                cAnimatedCreatureData* data = mpAnimatedCreature->mpData;
                const Vector3& bonePos = data->mpBones[it->mValue.mBoneIndex].mPosition;
                SetTrackPosition(it->mValue.mTrack, data->mPosition + RotateVector(data->mOrientation, bonePos));
                it = (sound_node*)RBTreeIncrement(it);
            } else {
                StopTrack(it->mValue.mTrack);
                it = field_E08.erase(it);
            }
        }
    }

    if (IsFlag9()) {
        bool active;
        if (!mbDead && field_137 && flagF90 && mpSpeciesProfile->mf58C == 0.0f)
            active = true;
        else
            active = false;
        if (field_B68 || active != field_B69) {
            field_B68 = false;
            if (active) {
                if (field_B6C == 0) {
                    const Vector3& pos = mLocomotion.GetPosition();
                    field_B6C = NewTrack();
                    Start3dSoundByName(0x1da7e755, field_B6C, pos);
                }
            } else if (field_B6C != 0) {
                ::StopTrack(field_B6C, 0);
                field_B6C = 0;
            }
            field_B69 = active;
        }
        if (active) {
            SetTrackPosition(field_B6C, mLocomotion.GetPosition());
            float speed = Clamp(mLocomotion.GetVelocity().Length(), 0.0f, 10.0f);
            SP::EditorUtils::PlayEditorSound(field_B6C, 0xd71e9b18, speed * 0.1f, 0);
            float ageParam = 0.0f;
            if (mAge == 1)
                ageParam = Clamp(mpSpeciesProfile->mf574, 0.1f, 1.5f) * 0.6666667f;
            SP::EditorUtils::PlayEditorSound(field_B6C, 0xcf2b2dfc, ageParam, 0);
            SP::EditorUtils::PlayEditorSound(field_B6C, 0x766f742e, (float)IsFlag9(), 0);
        }
    }

    if (!field_F84.empty()) {
        list_node_base* it = field_F84.begin();
        Transform xf((Transform::InlineInit()));
        xf.SetRotation(Matrix3FromQuaternion(mpAnimatedCreature->mOrientation));
        xf.SetOffset(mpAnimatedCreature->GetPosition());
        while (it != field_F84.end()) {
            IVisualEffect* effect = ((effect_list_node*)it)->mpValue;
            if (effect->IsRunning()) {
                Transform effectXf((Transform::InlineInit()));
                effect->GetTransform(effectXf);
                xf.CopyScale(effectXf);
                effect->SetTransform(xf);
                it = it->mpNext;
            } else {
                it = field_F84.erase(it);
            }
        }
    }
}

}  // namespace Simulator
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct Swarm {
    void erase(int); // 0x00d2c9f0
    void begin(); // 0x00594410
};
}
