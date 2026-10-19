// src/game/SPCreatureAnim/creature_spore.cpp -- migrated from slice(s) s009cbee0, s009c9910, s009c8a90 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/creature_spore.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "nSPCreatureAnim/creature_instance_data.h"
#include "checkerlib/vector_3.h"
#include "checkerlib/vector_4.h"
#include "checkerlib/matrix_3x3.h"
#include "nSPCreatureAnim/creature_body_static_data.h"
#include "nSPCreatureAnim/creature_static_data.h"

// ---- items of slice s009c8a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
struct vector_3_s009c_8a90 {
    float x, y, z;
    vector_3_s009c_8a90& operator=(const vector_3_s009c_8a90& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
}
namespace checkerlib {
struct vector_4_s009c_8a90 {
    float x, y, z, w;
};
}
namespace checkerlib {
inline vector_3_s009c_8a90 operator+(const vector_3_s009c_8a90& a, const vector_3_s009c_8a90& b) { vector_3_s009c_8a90 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
}
namespace checkerlib {
inline vector_3_s009c_8a90 operator-(const vector_3_s009c_8a90& a, const vector_3_s009c_8a90& b) { vector_3_s009c_8a90 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
}
namespace checkerlib {
inline vector_3_s009c_8a90 operator*(const vector_3_s009c_8a90& a, float s) { vector_3_s009c_8a90 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }
}
namespace checkerlib {
vector_3_s009c_8a90* QuaternionVectorTransform(vector_3_s009c_8a90* out, const vector_4_s009c_8a90* q, const vector_3_s009c_8a90* v);         // 0x0099c1a0
}
namespace checkerlib {
vector_3_s009c_8a90* QuaternionVectorTransformInverse(vector_3_s009c_8a90* out, const vector_4_s009c_8a90* q, const vector_3_s009c_8a90* v);  // 0x0099c310
}
namespace EA {
namespace Hash {
uint32_t __cdecl FNV1_String8(const char* pString, uint32_t nInitialValue, int charCase);   // 0x00932e80
}
}
struct BlockFlags;
void __cdecl FUN_009fc220(BlockFlags*);                                  // 0x009fc220
struct BlockDef;
checkerlib::vector_3_s009c_8a90* __cdecl ScaledOffset(checkerlib::vector_3_s009c_8a90* out, BlockDef* b, float t);      // 0x009b53f0
struct BlockDef {
    char      name[0x104];       // +0x000
    uint32_t  hash;              // +0x104
    uint32_t  pad_108;
    checkerlib::vector_3_s009c_8a90  center;            // +0x10c
    checkerlib::vector_4_s009c_8a90  orient;            // +0x118
    uint32_t  pad_128[(0x138 - 0x128) / 4];
    checkerlib::vector_3_s009c_8a90  half;              // +0x138
    checkerlib::vector_3_s009c_8a90  local;             // +0x144
    BlockFlags* flags() { return (BlockFlags*)((char*)this + 0x150); }
    uint32_t  pad_150[(0x1fc - 0x150) / 4];
    int       parent;            // +0x1fc
    uint32_t  pad_200;
    int       childMark;         // +0x204
    int       refCount;          // +0x208
    uint32_t  pad_20c[(0x330 - 0x20c) / 4];
    checkerlib::vector_3_s009c_8a90  offset;            // +0x330
    uint32_t  pad_33c[(0x344 - 0x33c) / 4];
    checkerlib::vector_3_s009c_8a90  parentLocal;       // +0x344
    checkerlib::vector_3_s009c_8a90  parentOffset;      // +0x350
    checkerlib::vector_3_s009c_8a90  scaled;            // +0x35c
    float     scaledLen;         // +0x368
    float     limit;             // +0x36c
    uint32_t  pad_370[(0x378 - 0x370) / 4];
    float     scale;             // +0x378
    uint32_t  pad_37c[(0x468 - 0x37c) / 4];
};
struct BlockOwner {
    uint32_t  pad_000[0x384 / 4];
    BlockDef* blocks;            // +0x384
};
struct CreatureCommandState {
    uint32_t     pad_000;
    int          count;          // +0x04
    uint32_t     pad_008[2];
    checkerlib::vector_3_s009c_8a90     anchor;         // +0x10
    checkerlib::vector_3_s009c_8a90     anchor2;        // +0x1c
    checkerlib::vector_3_s009c_8a90     boxMin;         // +0x28
    checkerlib::vector_3_s009c_8a90     boxMax;         // +0x34
    BlockDef*    block;          // +0x40
    BlockOwner*  owner;          // +0x44
};
__forceinline checkerlib::vector_3_s009c_8a90 QuaternionVectorTransformInverse(const checkerlib::vector_4_s009c_8a90& q, const checkerlib::vector_3_s009c_8a90& v)
{
    checkerlib::vector_3_s009c_8a90 r;
    float nxw = -(q.x * q.w), nzw = -(q.z * q.w), nxx = -(q.x * q.x);
    float yx = q.y * q.x, zy = q.z * q.y, yw = q.y * q.w, zx = q.z * q.x;
    float nyy = -(q.y * q.y), nzz = -(q.z * q.z);
    r.x = (((yx - nzw) * v.y + (zx + -yw) * v.z) + (nzz + nyy) * v.x) * 2.0f + v.x;
    r.y = (((nzz + nxx) * v.y + (zy - nxw) * v.z) + (yx + nzw) * v.x) * 2.0f + v.y;
    r.z = (((nyy + nxx) * v.z + (zy + nxw) * v.y) + (zx - -yw) * v.x) * 2.0f + v.z;
    return r;
}
namespace {

struct cBlockBlockCommand {
    uint32_t              pad_000[12];
    CreatureCommandState* mState;       // +0x30

    void OnEndBlock(bool bCancel);      // 0x009c8a90
};

}  // namespace
// ---- items of slice s009c8a90 end

// ---- items of slice s009c9910 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace checkerlib {
class vector_3_s009c_9910 {
public:
    float x, y, z;
    vector_3_s009c_9910() {}
    vector_3_s009c_9910(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    vector_3_s009c_9910& operator*=(float s)
    {
        x *= s; y *= s; z *= s;
        return *this;
    }
};
}
namespace checkerlib {
class vector_4_s009c_9910 {
public:
    float x, y, z, w;
    vector_4_s009c_9910() {}
    vector_4_s009c_9910(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
};
}
namespace checkerlib {
class matrix_3x3_s009c_9910 {
public:
    float el[9];
};
}
namespace checkerlib {
inline vector_3_s009c_9910 operator+(const vector_3_s009c_9910& a, const vector_3_s009c_9910& b) { return vector_3_s009c_9910(a.x + b.x, a.y + b.y, a.z + b.z); }
}
namespace checkerlib {
__forceinline vector_3_s009c_9910 operator-(const vector_3_s009c_9910& a, const vector_3_s009c_9910& b) { return vector_3_s009c_9910(a.x - b.x, a.y - b.y, a.z - b.z); }
}
namespace checkerlib {
inline vector_3_s009c_9910 operator*(float s, const vector_3_s009c_9910& a) { return vector_3_s009c_9910(s * a.x, s * a.y, s * a.z); }
}
namespace checkerlib {
inline float Length2(const vector_3_s009c_9910& a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
}
namespace checkerlib {
inline vector_4_s009c_9910 QuaternionConjugate(const vector_4_s009c_9910& q) { return vector_4_s009c_9910(-q.x, -q.y, -q.z, q.w); }
}
namespace checkerlib {
inline vector_4_s009c_9910 QuaternionProduct(const vector_4_s009c_9910& a, const vector_4_s009c_9910& b)
{
    vector_4_s009c_9910 r;
    r.x = ((b.x * a.w + b.w * a.x) - a.z * b.y) + a.y * b.z;
    r.y = ((a.y * b.w + a.z * b.x) + b.y * a.w) - b.z * a.x;
    r.z = ((a.z * b.w - a.y * b.x) + b.z * a.w) + b.y * a.x;
    r.w = ((b.w * a.w - b.x * a.x) - a.y * b.y) - b.z * a.z;
    return r;
}
}
namespace checkerlib {
vector_3_s009c_9910 QuaternionVectorTransform(const vector_4_s009c_9910& q, const vector_3_s009c_9910& v); // 0x0099c1a0
}
namespace checkerlib {
matrix_3x3_s009c_9910 QuaternionToMatrix(const vector_4_s009c_9910& q);                          // 0x009a46a0
}
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    checkerlib::vector_3_s009c_9910 pos;
    float scale;
    checkerlib::matrix_3x3_s009c_9910 rot;
    XformMsg(); // 0x00434040
    void SetPos(const checkerlib::vector_3_s009c_9910& v) { pos = v; flags |= 4; ++count; }
    void SetScale(float s) { scale = s; ++count; }
    void SetRot(const checkerlib::matrix_3x3_s009c_9910& m) { rot = m; flags |= 2; ++count; }
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
typedef bool (*EffectCallback)(void* data, checkerlib::vector_3_s009c_9910* pos, checkerlib::matrix_3x3_s009c_9910* rot);
struct cAnimEffect {
    uint32_t pad00[2];
    uint32_t mBoneIndex;          // +0x08
    checkerlib::vector_3_s009c_9910 mOffset;             // +0x0c
    checkerlib::vector_4_s009c_9910 mRotation;           // +0x18
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
    checkerlib::vector_3_s009c_9910 mDirection;          // +0x64
    int mOrientMode;              // +0x70
    int mScaleMode;               // +0x74
    ReadyFlag* mpColorCreature;   // +0x78
    uint32_t mColorBone;          // +0x7c
    checkerlib::vector_3_s009c_9910 mColor;              // +0x80
    IEffect* mpEffect;            // +0x8c
    XformTarget* mpXformTarget;   // +0x90
    uint32_t mSoundHandle;        // +0x94
    checkerlib::vector_3_s009c_9910 mLastSoundPos;       // +0x98
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
    checkerlib::vector_3_s009c_9910 pos;                  // +0x10
    checkerlib::vector_4_s009c_9910 rot;                  // +0x1c
    uint32_t pad2c[(0xa0 - 0x2c) / 4];
    BoneAnimState mAnimState;      // +0xa0
    uint8_t padA1[700 - 0xa1];
};
bool IsSoundPlaying(uint32_t handle);                         // 0x009fbdd0
void SetSoundPosition(uint32_t handle, const checkerlib::vector_3_s009c_9910* pos);  // 0x009fbe50
float GetSoundValue(uint32_t handle);                         // 0x009fbe20
void SetEffectScale(IEffect* effect, float scale);            // 0x009fbd50
void SetEffectColor(IEffect* effect, const checkerlib::vector_3_s009c_9910* color);  // 0x009fbcd0
void SetEffectAlpha(IEffect* effect, float alpha);            // 0x009fbcf0
namespace nSPCreatureAnim {
bool ComputeEventLocationState(char randomize, uint32_t evFlags, uint32_t locFlags, uint32_t value,
                               void* owner, ReadyFlag* creature, uint32_t boneIdx, checkerlib::vector_3_s009c_9910* pos,
                               checkerlib::vector_3_s009c_9910* pos2, checkerlib::vector_4_s009c_9910* outQuat, float* outScalar,
                               checkerlib::vector_3_s009c_9910* outVec, checkerlib::vector_3_s009c_9910* dirIn, checkerlib::vector_3_s009c_9910* dirIn2, int p15); // 0x009a59e0
}
namespace nSPCreatureAnim {
class creature_instance_data_s009c_9910 {
public:
    uint32_t pad00[6];
    checkerlib::vector_3_s009c_9910 pos;                       // +0x18
    uint32_t pad24[(0x3c - 0x24) / 4];
    checkerlib::vector_4_s009c_9910 rot;                       // +0x3c
    uint32_t pad4c[(0x70 - 0x4c) / 4];
    float scale;                        // +0x70
    uint32_t pad74[(0x2e4 - 0x74) / 4];
    creature_bone* mBonesBegin;         // +0x2e4
    creature_bone* mBonesEnd;           // +0x2e8

    uint32_t BoneCount() const { return (uint32_t)(mBonesEnd - mBonesBegin); }

    bool UpdateEffect(cAnimEffect* effect);  // 0x009c9910 (nSPCreatureAnim::creature_instance_data::UpdateEffect)
};
}
// ---- items of slice s009c9910 end

// ---- items of slice s009cbee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace nSPCreatureAnim {
struct creature_static_data_s009c_bee0;
}
namespace nSPCreatureAnim {
template <class T> static inline T& at(void* p, int off) { return *(T*)((char*)p + off); }
}
namespace nSPCreatureAnim {
struct StaticDataStub {
    void Clear(int);              // 0x9c1dc0 creature_static_data::Clear
};
}
namespace nSPCreatureAnim {
struct BodyStub {
    void Clear();                 // 0x9b3180 creature_body_static_data::Clear
};
}
namespace nSPCreatureAnim {
struct BodyVecStub {
    void resize(unsigned n);      // 0x9cb840 eastl::vector<creature_body_static_data>::resize
};
}
namespace nSPCreatureAnim {
struct WiggleVecStub {
    void resize(unsigned n);      // 0x9cb8f0 eastl::vector<creature_body_wiggle_static_data>::resize
};
}
struct PollenKey { uint32_t instance; uint32_t type; uint32_t group; };
const wchar_t* __cdecl GetAssetName(PollenKey* key);                         // 0x552580 SP::Pollen::GetAssetName
uint32_t __cdecl InitVerbCollection(uint32_t v);                             // 0x4bb860
int __cdecl Sprintf16(wchar_t* dst, const wchar_t* fmt, ...);                // 0x9399c0
int __cdecl appendW(wchar_t* dst, const wchar_t* src, int cap);              // 0x92cb90
void __cdecl WideToNarrow(const wchar_t* src, char* dst, int cap);           // 0x6b8db0
int __cdecl Snprintf8(char* dst, int cap, const char* fmt, ...);             // 0x9384e0
float* __cdecl matrix_to_quaternion(float* outQuat, float* inMat3x3);        // 0x9a4f10
void __cdecl NormalizeFlags(void* p);                                        // 0x9fc220 (on body+0x150)
float* __cdecl ComputeBodyVector(float* out, void* body, float scale);       // 0x9b53f0
void __cdecl FinishNoBranches(void* sd);                                     // 0x9cbdb0
char __cdecl PostProcess(void* sd);                                          // 0x9c4a30
namespace nSPCreatureAnim {
#define BF(o) at<float>(b, (o))
}
namespace nSPCreatureAnim {
#define BU(o) at<uint32_t>(b, (o))
}
// ---- items of slice s009cbee0 end

// @ 0x009c8a90
void cBlockBlockCommand::OnEndBlock(bool bCancel)
{
    if (bCancel)
        return;

    CreatureCommandState* s = mState;
    BlockDef* b = s->block;
    checkerlib::vector_3_s009c_8a90 tmp;
    checkerlib::vector_3_s009c_8a90 mid = (s->boxMax + s->boxMin) * 0.5f;

    const checkerlib::vector_3_s009c_8a90* r = checkerlib::QuaternionVectorTransform(&tmp, &b->orient, &mid);
    s = mState;
    checkerlib::vector_3_s009c_8a90 c = *r + s->anchor;
    b->center.x = c.x; b->center.y = c.y; b->center.z = c.z;

    checkerlib::vector_3_s009c_8a90 d = s->anchor - c;
    r = QuaternionVectorTransformInverse(&tmp, &b->orient, &d);
    b->local = *r;

    s = mState;
    b->half = (s->boxMax - s->boxMin) * 0.5f;
    if (b->half.x <= 0.0f) b->half.x = 0.5f;
    if (b->half.y <= 0.0f) b->half.y = 0.5f;
    if (b->half.z <= 0.0f) b->half.z = 0.5f;

    FUN_009fc220(b->flags());
    int parentIdx = b->parent;
    b->childMark = -1;
    b->refCount = 0;

    if (parentIdx != -1) {
        BlockDef* p = mState->owner->blocks + parentIdx;
        p->refCount++;
        s = mState;
        // anchor2 relative to the parent block / this block, rotated by that block's orientation
        checkerlib::vector_3_s009c_8a90 vp, vb;
        vp.x = s->anchor2.x - p->center.x; vp.y = s->anchor2.y - p->center.y; vp.z = s->anchor2.z - p->center.z;
        checkerlib::vector_3_s009c_8a90 rp = QuaternionVectorTransformInverse(p->orient, vp);
        b->parentOffset.x = rp.x; b->parentOffset.y = rp.y; b->parentOffset.z = rp.z;
        vb.x = s->anchor2.x - b->center.x; vb.y = s->anchor2.y - b->center.y; vb.z = s->anchor2.z - b->center.z;
        checkerlib::vector_3_s009c_8a90 rb = QuaternionVectorTransformInverse(b->orient, vb);
        b->parentLocal.x = rb.x; b->parentLocal.y = rb.y; b->parentLocal.z = rb.z;
        r = ScaledOffset(&tmp, b, 1.0f);
        b->scaled = *r;
        b->scaledLen = (float)sqrt(b->scaled.x * b->scaled.x + b->scaled.y * b->scaled.y
                                   + b->scaled.z * b->scaled.z);
    }

    b->limit = FLT_MAX;
    if (b->hash == (uint32_t)-1) {
        if (b->name[0] == '0' && b->name[1] == 'x')
            b->hash = strtol(b->name, 0, 16);
        else
            b->hash = EA::Hash::FNV1_String8(b->name, 0x811c9dc5, 1);
    }

    float sc = b->scale;
    CreatureCommandState* st = mState;
    b->offset.x = b->offset.x * sc;
    b->offset.y = sc * b->offset.y;
    b->offset.z = b->offset.z * sc;
    b->offset.x = b->local.x + b->offset.x;
    b->offset.y = b->local.y + b->offset.y;
    b->offset.z = b->local.z + b->offset.z;
    st->count++;
}

// @ 0x009c9910
namespace nSPCreatureAnim {
bool creature_instance_data_s009c_9910::UpdateEffect(cAnimEffect* effect)
{
    bool result = false;
    checkerlib::vector_3_s009c_9910 pos;

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
            checkerlib::vector_3_s009c_9910 pos2;
            checkerlib::vector_4_s009c_9910 quat;
            checkerlib::vector_3_s009c_9910 colorPos;
            checkerlib::vector_3_s009c_9910 colorPos2;
            checkerlib::vector_4_s009c_9910 colorQuat;
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
                        checkerlib::matrix_3x3_s009c_9910 rotMatrix = checkerlib::QuaternionToMatrix(checkerlib::QuaternionConjugate(quat));
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
                    checkerlib::Length2(pos - effect->mLastSoundPos) >= 0.25f) {
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
        checkerlib::vector_4_s009c_9910 q;
        if (effect->mBoneIndex < BoneCount()) {
            creature_bone& bone = mBonesBegin[effect->mBoneIndex];
            pos.x = effect->mOffset.x;
            pos.y = effect->mOffset.y;
            pos.z = effect->mOffset.z;
            if (effect->mbScaleWithCreature)
                pos *= scale;
            checkerlib::vector_3_s009c_9910 local = bone.pos + checkerlib::QuaternionVectorTransform(bone.rot, pos);
            pos = checkerlib::QuaternionVectorTransform(rot, local) + this->pos;
            q = checkerlib::QuaternionProduct(checkerlib::QuaternionProduct(rot, bone.rot), effect->mRotation);
        } else {
            pos = this->pos + checkerlib::QuaternionVectorTransform(rot, effect->mOffset);
            q = checkerlib::QuaternionProduct(rot, effect->mRotation);
        }
        checkerlib::matrix_3x3_s009c_9910 rotMatrix = checkerlib::QuaternionToMatrix(checkerlib::QuaternionConjugate(q));

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
            if (checkerlib::Length2(pos - effect->mLastSoundPos) >= 0.25f) {
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
}  // namespace nSPCreatureAnim

// @ 0x009cbee0
namespace nSPCreatureAnim {
char InitCreatureStaticDataFromResource(creature_static_data_s009c_bee0* sdp, void* res)
{
    char* sd = (char*)sdp;
    uint8_t* r = (uint8_t*)res;
    uint32_t boneMap[255];

    ((StaticDataStub*)sd)->Clear(0);
    at<uint32_t>(sd, 0x318) = at<uint32_t>(r, 8);        // instance_id
    at<uint32_t>(sd, 0x31c) = at<uint32_t>(r, 0x10);     // group_id
    at<uint32_t>(sd, 0x320) = InitVerbCollection(at<uint32_t>(r, 0x18));  // type_id

    PollenKey key;
    key.instance = at<uint32_t>(r, 8);
    key.type = 0x30bdee3;
    uint32_t baseGroup = at<uint32_t>(r, 0x10) & 0xe0ffffff;
    key.group = baseGroup;
    const wchar_t* assetName = GetAssetName(&key);
    if (assetName) {
        const wchar_t* suffix = L"";
        if (baseGroup != at<uint32_t>(r, 0x10)) suffix = L" (baby)";
        Sprintf16((wchar_t*)sd, L"%s%s", assetName, suffix);
    } else {
        appendW((wchar_t*)sd, L"No Pollen Metadata", 0x104);
    }
    WideToNarrow((wchar_t*)sd, sd + 0x208, 0x100);  // filename

    // skin_colors[3] (vector_3 each) at +0x324
    {
        float* src = (float*)(r + 0x38);
        float* dst = (float*)(sd + 0x324);
        for (int i = 3; i != 0; --i) {
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            src += 3;
            dst += 3;
        }
    }

    int numBodies = (at<int>(r, 0x9c) - at<int>(r, 0x98)) / 0x8c;
    char* bodiesVec = sd + 0x384;  // eastl::vector<creature_body_static_data> Bodies (begin at +0x384, end at +0x388)
    ((BodyVecStub*)bodiesVec)->resize(numBodies);

    int meshBones = 0;  // num_bones_with_mesh_parts
    if (numBodies != 0) {
        short s = at<short>(at<char*>(r, 0x98), 4);
        if (s != -1) {
            meshBones = s;
            at<int>(sd, 0x3f0) = 1;
        }
    }
    at<int>(sd, 0x378) = meshBones;
    at<uint8_t>(sd, 0x380) = 0;
    at<uint8_t>(sd, 0x3f5) = at<uint8_t>(r, 0x110) & 1;

    {
        int srcOff = 0;
        for (int i = 0; i < numBodies; ++i) {
            char* sb = at<char*>(r, 0x98) + srcOff;  // source body record, stride 0x8c
            int bidx;
            if (i < meshBones)
                bidx = i + 1;
            else
                bidx = -(int)(i != meshBones) & i;
            char* b = at<char*>(bodiesVec, 0) + bidx * 0x468;
            ((BodyStub*)b)->Clear();
            BU(0x108) = at<uint32_t>(sb, 0x84);  // group_id
            uint32_t instId = at<uint32_t>(sb, 0x88);
            BU(0x104) = instId;                  // instance_id
            uint32_t grpId = BU(0x108);
            BU(0x1f8) = bidx;                    // caps.bidx
            BU(0x21c) = i;                       // source index
            Snprintf8(b, 0x104, "0x%08x!0x%08x.prop", grpId, instId);
            Snprintf8(b + 0x220, 0x104, "joint_b%d_n%d", bidx, (int)at<short>(sb, 2));
            BF(0x424) = 0.0f;                    // mHipHeight__SCALABLE
            BU(0x428) = 0;                       // foot_chain_foot_bidx
            at<uint8_t>(b, 0x42c) = 0;           // foot_chain_root_joint_bidx
            if (at<uint8_t>(sb, 8) & 0x20) BF(0x424) = at<float>(sb, 0x80);
            if (at<uint8_t>(sb, 8) & 0x40) BU(0x428) = at<uint32_t>(sb, 0x80);
            if (at<uint16_t>(sb, 8) & 0x400) at<uint8_t>(b, 0x42c) = 1;
            at<uint8_t>(b, 0x370) = (uint8_t)(~(uint8_t)(at<uint16_t>(sb, 8) >> 9) & 1);  // left_handed
            at<uint8_t>(b, 0x371) = (uint8_t)(at<uint16_t>(sb, 8) >> 0xb) & 1;
            BF(0x378) = at<float>(sb, 0x2c);     // local_joint_r.y
            BF(0x37c) = at<float>(sb, 0x6c);     // local_joint_r.z

            float cz = at<float>(sb, 0x5c);
            float cy = at<float>(sb, 0x58);
            float cx = at<float>(sb, 0x54);
            float scale = at<float>(sb, 0x2c);
            float e0 = at<float>(sb, 0x14) * scale;
            float e1 = at<float>(sb, 0x18) * scale;
            float e2 = at<float>(sb, 0x1c) * scale;
            float e3 = at<float>(sb, 0x20) * scale;
            float e4 = at<float>(sb, 0x24) * scale;
            float e5 = at<float>(sb, 0x28) * scale;

            float m[9];
            m[1] = 0; m[2] = 0; m[3] = 0; m[5] = 0; m[6] = 0; m[7] = 0;
            m[8] = 1.0f; m[4] = 1.0f; m[0] = 1.0f;
            {
                int k = 0, k1;
                float* p = (float*)(sb + 0x38);
                do {
                    k1 = k + 1;
                    m[k] = p[-2];
                    m[k + 3] = p[-1];
                    m[k + 6] = p[0];
                    k = k1;
                    p += 3;
                } while (k1 < 3);
            }
            float qbuf[4];
            float* q = matrix_to_quaternion(qbuf, m);
            BF(0x118) = q[0];  // rest orientation quaternion
            BF(0x11c) = q[1];
            BF(0x120) = q[2];
            BF(0x124) = q[3];

            float qy = BF(0x11c);
            float hx = (e4 + e1) * 0.5f;
            float hy = (e3 + e0) * 0.5f;
            float hz = (e5 + e2) * 0.5f;
            float qw = BF(0x124);
            float qx = BF(0x118);
            float qyqw = qy * qw;
            float qxqw = qx * qw;
            float qz = BF(0x120);
            float qzqw = qz * qw;
            float nqxqx = -(qx * qx);
            float qzqx = qz * qx;
            float qzqy = qz * qy;
            float t = ((((-(qy * qy) + nqxqx) * hz + (qzqy + qxqw) * hx) + (qzqx - qyqw) * hy) * 2.0f + hz) + cz;
            float dz = cz - t;
            BF(0x114) = t;                       // rest_center.z
            t = ((((qzqx + qyqw) * hz + (qy * qx - qzqw) * hx) + (-(qz * qz) + -(qy * qy)) * hy) * 2.0f + hy) + cx;
            float dx = cx - t;
            float ty = ((((-(qz * qz) + nqxqx) * hx + (qzqy - qxqw) * hz) + (qy * qx + qzqw) * hy) * 2.0f + hx) + cy;
            BF(0x10c) = t;                       // rest_center.x
            BF(0x110) = ty;                      // rest_center.y
            float dy = cy - ty;

            qx = BF(0x118);
            qw = BF(0x124);
            float nxw = -(qx * qw);
            qy = BF(0x11c);
            float nyw = -(qy * qw);
            qz = BF(0x120);
            float nxx = -(qx * qx);
            float nzw = -(qz * qw);
            BF(0x144) = (((-(qz * qz) + -(qy * qy)) * dx + (qy * qx - nzw) * dy) + (qz * qx + nyw) * dz) * 2.0f + dx;
            BF(0x148) = (((qy * qx + nzw) * dx + (-(qz * qz) + nxx) * dy) + (qz * qy - nxw) * dz) * 2.0f + dy;
            BF(0x14c) = (((qz * qx - nyw) * dx + (-(qy * qy) + nxx) * dz) + (qz * qy + nxw) * dy) * 2.0f + dz;
            BF(0x138) = (e3 - e0) * 0.5f;
            BF(0x140) = (e5 - e2) * 0.5f;
            BF(0x13c) = (e4 - e1) * 0.5f;
            for (int k = 0x324; k < 0x330; ++k) at<uint8_t>(b, k) = 0;
            float sc = at<float>(sb, 0x2c);
            float px = at<float>(sb, 0x64);
            float py = at<float>(sb, 0x68);
            float* ext = &BF(0x138);
            float yx = BF(0x148);
            float yy = BF(0x14c);
            BF(0x330) = at<float>(sb, 0x60) * sc + BF(0x144);
            BF(0x334) = yx + px * sc;
            BF(0x338) = yy + py * sc;
            for (int k = 3; k != 0; --k) {
                if (*ext <= 0.0f) *ext = 0.1f;
                ++ext;
            }

            uint32_t nApp = at<uint8_t>(sb, 0x10);
            if (nApp != 0) {
                float* fp = &BF(0x158);
                uint32_t k = 0;
                do {
                    *fp = at<float*>(r, 0xac)[at<uint16_t>(sb, 0xc) + k];
                    uint8_t v = at<uint8_t*>(r, 0xc0)[at<uint16_t>(sb, 0xc) + k];
                    ++k;
                    at<uint8_t>(b, 0x1d6 + k) = v;
                    ++fp;
                } while (k < nApp);
            }
            NormalizeFlags(b + 0x150);
            if (BU(0x154) & 4) ++at<int>(sd, 0x3c8);

            uint32_t v = at<uint8_t>(sb, 0xa);
            if (v == 0) v = 0xffffffff;
            BU(0x33c) = v;
            at<uint8_t>(b, 0x340) = at<uint8_t>(sb, 9) & 1;

            uint32_t nMass = at<uint8_t>(sb, 0x11);
            BU(0x380) = (nMass > 8) ? 8 : nMass;
            if (at<uint8_t>(sb, 0x11) != 0) {
                float* fp = &BF(0x38c);
                uint32_t k = 0;
                do {
                    uint16_t base = at<uint16_t>(sb, 0xe);
                    fp[0] = at<float*>(r, 0xe8)[base + k];
                    fp[2] = at<float*>(r, 0xfc)[base + k];
                    float mass = at<float*>(r, 0xd4)[base + k];
                    fp[-2] = mass;
                    if (mass == 0.0f) at<uint8_t>(sd, 0x380) = 1;
                    ++k;
                    fp += 5;
                } while (k < at<uint8_t>(sb, 0x11));
            }

            short parent = at<short>(sb, 4);
            if (parent == -1) {
                BU(0x1fc) = 0xffffffff;
            } else {
                int pi = parent;
                if (pi < meshBones)
                    BU(0x1fc) = pi + 1;
                else
                    BU(0x1fc) = -(int)(pi != meshBones) & pi;
            }
            srcOff += 0x8c;
            BU(0x200) = (int)at<short>(sb, 6);
            BU(0x204) = 0xffffffff;
            BU(0x208) = 0;
            BU(0x36c) = 0x7f7fffffu;  // FLT_MAX
        }
    }

    // second pass: child offsets relative to parents
    if ((unsigned)numBodies != 0) {
        int off = 0;
        unsigned remaining = numBodies;
        do {
            char* begin = at<char*>(bodiesVec, 0);
            char* b = begin + off;
            char* sb = at<char*>(r, 0x98) + BU(0x21c) * 0x8c;
            if (BU(0x1fc) != 0xffffffff) {
                int poff = BU(0x1fc) * 0x468;
                char* pb = begin + poff;
                ++at<int>(pb, 0x208);  // num_children
                float px = at<float>(sb, 0x54);
                float py = at<float>(sb, 0x58);
                float pz = at<float>(sb, 0x5c);
                if (at<uint8_t>(sb, 0xb) == 5 && at<short>(sb, 4) > -1) {
                    char* ps = at<char*>(r, 0x98) + at<short>(sb, 4) * 0x8c;
                    py = (at<float>(ps, 0x58) + py) * 0.5f;
                    pz = (at<float>(ps, 0x5c) + pz) * 0.5f;
                    px = (px + at<float>(ps, 0x54)) * 0.5f;
                }
                float dy = py - at<float>(pb, 0x110);
                float dx = px - at<float>(pb, 0x10c);
                float qy = at<float>(pb, 0x11c);
                float dz = pz - at<float>(pb, 0x114);
                float qw = at<float>(pb, 0x124);
                float qx = at<float>(pb, 0x118);
                float nxw = -(qx * qw);
                float qz = at<float>(pb, 0x120);
                float nxx = -(qx * qx);
                float nzw = -(qz * qw);
                float qzqy = qz * qy;
                float nyw = -(qy * qw);
                at<float>(b, 0x350) = (((qy * qx - nzw) * dy + (qz * qx + nyw) * dz) + (-(qz * qz) + -(qy * qy)) * dx) * 2.0f + dx;
                at<float>(b, 0x354) = (((-(qz * qz) + nxx) * dy + (qzqy - nxw) * dz) + (qy * qx + nzw) * dx) * 2.0f + dy;
                at<float>(b, 0x358) = (((qz * qx - nyw) * dx + (-(qy * qy) + nxx) * dz) + (qzqy + nxw) * dy) * 2.0f + dz;

                float ex = px - at<float>(b, 0x10c);
                float cqy = at<float>(b, 0x124);
                float cqx = at<float>(b, 0x11c);
                float ey = py - at<float>(b, 0x110);
                float ez = pz - at<float>(b, 0x114);
                float cqw = at<float>(b, 0x118);
                float cqz = at<float>(b, 0x120);
                float ncqwy = -(cqw * cqy);
                float ncqzy = -(cqz * cqy);
                float ncqww = -(cqw * cqw);
                float ncqxy = -(cqx * cqy);
                at<float>(b, 0x344) = (((cqx * cqw - ncqzy) * ey + (cqz * cqw + ncqxy) * ez) + (-(cqz * cqz) + -(cqx * cqx)) * ex) * 2.0f + ex;
                at<float>(b, 0x348) = (((-(cqz * cqz) + ncqww) * ey + (cqz * cqx - ncqwy) * ez) + (cqx * cqw + ncqzy) * ex) * 2.0f + ey;
                at<float>(b, 0x34c) = (((-(cqx * cqx) + ncqww) * ez + (cqz * cqx + ncqwy) * ey) + (cqz * cqw - ncqxy) * ex) * 2.0f + ez;

                float tmp[4];
                float* out = ComputeBodyVector(tmp, b, 1.0f);
                at<float>(b, 0x35c) = out[0];
                at<float>(b, 0x360) = out[1];
                at<float>(b, 0x364) = out[2];
                at<float>(b, 0x368) = sqrtf(at<float>(b, 0x35c) * at<float>(b, 0x35c) +
                                                       at<float>(b, 0x360) * at<float>(b, 0x360) +
                                                       at<float>(b, 0x364) * at<float>(b, 0x364));
            }
            off += 0x468;
        } while (--remaining != 0);
    }

    if (at<int>(sd, 0x3c8) == 0 && at<int>(sd, 0x3f0) == 0) FinishNoBranches(sd);
    char ok = PostProcess(sd);
    if (at<uint8_t>(sd, 0x3f4) == 0) at<uint8_t>(sd, 0x3f5) = 0;

    if (ok != 0) {
        unsigned count = (at<int>(bodiesVec, 4) - at<int>(bodiesVec, 0)) / 0x468;
        for (unsigned i = 0; i < count; ++i) {
            // recompute each time like the original
            char* bb = at<char*>(bodiesVec, 0) + i * 0x468;
            uint32_t srcIdx = at<uint32_t>(bb, 0x21c);
            if (srcIdx < 0xff) boneMap[srcIdx] = at<uint32_t>(bb, 0x1f8);
            count = (at<int>(bodiesVec, 4) - at<int>(bodiesVec, 0)) / 0x468;
        }

        unsigned nWig = (at<int>(r, 0x118) - at<int>(r, 0x114)) / 0x38;
        char* wigVec = sd + 0x398;  // eastl::vector<creature_body_wiggle_static_data> mWiggles
        ((WiggleVecStub*)wigVec)->resize(nWig);
        if (nWig != 0) {
            int srcOff = 0;
            int dstOff = 0;
            do {
                float* w = (float*)(at<char*>(r, 0x114) + srcOff);  // source wiggle record, stride 0x38
                uint32_t bi = boneMap[((uint32_t*)w)[0]];
                char* e = at<char*>(wigVec, 0) + dstOff;           // dest wiggle, stride 0x28
                char* sb = at<char*>(r, 0x98) + ((uint32_t*)w)[0] * 0x8c;
                char* b = at<char*>(bodiesVec, 0);
                at<uint32_t>(e, 4) = bi;
                at<uint32_t>(e, 0) = ((uint32_t*)w)[1];
                at<float>(e, 8) = at<float>(sb, 0x2c);
                float sc = at<float>(sb, 0x2c);
                float w3 = w[3];
                float w4 = w[4];
                float by = at<float>(b, bi * 0x468 + 0x148);
                float bz = at<float>(b, bi * 0x468 + 0x14c);
                at<float>(e, 0xc) = at<float>(b, bi * 0x468 + 0x144) + sc * w[2];
                at<float>(e, 0x10) = by + w3 * sc;
                at<float>(e, 0x14) = bz + w4 * sc;

                float m[9];
                m[1] = 0; m[2] = 0; m[3] = 0; m[5] = 0; m[6] = 0; m[7] = 0;
                m[8] = 1.0f; m[4] = 1.0f; m[0] = 1.0f;
                {
                    int k = 0, k1;
                    float* p = w + 7;
                    do {
                        k1 = k + 1;
                        m[k] = p[-2];
                        m[k + 3] = p[-1];
                        m[k + 6] = p[0];
                        k = k1;
                        p += 3;
                    } while (k1 < 3);
                }
                float qbuf[4];
                float* q = matrix_to_quaternion(qbuf, m);
                srcOff += 0x38;
                at<float>(e, 0x18) = q[0];
                dstOff += 0x28;
                at<float>(e, 0x1c) = q[1];
                --nWig;
                at<float>(e, 0x20) = q[2];
                at<float>(e, 0x24) = q[3];
            } while (nWig != 0);
        }
    }
    return ok;
}
}  // namespace nSPCreatureAnim
