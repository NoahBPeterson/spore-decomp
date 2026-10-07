// Slice s009c9910: nSPCreatureAnim::creature_instance_data::UpdateEffect (0x009c9910, 2921 bytes).
//
// Updates one animation-driven effect/sound attachment of a creature. Two modes:
//  - event-located (mbEventLocated): resolve position / orientation / scale through
//    ComputeEventLocationState for the bones named by the event, then push them into the
//    effect (XformMsg), the effect's scale/colour helpers and the audio handle;
//  - bone-attached: offset (optionally scaled by the creature scale) and rotation relative to
//    a bone (or to the creature root when the bone index is out of range), composed with the
//    creature transform, then pushed to the effect, the user callback, the audio handle and
//    the shared transform message.
// Returns whether the effect is still alive/updated.
//
// Retail layouts (newer than the 2008 PDB: quaternions instead of matrices) come from the
// disassembly. Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace checkerlib {
class vector_3 {
public:
    float x, y, z;
    vector_3() {}
    vector_3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    vector_3& operator*=(float s)
    {
        x *= s; y *= s; z *= s;
        return *this;
    }
};
class vector_4 {
public:
    float x, y, z, w;
    vector_4() {}
    vector_4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
class matrix_3x3 {
public:
    float el[9];
};

inline vector_3 operator+(const vector_3& a, const vector_3& b) { return vector_3(a.x + b.x, a.y + b.y, a.z + b.z); }
__forceinline vector_3 operator-(const vector_3& a, const vector_3& b) { return vector_3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline vector_3 operator*(float s, const vector_3& a) { return vector_3(s * a.x, s * a.y, s * a.z); }
inline float Length2(const vector_3& a) { return a.x * a.x + a.y * a.y + a.z * a.z; }

inline vector_4 QuaternionConjugate(const vector_4& q) { return vector_4(-q.x, -q.y, -q.z, q.w); }

// Hamilton product a*b.
inline vector_4 QuaternionProduct(const vector_4& a, const vector_4& b)
{
    vector_4 r;
    r.x = ((b.x * a.w + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.y * b.w + a.z * b.x) + b.y * a.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + b.z * a.w) + b.y * a.x;
    r.w = ((b.w * a.w - b.x * a.x) - a.y * b.y) - b.z * a.z;
    return r;
}

vector_3 QuaternionVectorTransform(const vector_4& q, const vector_3& v); // 0x0099c1a0
matrix_3x3 QuaternionToMatrix(const vector_4& q);                          // 0x009a46a0
}
using namespace checkerlib;

// Effect transform message (flags select which parts are valid).
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    vector_3 pos;
    float scale;
    matrix_3x3 rot;
    XformMsg(); // 0x00434040
    void SetPos(const vector_3& v) { pos = v; flags |= 4; ++count; }
    void SetScale(float s) { scale = s; ++count; }
    void SetRot(const matrix_3x3& m) { rot = m; flags |= 2; ++count; }
};

class IEffect {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual bool IsPlaying();              // +0x10
    virtual void v14();
    virtual void SetXform(XformMsg* msg);  // +0x18
    virtual void v1c();
    virtual void GetXform(XformMsg* msg);  // +0x20
};

struct XformTarget {
    uint32_t pad00[2];
    XformMsg msg; // +0x08
};

struct ReadyFlag {
    uint32_t pad00[3];
    bool mbReady; // +0x0c
};

typedef bool (*EffectCallback)(void* data, vector_3* pos, matrix_3x3* rot);

struct cAnimEffect {
    uint32_t pad00[2];
    uint32_t mBoneIndex;          // +0x08
    vector_3 mOffset;             // +0x0c
    vector_4 mRotation;           // +0x18
    uint8_t pad28;
    bool mbScaleWithCreature;     // +0x29
    uint8_t pad2a[2];
    float mScale;                 // +0x2c
    bool mbEventLocated;          // +0x30
    uint8_t pad31[3];
    uint32_t mEventFlags;         // +0x34
    uint32_t mLocFlags;           // +0x38
    uint32_t mLocFlags2;          // +0x3c
    uint32_t pad40;
    uint32_t mLocFlags3;          // +0x44
    uint32_t mEventValue;         // +0x48 (float bits)
    ReadyFlag* mpCreature;        // +0x4c
    ReadyFlag* mpCreature2;       // +0x50
    ReadyFlag* mpCreature3;       // +0x54
    uint32_t mBone;               // +0x58
    uint32_t mBone2;              // +0x5c
    uint32_t pad60;
    vector_3 mDirection;          // +0x64
    int mOrientMode;              // +0x70
    int mScaleMode;               // +0x74
    ReadyFlag* mpColorCreature;   // +0x78
    uint32_t mColorBone;          // +0x7c
    vector_3 mColor;              // +0x80
    IEffect* mpEffect;            // +0x8c
    XformTarget* mpXformTarget;   // +0x90
    uint32_t mSoundHandle;        // +0x94
    vector_3 mLastSoundPos;       // +0x98
    void* mpCallbackData;         // +0xa4
    EffectCallback mpCallback;    // +0xa8
};

struct BoneStatic {
    uint8_t pad[0x154];
    uint8_t mFlags; // +0x154
};

class BoneAnimState {
public:
    void SetFloatParam(uint32_t id, int a, float value, float weight); // 0x0099c4a0
};

struct creature_bone {             // 700 bytes
    BoneStatic* mpStatic;          // +0x00
    uint32_t pad04[3];
    vector_3 pos;                  // +0x10
    vector_4 rot;                  // +0x1c
    uint32_t pad2c[(0xa0 - 0x2c) / 4];
    BoneAnimState mAnimState;      // +0xa0
    uint8_t padA1[700 - 0xa1];
};

bool IsSoundPlaying(uint32_t handle);                         // 0x009fbdd0
void SetSoundPosition(uint32_t handle, const vector_3* pos);  // 0x009fbe50
float GetSoundValue(uint32_t handle);                         // 0x009fbe20
void SetEffectScale(IEffect* effect, float scale);            // 0x009fbd50
void SetEffectColor(IEffect* effect, const vector_3* color);  // 0x009fbcd0
void SetEffectAlpha(IEffect* effect, float alpha);            // 0x009fbcf0

namespace nSPCreatureAnim {

bool ComputeEventLocationState(char randomize, uint32_t evFlags, uint32_t locFlags, uint32_t value,
                               void* owner, ReadyFlag* creature, uint32_t boneIdx, vector_3* pos,
                               vector_3* pos2, vector_4* outQuat, float* outScalar,
                               vector_3* outVec, vector_3* dirIn, vector_3* dirIn2, int p15); // 0x009a59e0

class creature_instance_data {
public:
    uint32_t pad00[6];
    vector_3 pos;                       // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    vector_4 rot;                       // +0x3c
    uint32_t pad4c[(0x70 - 0x4c) / 4];
    float scale;                        // +0x70
    uint32_t pad74[(0x2e4 - 0x74) / 4];
    creature_bone* mBonesBegin;         // +0x2e4
    creature_bone* mBonesEnd;           // +0x2e8

    uint32_t BoneCount() const { return (uint32_t)(mBonesEnd - mBonesBegin); }

    bool UpdateEffect(cAnimEffect* effect);
};

// @ 0x009c9910
bool creature_instance_data::UpdateEffect(cAnimEffect* effect)
{
    bool result = false;
    vector_3 pos;

    if (effect->mbEventLocated) {
        if (effect->mpEffect && effect->mpEffect->IsPlaying())
            result = true;
        if (effect->mSoundHandle && IsSoundPlaying(effect->mSoundHandle))
            result = true;
        if ((effect->mpCreature && !effect->mpCreature->mbReady) ||
            (effect->mpCreature2 && !effect->mpCreature2->mbReady) ||
            (effect->mpCreature3 && !effect->mpCreature3->mbReady))
            result = false;
        if (effect->mpColorCreature && !effect->mpColorCreature->mbReady) {
            result = false;
            return result;
        }
        if (result) {
            float scalar = 1.0f;
            float alpha = 1.0f;
            bool bUsePos2;
            vector_3 pos2;
            vector_4 quat;
            vector_3 colorPos;
            vector_3 colorPos2;
            vector_4 colorQuat;
            uint32_t flags = effect->mEventFlags;
            if (flags & 0x105800) {
                if ((flags & 0x8000) && effect->mOrientMode != 0)
                    bUsePos2 = false;
                else
                    bUsePos2 = true;
                ComputeEventLocationState(0, flags, effect->mLocFlags, effect->mEventValue, this,
                                          effect->mpCreature, effect->mBone, &pos,
                                          bUsePos2 ? &pos2 : 0,
                                          effect->mOrientMode == 0 ? &quat : 0,
                                          effect->mScaleMode == 0 ? &scalar : 0,
                                          &effect->mDirection, &pos, &pos2, 0);
                if (effect->mOrientMode == 1)
                    ComputeEventLocationState(0, effect->mEventFlags, effect->mLocFlags2,
                                              effect->mEventValue, this, effect->mpCreature2,
                                              effect->mBone2, 0, bUsePos2 ? 0 : &pos2, &quat,
                                              effect->mScaleMode == 1 ? &scalar : 0, 0, &pos,
                                              &pos2, 0);
                if (effect->mScaleMode == 2)
                    ComputeEventLocationState(0, effect->mEventFlags, effect->mLocFlags2,
                                              effect->mEventValue, this, effect->mpCreature2,
                                              effect->mBone2, 0, 0, 0, &scalar, 0, &pos, &pos2, 0);
            }
            if (effect->mEventFlags & 0x2000)
                ComputeEventLocationState(0, effect->mEventFlags, effect->mLocFlags3,
                                          effect->mEventValue, this, effect->mpColorCreature,
                                          effect->mColorBone, &colorPos, &colorPos2, &colorQuat,
                                          &alpha, &effect->mColor, &colorPos, &colorPos2, 0);
            if (effect->mpEffect) {
                if (effect->mEventFlags & 0x104800) {
                    XformMsg msg;
                    effect->mpEffect->GetXform(&msg);
                    if (effect->mEventFlags & 0x800)
                        msg.SetPos(pos);
                    if (effect->mEventFlags & 0x4000) {
                        matrix_3x3 rotMatrix = QuaternionToMatrix(QuaternionConjugate(quat));
                        msg.SetRot(rotMatrix);
                    }
                    if (effect->mEventFlags & 0x100000)
                        msg.SetScale(scalar);
                    effect->mpEffect->SetXform(&msg);
                }
                if (effect->mEventFlags & 0x1000)
                    SetEffectScale(effect->mpEffect, scalar);
                if (effect->mEventFlags & 0x2000) {
                    SetEffectColor(effect->mpEffect, &colorPos);
                    SetEffectAlpha(effect->mpEffect, 1.0f);
                }
            }
            if (effect->mSoundHandle) {
                if ((effect->mEventFlags & 0x800) &&
                    Length2(pos - effect->mLastSoundPos) >= 0.25f) {
                    SetSoundPosition(effect->mSoundHandle, &pos);
                    effect->mLastSoundPos.x = pos.x;
                    effect->mLastSoundPos.y = pos.y;
                    effect->mLastSoundPos.z = pos.z;
                }
                uint32_t evFlags = effect->mEventFlags;
                if ((evFlags & 0x400) && effect->mBone < BoneCount()) {
                    creature_bone& bone = mBonesBegin[effect->mBone];
                    if (bone.mpStatic->mFlags & 0x20) {
                        float weight = 1.0f;
                        if ((evFlags & 0x300) == 0x200)
                            weight = *(float*)&effect->mEventValue;
                        bone.mAnimState.SetFloatParam(0x4d5bf589, 1, GetSoundValue(effect->mSoundHandle), weight);
                    }
                }
            }
        }
    } else {
        vector_4 q;
        if (effect->mBoneIndex < BoneCount()) {
            creature_bone& bone = mBonesBegin[effect->mBoneIndex];
            pos.x = effect->mOffset.x;
            pos.y = effect->mOffset.y;
            pos.z = effect->mOffset.z;
            if (effect->mbScaleWithCreature)
                pos *= scale;
            vector_3 local = bone.pos + QuaternionVectorTransform(bone.rot, pos);
            pos = QuaternionVectorTransform(rot, local) + this->pos;
            q = QuaternionProduct(QuaternionProduct(rot, bone.rot), effect->mRotation);
        } else {
            pos = this->pos + QuaternionVectorTransform(rot, effect->mOffset);
            q = QuaternionProduct(rot, effect->mRotation);
        }
        matrix_3x3 rotMatrix = QuaternionToMatrix(QuaternionConjugate(q));

        if (effect->mpEffect && effect->mpEffect->IsPlaying()) {
            result = true;
            XformMsg msg;
            effect->mpEffect->GetXform(&msg);
            msg.SetPos(pos);
            msg.SetRot(rotMatrix);
            if (effect->mbScaleWithCreature)
                msg.SetScale(scale * effect->mScale);
            effect->mpEffect->SetXform(&msg);
        }
        if (effect->mpCallbackData && effect->mpCallback &&
            effect->mpCallback(effect->mpCallbackData, &pos, &rotMatrix))
            result = true;
        if (effect->mSoundHandle && IsSoundPlaying(effect->mSoundHandle)) {
            result = true;
            if (Length2(pos - effect->mLastSoundPos) >= 0.25f) {
                SetSoundPosition(effect->mSoundHandle, &pos);
                effect->mLastSoundPos.x = pos.x;
                effect->mLastSoundPos.y = pos.y;
                effect->mLastSoundPos.z = pos.z;
            }
        }
        if (effect->mpXformTarget) {
            effect->mpXformTarget->msg.SetPos(pos);
            effect->mpXformTarget->msg.SetRot(rotMatrix);
            result = true;
        }
    }
    return result;
}

} // namespace nSPCreatureAnim
